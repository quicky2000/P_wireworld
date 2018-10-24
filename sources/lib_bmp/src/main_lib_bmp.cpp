/*    This file is part of lib_bmp
      The aim of this software is to provide way to interact with BMP
      files
      Copyright (C) 2017  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifdef LIB_BMP_SELF_TEST

#include "my_bmp.h"

int main(int argc, char ** argv)
{
    lib_bmp::my_bmp l_bmp(640,480,24);
    for(unsigned int l_y = 0;
        l_y < 480;
        ++l_y
        )
    {
        for(unsigned int l_x = 0;
            l_x < 640;
            ++l_x
                )
        {
            lib_bmp::my_color_alpha l_color = lib_bmp::my_color_alpha((uint8_t )(l_x % 256), (uint8_t )(l_y % 256),(uint8_t)((l_x * l_y) % 256));
            l_bmp.set_pixel_color(l_x, l_y,l_color);
        }
    }
    l_bmp.save("test.bmp");
}
#endif // LIB_BMP_SELF_TEST
//EOF

