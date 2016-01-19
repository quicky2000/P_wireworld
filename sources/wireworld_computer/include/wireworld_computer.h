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
#ifndef __WIREWORLD_COMPUTER_H__
#define __WIREWORLD_COMPUTER_H__

#include "register_if.h"
#include "register_information.h"
#include "wireworld_computer_utils.h"

namespace wireworld_computer
{
  class wireworld_computer
  {
  public:
    wireworld_computer(const wireworld_computer_utils::t_register_informations & p_informations,
		       const std::string & p_output_file,
		       bool p_detailled_display,
		       const uint32_t & p_instruction_delay);
    void run(void);
  private:
    uint8_t decodeDestination(uint16_t p_instr);
    uint8_t decodeSource(uint16_t p_instr);
    uint16_t getInstruction(void);
    void execInstruction(uint16_t p_instr);
    register_if* m_registers[64];
    uint32_t m_instruction_delay;
  };

}
#endif //__WIREWORLD_COMPUTER_H__
//EOF
