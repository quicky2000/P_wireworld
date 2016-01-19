/*
  This file is part of wireworld_computer
  Copyright (C) 2015  Julien Thevenon ( julien_thevenon at yahoo.fr )

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef __PROGRAM_PARSER_H__
#define __PROGRAM_PARSER_H__

#include "wireworld_computer_utils.h"
#include "quicky_exception.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

namespace wireworld_computer
{
  class program_parser
  {
  public:
    static inline void parse(const std::string & p_file_name,
			     wireworld_computer_utils::t_register_informations & p_register_informations);
  private:
    static inline void parser_error(const std::string & p_error_message,
				    const unsigned int & p_line_number,
				    const unsigned int & p_source_line_number,
				    const char * p_file_name);
  };

  //----------------------------------------------------------------------------
  void program_parser::parser_error(const std::string & p_error_message,
				    const unsigned int & p_line_number,
				    const unsigned int & p_source_line_number,
				    const char * p_file_name)
  {
    std::stringstream l_stream;
    l_stream << p_line_number;
    throw quicky_exception::quicky_logic_exception("Parse error : " + p_error_message + " at line " + l_stream.str(),p_source_line_number,p_file_name);
  }

  //----------------------------------------------------------------------------
  void program_parser::parse(const std::string & p_file_name,
			     wireworld_computer_utils::t_register_informations & p_register_informations)
  {
    p_register_informations.clear();
    std::ifstream l_input_file(p_file_name);
    if(!l_input_file.is_open())
      {
	throw quicky_exception::quicky_runtime_exception("Unable to open file \""+p_file_name+"\"",__LINE__,__FILE__);
      }

    std::string l_line;
    uint32_t l_nb_line = 1;
    while(!l_input_file.eof())
      {
        getline(l_input_file,l_line);
        if("" != l_line)
          {
	    // Trim line
	    size_t l_pos = l_line.find_first_not_of(" \t");
	    if(std::string::npos != l_pos)
	      {
		l_line = l_line.substr(l_pos);
	      }
	    // Check if this is a comment
	    if(l_line[0] != ';')
	      {
		// Extract register id
		l_pos = l_line.find(":");
		if(std::string::npos == l_pos)
		  {
		    parser_error("Unable to find ':' that follow register number",l_nb_line,__LINE__,__FILE__);
		  }
		std::string l_register_id_str = l_line.substr(0,l_pos);
		size_t l_blank_pos = l_register_id_str.find_first_not_of("0x123456789ABCDEFabcdef");
		if(std::string::npos != l_blank_pos )
		  {
		    l_register_id_str = l_register_id_str.substr(0,l_blank_pos);
		  }
		unsigned int l_register_id = strtoul(l_register_id_str.c_str(),nullptr,0);

		if(l_pos == l_line.size() - 1)
		  {
		    parser_error("Line is empty after ':' following register id",l_nb_line,__LINE__,__FILE__);
		    l_line = l_line.substr(l_pos+1);
		  }
		l_pos = l_line.find_first_not_of(" \t",l_pos+1);
		l_line = l_line.substr(l_pos);

		// Extract label if any
		std::string l_label;
		if('<' == l_line[0])
		  {
		    l_pos = l_line.find('>');
		    if(std::string::npos == l_pos)
		      {
			parser_error("Missing '>' closing label",l_nb_line,__LINE__,__FILE__);
		      }
		    l_label = l_line.substr(1,l_pos -1);
		    l_pos = l_line.find(':',l_pos);
		    if(std::string::npos == l_pos)
		      {
			parser_error("Missing ':' after label",l_nb_line,__LINE__,__FILE__);
		      }

		    if(l_pos == l_line.size() - 1)
		      {
			parser_error("Line is empty after ':' following label",l_nb_line,__LINE__,__FILE__);
		      }
		    l_line = l_line.substr(l_pos+1);
		    l_pos = l_line.find_first_not_of(" \t");
		    l_line = l_line.substr(l_pos);
		  }

		// Check if there is a comment at the end of line
		std::string l_comment;
		l_pos = l_line.find(";");
		if(std::string::npos != l_pos && l_line.size() > l_pos)
		  {
		    l_comment = l_line.substr(l_pos+1);
		    l_line = l_line.substr(0,l_pos);
		  }

		// Extract main part of the line
		bool l_instruction = false;
		bool l_unused = false;
		uint16_t l_value = 0;
		if(l_line.size() >= 3 && "MOV" == l_line.substr(0,3))
		  {
		    l_instruction = true;
		    l_pos = l_line.find('R');
		    if(std::string::npos == l_pos)
		      {
			parser_error("Unable to find 'R' of destination register",l_nb_line,__LINE__,__FILE__);
		      }
		    if(l_pos == l_line.size() - 1)
		      {
			parser_error("Line is empty after 'R' of destination register",l_nb_line,__LINE__,__FILE__);
		      }
		    l_line = l_line.substr(l_pos+1);
		    
		    l_pos = l_line.find(',');
		    if(std::string::npos == l_pos)
		      {
			parser_error("Unable to find ',' following destination register",l_nb_line,__LINE__,__FILE__);
		      }
		    unsigned int l_dest = strtoul(l_line.substr(0,l_pos).c_str(),nullptr,10);
		    if(l_dest > 63)
		      {
			std::stringstream l_dest_id;
			l_dest_id << l_dest;
			parser_error("Destination register Id " +l_dest_id.str()+" is greater than 63",l_nb_line,__LINE__,__FILE__);
		      }
		    if(l_pos == l_line.size() - 1)
		      {
			parser_error("Line is empty after 'R' of destination register",l_nb_line,__LINE__,__FILE__);
		      }
		    l_line = l_line.substr(l_pos+1);
		    l_pos = l_line.find('R');
		    if(std::string::npos == l_pos)
		      {
			parser_error("Unable to find 'R' of source register",l_nb_line,__LINE__,__FILE__);
		      }
		    if(l_pos == l_line.size() - 1)
		      {
			parser_error("Line is empty after 'R' of source register",l_nb_line,__LINE__,__FILE__);
		      }
		    l_line = l_line.substr(l_pos+1);
		    l_pos = l_line.find_first_not_of("0123456789");
		    if(std::string::npos != l_pos)
		      {
			l_line = l_line.substr(0,l_pos);
		      }
		    unsigned int l_source = strtoul(l_line.c_str(),nullptr,10);
		    if(l_source > 63)
		      {
			std::stringstream l_source_id;
			l_source_id << l_source;
			parser_error("Source register Id " +l_source_id.str()+" is greater than 63",l_nb_line,__LINE__,__FILE__);
		      }
		    l_value = (l_dest << 8) + l_source;
		    
		  }
		else if(l_line.size() >= std::string("UNUSED").size() && "UNUSED" == l_line.substr(0,std::string("UNUSED").size()))
		  {
		    l_unused = true;
		  }
		else
		  {
		    l_pos = l_line.find_first_of(" \t");
		    if(std::string::npos != l_pos)
		      {
			l_line = l_line.substr(0,l_pos);
		      }
		    l_pos = l_line.find_first_not_of("0x123456789abcdefABCDEF");
		    if(std::string::npos != l_pos)
		      {
			parser_error("Unsupported character '"+std::string(1,l_line[l_pos])+"' in value definition",l_nb_line,__LINE__,__FILE__);
		      }
		    l_value = strtoul(l_line.c_str(),nullptr,0);
		  }
		if(!l_unused || "" != l_label || "" != l_comment )
		  {
		    bool l_new = p_register_informations.insert(wireworld_computer_utils::t_register_informations::value_type(l_register_id,register_information(l_instruction,l_value,l_comment,l_label))).second;
		    if(!l_new)
		      {
			parser_error("Register "+l_register_id_str+" already defined",l_nb_line,__LINE__,__FILE__);
		      }
		  }
	      }
          }
        ++l_nb_line;
      }
    l_input_file.close();
  }
}
#endif //__PROGRAM_PARSER_H__
//EOF
