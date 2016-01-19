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
#ifndef _WIREWORLD_GENERIC_ITEM_H_
#define _WIREWORLD_GENERIC_ITEM_H_

#include "quicky_exception.h"
#include <string>
#include <iostream>

namespace wireworld_common
{
  class wireworld_generic_item
  {
    friend std::ostream & operator<<(std::ostream & p_stream, const wireworld_generic_item & p_item);
  public:
    inline wireworld_generic_item(const std::string & p_name);
    inline const std::string & get_name(void)const;
    inline void set_electron_head(const int & p_x, const int & p_y);
    inline void set_electron_queue(const int & p_x, const int & p_y);
    inline bool is_head_defined(void)const;
    inline bool is_queue_defined(void)const;
    typedef std::pair<int,int> t_generic_coordinates;
    inline const t_generic_coordinates & get_head_coord(void)const;
    inline const t_generic_coordinates & get_queue_coord(void)const;

  private:
    std::string m_name;
    bool m_head_defined;
    t_generic_coordinates m_h_coord;
    bool m_queue_defined;
    t_generic_coordinates m_q_coord;    
  };
  //----------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream, const wireworld_generic_item & p_item)
  {
    p_stream << p_item.m_name << "[" ;
    if(p_item.m_head_defined)
      {
	p_stream << "HEAD(" << p_item.m_h_coord.first << "," << p_item.m_h_coord.second << ")" ;
	if(p_item.m_queue_defined)
	  {
	    p_stream << " ";
	  }
      }
    if(p_item.m_queue_defined)
      {
	p_stream << "QUEUE(" << p_item.m_q_coord.first << "," << p_item.m_q_coord.second << ")" ;
     }
    p_stream <<  "]" ;
    return p_stream;
  }

  //----------------------------------------------------------------------------
  wireworld_generic_item::wireworld_generic_item(const std::string & p_name):
    m_name(p_name),
    m_head_defined(false),
    m_h_coord(0,0),
    m_queue_defined(false),
    m_q_coord(0,0)
  {
  }

  //----------------------------------------------------------------------------
  const std::string & wireworld_generic_item::get_name(void)const
  {
    return m_name;
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_item::set_electron_head(const int & p_x, const int & p_y)
  {
    m_head_defined = true;
    m_h_coord = t_generic_coordinates(p_x,p_y);
  }

  //----------------------------------------------------------------------------
  void wireworld_generic_item::set_electron_queue(const int & p_x, const int & p_y)
  {
    m_queue_defined = true;
    m_q_coord = t_generic_coordinates(p_x,p_y);
  }

  //----------------------------------------------------------------------------
  bool wireworld_generic_item::is_head_defined(void)const
  {
    return m_head_defined;
  }

  //----------------------------------------------------------------------------
  bool wireworld_generic_item::is_queue_defined(void)const
  {
    return m_queue_defined;
  }

  //----------------------------------------------------------------------------
  const wireworld_generic_item::t_generic_coordinates & wireworld_generic_item::get_head_coord(void)const
  {
    if(!m_head_defined)
      {
	throw quicky_exception::quicky_logic_exception("Try to access to undefined electron head coordinates for item \""+m_name+"\"",__LINE__,__FILE__);
      }
    return m_h_coord;
  }

  //----------------------------------------------------------------------------
  const wireworld_generic_item::t_generic_coordinates & wireworld_generic_item::get_queue_coord(void)const
  {
    if(!m_queue_defined)
      {
	throw quicky_exception::quicky_logic_exception("Try to access to undefined electron head coordinates for item \""+m_name+"\"",__LINE__,__FILE__);
      }
    return m_q_coord;
  }
}

#endif // _WIREWORLD_GENERIC_ITEM_H_
//EOF
