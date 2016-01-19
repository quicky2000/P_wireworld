/*    This file is part of quicky_utils
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
#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "signal_handler_listener_if.h"
#include <iostream>

namespace quicky_utils
{

  class signal_handler
  {
  public:
    inline signal_handler(signal_handler_listener_if & p_listener);
    inline static void handler(int p_signal);
  private:
    static signal_handler_listener_if * m_listener;
  };

  //----------------------------------------------------------------------------
  signal_handler::signal_handler(signal_handler_listener_if & p_listener)
    {
      m_listener = &p_listener;
#ifndef _WIN32
      //Preparing signal handling to manage stop
      // Structure declaration to put handlers in place
      struct sigaction l_signal_action;

      // Filling the structure
      // with handler address
      l_signal_action.sa_handler=handler;

      // This flag is theorically ignored but put as zero to be clean
      l_signal_action.sa_flags=0;

      // we don't block specific signals
      sigemptyset(&l_signal_action.sa_mask);

      // Handlers are put in place for 3 signals
      sigaction(SIGINT,&l_signal_action,0);
      sigaction(SIGTERM,&l_signal_action,0);
      sigaction(SIGUSR1,&l_signal_action,0);
#else
      signal(SIGINT,handler);
      signal(SIGTERM,handler);
      signal(SIGUSR1,handler);
#endif
    }

  //----------------------------------------------------------------------------
  void signal_handler::handler(int p_signal)
  {
    m_listener->handle(p_signal);
  }
}
#endif // SIGNAL_HANDLER_H
//EOF
