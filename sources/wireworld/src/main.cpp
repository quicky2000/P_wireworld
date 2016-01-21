/*
  This file is part of wireworld
  Copyright (C) 2011  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "wireworld_prepare.h"
#include "wireworld_parameters.h"
#include "wireworld_types.h"
#include "wireworld_configuration.h"
#include "wireworld.h"

int main(int argc,char ** argv)
{
  try
    {
      wireworld_common::wireworld_configuration l_config;
      wireworld_common::wireworld_types::t_cell_list l_copper_cells;
      wireworld_common::wireworld_types::t_cell_list l_tail_cells;
      wireworld_common::wireworld_types::t_cell_list l_electron_cells;
      wireworld_common::wireworld_types::t_cell_list l_inactive_cells;
      wireworld_common::wireworld_types::t_neighbours l_neighbours;
      uint32_t l_x_max = 0;
      uint32_t l_y_max = 0;

      wireworld_common::wireworld_prepare::prepare(argc,argv,
						   l_config,
						   l_copper_cells,
						   l_tail_cells,
						   l_electron_cells,
						   l_inactive_cells,
						   l_neighbours,
						   l_x_max,
						   l_y_max);

      //Creating world
      wireworld::wireworld l_world(l_copper_cells,l_electron_cells,l_tail_cells,l_config,l_x_max,l_y_max,l_inactive_cells,l_neighbours);

      // Launching simulation
      l_world.run();

    }
  catch(quicky_exception::quicky_logic_exception & e)
    {
      std::cout << "ERROR : Runtime exception : " << e.what() << std::endl ;
      return -1;
    }
  catch(quicky_exception::quicky_runtime_exception & e)
    {
      std::cout << "ERROR : Runtime exception : " << e.what() << std::endl ;
      return -1;
    }
  return 0;
}
//EOF
