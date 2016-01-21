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

#ifndef WIREWORLD_H
#define WIREWORLD_H

#include "systemc.h"
#include "wireworld_gui.h"
#include "wireworld_configuration.h"
#include "cell_factory.h"
#include "signal_handler.h"
#include <vector>
#include <set>
#include <map>
#include <queue>

namespace wireworld_systemc
{
  class wireworld: public sc_module, public quicky_utils::signal_handler_listener_if
  {
  public:
    SC_HAS_PROCESS(wireworld);
    inline wireworld(sc_module_name p_name,
                     const wireworld_common::wireworld_types::t_cell_list & p_copper_cells,
                     const wireworld_common::wireworld_types::t_cell_list & p_tail_cells,
                     const wireworld_common::wireworld_types::t_cell_list & p_electron_cells,
		     const wireworld_common::wireworld_configuration & p_conf,
		     const uint32_t & p_x_max,
		     const uint32_t & p_y_max,
		     const wireworld_common::wireworld_types::t_cell_list & p_inactive_cells,
		     const wireworld_common::wireworld_types::t_neighbours & p_neighbours);
    inline ~wireworld(void);

    // Method inherited from signal_handler_listener_if
    inline void handle(int p_signal);
    // End of method inherited from signal_handler_listener_if
    sc_in<bool> m_clk;
  private:
    inline void clk_management(void);
    

    typedef std::map<wireworld_common::wireworld_types::t_coordinates,std::vector<wireworld_common::wireworld_types::t_coordinates>> t_neighbours;
    inline void instanciate_cells(const wireworld_common::wireworld_types::t_cell_list & p_cells,
                                  const wireworld_common::wireworld_types::t_cell_state & p_state,
                                  const t_neighbours & p_neighbours);

    typedef unsigned int t_partition_id;
    typedef std::set<t_partition_id> t_active_partitions;
    typedef std::map<wireworld_common::wireworld_types::t_coordinates,t_partition_id> t_partitionned_cells;
    inline void compute_active_partitions(const wireworld_common::wireworld_types::t_cell_list & p_cells,
					  const t_partitionned_cells & p_partitionned_cells,
					  t_active_partitions & p_active_partitions);
    typedef std::map<wireworld_common::wireworld_types::t_coordinates,std::pair<cell_base*,sc_signal<bool>*>> t_cell_map;
    t_cell_map m_cells;
    sc_signal<bool> m_clk_sig;
    sc_trace_file *m_trace_file;
    unsigned int m_nb_electron;
    unsigned int m_nb_tail;
    sc_signal<uint32_t> m_nb_electron_sig;
    sc_signal<uint32_t> m_generation_sig;
    uint64_t m_generation;
    wireworld_common::wireworld_gui m_gui;
    wireworld_common::wireworld_configuration m_config;
    bool m_stop;
    quicky_utils::signal_handler m_signal_handler;
  };

  //----------------------------------------------------------------------------
  void wireworld::clk_management(void)
  {
    m_clk_sig.write(m_clk.read());
    if(!m_clk_sig.read())
      {
	// GUI refresh management
	if(m_generation >= m_config.get_start_cycle() && !(m_generation % m_config.get_refresh_interval()))
	  {
#ifdef DEBUG_MESSAGES
	    std::cout << m_generation << " : " << m_nb_electron << "E\t" << m_nb_tail << "Q" << std::endl ;
#endif // DEBUG_MESSAGES
	    m_gui.refresh();
	    SDL_Delay(m_config.get_display_duration());
	  }

        m_nb_electron_sig.write(m_nb_electron);
        m_generation_sig.write(m_generation);
        ++m_generation;
        if(!m_stop && (m_nb_electron || m_nb_tail) && m_generation <= m_config.get_nb_max_cycle())
          {
            m_nb_tail = m_nb_electron;
            m_nb_electron = 0;
          }
        else
          {
            sc_stop();
          }
      }
  }

  //----------------------------------------------------------------------------
  void wireworld::handle(int p_signal)
    {
      std::cout << "STOP requested !" << std::endl ;
      m_stop = true;
    }

  //----------------------------------------------------------------------------
  wireworld::wireworld(sc_module_name p_name,
                       const wireworld_common::wireworld_types::t_cell_list & p_copper_cells,
                       const wireworld_common::wireworld_types::t_cell_list & p_tail_cells,
                       const wireworld_common::wireworld_types::t_cell_list & p_electron_cells,
		       const wireworld_common::wireworld_configuration & p_conf,
		       const uint32_t & p_x_max,
		       const uint32_t & p_y_max,
                       const wireworld_common::wireworld_types::t_cell_list & p_inactive_cells,
		       const wireworld_common::wireworld_types::t_neighbours & p_neighbours):
    sc_module(p_name),
    m_clk("clk_in"),
    m_clk_sig("clk"),
    m_trace_file(nullptr),
    m_nb_electron_sig("nb_electron"),
    m_generation_sig("generation"),
    m_generation(0),
    m_config(p_conf),
    m_stop(false),
    m_signal_handler(*this)
    {

      std::cout << "Number of active cells in design : " << p_copper_cells.size() << std::endl ;

      m_trace_file = sc_create_vcd_trace_file("trace");
      SC_METHOD(clk_management);
      dont_initialize();
      sensitive << m_clk;

      sc_trace(m_trace_file,m_clk_sig,m_clk_sig.name());
      sc_trace(m_trace_file,m_nb_electron_sig,m_nb_electron_sig.name());
      sc_trace(m_trace_file,m_generation_sig,m_generation_sig.name());

      m_nb_tail = p_tail_cells.size();
      m_nb_electron = p_electron_cells.size();

      // Create GUI
      m_gui.createWindow(p_x_max + 2,p_y_max + 2);

      // Instanciate cells
      instanciate_cells(p_electron_cells,wireworld_common::wireworld_types::t_cell_state::ELECTRON,p_neighbours);
      instanciate_cells(p_tail_cells,wireworld_common::wireworld_types::t_cell_state::TAIL,p_neighbours);
      instanciate_cells(p_copper_cells,wireworld_common::wireworld_types::t_cell_state::COPPER,p_neighbours);

      // Display inactive cells
      for(auto l_iter:p_inactive_cells)
	{
	  m_gui.displayCell(l_iter.first,l_iter.second,wireworld_common::wireworld_types::t_cell_state::COPPER);
	}

      // Bind cells
      for(auto l_iter: p_copper_cells)
        {
          // Find cell
          t_cell_map::iterator l_cell_iter = m_cells.find(l_iter);
          assert(m_cells.end() != l_cell_iter);

          // Bind unique clock signal and electron signals
          l_cell_iter->second.first->bind_clk(m_clk_sig);
          l_cell_iter->second.first->bind_electron(*(l_cell_iter->second.second));

	  if(p_conf.get_trace() && l_iter.first >= p_conf.get_trace_x_origin() && l_iter.first < (p_conf.get_trace_x_origin() + p_conf.get_trace_width()) && l_iter.second >= p_conf.get_trace_y_origin() && l_iter.second < (p_conf.get_trace_y_origin() + p_conf.get_trace_height()))
	    {
	      sc_trace(m_trace_file,*(l_cell_iter->second.second),l_cell_iter->second.second->name());
	    }

          // Search for neighbours coordinates
          t_neighbours::const_iterator l_neighbour_list_iter = p_neighbours.find(l_iter);
          assert(p_neighbours.end() != l_neighbour_list_iter);

          // Iterate on neighbours
          unsigned int l_index = 0;
          for(auto l_neighbour_iter:l_neighbour_list_iter->second)
            {
              t_cell_map::iterator l_neighbour_cell_iter = m_cells.find(l_neighbour_iter);
              assert(m_cells.end() != l_neighbour_cell_iter);

              // Bind neighbour
              l_cell_iter->second.first->bind_neighbour(*(l_neighbour_cell_iter->second.second),l_index);
              ++l_index;
            }
        }

      std::cout << "Number of cells instanciated : " << m_cells.size() << std::endl;
      m_gui.refresh();
    }

  //----------------------------------------------------------------------------
  void wireworld::instanciate_cells(const wireworld_common::wireworld_types::t_cell_list & p_cells,
                                    const wireworld_common::wireworld_types::t_cell_state & p_state,
                                    const wireworld::t_neighbours & p_neighbours)
  {
    for(auto l_iter:p_cells)
      {
        if(m_cells.end() == m_cells.find(l_iter))
          {
            std::stringstream l_stream;
            l_stream << l_iter.first << "_" << l_iter.second;
            std::string l_name = l_stream.str();
            std::string l_cell_name = "cell_" + l_name;
            t_neighbours::const_iterator l_neighbour_iter = p_neighbours.find(l_iter);
            assert(p_neighbours.end() != l_neighbour_iter);
            m_cells.insert(t_cell_map::value_type(
                                                  l_iter,
                                                  std::pair<cell_base*,sc_signal<bool>*>(cell_factory::create(l_cell_name.c_str(),
                                                                                                              l_neighbour_iter->second,
                                                                                                              p_state,
                                                                                                              l_iter.first,
                                                                                                              l_iter.second,
                                                                                                              &m_gui,
                                                                                                              m_nb_electron
                                                                                                              ),
                                                                                         new sc_signal<bool>(l_name.c_str(),
                                                                                                             wireworld_common::wireworld_types::t_cell_state::ELECTRON == p_state
                                                                                                             )
                                                                                         )
                                                  )
                           );
          }
      }
  }

  //----------------------------------------------------------------------------
  void wireworld::compute_active_partitions(const wireworld_common::wireworld_types::t_cell_list & p_cells,
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

  //----------------------------------------------------------------------------
  wireworld::~wireworld(void)
  {
    sc_close_vcd_trace_file(m_trace_file);
    for(auto l_iter:m_cells)
      {
        delete l_iter.second.first;
        delete l_iter.second.second;
      }
  }
}
#endif // WIREWORLD_H
//EOF
