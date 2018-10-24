/*    This file is part of parameter manager
      The aim of this software is to provide basic facilities to handle
      command line parameters
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifndef PARAMETER_IF_H
#define PARAMETER_IF_H
#include "quicky_exception.h"
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

namespace parameter_manager
{
  class parameter_if
  {
  public:
    parameter_if(const std::string & p_name,
		 bool p_prefixed=false);
    inline void set_text_value(const std::string & p_value);
    inline bool value_set(void)const;
    inline const std::string & get_name(void)const;
    inline bool is_prefixed(void)const;
    template <typename T> T get_value(void)const;
  private:
    const std::string m_name;
    std::string m_text_value;
    bool m_set;
    bool m_prefixed;
  };

  //----------------------------------------------------------------------------
  parameter_if::parameter_if(const std::string & p_name,
			     bool p_prefixed):
    m_name(p_name),
    m_text_value(""),
    m_set(false),
    m_prefixed(p_prefixed)
      {
      }

    //----------------------------------------------------------------------------
    void parameter_if::set_text_value(const std::string &p_value)
    {
      m_text_value = p_value;
      m_set = true;
    }

    //----------------------------------------------------------------------------
    bool parameter_if::value_set(void)const
    {
      return m_set;
    }

    //----------------------------------------------------------------------------
    bool parameter_if::is_prefixed(void)const
    {
      return m_prefixed;
    }

    //----------------------------------------------------------------------------
    const std::string & parameter_if::get_name(void)const
      {
	return m_name;
      }

    //----------------------------------------------------------------------------
    template <typename T> T parameter_if::get_value(void)const
      {
	return m_text_value;
      }

    //----------------------------------------------------------------------------
    template <> int parameter_if::get_value(void)const
      {
	return stoi(m_text_value,nullptr,10);
      }

    //----------------------------------------------------------------------------
    template <> unsigned int parameter_if::get_value(void)const
      {
	return stoul(m_text_value,nullptr,10);
      }

    //----------------------------------------------------------------------------
    template <> unsigned long long int parameter_if::get_value(void)const
      {
	return stoull(m_text_value,nullptr,10);
      }

    //----------------------------------------------------------------------------
    template <> float parameter_if::get_value(void)const
      {
	return stof(m_text_value);
      }

    //----------------------------------------------------------------------------
    template <> double parameter_if::get_value(void)const
      {
	return stod(m_text_value);
      }

    //----------------------------------------------------------------------------
    template <> bool parameter_if::get_value(void)const
      {
	if("1" == m_text_value)
	  {
	    return true;
	  }
	else if("0" == m_text_value)
	  {
	    return false;
	  }
	else
	  {
	    std::string l_lower_text_value = m_text_value;
	    std::transform(m_text_value.begin(), m_text_value.end(),l_lower_text_value.begin(),(int(*)(int)) std::tolower);
	    if("yes" == l_lower_text_value || "true" == l_lower_text_value)
	      {
		return true;
	      }
	    else if("no" == l_lower_text_value || "false" == l_lower_text_value)
	      {
		return false;
	      }
	  }
	throw quicky_exception::quicky_logic_exception("Parameter \"" + m_name + "\" value \"" + m_text_value + "\" is not a valid bool value : true, false, yes, no, 0, 1",__LINE__,__FILE__);
      }
}
#endif // PARAMETER_IF_H
//EOF
