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
#ifndef _FRACT_H_
#define _FRACT_H_

#include "type_string.h"
#include <iostream>
#include <cinttypes>
#include <cstdlib>
#include <type_traits>
#include <cassert>
#include <limits>

namespace quicky_utils
{
    template <typename T>
    class fract;

    template <typename T>
    std::ostream & operator<<(std::ostream & p_stream,
                              const fract<T> & p_fract
                             );

    template <typename T>
    fract<T> operator+(const int & p_op1,
			   const fract<T> & p_op2
			   );

    template <typename T>
    fract<T> operator-(const int & p_op1,
                       const fract<T> & p_op2
                      );

    template <typename T>
    fract<T> operator*(const int & p_op1,
			           const fract<T> & p_op2
			          );

    template <typename T>
    fract<T> operator/(const int & p_op1,
                       const fract<T> & p_op2
                      );

    template <typename T>
    bool operator==(const int & p_op1,
                    const fract<T> & p_op2
                   );

    template <typename T>
    bool operator==(const fract<T> & p_op1,
                    const int & p_op2
                   );

    template <typename T>
    bool operator!=(const int & p_op1,
                    const fract<T> & p_op2
                   );

    template <typename T>
    bool operator!=(const fract<T> & p_op1,
                    const int & p_op2
                   );

    template <typename T>
    bool operator<(const fract<T> & p_op1,
                   const int & p_op2
                  );

    template <typename T>
    bool operator<=(const fract<T> & p_op1,
                    const int & p_op2
                   );

    template <typename T>
    bool operator>(const fract<T> & p_op1,
                   const int & p_op2
                  );

    template <typename T>
    bool operator>=(const fract<T> & p_op1,
                    const int & p_op2
                   );

  template <typename T>
  class fract
  {
    friend std::ostream & operator<< <>(std::ostream & p_stream,
				     const fract<T> & p_fract
				     );
    friend fract<T> operator+<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend fract<T> operator-<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend fract<T> operator*<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend fract<T> operator/<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend bool operator==<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend bool operator==<>(const fract<T> & p_op1,
			   const int & p_op2
			   );
    friend bool operator!=<>(const int & p_op1,
			   const fract<T> & p_op2
			   );
    friend bool operator!=<>(const fract<T> & p_op1,
			   const int & p_op2
			   );
    friend bool operator< <>(const fract<T> & p_op1,
			  const int & p_op2
			  );
    friend bool operator<= <>(const fract<T> & p_op1,
			   const int & p_op2
			   );
    friend bool operator> <>(const fract<T> & p_op1,
			  const int & p_op2
			  );
    friend bool operator>= <>(const fract<T> & p_op1,
			   const int & p_op2
			   );
    public:
    typedef T t_coef;
    typedef typename std::make_signed<t_coef>::type t_coef_num;
    typedef typename std::make_unsigned<t_coef>::type t_coef_den;

    inline constexpr fract(void) noexcept;

    inline constexpr fract(const t_coef_num & p_num);

    inline constexpr fract(const t_coef_den & p_den
	                      ,std::nullptr_t
		                  );

    inline fract(const t_coef_num & p_num
                ,const t_coef_num & p_den
                );

    inline fract(const t_coef_num & p_num
                ,const t_coef_den & p_den
                );

    inline fract(const t_coef_den & p_num
                ,const t_coef_den & p_den
                );

    inline fract(const t_coef_den & p_num
                ,const t_coef_num & p_den
                );


    inline constexpr fract(const t_coef_num & p_num
                          ,const t_coef_num & p_den
                          ,std::nullptr_t
                          );

    inline constexpr fract(const t_coef_num & p_num
                          ,const t_coef_den & p_den
                          ,std::nullptr_t
                          );

    inline constexpr fract(const t_coef_den & p_num
                          ,const t_coef_num & p_den
                          ,std::nullptr_t
                          );

    inline constexpr fract(const t_coef_den & p_num
                          ,const t_coef_den & p_den
                          ,std::nullptr_t
                          );

      inline fract operator+(const fract & p_op1
			   ) const;

    inline fract operator-(const fract & p_op1
			   ) const;

    inline fract operator*(const fract & p_op1
			   ) const;

    inline fract operator/(const fract & p_op1
			   ) const;

    inline bool operator==(const fract & p_op)const;

    inline bool operator!=(const fract & p_op)const;

    inline fract operator-(void)const;
    inline fract operator+(void)const;

   /**
       Pre increment
    */
    inline fract & operator++(void);

    /**
       Post increment
     */
    inline fract operator++(int);

    /**
       Pre decrement
    */
    inline fract & operator--(void);

    /**
       Post decrement
     */
    inline fract operator--(int);

    /**
       Conversion operator
    */
    inline operator bool(void)const;

    inline fract & operator+=(const fract & p_op1);
    inline fract & operator-=(const fract & p_op1);
    inline fract & operator*=(const fract & p_op1);
    inline fract & operator/=(const fract & p_op1);

    inline bool operator<(const fract & p_op)const;
    inline bool operator<=(const fract & p_op)const;
    inline bool operator>(const fract & p_op)const;
    inline bool operator>=(const fract & p_op)const;

    inline fract& operator=(fract&& p_other) noexcept;
    inline fract& operator=(const fract& p_other);
    inline fract(const fract & p_op);

    inline float to_float(void)const;
    inline double to_double(void)const;

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PGCD of first and second number
    */
    inline static constexpr
    t_coef_den PGCD(const t_coef_num & p_a
                   ,const t_coef_num & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PGCD of first and second number
    */
    inline static constexpr
    t_coef_den PGCD(const t_coef_den & p_a
                   ,const t_coef_den & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PGCD of first and second number
    */
    inline static constexpr
    t_coef_den PGCD(const t_coef_num & p_a
                   ,const t_coef_den & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PGCD of first and second number
    */
    inline static constexpr
    t_coef_den PGCD(const t_coef_den & p_a
                   ,const t_coef_num & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @return PGCD of first and second number
    */
    inline static
    t_coef_den PGCD(const t_coef_num & p_a
                   ,const t_coef_num & p_b
	               );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @return PGCD of first and second number
    */
    inline static
    t_coef_den PGCD(const t_coef_den & p_a
                   ,const t_coef_den & p_b
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @return PGCD of first and second number
    */
    inline static
    t_coef_den PGCD(const t_coef_num & p_a
                   ,const t_coef_den & p_b
                   );

    /**
       Return PGCD computed yusing Euclide algorithm
       @param first number
       @param second number
       @return PGCD of first and second number
    */
    inline static
    t_coef_den PGCD(const t_coef_den & p_a
                   ,const t_coef_num & p_b
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @return PPCM of first and second number
    */
    inline static
    t_coef_den PPCM(const t_coef_num & p_a
                   ,const t_coef_num & p_b
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @return PPCM of first and second number
    */
    inline static
    t_coef_den PPCM(const t_coef_den & p_a
                   ,const t_coef_den & p_b
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @return PPCM of first and second number
    */
    inline static
    t_coef_den PPCM(const t_coef_num & p_a
                   ,const t_coef_den & p_b
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @return PPCM of first and second number
    */
    inline static
    t_coef_den PPCM(const t_coef_den & p_a
                   ,const t_coef_num & p_b
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PPCM of first and second number
    */
    inline static constexpr
    t_coef_den PPCM(const t_coef_num & p_a
                   ,const t_coef_num & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PPCM of first and second number
    */
    inline static constexpr
    t_coef_den PPCM(const t_coef_den & p_a
                   ,const t_coef_den & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PPCM of first and second number
    */
    inline static constexpr
    t_coef_den PPCM(const t_coef_num & p_a
                   ,const t_coef_den & p_b
                   ,std::nullptr_t
                   );

    /**
       Return PPCM using PGCD/PPCM correspondancy
       @param first number
       @param second number
       @param dummy parameter to have a different prototype of non constexpr
       implementation
       @return PPCM of first and second number
    */
    inline static constexpr
    t_coef_den PPCM(const t_coef_den & p_a
                   ,const t_coef_num & p_b
                   ,std::nullptr_t
                   );

    private:
#ifdef FRACT_DOUBLE_CHECK
    inline static bool double_equal(const double & p_op1,
				    const double & p_op2
				    );
    double m_double;
#endif // FRACT_DOUBLE_CHECK
    t_coef_num m_num;
    t_coef_den m_den;
  };

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(void) noexcept:
#ifdef FRACT_DOUBLE_CHECK
    m_double(0.0),
#endif // FRACT_DOUBLE_CHECK
    m_num(0),
    m_den((unsigned int)1)
  {
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_num & p_num):
#ifdef FRACT_DOUBLE_CHECK
    m_double(p_num),
#endif // FRACT_DOUBLE_CHECK
    m_num(p_num),
    m_den((unsigned int)1)
  {
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_den & p_den
                           ,std::nullptr_t
                           ):
#ifdef FRACT_DOUBLE_CHECK
            m_double(((double)1)/((double)p_den)),
#endif // FRACT_DOUBLE_CHECK
          m_num(1),
          m_den(p_den)
  {
  }

    //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::fract(const t_coef_num & p_num
	             ,const t_coef_num & p_den
	             )
#ifdef FRACT_DOUBLE_CHECK
    :m_double(((double)p_num)/((double)p_den))
#endif // FRACT_DOUBLE_CHECK
  {
    assert(p_den);
    t_coef_den l_pgcd = PGCD(p_num,p_den);
    m_num = abs(p_num) / ((t_coef_num)l_pgcd);

    if((p_num > (decltype(m_num))0 && p_den < (decltype(m_num))0) ||
       (p_num < (decltype(m_num))0 && p_den > (decltype(m_num))0)
       )
      {
          m_num = -m_num;
      }
    m_den = (t_coef_den)(abs(p_den)) / l_pgcd;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::fract(const t_coef_num & p_num
                 ,const t_coef_den & p_den
                 )
#ifdef FRACT_DOUBLE_CHECK
    :m_double(((double)p_num)/((double)p_den))
#endif // FRACT_DOUBLE_CHECK
  {
      assert(p_den);
      t_coef_den l_pgcd = PGCD(p_num,p_den);
      m_num = p_num / ((t_coef_num)l_pgcd);
      m_den = p_den / l_pgcd;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::fract(const t_coef_den & p_num
                 ,const t_coef_den & p_den
                 )
#ifdef FRACT_DOUBLE_CHECK
    :m_double(((double)p_num)/((double)p_den))
#endif // FRACT_DOUBLE_CHECK
  {
      assert(p_den);
      t_coef_den l_pgcd = PGCD(p_num,p_den);
      m_num = (t_coef_num)(p_num / l_pgcd);
      m_den = p_den / l_pgcd;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::fract(const t_coef_den & p_num
                 ,const t_coef_num & p_den
                 )
#ifdef FRACT_DOUBLE_CHECK
    :m_double(((double)p_num)/((double)p_den))
#endif // FRACT_DOUBLE_CHECK
  {
      assert(p_den);
      t_coef_den l_pgcd = PGCD(p_num,p_den);
      m_num = (t_coef_num)(p_num / l_pgcd) * ((t_coef_num)(p_den < ((t_coef_num)0) ? - 1: 1));
      m_den = ((t_coef_den) abs(p_den)) / l_pgcd;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_num & p_num
                           ,const t_coef_num & p_den
                           ,std::nullptr_t
                           ):
#ifdef FRACT_DOUBLE_CHECK
            m_double(((double)p_num)/((double)p_den)),
#endif // FRACT_DOUBLE_CHECK
          m_num((abs(p_num) / ((t_coef_num)PGCD(p_num,p_den,nullptr))) * (((p_num > 0 && p_den < 0) || (p_num < 0 && p_den > 0))? -1 : 1)),
          m_den((t_coef_den)(abs(p_den)) / PGCD(p_num,p_den,nullptr))
  {
      //    static_assert(p_den);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_num & p_num
                           ,const t_coef_den & p_den
                           ,std::nullptr_t
                           ):
#ifdef FRACT_DOUBLE_CHECK
            m_double(((double)p_num)/((double)p_den)),
#endif // FRACT_DOUBLE_CHECK
          m_num(p_num / ((t_coef_num)PGCD(p_num,p_den,nullptr))),
          m_den(p_den / PGCD(p_num,p_den,nullptr))
  {
      //    static_assert(p_den);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_den & p_num
                           ,const t_coef_num & p_den
                           ,std::nullptr_t
                           ):
#ifdef FRACT_DOUBLE_CHECK
            m_double(((double)p_num)/((double)p_den)),
#endif // FRACT_DOUBLE_CHECK
            m_num(((t_coef_num)(p_num / PGCD(p_num,p_den,nullptr))) * ((t_coef_num )(p_den < 0 ? -1 : 1))),
            m_den((t_coef_den)(abs(p_den)) / PGCD(p_num,p_den,nullptr))
    {
        //    static_assert(p_den);
    }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr fract<T>::fract(const t_coef_den & p_num
                           ,const t_coef_den & p_den
                           ,std::nullptr_t
                           ):
#ifdef FRACT_DOUBLE_CHECK
            m_double(((double)p_num)/((double)p_den)),
#endif // FRACT_DOUBLE_CHECK
          m_num(((t_coef_num)(p_num / PGCD(p_num,p_den,nullptr)))),
          m_den(p_den / PGCD(p_num,p_den,nullptr))
  {
      //    static_assert(p_den);
  }

    //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator+(const fract & p_op
			 ) const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			 p_op.m_den
			 );
    t_coef_num l_num = (t_coef_num)(l_ppcm / this->m_den) * this->m_num + (t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num;
    fract l_result = fract(l_num, l_ppcm);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(l_result.to_double(), (this->to_double() + p_op.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator-(const fract & p_op
			 ) const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			 p_op.m_den
			 );
    t_coef_num l_num = (t_coef_num)(l_ppcm / this->m_den) * this->m_num - (t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num;
    fract l_result = fract(l_num, l_ppcm);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(l_result.to_double(), (this->to_double() - p_op.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator*(const fract & p_op
			 ) const 
  {
    fract l_result = fract(m_num * p_op.m_num,m_den * p_op.m_den);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(l_result.to_double(), (this->to_double() * p_op.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator/(const fract & p_op
			 )const
  {
    fract l_result = fract(m_num * (t_coef_num)p_op.m_den,((t_coef_num)(m_den)) * p_op.m_num);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(l_result.to_double(), (this->to_double() / p_op.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator==(const fract & p_op)const
  {
    bool l_result = m_num == p_op.m_num && m_den == p_op.m_den;
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result == double_equal(this->to_double(), p_op.to_double()));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator!=(const fract & p_op)const
  {
    bool l_result = m_num != p_op.m_num || m_den != p_op.m_den;
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result != double_equal(this->to_double(), p_op.to_double()));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator++(void)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this + fract((typename fract<T>::t_coef_num)1);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before + 1)));
#endif // FRACT_DOUBLE_CHECK
    return *this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator++(int)
  {
    fract tmp(*this); 
    *this = *this + fract((typename fract<T>::t_coef_num)1);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (tmp.to_double() + 1)));
#endif // FRACT_DOUBLE_CHECK
    return tmp;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator--(void)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this - fract((typename fract<T>::t_coef_num)1);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before - 1)));
#endif // FRACT_DOUBLE_CHECK
    return *this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator--(int)
  {
    fract tmp(*this); 
    *this = *this - fract((typename fract<T>::t_coef_num)1);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (tmp.to_double() - 1)));
#endif // FRACT_DOUBLE_CHECK
    return tmp;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator-(void)const
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    fract l_result = fract(-m_num, m_den);
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), -l_before));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> fract<T>::operator+(void)const
  {
    return fract(m_num, m_den);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::operator bool(void)const
  {
    return (bool)m_num;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator+=(const fract & p_op1)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this + p_op1;
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before + p_op1.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return * this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator-=(const fract & p_op1)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this - p_op1;
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before - p_op1.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return * this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator*=(const fract & p_op1)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this * p_op1;
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before * p_op1.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return * this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T> & fract<T>::operator/=(const fract & p_op1)
  {
#ifdef FRACT_DOUBLE_CHECK
    double l_before = this->to_double();
#endif // FRACT_DOUBLE_CHECK
    *this = *this / p_op1;
#ifdef FRACT_DOUBLE_CHECK
    assert(double_equal(this->to_double(), (l_before / p_op1.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return * this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator<(const fract & p_op)const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			     p_op.m_den
			     );
    return ((t_coef_num)(l_ppcm / this->m_den) * this->m_num) < ((t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator<=(const fract & p_op)const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			     p_op.m_den
			     );
    return ((t_coef_num)(l_ppcm / this->m_den) * this->m_num) <= ((t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator>(const fract & p_op)const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			     p_op.m_den
			     );
    return ((t_coef_num)(l_ppcm / this->m_den) * this->m_num) > ((t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  bool fract<T>::operator>=(const fract & p_op)const
  {
    t_coef_den l_ppcm = PPCM(this->m_den,
			     p_op.m_den
			     );
    return ((t_coef_num)(l_ppcm / this->m_den) * this->m_num) >= ((t_coef_num)(l_ppcm / p_op.m_den) * p_op.m_num);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>::fract(const fract & p_op):
#ifdef FRACT_DOUBLE_CHECK
    m_double(p_op.m_double),
#endif // FRACT_DOUBLE_CHECK
    m_num(p_op.m_num),
    m_den(p_op.m_den)
  {
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>& fract<T>::operator=(fract&& p_other) noexcept
  {
	// no-op on self-move-assignment
    if(this != &p_other)
      {
	std::swap(m_num,p_other.m_num);
	std::swap(m_den,p_other.m_den);
#ifdef FRACT_DOUBLE_CHECK
	std::swap(m_double,p_other.m_double);
#endif // FRACT_DOUBLE_CHECK
      }
    return *this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  fract<T>& fract<T>::operator=(const fract& p_other)
  {
    this->m_num = p_other.m_num;
    this->m_den = p_other.m_den;
#ifdef FRACT_DOUBLE_CHECK
    this->m_double = p_other.m_double;
#endif // FRACT_DOUBLE_CHECK
    return *this;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  float fract<T>::to_float(void)const
  {
    return ((float)m_num)/((float)m_den);

  }

  //----------------------------------------------------------------------------
  template <typename T>
  double fract<T>::to_double(void)const
  {
    return ((double)m_num)/((double)m_den);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_den & p_a
                                              ,const t_coef_den & p_b
                                              )
  {
      assert(p_b);
      t_coef_den l_a = p_a;
      t_coef_den l_b = p_b;
      t_coef_den l_r;
      while((l_r = (l_a % l_b)))
      {
          l_a = l_b;
          l_b = l_r;
      }
      return l_b;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_num & p_a
                                              ,const t_coef_num & p_b
                                              )
  {
      return PGCD((t_coef_den) abs(p_a),(t_coef_den) abs(p_b));
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_num & p_a
                                              ,const t_coef_den & p_b
                                              )
  {
      return PGCD((t_coef_den) abs(p_a), p_b);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_den & p_a
                                              ,const t_coef_num & p_b
                                              )
  {
      return PGCD(p_a, (t_coef_den) abs(p_b));
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_num & p_a
                                                        ,const t_coef_num & p_b
					                                    ,std::nullptr_t
					                                    )
  {
    return ((p_a % p_b) ? PGCD((fract<T>::t_coef_den)abs(p_b),(fract<T>::t_coef_den)abs(p_a) % (fract<T>::t_coef_den)abs(p_b),nullptr) : (fract<T>::t_coef_den)abs(p_b));
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_den & p_a
                                                        ,const t_coef_den & p_b
                                                        ,std::nullptr_t
                                                        )
  {
      return ((p_a % p_b) ? PGCD(p_b,p_a % p_b,nullptr) : p_b);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_den & p_a
                                                        ,const t_coef_num & p_b
                                                        ,std::nullptr_t
                                                        )
  {
      return ((p_a % p_b) ? PGCD((fract<T>::t_coef_den)abs(p_b),p_a % (fract<T>::t_coef_den)abs(p_b),nullptr) : (fract<T>::t_coef_den)abs(p_b));
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PGCD(const t_coef_num & p_a
                                                        ,const t_coef_den & p_b
                                                        ,std::nullptr_t
                                                        )
  {
      return ((p_a % p_b) ? PGCD(p_b,abs(p_a) % p_b,nullptr) : p_b);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_den & p_a,
                                               const t_coef_den & p_b
                                              )
  {
    return p_a *p_b / PGCD(p_a, p_b);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_num & p_a,
                                               const t_coef_num & p_b
                                              )
  {
      return PPCM((t_coef_den )abs(p_a), (t_coef_den)abs(p_b));
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_num & p_a,
                                               const t_coef_den & p_b
                                              )
  {
      return PPCM((t_coef_den )abs(p_a), p_b);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_den & p_a,
                                               const t_coef_num & p_b
                                              )
  {
      return PPCM(p_a, (t_coef_den)abs(p_b));
  }


  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_den & p_a,
                                                         const t_coef_den & p_b,
                                                         std::nullptr_t
                                                        )
  {
      return p_a * p_b / PGCD(p_a,p_b,nullptr);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_num & p_a,
                                                         const t_coef_num & p_b,
                                                         std::nullptr_t
                                                        )
  {
    return ((t_coef_den)abs(p_a)) * ((t_coef_den)abs(p_b)) / PGCD(((t_coef_den )abs(p_a)),((t_coef_den )abs(p_b)),nullptr);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_den & p_a,
                                                         const t_coef_num & p_b,
                                                         std::nullptr_t
                                                        )
  {
      return p_a * ((t_coef_den)abs(p_b)) / PGCD(p_a,((t_coef_den )abs(p_b)),nullptr);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  constexpr typename fract<T>::t_coef_den fract<T>::PPCM(const t_coef_num & p_a,
                                                         const t_coef_den & p_b,
                                                         std::nullptr_t
                                                        )
  {
      return ((t_coef_den)abs(p_a)) * p_b / PGCD(((t_coef_den )abs(p_a)),p_b,nullptr);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline std::ostream & operator<<(std::ostream & p_stream,
				   const fract<T> & p_fract
				   )
  {
    p_stream << p_fract.m_num;
    if(p_fract.m_num && ((decltype(p_fract.m_den))(unsigned int)1) != p_fract.m_den)
      {
	p_stream << "/" << p_fract.m_den;
      }
    return p_stream;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline fract<T> operator+(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    fract<T> l_result = fract<T>((typename fract<T>::t_coef_num)p_op1) + p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(fract<T>::double_equal(l_result.to_double(), (((double)p_op1) + p_op2.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline fract<T> operator-(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    fract<T> l_result = fract<T>(p_op1) - p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(fract<T>::double_equal(l_result.to_double(), (((double)p_op1) - p_op2.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline fract<T> operator*(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    fract<T> l_result = fract<T>(p_op1) * p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(fract<T>::double_equal(l_result.to_double(), (((double)p_op1) * p_op2.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline fract<T> operator/(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    fract<T> l_result = fract<T>(p_op1) / p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(fract<T>::double_equal(l_result.to_double(), (((double)p_op1) / p_op2.to_double())));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator==(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    bool l_result = fract<T>(p_op1) == p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result == fract<T>::double_equal((double)p_op1,p_op2));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator==(const fract<T> & p_op1,
			 const int & p_op2
			 )
  {
    bool l_result = p_op1 == fract<T>(p_op2);
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result == fract<T>::double_equal(p_op1,(double)p_op2));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator!=(const int & p_op1,
			 const fract<T> & p_op2
			 )
  {
    bool l_result = fract<T>((typename fract<T>::t_coef_num)p_op1) != p_op2;
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result != fract<T>::double_equal((double)p_op1,p_op2.to_double()));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator!=(const fract<T> & p_op1,
			 const int & p_op2
			 )
  {
    bool l_result = p_op1 != fract<T>((typename fract<T>::t_coef_num)p_op2);
#ifdef FRACT_DOUBLE_CHECK
    assert(l_result != fract<T>::double_equal(p_op1.to_double(),(double)p_op2));
#endif // FRACT_DOUBLE_CHECK
    return l_result;
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator<(const fract<T> & p_op1,
			const int & p_op2
			)
  {
    return p_op1 < fract<T>((typename fract<T>::t_coef_num)p_op2);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator<=(const fract<T> & p_op1,
			const int & p_op2
			)
  {
    return p_op1 <= fract<T>((typename fract<T>::t_coef_num)p_op2);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator>(const fract<T> & p_op1,
			const int & p_op2
			)
  {
    return p_op1 > fract<T>((typename fract<T>::t_coef_num)p_op2);
  }

  //----------------------------------------------------------------------------
  template <typename T>
  inline bool operator>=(const fract<T> & p_op1,
			const int & p_op2
			)
  {
    return p_op1 >= fract<T>((typename fract<T>::t_coef_num)p_op2);
  }

#ifdef FRACT_DOUBLE_CHECK
  bool fract<T>::double_equal(const double & p_op1,
			   const double & p_op2
			   )
  {
    double l_epsilon = 0.000000000000001;
    return fabs(fabs(p_op1) - fabs(p_op2)) < l_epsilon;
  }
#endif // FRACT_DOUBLE_CHECK
  declare_template_specialise_type_string(typename T,fract<T>,"fract<" + type_string<T>::name() + ">");
  template_specialise_type_string(typename T,fract<T>,"fract<" + type_string<T>::name() + ">");

}

#include <limits>

namespace std
{
  template<>
  template <typename T>
    class is_signed<quicky_utils::fract<T>>
    {
    public:
      static const bool value = true;
    };

  template<>
  template <typename T>
    class numeric_limits<quicky_utils::fract<T>>
    {
    public:
      static constexpr bool is_specialized = true;
      static constexpr quicky_utils::fract<T> min() noexcept
	{
	  return quicky_utils::fract<T>(std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::min());
	}
      static constexpr quicky_utils::fract<T> max() noexcept
	{
	  return quicky_utils::fract<T>(std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::max());
	}
      static constexpr quicky_utils::fract<T> lowest() noexcept
	{
	  return quicky_utils::fract<T>(std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::lowest());
	}
      static constexpr int digits = std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::digits;
      static constexpr int digits10 = std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::digits10;
      static constexpr int max_digits10 = std::numeric_limits<typename quicky_utils::fract<T>::t_coef_num>::max_digits10;
      static constexpr bool is_signed = true;
      static constexpr bool is_integer = false;
      static constexpr bool is_exact = true;
      static constexpr int radix = 2;
      static constexpr quicky_utils::fract<T> epsilon() noexcept
	{
	  return quicky_utils::fract<T>(std::numeric_limits<typename quicky_utils::fract<T>::t_coef_den>::max(),
				     nullptr
				     );
	}
      static constexpr quicky_utils::fract<T> round_error() noexcept
	{
	  return quicky_utils::fract<T>(std::numeric_limits<typename quicky_utils::fract<T>::t_coef_den>::max(),
				     nullptr
				     );
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
      static constexpr bool is_modulo = true;
      static constexpr bool traps = false;
      static constexpr bool tinyness_before = false;
      static constexpr float_round_style round_style = round_toward_zero;
    };
}

#endif // _FRACT_H_
// EOF
