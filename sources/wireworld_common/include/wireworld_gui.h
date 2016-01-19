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
#ifndef _WIREWORLD_GUI_H_
#define _WIREWORLD_GUI_H_

#include "simple_gui.h"
#include "wireworld_types.h"
#include "quicky_exception.h"
#include <sstream>

namespace wireworld_common
{
  class wireworld_gui: public simple_gui
  {
  public:
    inline wireworld_gui(void);
    inline void createWindow(uint32_t p_width,uint32_t p_height);
    inline void displayCopper(uint32_t p_x,uint32_t p_y);
    inline void displayQueue(uint32_t p_x,uint32_t p_y);
    inline void displayElectron(uint32_t p_x,uint32_t p_y);
    inline void displayCell(uint32_t p_x,uint32_t p_y,const wireworld_types::t_cell_state & p_state);

  private:
    uint32_t m_copper_color;
    uint32_t m_queue_color;
    uint32_t m_electron_color;
  };

  //------------------------------------------------------------------------------
  wireworld_gui::wireworld_gui(void):
    simple_gui(),
    m_copper_color(0),
    m_queue_color(0),
    m_electron_color(0)
      {
      }

    //------------------------------------------------------------------------------
    void wireworld_gui::createWindow(uint32_t p_width,uint32_t p_height)
    {
      simple_gui::createWindow(p_width,p_height);
      m_copper_color = getColorCode(255,160,0);
      m_queue_color = getColorCode(0,160,255);
      m_electron_color = getColorCode(255,255,255);
    }

    //------------------------------------------------------------------------------
    void wireworld_gui::displayCopper(uint32_t p_x,uint32_t p_y)
    {
      setPixel(p_x,p_y,m_copper_color);
    }

    //------------------------------------------------------------------------------
    void wireworld_gui::displayQueue(uint32_t p_x,uint32_t p_y)
    {
      setPixel(p_x,p_y,m_queue_color);
    }

    //------------------------------------------------------------------------------
    void wireworld_gui::displayElectron(uint32_t p_x,uint32_t p_y)
    {
      setPixel(p_x,p_y,m_electron_color);
    }

    //------------------------------------------------------------------------------
    void wireworld_gui::displayCell(uint32_t p_x,uint32_t p_y,const wireworld_types::t_cell_state & p_state)
    {
      switch(p_state)
        {
	case wireworld_types::t_cell_state::COPPER:
          setPixel(p_x,p_y,m_copper_color);
	  break;
	case wireworld_types::t_cell_state::QUEUE:
          setPixel(p_x,p_y,m_queue_color);
	  break;
	case wireworld_types::t_cell_state::ELECTRON:
          setPixel(p_x,p_y,m_electron_color);
	  break;
        default:
	  {
	    std::stringstream l_stream;
	    l_stream << (unsigned int) p_state ;
	    throw quicky_exception::quicky_logic_exception("Unknown state value : "+l_stream.str(),__LINE__,__FILE__);
	  }
        }
    }

}
#endif // _WIREWORLD_GUI_H_ 
//EOF

