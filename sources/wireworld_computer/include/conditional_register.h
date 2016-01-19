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
#ifndef __CONDITIONAL_REGISTER_H__
#define __CONDITIONAL_REGISTER_H__

#include "simple_register.h"
#include "return_zero_register.h"
#include <cassert>
#include <iostream>

namespace wireworld_computer
{
  class conditional_register: public register_if
  {
  public:
    inline conditional_register(const return_zero_register * const p_register1,
				const return_zero_register * const p_register2);
    inline uint16_t read(void)const;
    inline void write(uint16_t p_value);
  private:
    const return_zero_register * const m_reg1;
    const return_zero_register * const m_reg2;
    simple_register m_register;
  };

  //----------------------------------------------------------------------------
  conditional_register::conditional_register(const return_zero_register * const p_register1,
					     const return_zero_register * const p_register2):
    m_reg1(p_register1),
    m_reg2(p_register2)
      {
	assert(p_register1);
	assert(p_register2);
      }

  //----------------------------------------------------------------------------
  uint16_t conditional_register::read(void)const
  {
    return m_register.read() ? m_reg1->m_value : m_reg2->m_value  ;
  }

  //----------------------------------------------------------------------------
  void conditional_register::write(uint16_t p_value)
  {
    return m_register.write(p_value);
  }
}
#endif //__CONDITIONAL_REGISTER_H__
//EOF
