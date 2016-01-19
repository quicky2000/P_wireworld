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
#ifndef _WIREWORLD_PREPARE_H_
#define _WIREWORLD_PREPARE_H_

#include "wireworld_configuration.h"
#include "wireworld_generic_configuration.h"
#include "wireworld_types.h"
#include "wireworld_parser.h"
#include "wireworld_analyzer.h"
#include "wireworld_generic_parser.h"
#include "wireworld_config_parser.h"
#include "wireworld_parameters.h"
#include <cinttypes>

namespace wireworld_common
{
  class wireworld_prepare
  {
  public:
    inline static void prepare(int argc,
			       char ** argv,
			       wireworld_common::wireworld_configuration & p_config,
			       wireworld_common::wireworld_types::t_cell_list & p_copper_cells,
			       wireworld_common::wireworld_types::t_cell_list & p_queue_cells,
			       wireworld_common::wireworld_types::t_cell_list & p_electron_cells,
			       wireworld_common::wireworld_types::t_cell_list & p_inactive_cells,
			       wireworld_common::wireworld_types::t_neighbours & p_neighbours,
			       uint32_t & p_x_max,
			       uint32_t & p_y_max
			       );
  };

  //----------------------------------------------------------------------------
  void wireworld_prepare::prepare(int argc,
				  char ** argv,
				  wireworld_common::wireworld_configuration & p_config,
				  wireworld_common::wireworld_types::t_cell_list & p_copper_cells,
				  wireworld_common::wireworld_types::t_cell_list & p_queue_cells,
				  wireworld_common::wireworld_types::t_cell_list & p_electron_cells,
				  wireworld_common::wireworld_types::t_cell_list & p_inactive_cells,
				  wireworld_common::wireworld_types::t_neighbours & p_neighbours,
				  uint32_t & p_x_max,
				  uint32_t & p_y_max
				  )
  {
    wireworld_common::wireworld_parameters::configure(argc,argv,p_config);

    wireworld_common::wireworld_types::t_cell_list l_raw_copper_cells;
    wireworld_common::wireworld_parser::parse(p_config.get_input_file_name(),l_raw_copper_cells,p_queue_cells,p_electron_cells);

    wireworld_common::wireworld_generic_configuration l_generic_config;
    if("" != p_config.get_generic_file_name())
      {
	wireworld_common::wireworld_generic_parser l_generic_parser(p_config.get_generic_file_name());
	l_generic_parser.parse(l_generic_config);
      }

    wireworld_common::wireworld_types::t_config_items l_config_items;
    if("" != p_config.get_config_file_name())
      {
	if("" == p_config.get_generic_file_name())
	  {
	    throw quicky_exception::quicky_logic_exception("A config files has been provided without generic config file ",__LINE__,__FILE__);
	  }
	wireworld_common::wireworld_config_parser l_config_parser(p_config.get_config_file_name());
	l_config_parser.parse(l_config_items);
      }
 
    wireworld_common::wireworld_analyzer::analyze(l_raw_copper_cells,p_queue_cells,p_electron_cells,l_generic_config,l_config_items,p_x_max,p_y_max,p_copper_cells,p_inactive_cells,p_neighbours);
  }
}

#endif // _WIREWORLD_PREPARE_H_
//EOF
