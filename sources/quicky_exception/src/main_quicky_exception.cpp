/*
  This file is part of quicky_exception
  Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include <iostream>
#include "quicky_exception.h"

#ifdef QUICKY_EXCEPTION_SELF_TEST

/**
 * Generate and catch an exception
 * @tparam T type of exception generated
 * @param String name of exception type
 * @return true if succeed to generate and catch exception
 */
template <class T>
bool
generate_exception(const std::string & p_exception_type)
{
    try
    {
        throw T(p_exception_type,__LINE__,__FILE__);
    }
    catch(const T & e)
    {
        std::cout << "Catch exception \"" << e.what() ;
        std::cout << "\" emitted from " << e.get_file() << ":" ;
        std::cout << e.get_line() << std::endl;
        return true;
    }
    return false;
}

int main(int argc, char ** argv)
{
    std::cout << "Running quicky_exception test" << std::endl;
    bool l_result = true;
    l_result &= generate_exception<quicky_exception::quicky_runtime_exception>("quicky_runtime_exception");
    l_result &= generate_exception<quicky_exception::quicky_logic_exception>("quicky_logic_exception");
    return l_result ? 0 : 1;
}
#endif // QUICKY_EXCEPTION_SELF_TEST
//EOF
