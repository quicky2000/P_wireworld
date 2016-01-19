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
#ifndef __BITWISE_AND_NOT_REGISTER_H__
#define __BITWISE_AND_NOT_REGISTER_H__

#include "register_if.h"
#include <cassert>

namespace wireworld_computer
{
  class bitwise_and_not_register: public register_if
  {
  public:
    inline bitwise_and_not_register(simple_register * const p_register1, const simple_register  * const p_register2);
    inline uint16_t read(void)const;
    inline void write(uint16_t p_value);
  private:
    simple_register * const m_reg1;
    const simple_register * const m_reg2;
  };

  //----------------------------------------------------------------------------
  bitwise_and_not_register::bitwise_and_not_register(simple_register * const p_register1, const simple_register  * const p_register2):
    m_reg1(p_register1),
    m_reg2(p_register2)
      {
	assert(p_register1);
	assert(p_register2);
      }

  //----------------------------------------------------------------------------
  uint16_t bitwise_and_not_register::read(void)const
  {
    return ~(m_reg1->read()) & (m_reg2->read());
  }

  //----------------------------------------------------------------------------
  void bitwise_and_not_register::write(uint16_t p_value)
  {
    m_reg1->write(p_value);
  }

}
#endif //__BITWISE_AND_NOT_REGISTER_H__
//EOF
