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
#ifndef WIREWORLD_PARSER
#define WIREWORLD_PARSER

#include "wireworld_types.h"
#include "quicky_exception.h"
#include <string>
#include <fstream>
#include <vector>
#include <cinttypes>

namespace wireworld_common
{
  class wireworld_parser
  {
  public:
    inline static void parse(const std::string & p_file_name,
                             std::vector<wireworld_types::t_coordinates > & p_copper_cells,
                             std::vector<wireworld_types::t_coordinates > & p_tail_cells,
                             std::vector<wireworld_types::t_coordinates > & p_electron_cells);
                      
  private:
  };

  //----------------------------------------------------------------------------
  void wireworld_parser::parse(const std::string & p_file_name,
                               std::vector<wireworld_types::t_coordinates > & p_copper_cells,
                               std::vector<wireworld_types::t_coordinates > & p_tail_cells,
                               std::vector<wireworld_types::t_coordinates > & p_electron_cells)
  {
    std::ifstream l_input_file(p_file_name.c_str());
    if(!l_input_file.is_open())
      {
        throw quicky_exception::quicky_runtime_exception("Unable to open file \"" + p_file_name + "\"",__LINE__,__FILE__);
      }
    std::string l_line;
    uint32_t l_nb_line = 0;
    while(!l_input_file.eof())
      {
        getline(l_input_file,l_line);
        if(!l_input_file.eof())
          {
            uint32_t l_size = l_line.length();
            for(uint32_t l_index = 0 ; l_index < l_size ; ++l_index)
              {
                switch(l_line[l_index])
                  {
                  case '.':
                  case ' ':
                    break;
                  case 'E':
                    p_copper_cells.push_back(std::pair<uint32_t,uint32_t>(l_index,l_nb_line));
                    p_electron_cells.push_back(std::pair<uint32_t,uint32_t>(l_index,l_nb_line));
                    break;
                  case 'Q':
                    p_copper_cells.push_back(std::pair<uint32_t,uint32_t>(l_index,l_nb_line));
                    p_tail_cells.push_back(std::pair<uint32_t,uint32_t>(l_index,l_nb_line));
                    break;
                  case '#':
                    p_copper_cells.push_back(std::pair<uint32_t,uint32_t>(l_index,l_nb_line));
                    break;
                  }
              }
          }
        ++l_nb_line;
      }
    l_input_file.close();
  }
}
#endif // WIREWORLD_PARSER
//EOF
