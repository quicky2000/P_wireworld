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

#ifndef WIREWORLD_GENERIC_PARSER_H
#define WIREWORLD_GENERIC_PARSER_H

#include "wireworld_generic_configuration.h"
#include "xmlParser.h"
#include "quicky_exception.h"
#include <sstream>
#include <string>
#include <cstring>


namespace wireworld_common
{
  class wireworld_generic_parser
  {
  public:
    inline wireworld_generic_parser(const std::string & p_input_file);
    inline void parse(wireworld_generic_configuration & p_generic_config);
  private:
    inline void extract_coordinates(const std::string & p_coord_str,int & p_x, int & p_y);
    inline void parse_item_list(const XMLNode & p_node,wireworld_generic_configuration & p_generic_config);
    std::string m_file_name;
  };

  //----------------------------------------------------------------------------
  wireworld_generic_parser::wireworld_generic_parser(const std::string & p_input_file):
    m_file_name(p_input_file)
  {
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_parser::parse(wireworld_generic_configuration & p_generic_config)
  {
    // Check file existence
    std::ifstream l_input_file;
    l_input_file.open(m_file_name.c_str());
    if(!l_input_file.is_open())
      {
	throw quicky_exception::quicky_runtime_exception("Unable to open file \"" + m_file_name + "\" for read",__LINE__,__FILE__);
      }
    l_input_file.close();

    // Parse file
    XMLResults l_err= {eXMLErrorNone,0,0};
    XMLNode l_node = XMLNode::parseFile(m_file_name.c_str(),"generic_definition",&l_err);
    std::string l_error_msg = XMLNode::getError(l_err.error);
      
    if(l_error_msg != "No error")
      {
	std::stringstream l_line_number ;
	l_line_number << l_err.nLine;
	std::stringstream l_column_number ;
	l_column_number << l_err.nColumn;

	l_error_msg = "dom_parser : \"" + l_error_msg+ "\" on line " + l_line_number.str() + " when parsing XML column " + l_column_number.str();
	throw quicky_exception::quicky_logic_exception("dom_parser : \"" + l_error_msg+ "\" on line " + l_line_number.str() + " when parsing XML column " + l_column_number.str()+" of file \""+ m_file_name + "\"",__LINE__,__FILE__);
      }

    // Extract data from XML tree
    int l_nb_child_object = l_node.nChildNode();
    if(l_nb_child_object < 1)
      {
	throw quicky_exception::quicky_logic_exception("Expecting at leat one childre node in generic_definition node in file \"" + m_file_name + "\"",__LINE__,__FILE__);
      }
    if(l_nb_child_object > 2)
      {
	throw quicky_exception::quicky_logic_exception("Expecting nothing more than 2 nodes : origin and item_list in generic_definition node in file \"" + m_file_name + "\"",__LINE__,__FILE__);
      }
    
    const XMLNode & l_first_node = l_node.getChildNode(0);

    if(2 == l_nb_child_object)
      {
	if(strcmp("origin",l_first_node.getName()))
	  {
	    throw quicky_exception::quicky_logic_exception("Expecting nothing first node to be of type \"origin\" rather than \"" + std::string(l_first_node.getName()) + "\" in file \"" + m_file_name + "\"",__LINE__,__FILE__);
	  }
	else
	  {
	    XMLCSTR l_coordinates_str = l_first_node.getAttribute("coord");
	    if(NULL == l_coordinates_str)
	      {
		throw quicky_exception::quicky_logic_exception("Mandatory attribute \"coord\" is missing in node \"origin\" of file \""+m_file_name+"\"",__LINE__,__FILE__);
	      }
	    int l_x = 0;
	    int l_y = 0;
	    extract_coordinates(l_coordinates_str,l_x,l_y);
	    if(l_x < 0 || l_y < 0)
	      {
		throw quicky_exception::quicky_logic_exception("Origin coordinates should positive in value \"" + std::string(l_coordinates_str) + "\"  of \"coord\" attribute in node \"origin\" of file \""+m_file_name+"\"",__LINE__,__FILE__);
	      }
	    p_generic_config.set_origin((unsigned int)l_x,(unsigned int)l_y);
	  }
      }
    const XMLNode & l_second_node = 2 == l_nb_child_object ? l_node.getChildNode(1) : l_node.getChildNode(0);
    const XMLNode & l_item_list_node = 1 == l_nb_child_object ? l_first_node : l_second_node;

    std::string l_node_type = l_item_list_node.getName();
    if("item_list" == l_node_type)
      {
	parse_item_list(l_item_list_node,p_generic_config);
      }
    else
      {
	throw quicky_exception::quicky_logic_exception("Expecting node of type \"item_list\" but get node with type \""+std::string(l_item_list_node.getName())+"\" in file \"" + m_file_name + "\"",__LINE__,__FILE__);
      }
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_parser::parse_item_list(const XMLNode & p_node, wireworld_generic_configuration & p_generic_config)
  {
    int l_nb_child_object = p_node.nChildNode();
    for(int l_index = 0 ; l_index < l_nb_child_object ; ++l_index)
      {
	const XMLNode & l_conf_node = p_node.getChildNode(l_index);
	std::string l_node_type = l_conf_node.getName();
	if("item" == l_node_type)
	  {
	    XMLCSTR l_name_str = l_conf_node.getAttribute("name");
	    if(NULL == l_name_str)
	      {
		throw quicky_exception::quicky_logic_exception("Mandatory attribute \"name\" is missing in node \"" + std::string(l_node_type) + "\" of file \""+m_file_name+"\"",__LINE__,__FILE__);
	      }
	    wireworld_generic_item l_generic_item(l_name_str);
	    bool l_empty_item = true;
	    XMLCSTR l_e_head_str = l_conf_node.getAttribute("e_head");
	    if(NULL != l_e_head_str)
	      {
		l_empty_item = false;
		int l_x = 0;
		int l_y = 0;
		extract_coordinates(l_e_head_str,l_x,l_y);
		l_generic_item.set_electron_head(l_x,l_y);
	      }
	    XMLCSTR l_e_queue_str = l_conf_node.getAttribute("e_queue");
	    if(NULL != l_e_queue_str)
	      {
		l_empty_item = false;
		int l_x = 0;
		int l_y = 0;
		extract_coordinates(l_e_queue_str,l_x,l_y);
		l_generic_item.set_electron_queue(l_x,l_y);
	      }
	    if(l_empty_item)
	      {
		throw quicky_exception::quicky_logic_exception("Item should contain an attribute \"e_queue\" or an attribure \"e_head\"in file \""+m_file_name+"\"",__LINE__,__FILE__);
	      }
	    p_generic_config.add(l_generic_item);
	  }
	else
	  {
	    throw quicky_exception::quicky_logic_exception("Expecting node of type \"item\" but get node with type \""+std::string(l_conf_node.getName())+"\" in file \"" + m_file_name + "\"",__LINE__,__FILE__);
	  }
      }
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_parser::extract_coordinates(const std::string & p_coord_str,int & p_x, int & p_y)
  {
    size_t l_pos = p_coord_str.find(',');
    if(std::string::npos == l_pos)
      {
	throw quicky_exception::quicky_logic_exception("Attribute \"e_queue\" should be of the form \"x,y\" : ',' character is missing : \""+p_coord_str+"\" in generic item of file \""+m_file_name+"\"",__LINE__,__FILE__);
      }
    if(!l_pos)
      {
	throw quicky_exception::quicky_logic_exception("Attribute \"e_queue\" should be of the form \"x,y\" : coordinate is missing before ',' character in : \""+p_coord_str+"\" in generic item of file \""+m_file_name+"\"",__LINE__,__FILE__);
      }
    std::string l_x = p_coord_str.substr(0,l_pos);
    if(p_coord_str.size() -1 == l_pos)
      {
	throw quicky_exception::quicky_logic_exception("Attribute \"e_queue\" should be of the form \"x,y\" : coordinate is missing after ',' character in : \""+p_coord_str+"\" in generic item of file \""+m_file_name+"\"",__LINE__,__FILE__);
      }
    std::string l_y = p_coord_str.substr(l_pos+1);
    p_x = atoi(l_x.c_str());
    p_y = atoi(l_y.c_str());
  }

}
#endif // WIREWORLD_GENERIC_PARSER_H
//EOF
