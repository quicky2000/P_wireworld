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

#ifndef QUICKY_UTILS_SAFE_UINT_H
#define QUICKY_UTILS_SAFE_UINT_H

#include "safe_type_exception.h"
#include "type_string.h"
#include <limits>
#include <iostream>
#include <type_traits>

namespace quicky_utils
{
    template <typename T>
    class safe_uint;

    template <typename T>
    class safe_int;

    template <typename T>
    std::ostream & operator<<(std::ostream & , const safe_uint<T> & );

    template <typename T>
    bool operator==(const T & p_op1,
                    const safe_uint<T> & p_safe_uint
                   );

    /**
     * Class redefining basic built-in int types but raising exception in case of overflow/underflow etc
     * @tparam T build-in types made safe
     */
    template <typename T>
    class safe_uint
    {
      public:
        safe_uint(void);
        safe_uint(T p_value);

        safe_uint(const safe_int<typename std::make_signed<T>::type> & p_value);

        explicit operator bool() const;
        explicit operator float() const;
        explicit operator double() const;

        bool
        operator==(const safe_uint & p_operand) const;

        bool
        operator!=(const safe_uint & p_op) const;

        bool
        operator<(const safe_uint & p_op) const;

        bool
        operator>(const safe_uint & p_op) const;

        bool
        operator<=(const safe_uint & p_op) const;

        bool
        operator>=(const safe_uint & p_op) const;

        safe_uint
        operator+(const safe_uint & p_op) const;

        safe_uint
        operator-(const safe_uint & p_op) const;

        safe_uint
        operator*(const safe_uint & p_op) const;

        safe_uint
        operator/(const safe_uint & p_op) const;

        safe_uint
        operator%(const safe_uint & p_op) const;

        safe_uint
        operator-(void)const;

        safe_uint
        operator+(void)const;

        safe_uint
        operator+=(const safe_uint & p_op);

        safe_uint
        operator-=(const safe_uint & p_op);

        safe_uint
        operator*=(const safe_uint & p_op);

        safe_uint
        operator/=(const safe_uint & p_op);

        const T & get_value(void)const;

        friend std::ostream &
        operator<< <>(std::ostream & os,
                   const safe_uint<T> & safe_uint
                  );

        typedef T base_type;

        /**
         * Method performing addition, returning the result and setting a
         * boolean to true in case of overflow
         * @param p_op1 first operand
         * @param p_op2 second operand
         * @param p_overflow true in case of overflow
         * @return result of traditionnal addition
         */
        static
        T
        check_add(const T & p_op1,
                  const T & p_op2,
                  bool & p_overflow
                 );

        /**
         * Method performing substraction, returning the result and setting a
         * boolean to true in case of underflow
         * @param p_op1 first operand
         * @param p_op2 second operand
         * @param p_overflow true in case of underflow
         * @return  result of traditionnal substraction
         */
        static
        T
        check_substr(const T & p_op1,
                     const T & p_op2,
                     bool & p_overflow
                    );

      private:
        static_assert(std::is_unsigned<T>::value,"Check that type is unsigned");
        T m_value;
    };

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::operator bool() const
    {
        return m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::operator float() const
    {
        return (float)m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::operator double() const
    {
        return (double)m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::safe_uint(void):
            m_value(0)
    {}

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::safe_uint(T m_value):
            m_value(m_value)
    {}

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>::safe_uint(const safe_int<typename std::make_signed<T>::type> & p_value):
    m_value((T)p_value.get_value())
    {
        if(p_value.get_value() <0)
        {
            throw safe_type_exception("Convert negative int to uint",
                                      __LINE__,
                                      __FILE__
                                     );
        }
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator!=(const safe_uint & p_op) const
    {
        return m_value != p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator==(const safe_uint & p_op) const
    {
        return m_value == p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator<(const safe_uint & p_op) const
    {
        return m_value < p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator>(const safe_uint & p_op) const
    {
        return m_value > p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator<=(const safe_uint & p_op) const
    {
        return m_value <= p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool
    safe_uint<T>::operator>=(const safe_uint & p_op) const
    {
        return m_value >= p_op.m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator+(const safe_uint & p_op) const
    {
        bool l_overflow;
        T l_sum = check_add(m_value, p_op.m_value,l_overflow);
        if (l_overflow)
        {
            throw safe_type_exception("Addition overflow",
                                      __LINE__,
                                      __FILE__
                                     );
        }
        return safe_uint(l_sum);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator-(const safe_uint & p_op) const
    {
        bool l_underflow;
        T l_result = check_substr(m_value, p_op.m_value, l_underflow);
        if (l_underflow)
        {
            throw safe_type_exception("Substraction underflow",
                                      __LINE__,
                                      __FILE__
                                     );
        }
        return safe_uint(l_result);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator*(const safe_uint & p_op) const
    {
        T l_result = m_value * p_op.m_value;
        if (m_value && (std::numeric_limits<T>::max() / m_value) < p_op.m_value)
        {
            throw safe_type_exception("Multiplication overflow",
                                      __LINE__,
                                      __FILE__
                                     );
        }
        return safe_uint(l_result);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator/(const safe_uint & p_op) const
    {
        T l_result = m_value / p_op.m_value;
        return safe_uint(l_result);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator%(const safe_uint & p_op) const
    {
        T l_result = m_value % p_op.m_value;
        return safe_uint(l_result);
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator-(void)const
    {
        throw safe_type_exception("Illegal safe_uint operator-",
                                  __LINE__,
                                  __FILE__
                                 );
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator+(void)const
    {
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator+=(const safe_uint & p_op)
    {
        *this = *this + p_op;
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator-=(const safe_uint & p_op)
    {
        *this = *this - p_op;
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator*=(const safe_uint & p_op)
    {
        *this = *this * p_op;
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    safe_uint<T>
    safe_uint<T>::operator/=(const safe_uint & p_op)
    {
        *this = *this / p_op;
        return *this;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    const T &
    safe_uint<T>::get_value(void) const
    {
        return m_value;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    std::ostream &
    operator<<(std::ostream & p_stream,
               const safe_uint<T> & p_safe_uint
              )
    {
        p_stream << p_safe_uint.m_value;
        return p_stream;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    T
    safe_uint<T>::check_add(const T & p_op1,
                            const T & p_op2,
                            bool & p_overflow
                           )
    {
        T l_sum = p_op1 + p_op2;
        p_overflow = l_sum < p_op1 || l_sum < p_op2;
        return l_sum;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    T
    safe_uint<T>::check_substr(const T & p_op1,
                               const T & p_op2,
                               bool & p_overflow
                              )
    {
        T l_result = p_op1 - p_op2;
        p_overflow = l_result > p_op1;
        return l_result;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    bool operator==(const T & p_op1,
                    const safe_uint<T> & p_safe_uint
                   )
    {
        return safe_uint<T>(p_op1) == p_safe_uint;
    }

    declare_template_specialise_type_string(typename T,safe_uint<T>,"safe_uint<" + type_string<T>::name() + ">");
    template_specialise_type_string(typename T,safe_uint<T>,"safe_uint<" + type_string<T>::name() + ">");
}

namespace std
{
    template<>
    template<typename T>
    struct is_integral<quicky_utils::safe_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template<>
    template<typename T>
    struct is_arithmetic<quicky_utils::safe_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template<>
    template<typename T>
    struct is_scalar<quicky_utils::safe_uint<T>>
    {
      public:
        static constexpr bool value = true;
    };

    template<>
    template <typename T>
    class is_signed<quicky_utils::safe_uint<T> >
    {
      public:
        static const bool value = false;
    };

    template<>
    template <typename T>
    class make_signed<quicky_utils::safe_uint<T> >
    {
      public:
        typedef quicky_utils::safe_int<typename std::make_signed<T>::type> type;
    };

    template<>
    template <typename T>
    class make_unsigned<quicky_utils::safe_uint<T> >
    {
      public:
        typedef quicky_utils::safe_uint<typename std::make_unsigned<T>::type> type;
    };

    template<>
    template <typename T>
    class numeric_limits<quicky_utils::safe_uint<T> >
    {
      public:
        static constexpr bool is_specialized = true;
        static constexpr quicky_utils::safe_uint<T> min() noexcept
        {
            return quicky_utils::safe_uint<T>(std::numeric_limits<T>::min());
        }
        static constexpr quicky_utils::safe_uint<T> max() noexcept
        {
            return quicky_utils::safe_uint<T>(std::numeric_limits<T>::max());
        }
        static constexpr quicky_utils::safe_uint<T> lowest() noexcept
        {
            return quicky_utils::safe_uint<T>(std::numeric_limits<T>::lowest());
        }
        static constexpr int digits = std::numeric_limits<T>::digits;
        static constexpr int digits10 = std::numeric_limits<T>::digits10;
        static constexpr int max_digits10 = std::numeric_limits<T>::max_digits10;
        static constexpr bool is_signed = false;
        static constexpr bool is_integer = true;
        static constexpr bool is_exact = true;
        static constexpr int radix = 2;
        static constexpr quicky_utils::safe_uint<T> epsilon() noexcept
        {
            return std::numeric_limits<T>::epsilon();
        }
        static constexpr quicky_utils::safe_uint<T> round_error() noexcept
        {
            return std::numeric_limits<T>::round_error();
        }
        static constexpr int min_exponent = 0; // No sense
        static constexpr int min_exponent10 = 0; // No sense
        static constexpr int max_exponent = 0; // No sense
        static constexpr int max_exponent10 = 0; // No sense
        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss = false;
        static constexpr bool infinity() noexcept { return 0; } // No sense
        static constexpr bool quiet_NaN() noexcept { return 0; } // No sense
        static constexpr bool signaling_NaN() noexcept { return 0; } // No sense
        static constexpr bool denorm_min() noexcept { return 0; } // No sense
        static constexpr bool is_iec559 = false;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;
        static constexpr bool traps = true;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_toward_zero;
    };
}
#endif //QUICKY_UTILS_SAFE_UINT_H
//EOF
