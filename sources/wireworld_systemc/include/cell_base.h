/*
    This file is part of wireworld_systemc
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

#ifndef CELL_BASE_H
#define CELL_BASE_H

#include "systemc.h"

namespace wireworld_systemc
{

  class cell_base
  {
  public:
    virtual void bind_clk(sc_signal<bool> & p_clk)=0;
    virtual void bind_neighbour(sc_signal<bool> & p_neighbour, const unsigned int & p_index)=0;
    virtual void bind_electron(sc_signal<bool> & p_electron)=0;
    virtual ~cell_base(void){}
  private:
  };
}
#endif // CELL_BASE_H
//EOF
