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
#ifdef QUICKY_UTILS_SELF_TEST
#include "type_string.h"
#include "quicky_exception.h"
#include "quicky_bitfield.h"
#include "safe_types.h"
#include "ext_uint.h"
#include "ext_int.h"
#include "test_fract.h"
#include "quicky_test.h"
#include "ansi_colors.h"
#include <fstream>
#include <iostream>
#include <functional>
#include <sstream>

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

using namespace quicky_utils;

/**
 * Method regrouping test of test utilites
 */
bool
check_test_utilities();

//------------------------------------------------------------------------------
int main(int argc,char ** argv)
{
    bool l_ok = true;
    try
    {
        std::ofstream l_report_file;
        l_report_file.open("report.log");
        if(!l_report_file.is_open())
        {
            throw quicky_exception::quicky_runtime_exception("Unable to create file report.log", __LINE__, __FILE__);
        }
        quicky_test::set_ostream(l_report_file);
#if 0
        l_ok &= check_test_utilities();
        l_ok &= test_ext_uint();
        l_ok &= test_ext_int();
        l_ok &= test_type_string();
#endif // 0
        l_ok &= test_fract();
#if 0
        l_ok &= test_safe_types();
        test_ansi_colors();
#endif // 0
        l_report_file.close();

    }
    catch (quicky_exception::quicky_runtime_exception & e)
    {
        std::cout << "ERROR : " << e.what() << " " << e.get_file() << ":" << e.get_line() << std::endl;
        return (-1);
    }
    catch (quicky_exception::quicky_logic_exception & e)
    {
        std::cout << "ERROR : " << e.what() << " " << e.get_file() << ":" << e.get_line() << std::endl;
        return (-1);
    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- TEST " << (l_ok ? "PASSED" : "FAILED") << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    return !l_ok;
}

//-----------------------------------------------------------------------------
bool
check_test_utilities()
{
    quicky_test::get_ostream() << "----------------------------------------------" << std::endl;
    quicky_test::get_ostream() << "| CHECK test_utilities" << std::endl;
    quicky_test::get_ostream() << "----------------------------------------------" << std::endl;
    bool l_ok = true;
    l_ok &= quicky_test::check_expected(quicky_test::check_expected_quiet(false,true),false, "Failed expected verification");
    l_ok &= quicky_test::check_expected(quicky_test::check_expected_quiet(true,true),true,"Passed expected verification");
    l_ok &= quicky_test::check_expected(quicky_test::check_exception_quiet<quicky_exception::quicky_logic_exception>([]{
                                                                                                                         throw quicky_exception::quicky_logic_exception("Volontary exception",
                                                                                                                                                                        __LINE__,
                                                                                                                                                                        __FILE__
                                                                                                                                                                       );
                                                                                                                       }
                                                                                                               ),
                                        true,
                                        "Exception detection verification"
                                       );
    l_ok &= quicky_test::check_expected(quicky_test::check_exception_quiet<quicky_exception::quicky_logic_exception>([]{},
                                                                                                                     false // No exception expected
                                                                                                                    ),
                                        true,
                                        "No exception detection verification"
                                       );
    l_ok &= quicky_test::check_expected(quicky_test::check_ostream_operator_quiet<uint32_t>(12,"23"),false,"Failed ostream operator verification");
    l_ok &= quicky_test::check_expected(quicky_test::check_ostream_operator_quiet<uint32_t>(12,"12"),true,"Passed ostream operator verification");
    return l_ok;
}

#endif // QUICKY_UTILS_SELF_TEST
//EOF
