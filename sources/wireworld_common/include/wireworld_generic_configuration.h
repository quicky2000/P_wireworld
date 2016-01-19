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
#ifndef _WIREWORLD_GENERIC_CONFIGURATION_H_
#define _WIREWORLD_GENERIC_CONFIGURATION_H_

#include "wireworld_generic_item.h"
#include "wireworld_types.h"
#include "quicky_exception.h"
#include <string>
#include <map>
#include <vector>

namespace wireworld_common
{
  class wireworld_generic_configuration
  {
  public:
    inline wireworld_generic_configuration(void);
    inline void add(const wireworld_generic_item & p_item);
    inline bool contains(const std::string & p_name)const;
    inline const wireworld_generic_item & get(const std::string & p_name)const;
    inline void set_origin(const unsigned int & p_x, const unsigned int & p_y);
    inline const wireworld_types::t_item_list & get_configurable_cells(void)const;
  private:
    typedef std::map<std::string,wireworld_generic_item> t_items;
    wireworld_types::t_coordinates m_origin;
    t_items m_items;
    wireworld_types::t_item_list m_item_list;
  };
  //----------------------------------------------------------------------------
  wireworld_generic_configuration::wireworld_generic_configuration(void):
  m_origin(0,0)
  {
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_configuration::set_origin(const unsigned int & p_x, const unsigned int & p_y)
  {
    m_origin = wireworld_types::t_coordinates(p_x,p_y);
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_configuration::add(const wireworld_generic_item & p_item)
  {
    if(m_items.end() != m_items.find(p_item.get_name()))
      {
	throw quicky_exception::quicky_runtime_exception("Item \""+p_item.get_name()+"\" already exists in generic configuration",__LINE__,__FILE__);
      }
    wireworld_generic_item l_item(p_item.get_name());
    if(p_item.is_head_defined())
      {
	const wireworld_generic_item::t_generic_coordinates & l_coord = p_item.get_head_coord();
	l_item.set_electron_head(l_coord.first + m_origin.first,l_coord.second + m_origin.second);
      }
   if(p_item.is_queue_defined())
      {
	const wireworld_generic_item::t_generic_coordinates & l_coord = p_item.get_queue_coord();
	l_item.set_electron_queue(l_coord.first + m_origin.first,l_coord.second + m_origin.second);
      }
   m_items.insert(t_items::value_type(p_item.get_name(),l_item));
    m_item_list.push_back(l_item);
  }

  //----------------------------------------------------------------------------
  bool wireworld_generic_configuration::contains(const std::string & p_name)const
  {
    return m_items.end() != m_items.find(p_name);
  }

  //----------------------------------------------------------------------------
  const wireworld_generic_item & wireworld_generic_configuration::get(const std::string & p_name)const
  {
    t_items::const_iterator l_iter = m_items.find(p_name);
    if(m_items.end() == l_iter)
    {
      throw quicky_exception::quicky_runtime_exception("No item \""+p_name+"\"  in generic configuration",__LINE__,__FILE__);
    }
    return l_iter->second;
  }

  //----------------------------------------------------------------------------
  const wireworld_types::t_item_list & wireworld_generic_configuration::get_configurable_cells(void)const
  {
    return m_item_list;
  }
}

#endif // _WIREWORLD_GENERIC_CONFIGURATION_H_
//EOF
