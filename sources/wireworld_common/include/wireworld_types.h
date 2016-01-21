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

#ifndef WIREWORLD_TYPES_H
#define WIREWORLD_TYPES_H

#include "wireworld_generic_item.h"
#include <cinttypes>
#include <string>
#include <cassert>
#include <map>
#include <vector>

namespace wireworld_common
{
  class wireworld_types
  {
  public:
    typedef std::pair<uint32_t,uint32_t> t_coordinates;
    typedef enum class cell_state_t {COPPER=0,TAIL,ELECTRON} t_cell_state;
    inline static const std::string & cell_state2string(const t_cell_state & p_state);
    typedef std::vector<t_coordinates> t_cell_list;
    typedef std::map<t_coordinates,t_cell_list> t_neighbours;
    typedef std::vector<wireworld_generic_item> t_item_list;
    typedef std::map<std::string,bool> t_config_items;
  private:
    static std::string m_state2string[3];
  };

  //----------------------------------------------------------------------------
  const std::string & wireworld_types::cell_state2string(const t_cell_state & p_state)
    {
      assert((unsigned int)p_state < 3);
      return m_state2string[(unsigned int)p_state];
    }
}
#endif // WIREWORLD_TYPES_H
//EOF
