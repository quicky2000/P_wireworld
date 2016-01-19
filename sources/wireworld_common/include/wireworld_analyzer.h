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
#ifndef WIREWORLD_ANALYZER
#define WIREWORLD_ANALYZER

#include "wireworld_types.h"
#include "wireworld_generic_configuration.h"
#include <sstream>
#include <vector>
#include <cinttypes>
#include <map>
#include <set>
#include <queue>

namespace wireworld_common
{
  class wireworld_analyzer
  {
  public:
    inline static void analyze(const wireworld_types::t_cell_list & p_raw_copper_cells,
			       wireworld_types::t_cell_list & p_queue_cells,
			       wireworld_types::t_cell_list & p_electron_cells,
			       const wireworld_generic_configuration & p_generic_config,
			       const wireworld_types::t_config_items & p_config_list,
			       uint32_t & p_x_max,
			       uint32_t & p_y_max,
			       wireworld_types::t_cell_list & p_copper_cells,
			       wireworld_types::t_cell_list & p_inactive_cells,
			       wireworld_types::t_neighbours & p_neighbours);
  private:
    typedef unsigned int t_partition_id;
    typedef std::map<wireworld_types::t_coordinates,t_partition_id> t_partitionned_cells;
    typedef std::set<t_partition_id> t_active_partitions;
    inline static void compute_active_partitions(const wireworld_types::t_cell_list & p_cells,
						 const t_partitionned_cells & p_partitionned_cells,
						 t_active_partitions & p_active_partitions);
  };

  //----------------------------------------------------------------------------
  void wireworld_analyzer::analyze(const wireworld_types::t_cell_list & p_raw_copper_cells,
				   wireworld_types::t_cell_list & p_queue_cells,
				   wireworld_types::t_cell_list & p_electron_cells,
				   const wireworld_generic_configuration & p_generic_config,
				   const wireworld_types::t_config_items & p_config_list,
				   uint32_t & p_x_max,
				   uint32_t & p_y_max,
				   wireworld_types::t_cell_list & p_copper_cells,
				   wireworld_types::t_cell_list & p_inactive_cells,
				   wireworld_types::t_neighbours & p_neighbours)
  {
    // Insert copper cells in a set to have a kind of spatial access
    t_partitionned_cells l_cells;
    for(auto l_iter: p_raw_copper_cells)
      {
	l_cells.insert(t_partitionned_cells::value_type(l_iter,0));
	// Search for max X and max Y
	if(l_iter.first > p_x_max) p_x_max = l_iter.first;
	if(l_iter.second > p_y_max) p_y_max = l_iter.second;
      }

    // Check if configurable cells corresponds to copper cells
    const wireworld_types::t_item_list & l_generic_list = p_generic_config.get_configurable_cells();
    for(auto l_iter : l_generic_list)
    {
      if(l_iter.is_head_defined())
      {
	const wireworld_generic_item::t_generic_coordinates & l_gen_coord = l_iter.get_head_coord();
	const wireworld_types::t_coordinates l_coord((unsigned int)(l_gen_coord.first),(unsigned int)(l_gen_coord.second));
	if(l_cells.end() == l_cells.find(l_coord))
	  {
	    std::stringstream l_stream;
	    l_stream << l_iter;
	    throw quicky_exception::quicky_logic_exception("Generic item head "+l_stream.str()+" does not correspond to a copper cell",__LINE__,__FILE__);
	  }
      }
      if(l_iter.is_queue_defined())
      {
	const wireworld_generic_item::t_generic_coordinates & l_gen_coord = l_iter.get_queue_coord();
	const wireworld_types::t_coordinates l_coord((unsigned int)(l_gen_coord.first),(unsigned int)(l_gen_coord.second));
	if(l_cells.end() == l_cells.find(l_coord))
	  {
	    std::stringstream l_stream;
	    l_stream << l_iter;
	    throw quicky_exception::quicky_logic_exception("Generic item queue "+l_stream.str()+" does not correspond to a copper cell",__LINE__,__FILE__);
	  }
      }
      if(p_config_list.end() == p_config_list.find(l_iter.get_name()))
	{
	  std::cout << "WARNING : generic item \"" << l_iter.get_name() << "\" has not been configured" << std::endl ;
	}
    }

    // Apply config
    for(auto l_iter : p_config_list)
    {
      const wireworld_generic_item & l_generic_item = p_generic_config.get(l_iter.first);
      if(l_iter.second)
	{
	  if(l_generic_item.is_head_defined())
	    {
	      const wireworld_generic_item::t_generic_coordinates & l_gen_coord = l_generic_item.get_head_coord();
	      const wireworld_types::t_coordinates l_coord((unsigned int)(l_gen_coord.first),(unsigned int)(l_gen_coord.second));
	      p_electron_cells.push_back(l_coord);
	    }
	  if(l_generic_item.is_queue_defined())
	    {
	      const wireworld_generic_item::t_generic_coordinates & l_gen_coord = l_generic_item.get_queue_coord();
	      const wireworld_types::t_coordinates l_coord((unsigned int)(l_gen_coord.first),(unsigned int)(l_gen_coord.second));
	      p_queue_cells.push_back(l_coord);
	    }
	}
    }

    // Cout number of neighbours
    for(auto l_iter:l_cells)
      {
	wireworld_types::t_neighbours::iterator l_neighbour_iter = p_neighbours.insert(wireworld_types::t_neighbours::value_type(l_iter.first,wireworld_types::t_cell_list())).first;

	uint32_t l_x = l_iter.first.first;
	uint32_t l_y = l_iter.first.second;

	for(int l_y_index = -1 ; l_y_index < 2 ; ++l_y_index)
	  {
	    for(int l_x_index = -1 ; l_x_index < 2 ; ++l_x_index)
	      {
		int l_rel_x = l_x + l_x_index;
		int l_rel_y = l_y + l_y_index;
		if((l_x_index || l_y_index) && l_cells.end() != l_cells.find(wireworld_common::wireworld_types::t_coordinates(l_rel_x,l_rel_y)))
		  {
		    l_neighbour_iter->second.push_back(wireworld_common::wireworld_types::t_coordinates(l_rel_x,l_rel_y));
		  }
	      }
	  }
      }

    // Compute partitions
    t_partition_id l_next_partition_id = 1;
    for(auto l_iter:l_cells)
      {
	// Check if current cell is already in a partition
	if(!l_iter.second)
	  {
	    l_iter.second = l_next_partition_id;
	    // Extend partition to neighbours
	    std::queue<wireworld_common::wireworld_types::t_coordinates> l_partition_neighbours;
	    l_partition_neighbours.push(l_iter.first);
	    while(l_partition_neighbours.size())
	      {
		wireworld_types::t_neighbours::const_iterator l_neighbours_iter = p_neighbours.find(l_partition_neighbours.front());
		assert(p_neighbours.end() != l_neighbours_iter);
		for(auto l_neighbour_iter : l_neighbours_iter->second)
		  {
		    t_partitionned_cells::iterator l_neighbour_cell_iter = l_cells.find(l_neighbour_iter);
		    assert(l_cells.end() != l_neighbour_cell_iter);
		    if(!l_neighbour_cell_iter->second)
		      {
			l_neighbour_cell_iter->second = l_next_partition_id;
			l_partition_neighbours.push(l_neighbour_cell_iter->first);
		      }
		  }
		l_partition_neighbours.pop();
	      }
	    ++l_next_partition_id;
	  }
      }
    std::cout << "Number of partitions : " << l_next_partition_id - 1 << std::endl ;

    // Determine active partitions
    t_active_partitions l_active_partitions;
    compute_active_partitions(p_electron_cells,l_cells,l_active_partitions);
    compute_active_partitions(p_queue_cells,l_cells,l_active_partitions);
    std::cout << "Number of active partitions : " << l_active_partitions.size() << std::endl ;

    // Determine with copper cells can become active or not
    for(auto l_iter:p_raw_copper_cells)
      {
	t_partitionned_cells::iterator l_cell_iter = l_cells.find(l_iter);
	assert(l_cells.end() != l_cell_iter);
	if(l_active_partitions.end() != l_active_partitions.find(l_cell_iter->second))
	  {
	    p_copper_cells.push_back(l_iter);
	  }
	else
	  {
	    p_inactive_cells.push_back(l_iter);
	  }
      }

  }

  //----------------------------------------------------------------------------
  void wireworld_analyzer::compute_active_partitions(const wireworld_common::wireworld_types::t_cell_list & p_cells,
						     const t_partitionned_cells & p_partitionned_cells,
						     t_active_partitions & p_active_partitions)
  {
    for(auto l_iter : p_cells)
      {
	t_partitionned_cells::const_iterator l_cell_iter = p_partitionned_cells.find(l_iter);
	assert(p_partitionned_cells.end() != l_cell_iter);
	t_partition_id l_partition_id = l_cell_iter->second;
	if(p_active_partitions.end() == p_active_partitions.find(l_partition_id))
	  {
	    p_active_partitions.insert(l_partition_id);
	  }
      }
  }

}
#endif // WIREWORLD_ANALYZER
//EOF
