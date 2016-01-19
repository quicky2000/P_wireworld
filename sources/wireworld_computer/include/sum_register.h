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
#ifndef __SUM_REGISTER_H__
#define __SUM_REGISTER_H__

#include "simple_register.h"
#include <cassert>

namespace wireworld_computer
{
  class sum_register: public register_if
  {
    friend class  sum_operand_register;
  public:
    inline sum_register(const register_if * const p_operand_register);
    inline uint16_t read(void)const;
    inline void write(uint16_t p_value);
  private:
    inline void compute(void);

    const register_if * const m_operand_register;
    simple_register m_register;
    bool m_carry;
    uint16_t m_value;
  };

  //----------------------------------------------------------------------------
  sum_register::sum_register(const register_if * const p_operand_register):
    m_operand_register(p_operand_register),
    m_carry(false)
    {
      assert(p_operand_register);
    }

  //----------------------------------------------------------------------------
  void  sum_register::compute(void)
  {
    uint16_t l_op1 = m_operand_register->read();
    uint16_t l_op2 = m_register.read();
    uint16_t l_sum16 = l_op1 + l_op2;
    uint32_t l_op1_32 = m_operand_register->read();
    uint32_t l_op2_32 = m_register.read();
    uint32_t l_sum32 = l_op1_32 + l_op2_32 + m_carry;
    m_carry = (l_sum32 & 0x10000);
    m_value = l_sum16 + (m_carry ? 1 : 0);
  }

  //----------------------------------------------------------------------------
  uint16_t sum_register::read(void)const
  {
    return m_value;
  }

  //----------------------------------------------------------------------------
  void sum_register::write(uint16_t p_value)
  {
    m_register.write(p_value);
    compute();
  }
}
#endif //__SUM_REGISTER_H__
//EOF
