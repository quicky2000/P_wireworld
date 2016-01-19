/*
  This file is part of wireworld_computer
  Copyright (C) 2015  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef __SUM_OPERAND_REGISTER_H__
#define __SUM_OPERAND_REGISTER_H__

#include "simple_register.h"
#include <cassert>

namespace wireworld_computer
{
  class sum_register;
  class sum_operand_register: public simple_register
  {
  public:
    inline sum_operand_register(void);
    void  write(uint16_t p_value);
    inline void set_sum_register(sum_register & p_sum_register);
  private:
    sum_register * m_sum_register;
  };

  //----------------------------------------------------------------------------
  sum_operand_register::sum_operand_register(void):
    m_sum_register(nullptr)
  {
  }

  //----------------------------------------------------------------------------
  void sum_operand_register::set_sum_register(sum_register & p_sum_register)
  {
    m_sum_register = & p_sum_register;
  }

}
#endif //__SUM_OPERAND_REGISTER_H__
//EOF
