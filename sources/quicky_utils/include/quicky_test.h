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

#ifndef QUICKY_UTILS_QUICKY_TEST_H
#define QUICKY_UTILS_QUICKY_TEST_H

#include "quicky_exception.h"
#include <string>
#include <sstream>
#include <iostream>
#include <functional>

namespace quicky_utils
{
    /**
     * Some utilities to test software
     */
    class quicky_test
    {
      public:
        typedef enum class test_verbosity {QUIET, FAILED_ONLY, VERBOSE} test_verbosity_t;

        /**
         * Generate automatic message with file info
         * @param p_file_name file name
         * @param p_line line index
         * @return generated message
         */
        static inline std::string auto_message(const std::string & p_file_name,
                                               const unsigned int & p_line
                                              );

        /**
         * Define stream to use by default
         * @param p_stream default output stream
         */
        static inline void set_ostream(std::ostream & p_stream);

        /**
         * Return stream used by default
         * @return default output stream
         */
        static inline std::ostream & get_ostream();

        /**
         * Define test verbosity
         * @param p_verbosity verbosity level
         */
        static inline void set_verbosity(const test_verbosity_t & p_verbosity);

        /**
         * Get test verbosity
         * @return verbosity level
         */
        static inline test_verbosity_t get_verbosity();

        /**
         * Provide string representation of verbosity
         * @param p_verbosity
         * @return string representation of verbosity
         */
        static std::string to_string(const test_verbosity_t & p_verbosity);

        /**
         * Check expected value without displaying message
         * @tparam T type of value to check
         * @param p_value value to check
         * @param p_expected expected value
         * @return true in case of success
         */
        template<typename T>
        static inline bool
        check_expected_quiet(const T & p_value,
                             const T & p_expected
                            );

        /**
         * Check expected value and display message
         * @tparam T type of value to check
         * @param p_value value t check
         * @param p_expected expected value
         * @param p_message message to display
         * @return true in case of success
         */
        template<typename T>
        static inline bool
        check_expected(const T & p_value,
                       const T & p_expected,
                       const std::string & p_message = ""
                      );

        /**
         * Check if code raised an exception without displaying message
         * @tparam EXCEPTION type of exception to be raised or not
         * @param p_function code to execute
         * @param p_exception_expected true if exception is expected
         * @return true in case of success
         */
        template<class EXCEPTION>
        static inline bool
        check_exception_quiet(const std::function<void(void)> & p_function,
                              bool p_exception_expected = true
                             );

        /**
         *
         * @tparam EXCEPTION type of exception to be raised or not
         * @param p_function code to execute
         * @param p_exception_expected true if exception is expected
         * @param p_message message to display
         * @return true in case of success
         */
        template<class EXCEPTION>
        static inline bool
        check_exception(const std::function<void(void)> & p_function,
                        bool p_exception_expected,
                        const std::string & p_message = ""
                       );

        /**
         * Check result of ostream operator
         * @tparam T Type of object applied to ostream operator
         * @param p_object object applied to ostream operator
         * @param p_expected expected displayed string
         * @return true if displayed string is the expected one
         */
        template<typename T>
        static inline bool
        check_ostream_operator_quiet(const T & p_object,
                                     const std::string & p_expected
                                    );

        /**
         * Check result of ostream operator
         * @tparam T Type of object applied to ostream operator
         * @param p_object object applied to ostream operator
         * @param p_expected expected displayed string
         * @param p_message optionnal message to display
         * @return true if displayed string is the expected one
         */
        template<typename T>
        static inline bool
        check_ostream_operator(const T & p_object,
                               const std::string & p_expected,
                               const std::string & p_message = ""
                              );
      private:
        /**
         * Check provided value vs expected value and return a boolean
         * indicating if comparison was OK or not
         * @tparam T Type of values to compare
         * @param p_value Value to check
         * @param p_expected Expected value
         * @param p_message Additional message to print before check result
         * @param p_stream Output stream where to send the message
         * @param p_quiet if false a message is send to output stream
         * @return true in case of equality false in contrary case
         */
        template<typename T>
        static inline bool
        check_expected(const T & p_value,
                       const T & p_expected,
                       const std::string & p_message,
                       std::ostream & p_stream,
                       test_verbosity_t p_quiet
                      );

        /**
         * Check if a code raise an exception and return a boolean indicating
         * if code behaviour is the expected one
         * @tparam EXCEPTION exception type
         * @param p_function code to execute
         * @param p_exception_expected indicate if an exception is expected
         * @param p_message optionnal message to display
         * @param p_ostream output stream where diagnostic message is sent
         * @param p_quiet if false a message is send to output stream
         * @return true if expected exception was raised
         */
        template<class EXCEPTION>
        static inline bool
        check_exception(const std::function<void(void)> & p_function,
                        bool p_exception_expected,
                        const std::string & p_message,
                        std::ostream & p_ostream,
                        test_verbosity_t p_quiet
                       );

        /**
         * Check result of ostream operator
         * @tparam T Type of object applied to ostream operator
         * @param p_object object applied to ostream operator
         * @param p_expected expected displayed string
         * @param p_message optionnal message to display
         * @param p_ostream output stream where diagnostic message is sent
         * @param p_quiet if false a message is send to output stream
         * @return true if displayed string is the expected one
         */
        template<typename T>
        static inline bool
        check_ostream_operator(const T & p_object,
                               const std::string & p_expected,
                               const std::string & p_message,
                               std::ostream & p_ostream,
                               test_verbosity_t p_quiet
                              );

        inline quicky_test(std::ostream & p_ostream);

        std::ostream * m_default_ostream;
        static quicky_test m_unique_instance;
        static test_verbosity_t m_verbosity;
    };

    //-------------------------------------------------------------------------
    inline std::ostream & operator<<(std::ostream & p_stream, const quicky_test::test_verbosity_t & p_verbosity)
    {
        p_stream << quicky_test::to_string(p_verbosity);
        return p_stream;
    }

    //-------------------------------------------------------------------------
    template<typename T>
    bool
    quicky_test::check_expected(const T & p_value,
                                const T & p_expected,
                                const std::string & p_message,
                                std::ostream & p_stream,
                                test_verbosity_t p_quiet
                               )
    {
        bool l_result = p_value == p_expected;
        if(test_verbosity_t::VERBOSE == p_quiet || ( test_verbosity_t::FAILED_ONLY == p_quiet && !l_result))
        {
            if(!p_message.empty())
            {
                p_stream << p_message << ": ";
            }
            p_stream << "Expected value : " << p_expected << "\tValue : " << p_value << " => " << (l_result ? "PASSED" : "FAILED") << std::endl;
        }
        return l_result;
    }

    //-------------------------------------------------------------------------
    template<>
    inline bool
    quicky_test::check_expected(const std::string & p_value,
                                const std::string & p_expected,
                                const std::string & p_message,
                                std::ostream & p_stream,
                                test_verbosity_t p_quiet
                               )
    {
        bool l_result = p_value == p_expected;
        if(test_verbosity_t::VERBOSE == p_quiet || ( test_verbosity_t::FAILED_ONLY == p_quiet && !l_result))
        {
            if(!p_message.empty())
            {
                p_stream << p_message << ": ";
            }
            p_stream << "Expected value : \"" << p_expected << "\"\tValue : \"" << p_value << "\" => " << (l_result ? "PASSED" : "FAILED") << std::endl;
        }
        return l_result;
    }

    //-------------------------------------------------------------------------
    template <class EXCEPTION>
    bool
    quicky_test::check_exception(const std::function<void(void)> & p_function,
                                 bool p_exception_expected,
                                 const std::string & p_message,
                                 std::ostream & p_ostream,
                                 test_verbosity_t p_quiet
                                )
    {
        bool l_exception_raised = false;
        try
        {
            p_function();
        }
        catch(EXCEPTION & e)
        {
            l_exception_raised = true;
        }
        bool l_result = p_exception_expected == l_exception_raised;
        if(test_verbosity_t::VERBOSE == p_quiet || ( test_verbosity_t::FAILED_ONLY == p_quiet && !l_result))
        {
            if(!p_message.empty())
            {
                p_ostream << p_message << ": ";
            }
            p_ostream << "Exception expected : " << (p_exception_expected ? "YES" : "NO") << "\tException raised : " << (l_exception_raised ? "YES" : "NO") << " => " << (l_result ? "PASSED" : "FAILED") << std::endl;
        }
        return l_result;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    quicky_test::check_ostream_operator(const T & p_object,
                                        const std::string & p_expected,
                                        const std::string & p_message,
                                        std::ostream & p_ostream,
                                        test_verbosity_t p_quiet
                                       )
    {
        std::stringstream l_stream;
        l_stream << p_object;
        std::string l_string = l_stream.str();
        return check_expected(l_string, p_expected, p_message, p_ostream, p_quiet);
    }

    //-------------------------------------------------------------------------
    std::string
    quicky_test::auto_message(const std::string & p_file_name,
                              const unsigned int & p_line
                             )
    {
        return p_file_name + ":" + std::to_string(p_line);
    }

    //-------------------------------------------------------------------------
    quicky_test::quicky_test(std::ostream & p_ostream):
    m_default_ostream(&p_ostream)
    {

    }

    //-------------------------------------------------------------------------
    void
    quicky_test::set_ostream(std::ostream & p_stream)
    {
        m_unique_instance.m_default_ostream = &p_stream;
    }

    //-------------------------------------------------------------------------
    std::ostream &
    quicky_test::get_ostream()
    {
        return *m_unique_instance.m_default_ostream;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    quicky_test::check_expected_quiet(const T & p_value,
                                      const T & p_expected
                                     )
    {
        return check_expected<T>(p_value,p_expected,"",*m_unique_instance.m_default_ostream,test_verbosity_t::QUIET);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    quicky_test::check_expected(const T & p_value,
                                const T & p_expected,
                                const std::string & p_message
                               )
    {
        return check_expected<T>(p_value,p_expected,p_message,*m_unique_instance.m_default_ostream,m_verbosity);
    }

    //-------------------------------------------------------------------------
    template <class EXCEPTION>
    bool
    quicky_test::check_exception_quiet(const std::function<void(void)> & p_function,
                                       bool p_exception_expected
                                      )
    {
        return check_exception<EXCEPTION>(p_function, p_exception_expected, "", *m_unique_instance.m_default_ostream, test_verbosity::QUIET);
    }

    //-------------------------------------------------------------------------
    template <class EXCEPTION>
    bool
    quicky_test::check_exception(const std::function<void(void)> & p_function,
                                 bool p_exception_expected,
                                 const std::string & p_message
                                )
    {
        return check_exception<EXCEPTION>(p_function, p_exception_expected, p_message, *m_unique_instance.m_default_ostream, m_verbosity);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    quicky_test::check_ostream_operator_quiet(const T & p_object,
                                              const std::string & p_expected
                                             )
    {
        return check_ostream_operator(p_object, p_expected, "", *m_unique_instance.m_default_ostream, test_verbosity::QUIET);
    }

    //-------------------------------------------------------------------------
    template <typename T>
    bool
    quicky_test::check_ostream_operator(const T & p_object,
                                        const std::string & p_expected,
                                        const std::string & p_message
                                       )
    {
        return check_ostream_operator(p_object, p_expected, p_message, *m_unique_instance.m_default_ostream, m_verbosity);
    }

    //-------------------------------------------------------------------------
    void
    quicky_test::set_verbosity(const quicky_test::test_verbosity_t & p_verbosity)
    {
        m_verbosity = p_verbosity;
    }

    //-------------------------------------------------------------------------
    quicky_test::test_verbosity_t
    quicky_test::get_verbosity()
    {
        return m_verbosity;
    }

    //-------------------------------------------------------------------------
    inline
    std::string
    quicky_test::to_string(const quicky_test::test_verbosity_t & p_verbosity)
    {
        switch(p_verbosity)
        {
            case test_verbosity_t::QUIET:
                return "QUIET";
                break;
            case test_verbosity_t::FAILED_ONLY:
                return "FAILED_ONLY";
                break;
            case test_verbosity_t::VERBOSE:
                return "VERBOSE";
                break;
            default:
                throw quicky_exception::quicky_logic_exception("Unknown value for test_verbosity_t :" + std::to_string((int)p_verbosity), __LINE__, __FILE__);
        }
        return "";
    }
}
#endif //QUICKY_UTILS_QUICKY_TEST_H
// EOF