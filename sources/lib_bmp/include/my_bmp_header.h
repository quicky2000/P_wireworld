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
#ifndef MY_BMP_HEADER_H
#define MY_BMP_HEADER_H

#include "quicky_C_io.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

namespace lib_bmp
{
  class my_bmp_header
  {
  public:
    inline my_bmp_header(FILE * p_file);
    inline void save(FILE *p_file)const;
    inline my_bmp_header(uint32_t p_width,
			 uint32_t p_height,
			 uint16_t p_nb_bits_per_pixel,
			 uint32_t p_palette_size);
    inline uint32_t get_palette_size(void)const;
    inline void display(void)const;

    inline const uint16_t & get_nb_bits_per_pixel(void)const;
    inline const uint32_t & get_width(void)const;
    inline const uint32_t & get_height(void)const;
    inline const uint32_t & get_picture_size(void)const;

  private:
    inline uint32_t compute_picture_size(uint32_t p_width,
					 uint32_t p_height,
					 uint16_t p_nb_bits_per_pixel);

    uint8_t m_file_type[2];
    uint32_t m_file_size;
    uint32_t m_reserved;
    uint32_t m_offset;
    uint32_t m_remaining_header_size;
    uint32_t m_picture_width;
    uint32_t m_picture_height;
    uint16_t m_nb_plan;
    uint16_t m_nb_bits_per_pixel;
    uint32_t m_compression;
    uint32_t m_picture_size;
    uint32_t m_nb_horizontal_pixel_per_meter;
    uint32_t m_nb_vertical_pixel_per_meter;
    uint32_t m_nb_colour_used;
    uint32_t m_nb_important_colors;
  };

  //----------------------------------------------------------------------------
  my_bmp_header::my_bmp_header(FILE * p_file):
    m_reserved(0),
    m_offset(54),
    m_remaining_header_size(40),
    m_picture_width(0),
    m_picture_height(0),
    m_nb_plan(1),
    m_nb_bits_per_pixel(0),
    m_compression(0),
    m_picture_size(0),
    m_nb_horizontal_pixel_per_meter(3780),
    m_nb_vertical_pixel_per_meter(3780),
    m_nb_colour_used(0),
    m_nb_important_colors(0)
      {
	assert(p_file);

	quicky_utils::quicky_C_io::my_fread<sizeof(uint8_t)>(&m_file_type,2,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_file_size,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_reserved,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_offset,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_remaining_header_size,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_picture_width,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_picture_height,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint16_t)>(&m_nb_plan,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint16_t)>(&m_nb_bits_per_pixel,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_compression,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_picture_size,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_nb_horizontal_pixel_per_meter,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_nb_vertical_pixel_per_meter,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_nb_colour_used,1,p_file);
	quicky_utils::quicky_C_io::my_fread<sizeof(uint32_t)>(&m_nb_important_colors,1,p_file);
	if(!m_picture_size)
	  {
	    m_picture_size = compute_picture_size(m_picture_width,m_picture_height,m_nb_bits_per_pixel);
	    std::cout << "Picture size read from file is 0 so replacing this by computed value " << m_picture_size << std::endl ;
	  }
      }

    //----------------------------------------------------------------------------
    void my_bmp_header::save(FILE *p_file)const
    {
      assert(p_file);

      fwrite(&m_file_type,sizeof(uint8_t),2,p_file);
      fwrite(&m_file_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_reserved,sizeof(uint32_t),1,p_file);
      fwrite(&m_offset,sizeof(uint32_t),1,p_file);
      fwrite(&m_remaining_header_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_width,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_height,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_plan,sizeof(uint16_t),1,p_file);
      fwrite(&m_nb_bits_per_pixel,sizeof(uint16_t),1,p_file);
      fwrite(&m_compression,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_horizontal_pixel_per_meter,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_vertical_pixel_per_meter,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_colour_used,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_important_colors,sizeof(uint32_t),1,p_file);
    }

    //----------------------------------------------------------------------------
    my_bmp_header::my_bmp_header(uint32_t p_width,
				 uint32_t p_height,
				 uint16_t p_nb_bits_per_pixel,
				 uint32_t p_palette_size):
      m_file_size(0),
      m_reserved(0),
      m_offset(54+p_palette_size*4),
      m_remaining_header_size(40),
      m_picture_width(p_width),
      m_picture_height(p_height),
      m_nb_plan(1),
      m_nb_bits_per_pixel(p_nb_bits_per_pixel),
      m_compression(0),
      m_picture_size(compute_picture_size(p_width,p_height,p_nb_bits_per_pixel)),
      m_nb_horizontal_pixel_per_meter(3780),
      m_nb_vertical_pixel_per_meter(3780),
      m_nb_colour_used(0),
      m_nb_important_colors(0)
	{
	  m_file_type[0] = 'B';
	  m_file_type[1] = 'M';
	  m_file_size = m_offset+m_picture_size;
	}

      //----------------------------------------------------------------------------
      uint32_t my_bmp_header::get_palette_size(void)const
      {
	return (m_offset - 54) / 4;
      }

      //----------------------------------------------------------------------------
      void my_bmp_header::display(void)const
      {
	std::cout << "File type : \"" << (char)m_file_type[0] << (char)m_file_type[1] << "\"" << std::endl;
	std::cout << "File size : " << m_file_size << std::endl ;
	std::cout << "4 Reserved bytes : " << m_reserved << std::endl ;
	std::cout << "Offset : " << m_offset << std::endl ;
	std::cout << "Remaining header size : " <<  m_remaining_header_size << std::endl ;
	std::cout << "Picture width : " << m_picture_width << std::endl ;
	std::cout << "Picture height : "<< m_picture_height << std::endl ;
	std::cout << "Nb plan : " << m_nb_plan << std::endl ;
	std::cout << "Nb bits per pixel : " << m_nb_bits_per_pixel << std::endl ;
	std::cout << "Compression : " << m_compression << std::endl;
	std::cout << "Picture size : " << m_picture_size << std::endl ;
	std::cout << "Nb horizontal pixel per meter : " << m_nb_horizontal_pixel_per_meter << std::endl ;
	std::cout << "Nb vertical pixel per meter : " << m_nb_vertical_pixel_per_meter << std::endl ;
	std::cout << "Nb colour used : " << m_nb_colour_used << std::endl ;
	std::cout << "Nb important colours : " <<  m_nb_important_colors << std::endl ;
      }

      //----------------------------------------------------------------------------
      const uint16_t & my_bmp_header::get_nb_bits_per_pixel(void)const
      {
	return m_nb_bits_per_pixel;
      }

      //----------------------------------------------------------------------------
      const uint32_t & my_bmp_header::get_width(void)const
      {
	return m_picture_width;
      }

      //----------------------------------------------------------------------------
      const uint32_t & my_bmp_header::get_height(void)const
      {
	return m_picture_height;
      }

      //----------------------------------------------------------------------------
      const uint32_t & my_bmp_header::get_picture_size(void)const
      {
	return m_picture_size;
      }

      //----------------------------------------------------------------------------
      uint32_t my_bmp_header::compute_picture_size(uint32_t p_width,
						   uint32_t p_height,
						   uint16_t p_nb_bits_per_pixel)
      {
	return 4 * p_height * (uint32_t)ceil((p_width * p_nb_bits_per_pixel) / 32.0 );
      }

}

#endif // MY_BMP_HEADER
//EOF
