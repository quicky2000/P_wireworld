/*    This file is part of parameter_manager
      The aim of this software is to provided facilities for parameter
      management
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

#ifdef PARAMETER_MANAGER_SELF_TEST

#include "parameter_manager.h"
#include "parameter.h"

int main(int argc, char ** argv)
{
    try
    {
        std::cout << "Parameter received : " << argc << std::endl;
        parameter_manager::parameter_manager l_parameter_manager("main_parameter_manager","--",2);
        parameter_manager::parameter<std::string> l_string_param("string_param",false);
        parameter_manager::parameter<int32_t> l_int_param("int_param",false,13);
        parameter_manager::parameter<double> l_double_param("double_param", true,3.14159);

        l_parameter_manager.add(l_string_param);
        l_parameter_manager.add(l_int_param);
        l_parameter_manager.add(l_double_param);

        l_parameter_manager.treat_parameters(argc,argv);

        std::cout << "String param value \"" << l_string_param.get_value() << "\"" << std::endl;
        std::cout << "Int param value " << l_int_param.get_value() << std::endl;
        std::cout << "Double param value " << l_double_param.get_value() << std::endl;
    }
    catch(quicky_exception::quicky_logic_exception & e)
    {
        std::cout << "ERROR : " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

#endif // PARAMETER_MANAGER_SELF_TEST
//EOF
