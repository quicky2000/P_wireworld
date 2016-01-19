/*    This file is part of lib_bmp
      The aim of this software is to provide way to interact with BMP
      files
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef MY_COLOR_ALPHA_H
#define MY_COLOR_ALPHA_H

#include "my_color.h"

namespace lib_bmp
{
  class my_color_alpha: public my_color
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const my_color_alpha & p_color);
  public:
    inline my_color_alpha(uint8_t p_R,uint8_t p_G,uint8_t p_B,uint8_t p_alpha=0);
    inline my_color_alpha(void);
    inline void display(void)const;
    inline uint8_t get_alpha(void)const;
    inline bool operator ==(const my_color_alpha & p_color)const;
    inline bool operator !=(const my_color_alpha & p_color)const;
    inline bool operator <(const my_color_alpha & p_color)const;
  private:
	uint8_t m_alpha;
  };

  //----------------------------------------------------------------------------
    bool my_color_alpha::operator ==(const my_color_alpha & p_color)const
    {
    return ((my_color)(*this))==(p_color) && m_alpha == p_color.m_alpha;
    }

  //----------------------------------------------------------------------------
    bool my_color_alpha::operator !=(const my_color_alpha & p_color)const
    {
    return ((my_color)(*this))!=(p_color) || m_alpha != p_color.m_alpha;
    }

  //----------------------------------------------------------------------------
  bool my_color_alpha::operator <(const my_color_alpha & p_color)const
  {
    if(((my_color)(*this))<(p_color))
      {
	return true;
      }
    else if(((my_color)(*this))>(p_color))
      {
	return false;
      }
    else if(m_alpha < p_color.m_alpha)
      {
	return true;
      }
    return false;
  }

 
  //----------------------------------------------------------------------------
  my_color_alpha::my_color_alpha(uint8_t p_R,
				 uint8_t p_G,
				 uint8_t p_B,
				 uint8_t p_alpha):
    my_color(p_R,p_G,p_B),
    m_alpha(p_alpha)
      {
      }


  //----------------------------------------------------------------------------
  my_color_alpha::my_color_alpha(void):
    my_color(),
    m_alpha(0)
  {
  }

  //----------------------------------------------------------------------------
  void my_color_alpha::display(void)const
  {
    my_color::display();
    std::cout << ", A=" << std::setw(3) << (uint32_t)m_alpha ;
  }

  //----------------------------------------------------------------------------
  uint8_t my_color_alpha::get_alpha(void)const
  {
    return m_alpha;
  }

  //----------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const my_color_alpha & p_color)
  {
    p_stream << (my_color)p_color;
    p_stream << ", A=" << std::setw(3) << (uint32_t)p_color.m_alpha ;
    return p_stream;
  }
}
#endif // MY_COLOR_ALPHA_H
//EOF
