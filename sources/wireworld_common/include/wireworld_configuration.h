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
#ifndef _WIREWORLD_CONFIGURATION_H_
#define _WIREWORLD_CONFIGURATION_H_

#include <cinttypes>
#include <string>

namespace wireworld_common
{
  class wireworld_configuration
  {
  public:
    inline wireworld_configuration(void);

    inline void set_input_file_name(const std::string & p_name);
    inline const std::string & get_input_file_name(void)const;
    inline void set_nb_max_cycle(uint32_t p_nb_max_cycle);
    inline uint32_t get_nb_max_cycle(void)const;
    inline void set_start_cycle(uint32_t p_start_cycle);
    inline uint32_t get_start_cycle(void)const;
    inline void set_refresh_interval(uint32_t p_refresh_interval);
    inline uint32_t get_refresh_interval(void)const;
    inline void set_display_duration(uint32_t p_display_duration);
    inline uint32_t get_display_duration(void)const;
    inline void set_generic_file_name(const std::string & p_name);
    inline const std::string & get_generic_file_name(void)const;
    inline void set_config_file_name(const std::string & p_name);
    inline const std::string & get_config_file_name(void)const;
#ifdef COMPILE_TRACE_FEATURE
    inline void set_trace(bool p_trace);
    inline bool get_trace(void)const;
    inline void set_trace_x_origin(const unsigned int & p_trace_x_origin);
    inline unsigned int get_trace_x_origin(void)const;
    inline void set_trace_y_origin(const unsigned int & p_trace_y_origin);
    inline unsigned int get_trace_y_origin(void)const;
    inline void set_trace_width(const unsigned int & p_trace_width);
    inline unsigned int get_trace_width(void)const;
    inline void set_trace_height(const unsigned int & p_trace_height);
    inline unsigned int get_trace_height(void)const;
#endif // COMPILE_TRACE_FEATURE
  private:
#ifdef COMPILE_TRACE_FEATURE
    bool m_trace;
    unsigned int m_trace_x_origin;
    unsigned int m_trace_y_origin;
    unsigned int m_trace_width;
    unsigned int m_trace_height;
#endif // COMPILE_TRACE_FEATURE
    std::string m_input_file_name;
    std::string m_generic_file_name;
    std::string m_config_file_name;
    uint32_t m_nb_max_cycle;
    uint32_t m_start_cycle;
    uint32_t m_refresh_interval;
    uint32_t m_display_duration;
  };

  //------------------------------------------------------------------------------
  wireworld_configuration::wireworld_configuration(void):
 #ifdef COMPILE_TRACE_FEATURE
    m_trace(false),
    m_trace_x_origin(0),
    m_trace_y_origin(0),
    m_trace_width(0),
    m_trace_height(0),
#endif // COMPILE_TRACE_FEATURE
    m_input_file_name("wireworld.txt"),
    m_generic_file_name(""),
    m_config_file_name(""),
    m_nb_max_cycle(1000),
    m_start_cycle(0),
    m_refresh_interval(1),
    m_display_duration(500)
    {
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_input_file_name(const std::string & p_name)
    {
      m_input_file_name = p_name;
    }

    //------------------------------------------------------------------------------
    const std::string & wireworld_configuration::get_input_file_name(void)const
      {
	return m_input_file_name;
      }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_generic_file_name(const std::string & p_name)
    {
      m_generic_file_name = p_name;
    }

    //------------------------------------------------------------------------------
    const std::string & wireworld_configuration::get_generic_file_name(void)const
      {
	return m_generic_file_name;
      }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_config_file_name(const std::string & p_name)
    {
      m_config_file_name = p_name;
    }

    //------------------------------------------------------------------------------
    const std::string & wireworld_configuration::get_config_file_name(void)const
      {
	return m_config_file_name;
      }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_nb_max_cycle(uint32_t p_nb_max_cycle)
    {
      m_nb_max_cycle = p_nb_max_cycle;
    }

    //------------------------------------------------------------------------------
    uint32_t wireworld_configuration::get_nb_max_cycle(void)const
    {
      return m_nb_max_cycle;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_start_cycle(uint32_t p_start_cycle)
    {
      m_start_cycle = p_start_cycle;
    }

    //------------------------------------------------------------------------------
    uint32_t wireworld_configuration::get_start_cycle(void)const
    {
      return m_start_cycle;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_refresh_interval(uint32_t p_refresh_interval)
    {
      m_refresh_interval = p_refresh_interval;
    }

    //------------------------------------------------------------------------------
    uint32_t wireworld_configuration::get_refresh_interval(void)const
    {
      return m_refresh_interval;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_display_duration(uint32_t p_display_duration)
    {
      m_display_duration = p_display_duration;
    }

    //------------------------------------------------------------------------------
    uint32_t wireworld_configuration::get_display_duration(void)const
    {
      return m_display_duration;
    }
#ifdef COMPILE_TRACE_FEATURE
    //------------------------------------------------------------------------------
    void wireworld_configuration::set_trace(bool p_trace)
    {
      m_trace = p_trace;
    }

    //------------------------------------------------------------------------------
    bool wireworld_configuration::get_trace(void)const
    {
      return m_trace;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_trace_x_origin(const unsigned int & p_trace_x_origin)
    {
      m_trace_x_origin = p_trace_x_origin;
    }

    //------------------------------------------------------------------------------
    unsigned int wireworld_configuration::get_trace_x_origin(void)const
    {
      return m_trace_x_origin;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_trace_y_origin(const unsigned int & p_trace_y_origin)
    {
      m_trace_y_origin = p_trace_y_origin;
    }

    //------------------------------------------------------------------------------
    unsigned int wireworld_configuration::get_trace_y_origin(void)const
    {
      return m_trace_y_origin;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_trace_width(const unsigned int & p_trace_width)
    {
      m_trace_width = p_trace_width;
    }

    //------------------------------------------------------------------------------
    unsigned int wireworld_configuration::get_trace_width(void)const
    {
      return m_trace_width;
    }

    //------------------------------------------------------------------------------
    void wireworld_configuration::set_trace_height(const unsigned int & p_trace_height)
    {
      m_trace_height = p_trace_height;
    }

    //------------------------------------------------------------------------------
    unsigned int wireworld_configuration::get_trace_height(void)const
    {
      return m_trace_height;
    }
#endif // COMPILE_TRACE_FEATURE

}
#endif /* _WIREWORLD_CONFIGURATION_H_ */
//EOF
