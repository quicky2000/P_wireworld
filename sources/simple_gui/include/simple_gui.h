/*    This file is part of simple_gui
      The aim of this software is to provide a simple SDL based GUI
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
#ifndef _SIMPLE_GUI_H_
#define _SIMPLE_GUI_H_

#include "SDL/SDL.h"
#include <cinttypes>

namespace simple_gui
{

  class simple_gui
  {
  public:
    simple_gui(void);
    void get_screen_info(uint32_t & p_width,
			 uint32_t & p_height,
			 uint32_t & p_nb_bits_per_pixel);
    void create_window(uint32_t p_width,uint32_t p_height);

    inline uint32_t get_color_code(uint8_t r,uint8_t g,uint8_t b);
    inline void get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b);
    inline void refresh(void);
    inline void refresh(const uint32_t & p_x,
			const uint32_t & p_y,
			const uint32_t & p_width,
			const uint32_t & p_height);
    inline void * save_buffer(void)const;
    inline void load_buffer(void *);
    void * export_rectangle(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height);
    void import_rectangle(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height,void* p_data);
    inline void free_rectangle(void *);

    virtual ~simple_gui(void);
    void set_pixel(uint32_t p_x,uint32_t p_y,uint32_t p_color);
    inline void set_pixel_without_lock(uint32_t p_x,uint32_t p_y,uint32_t p_color);
    uint32_t get_pixel(uint32_t p_x,uint32_t p_y)const;

    inline void set_rectangle_without_lock(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height, const uint32_t & p_color);
    inline void set_rectangle(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height, const uint32_t & p_color);

    void draw_line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t p_color);

    inline void lock(void);
    inline void unlock(void);

    inline const uint32_t & get_width(void)const;
    inline const uint32_t & get_height(void)const;
  private:
    SDL_Surface *m_screen;
    uint32_t m_coef;
    void * m_start;
    uint32_t m_size;
    unsigned int m_width;
    unsigned int m_height;
  };

  //------------------------------------------------------------------------------
  void * simple_gui::save_buffer(void)const
    {
      void * l_buffer = new uint8_t[m_size];
      memset(l_buffer,0,m_size);
      memcpy(l_buffer,m_start,m_size);
      return l_buffer;
    }

  //------------------------------------------------------------------------------
  void simple_gui::load_buffer(void * p_buffer)
  {
    memcpy(m_start,p_buffer,m_size);
  }


  //------------------------------------------------------------------------------
  uint32_t simple_gui::get_color_code(uint8_t r,uint8_t g,uint8_t b)
  {
    return SDL_MapRGB(m_screen->format,r,g,b);
  }

  //------------------------------------------------------------------------------
  void simple_gui::get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b)
  {
    SDL_GetRGB(p_color,m_screen->format,&r,&g,&b);
  }

  //------------------------------------------------------------------------------
  void simple_gui::refresh(void)
  {
    SDL_UpdateRect(m_screen,0,0,0,0);
  }

  //------------------------------------------------------------------------------
  void simple_gui::refresh(const uint32_t & p_x,
			   const uint32_t & p_y,
			   const uint32_t & p_width,
			   const uint32_t & p_height)
  {
    SDL_UpdateRect(m_screen,p_x * m_coef,p_y * m_coef,p_width * m_coef,p_height * m_coef);
  }

  //------------------------------------------------------------------------------
  void simple_gui::set_pixel_without_lock(uint32_t p_x,uint32_t p_y,uint32_t p_color)
  {
#if 1
    for(uint32_t l_x = p_x * m_coef;l_x < m_coef *(p_x + 1);++l_x)
      {
	for(uint32_t l_y = p_y * m_coef;l_y < m_coef *(p_y + 1);++l_y)
	  {
	    if(l_x >= 0 && l_x < m_width && l_y >= 0 && l_y < m_height)
	      {
		uint32_t *l_bufp = (uint32_t *)m_screen->pixels + l_y * m_screen->pitch/4 + l_x;
		*l_bufp = p_color;
	      }
	  }
      } 
#else
    SDL_Rect rect;
    rect.x = p_x * m_coef;
    rect.y = p_y * m_coef;
    rect.w = m_coef  ;
    rect.h = m_coef  ;
    SDL_FillRect( m_screen, &rect, p_color);
#endif

  }

  //------------------------------------------------------------------------------
  void simple_gui::set_rectangle_without_lock(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height, const uint32_t & p_color)
  {
    SDL_Rect rect;
    rect.x = p_x * m_coef;
    rect.y = p_y * m_coef;
    rect.w = m_coef * p_width ;
    rect.h = m_coef * p_height ;
    SDL_FillRect( m_screen, &rect, p_color);
  }

  //------------------------------------------------------------------------------
  void simple_gui::set_rectangle(const uint32_t & p_x,const uint32_t & p_y, const uint32_t & p_width, const uint32_t & p_height, const uint32_t & p_color)
  {
    lock();
    set_rectangle_without_lock(p_x,p_y,p_width,p_height,p_color);
    unlock();
  }

  //------------------------------------------------------------------------------
  void simple_gui::lock(void)
  {
    if ( SDL_MUSTLOCK(m_screen) )
      {
	if ( SDL_LockSurface(m_screen) < 0 )
	  {
	    exit(-1);
	  }
      }
  }

  //------------------------------------------------------------------------------
  void simple_gui::unlock(void)
  {
    if ( SDL_MUSTLOCK(m_screen) )
      {
	SDL_UnlockSurface(m_screen);
      }
  }

  //------------------------------------------------------------------------------
  const uint32_t & simple_gui::get_width(void)const
    {
      return m_width;
    }

  //------------------------------------------------------------------------------
  const uint32_t & simple_gui::get_height(void)const
    {
      return m_height;
    }

  //------------------------------------------------------------------------------
  void simple_gui::free_rectangle(void * p_data)
  {
    SDL_FreeSurface((SDL_Surface*)p_data);
  }
}
#endif // _SIMPLE_GUI_H_
//EOF
