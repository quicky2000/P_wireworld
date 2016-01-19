/*
  This file is part of wireworld_computer
  Copyright (C) 2010  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "wireworld_computer.h"
#include "program_parser.h"
#include "parameter_manager.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc,char **argv)
{
  try
    {
      // Defining application command line parameters
      parameter_manager::parameter_manager l_param_manager("wireworld.exe","--",1);
      parameter_manager::parameter_if l_param_file("program_file");
      parameter_manager::parameter_if l_param_detailled_display("detailled_display",true);
      parameter_manager::parameter_if l_output_file("output_file",true);
      parameter_manager::parameter_if l_instruction_delay("instruction_delay",true);
      l_param_manager.add(l_param_file);
      l_param_manager.add(l_param_detailled_display);
      l_param_manager.add(l_output_file);
      l_param_manager.add(l_instruction_delay);

      // Treating parameters
      l_param_manager.treat_parameters(argc,argv);

      typedef wireworld_computer::wireworld_computer_utils::t_register_informations t_reg_infos;
      t_reg_infos l_register_informations;

      wireworld_computer::program_parser::parse(l_param_file.get_value<std::string>(),l_register_informations);

      std::string l_detailled_display_str = l_param_detailled_display.get_value<std::string>();
      bool l_detailled_display = false;
      if(l_param_detailled_display.value_set())
      {
        if("yes" == l_detailled_display_str)
          {
            l_detailled_display = true;
          }
        else if("no" != l_detailled_display_str)
          {
            throw quicky_exception::quicky_logic_exception("Bad detailled_display parameter argument \""+l_detailled_display_str+"\" should be yes or no",__LINE__,__FILE__);
          }
      }

      uint32_t l_instruction_delay_value = l_instruction_delay.value_set() ? l_instruction_delay.get_value<uint32_t>() : 1000000;
      wireworld_computer::wireworld_computer l_computer(l_register_informations,l_output_file.get_value<std::string>(),l_detailled_display,l_instruction_delay_value);
      l_computer.run();
    }
  catch(quicky_exception::quicky_logic_exception & e)
    {
      std::cout << "ERROR : Logic exception : " << e.what() << std::endl ;
      return -1;
    }
  catch(quicky_exception::quicky_runtime_exception & e)
    {
      std::cout << "ERROR : Runtime exception : " << e.what() << std::endl ;
      return -1;
    }
  return 0;
}
