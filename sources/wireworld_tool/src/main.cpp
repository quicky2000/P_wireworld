/*
    This file is part of wireworld_tool
    Copyright (C) 2011  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "my_bmp.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc,char ** argv)
{
  if(argc != 2)
    {
      cout << "usage is : main.exe input_file" << endl ;
      exit(-1);
    }

  
  string l_file_name(argv[1]);
  cout << "Input file : \"" << l_file_name << "\"" << endl ;
  std::size_t l_pos = l_file_name.find('.');
  if(l_pos == string::npos)
    {
      cout << "ERROR : file name \"" << l_file_name << "\" has no extension" << endl ;
      exit(-1);
    }
  string l_file_name_without_extension = l_file_name.substr(0,l_pos);
  cout << "File name without extension \"" << l_file_name_without_extension << "\"" << endl ;


  ofstream l_output_h_file((l_file_name_without_extension+".h").c_str());
  if(!l_output_h_file.is_open())
    {
      std::cout << "ERROR : Unable to open output file" << std::endl ;
      exit(-1);
    }

  ofstream l_output_text_file((l_file_name_without_extension+".txt").c_str());
  if(!l_output_text_file.is_open())
    {
      std::cout << "ERROR : Unable to open output file" << std::endl ;
      exit(-1);
    }

  lib_bmp::my_bmp l_bmp(l_file_name);
  l_bmp.display_info();

  uint32_t l_width = l_bmp.get_width();
  uint32_t l_height = l_bmp.get_height();
  for(uint32_t l_y = 0 ; l_y < l_height;++l_y)
    {
      for(uint32_t l_x = 0 ; l_x < l_width ;++l_x)
	{
	  lib_bmp::my_color_alpha l_ref;
	  lib_bmp::my_color_alpha l_electron(255,255,255,0);
	  lib_bmp::my_color_alpha l_tail(0,160,255,0);
	  lib_bmp::my_color_alpha l_copper(255,160,0,0);
	  lib_bmp::my_color_alpha l_color = l_bmp.get_pixel_color(l_x,l_y);

	  if( l_color == l_ref)
	    {
	      l_output_text_file << "." ;
	    }
	  else if(l_color == l_electron)
	    {

	      l_output_h_file << "l_copper_cells.push_back(std::pair<uint32_t,uint32_t>(" << l_x << "," << l_y   << "));" << endl ;
	      l_output_text_file << "E" ;
	      l_output_h_file << "l_electron_cells.push_back(std::pair<uint32_t,uint32_t>(" << l_x << "," << l_y   << "));" << endl ;
	    }
	  else if(l_color == l_tail)
	    {
	      l_output_h_file << "l_copper_cells.push_back(std::pair<uint32_t,uint32_t>(" << l_x << "," << l_y   << "));" << endl ;
	      l_output_text_file << "Q" ;
	      l_output_h_file << "l_tail_cells.push_back(std::pair<uint32_t,uint32_t>(" << l_x << "," << l_y   << "));" << endl ;
	    }
	  else if(l_color == l_copper)
	    {
	      l_output_text_file << "#" ;
	      l_output_h_file << "l_copper_cells.push_back(std::pair<uint32_t,uint32_t>(" << l_x << "," << l_y   << "));" << endl ;
	    }
	  else
	    {
	      std::cout << "ERROR : Unknown color ";
	      l_color.display();
	      std::cout << std::endl;
	      exit(-1);
	    }
	}
      l_output_text_file << std::endl ;
    }

  l_output_h_file.close();
  l_output_text_file.close();
  
  return 0;

}
//EOF
