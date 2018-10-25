/*    This file is part of simple_gui
      The aim of this software is to provide a simple SDL based GUI
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

#ifdef SIMPLE_GUI_SELF_TEST
#include <iostream>
#include "simple_gui.h"

int main(int argc, char ** argv)
{
    std::cout << "Test simple_gui" << std::endl;
    simple_gui::simple_gui l_gui;
    uint32_t l_width;
    uint32_t l_height;
    uint32_t l_nb_bits_per_pixel;
    l_gui.get_screen_info(l_width,l_height,l_nb_bits_per_pixel);
    std::cout << "Current screen resolution : " << l_width << "*" << l_height << " | " << l_nb_bits_per_pixel << " bits" << std::endl;
    if(!l_width || !l_height) return 0;
    const auto l_window_width = (uint32_t)(l_width * 0.9);
    const auto l_window_height = (uint32_t)(l_height * 0.9);
    l_gui.create_window(l_window_width,
                        l_window_height
                       );
    for(unsigned int l_y = 0;
            l_y < l_window_height;
            ++l_y)
    {
        for(unsigned int l_x = 0;
            l_x < l_window_width;
            ++l_x)
        {
            uint32_t l_color = l_gui.get_color_code((uint8_t)(l_x % 256),(uint8_t)(l_y % 256),(uint8_t)((l_x * l_y) % 256));
            l_gui.set_pixel_without_lock(l_x,l_y,l_color);
        }
        l_gui.refresh();
    }
    return 0;
}
#endif // SIMPLE_GUI_SELF_TEST
//EOF
