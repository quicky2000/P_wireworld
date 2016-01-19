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
#ifndef MY_COLOR_H
#define MY_COLOR_H

#include <inttypes.h>
#include <iomanip>
#include <iostream>

namespace lib_bmp
{
  class my_color
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const my_color & p_color);
  public:
    inline my_color(void);
    inline my_color(uint8_t p_R,
		    uint8_t p_G,
		    uint8_t p_B);

    inline bool operator ==(const my_color & p_color)const;
    inline bool operator <(const my_color & p_color)const;
    inline bool operator >(const my_color & p_color)const;
    inline bool operator !=(const my_color & p_color)const;
    inline void set_red(uint8_t p_r);
    inline void set_green(uint8_t p_g);
    inline void set_blue(uint8_t p_b);
    inline uint8_t get_red(void)const;
    inline uint8_t get_green(void)const;
    inline uint8_t get_blue(void)const;
    inline virtual void display(void)const;
    inline virtual ~my_color(void){}
  private:
    uint8_t m_R;
    uint8_t m_G;
    uint8_t m_B;
  };


  //----------------------------------------------------------------------------
  my_color::my_color(void):
    m_R(0),
    m_G(0),
    m_B(0)
      {
      }

    //----------------------------------------------------------------------------
    my_color::my_color(uint8_t p_R,
		       uint8_t p_G,
		       uint8_t p_B):
      m_R(p_R),
      m_G(p_G),
      m_B(p_B)
	{
	}

      //----------------------------------------------------------------------------
      bool my_color::operator ==(const my_color & p_color)const
      {
	return m_R==p_color.m_R && m_G==p_color.m_G && m_B==p_color.m_B;
      }

      //----------------------------------------------------------------------------
      bool my_color::operator <(const my_color & p_color)const
      {
	if(m_R < p_color.m_R)
	  {
	    return true;
	  }
	else if(m_R > p_color.m_R)
	  {
	    return false;
	  }
	else if(m_G < p_color.m_G)
	  {
	    return true;
	  }
	else if(m_G > p_color.m_G)
	  {
	    return false;
	  }
	else if(m_B < p_color.m_B)
	  {
	    return true;
	  }
	return false;
      }

      //----------------------------------------------------------------------------
      bool my_color::operator >(const my_color & p_color)const
      {
	if(m_R > p_color.m_R)
	  {
	    return true;
	  }
	else if(m_R < p_color.m_R)
	  {
	    return false;
	  }
	else if(m_G > p_color.m_G)
	  {
	    return true;
	  }
	else if(m_G < p_color.m_G)
	  {
	    return false;
	  }
	else if(m_B > p_color.m_B)
	  {
	    return true;
	  }
	return false;
      }

      //----------------------------------------------------------------------------
      bool my_color::operator !=(const my_color & p_color)const
      {
	return m_R != p_color.m_R || m_G != p_color.m_G || m_B != p_color.m_B;
      }

      //----------------------------------------------------------------------------
      void my_color::set_red(uint8_t p_r)
      {
	m_R = p_r;
      }

      //----------------------------------------------------------------------------
      void my_color::set_green(uint8_t p_g)
      {
	m_G = p_g;
      }

      //----------------------------------------------------------------------------
      void my_color::set_blue(uint8_t p_b)
      {
	m_B = p_b;
      }

      //----------------------------------------------------------------------------
      uint8_t my_color::get_red(void)const
      {
	return m_R;
      }

      //----------------------------------------------------------------------------
      uint8_t my_color::get_green(void)const
      {
	return m_G;
      }

      //----------------------------------------------------------------------------
      uint8_t my_color::get_blue(void)const
      {
	return m_B;
      }

      //----------------------------------------------------------------------------
      void my_color::display(void)const
      {
	std::cout << "R=" << std::setw(3) << (uint32_t)m_R << ", G=" << std::setw(3) << (uint32_t)m_G << ", B=" << std::setw(3) << (uint32_t)m_B ;
      }

      //----------------------------------------------------------------------------
      inline std::ostream & operator<<(std::ostream & p_stream,const my_color & p_color)
      {
	p_stream << "R=" << std::setw(3) << (uint32_t)p_color.m_R << ", G=" << std::setw(3) << (uint32_t)p_color.m_G << ", B=" << std::setw(3) << (uint32_t)p_color.m_B ;
	return p_stream;
      }
}
#endif // MY_COLOR_H
//EOF
