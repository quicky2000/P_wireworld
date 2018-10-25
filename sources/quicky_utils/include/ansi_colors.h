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

#ifndef QUICKY_UTILS_ANSI_COLORS_H
#define QUICKY_UTILS_ANSI_COLORS_H

#include "quicky_exception.h"
#include <iostream>
#include <string>
#include <sstream>

namespace quicky_utils
{
    typedef enum class _ansi_color
    {
        black = 0,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white,
        def = 9
    } ansi_color;

    /**
     * More information can be found on https://en.wikipedia.org/wiki/ANSI_escape_code
     */
    class ansi_escape_code
    {
        inline friend
        std::ostream &
        operator<<(std::ostream & p_stream,
                   const ansi_escape_code & p_color
                  );
      protected:
        inline explicit ansi_escape_code(const std::string & p_code);

        std::string m_code;
    };

    class esc_8bits
    {
      public:
        inline const std::string & get_code()const;
      protected:
        inline explicit esc_8bits(unsigned int p_code);
      private:
        const std::string m_code;
    };

    //-------------------------------------------------------------------------
    esc_8bits::esc_8bits(unsigned int p_code):
    m_code("5;" + std::to_string(p_code))
    {
        if(p_code > 255)
        {
            throw quicky_exception::quicky_logic_exception("8 bits escape code should be in range [0,255] : " + std::to_string(p_code), __LINE__, __FILE__);
        }
    }

    //-------------------------------------------------------------------------
    const std::string & esc_8bits::get_code()const
    {
        return m_code;
    }

    /**
     * 8 bits color
     */
    class color_8b: public esc_8bits
    {
      public:
        inline color_8b(unsigned int p_r,
                        unsigned int p_g,
                        unsigned int p_b
                       );
      private:
    };

    //-------------------------------------------------------------------------
    color_8b::color_8b(unsigned int p_r,
                       unsigned int p_g,
                       unsigned int p_b
                      ):
            esc_8bits(16 + 36 * p_r + 6 * p_g + p_b)
    {
        if(p_r > 5 ||  p_g > 5 || p_b > 5)
        {
            std::stringstream l_stream;
            l_stream << "(" << p_r << "," << p_g << "," << p_b << ")";
            throw quicky_exception::quicky_logic_exception("RGB components should be in range [0,5] : " + l_stream.str(), __LINE__, __FILE__);
        }
    }

    /**
     * 8 bits gray
     */
    class gray_8b: public esc_8bits
    {
      public:
        inline explicit gray_8b(unsigned int p_gray);
    };

    //-------------------------------------------------------------------------
    gray_8b::gray_8b(unsigned int p_gray):
            esc_8bits(232 + p_gray)
    {
        if(p_gray > 23)
        {
            throw quicky_exception::quicky_logic_exception("Gray index should be in range [0,23] : " + std::to_string(p_gray), __LINE__, __FILE__);
        }
    }

    /**
     * 24 bits color
     */
    class color_24b
    {
      public:
        inline color_24b(unsigned int p_r,
                         unsigned int p_g,
                         unsigned int p_b
                        );
        inline const std::string & get_code()const;
      private:
        std::string m_code;
    };

    //-------------------------------------------------------------------------
    color_24b::color_24b(unsigned int p_r,
                         unsigned int p_g,
                         unsigned int p_b
                        ):
            m_code("2;" + std::to_string(p_r) + ";" + std::to_string(p_g) + ":" + std::to_string(p_b))
    {
        if(p_r > 255 ||  p_g > 255 || p_b > 255)
        {
            std::stringstream l_stream;
            l_stream << "(" << p_r << "," << p_g << "," << p_b << ")";
            throw quicky_exception::quicky_logic_exception("RGB components should be in range [0,255] : " + l_stream.str(), __LINE__, __FILE__);
        }
    }

    //-------------------------------------------------------------------------
    const std::string &
    color_24b::get_code() const
    {
        return m_code;
    }

    //-------------------------------------------------------------------------
    std::ostream &
    operator<<(std::ostream & p_stream,
               const ansi_escape_code & p_color
              )
    {
        p_stream << "\x1b[" << p_color.m_code << "m";
        return p_stream;
    }

    //-------------------------------------------------------------------------
    ansi_escape_code::ansi_escape_code(const std::string & p_code):
            m_code(p_code)
    {
    }

    /**
     * I/O manipulator to set characters color
     */
    class set_fcolor: public ansi_escape_code
    {
      public:
        /**
         * Constructor for 3 bits colors
         * @param p_code code of 3 bits color
         */
        inline explicit set_fcolor(const ansi_color & p_code);

        /**
         * Constructor for 8 bits colors
         * @param p_color code of 8 bits color
         */
        inline explicit set_fcolor(const color_8b & p_color);

        /**
         * Constructor for 8 bits gray
         * @param p_gray code of 8 bits color
         */
        inline explicit set_fcolor(const gray_8b & p_gray);

        /**
         * Constructor for 24 bits colors
         * @param p_color code of 24 bits color
         */
        inline explicit set_fcolor(const color_24b & p_color);

    };

    //-------------------------------------------------------------------------
    set_fcolor::set_fcolor(const ansi_color & p_code):
            ansi_escape_code(std::to_string(30 + (unsigned int)p_code))
    {

    }

    //-------------------------------------------------------------------------
    set_fcolor::set_fcolor(const color_8b & p_color):
            ansi_escape_code("38;" + p_color.get_code())
    {

    }

    //-------------------------------------------------------------------------
    set_fcolor::set_fcolor(const gray_8b & p_gray):
            ansi_escape_code("38;" + p_gray.get_code())
    {

    }

    set_fcolor::set_fcolor(const color_24b & p_color):
            ansi_escape_code("38;" + p_color.get_code())
    {

    }

    /**
     * I/O manipulator to set characters color
     */
    class set_bright_fcolor: public ansi_escape_code
    {
      public:
        /**
         * Constructor for 3 bits colors
         * @param p_code code of 8 bit color
         */
        inline explicit set_bright_fcolor(const ansi_color & p_code);

    };

    //-------------------------------------------------------------------------
    set_bright_fcolor::set_bright_fcolor(const ansi_color & p_code):
            ansi_escape_code(std::to_string(90 + (unsigned int)p_code))
    {

    }

    /**
     * I/O manipulator to set background color
     */
    class set_bcolor: public ansi_escape_code
    {
      public:
        /**
         * Constructor for 3 bits colors
         * @param p_code code of 8 bit color
         */
        inline explicit set_bcolor(const ansi_color & p_code);

        /**
         * Constructor for 8 bits colors
         * @param p_color code of 8 bits color
         */
        inline explicit set_bcolor(const color_8b & p_color);

        /**
         * Constructor for 8 bits gray
         * @param p_gray code of 8 bits color
         */
        inline explicit set_bcolor(const gray_8b & p_gray);

        /**
         * Constructor for 24 bits colors
         * @param p_color code of 24 bits color
         */
        inline explicit set_bcolor(const color_24b & p_color);

    };

    //-------------------------------------------------------------------------
    set_bcolor::set_bcolor(const ansi_color & p_code):
            ansi_escape_code(std::to_string(40 + (unsigned int)p_code))
    {

    }

    //-------------------------------------------------------------------------
    set_bcolor::set_bcolor(const color_8b & p_color):
            ansi_escape_code("48;" + p_color.get_code())
    {

    }

    //-------------------------------------------------------------------------
    set_bcolor::set_bcolor(const gray_8b & p_gray):
            ansi_escape_code("48;" + p_gray.get_code())
    {

    }

    //-------------------------------------------------------------------------
    set_bcolor::set_bcolor(const color_24b & p_color):
            ansi_escape_code("48;" + p_color.get_code())
    {

    }

    /**
     * I/O manipulator to set background color
     */
    class set_bright_bcolor: public ansi_escape_code
    {
      public:
        /**
         * Constructor for 3 bits colors
         * @param p_code code of 8 bit color
         */
        inline explicit set_bright_bcolor(const ansi_color & p_code);

    };

    //-------------------------------------------------------------------------
    set_bright_bcolor::set_bright_bcolor(const ansi_color & p_code):
            ansi_escape_code(std::to_string(100 + (unsigned int)p_code))
    {
    }

    /**
     * I/O manipulator to set bold mode
     */
    class set_bold: public ansi_escape_code
    {
      public:
        inline set_bold();
    };

    //-------------------------------------------------------------------------
    set_bold::set_bold():
            ansi_escape_code("1")
    {

    }

    /**
     * I/O manipulator to set underline mode
     */
    class set_underline: public ansi_escape_code
    {
      public:
        inline set_underline();
    };

    //-------------------------------------------------------------------------
    set_underline::set_underline():
            ansi_escape_code("4")
    {

    }

    /**
     * I/O manipulator to set reverse mode
     */
    class set_reverse: public ansi_escape_code
    {
      public:
        inline set_reverse();
    };

    //-------------------------------------------------------------------------
    set_reverse::set_reverse():
            ansi_escape_code("7")
    {

    }

    /**
     * I/O manipulator to set normal mode
     */
    class set_normal: public ansi_escape_code
    {
      public:
        inline set_normal();
    };

    //-------------------------------------------------------------------------
    set_normal::set_normal():
            ansi_escape_code("0")
    {

    }

#ifdef QUICKY_UTILS_SELF_TEST
    void test_ansi_colors();
#endif // QUICKY_UTILS_SELF_TEST

}
#endif //QUICKY_UTILS_ANSI_COLORS_H
//EOF
