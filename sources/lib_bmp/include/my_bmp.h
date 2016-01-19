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
#include "my_color_alpha.h"
#include "my_bmp_header.h"
#include "my_palette.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <assert.h>

#ifndef MY_BMP_H
#define MY_BMP_H

namespace lib_bmp
{

  class my_bmp
  {
  public:
    inline my_bmp(uint32_t p_width,
		  uint32_t p_height,
		  uint32_t p_nb_bits_per_pixel);
    inline my_bmp(const std::string & p_name);
    inline const uint32_t & get_width(void)const;
    inline const uint32_t & get_height(void)const;
    inline const uint16_t & get_nb_bits_per_pixel(void)const;
    static inline uint32_t get_default_palette_size(uint32_t p_nb_bits);
    inline const my_palette & get_palette(void)const;
    inline void save(const std::string & p_name)const;
    inline const my_color_alpha & get_pixel_color(uint32_t p_x,
						  uint32_t p_y)const;
    inline void set_pixel_color(uint32_t p_x,
				uint32_t p_y,
				const my_color_alpha &p_color)const;
    inline void display_info(void)const;
    inline ~my_bmp(void);
  private:
    inline uint32_t get_pixel_index(uint32_t p_x,
				    uint32_t p_y,
				    uint32_t p_width,
				    uint32_t p_height,
				    uint32_t p_nb_bits)const;
    inline uint32_t get_pixel_bit_index(uint32_t p_x,
					uint32_t p_y,
					uint32_t p_nb_bits)const;
    inline my_color_alpha & access_pixel(uint32_t p_x,
					 uint32_t p_y)const;
    inline void create_content(void);
    inline void create_palette(FILE *p_file=NULL);

    my_bmp_header *m_header;
    my_palette *m_palette;
    my_color_alpha * m_content;
  };

  //----------------------------------------------------------------------------
  my_bmp::my_bmp(uint32_t p_width,
		 uint32_t p_height,
		 uint32_t p_nb_bits_per_pixel):
    m_header(new my_bmp_header(p_width,p_height,p_nb_bits_per_pixel,get_default_palette_size(p_nb_bits_per_pixel))),
    m_palette(NULL),
    m_content(NULL)
      {
	create_palette();
	create_content();
      }

    //----------------------------------------------------------------------------
    my_bmp::my_bmp(const std::string & p_name):
      m_header(NULL),
      m_palette(NULL),
      m_content(NULL)
	{
	  FILE * l_file= fopen(p_name.c_str(),"r");
	  if(l_file == NULL)
	    {
	      std::cout << "ERROR : Unable to open file \"" << p_name << std::endl ;
	      exit(-1);
	    }

	  m_header = new my_bmp_header(l_file);

	  create_palette(l_file);

	  create_content();

	  // Create temporary buffer containing code picture content 
	  uint8_t * l_tmp_content = new uint8_t[m_header->get_picture_size()];
	  quicky_utils::quicky_C_io::my_fread(l_tmp_content,m_header->get_picture_size(),1,l_file);

	  // Use coded picture to fill the RGB array representing pixels
	  uint16_t l_nb_bits = m_header->get_nb_bits_per_pixel();
	  uint32_t l_width = m_header->get_width();
	  uint32_t l_height = m_header->get_height();
	  for(uint32_t l_y = 0 ; l_y < l_height ; ++l_y)
	    {
	      for(uint32_t l_x = 0 ; l_x < l_width ; ++l_x)
		{
		  my_color_alpha & l_color = access_pixel(l_x,l_y);
		  uint32_t l_index= get_pixel_index(l_x,l_y,l_width,l_height,l_nb_bits);
		  uint32_t l_bit_index= get_pixel_bit_index(l_x,l_y,l_nb_bits);

		  switch(l_nb_bits)
		    {
		    case 1:
		      l_color = m_palette->get_color(((l_tmp_content[l_index])>>(7-l_bit_index))&1);
		      break;
		    case 4:
		      l_color = m_palette->get_color(((l_tmp_content[l_index])>>(4-l_bit_index))&15);
		      break;
		    case 8 :
		      l_color = m_palette->get_color(l_tmp_content[l_index]);
		      break;
		    case 16:
		      std::cout << "ERROR : 16 bits per pixel is not supported" << std::endl ;
		      exit(-1);
		      break;
		    case 24:
		      l_color.set_red(l_tmp_content[l_index+2]);
		      l_color.set_green(l_tmp_content[l_index+1]);
		      l_color.set_blue(l_tmp_content[l_index]);
		      break;
		    default:
		      std::cout << "ERROR : wrong value for field nb bits per pixel " << l_nb_bits << std::endl ;
		      exit(-1);
		    }
  
		}
	    }
	  
	  delete[] l_tmp_content;
	  fclose(l_file);


	  
	}

      //----------------------------------------------------------------------------
      const uint32_t & my_bmp::get_width(void)const
      {
	return m_header->get_width();
      }

      //----------------------------------------------------------------------------
      const uint32_t & my_bmp::get_height(void)const
      {
	return m_header->get_height();
      }

      //----------------------------------------------------------------------------
      const uint16_t & my_bmp::get_nb_bits_per_pixel(void)const
        {
          return m_header->get_nb_bits_per_pixel();
        }

      //----------------------------------------------------------------------------
      uint32_t my_bmp::get_default_palette_size(uint32_t p_nb_bits)
	{
	  return (p_nb_bits >= 16 ? 0 : 1 << p_nb_bits);
	}

      //----------------------------------------------------------------------------
      const my_palette & my_bmp::get_palette(void)const
      {
        if(m_palette) return *m_palette;
        throw quicky_exception::quicky_logic_exception("Try to access to palette which do not exist",__LINE__,__FILE__);
      }

      //----------------------------------------------------------------------------
      void my_bmp::save(const std::string & p_name)const
      {
	FILE * l_file= fopen(p_name.c_str(),"w");
	if(l_file == NULL)
	  {
	    std::cout << "ERROR : Unable to open file \"" << p_name << std::endl ;
	    exit(-1);
	  }

	m_header->save(l_file);
	if(m_palette) m_palette->save(l_file);

	// Create temporary buffer containing code picture content 
	uint8_t * l_tmp_content = new uint8_t[m_header->get_picture_size()];

	// Use RGB array representing pixelsto fill the coded picture 
	uint16_t l_nb_bits = m_header->get_nb_bits_per_pixel();
	uint32_t l_width = m_header->get_width();
	uint32_t l_height = m_header->get_height();
	for(uint32_t l_y = 0 ; l_y < l_height ; ++l_y)
	  {
	    for(uint32_t l_x = 0 ; l_x < l_width ; ++l_x)
	      {
		my_color_alpha & l_color = access_pixel(l_x,l_y);
		uint32_t l_index= get_pixel_index(l_x,l_y,l_width,l_height,l_nb_bits);
		uint32_t l_bit_index= get_pixel_bit_index(l_x,l_y,l_nb_bits);

		switch(l_nb_bits)
		  {

		  case 1:
		    if(m_palette->get_index(l_color))
		      {
			l_tmp_content[l_index]=(l_tmp_content[l_index])|(1<<(7-l_bit_index));
		      }
		    else
		      {
			l_tmp_content[l_index]=(l_tmp_content[l_index])&(~(1<<(7-l_bit_index)));
		      }
		    break;
		  case 4:
		    l_tmp_content[l_index]=(l_tmp_content[l_index])&(~(15<<(4-l_bit_index)));
		      
		    l_tmp_content[l_index]=(l_tmp_content[l_index])|((m_palette->get_index(l_color))<<(4-l_bit_index));
		    break;
		  case 8:
		    l_tmp_content[l_index]=m_palette->get_index(l_color);
		    break;
		  case 16:
		    std::cout << "ERROR : 16 bits per pixel is not supported" << std::endl ;
		    exit(-1);
		    break;
		  case 24:
		    l_tmp_content[l_index+2] = l_color.get_red();
		    l_tmp_content[l_index+1] = l_color.get_green();
		    l_tmp_content[l_index] = l_color.get_blue();
		    break;
		  default:
		    std::cout << "ERROR : wrong value for field nb bits per pixel " << l_nb_bits << std::endl ;
		    exit(-1);
		  }
	      }
	  }
	fwrite(l_tmp_content,m_header->get_picture_size(),1,l_file);
	delete[] l_tmp_content;
	fclose(l_file);
      }

      //----------------------------------------------------------------------------
      const my_color_alpha & my_bmp::get_pixel_color(uint32_t p_x,
						     uint32_t p_y)const
	{
	  return access_pixel(p_x,p_y);
	}

      //----------------------------------------------------------------------------
      void my_bmp::set_pixel_color(uint32_t p_x,
				   uint32_t p_y,
				   const my_color_alpha &p_color)const
      {
	access_pixel(p_x,p_y) = p_color;
      }

      //----------------------------------------------------------------------------
      void my_bmp::display_info(void)const
      {
	m_header->display();
	if(m_palette) m_palette->display();
      }

      //----------------------------------------------------------------------------
      my_bmp::~my_bmp(void)
	{
	  delete m_header;
	  delete m_palette;
	  delete[] m_content;
	}
      //----------------------------------------------------------------------------
      uint32_t my_bmp::get_pixel_index(uint32_t p_x,
				       uint32_t p_y,
				       uint32_t p_width,
				       uint32_t p_height,
				       uint32_t p_nb_bits)const
      {
	return((p_x * p_nb_bits) / 8 + 4 * (p_height - p_y - 1)*(uint32_t)ceil((p_width * p_nb_bits)/32.0));
      }

      //----------------------------------------------------------------------------
      uint32_t my_bmp::get_pixel_bit_index(uint32_t p_x,
					   uint32_t p_y,
					   uint32_t p_nb_bits)const
      {
	return ((p_x * p_nb_bits) % 8);
      }

      //----------------------------------------------------------------------------
      my_color_alpha & my_bmp::access_pixel(uint32_t p_x,
					    uint32_t p_y)const
	{
	  return m_content[m_header->get_width() * p_y + p_x];
	}

      //----------------------------------------------------------------------------
      void my_bmp::create_content(void)
      {
	m_content = new my_color_alpha[m_header->get_width() * m_header->get_height()];
      }

      //----------------------------------------------------------------------------
      void my_bmp::create_palette(FILE *p_file)
      {
	uint32_t l_palette_size = m_header->get_palette_size();
	if(l_palette_size)
	  {
	    m_palette = new my_palette(l_palette_size,p_file);
	  }
      }

}
#endif // MY_BMP_H
//EOF
