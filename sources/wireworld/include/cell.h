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
#ifndef _CELL_H_
#define _CELL_H_

#include <cinttypes>
#include <iostream>
#include <cassert>

namespace wireworld
{
  class cell
  {
  public:
    inline cell(uint32_t p_x,uint32_t p_y);

    inline void add_neighbour(cell * p_cell);
    inline uint32_t get_nb_neighbour(void)const;
    inline cell* get_neighbour(uint32_t p_index);
    inline void become_electron(void);
    inline void become_queue(void);
    inline void checked(void);
    inline void become_copper(void);

  public:
      inline uint32_t getX(void)const;
      inline uint32_t getY(void)const;
      inline bool is_copper(void)const;
      inline void signal_electron(void);
      inline uint32_t get_nb_electron_around(void)const;
      inline bool to_be_checked(void)const;

  private:
      typedef enum cell_state {COPPER,QUEUE,ELECTRON} t_cell_state;
      uint32_t m_x;
      uint32_t m_y;
      t_cell_state m_current_state;
      bool m_to_check;
      uint32_t m_nb_neighbours;
      cell* m_neighbours[8];
      uint32_t m_nb_electrons_around;
  };

  //----------------------------------------------------------------------------
  cell::cell(uint32_t p_x,uint32_t p_y):
      m_x(p_x),
      m_y(p_y),
      m_current_state(COPPER),
      m_to_check(false),
      m_nb_neighbours(0),
      m_nb_electrons_around(0)
	{
#ifdef DEBUG
	  std::cout << "Create cell(" << m_x << "," << m_y << ")" << std::endl ;
#endif
	}

  //----------------------------------------------------------------------------
    void cell::add_neighbour(cell * p_cell)
      {
	assert(m_nb_neighbours<8);
	m_neighbours[m_nb_neighbours] = p_cell;
	++m_nb_neighbours;
      }

    //--------------------------------------------------------------------------
    uint32_t cell::get_nb_neighbour(void)const
	{
	  return m_nb_neighbours;
	}

    //--------------------------------------------------------------------------
    cell* cell::get_neighbour(uint32_t p_index)
	{
	  assert(p_index<8);
	  return m_neighbours[p_index];
	}

    //--------------------------------------------------------------------------
    void cell::become_electron(void)
	{
#ifdef DEBUG
	  std::cout << "Cell(" << m_x << "," << m_y << ") set as electron" << std::endl;
#endif
	  assert(m_current_state == COPPER);
	  m_current_state = ELECTRON;
	}

    //--------------------------------------------------------------------------
    void cell::become_queue(void)
	{
#ifdef DEBUG
	  std::cout << "Cell(" << m_x << "," << m_y << ") set as queue" << std::endl;
#endif
	  m_current_state = QUEUE;
	}

    //--------------------------------------------------------------------------
    void cell::checked(void)
	{
	  m_to_check = false;
	  m_nb_electrons_around = 0;
	}

    //--------------------------------------------------------------------------
    void cell::become_copper(void)
	{
#ifdef DEBUG
	  std::cout << "Cell(" << m_x << "," << m_y << ") set as copper" << std::endl;
#endif
	  assert(m_current_state = QUEUE);
	  m_current_state = COPPER;
	}

  //----------------------------------------------------------------------------
    bool cell::to_be_checked(void)const
	{
	  return m_to_check ;
	}

    //----------------------------------------------------------------------------
    uint32_t cell::get_nb_electron_around(void)const
	{
#ifdef DEBUG
	  std::cout << "Cell(" << m_x << "," << m_y << ") has " << m_nb_electrons_around << " electrons around "<< std::endl;
#endif
	  return m_nb_electrons_around;
	}
    //----------------------------------------------------------------------------
    uint32_t cell::getX(void)const
	{
	  return m_x;
	}

    //----------------------------------------------------------------------------
    uint32_t cell::getY(void)const
	{
	  return m_y;
	}

    //----------------------------------------------------------------------------
    bool cell::is_copper(void)const
	{
	  return m_current_state==COPPER;
	}

    //----------------------------------------------------------------------------
    void cell::signal_electron(void)
	{
	  m_to_check = true;
	  ++m_nb_electrons_around;
	}


}
#endif // _CELL_H_
//EOF
