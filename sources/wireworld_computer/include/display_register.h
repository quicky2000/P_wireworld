/*
  This file is part of wireworld_computer
  Copyright (C) 2010  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef __DISPLAY_REGISTER_H__
#define __DISPLAY_REGISTER_H__

#include "register_if.h"

#include <iostream>
#include <iomanip>

namespace wireworld_computer
{
  class display_register: public register_if
  {
  public:
    inline display_register(bool p_details);
    inline uint16_t read(void)const;
    inline void write(uint16_t p_value);
  private:
    inline void binary2bcd(const uint64_t & p_number);
    bool m_details;
    uint16_t m_value;
  };

  //----------------------------------------------------------------------------
  display_register::display_register(bool p_details):
    m_details(p_details),
    m_value(0)
    {
    }

  //----------------------------------------------------------------------------
  uint16_t display_register::read(void)const
  {
    return 0;
  }

  //----------------------------------------------------------------------------
  void display_register::write(uint16_t p_value)
  {
    m_value = p_value;
    if(m_details)
      {
        binary2bcd(m_value);
      }
    std::cout << "-----------------------------------" << std::endl ;
    std::cout << "** DISPLAY => " << m_value << std::endl ;
    std::cout << "-----------------------------------" << std::endl ;
  }

  //----------------------------------------------------------------------------
  void display_register::binary2bcd(const uint64_t & p_number)
  {
    uint32_t l_bottom_loop[] = {
      0xFFFF63C0,
      0x4E20,
      0x2710,
      0x7D0,
      0xFA0,
      0x7D0,
      0x3E8,
      0xC8,
      0x190,
      0xC8,
      0x64,
      0x14,
      0x28,
      0x14,
      0xA,
      0x2,
      0x4,
      0x2,
      0x1,
      0x1
    };

    uint32_t l_top_loop[] = {
      0xFFFFFF80,
      0x0,
      0x0,
      0x1890,
      0x0,
      0x0,
      0x0,
      0x3E8,
      0x0,
      0x0,
      0x0,
      0x44,
      0x0,
      0x0,
      0x0,
      0xA,
      0x0,
      0x0,
      0x0,
      0x1,
    };

    uint64_t l_adder_content = p_number;
    uint64_t l_adder_full = 0xFFFFFFFF;
    uint32_t l_display[5] = {0,0,0,0,0};
    uint32_t l_display_index = 0;
    uint32_t l_power_index = 2;
    uint32_t l_carry = 0;

    std::cout << "-----------------------------------" << std::endl ;
    for(uint32_t l_index = 0; l_index < 20 ; ++l_index)
      {
        if(((l_index + 1) % 4) == 0)
          {
            std::cout << "-------------------------------------------------------";
            std::cout << "-------------------------------------------------------";
            std::cout << "-------------------------------------------------------";
            std::cout << "--------------------------------------------------" << std::endl ;
          }
        std::cout << "Step[" << std::setfill(' ') << std::setw(2) << l_index << "]: ";
        std::cout << "carry : 0x" << std::setw(8) << std::setfill('0') << std::hex << l_carry << std::dec << " & ~(" ;
        std::cout << "Top_loop[" << std::setfill(' ') << std::setw(2) << l_index << "] : 0x" << std::setw(8) << std::setfill('0') << std::hex << l_top_loop[l_index] << std::dec << ") => " ;
        l_carry = l_carry & ( ~ (l_top_loop[l_index]));
        std::cout << "Adjusted carry 0x" << std::setw(8) << std::setfill('0') << std::hex << l_carry << std::dec << " ^ " ;
        std::cout << "Bot_loop[" << std::setfill(' ') << std::setw(2) << l_index << "] : 0x" << std::setw(8) << std::setfill('0') << std::hex << l_bottom_loop[l_index] << std::dec << " => " ;
        uint32_t l_to_add = l_carry ^ l_bottom_loop[l_index];
        std::cout << "To add 0x" << std::setw(8) << std::setfill('0') << std::hex << l_to_add <<std::dec << " + " ;
        std::cout << "Adder content : " << std::setw(8) << std::setfill('0') << std::hex << l_adder_content << std::dec << " | " ;
        l_adder_content +=  l_to_add;
        std::cout << "==> Adder content : " << std::setw(8) << std::setfill('0') << std::hex << l_adder_content << std::dec ;
        if(l_adder_content > l_adder_full)
          {
            std::cout << "\tOverflow !" ;
            l_adder_content = (l_adder_content & 0xFFFFFFFF) + 1;
            l_carry = 0xFFFFFFFF;

            // Part implemented by Pulse controler
            l_display[l_display_index]+= 1 << l_power_index;
          }
        else
          {
            l_carry = 0;
          }
        // Part implemented by Pulse controler
        l_power_index = (l_power_index > 0 ? l_power_index - 1 : 3);
        // Part implemented by Pulse controler and Digit display controler
        if(l_power_index == 3)
          {
            ++l_display_index;
          }
        std::cout << std::endl;
      }

    // Display Results
    for(uint32_t l_index = 0 ; l_index < 5; ++l_index)
      {
        std::cout << "|" << l_display[l_index] ;
      }
    std::cout << "|" << std::endl ;
  }


}
#endif //__DISPLAY_REGISTER_H__
//EOF
