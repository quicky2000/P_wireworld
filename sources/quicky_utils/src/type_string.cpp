/*    This file is part of quicky_utils
      Copyright (C) 2018  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#include "type_string.h"

namespace quicky_utils
{
    simple_type_string(uint8_t);
    simple_type_string(uint16_t);
    simple_type_string(uint32_t);
    simple_type_string(uint64_t);

    simple_type_string(int8_t);
    simple_type_string(int16_t);
    simple_type_string(int32_t);
    simple_type_string(int64_t);

    simple_type_string(char);
    simple_type_string(float);
    simple_type_string(double);
    simple_type_string(std::string);
}
// EOF
