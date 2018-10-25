/*    This file is part of quicky_utils
      Copyright (C) 2017  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifndef QUICKY_UTILS_SAFE_TYPES_H
#define QUICKY_UTILS_SAFE_TYPES_H

#include "safe_uint.h"
#include "safe_int.h"
#include <inttypes.h>

namespace quicky_utils
{
    typedef safe_uint<uint8_t> safe_uint8_t;
    typedef safe_uint<uint16_t> safe_uint16_t;
    typedef safe_uint<uint32_t> safe_uint32_t;
    typedef safe_uint<uint64_t> safe_uint64_t;

    typedef safe_int<int8_t> safe_int8_t;
    typedef safe_int<int16_t> safe_int16_t;
    typedef safe_int<int32_t> safe_int32_t;
    typedef safe_int<int64_t> safe_int64_t;

#ifdef QUICKY_UTILS_SELF_TEST
    bool
    test_safe_types();
#endif // QUICKY_UTILS_SELF_TEST

}
#endif //QUICKY_UTILS_SAFE_TYPES_H
