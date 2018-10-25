/*    This file is part of simple_gui
      The aim of this software is to provide a simple SDL based GUI
      Copyright (C) 2016  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef _AUTO_REFRESH_GUI_H_
#define _AUTO_REFRESH_GUI_H_

#include "simple_gui.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <cassert>

namespace simple_gui
{
  class auto_refresh_gui: public simple_gui
  {
  public:
    inline auto_refresh_gui(void);
    inline void start_refresh(const std::chrono::milliseconds & p_delay);
    inline void stop_refresh(void);
    inline const std::chrono::milliseconds & get_delay(void)const;
    inline bool is_running(void)const;
    inline ~auto_refresh_gui(void);
  private:
    inline static void periodic_refresh(const std::atomic<bool> & p_stop,
					simple_gui & p_gui,
					const std::chrono::milliseconds & p_delay);

    std::chrono::milliseconds m_delay;
    std::atomic<bool> m_stop_requested;
    std::thread * m_thread;
  };

  //----------------------------------------------------------------------------
  auto_refresh_gui::auto_refresh_gui(void):
    simple_gui(),
    m_delay(33),
    m_stop_requested(false),
    m_thread(nullptr)
    {
    }

    //------------------------------------------------------------------------------
    void auto_refresh_gui::periodic_refresh(const std::atomic<bool> & p_stop,
					    simple_gui & p_gui,
					    const std::chrono::milliseconds & p_delay)
    {
      while(!static_cast<bool>(p_stop))
	{
	  p_gui.refresh();
	  std::this_thread::sleep_for(p_delay);
	}
    }

    //------------------------------------------------------------------------------
    void auto_refresh_gui::start_refresh(const std::chrono::milliseconds & p_delay)
    {
      m_delay = p_delay;
      m_thread = new std::thread(periodic_refresh,std::ref(m_stop_requested),std::ref(*this),std::ref(m_delay));
    }

    //------------------------------------------------------------------------------
    void auto_refresh_gui::stop_refresh(void)
    {
      assert(m_thread);
      m_stop_requested.store(true,std::memory_order_relaxed);      
      m_thread->join();
      delete m_thread;
      m_thread = nullptr;
      m_stop_requested.store(false,std::memory_order_relaxed);      
    }

    //------------------------------------------------------------------------------
    const std::chrono::milliseconds & auto_refresh_gui::get_delay(void)const
      {
	return m_delay;
      }

    //------------------------------------------------------------------------------
    bool auto_refresh_gui::is_running(void)const
    {
      return nullptr != m_thread;
    }

    //------------------------------------------------------------------------------
    auto_refresh_gui::~auto_refresh_gui(void)
    {
      if(m_thread)
	{
	  stop_refresh();
	}
    }

}
#endif // _AUTO_REFRESH_GUI_H_
//EOF
