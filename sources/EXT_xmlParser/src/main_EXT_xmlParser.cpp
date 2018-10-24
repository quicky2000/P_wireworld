/*    This file is part of EXT_xmlParser
      Copyright (C) 2018  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifdef EXT_XMLPARSER_SELF_TEST

#include "xmlParser.h"
#include <iostream>
#include <fstream>

int main(void)
{
    std::cout << "Create XML file" << std::endl;
    std::ofstream l_xml_file;
    l_xml_file.open("dummy.xml");
    if(!l_xml_file.is_open())
    {
        std::cout << "Unable to generate XML file" << std::endl;
        exit(-1);
    }
    l_xml_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    l_xml_file << "<DATA version=\"1.0\">" << std::endl;
    l_xml_file << "<component name=\"Hello World\"/>" << std::endl;
    l_xml_file << "</DATA>" << std::endl;
    l_xml_file.close();

    // this open and parse the XML file:
    std::cout << "Parse XML file" << std::endl;
    XMLNode l_main_node=XMLNode::openFileHelper("dummy.xml","DATA");
    std::string l_name = l_main_node.getChildNode("component").getAttribute("name");
    std::cout << "component name : \"" << l_name << "\"" << std::endl;

    return "Hello World" != l_name;
}
#endif // EXT_XMLPARSER_SELF_TEST
// EOF
