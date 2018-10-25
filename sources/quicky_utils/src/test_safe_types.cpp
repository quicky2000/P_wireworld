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
#include "safe_types.h"
#include "fract.h"
#include "quicky_test.h"
#include <cassert>

namespace quicky_utils
{

    template <typename SAFE_TYPE, typename REFERENCE_TYPE>
    bool test_safe_type();

    template <typename SOURCE_TYPE, typename TARGET_TYPE>
    bool test_type_conversion(const typename SOURCE_TYPE::base_type & p_value,
                              bool p_exception_expected
                             );

    template <typename TYPE>
    bool check_safe_equal(const TYPE & p_op1,
                          const TYPE & p_op2,
                          bool p_expected
                         );

    template <typename TYPE>
    bool check_safe_not_equal(const TYPE & p_op1,
                              const TYPE & p_op2,
                              bool p_expected
                             );

    template <typename SAFE_TYPE, typename REFERENCE_TYPE>
    bool test_safe_operator(const REFERENCE_TYPE l_op1,
                            const REFERENCE_TYPE l_op2,
                            char p_operator
                           );

#if __cplusplus==201402L
    auto g_lambda = [] (auto x, auto y, char op)
        {
            switch(op)
            {
                case '+':return x + y;
                case '-':return x - y;
                case '/':return x / y;
                case '*':return x * y;
                case '%':return x % y;
                default: throw quicky_exception::quicky_logic_exception("Unsupported operator '" + std::string(1,op) +"'",__LINE__,__FILE__);
            }
        };
#else
#define g_lambda(x,y,op) ((op) == '+' ? (x) + (y) :((op) == '-' ? (x) - (y) :((op) == '*' ? (x) * (y) : ((op) == '/' ? (x) / (y) : ((op) == '%' ? (x) % (y) : (decltype(x))0)))))
#endif // __cplusplus


    //------------------------------------------------------------------------------
    bool
    test_safe_types()
    {
        bool l_ok = true;
        l_ok &= test_safe_type<typename quicky_utils::safe_uint<uint8_t>, uint32_t>();
        l_ok &= test_safe_type<typename quicky_utils::safe_int<int8_t>, int32_t>();

        quicky_utils::safe_int<int16_t> l_safe_int(-128);
        std::cout << l_safe_int << std::endl;
        l_safe_int = abs(l_safe_int);
        l_safe_int = std::abs(l_safe_int);
        std::cout << l_safe_int << std::endl;
        quicky_utils::safe_uint<uint16_t> l_safe_uint(128);
        std::cout << l_safe_uint << std::endl;
        std::cout << abs(l_safe_int) << std::endl;
        assert(l_safe_uint);
        assert(l_safe_int);
        quicky_utils::fract<quicky_utils::safe_uint<uint16_t>> l_fract((quicky_utils::fract<quicky_utils::safe_uint<uint16_t>>::t_coef_den)1, (quicky_utils::fract<quicky_utils::safe_uint<uint16_t>>::t_coef_den)12);
        quicky_utils::fract<quicky_utils::safe_uint<uint16_t>> l_fract2((quicky_utils::fract<quicky_utils::safe_uint<uint16_t>>::t_coef_den)1,(quicky_utils::fract<quicky_utils::safe_uint<uint16_t>>::t_coef_den)4);
        std::cout << (l_fract + l_fract2) << std::endl;

        // Try to change a safe_int in a safe_uint
        l_ok &= test_type_conversion<quicky_utils::safe_int<int8_t>, quicky_utils::safe_uint<uint8_t> >(-128,
                                                                                                        true
                                                                                                       );
        l_ok &= test_type_conversion<quicky_utils::safe_int<int8_t>, quicky_utils::safe_uint<uint8_t> >(-1,
                                                                                                        true
                                                                                                       );
        l_ok &= test_type_conversion<quicky_utils::safe_int<int8_t>, quicky_utils::safe_uint<uint8_t> >(0,
                                                                                                        false
                                                                                                       );

        // Try to change a safe_uint in a safe_int
        l_ok &= test_type_conversion<quicky_utils::safe_uint<uint8_t>, quicky_utils::safe_int<int8_t> >(0,
                                                                                                        false
                                                                                                       );
        l_ok &= test_type_conversion<quicky_utils::safe_uint<uint8_t>, quicky_utils::safe_int<int8_t> >(127,
                                                                                                        false
                                                                                                       );
        l_ok &= test_type_conversion<quicky_utils::safe_uint<uint8_t>, quicky_utils::safe_int<int8_t> >(128,
                                                                                                        true
                                                                                                       );
        // Test equality operator
        l_ok &= check_safe_equal<quicky_utils::safe_uint<uint8_t>>(1,
                                                                   1,
                                                                   true
                                                                  );
        l_ok &= check_safe_equal<quicky_utils::safe_uint<uint8_t>>(1,
                                                                   2,
                                                                   false
                                                                  );
        l_ok &= check_safe_not_equal<quicky_utils::safe_uint<uint8_t>>(1,
                                                                       1,
                                                                       false
                                                                      );
        l_ok &= check_safe_not_equal<quicky_utils::safe_uint<uint8_t>>(1,
                                                                       2,
                                                                       true
                                                                      );

        return l_ok;
    }

    //------------------------------------------------------------------------------
    template <typename SAFE_TYPE, typename REFERENCE_TYPE>
    bool test_safe_type()
    {
        bool l_ok = true;
        static_assert(std::is_signed<SAFE_TYPE>::value == std::is_signed<REFERENCE_TYPE>::value,"Check sign coherency between safe_type and reference type");
        std::array<char,5> l_operators = {'+', '-', '*', '/','%'};
        for(auto l_operator: l_operators)
        {
            std::cout << "Operator '" << l_operator << "'" << std::endl;
            typename SAFE_TYPE::base_type l_min = std::numeric_limits<typename SAFE_TYPE::base_type>::min();
            typename SAFE_TYPE::base_type l_max = std::numeric_limits<typename SAFE_TYPE::base_type>::max();
            for (REFERENCE_TYPE l_x = l_min ;
                 l_x < l_max;
                 ++l_x
                    )
            {
                for (REFERENCE_TYPE l_y = l_min;
                     l_y < l_max;
                     ++l_y
                        )
                {
                    if(('/' == l_operator  || '%' == l_operator) && !l_y) break;
                    l_ok &= test_safe_operator<SAFE_TYPE, REFERENCE_TYPE >(l_x,
                                                                           l_y,
                                                                           l_operator
                                                                          );
                }
            }
        }
        return l_ok;
    }

    //------------------------------------------------------------------------------
    template <typename SAFE_TYPE, typename REFERENCE_TYPE>
    bool test_safe_operator(const REFERENCE_TYPE l_op1,
                            const REFERENCE_TYPE l_op2,
                            char p_operator
                           )
    {
        bool l_ok = true;
        auto l_base_x = (typename SAFE_TYPE::base_type) l_op1;
        auto l_base_y = (typename SAFE_TYPE::base_type) l_op2;
        SAFE_TYPE l_safe_x(l_base_x);
        SAFE_TYPE l_safe_y(l_base_y);

        REFERENCE_TYPE l_ref_result = g_lambda(l_base_x,
                                               l_base_y,
                                               p_operator
                                              );
        typename SAFE_TYPE::base_type l_result = g_lambda(l_base_x,
                                                          l_base_y,
                                                          p_operator
                                                         );
        SAFE_TYPE l_safe_result;
        bool l_compute_ok = true;
        try
        {
            l_safe_result = g_lambda(l_safe_x,
                                     l_safe_y,
                                     p_operator
                                    );
        }
        catch (quicky_utils::safe_type_exception & e)
        {
            l_compute_ok = false;
        }
        bool l_coherent_result = l_ref_result == (REFERENCE_TYPE) l_result;
        if (l_coherent_result)
        {
            l_ok &= quicky_test::check_expected(l_safe_result.get_value() == l_result,
                                                true
                                               );
        }
        l_ok &= quicky_test::check_expected(l_coherent_result == l_compute_ok,
                                            true
                                           );
        return l_ok;
    }

    //------------------------------------------------------------------------------
    template <typename TYPE>
    bool check_safe_equal(const TYPE & p_op1,
                          const TYPE & p_op2,
                          bool p_expected
                         )
    {
        return quicky_test::check_expected(p_op1 == p_op2, p_expected);
    }

    //------------------------------------------------------------------------------
    template <typename TYPE>
    bool check_safe_not_equal(const TYPE & p_op1,
                              const TYPE & p_op2,
                              bool p_expected
                             )
    {
        return quicky_test::check_expected(p_op1 != p_op2, p_expected);
    }

    //------------------------------------------------------------------------------
    template <typename SOURCE_TYPE, typename TARGET_TYPE>
    bool test_type_conversion(const typename SOURCE_TYPE::base_type & p_value,
                              bool p_exception_expected
                             )
    {
        std::string l_message("test type conversion ");
        l_message += type_string<SOURCE_TYPE>::name() + " -> " + type_string<TARGET_TYPE>::name();
        SOURCE_TYPE l_source(p_value);
        return quicky_test::check_exception<quicky_exception::quicky_logic_exception>([&]{TARGET_TYPE l_target(l_source);},p_exception_expected, l_message);
    }


}

#endif // QUICKY_UTILS_SELF_TEST
// EOF
