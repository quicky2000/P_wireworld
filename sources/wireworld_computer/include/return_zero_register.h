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
#ifndef __RETURN_ZERO_REGISTER_H__
#define __RETURN_ZERO_REGISTER_H__

#include "register_if.h"

#include <iostream>

namespace wireworld_computer
{
  class return_zero_register: public register_if
  {
    friend class conditional_register;
  public:
    inline return_zero_register(void);
    inline uint16_t read(void)const;
    inline void write(uint16_t p_value);
  private:
    uint16_t m_value;
  };

  //----------------------------------------------------------------------------
  return_zero_register::return_zero_register(void):
    m_value(0)
    {
    }

  //----------------------------------------------------------------------------
  uint16_t return_zero_register::read(void)const
  {
    return 0;
  }

  //----------------------------------------------------------------------------
  void return_zero_register::write(uint16_t p_value)
  {
    m_value = p_value;
  }
}
#endif //__RETURN_ZERO_REGISTER_H__
//EOF
