/*
    This file is part of wireworld_common
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

#ifndef WIREWORLD_CONFIG_PARSER_H
#define WIREWORLD_CONFIG_PARSER_H

#include "quicky_exception.h"
#include <string>
#include <map>
#include <fstream>

namespace wireworld_common
{
  class wireworld_config_parser
  {
  public:
    inline wireworld_config_parser(const std::string & p_file_name);
    inline void parse(wireworld_types::t_config_items & p_config_items)const;
  private:
    inline void parse_error(const unsigned int & p_line_error,
			    const std::string & p_text_line,
			    const std::string & p_msg,
			    const unsigned int & p_line, 
			    const char * p_file_name)const;
    std::string m_file_name;
  };

  //----------------------------------------------------------------------------
  wireworld_config_parser::wireworld_config_parser(const std::string & p_file_name):
  m_file_name(p_file_name)
  {
  }

  //----------------------------------------------------------------------------
  void wireworld_config_parser::parse_error(const unsigned int & p_line_error,
					    const std::string & p_text_line,
					    const std::string & p_msg,
					    const unsigned int & p_line,
					    const char * p_file_name)const
  {
    std::stringstream l_line;
    l_line << p_line_error;
    throw quicky_exception::quicky_runtime_exception("Parser error : "+p_msg+" in line \""+p_text_line+"\" of file "+m_file_name+":"+l_line.str(),p_line,p_file_name);
  }

  //----------------------------------------------------------------------------
  void wireworld_config_parser::parse(wireworld_types::t_config_items & p_config_items)const
  {
    // Check file existence
    std::ifstream l_input_file;
    l_input_file.open(m_file_name.c_str());
    if(!l_input_file.is_open())
      {
	throw quicky_exception::quicky_runtime_exception("Unable to open file \"" + m_file_name + "\" for read",__LINE__,__FILE__);
      }
    std::string l_line;
    unsigned int l_nb_line = 1;
    while(!l_input_file.eof())
      {
        getline(l_input_file,l_line);
        if("" != l_line)
          {
	    size_t l_pos = l_line.find_first_not_of(" \t");
	    if(std::string::npos != l_pos)
	      {
		l_line = l_line.substr(l_pos);
	      }
	    // Ignore comments
	    if('#' != l_line[0])
	      {
                // Remove comments at the end of line
                l_pos = l_line.find('#');
                if(std::string::npos != l_pos)
                  {
                    l_line = l_line.substr(0,l_pos);
                  }
                // Remove blank characters at the end of line
                l_pos = l_line.find_last_not_of(" \t");
                if(std::string::npos != l_pos && l_pos + 1 < l_line.size())
                  {
                    l_line = l_line.substr(0,l_pos + 1);
                  }

		l_pos = l_line.find(':');
		if(std::string::npos != l_pos)
		  {
		    if(!l_pos)
		      {
			parse_error(l_nb_line,l_line,"Item name is missing",__LINE__,__FILE__);
		      }
		    else if(l_line.size() - 1 == l_pos)
		      {
			parse_error(l_nb_line,l_line,"Item value is missing",__LINE__,__FILE__);
		      }
		    std::string l_item_name = l_line.substr(0,l_pos);
		    std::string l_item_value_str = l_line.substr(l_pos+1);
		    bool l_item_value = false;
		    if("0" == l_item_value_str)
		      {
			l_item_value = false;
		      }
		    else if("1" == l_item_value_str)
		      {
			l_item_value = true;
		      }
		    else
		      {
			parse_error(l_nb_line,l_line,"Item value should be 0 or 1 instead of "+l_item_value_str,__LINE__,__FILE__);
		      }
		    bool l_existing = p_config_items.insert(wireworld_types::t_config_items::value_type(l_item_name,l_item_value)).second;
                    if(!l_existing)
                    {
                       parse_error(l_nb_line,l_line,"Item name \""+l_item_name+"\" has already been defined",__LINE__,__FILE__);
                    }
		  }
		else
		  {
		    parse_error(l_nb_line,l_line,"Character ':' separating item name from value is missing",__LINE__,__FILE__);
		  }

              }
          }
        ++l_nb_line;
      }
    l_input_file.close();

  }
}
#endif // WIREWORLD_CONFIG_PARSER_H
//EOF
