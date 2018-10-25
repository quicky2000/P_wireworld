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

#ifdef QUICKY_UTILS_SELF_TEST

#include "type_string.h"
#include "quicky_test.h"
#include "safe_types.h"

namespace quicky_utils
{
    /**
    * Method checking type string representation against expected
    * @tparam T
    * @return true if test is successfull
    */
    template <typename T>
    bool check_a_type_string(const std::string & p_reference)
    {
        return quicky_test::check_expected(quicky_utils::type_string<T>::name(), p_reference, "Check name of " + quicky_utils::type_string<T>::name());
    }
#define check(type) check_a_type_string<type>(#type)
#define check_name(type,type_name) check_a_type_string<type>(type_name)
#define check_prefix(prefix,type) check_a_type_string<prefix::type>(#type)

    bool test_type_string()
    {
        bool l_ok = true;
        l_ok &= check(uint8_t);
        l_ok &= check(uint16_t);
        l_ok &= check(uint32_t);
        l_ok &= check(uint64_t);

        l_ok &= check(int8_t);
        l_ok &= check(int16_t);
        l_ok &= check(int32_t);
        l_ok &= check(int64_t);

        l_ok &= check(char);
        l_ok &= check(double);
        l_ok &= check(float);
        l_ok &= check(std::string);

        l_ok &= check_name(quicky_utils::safe_uint32_t,"safe_uint<uint32_t>");
        l_ok &= check_name(quicky_utils::safe_uint64_t,"safe_uint<uint64_t>");

        l_ok &= check_prefix(quicky_utils,safe_uint<uint8_t>);
        l_ok &= check_name(quicky_utils::safe_uint<uint8_t>,"safe_uint<uint8_t>");
        l_ok &= check_prefix(quicky_utils,safe_uint<uint16_t>);
        l_ok &= check_name(quicky_utils::safe_uint<uint16_t>,"safe_uint<uint16_t>");

        l_ok &= check_name(quicky_utils::safe_int8_t,"safe_int<int8_t>");
        l_ok &= check_name(quicky_utils::safe_int16_t,"safe_int<int16_t>");
        l_ok &= check_name(quicky_utils::safe_int32_t,"safe_int<int32_t>");
        l_ok &= check_name(quicky_utils::safe_int64_t,"safe_int<int64_t>");

        return l_ok;

    }
}

#endif // QUICKY_UTILS_SELF_TEST
// EOF
