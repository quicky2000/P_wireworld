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
#ifndef __REGISTER_IF_H__
#define __REGISTER_IF_H__

#include <cstdint>

namespace wireworld_computer
{
  class register_if
  {
  public:
    virtual uint16_t read(void)const=0;
    virtual void write(uint16_t p_value)=0;
    virtual ~register_if(void){};
  };
}
#endif //__REGISTER_IF_H__
//EOF
