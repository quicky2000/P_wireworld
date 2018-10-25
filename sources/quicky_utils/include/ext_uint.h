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
#ifndef QUICKY_UTILS_EXT_UINT_H
#define QUICKY_UTILS_EXT_UINT_H

#include "safe_uint.h"
#include "quicky_exception.h"
#include "ext_int.h"
#include "type_string.h"
#include <vector>
#include <cstdio>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <type_traits>

namespace quicky_utils
{

    template <typename T>
    class ext_uint;

    template <typename T>
    class ext_int;

    template <typename T>
    std::ostream &
    operator<<(std::ostream & p_stream,
               const ext_uint<T> & p_ext_uint
              );

    /**
     * Class defining uint type that will extend as necessary to avoid overflows
     * @tparam T build-in types made safe
     */
    template <typename T>
    class ext_uint
    {
      public:
        /**
         * Empty constructor
         */
        ext_uint();

        /**
         * Move constructor
         */
        ext_uint(const ext_uint && p_value)noexcept;

        /**
         * Copy constructor
         */
        ext_uint(const ext_uint & p_value);

        /**
         * Initializer list constructor
         * @param p_init_list list of values to fill vector
         */
        ext_uint(const std::initializer_list<T> & p_init_list);

        /**
         * Constructor from uint32_t
         * @param p_value value to convert to ext_uint
         */
#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_UINT_DISABLE_EXPLICIT
        ext_uint(const uint32_t & p_value);

        /**
         * Constructor from uint64_t
         * @param p_value value to convert to ext_uint
         */
#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_INT_DISABLE_EXPLICIT
        ext_uint(const uint64_t & p_value);

        /**
         * Constructor from ext_uint
         * @param T
         */
#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_INT_DISABLE_EXPLICIT
        ext_uint(const ext_int<typename std::make_signed<T>::type> & p_ext_int);

#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_INT_DISABLE_EXPLICIT
        operator bool() const;

#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_INT_DISABLE_EXPLICIT
        operator float() const;

#ifndef EXT_UINT_DISABLE_EXPLICIT
        explicit
#endif // EXT_INT_DISABLE_EXPLICIT
        operator double() const;

        /**
         * Accessor returning number of words composing type
         * @return number of word composing type
         */
        size_t get_nb_words()const;

        /**
         * Accessor returning number of bytes composing type
         * @return number of bytes composing type
         */
        size_t get_nb_bytes() const;

        /**
         * Return word located at p_index
         * @param p_index location of word to return
         * @return word located at place defined by paramter
         */
        const T & get_word(const unsigned int & p_index) const;

        /**
         * Display content of ext_uint in hexadecimal
         * @param os output stream
         * @param p_ext_uint ext_uint to display
         */
        friend std::ostream &
        operator<< <>(std::ostream & os,
                   const ext_uint<T> & p_ext_uint
                  );

        /**
         * Move assignment operator
         * @param p_op value to move
         * @return assigned object
         */
        ext_uint<T> & operator=(ext_uint<T> && p_op);

        /**
         * Assignment operator
         * @param p_op value to move
         * @return assigned object
         */
        ext_uint<T> & operator=(const ext_uint<T> & p_op);

        bool
        operator==(const ext_uint & p_op) const;

        bool
        operator!=(const ext_uint & p_op) const;

        bool
        operator<(const ext_uint & p_op) const;

        bool
        operator>(const ext_uint & p_op) const;

        bool
        operator<=(const ext_uint & p_op) const;

        bool
        operator>=(const ext_uint & p_op) const;

        ext_uint<T>
        operator<<(const ext_uint & p_op) const;

        ext_uint<T>
        operator>>(const ext_uint & p_op) const;

        ext_uint<T>
        operator+(const ext_uint & p_op) const;

        ext_uint<T>
        operator-(const ext_uint & p_op) const;

        ext_uint<T>
        operator*(const ext_uint & p_op) const;

        ext_uint<T>
        operator/(const ext_uint & p_op) const;

        ext_uint<T>
        operator%(const ext_uint & p_op) const;

        ext_uint<T>
        operator-(void)const;

        ext_uint<T>
        operator+(void)const;

        ext_uint<T>
        operator+=(const ext_uint & p_op);

        ext_uint<T>
        operator-=(const ext_uint & p_op);

        ext_uint<T>
        operator*=(const ext_uint & p_op);

        ext_uint<T>
        operator/=(const ext_uint & p_op);

        typedef T base_type;

        /**
         * Extension accessor
         * @return extension
         */
        const std::vector<T> & get_extension()const;

        /**
         * string cast operator
         * @return string representation
         */
        operator std::string() const;

        /**
         * Helper method used in / and % operator
         * @param p_op operand for division
         * @param p_compute_mult indicate if mult should be computed
         * @param p_mult value or returned result * p_op
         * @return value of this / div
         */
        ext_uint <T>
        div(const ext_uint & p_op,
            bool p_compute_mult,
            ext_uint <T> & p_mult
           ) const;

      private:
        /**
         * Method checking ig object has the shortest possible representation
         * @return true if object don't have shortest possible representation
         */
        bool is_trimmable() const;

        /**
         * Method ensuring that object has the shortest possible representation
         */
        ext_uint<T> & trim();


        /**
         * Constuctor form a vector
         * @param p_vec Vector representing number
         * @param check_trim check if number is trimmable or not
         */
        ext_uint(const std::vector<T> & p_vec
                ,bool check_trim = true
                );

        /**
         * Methods extracting necessary info to build ext_int from an integer
         * value ( int64_t etc )
         * @tparam UINT_TYPE type of unsigned integer value to extract
         * @param p_value value to extract
         * @param p_vector vector to fill
         * */
        template <typename UINT_TYPE, typename std::enable_if<sizeof(T) < sizeof(UINT_TYPE), int>::type = 0>
        static
        void extract(const UINT_TYPE & p_value,
                     std::vector<T> & p_vector
                    );

        /**
         * Methods extracting necessary info to build ext_int from an integer
         * value ( int64_t etc )
         * @tparam UINT_TYPE type of unsigned integer value to extract
         * @param p_value value to extract
         * @param p_vector vector to fill
         * */
        template <typename UINT_TYPE, typename std::enable_if<sizeof(UINT_TYPE) <= sizeof(T), int>::type = 0>
        static
        void extract(const UINT_TYPE & p_value,
                     std::vector<T> & p_vector
                    );

        static void partial_mult(const T & p_op1,
                                 const T & p_op2,
                                 T & p_result_low,
                                 T & p_result_high
                                );

        template <typename FLOATING_TYPE, typename MANTISSA_TYPE, typename std::enable_if< sizeof(FLOATING_TYPE) <= sizeof(T), int>::type = 0>
        FLOATING_TYPE
        extract_mantissa() const;
        template <typename FLOATING_TYPE, typename MANTISSA_TYPE, typename std::enable_if< sizeof(T) < sizeof(FLOATING_TYPE), int>::type = 0>
        FLOATING_TYPE
        extract_mantissa() const;

       template <typename FLOATING_TYPE, typename MANTISSA_TYPE>
        FLOATING_TYPE complete_mantissa(MANTISSA_TYPE p_mantissa
                                        ,size_t p_index
                                       ) const;

        template <typename FLOATING_TYPE, typename MANTISSA_TYPE>
        static
        FLOATING_TYPE add_exponent(FLOATING_TYPE & p_floating
                                  ,int p_add
                                  );

        static_assert(std::is_unsigned<T>::value,"Ckeck base type is unsigned");

        /**
         * Extensions
         */
        std::vector<T> m_ext;

    };

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint():
            m_ext({0})
    {
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const ext_uint<T> && p_value) noexcept:
            m_ext(std::move(p_value.m_ext))
    {

    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const ext_uint<T> & p_value):
            m_ext(p_value.m_ext)
    {

    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const std::initializer_list<T> & p_init_list):
            m_ext(p_init_list)
    {
        assert(p_init_list.size());
        if(is_trimmable())
        {
            throw quicky_exception::quicky_logic_exception("Upper word of ext_uint should be non-zero", __LINE__, __FILE__);
        }
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const std::vector<T> & p_vec
                         ,bool p_check_trim
                         ):
            m_ext(p_vec)
    {
        if(p_check_trim && is_trimmable())
        {
            throw quicky_exception::quicky_logic_exception("Upper word of ext_uint should be non-zero", __LINE__, __FILE__);
        }
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const ext_int<typename std::make_signed<T>::type> & p_ext_int):
    m_ext(p_ext_int.get_extension())
    {
        auto l_root = p_ext_int.get_root();
        if(l_root < 0)
        {
            throw quicky_exception::quicky_logic_exception("Convert negative ext_int to ext_uint", __LINE__, __FILE__);
        }
        if(l_root || !m_ext.size())
        {
            m_ext.push_back(l_root);
        }
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const uint32_t & p_value)
    {
        extract<uint32_t>(p_value, m_ext);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::ext_uint(const uint64_t & p_value)
    {
        extract<uint64_t>(p_value, m_ext);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::operator bool() const
    {
        assert(m_ext.size());
        return m_ext.back();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::operator float() const
    {
        return extract_mantissa<float, uint32_t>();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::operator double() const
    {
        return extract_mantissa<double,uint64_t>();
    }


    //-------------------------------------------------------------------------
    template <typename T>
    size_t
    ext_uint<T>::get_nb_words() const
    {
        return m_ext.size();
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    size_t
    ext_uint<T>::get_nb_bytes() const
    {
        return m_ext.size() * sizeof(T);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    const T &
    ext_uint<T>::get_word(const unsigned int & p_index) const
    {
        assert(p_index < m_ext.size());
        return m_ext[p_index];
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    std::ostream &
    operator<<(std::ostream & p_stream,
               const ext_uint<T> & p_ext_uint
              )
    {
        p_stream << "0x";
        assert(p_ext_uint.m_ext.size());
        char l_fill = p_stream.fill();
        std::streamsize l_width = p_stream.width();
        std::ios::fmtflags l_flags = p_stream.flags();

        for(typename std::vector<T>::const_reverse_iterator l_iter = p_ext_uint.m_ext.rbegin();
            l_iter != p_ext_uint.m_ext.rend();
            ++l_iter
            )
        {
            p_stream << std::hex << std::setw(2*sizeof(T)) << std::setfill('0') << (uint64_t)(*l_iter);
        }

        p_stream << std::setfill(l_fill) << std::setw(l_width) << std::setiosflags(l_flags);
        return p_stream;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T> &
    ext_uint<T>::operator=(ext_uint<T> && p_op)
    {
        m_ext = std::move(p_op.m_ext);
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T> &
    ext_uint<T>::operator=(const ext_uint<T> & p_op)
    {
        m_ext = p_op.m_ext;
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator==(const ext_uint & p_op) const
    {
        if(m_ext.size() != p_op.m_ext.size())
        {
            return false;
        }
        else
        {
            for(unsigned int l_index = 0;
                l_index < m_ext.size();
                ++l_index
               )
            {
                if(m_ext[l_index] != p_op.m_ext[l_index]) return false;
            }
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator!=(const ext_uint & p_op) const
    {
        if(m_ext.size() != p_op.m_ext.size())
        {
            return true;
        }
        else
        {
            for(unsigned int l_index = 0;
                l_index < m_ext.size();
                ++l_index
                    )
            {
                if(m_ext[l_index] != p_op.m_ext[l_index]) return true;
            }
        }
        return false;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator<(const ext_uint & p_op) const
    {
        if (m_ext.size() != p_op.m_ext.size())
        {
            return m_ext.size() < p_op.m_ext.size();
        }
        assert(m_ext.size());
        size_t l_index = m_ext.size() - 1;
        while (l_index < m_ext.size())
        {
            if (m_ext[l_index] != p_op.m_ext[l_index])
            {
                return m_ext[l_index] < p_op.m_ext[l_index];
            }
            --l_index;
        }
        return false;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator>(const ext_uint & p_op) const
    {
        if (m_ext.size() != p_op.m_ext.size())
        {
            return m_ext.size() > p_op.m_ext.size();
        }
        assert(m_ext.size());
        size_t l_index = m_ext.size() - 1;
        while (l_index < m_ext.size())
        {
            if (m_ext[l_index] != p_op.m_ext[l_index])
            {
                return m_ext[l_index] > p_op.m_ext[l_index];
            }
            --l_index;
        }
        return false;
     }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator<=(const ext_uint & p_op) const
    {
        if (m_ext.size() != p_op.m_ext.size())
        {
            return m_ext.size() < p_op.m_ext.size();
        }
        assert(m_ext.size());
        size_t l_index = m_ext.size() - 1;
        while (l_index < m_ext.size())
        {
            if (m_ext[l_index] != p_op.m_ext[l_index])
            {
                return m_ext[l_index] <= p_op.m_ext[l_index];
            }
            --l_index;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::operator>=(const ext_uint & p_op) const
    {
        if (m_ext.size() != p_op.m_ext.size())
        {
            return m_ext.size() > p_op.m_ext.size();
        }
        assert(m_ext.size());
        size_t l_index = m_ext.size() - 1;
        while (l_index < m_ext.size())
        {
            if (m_ext[l_index] != p_op.m_ext[l_index])
            {
                return m_ext[l_index] >= p_op.m_ext[l_index];
            }
            --l_index;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator+(const ext_uint & p_op) const
    {
        size_t l_max_size = m_ext.size() > p_op.m_ext.size() ? m_ext.size() : p_op.m_ext.size();
        size_t l_min_size = m_ext.size() < p_op.m_ext.size() ? m_ext.size() : p_op.m_ext.size();
        bool l_previous_overflow = false;
        std::vector<T> l_new_ext;
        T l_sum;
        for(size_t l_index = 0;
            l_index < l_min_size;
            ++l_index
           )
        {
            bool l_overflow;
            l_sum = safe_uint<T>::check_add(m_ext[l_index],p_op.m_ext[l_index],l_overflow);
            if(l_previous_overflow)
            {
                if (!l_overflow)
                {
                    l_sum = safe_uint<T>::check_add(l_sum,
                                                    l_previous_overflow,
                                                    l_overflow
                                                   );
                } else
                {
                    l_sum += l_previous_overflow;
                }
            }
            l_previous_overflow = l_overflow;
            l_new_ext.push_back(l_sum);
        }
        const std::vector<T> & l_longer = m_ext.size() > p_op.m_ext.size() ? m_ext : p_op.m_ext;
        for(size_t l_index = l_min_size;
            l_index < l_max_size;
            ++l_index
           )
        {
            if(!l_previous_overflow)
            {
                l_sum = l_longer[l_index];
            }
            else
            {
                l_sum = safe_uint<T>::check_add(l_longer[l_index],
                                                l_previous_overflow,
                                                l_previous_overflow
                                               );
            }
            l_new_ext.push_back(l_sum);
        }
        if(l_previous_overflow)
        {
            l_new_ext.push_back(1);
        }
        return ext_uint(l_new_ext, false).trim();
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator-(const ext_uint & p_op) const
    {
        if(m_ext.size() < p_op.m_ext.size())
        {
            throw quicky_exception::quicky_logic_exception("ext_uint substraction underflow", __LINE__, __FILE__);
        }
        std::vector<T> l_new_ext;
        bool l_previous_underflow = false;
        T l_result;
        for(size_t l_index = 0;
            l_index < p_op.m_ext.size();
            ++l_index
                )
        {
            bool l_underflow;
            l_result = safe_uint<T>::check_substr(m_ext[l_index], p_op.m_ext[l_index], l_underflow);
            if(l_underflow && 1 == m_ext.size())
            {
                throw quicky_exception::quicky_logic_exception("ext_uint substraction underflow", __LINE__, __FILE__);
            }
            if(l_previous_underflow)
            {
                if(!l_underflow)
                {
                    l_result = safe_uint<T>::check_substr(l_result, l_previous_underflow, l_underflow);
                }
                else
                {
                    l_result -= l_previous_underflow;
                }
            }
            l_previous_underflow = l_underflow;
            if(l_result || l_index != m_ext.size() - 1 || !l_index)
            {
                l_new_ext.push_back(l_result);
            }
        }
        for(size_t l_index = p_op.m_ext.size();
            l_index < m_ext.size();
            ++l_index
           )
        {
            if(l_previous_underflow)
            {
                l_result = safe_uint<T>::check_substr(m_ext[l_index], l_previous_underflow, l_previous_underflow);
            }
            else
            {
                l_result = m_ext[l_index];
            }
            if(l_result || l_index != m_ext.size() - 1)
            {
                l_new_ext.push_back(l_result);
            }
        }
        return ext_uint(l_new_ext, false).trim();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator*(const ext_uint & p_op) const
    {
        if((1 == m_ext.size() && !m_ext[0]) || (1 == p_op.m_ext.size() && !p_op.m_ext[0]))
        {
            return ext_uint();
        }
        size_t l_new_size = m_ext.size() + p_op.m_ext.size();
        std::vector<T> l_new_ext(l_new_size,0);

        // 12345
        // ABCDE
        // E1 E2 E3 E5
        for(size_t l_index = 0;
            l_index < l_new_size - 1;
            ++l_index
            )
        {
            size_t l_start_index = l_index >= p_op.m_ext.size() ? l_index - p_op.m_ext.size() + 1 : 0;
            for(size_t l_index_op1 = l_start_index;
                l_index_op1 <= l_index && l_index_op1 < m_ext.size();
                ++l_index_op1
               )
            {
                size_t l_index_op2 = l_index - l_index_op1;
                T l_result_low;
                T l_result_high;
                partial_mult(m_ext[l_index_op1],
                             p_op.m_ext[l_index_op2],
                             l_result_low,
                             l_result_high
                            );
                bool l_overflow;
                l_new_ext[l_index] = safe_uint<T>::check_add(l_new_ext[l_index],
                                                             l_result_low,
                                                             l_overflow
                                                            );
                bool l_previous_overflow = l_overflow;
                l_new_ext[l_index + 1] = safe_uint<T>::check_add(l_new_ext[l_index + 1],
                                                                 l_result_high,
                                                                 l_overflow
                                                                );
                if (l_previous_overflow)
                {
                    if (!l_overflow)
                    {
                        l_new_ext[l_index + 1] = safe_uint<T>::check_add(l_new_ext[l_index + 1],
                                                                         l_previous_overflow,
                                                                         l_overflow
                                                                        );
                    }
                    else
                    {
                        l_new_ext[l_index + 1] += l_previous_overflow;
                    }
                }
                if(l_overflow)
                {
                    l_new_ext[l_index + 2]++;
                }
            }
        }
        if(!l_new_ext.back())
        {
            l_new_ext.pop_back();
        }
        return ext_uint(l_new_ext, false).trim();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    void
    ext_uint<T>::partial_mult(const T & p_op1,
                              const T & p_op2,
                              T & p_result_low,
                              T & p_result_high
                             )
    {
        if(!p_op1 || !p_op2)
        {
            p_result_low = 0;
            p_result_high = 0;
            return;
        }
        // AB * CD = (10 * A + B) ( 10 * C + D)
        // AB * CD = 100 * AC + 10 * A * D + B * 10 * C + BD
        // AB * CD = 100 * AC + 10 * (A *D + B  *C) + BD
        constexpr size_t l_shift = sizeof(T) * 4;
        constexpr T l_carry_mask = ((T)1) << l_shift;
        constexpr T l_half_low_mask = l_carry_mask - 1;
        constexpr T l_half_high_mask = l_half_low_mask << l_shift;

        T l_low_part1 = l_half_low_mask & p_op1;
        T l_high_part1 = (l_half_high_mask & p_op1) >> l_shift;
        T l_low_part2 = l_half_low_mask & p_op2;
        T l_high_part2 = (l_half_high_mask & p_op2) >> l_shift;

        T l_result_lower_part = l_low_part1 * l_low_part2;
        bool l_overflow;
        T l_result_l_midlle_part = safe_uint<T>::check_add(l_low_part1 * l_high_part2,l_low_part2 * l_high_part1, l_overflow);
        T l_result_upper_part = l_high_part1 * l_high_part2;

        T l_compl1 = (l_result_l_midlle_part & l_half_low_mask) << l_shift ;
        T l_compl2 = (l_result_l_midlle_part >> l_shift) | (l_carry_mask * l_overflow);

        p_result_low = safe_uint<T>::check_add(l_result_lower_part, l_compl1, l_overflow);
        if(l_overflow)
        {
            l_result_upper_part  = safe_uint<T>::check_add(l_result_upper_part, l_overflow, l_overflow);
        }
        p_result_high = l_compl2 + l_result_upper_part;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator/(const ext_uint & p_op) const
    {
        if(m_ext.size() == 1 && m_ext[0] == 0)
        {
            return ext_uint();
        }
        if(1 == p_op.m_ext.size())
        {
            if (1 == p_op.m_ext[0])
            {
                return *this;
            }
            else if (p_op.m_ext[0] == 0)
            {
                throw quicky_exception::quicky_logic_exception("Illegal division by 0 ext_uint",
                                                               __LINE__,
                                                               __FILE__
                                                              );
            }
            if(1 == m_ext.size())
            {
                return ext_uint<T>({(T)(m_ext[0] / p_op.m_ext[0])});
            }
        }
        if(*this < p_op)
        {
            return ext_uint();
        }
        ext_uint<T> l_mult;
        return div(p_op,
                   false,
                   l_mult
                  );
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator%(const ext_uint & p_op) const
    {
        if(m_ext.size() == 1 && m_ext[0] == 0)
        {
            return ext_uint();
        }
        if(1 == p_op.m_ext.size())
        {
            if (1 == p_op.m_ext[0])
            {
                return ext_uint();
            }
            else if (p_op.m_ext[0] == 0)
            {
                throw quicky_exception::quicky_logic_exception("Illegal division by 0 ext_uint",
                                                               __LINE__,
                                                               __FILE__
                                                              );
            }
            if(1 == m_ext.size())
            {
                return ext_uint<T>({(T)(m_ext[0] % p_op.m_ext[0])});
            }
        }
        if(*this < p_op)
        {
            return *this;
        }
        ext_uint<T> l_mult;
        div(p_op,
            true,
            l_mult
           );
        return (*this - l_mult).trim();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator<<(const ext_uint & p_op) const
    {
        if(p_op.m_ext.size() == 1)
        {
            size_t l_additional_ext = p_op.m_ext[0] / (8 * sizeof(T));
            size_t l_real_shift = p_op.m_ext[0] % (8 * sizeof(T));
            size_t l_new_size = m_ext.size() + l_additional_ext;
            std::vector<T> l_new_ext(l_new_size);
            if(l_real_shift)
            {
                T l_apply_shift = 8 * sizeof(T) - l_real_shift;
                T l_select_mask = (((T)1) << l_real_shift) - 1;
                T l_reminder = 0;
                for (size_t l_index = 0;
                     l_index < m_ext.size();
                     ++l_index
                    )
                {
                    l_new_ext[l_index + l_additional_ext] = (m_ext[l_index] << l_real_shift) | l_reminder;
                    l_reminder = (m_ext[l_index] >> l_apply_shift) & l_select_mask;
                }
                if(l_reminder)
                {
                    l_new_ext.push_back(l_reminder);
                }
            }
            else
            {
                for (size_t l_index = 0;
                     l_index < m_ext.size();
                     ++l_index
                    )
                {
                    l_new_ext[l_index + l_additional_ext] = m_ext[l_index];
                }
            }
        return ext_uint<T>(l_new_ext, false).trim();
        }
        throw quicky_exception::quicky_logic_exception("ext_uint shift operator works only for single extesion", __LINE__, __FILE__);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator>>(const ext_uint & p_op) const
    {
        if(p_op.m_ext.size() == 1)
        {
            size_t l_remove_ext = p_op.m_ext[0] / (8 * sizeof(T));
            size_t l_real_shift = p_op.m_ext[0] % (8 * sizeof(T));
            if(l_remove_ext >= m_ext.size())
            {
                return ext_uint();
            }
            size_t l_new_size = m_ext.size() - l_remove_ext;
            std::vector<T> l_new_ext(l_new_size);
            if(l_real_shift)
            {
                T l_apply_shift = 8 * sizeof(T) - l_real_shift;
                T l_select_mask = (((T)1) << l_real_shift) - 1;
                T l_reminder = 0;
                for (size_t l_index = l_new_size - 1;
                     l_index < l_new_size;
                     --l_index
                        )
                {
                    l_new_ext[l_index] =
                            (m_ext[l_index + l_remove_ext] >> l_real_shift) | (l_reminder << l_apply_shift);
                    l_reminder = m_ext[l_index + l_remove_ext] & l_select_mask;
                }
            }
            else
            {
                for (size_t l_index = 0;
                     l_index < l_new_size;
                     ++l_index
                        )
                {
                    l_new_ext[l_index] = m_ext[l_index + l_remove_ext];
                }
            }
            return ext_uint<T>(l_new_ext, false).trim();
        }
        throw quicky_exception::quicky_logic_exception("ext_uint shift operator works only for single extesion", __LINE__, __FILE__);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint <T>
    ext_uint<T>::div(const ext_uint & p_op,
                         bool p_compute_mult,
                         ext_uint <T> & p_mult
                        ) const
    {
        ext_uint<T> l_min({1});
        ext_uint<T> l_max(m_ext);
        do
        {
            ext_uint<T> l_result = (l_min + l_max) >> ext_uint<T>({1});
            p_mult = p_op * l_result;
            if(p_mult > *this)
            {
                l_max = l_result;
            }
            else if(p_mult <= *this)
            {
                l_min = l_result;
                if(p_mult == *this) return l_min;
            }
        } while(p_mult != * this && l_max - l_min > ext_uint<T>({1}));
        if(p_compute_mult)
        {
            p_mult = l_min * p_op;
        }
        return l_min;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator-(void) const
    {
        throw safe_type_exception("Illegal ext_uint operator-",
                                  __LINE__,
                                  __FILE__
                                 );
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator+(void) const
    {
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator+=(const ext_uint & p_op)
    {
        *this = *this + p_op;
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator-=(const ext_uint & p_op)
    {
        *this = *this - p_op;
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator*=(const ext_uint & p_op)
    {
        *this = *this * p_op;
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>
    ext_uint<T>::operator/=(const ext_uint & p_op)
    {
        *this = *this / p_op;
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    const std::vector<T> &
    ext_uint<T>::get_extension() const
    {
        return m_ext;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename UINT_TYPE, typename std::enable_if<sizeof(T) < sizeof(UINT_TYPE), int>::type>
    void
    ext_uint<T>::extract(const UINT_TYPE & p_value,
                         std::vector<T> & p_vector
                        )
    {
        static_assert(std::is_unsigned<UINT_TYPE>::value, "ext_uint extract method should be used on unsigned types");
        UINT_TYPE l_value = p_value;
        do
        {
            T l_chunk = l_value & ((T) -1);
            l_value = l_value >> (8 * sizeof(T));
            p_vector.push_back(l_chunk);
        }
        while(l_value);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename UINT_TYPE, typename std::enable_if<sizeof(UINT_TYPE) <= sizeof(T), int>::type>
    void
    ext_uint<T>::extract(const UINT_TYPE & p_value,
                         std::vector<T> & p_vector
                        )
    {
        static_assert(std::is_unsigned<UINT_TYPE>::value, "ext_uint extract method should be used on unsigned types");
        p_vector.push_back(p_value);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T>::operator std::string() const
    {
        std::stringstream l_stream;
        l_stream << *this;
        return l_stream.str();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    ext_uint<T>::is_trimmable() const
    {
        return m_ext.size() > 1 && !m_ext.back();
    }

    //-------------------------------------------------------------------------
    template <typename T>
    ext_uint<T> &
    ext_uint<T>::trim()
    {
        while(is_trimmable())
        {
            m_ext.pop_back();
        }
        return *this;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename FLOATING_TYPE, typename MANTISSA_TYPE, typename std::enable_if< sizeof(FLOATING_TYPE) <= sizeof(T), int>::type>
    FLOATING_TYPE
    ext_uint<T>::extract_mantissa() const
    {
        static_assert(sizeof(MANTISSA_TYPE) >= sizeof(FLOATING_TYPE), "Sizeof MANTISSA_TYPE is unsifficiant to represent FLOATING_TYPE mantissa");
        assert(m_ext.size());
        if(1 == m_ext.size())
        {
            return (FLOATING_TYPE)m_ext.back();
        }
        // Rebuild mantissa with MSB bits
        if(m_ext.back() > std::numeric_limits<MANTISSA_TYPE>::max())
          {
            FLOATING_TYPE l_result = m_ext.back();
            return add_exponent<FLOATING_TYPE,MANTISSA_TYPE>(l_result, 8 * sizeof(T) * (m_ext.size() - 1));
          }
        MANTISSA_TYPE l_mantissa = m_ext.back();
        unsigned int l_index = m_ext.size() - 2;
        return complete_mantissa<FLOATING_TYPE,MANTISSA_TYPE>(l_mantissa, l_index);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename FLOATING_TYPE, typename MANTISSA_TYPE, typename std::enable_if< sizeof(T) < sizeof(FLOATING_TYPE), int>::type>
    FLOATING_TYPE
    ext_uint<T>::extract_mantissa() const
    {
        static_assert(sizeof(MANTISSA_TYPE) >= sizeof(FLOATING_TYPE), "Sizeof MANTISSA_TYPE is unsifficiant to represent FLOATING_TYPE mantissa");
        assert(m_ext.size());
        MANTISSA_TYPE l_mantissa = m_ext.back();
        size_t l_index = m_ext.size() - 2;
        constexpr const MANTISSA_TYPE l_limit = ((MANTISSA_TYPE)1) << (8 * sizeof(MANTISSA_TYPE) - 8 * sizeof(T));
        // Rebuild mantissa using complete extension words
        while(l_index < m_ext.size() && l_mantissa < l_limit)
        {
            l_mantissa = l_mantissa << 8 * sizeof(T);
            l_mantissa |= m_ext[l_index];
            --l_index;
        }
        FLOATING_TYPE l_result = l_mantissa;
        if(l_index < m_ext.size())
          {
            l_result = complete_mantissa<FLOATING_TYPE,MANTISSA_TYPE>(l_mantissa, l_index);
          }
        return l_result;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename FLOATING_TYPE, typename MANTISSA_TYPE>
    FLOATING_TYPE ext_uint<T>::complete_mantissa(MANTISSA_TYPE p_mantissa
                                                ,size_t p_index
                                                ) const
    {
      constexpr const MANTISSA_TYPE l_limit = ((MANTISSA_TYPE)1) << (8 * sizeof(MANTISSA_TYPE) - 1);
      unsigned int l_exp = 0;
      size_t l_shift = 0;
      while(!(p_mantissa & l_limit))
      {
          ++l_shift;
          p_mantissa = p_mantissa << 1;
      }

      FLOATING_TYPE l_result = p_mantissa;
      if(l_shift)
      {
          size_t l_ignored = (8 * sizeof(T) - l_shift);
          T l_shifted_part = ((T) m_ext[p_index]) >> l_ignored;
          p_mantissa |= l_shifted_part;
          l_exp += l_ignored;
          l_result = (FLOATING_TYPE)p_mantissa;
          if(p_index - 1 < m_ext.size())
          {
              l_exp += 8 * sizeof(T) * p_index;
          }
      }
      else
      {
          l_exp += 8 * sizeof(T) * (p_index + 1);
      }
      if(l_exp)
      {
          l_result = add_exponent<FLOATING_TYPE, MANTISSA_TYPE>(l_result, l_exp);
      }
      return l_result;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    template <typename FLOATING_TYPE, typename MANTISSA_TYPE>
    FLOATING_TYPE ext_uint<T>::add_exponent(FLOATING_TYPE & p_floating
                                           ,int p_add
                                           )
    {
      constexpr const size_t l_mantissa_size = std::numeric_limits<FLOATING_TYPE>::digits - 1;
      constexpr const MANTISSA_TYPE l_mantissa_mask = (((MANTISSA_TYPE)1) << l_mantissa_size) - 1;
      constexpr const size_t l_exp_size = (8 * sizeof(FLOATING_TYPE) - l_mantissa_size - 1);
      constexpr const MANTISSA_TYPE l_exponent_mask = (((MANTISSA_TYPE)1) << l_exp_size) - 1;
      // Extract mantissa un exponent
      MANTISSA_TYPE & l_floating_ref = *((MANTISSA_TYPE*) (&p_floating));
      MANTISSA_TYPE l_mantissa = l_floating_ref & l_mantissa_mask;
      unsigned int l_exponent = (l_floating_ref >> l_mantissa_size) & l_exponent_mask;

      l_exponent += p_add;

      constexpr const int l_max_exp = (1 << l_exp_size) - 1;
      if(l_max_exp <= l_exponent)
        {
          l_mantissa = 0;
        }

      // Rebuild new result
      FLOATING_TYPE l_result = 0.0;
      MANTISSA_TYPE & l_result_ref = *((MANTISSA_TYPE*) (&l_result));
      l_result_ref = l_mantissa;
      l_result_ref |= ((MANTISSA_TYPE)l_exponent) << l_mantissa_size;
      return l_result;
    }

    declare_template_specialise_type_string(typename T,ext_uint<T>,"ext_uint<" + type_string<T>::name() + ">");
    template_specialise_type_string(typename T,ext_uint<T>,"ext_uint<" + type_string<T>::name() + ">");

#ifdef QUICKY_UTILS_SELF_TEST
    /**
     * Method regrouping tests of ext_uint class
    */
    bool
    test_ext_uint();
#endif // QUICKY_UTILS_SELF_TEST
}

namespace std
{
    template <>
    template <typename T>
    struct is_integral<quicky_utils::ext_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template <>
    template <typename T>
    struct is_arithmetic<quicky_utils::ext_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template <>
    template <typename T>
    struct is_scalar<quicky_utils::ext_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template <>
    template <typename T>
    class is_signed<quicky_utils::ext_uint<T> >
    {
      public:
        static const bool value = false;
    };

    template <>
    template <typename T>
    class make_signed<quicky_utils::ext_uint<T> >
    {
      public:
        typedef quicky_utils::ext_int<typename std::make_signed<T>::type> type;
    };

    template <>
    template <typename T>
    class make_unsigned<quicky_utils::ext_uint<T> >
    {
      public:
        typedef quicky_utils::ext_uint<typename std::make_unsigned<T>::type> type;
    };
}
#endif //QUICKY_UTILS_EXT_UINT_H
// EOF
