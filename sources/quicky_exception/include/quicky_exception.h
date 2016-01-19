/*
  This file is part of quicky_exception
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
#ifndef _QUICKY_EXCEPTION_H_
#define _QUICKY_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace quicky_exception
{

  class quicky_base_exception
  {
  public:
    inline quicky_base_exception (const unsigned int &p_line,
				  const std::string & p_file);
    inline const unsigned int &get_line (void) const;
    inline const std::string & get_file (void) const;
    inline virtual ~ quicky_base_exception (void) throw ()
    {
    }
  private:
    const unsigned int m_line;
    const std::string m_file;
  };

  class quicky_runtime_exception:public std::runtime_error,
    public quicky_base_exception
  {
  public:
    inline quicky_runtime_exception (const std::string & p_msg,
				     const unsigned int &p_line,
				     const std::string & p_file);
  private:
  };

  class quicky_logic_exception:public std::logic_error,
    public quicky_base_exception
  {
  public:
    inline quicky_logic_exception (const std::string & p_msg,
				   const unsigned int &p_line,
				   const std::string & p_file);
  private:
  };


  //----------------------------------------------------------------------------
  quicky_base_exception::quicky_base_exception (const unsigned int &p_line,
						const std::
						string &
						p_file):m_line (p_line),
    m_file (p_file)
  {
  }


  //----------------------------------------------------------------------------
  const unsigned int &quicky_base_exception::get_line (void) const
  {
    return m_line;
  }

  //----------------------------------------------------------------------------
  const std::string & quicky_base_exception::get_file (void) const
  {
    return m_file;
  }

  //----------------------------------------------------------------------------
  quicky_runtime_exception::quicky_runtime_exception (const std::
						      string & p_msg,
						      const unsigned int
						      &p_line,
						      const std::
						      string & p_file):std::
    runtime_error (p_msg), quicky_base_exception (p_line, p_file)
  {
  }

  //----------------------------------------------------------------------------
  quicky_logic_exception::quicky_logic_exception (const std::string & p_msg,
						  const unsigned int &p_line,
						  const std::
						  string & p_file):std::
    logic_error (p_msg), quicky_base_exception (p_line, p_file)
  {
  }


}
#endif // _QUICKY_EXCEPTION_H_
//EOF
