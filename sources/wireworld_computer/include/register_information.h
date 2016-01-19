/*
  This file is part of wireworld_computer
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
#ifndef __REGISTER_INFORMATION_H__
#define __REGISTER_INFORMATION_H__

#include <string>

namespace wireworld_computer
{
  class register_information
  {
  public:
    inline register_information(bool p_instruction,
				const uint16_t & p_initial_value,
				const std::string & p_comment,
				const std::string & p_label="");
    inline register_information(void);
    inline uint16_t get_initial_value(void)const;
    inline bool is_instruction(void)const;
    inline const std::string & get_label(void)const;
    inline const std::string & get_comment(void)const;
  private:
    bool m_instruction;
    uint16_t m_initial_value;
    std::string m_label;
    std::string m_comment;
  };

  //----------------------------------------------------------------------------
  register_information::register_information(bool p_instruction,
					     const uint16_t & p_initial_value,
					     const std::string & p_comment,
					     const std::string & p_label):
    m_instruction(p_instruction),
    m_initial_value(p_initial_value),
    m_label(p_label),
    m_comment(p_comment)
  {
  }

  //----------------------------------------------------------------------------
  register_information::register_information(void):
    m_instruction(false),
    m_initial_value(0),
    m_label(""),
    m_comment("")
    {
    }

  //----------------------------------------------------------------------------
  bool register_information::is_instruction(void)const
  {
    return m_instruction;
  }

  //----------------------------------------------------------------------------
  uint16_t register_information::get_initial_value(void)const
  {
    return m_initial_value;
  }

  //----------------------------------------------------------------------------
  const std::string & register_information::get_label(void)const
  {
    return m_label;
  }

  //----------------------------------------------------------------------------
  const std::string & register_information::get_comment(void)const
  {
    return m_comment;
  }

}
#endif //__REGISTER_INFORMATION_H__
//EOF
