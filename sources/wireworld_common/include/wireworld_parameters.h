/*
    This file is part of wireworld_common
    Copyright (C) 2015  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifndef WIREWORLD_PARAMETERS
#define WIREWORLD_PARAMETERS

#include "parameter_manager.h"
#include "wireworld_configuration.h"

namespace wireworld_common
{
  class wireworld_parameters
  {
  public:
    static inline void configure(int argc,char **argv,wireworld_configuration & p_config);
  private:
  };

  //----------------------------------------------------------------------------
  void wireworld_parameters::configure(int argc,char **argv,wireworld_configuration & p_config)
  {
    // Defining application command line parameters
    parameter_manager::parameter_manager l_param_manager("wireworld.exe","--",1);
    parameter_manager::parameter_if l_param_file("input_file");
    parameter_manager::parameter_if l_param_nb_max_cycle("nb_max_cycle",true);
    parameter_manager::parameter_if l_param_start_cycle("start_cycle",true);
    parameter_manager::parameter_if l_param_refresh_interval("refresh_interval",true);
    parameter_manager::parameter_if l_param_display_duration("display_duration",true);
    parameter_manager::parameter_if l_param_generic_file("generic_file",true);
    parameter_manager::parameter_if l_param_config_file("config_file",true);
#ifdef COMPILE_TRACE_FEATURE
    parameter_manager::parameter_if l_param_trace("trace",true);
    parameter_manager::parameter_if l_param_trace_x_origin("trace_x_origin",true);
    parameter_manager::parameter_if l_param_trace_y_origin("trace_y_origin",true);
    parameter_manager::parameter_if l_param_trace_width("trace_width",true);
    parameter_manager::parameter_if l_param_trace_height("trace_height",true);
    l_param_manager.add(l_param_trace);
    l_param_manager.add(l_param_trace_x_origin);
    l_param_manager.add(l_param_trace_y_origin);
    l_param_manager.add(l_param_trace_width);
    l_param_manager.add(l_param_trace_height);
#endif // COMPILE_TRACE_FEATURE
    l_param_manager.add(l_param_file);
    l_param_manager.add(l_param_generic_file);
    l_param_manager.add(l_param_config_file);
    l_param_manager.add(l_param_start_cycle);
    l_param_manager.add(l_param_nb_max_cycle);
    l_param_manager.add(l_param_refresh_interval);
    l_param_manager.add(l_param_display_duration);

    // Treating parameters
    l_param_manager.treat_parameters(argc,argv);

    // Defining configuration according to parameters
    if(l_param_file.value_set())
      {
	p_config.set_input_file_name(l_param_file.get_value<std::string>());
      }

    if(l_param_generic_file.value_set())
      {
	p_config.set_generic_file_name(l_param_generic_file.get_value<std::string>());
      }

    if(l_param_config_file.value_set())
      {
	p_config.set_config_file_name(l_param_config_file.get_value<std::string>());
      }

    if(l_param_nb_max_cycle.value_set())
      {
	p_config.set_nb_max_cycle(l_param_nb_max_cycle.get_value<uint32_t>());
      }

    if(l_param_start_cycle.value_set())
      {
	p_config.set_start_cycle(l_param_start_cycle.get_value<uint32_t>());
      }

    if(l_param_refresh_interval.value_set())
      {
	unsigned int l_refresh_interval = l_param_refresh_interval.get_value<uint32_t>();
	if(!l_refresh_interval)
	  {
	    throw quicky_exception::quicky_logic_exception("Refresh interval must not be null",__LINE__,__FILE__);
	  }
	p_config.set_refresh_interval(l_refresh_interval);
      }

    if(l_param_display_duration.value_set())
      {
	p_config.set_display_duration(l_param_display_duration.get_value<uint32_t>());
      }
#ifdef COMPILE_TRACE_FEATURE
    if(l_param_trace.value_set())
      {
	std::string l_trace_str = l_param_trace.get_value<std::string>();
	if("1" != l_trace_str && "0" != l_trace_str)
	  {
	    throw quicky_exception::quicky_logic_exception("Trace parameter value should be 0 or 1 not "+l_trace_str,__LINE__,__FILE__);
	  }
	p_config.set_trace(l_param_trace.get_value<uint32_t>());
      }
    if(l_param_trace_x_origin.value_set())
      {
	p_config.set_trace_x_origin(l_param_trace_x_origin.get_value<uint32_t>());
      }
    if(l_param_trace_y_origin.value_set())
      {
	p_config.set_trace_y_origin(l_param_trace_y_origin.get_value<uint32_t>());
      }
    if(l_param_trace_width.value_set())
      {
	p_config.set_trace_width(l_param_trace_width.get_value<uint32_t>());
      }
    if(l_param_trace_height.value_set())
      {
	p_config.set_trace_height(l_param_trace_height.get_value<uint32_t>());
      }
#endif // COMPILE_TRACE_FEATURE

  }

}

#endif // WIREWORLD_PARAMETERS
//EOF
