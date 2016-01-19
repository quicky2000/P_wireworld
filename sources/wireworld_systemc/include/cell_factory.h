/*
    This file is part of wireworld_systemc
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

#ifndef CELL_FACTORY_H
#define CELL_FACTORY_H

#include "systemc.h"
#include "cell.h"

namespace wireworld_systemc
{
  class cell_factory
  {
  public:
    inline static cell_base * create(sc_module_name p_name,
                                     const std::vector<wireworld_common::wireworld_types::t_coordinates> & p_neighbour_coordinates,
                                     const wireworld_common::wireworld_types::t_cell_state & p_state,
                                     const unsigned int & p_x,
                                     const unsigned int & p_y,
                                     wireworld_common::wireworld_gui * p_gui,
                                     unsigned int & p_nb_electron);  
  private:
  };

  //----------------------------------------------------------------------------
  cell_base * cell_factory::create(sc_module_name p_name,
                                   const std::vector<wireworld_common::wireworld_types::t_coordinates> & p_neighbour_coordinates,
                                   const wireworld_common::wireworld_types::t_cell_state & p_state,
                                   const unsigned int & p_x,
                                   const unsigned int & p_y,
                                   wireworld_common::wireworld_gui * p_gui,
                                   unsigned int & p_nb_electron)
    {
      switch(p_neighbour_coordinates.size())
	{
	case 1:
	  return new cell<1>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 2:
	  return new cell<2>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 3:
	  return new cell<3>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 4:
	  return new cell<4>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 5:
	  return new cell<5>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 6:
	  return new cell<6>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 7:
	  return new cell<7>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	case 8:
	  return new cell<8>(p_name, p_neighbour_coordinates, p_state, p_x, p_y, p_gui, p_nb_electron);
	  break;
	default:
	  {
	    std::stringstream l_stream;
	    l_stream << p_neighbour_coordinates.size();
	    std::stringstream l_x_stream;
	    l_x_stream << p_x;
	    std::stringstream l_y_stream;
	    l_y_stream << p_y;
	    throw quicky_exception::quicky_logic_exception("Unsupported number of neighbour "+l_stream.str()+" for cell located in ("+l_x_stream.str()+","+l_y_stream.str()+")",__LINE__,__FILE__);
	  }
	}
    }


}
#endif // CELL_FACTORY_H
