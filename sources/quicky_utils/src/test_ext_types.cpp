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
#include "ext_uint.h"
#include "ext_int.h"
#include "quicky_test.h"
#include <cassert>
#include <cmath>

namespace quicky_utils
{
    /**
    * Methods converting infinite type to integer type if possible
    * in contrary case an exception is raised
    * @tparam EXT_INT_TYPE infinite type like infinite_uint
    * @tparam INT_TYPE integer type like uint32_t
    * @param p_ext_int_type extensible integer type variable to convert to integer type
    * @return integer type representing extensible integer type if possible
    */
    template <typename INT_TYPE,
              typename EXT_INT_TYPE
             >
    INT_TYPE convert(const EXT_INT_TYPE & p_ext_int_type)
    {
        if(p_ext_int_type.get_nb_bytes() <= sizeof(INT_TYPE))
        {
            INT_TYPE l_result = 0;
            for(unsigned int l_index = 0;
                l_index < p_ext_int_type.get_nb_words();
                ++l_index
                    )
            {
                l_result |= ((INT_TYPE) p_ext_int_type.get_word(l_index)) << (l_index * 8 * sizeof(typename EXT_INT_TYPE::base_type));
            }
            return l_result;
        }
        throw quicky_exception::quicky_logic_exception("Infinite type size is greater than integer type size", __LINE__, __FILE__);
    }

    /**
    * Check if conversion from extensible integer type to integer type provide the expected result
    * @tparam INT_TYPE integer type
    * @tparam EXT_INT_TYPE extensible integer type
    * @param p_ext_type extensible integer variable
    * @param p_expected expected integer value
    */
    template <typename INT_TYPE,
              typename EXT_INT_TYPE
             >
    bool check_convert(const EXT_INT_TYPE & p_ext_type,
                       const INT_TYPE & p_expected
                      )
    {
        auto l_result = convert<INT_TYPE,EXT_INT_TYPE>(p_ext_type);
        std::stringstream l_stream;
        l_stream << p_ext_type;
        return quicky_test::check_expected<INT_TYPE>(l_result, p_expected, "Check conversion of " + l_stream.str() + " to " + quicky_utils::type_string<INT_TYPE>::name());
    }

    /**
     * Display internal representation of floating types
     * @tparam T Floating type
     * @tparam INT_T size equivalent integer type
     * @param p_floating floating number to display representation
     */
    template <typename T, typename INT_T>
    void display_floating(const T & p_floating)
    {
        static_assert(sizeof(T) == sizeof(INT_T), "INT_T is unsifficant to store floating type representation");
        constexpr const size_t l_mantissa_size = std::numeric_limits<T>::digits - 1;
        constexpr const INT_T l_mantissa_mask = (((INT_T)1) << l_mantissa_size) - 1;
        constexpr const INT_T l_exponent_mask = (((INT_T)1) << (8 * sizeof(T) - l_mantissa_size - 1)) - 1;
        INT_T l_int = *((INT_T*)&p_floating);
        INT_T l_mantissa = l_int & l_mantissa_mask;
        INT_T l_exponent = (l_int >> l_mantissa_size) & l_exponent_mask;
        INT_T l_sign = l_int >> (8 *sizeof(INT_T) - 1);
        std::cout << "Sign: " << l_sign << " Exp: 0x" << std::hex << l_exponent << " Mantissa: 0x" << l_mantissa << std::dec << std::endl;
    }

    /**
     * Display internal representation of floating types
     * There are specialisations for float and double
     * @tparam T Float type
     * @param p_floating floating number to display representation
     */
    template <typename T>
    void display_floating(const T & p_floating)
    {
        throw quicky_exception::quicky_logic_exception("Not implemented", __LINE__, __FILE__);
    }

    /**
     * Display internal representation of float
     * @param p_floating float number to display representation
     */
    template <>
    void display_floating<float>(const float & p_floating)
    {
        display_floating<float,uint32_t>(p_floating);
    }

    /**
     * Display internal representation of double
     * @param p_floating double number to display representation
     */
    template <>
    void display_floating<double>(const double & p_floating)
    {
        display_floating<double,uint64_t>(p_floating);
    }

    /**
    * Display ldexp arguments leading to floating type
    * @tparam T Floatin type
    * @param p_floating floating type to revert
    */
    template <typename T>
    void rdisplay_floating(const T & p_floating)
    {
        int l_exp;
        T l_mantissa = frexp(p_floating, &l_exp);
        std::cout << "Inverted M: ";
        if(l_mantissa < 1)
        {
            std::cout << l_mantissa;
        }
        else
        {
            std::cout << "0x" << std::hex << l_mantissa << std::dec;
        }
        std::cout << " E: ";
        if(l_exp >= 0)
        {
            std::cout << "0x" << std::hex << l_exp << std::dec;
        }
        else
        {
            std::cout << l_exp;
        }
        std::cout << std::endl;
    }


    template <typename INT_T, typename EXT_INT_T, typename FLOATING_T>
    bool check_floating_conversion(const INT_T & p_mantissa)
    {
        EXT_INT_T l_number(p_mantissa);
        FLOATING_T l_float = p_mantissa;
        FLOATING_T l_previous_float;
        bool l_ok = true;
        while(l_float != l_previous_float)
        {
            FLOATING_T l_float_ext = (FLOATING_T) l_number;
            l_ok &= quicky_test::check_expected(l_float_ext,
                                                l_float,
                                                "To float " + std::string(l_number)
                                               );
            if(!l_ok)
            {
                std::cout << l_float << " " << l_float_ext << " " << (std::string) l_number << std::endl;
                std::cout << "Ref: ";
                display_floating(l_float);
                std::cout << "Ext: ";
                display_floating(l_float_ext);
                std::cout << std::endl;
                l_float_ext = (FLOATING_T) l_number;
            }
            l_previous_float = l_float;
            l_float *= 2;
            l_number *= (EXT_INT_T)((uint32_t)2);
        }
        return l_ok;
    }

    //------------------------------------------------------------------------------
    template <typename T1, typename T2>
    void generate_test_values(const std::vector<uint8_t> & p_bytes
                             ,std::vector<std::pair<T1, T2 >> & p_test_values
                             )
    {
        T1 l_value = 0;
        uint8_t * l_ptr = (uint8_t*)&l_value;
        for(unsigned int l_i = 0;
            l_i < pow(p_bytes.size(),sizeof(T1));
            ++l_i
                )
        {
            for (unsigned int l_j = sizeof(T1) - 1;
                 l_j <= sizeof(T1) - 1;
                 --l_j
                    )
            {
                size_t l_byte_index = (l_i / ((typename std::make_unsigned<T1>::type) pow(p_bytes.size(),
                                                                                 l_j
                                                                                ))) % p_bytes.size();
                l_ptr[l_j] = p_bytes[l_byte_index];
#ifdef DEBUG
                std::cout << l_byte_index;
#endif // DEBUG
            }
#ifdef DEBUG
            std::cout << std::endl;
                        std::cout << "0x" << std::hex << (typename std::make_unsigned<T1>::type)l_value << std::dec << "\t" << l_value << std::endl;
#endif // DEBUG
            p_test_values.push_back(std::pair<T1, T2 >(l_value
                                                      ,T2(l_value)
                                                      )
                                   );
        }
    }

    //------------------------------------------------------------------------------
    bool
    test_ext_uint()
    {
        std::string l_type_name = type_string<ext_uint<uint8_t>>::name();
        bool l_ok = true;
        quicky_utils::ext_uint<uint8_t> l_zero;
        quicky_utils::ext_uint<uint8_t> l_zero_bis;
        quicky_utils::ext_uint<uint8_t> l_zero_list_init({0});
        quicky_utils::ext_uint<uint8_t> l_zero_list_init_bis({0});
        quicky_utils::ext_uint<uint8_t> l_un({1});
        quicky_utils::ext_uint<uint8_t> l_un_bis({1});
        quicky_utils::ext_uint<uint8_t> l_256({0,1});
        quicky_utils::ext_uint<uint8_t> l_256_bis({0,1});
        quicky_utils::ext_uint<uint8_t> l_max({0xFF, 0xFF, 0xFF, 0xFF});

        quicky_test::get_ostream() << std::endl << "Test " << l_type_name << " output stream operator:" << std::endl;
        l_ok &= quicky_test::check_ostream_operator(l_zero,"0x00");
        l_ok &= quicky_test::check_ostream_operator(l_un,"0x01");
        l_ok &= quicky_test::check_ostream_operator(l_256,"0x0100");

        quicky_test::get_ostream() << std::endl << "Test " << l_type_name << " conversion to integer type" << std::endl;
        l_ok &= check_convert<uint32_t,quicky_utils::ext_uint<uint8_t>>(l_256, 256);
        l_ok &= check_convert<uint32_t,quicky_utils::ext_uint<uint8_t>>(l_zero, 0);
        l_ok &= check_convert<uint32_t,quicky_utils::ext_uint<uint8_t>>(l_un, 1);
        l_ok &= check_convert<uint32_t,quicky_utils::ext_uint<uint8_t>>(l_max, std::numeric_limits<uint32_t>::max());

        quicky_test::get_ostream() << std::endl << "Test " << l_type_name << " == operator" << std::endl;
        l_ok &= quicky_test::check_expected(l_zero == l_zero_bis, true, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero_list_init == l_zero_list_init_bis, true, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero == l_zero_list_init_bis, true, quicky_test::auto_message(__FILE__, __LINE__));

        l_ok &= quicky_test::check_expected(l_un == l_un_bis, true, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero == l_un, false, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero_list_init == l_un, false, quicky_test::auto_message(__FILE__, __LINE__));

        l_ok &= quicky_test::check_expected(l_zero < l_un, true, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero < l_zero_bis, false, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_un < l_zero, false, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_zero < l_256, true, quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_expected(l_256 < l_zero, false, quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test + operator" << std::endl;
        quicky_utils::ext_uint<uint8_t> l_result;
        l_result = l_zero + l_zero;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_zero + l_un;
        l_ok &= quicky_test::check_expected(l_result, l_un, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255}) + l_un;
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255, 255}) + l_un;
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0, 0, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255, 255}) + quicky_utils::ext_uint<uint8_t>({0,1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({255, 0, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255}) + quicky_utils::ext_uint<uint8_t>({255});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({254, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test - operator" << std::endl;
        l_result = l_zero - l_zero_bis;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_un - l_un_bis;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_256 - l_256_bis;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_256 - l_un;
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({255}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result =quicky_utils::ext_uint<uint8_t>({255, 255}) - quicky_utils::ext_uint<uint8_t>({0,1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({255, 254}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result =quicky_utils::ext_uint<uint8_t>({255, 255}) - quicky_utils::ext_uint<uint8_t>({1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({254, 255}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result =quicky_utils::ext_uint<uint8_t>({0, 0, 1}) - quicky_utils::ext_uint<uint8_t>({1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({255, 255}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result =quicky_utils::ext_uint<uint8_t>({0, 0, 2}) - quicky_utils::ext_uint<uint8_t>({1, 1, 1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({255, 254}), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test * operator" << std::endl;
        l_result = l_zero * l_zero;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_zero * l_un;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_un * l_zero;
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_un * l_un;
        l_ok &= quicky_test::check_expected(l_result, l_un, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({128}) * quicky_utils::ext_uint<uint8_t>({42});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0x0, 0x15}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255, 255}) * quicky_utils::ext_uint<uint8_t>({255});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0x1, 0xFF, 0xFE}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255, 255}) * quicky_utils::ext_uint<uint8_t>({255, 255});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0x1, 0x0, 0xFE, 0xFF}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t>({255, 255, 255, 255}) * quicky_utils::ext_uint<uint8_t>({255, 255, 255, 255});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0x1, 0x0, 0x0, 0x0, 0xFE, 0xFF, 0xFF, 0xFF}), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test >> operator" << std::endl;
        l_result = l_256 >> quicky_utils::ext_uint<uint8_t>({1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({128}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_256 >> quicky_utils::ext_uint<uint8_t>({20});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>(), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test << operator" << std::endl;
        l_result = l_un << quicky_utils::ext_uint<uint8_t>({1});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({2}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_un << quicky_utils::ext_uint<uint8_t>({8});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = l_un << quicky_utils::ext_uint<uint8_t>({16});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0, 0, 1}), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test / operator" << std::endl;
        l_result = quicky_utils::ext_uint<uint8_t >({12}) / quicky_utils::ext_uint<uint8_t>({6});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({2}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t >({13}) / quicky_utils::ext_uint<uint8_t>({6});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({2}), quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t >({0xFF,0x1}) / quicky_utils::ext_uint<uint8_t>({0x12});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({0x1C}), quicky_test::auto_message(__FILE__, __LINE__));

        quicky_test::get_ostream() << std::endl << "Test % operator" << std::endl;
        l_result = quicky_utils::ext_uint<uint8_t >({12}) % quicky_utils::ext_uint<uint8_t>({6});
        l_ok &= quicky_test::check_expected(l_result, l_zero, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t >({13}) % quicky_utils::ext_uint<uint8_t>({6});
        l_ok &= quicky_test::check_expected(l_result, l_un, quicky_test::auto_message(__FILE__, __LINE__));

        l_result = quicky_utils::ext_uint<uint8_t >({0xFF,0x1}) % quicky_utils::ext_uint<uint8_t>({0x12});
        l_ok &= quicky_test::check_expected(l_result, ext_uint<uint8_t>({7}), quicky_test::auto_message(__FILE__, __LINE__));

        std::vector<uint8_t> l_significative_bytes = {0x0, 0x1, 0xFE, 0xFF};
        typedef std::pair<uint32_t, quicky_utils::ext_uint<uint8_t> > test_value_t;
        std::vector<test_value_t> l_test_values;
        generate_test_values<uint32_t, quicky_utils::ext_uint<uint8_t >>(l_significative_bytes,l_test_values);


        std::cout << "Check " << l_type_name << " + operator" << std::endl;
        // Check + operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                uint64_t l_result = (uint64_t)l_iter1.first + (uint64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(l_iter1.second + l_iter2.second,
                                                    quicky_utils::ext_uint<uint8_t>(l_result),
                                                    (std::string)l_iter1.second + " + " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " - operator" << std::endl;
        // Check - operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter1.first < l_iter2.first)
                {
                    break;
                }
                uint64_t l_result = (uint64_t)l_iter1.first - (uint64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(l_iter1.second - l_iter2.second,
                                                    quicky_utils::ext_uint<uint8_t>(l_result),
                                                    (std::string)l_iter1.second + " - " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " * operator" << std::endl;
        // Check * operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                uint64_t l_result = (uint64_t)l_iter1.first * (uint64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(l_iter1.second * l_iter2.second,
                                                    quicky_utils::ext_uint<uint8_t>(l_result),
                                                    (std::string)l_iter1.second + " * " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " / operator" << std::endl;
        // Check / operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter2.first)
                {
                    uint64_t l_result = (uint64_t) l_iter1.first / (uint64_t) l_iter2.first;
                    l_ok &= quicky_test::check_expected(l_iter1.second / l_iter2.second,
                                                        quicky_utils::ext_uint<uint8_t>(l_result),
                                                        (std::string) l_iter1.second + " / " +
                                                        (std::string) l_iter2.second
                                                       );
                }
            }
        }

        std::cout << "Check " << l_type_name << " % operator" << std::endl;
        // Check % operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter2.first)
                {
                    uint64_t l_result = (uint64_t) l_iter1.first % (uint64_t) l_iter2.first;
                    l_ok &= quicky_test::check_expected(l_iter1.second % l_iter2.second,
                                                        quicky_utils::ext_uint<uint8_t>(l_result),
                                                        (std::string) l_iter1.second + " % " +
                                                        (std::string) l_iter2.second
                                                       );
                }
            }
        }

        std::cout << "Check " << l_type_name << " >> operator" << std::endl;
        // Check >> operator
        for(auto l_iter1: l_test_values)
        {
            for(unsigned int l_i = 0; l_i < 1 + 8 * sizeof(uint32_t); ++l_i)
            {
                uint64_t l_result = ((uint64_t) l_iter1.first) >> l_i;
                l_ok &= quicky_test::check_expected(l_iter1.second >> ext_uint<uint8_t>(l_i),
                                                    quicky_utils::ext_uint<uint8_t>(l_result),
                                                    (std::string) l_iter1.second + " >> " +
                                                    std::to_string(l_i)
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " << operator" << std::endl;
        // Check << operator
        for(auto l_iter1: l_test_values)
        {
            for(unsigned int l_i = 0; l_i < 8 * sizeof(uint32_t); ++l_i)
            {
                uint64_t l_result = ((uint64_t) l_iter1.first) << l_i;
                l_ok &= quicky_test::check_expected(l_iter1.second << ext_uint<uint8_t>(l_i),
                                                    quicky_utils::ext_uint<uint8_t>(l_result),
                                                    (std::string) l_iter1.second + " << " +
                                                    std::to_string(l_i)
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " << float()/double() operator" << std::endl;
        for(auto l_iter: l_test_values)
        {
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint8_t>, float>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint8_t>, double>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint16_t>, float>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint16_t>, double>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint32_t>, float>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint32_t>, double>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint64_t>, float>(l_iter.first);
            l_ok &= check_floating_conversion<uint32_t, ext_uint<uint64_t>, double>(l_iter.first);
        }

        return l_ok;
    }

    //------------------------------------------------------------------------------
    bool
    test_ext_int()
    {
        std::string l_type_name = type_string<ext_int<int8_t>>::name();

        bool l_ok = true;

        std::vector<uint8_t> l_significative_bytes = {0x0, 0x1, 0x7F, 0x80, 0xFE, 0xFF};
        typedef std::pair<int32_t, quicky_utils::ext_int<int8_t> > test_value_t;
        std::vector<test_value_t> l_test_values;

        generate_test_values<int32_t, quicky_utils::ext_int<int8_t >>(l_significative_bytes,l_test_values);

        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<uint32_t>::max()), quicky_utils::ext_int<int8_t>(0,{0xFF,0xFF,0xFF,0xFF}), "uint32_t max");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<uint32_t>::min()), quicky_utils::ext_int<int8_t>(0,{}), "uint32_t min");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<int32_t>::max()), quicky_utils::ext_int<int8_t>(0x7F,{0xFF,0xFF,0xFF}), "int32_t max");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<int32_t>::min()), quicky_utils::ext_int<int8_t>((int8_t)0x80,{0x0,0x0,0x0}), "int32_t min");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<uint64_t>::max()), quicky_utils::ext_int<int8_t>(0,{0xFF,0xFF,0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF}), "uint64_t max");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<uint64_t>::min()), quicky_utils::ext_int<int8_t>(0,{}), "uint64_t min");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<int64_t>::max()), quicky_utils::ext_int<int8_t>(0x7F,{0xFF,0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF}), "int64_t max");
        l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(std::numeric_limits<int64_t>::min()), quicky_utils::ext_int<int8_t>((int8_t)0x80,{0x0,0x0,0x0, 0x0, 0x0, 0x0, 0x0}), "int64_t min");

        // Check ostream operator
        std::cout << "Check " << l_type_name << " ostream operator" << std::endl;

        for(auto l_iter: l_test_values)
        {
            // Build reference string from integer
            bool l_neg = l_iter.first < 0;
            uint32_t l_abs_value = l_neg ? - l_iter.first : l_iter.first;
            std::stringstream l_stream;
            l_stream << std::hex << std::uppercase << l_abs_value << std::dec;
            std::string l_reference = l_stream.str();
            if(l_reference.size() % 2)
            {
                l_reference.insert(l_reference.begin(),'0');
            }
            l_reference.insert(0,"0x");
            if(l_neg)
            {
                l_reference.insert(0,"-");
            }
            // Compare reference string with ext_int string representation
            l_ok &= quicky_test::check_ostream_operator(l_iter.second, l_reference, quicky_test::auto_message(__FILE__, __LINE__));
        }

        std::cout << "Check " << l_type_name << " == operator" << std::endl;
        // Check == operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second == l_iter2.second,
                                                    l_iter1.first == l_iter2.first,
                                                    (std::string)l_iter1.second + " == " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " != operator" << std::endl;
        // Check != operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second != l_iter2.second,
                                                    l_iter1.first != l_iter2.first,
                                                    (std::string)l_iter1.second + " != " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " < operator" << std::endl;
        // Check < operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second < l_iter2.second,
                                                    l_iter1.first < l_iter2.first,
                                                    (std::string)l_iter1.second + " < " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " <= operator" << std::endl;
        // Check <= operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second <= l_iter2.second,
                                                    l_iter1.first <= l_iter2.first,
                                                    (std::string)l_iter1.second + " <= " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " > operator" << std::endl;
        // Check > operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second > l_iter2.second,
                                                    l_iter1.first > l_iter2.first,
                                                    (std::string)l_iter1.second + " > " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " >= operator" << std::endl;
        // Check >= operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                l_ok &= quicky_test::check_expected(l_iter1.second >= l_iter2.second,
                                                    l_iter1.first >= l_iter2.first,
                                                    (std::string)l_iter1.second + " >= " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " + operator" << std::endl;
        // Check + operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t)l_iter1.first + (int64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(quicky_utils::ext_int<int8_t>(l_result),
                                                    l_iter1.second + l_iter2.second,
                                                    (std::string)l_iter1.second + " + " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " - operator" << std::endl;
        // Check - operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t)l_iter1.first - (int64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(l_iter1.second - l_iter2.second,
                                                    quicky_utils::ext_int<int8_t>(l_result),
                                                    (std::string)l_iter1.second + " - " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " * operator" << std::endl;
        // Check * operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t)l_iter1.first * (int64_t)l_iter2.first;
                l_ok &= quicky_test::check_expected(l_iter1.second * l_iter2.second,
                                                    quicky_utils::ext_int<int8_t>(l_result),
                                                    (std::string)l_iter1.second + " * " + (std::string)l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " / operator" << std::endl;
        // Check / operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter2.first)
                {
                    int64_t l_result = (int64_t) l_iter1.first / (int64_t) l_iter2.first;
                    l_ok &= quicky_test::check_expected(l_iter1.second / l_iter2.second,
                                                        quicky_utils::ext_int<int8_t>(l_result),
                                                        (std::string) l_iter1.second + " / " +
                                                        (std::string) l_iter2.second
                                                       );
                }
            }
        }

        std::cout << "Check " << l_type_name << " % operator" << std::endl;
        // Check % operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter2.first)
                {
                    int64_t l_result = (int64_t) l_iter1.first % (int64_t) l_iter2.first;
                    l_ok &= quicky_test::check_expected(l_iter1.second % l_iter2.second,
                                                        quicky_utils::ext_int<int8_t>(l_result),
                                                        (std::string) l_iter1.second + " % " +
                                                        (std::string) l_iter2.second
                                                       );
                }
            }
        }

        std::cout << "Check " << l_type_name << " += operator" << std::endl;
        // Check += operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t) l_iter1.first;
                l_result += (int64_t) l_iter2.first;
                ext_int<int8_t> l_test = l_iter1.second;
                l_test += l_iter2.second;
                l_ok &= quicky_test::check_expected(l_test,
                                                    quicky_utils::ext_int<int8_t>(l_result),
                                                    (std::string) l_iter1.second + " +=" +
                                                    (std::string) l_iter2.second
                                                       );
            }
        }

        std::cout << "Check " << l_type_name << " -= operator" << std::endl;
        // Check -= operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t) l_iter1.first;
                l_result -= (int64_t) l_iter2.first;
                ext_int<int8_t> l_test = l_iter1.second;
                l_test -= l_iter2.second;
                l_ok &= quicky_test::check_expected(l_test,
                                                    quicky_utils::ext_int<int8_t>(l_result),
                                                    (std::string) l_iter1.second + " -=" +
                                                    (std::string) l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " *= operator" << std::endl;
        // Check *= operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                int64_t l_result = (int64_t) l_iter1.first;
                l_result *= (int64_t) l_iter2.first;
                ext_int<int8_t> l_test = l_iter1.second;
                l_test *= l_iter2.second;
                l_ok &= quicky_test::check_expected(l_test,
                                                    quicky_utils::ext_int<int8_t>(l_result),
                                                    (std::string) l_iter1.second + " *=" +
                                                    (std::string) l_iter2.second
                                                   );
            }
        }

        std::cout << "Check " << l_type_name << " /= operator" << std::endl;
        // Check /= operator
        for(auto l_iter1: l_test_values)
        {
            for(auto l_iter2: l_test_values)
            {
                if(l_iter2.first)
                {
                    int64_t l_result = (int64_t) l_iter1.first;
                    l_result /= (int64_t) l_iter2.first;
                    ext_int<int8_t> l_test = l_iter1.second;
                    l_test /= l_iter2.second;
                    l_ok &= quicky_test::check_expected(l_test,
                                                        quicky_utils::ext_int<int8_t>(l_result),
                                                        (std::string) l_iter1.second + " /=" +
                                                        (std::string) l_iter2.second
                                                       );
                }
            }
        }

        std::cout << "Check " << l_type_name << " abs method" << std::endl;
        // Check abs operator
        for(auto l_iter1: l_test_values)
        {
            int64_t l_result = llabs((int64_t)l_iter1.first);
            l_ok &= quicky_test::check_expected(std::abs(l_iter1.second),
                                                quicky_utils::ext_int<int8_t>(l_result),
                                                "abs(" + (std::string)l_iter1.second +")"
                                               );
        }

        std::cout << "Check " << l_type_name << " >> operator" << std::endl;
        // Check >> operator
        for(auto l_iter1: l_test_values)
        {
            for(unsigned int l_i = 0; l_i < 1 + 8 * sizeof(uint32_t); ++l_i)
            {
                    int64_t l_result = ((int64_t) l_iter1.first) >> l_i;
                    l_ok &= quicky_test::check_expected(l_iter1.second >> ext_int<int8_t>(l_i),
                                                        quicky_utils::ext_int<int8_t>(l_result),
                                                        (std::string) l_iter1.second + " >> " +
                                                        std::to_string(l_i)
                                                       );
            }
        }

        std::cout << "Check " << l_type_name << " << operator" << std::endl;
        // Check << operator
        for(auto l_iter1: l_test_values)
        {
            for(unsigned int l_i = 0; l_i < 8 * sizeof(uint32_t); ++l_i)
            {
                    int64_t l_result = ((int64_t) l_iter1.first) << l_i;
                    l_ok &= quicky_test::check_expected(l_iter1.second << ext_int<int8_t>(l_i),
                                                        quicky_utils::ext_int<int8_t>(l_result),
                                                        (std::string) l_iter1.second + " << " +
                                                        std::to_string(l_i)
                                                       );
            }
        }

        //------------------------------------------------------------------
        //    |  0 |  0 |  0 |  0 |  0 |  0 |
        //    |0000|0000|0000|0000|0000|0000|
        // Sign: 0 Exp: 0x0 Mantissa: 0x0
        // Inverted M: 0 E: 0x0
        // OK = > 0x0
        //------------------------------------------------------------------
        //    |  0 |  0 |  0 |  0 |  0 |  1 |
        //    |0000|0000|0000|0000|0000|0001| Complete Mantissa
        // Sign: 0 Exp: 0x7f Mantissa: 0x0
        // Inverted M: 0.5 E: 0x1
        // OK = > 0x1
        //------------------------------------------------------------------
        //    |  0 |  0 |  0 |  0 |  0 |  2 |
        //    |0000|0000|0000|0000|0000|0010| Complete Mantissa
        // Sign: 0 Exp: 0x80 Mantissa: 0x0
        // Inverted M: 0.5 E: 0x2
        // OK = > 0x2
        //------------------------------------------------------------------
        //    |  4 |  0 |  0 |  0 |  0 |  1 |
        //    |0100|0000|0000|0000|0000|0001|
        //    |1000|0000|0000|0000|0000|0010| Complete Mantissa Shift <- 1
        //    | 000|0000|0000|0000|0000|0010| Truncated Mantissa
        // Sign: 0 Exp: 0x95 Mantissa: 0x2
        // Inverted M: 0.5 E: 0x17
        // OK = > 0x400001
        //------------------------------------------------------------------
        //    |  8 |  0 |  0 |  0 |  0 |  1 |
        //    |1000|0000|0000|0000|0000|0001|
        //    |1000|0000|0000|0000|0000|0001| Complete Mantissa Shift 0
        //    | 000|0000|0000|0000|0000|0001| Truncated Mantissa
        // Sign: 0 Exp: 0x96 Mantissa: 0x1
        // Inverted M: 0.5 E: 0x18
        // OK = > 0x800001
        //------------------------------------------------------------------
        //    |  8 |  0 |  0 |  0 |  0 |  0 |
        //    |1000|0000|0000|0000|0000|0000|
        //    |1000|0000|0000|0000|0000|0000| Complete Mantissa Shift 0
        //    | 000|0000|0000|0000|0000|0000| Truncated Mantissa
        // Sign: 0 Exp: 0x96 Mantissa: 0x0
        // Inverted M: 0.5 E: 0x18
        // OK = > 0x800000
        //------------------------------------------------------------------
        // 1  |  8 |  0 |  0 |  0 |  0 |  1 |
        //0001|1000|0000|0000|0000|0000|0001|
        // 000|1100|0000|0000|0000|0000|0000| Complete Mantissa Shift -> 1
        //    | 100|0000|0000|0000|0000|0000| Truncated Mantissa
        // Sign: 0 Exp: 0x97 Mantissa: 0x400000
        // Inverted M: 0.75 E: 0x19
        // KO = > 0x1800000
        //------------------------------------------------------------------
        // 1  |  8 |  0 |  0 |  0 |  0 |  2 |
        //0001|1000|0000|0000|0000|0000|0010|
        // 000|1100|0000|0000|0000|0000|0001| Complete Mantissa Shift -> 1
        //    | 100|0000|0000|0000|0000|0001| Truncated Mantissa
        // Sign: 0 Exp: 0x97 Mantissa: 0x400001
        // Inverted M: 0.75 E: 0x19
        // OK = > 0x1800002
        //------------------------------------------------------------------
        // 1  |  0 |  0 |  0 |  0 |  0 |  1 |
        //0001|0000|0000|0000|0000|0000|0001|
        // 000|1000|0000|0000|0000|0000|0000| Complete Mantissa Shift -> 1
        //    | 000|0000|0000|0000|0000|0000| Truncated Mantissa
        // Sign: 0 Exp: 0x97 Mantissa: 0x0
        // Inverted M: 0.5 E: 0x19
        // KO = > 0x1000000
        //------------------------------------------------------------------
        // 1  |  0 |  0 |  0 |  0 |  0 |  2 |
        //0001|0000|0000|0000|0000|0000|0010|
        // 000|1000|0000|0000|0000|0000|0001| Complete Mantissa Shift -> 1
        //    | 000|0000|0000|0000|0000|0001| Truncated Mantissa
        // Sign: 0 Exp: 0x97 Mantissa: 0x1
        // Inverted M: 0.5 E: 0x19
        // OK = > 0x1000002
        //------------------------------------------------------------------
        // 8  |  0 |  0 |  0 |  0 |  0 |  8 |  0 |
        //1000|0000|0000|0000|0000|0000|1000|0000|
        //          1000|0000|0000|0000|0000|0000| Complete Mantissa shift -> 8
        // Sign: 0 Exp: 0x9e Mantissa: 0x0
        // Inverted M: 0.5 E: 0x20
        // KO = > 0x80000000
        //------------------------------------------------------------------
        // 0  |  1 |  0 |  0 |  0 |  0 |  7 |  f |
        //0000|0001|0000|0000|0000|0000|0111|1111|
        //         |1000|0000|0000|0000|0011|1111| Complete Mantissa shift -> 1
        //           000|0000|0000|0000|0011|1111| Truncated Mantissa

        std::cout << "Check " << l_type_name << " << float()/double() operator" << std::endl;
        for(auto l_iter: l_test_values)
        {
          l_ok &= check_floating_conversion<int32_t, ext_int<int8_t>, float>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int8_t>, double>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int16_t>, float>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int16_t>, double>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int32_t>, float>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int32_t>, double>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int64_t>, float>(l_iter.first);
          l_ok &= check_floating_conversion<int32_t, ext_int<int64_t>, double>(l_iter.first);
        }

        // ||-128 |  64 |  32 |  16 |   8 |   4 |   2 |   1 |
        //-||-----------------------------------------------|
        // ||   0 |   1 |   1 |   1 |   1 |   1 |   1 |   1 | =>  127
        // ||   0 |   0 |   0 |   0 |   0 |   0 |   0 |   1 | =>    1
        // ||   1 |   1 |   1 |   1 |   1 |   1 |   1 |   1 | => -  1
        // ||   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 | =>    0
        // ||   1 |   0 |   0 |   0 |   0 |   0 |   0 |   1 | => -127
        // ||   1 |   0 |   0 |   0 |   0 |   0 |   0 |   0 | => -128
        // ||   1 |   1 |   1 |   1 |   1 |   1 |   0 |   1 | => -  3 [253]
        // ||   1 |   1 |   1 |   1 |   1 |   0 |   1 |   1 | => -  5 [251]
        // ||   0 |   0 |   0 |   0 |   1 |   1 |   1 |   1 | =>   15 [ 3 * 5]
        // ||   1 |   1 |   1 |   1 |   0 |   0 |   0 |   1 | =>  -15
//100      ||   1 |   1 |   1 |   1 |   0 |   0 |   0 |   1 | =>  -15 [-3 * 5]
// 10      ||   1 |   1 |   1 |   1 |   0 |   0 |   0 |   1 | =>  -15 [-5 * 3]


        // -512 | 256 || 128 |  64 |  32 |  16 |   8 |   4 |   2 |   1 |
        //------------||-----------------------------------------------|
        //    0 |   0 ||   1 |   0 |   0 |   0 |   0 |   0 |   0 |   0 | =>  128
        //    1 |   1 ||   1 |   0 |   0 |   0 |   0 |   0 |   0 |   0 | => -128
        //    1 |   1 ||   1 |   1 |   1 |   1 |   1 |   1 |   1 |   1 | => -  1
        //    1 |   1 ||   0 |   1 |   1 |   1 |   1 |   1 |   1 |   1 | => -129
        //    0 |   1 ||   0 |   0 |   0 |   0 |   0 |   0 |   0 |   1 | =>  257
        //    1 |   0 ||   1 |   1 |   1 |   1 |   1 |   1 |   1 |   1 | => -257

        std::cout << "Check " << l_type_name << " << bad constructs" << std::endl;
        l_ok &= quicky_test::check_exception<quicky_exception::quicky_logic_exception>([]{ext_int<int8_t> l_int8_t(0, {0x0});},true,"Check zero bad construct");
        l_ok &= quicky_test::check_exception<quicky_exception::quicky_logic_exception>([]{ext_int<int8_t> l_int8_t(0, {});},false,"Check zero good construct");
        l_ok &= quicky_test::check_exception<quicky_exception::quicky_logic_exception>([]{ext_int<int8_t> l_int8_t(-1, {});},false,"Check -1 good construct");
        l_ok &= quicky_test::check_exception<quicky_exception::quicky_logic_exception>([]{ext_int<int8_t> l_int8_t(-1, {0xFF});},true,"Check -1 bad construct");

        ext_int<int8_t> l_0(0,{});
        ext_int<int8_t> l_0_bis(0,{});
        ext_int<int8_t> l_1(1,{});
        ext_int<int8_t> l_m1(-1,{});
        ext_int<int8_t> l_127(127,{});
        ext_int<int8_t> l_m128(-128,{});
        ext_int<int8_t> l_128(0,{128});
        ext_int<int8_t> l_m256(-1,{0});
        ext_int<int8_t> l_256(1,{0});
        ext_int<int8_t> l_257(1,{1});
        ext_int<int8_t> l_257_bis(1,{1});

        std::cout << "Check " << l_type_name << " ostream operator" << std::endl;

        l_ok &= quicky_test::check_ostream_operator(l_0,"0x00",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_1,"0x01",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_m1,"-0x01",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_127,"0x7F",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_m128,"-0x80",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_128,"0x80",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_256,"0x0100",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_257,"0x0101",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(l_m256,"-0x0100",quicky_test::auto_message(__FILE__, __LINE__));
        l_ok &= quicky_test::check_ostream_operator(ext_int<int8_t>(-2,{255}),"-0x0101",quicky_test::auto_message(__FILE__, __LINE__));

        l_ok &= quicky_test::check_expected(l_0 == l_0_bis, true, "ext_int::== self comparison");
        l_ok &= quicky_test::check_expected(l_1 == l_0, false, "ext_int::== root comparison");
        l_ok &= quicky_test::check_expected(l_1 == l_256, false, "ext_int::== ext size comparison");
        l_ok &= quicky_test::check_expected(l_257 == l_256, false, "ext_int::== ext content comparison");
        l_ok &= quicky_test::check_expected(l_257 == l_257_bis, true, "ext_int::== ext content comparison");

        l_ok &= quicky_test::check_expected(l_0 != l_0_bis, false, "ext_int::!= self comparison");
        l_ok &= quicky_test::check_expected(l_1 != l_0, true, "ext_int::!= root comparison");
        l_ok &= quicky_test::check_expected(l_1 != l_256, true, "ext_int::!= ext size comparison");
        l_ok &= quicky_test::check_expected(l_257 != l_256, true, "ext_int::!= ext content comparison");
        l_ok &= quicky_test::check_expected(l_257 != l_257_bis, false, "ext_int::!= ext content comparison");

        l_ok &= quicky_test::check_expected(l_0 < l_0, false, "0 < 0");
        l_ok &= quicky_test::check_expected(l_0 < l_1, true, "0 < 1");
        l_ok &= quicky_test::check_expected(l_0 < l_m1, false, "0 < -1");
        l_ok &= quicky_test::check_expected(l_0 < l_127, true, "0 < 127");
        l_ok &= quicky_test::check_expected(l_0 < l_128, true, "0 < 128");
        l_ok &= quicky_test::check_expected(l_0 < l_m128, false, "0 < -128");
        l_ok &= quicky_test::check_expected(l_0 < l_256, true, "0 < 256");
        l_ok &= quicky_test::check_expected(l_0 < l_m256, false, "0 < -256");
        l_ok &= quicky_test::check_expected(l_0 < l_257, true, "0 < 257");

        l_ok &= quicky_test::check_expected(l_1 < l_0, false, "1 < 0");
        l_ok &= quicky_test::check_expected(l_1 < l_1, false, "1 < 1");
        l_ok &= quicky_test::check_expected(l_1 < l_m1, false, "1 < -1");
        l_ok &= quicky_test::check_expected(l_1 < l_127, true, "1 < 127");
        l_ok &= quicky_test::check_expected(l_1 < l_128, true, "1 < 128");
        l_ok &= quicky_test::check_expected(l_1 < l_m128, false, "1 < -128");
        l_ok &= quicky_test::check_expected(l_1 < l_256, true, "1 < 256");
        l_ok &= quicky_test::check_expected(l_1 < l_m256, false, "1 < -256");
        l_ok &= quicky_test::check_expected(l_1 < l_257, true, "1 < 257");

        l_ok &= quicky_test::check_expected(l_m1 < l_0, true, "-1 < 0");
        l_ok &= quicky_test::check_expected(l_m1 < l_1, true, "-1 < 1");
        l_ok &= quicky_test::check_expected(l_m1 < l_m1, false, "-1 < -1");
        l_ok &= quicky_test::check_expected(l_m1 < l_127, true, "-1 < 127");
        l_ok &= quicky_test::check_expected(l_m1 < l_128, true, "-1 < 128");
        l_ok &= quicky_test::check_expected(l_m1 < l_m128, false, "-1 < -128");
        l_ok &= quicky_test::check_expected(l_m1 < l_256, true, "-1 < 256");
        l_ok &= quicky_test::check_expected(l_m1 < l_m256, false, "-1 < -256");
        l_ok &= quicky_test::check_expected(l_m1 < l_257, true, "-1 < 257");

        l_ok &= quicky_test::check_expected(l_127 < l_0, false, "127 < 0");
        l_ok &= quicky_test::check_expected(l_127 < l_1, false, "127 < 1");
        l_ok &= quicky_test::check_expected(l_127 < l_m1, false, "127 < -1");
        l_ok &= quicky_test::check_expected(l_127 < l_127, false, "127 < 127");
        l_ok &= quicky_test::check_expected(l_127 < l_128, true, "127 < 128");
        l_ok &= quicky_test::check_expected(l_127 < l_m128, false, "127 < -128");
        l_ok &= quicky_test::check_expected(l_127 < l_256, true, "127 < 256");
        l_ok &= quicky_test::check_expected(l_127 < l_m256, false, "127 < -256");
        l_ok &= quicky_test::check_expected(l_127 < l_257, true, "127 < 257");

        l_ok &= quicky_test::check_expected(l_128 < l_0, false, "128 < 0");
        l_ok &= quicky_test::check_expected(l_128 < l_1, false, "128 < 1");
        l_ok &= quicky_test::check_expected(l_128 < l_m1, false, "128 < -1");
        l_ok &= quicky_test::check_expected(l_128 < l_127, false, "128 < 127");
        l_ok &= quicky_test::check_expected(l_128 < l_128, false, "128 < 128");
        l_ok &= quicky_test::check_expected(l_128 < l_m128, false, "128 < -128");
        l_ok &= quicky_test::check_expected(l_128 < l_256, true, "128 < 256");
        l_ok &= quicky_test::check_expected(l_128 < l_m256, false, "128 < -256");
        l_ok &= quicky_test::check_expected(l_128 < l_257, true, "128 < 257");

        l_ok &= quicky_test::check_expected(l_m128 < l_0, true, "-128 < 0");
        l_ok &= quicky_test::check_expected(l_m128 < l_1, true, "-128 < 1");
        l_ok &= quicky_test::check_expected(l_m128 < l_m1, true, "-128 < -1");
        l_ok &= quicky_test::check_expected(l_m128 < l_127, true, "-128 < 127");
        l_ok &= quicky_test::check_expected(l_m128 < l_128, true, "-128 < 128");
        l_ok &= quicky_test::check_expected(l_m128 < l_m128, false, "-128 < -128");
        l_ok &= quicky_test::check_expected(l_m128 < l_256, true, "-128 < 256");
        l_ok &= quicky_test::check_expected(l_m128 < l_m256, false, "-128 < -256");
        l_ok &= quicky_test::check_expected(l_m128 < l_257, true, "-128 < 257");

        l_ok &= quicky_test::check_expected(l_256 < l_0, false, "256 < 0");
        l_ok &= quicky_test::check_expected(l_256 < l_1, false, "256 < 1");
        l_ok &= quicky_test::check_expected(l_256 < l_m1, false, "256 < -1");
        l_ok &= quicky_test::check_expected(l_256 < l_127, false, "256 < 127");
        l_ok &= quicky_test::check_expected(l_256 < l_128, false, "256 < 128");
        l_ok &= quicky_test::check_expected(l_256 < l_m128, false, "256 < -128");
        l_ok &= quicky_test::check_expected(l_256 < l_256, false, "256 < 256");
        l_ok &= quicky_test::check_expected(l_256 < l_m256, false, "256 < -256");
        l_ok &= quicky_test::check_expected(l_256 < l_257, true, "256 < 257");

        l_ok &= quicky_test::check_expected(l_m256 < l_0, true, "-256 < 0");
        l_ok &= quicky_test::check_expected(l_m256 < l_1, true, "-256 < 1");
        l_ok &= quicky_test::check_expected(l_m256 < l_m1, true, "-256 < -1");
        l_ok &= quicky_test::check_expected(l_m256 < l_127, true, "-256 < 127");
        l_ok &= quicky_test::check_expected(l_m256 < l_128, true, "-256 < 128");
        l_ok &= quicky_test::check_expected(l_m256 < l_m128, true, "-256 < -128");
        l_ok &= quicky_test::check_expected(l_m256 < l_256, true, "-256 < 256");
        l_ok &= quicky_test::check_expected(l_m256 < l_m256, false, "-256 < -256");
        l_ok &= quicky_test::check_expected(l_m256 < l_257, true, "-256 < 257");

        l_ok &= quicky_test::check_expected(l_257 < l_0, false, "257 < 0");
        l_ok &= quicky_test::check_expected(l_257 < l_1, false, "257 < 1");
        l_ok &= quicky_test::check_expected(l_257 < l_m1, false, "257 < -1");
        l_ok &= quicky_test::check_expected(l_257 < l_127, false, "257 < 127");
        l_ok &= quicky_test::check_expected(l_257 < l_128, false, "257 < 128");
        l_ok &= quicky_test::check_expected(l_257 < l_m128, false, "257 < -128");
        l_ok &= quicky_test::check_expected(l_257 < l_256, false, "257 < 256");
        l_ok &= quicky_test::check_expected(l_257 < l_m256, false, "257 < -256");
        l_ok &= quicky_test::check_expected(l_257 < l_257, false, "257 < 257");

        l_ok &= quicky_test::check_expected(l_0 > l_0, false, "0 > 0");
        l_ok &= quicky_test::check_expected(l_0 > l_1, false, "0 > 1");
        l_ok &= quicky_test::check_expected(l_0 > l_m1, true, "0 > -1");
        l_ok &= quicky_test::check_expected(l_0 > l_127, false, "0 > 127");
        l_ok &= quicky_test::check_expected(l_0 > l_128, false, "0 > 128");
        l_ok &= quicky_test::check_expected(l_0 > l_m128, true, "0 > -128");
        l_ok &= quicky_test::check_expected(l_0 > l_256, false, "0 > 256");
        l_ok &= quicky_test::check_expected(l_0 > l_m256, true, "0 > -256");
        l_ok &= quicky_test::check_expected(l_0 > l_257, false, "0 > 257");

        l_ok &= quicky_test::check_expected(l_1 > l_0, true, "1 > 0");
        l_ok &= quicky_test::check_expected(l_1 > l_1, false, "1 > 1");
        l_ok &= quicky_test::check_expected(l_1 > l_m1, true, "1 > -1");
        l_ok &= quicky_test::check_expected(l_1 > l_127, false, "1 > 127");
        l_ok &= quicky_test::check_expected(l_1 > l_128, false, "1 > 128");
        l_ok &= quicky_test::check_expected(l_1 > l_m128, true, "1 > -128");
        l_ok &= quicky_test::check_expected(l_1 > l_256, false, "1 > 256");
        l_ok &= quicky_test::check_expected(l_1 > l_m256, true, "1 > -256");
        l_ok &= quicky_test::check_expected(l_1 > l_257, false, "1 > 257");

        l_ok &= quicky_test::check_expected(l_m1 > l_0, false, "-1 > 0");
        l_ok &= quicky_test::check_expected(l_m1 > l_1, false, "-1 > 1");
        l_ok &= quicky_test::check_expected(l_m1 > l_m1, false, "-1 > -1");
        l_ok &= quicky_test::check_expected(l_m1 > l_127, false, "-1 > 127");
        l_ok &= quicky_test::check_expected(l_m1 > l_128, false, "-1 > 128");
        l_ok &= quicky_test::check_expected(l_m1 > l_m128, true, "-1 > -128");
        l_ok &= quicky_test::check_expected(l_m1 > l_256, false, "-1 > 256");
        l_ok &= quicky_test::check_expected(l_m1 > l_m256, true, "-1 > -256");
        l_ok &= quicky_test::check_expected(l_m1 > l_257, false, "-1 > 257");

        l_ok &= quicky_test::check_expected(l_127 > l_0, true, "127 > 0");
        l_ok &= quicky_test::check_expected(l_127 > l_1, true, "127 > 1");
        l_ok &= quicky_test::check_expected(l_127 > l_m1, true, "127 > -1");
        l_ok &= quicky_test::check_expected(l_127 > l_127, false, "127 > 127");
        l_ok &= quicky_test::check_expected(l_127 > l_128, false, "127 > 128");
        l_ok &= quicky_test::check_expected(l_127 > l_m128, true, "127 > -128");
        l_ok &= quicky_test::check_expected(l_127 > l_256, false, "127 > 256");
        l_ok &= quicky_test::check_expected(l_127 > l_m256, true, "127 > -256");
        l_ok &= quicky_test::check_expected(l_127 > l_257, false, "127 > 257");

        l_ok &= quicky_test::check_expected(l_128 > l_0, true, "128 > 0");
        l_ok &= quicky_test::check_expected(l_128 > l_1, true, "128 > 1");
        l_ok &= quicky_test::check_expected(l_128 > l_m1, true, "128 > -1");
        l_ok &= quicky_test::check_expected(l_128 > l_127, true, "128 > 127");
        l_ok &= quicky_test::check_expected(l_128 > l_128, false, "128 > 128");
        l_ok &= quicky_test::check_expected(l_128 > l_m128, true, "128 > -128");
        l_ok &= quicky_test::check_expected(l_128 > l_256, false, "128 > 256");
        l_ok &= quicky_test::check_expected(l_128 > l_m256, true, "128 > -256");
        l_ok &= quicky_test::check_expected(l_128 > l_257, false, "128 > 257");

        l_ok &= quicky_test::check_expected(l_m128 > l_0, false, "-128 > 0");
        l_ok &= quicky_test::check_expected(l_m128 > l_1, false, "-128 > 1");
        l_ok &= quicky_test::check_expected(l_m128 > l_m1, false, "-128 > -1");
        l_ok &= quicky_test::check_expected(l_m128 > l_127, false, "-128 > 127");
        l_ok &= quicky_test::check_expected(l_m128 > l_128, false, "-128 > 128");
        l_ok &= quicky_test::check_expected(l_m128 > l_m128, false, "-128 > -128");
        l_ok &= quicky_test::check_expected(l_m128 > l_256, false, "-128 > 256");
        l_ok &= quicky_test::check_expected(l_m128 > l_m256, true, "-128 > -256");
        l_ok &= quicky_test::check_expected(l_m128 > l_257, false, "-128 > 257");

        l_ok &= quicky_test::check_expected(l_256 > l_0, true, "256 > 0");
        l_ok &= quicky_test::check_expected(l_256 > l_1, true, "256 > 1");
        l_ok &= quicky_test::check_expected(l_256 > l_m1, true, "256 > -1");
        l_ok &= quicky_test::check_expected(l_256 > l_127, true, "256 > 127");
        l_ok &= quicky_test::check_expected(l_256 > l_128, true, "256 > 128");
        l_ok &= quicky_test::check_expected(l_256 > l_m128, true, "256 > -128");
        l_ok &= quicky_test::check_expected(l_256 > l_256, false, "256 > 256");
        l_ok &= quicky_test::check_expected(l_256 > l_m256, true, "256 > -256");
        l_ok &= quicky_test::check_expected(l_256 > l_257, false, "256 > 257");

        l_ok &= quicky_test::check_expected(l_m256 > l_0, false, "-256 > 0");
        l_ok &= quicky_test::check_expected(l_m256 > l_1, false, "-256 > 1");
        l_ok &= quicky_test::check_expected(l_m256 > l_m1, false, "-256 > -1");
        l_ok &= quicky_test::check_expected(l_m256 > l_127, false, "-256 > 127");
        l_ok &= quicky_test::check_expected(l_m256 > l_128, false, "-256 > 128");
        l_ok &= quicky_test::check_expected(l_m256 > l_m128, false, "-256 > -128");
        l_ok &= quicky_test::check_expected(l_m256 > l_256, false, "-256 > 256");
        l_ok &= quicky_test::check_expected(l_m256 > l_m256, false, "-256 > -256");
        l_ok &= quicky_test::check_expected(l_m256 > l_257, false, "-256 > 257");

        l_ok &= quicky_test::check_expected(l_257 > l_0, true, "257 > 0");
        l_ok &= quicky_test::check_expected(l_257 > l_1, true, "257 > 1");
        l_ok &= quicky_test::check_expected(l_257 > l_m1, true, "257 > -1");
        l_ok &= quicky_test::check_expected(l_257 > l_127, true, "257 > 127");
        l_ok &= quicky_test::check_expected(l_257 > l_128, true, "257 > 128");
        l_ok &= quicky_test::check_expected(l_257 > l_m128, true, "257 > -128");
        l_ok &= quicky_test::check_expected(l_257 > l_256, true, "257 > 256");
        l_ok &= quicky_test::check_expected(l_257 > l_m256, true, "257 > -256");
        l_ok &= quicky_test::check_expected(l_257 > l_257, false, "257 > 257");

        l_ok &= quicky_test::check_expected(l_0 + l_0, l_0, "0 + 0 == 0");
        l_ok &= quicky_test::check_expected(l_0 + l_1, l_1, "0 + 1 == 1");
        l_ok &= quicky_test::check_expected(l_0 + l_m1, l_m1, "0 + -1 == -1");
        l_ok &= quicky_test::check_expected(l_0 + l_127, l_127, "0 + 127 == 127");
        l_ok &= quicky_test::check_expected(l_0 + l_128, l_128, "0 + 128 == 128");
        l_ok &= quicky_test::check_expected(l_0 + l_m128, l_m128, "0 + -128 == -128");
        l_ok &= quicky_test::check_expected(l_0 + l_256, l_256, "0 + 256 == 256");
        l_ok &= quicky_test::check_expected(l_0 + l_m256, l_m256, "0 + -256 == -256");
        l_ok &= quicky_test::check_expected(l_0 + l_257, l_257, "0 + 257 == 257");

        l_ok &= quicky_test::check_expected(l_1 + l_0, l_1, "1 + 0 == 1");
        l_ok &= quicky_test::check_expected(l_1 + l_1, ext_int<int8_t>(2,{}), "1 + 1 == 2");
        l_ok &= quicky_test::check_expected(l_1 + l_m1, l_0, "1 + -1 == 0");
        l_ok &= quicky_test::check_expected(l_1 + l_127, l_128, "1 + 127 == 128");
        l_ok &= quicky_test::check_expected(l_1 + l_128, ext_int<int8_t>(0,{129}), "1 + 128 == 129");
        l_ok &= quicky_test::check_expected(l_1 + l_m128, ext_int<int8_t>(-127,{}), "1 + -128 == -127");
        l_ok &= quicky_test::check_expected(l_1 + l_256, l_257, "1 + 256 == 257");
        l_ok &= quicky_test::check_expected(l_1 + l_m256, ext_int<int8_t>(-1,{1}), "1 + -256 == -255");
        l_ok &= quicky_test::check_expected(l_1 + l_257, ext_int<int8_t>(1, {2}), "1 + 257 == 258");

        l_ok &= quicky_test::check_expected(l_m1 + l_0, ext_int<int8_t>(-1,{}), "-1 + 0 == -1");
        l_ok &= quicky_test::check_expected(l_m1 + l_1, l_0, "-1 + 1 == 0");
        l_ok &= quicky_test::check_expected(l_m1 + l_m1, ext_int<int8_t>(-2,{}), "-1 + -1 == -2");
        l_ok &= quicky_test::check_expected(l_m1 + l_127, ext_int<int8_t>(126,{}), "-1 + 127 == 126");
        l_ok &= quicky_test::check_expected(l_m1 + l_128, l_127, "-1 + 128 == 127");
        l_ok &= quicky_test::check_expected(l_m1 + l_m128, ext_int<int8_t>(-1,{127}), "-1 + -128 == -129");
        l_ok &= quicky_test::check_expected(l_m1 + l_256, ext_int<int8_t>(0,{255}), "-1 + 256 == 255");
        l_ok &= quicky_test::check_expected(l_m1 + l_m256, ext_int<int8_t>(-2,{255}), "-1 + -256 == -257");
        l_ok &= quicky_test::check_expected(l_m1 + l_257, l_256, "-1 + 257 == 256");

        return l_ok;
    }

}

#endif // QUICKY_UTILS_SELF_TEST
// EOF
