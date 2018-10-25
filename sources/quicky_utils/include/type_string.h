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
#ifndef TYPE_STRING_H
#define TYPE_STRING_H

#include "quicky_exception.h"
#include <string>
#include <cinttypes>
#include <memory>

namespace quicky_utils
{
    /**
     * Class providing string representation of type name
     * A specialisation should be done for each type
     * @tparam T type to provide name as string
     */
    template <typename T>
    class type_string
    {
      public:
        type_string() = delete;
        type_string(const type_string & ) = delete;
        type_string(const type_string && ) = delete;

        inline static constexpr const std::string & name();
      private:
        static const std::string m_name;
    };

    template <typename T>
    constexpr const std::string & type_string<T>::name()
    {
        return m_name;
    }

    template <typename T>
    const std::string type_string<T>::m_name = "Unknown type";

#define declare_template_specialise_type_string(template_arg,type,type_name)      \
    template <>                                                                   \
    template <template_arg>                                                       \
    class type_string<type>                                                       \
    {                                                                             \
      public:                                                                     \
        type_string() = delete;                                                   \
        type_string(const type_string & ) = delete;                               \
        type_string(const type_string && ) = delete;                              \
                                                                                  \
        inline static const std::string & name();                                 \
      private:                                                                    \
        static std::unique_ptr<std::string> m_name;                               \
    }

#define template_specialise_type_string(template_arg,type,type_name)           \
    template <template_arg>                                                    \
    const std::string & type_string<type>::name()                              \
    {                                                                          \
        if(!m_name)                                                            \
        {                                                                      \
            m_name = std::unique_ptr<std::string>(new std::string(type_name)); \
        }                                                                      \
       return *m_name;                                                         \
    }                                                                          \
                                                                               \
    template <template_arg>                                                    \
    std::unique_ptr<std::string> type_string<type>::m_name = nullptr

#define declare_specialise_type_string(type,type_name)            \
    template <> class type_string<type> ;                         \
    template <>                                                   \
    class type_string<type>                                       \
    {                                                             \
      public:                                                     \
        type_string() = delete;                                   \
        type_string(const type_string & ) = delete;               \
        type_string(const type_string && ) = delete;              \
                                                                  \
        static const std::string & name();                        \
      private:                                                    \
        static std::unique_ptr<std::string>  m_name;              \
    }

#define specialise_type_string(type,type_name)                                 \
                                                                               \
    const std::string & type_string<type>::name()                              \
    {                                                                          \
        if(!m_name)                                                            \
        {                                                                      \
            m_name = std::unique_ptr<std::string>(new std::string(type_name)); \
        }                                                                      \
        return *m_name;                                                        \
    }                                                                          \
                                                                               \
    std::unique_ptr<std::string> type_string<type>::m_name = nullptr

#define simple_type_string(type) specialise_type_string(type,#type)
#define prefix_type_string(prefix,type) specialise_type_string(prefix::type,#type)
#define declare_simple_type_string(type) declare_specialise_type_string(type,#type)
#define declare_prefix_type_string(prefix,type) declare_specialise_type_string(prefix::type,#type)

    declare_simple_type_string(uint8_t);
    declare_simple_type_string(uint16_t);
    declare_simple_type_string(uint32_t);
    declare_simple_type_string(uint64_t);

    declare_simple_type_string(int8_t);
    declare_simple_type_string(int16_t);
    declare_simple_type_string(int32_t);
    declare_simple_type_string(int64_t);

    declare_simple_type_string(char);
    declare_simple_type_string(float);
    declare_simple_type_string(double);
    declare_simple_type_string(std::string);

#ifdef QUICKY_UTILS_SELF_TEST
    bool test_type_string();
#endif // QUICKY_UTILS_SELF_TEST

}
#endif //TYPE_STRING_H
// EOF

