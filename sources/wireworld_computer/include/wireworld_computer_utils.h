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
#ifndef __WIREWORLD_COMPUTER_UTILS_H__
#define __WIREWORLD_COMPUTER_UTILS_H__

#include <map>
namespace wireworld_computer
{
  class wireworld_computer_utils
  {
  public:
     typedef std::map<unsigned int,register_information> t_register_informations;
  };
}
#endif //__WIREWORLD_COMPUTER_UTILS_H__
//EOF
