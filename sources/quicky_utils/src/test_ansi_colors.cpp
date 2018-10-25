/*    This file is part of quicky_utils
      Copyright (C) 2018  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifdef QUICKY_UTILS_SELF_TEST

#include "ansi_colors.h"

namespace quicky_utils
{
    void test_ansi_colors()
    {
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::black) << "BLACK" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::red) << "RED" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::green) << "GREEN" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::yellow) << "YELLOW" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::blue) << "BLUE" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::magenta) << "MAGENTA" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::cyan) << "CYAN" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::white) << "WHITE" << std::endl;
        std::cout << quicky_utils::set_fcolor(quicky_utils::ansi_color::def) << "DEF" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::black) << "BLACK" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::red) << "RED" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::green) << "GREEN" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::yellow) << "YELLOW" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::blue) << "BLUE" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::magenta) << "MAGENTA" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::cyan) << "CYAN" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::white) << "WHITE" << std::endl;
        std::cout << quicky_utils::set_bcolor(quicky_utils::ansi_color::def) << "DEF" << std::endl;
        std::cout << quicky_utils::set_bold() << "BOLD" << quicky_utils::set_normal() << " BOLD" << std::endl;
        std::cout << quicky_utils::set_reverse() << "REVERSE" << quicky_utils::set_normal() << " REVERSE" << std::endl;
        std::cout << quicky_utils::set_underline() << "UNDERLINE" << quicky_utils::set_normal() << " UNDERLINE" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::black) << "BLACK" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::red) << "RED" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::green) << "GREEN" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::yellow) << "YELLOW" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::blue) << "BLUE" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::magenta) << "MAGENTA" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::cyan) << "CYAN" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::white) << "WHITE" << std::endl;
        std::cout << quicky_utils::set_bright_fcolor(quicky_utils::ansi_color::def) << "DEF" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::black) << "BLACK" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::red) << "RED" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::green) << "GREEN" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::yellow) << "YELLOW" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::blue) << "BLUE" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::magenta) << "MAGENTA" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::cyan) << "CYAN" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::white) << "WHITE" << std::endl;
        std::cout << quicky_utils::set_bright_bcolor(quicky_utils::ansi_color::def) << "DEF" << std::endl;
        for(unsigned int l_index = 0; l_index < 24; ++l_index)
        {
            std::cout << quicky_utils::set_fcolor(quicky_utils::gray_8b(l_index)) << "GREY[" << l_index << "]" << std::endl;
        }
        std::cout << set_fcolor(quicky_utils::_ansi_color::black);
        for(unsigned int l_index = 0; l_index < 24; ++l_index)
        {
            std::cout << quicky_utils::set_bcolor(quicky_utils::gray_8b(l_index)) << "GREY[" << l_index << "]" << std::endl;
        }
        std::cout << quicky_utils::set_normal() << std::endl;
        for(unsigned int l_r = 0; l_r < 6; ++l_r)
        {
            for(unsigned int l_g = 0; l_g < 6; ++l_g)
            {
                for(unsigned int l_b = 0; l_b < 6; ++l_b)
                {
                    std::cout << quicky_utils::set_fcolor(quicky_utils::color_8b(l_r, l_g, l_b)) << "A";
                }
            }
            std::cout << std::endl;
        }
        std::cout << quicky_utils::set_normal() << std::endl;
        for(unsigned int l_r = 0; l_r < 6; ++l_r)
        {
            for(unsigned int l_g = 0; l_g < 6; ++l_g)
            {
                for(unsigned int l_b = 0; l_b < 6; ++l_b)
                {
                    std::cout << quicky_utils::set_bcolor(quicky_utils::color_8b(l_r, l_g, l_b)) << "A";
                }
            }
            std::cout << std::endl;
        }
        std::cout << quicky_utils::set_normal() << std::endl;
#ifdef TEST_24BITS_COLORS
        for(unsigned int l_r = 0; l_r < 255; ++l_r)
    {
        for(unsigned int l_g = 0; l_g < 255; ++l_g)
        {
            for(unsigned int l_b = 0; l_b < 255; ++l_b)
            {
                std::cout << quicky_utils::set_fcolor(quicky_utils::color_24b(l_r, l_g, l_b)) << "A";
                if(!(l_b % 80)) std::cout << std::endl;
            }
        }
    }
    std::cout << quicky_utils::set_normal() << std::endl;
    for(unsigned int l_r = 0; l_r < 255; ++l_r)
    {
        for(unsigned int l_g = 0; l_g < 255; ++l_g)
        {
            for(unsigned int l_b = 0; l_b < 255; ++l_b)
            {
                std::cout << quicky_utils::set_bcolor(quicky_utils::color_24b(l_r, l_g, l_b)) << "A";
            }
            std::cout << std::endl;
        }
    }
    std::cout << quicky_utils::set_normal() << std::endl;
#endif // TEST_24BITS_COLORS
    }

}

#endif // QUICKY_UTILS_SELF_TEST
// EOF
