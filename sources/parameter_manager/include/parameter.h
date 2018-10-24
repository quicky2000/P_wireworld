/*    This file is part of parameter manager
      The aim of this software is to provide basic facilities to handle
      command line parameters
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

#ifndef PARAMETER_H
#define PARAMETER_H

#include "parameter_if.h"

namespace parameter_manager
{
  template <typename T>
    class parameter: public parameter_if
  {
  public:
    parameter(const std::string & p_name,
	      bool p_optionnal=false);
    parameter(const std::string & p_name,
	      bool p_optionnal,
	      const T & p_default_value);
    T get_value(void)const;
  private:
    T m_default_value;
  };

  //----------------------------------------------------------------------------
  template <typename T>
    parameter<T>::parameter(const std::string & p_name,
			    bool p_optionnal):
  parameter_if(p_name, p_optionnal)
  {
  }

  //----------------------------------------------------------------------------
  template <typename T>
    parameter<T>::parameter(const std::string & p_name,
			    bool p_optionnal,
			    const T & p_default_value):
  parameter_if(p_name, p_optionnal),
  m_default_value(p_default_value)
  {
  }
    
  //----------------------------------------------------------------------------
  template <typename T>
    T parameter<T>::get_value(void)const
  {
    return value_set() ? parameter_if::get_value<T>() : m_default_value;
  }
}
#endif // PARAMETER_H
//EOF
