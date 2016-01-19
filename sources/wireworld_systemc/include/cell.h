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

#ifndef CELL_H
#define CELL_H

#include "systemc.h"
#include "wireworld_types.h"
#include "cell_base.h"
#include "quicky_exception.h"
#include "wireworld_gui.h"
#include <vector>
#include <string>
#include <sstream>

namespace wireworld_systemc
{
  template <unsigned int SIZE>
    class cell: public sc_module,
    public cell_base
  {
  public:
    SC_HAS_PROCESS(cell);
    inline cell(sc_module_name p_name,
		const std::vector<wireworld_common::wireworld_types::t_coordinates> & p_neighbour_coordinates,
                const wireworld_common::wireworld_types::t_cell_state & p_state,
                const unsigned int & p_x,
                const unsigned int & p_y,
                wireworld_common::wireworld_gui * p_gui,
               unsigned int & p_nb_electron);

    // Virtual methods to implement
    inline void bind_clk(sc_signal<bool> & p_clk);
    inline void bind_neighbour(sc_signal<bool> & p_neighbour, const unsigned int & p_index);
    inline void bind_electron(sc_signal<bool> & p_electron);
    // End of virtual methods to implement

    inline ~cell(void);
    sc_in<bool> m_clk;
    sc_in<bool> *m_neighbours[SIZE];
    sc_out<bool> m_electron;
    
    inline void run(void);
  private:
    wireworld_common::wireworld_types::t_cell_state m_state;
    const unsigned int m_x;
    const unsigned int m_y;
    wireworld_common::wireworld_gui * m_gui;
    unsigned int & m_nb_electron;
  };


  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    cell<SIZE>::cell(sc_module_name p_name,
		     const std::vector<wireworld_common::wireworld_types::t_coordinates> & p_neighbour_coordinates,
                     const wireworld_common::wireworld_types::t_cell_state & p_state,
                     const unsigned int & p_x,
                     const unsigned int & p_y,
                     wireworld_common::wireworld_gui * p_gui,
                     unsigned int & p_nb_electron):
    sc_module(p_name),
    m_clk("clk"),
    m_electron("electron"),
    m_state(p_state),
    m_x(p_x),
    m_y(p_y),
    m_gui(p_gui),
    m_nb_electron(p_nb_electron)
    {
      assert(SIZE == p_neighbour_coordinates.size());
      unsigned int l_index = 0;
      for(auto l_iter:p_neighbour_coordinates)
	{
          std::stringstream l_stream;
          l_stream << "from_" << l_iter.first << "_" << l_iter.second ;
	  m_neighbours[l_index] = new sc_in<bool>(l_stream.str().c_str());
          ++l_index;
	}

      if(m_gui) m_gui->displayCell(m_x,m_y,m_state);

      SC_METHOD(run);
      dont_initialize();
      sensitive << m_clk.pos();
    }

  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    cell<SIZE>::~cell(void)
    {
      for(unsigned int l_index = 0 ; l_index < SIZE ; ++l_index)
	{
	  delete m_neighbours[l_index];
	}
    }

  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    void cell<SIZE>::bind_clk(sc_signal<bool> & p_clk)
    {
      m_clk(p_clk);
    }
  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    void cell<SIZE>::bind_neighbour(sc_signal<bool> & p_neighbour, const unsigned int & p_index)
    {
      assert(p_index < SIZE);
      assert(m_neighbours[p_index]);
      (*m_neighbours[p_index])(p_neighbour);
    }
  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    void cell<SIZE>::bind_electron(sc_signal<bool> & p_electron)
    {
      m_electron(p_electron);
    }

  //----------------------------------------------------------------------------
  template <unsigned int SIZE>
    void cell<SIZE>::run(void)
    {
      switch(m_state)
	{
	case wireworld_common::wireworld_types::t_cell_state::COPPER:
	  {
	    unsigned int l_total = 0;
	    for(unsigned int l_index = 0 ; l_index < SIZE ; ++l_index)
	      {
		l_total += m_neighbours[l_index]->read();
	      }
	    if(l_total && l_total < 3)
	      {
		m_electron.write(1);
		m_state = wireworld_common::wireworld_types::t_cell_state::ELECTRON;
                if(m_gui) m_gui->displayElectron(m_x,m_y);
                ++m_nb_electron;
#ifdef DEBUG_MESSAGES
                std::cout << "Cell(" << m_x << "," << m_y << ") switch to " << wireworld_common::wireworld_types::cell_state2string(m_state) << " @" << sc_time_stamp() << std::endl ;
#endif //DEBUG_MESSAGES
	      }
	  }
	  break;
	case wireworld_common::wireworld_types::t_cell_state::QUEUE:
	  m_state = wireworld_common::wireworld_types::t_cell_state::COPPER;
          if(m_gui) m_gui->displayCopper(m_x,m_y);
#ifdef DEBUG_MESSAGES
          std::cout << "Cell(" << m_x << "," << m_y << ") switch to " << wireworld_common::wireworld_types::cell_state2string(m_state) << " @" << sc_time_stamp()  << std::endl ;
#endif // DEBUG_MESSAGES
	  break;
	case wireworld_common::wireworld_types::t_cell_state::ELECTRON:
	  m_electron.write(0);
	  m_state = wireworld_common::wireworld_types::t_cell_state::QUEUE;
          if(m_gui) m_gui->displayQueue(m_x,m_y);
#ifdef DEBUG_MESSAGES
          std::cout << "Cell(" << m_x << "," << m_y << ") switch to " << wireworld_common::wireworld_types::cell_state2string(m_state) << " @" << sc_time_stamp()  << std::endl ;
#endif // DEBUG_MESSAGES
	  break;
        default:
	  {
	    std::stringstream l_stream;
	    l_stream << (unsigned int) m_state ;
	    throw quicky_exception::quicky_logic_exception("Unknown state value : "+l_stream.str(),__LINE__,__FILE__);
	  }
	}
    }

}
#endif // CELL_H
//EOF
