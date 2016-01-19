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
#ifndef _WIREWORLD_H_
#define _WIREWORLD_H_

#include "wireworld_configuration.h"
#include "wireworld_gui.h"
#include "signal_handler.h"
#include "signal_handler_listener_if.h"
#include <cinttypes>
#include <vector>

namespace wireworld
{
  class cell;

  class wireworld: public quicky_utils::signal_handler_listener_if
  {
  public:
    wireworld(const wireworld_common::wireworld_types::t_cell_list & p_copper_cells,
	      const wireworld_common::wireworld_types::t_cell_list & p_electron_cells,
	      const wireworld_common::wireworld_types::t_cell_list & p_queue_cells,
	      const wireworld_common::wireworld_configuration & p_conf,
	      const uint32_t & p_x_max,
	      const uint32_t & p_y_max,
	      const wireworld_common::wireworld_types::t_cell_list & p_inactive_cells,
	      const wireworld_common::wireworld_types::t_neighbours & p_neighbours
	      );

    ~wireworld(void);

    void set_queue(cell *p_cell);
    void signal_electron(cell *p_cell);
    void run(void);

    // Methods inherited from signal handler
    inline void handle(int p_signal);
    // End of methods inherited from signal handler

  private:
    uint32_t m_nb_cell;
    cell** m_copper_cells;
    cell** m_to_check_cells;
    cell** m_electron_cells;
    cell** m_futur_electron_cells;
    cell** m_queue_cells;
    uint32_t m_to_check_start_index;
    uint32_t m_to_check_current_index;
    uint32_t m_electron_current_index;
    uint32_t m_queue_current_index;
    wireworld_common::wireworld_gui m_gui;
    wireworld_common::wireworld_configuration m_conf;
    bool m_stop;
    quicky_utils::signal_handler m_signal_handler;
  };

  //------------------------------------------------------------------------------
  void wireworld::handle(int p_signal)
  {
    m_stop = true;
  }
}
#endif // _WIREWORLD_H_
//EOF
