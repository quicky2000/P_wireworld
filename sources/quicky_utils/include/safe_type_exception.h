/*    This file is part of quicky_utils
      Copyright (C) 2017  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifndef QUICKY_UTILS_SAFE_UINT_EXCEPTION_H
#define QUICKY_UTILS_SAFE_UINT_EXCEPTION_H

#include "quicky_exception.h"

namespace quicky_utils
{
    class safe_type_exception: public quicky_exception::quicky_logic_exception
    {
      public:
        inline safe_type_exception (const std::string & p_msg,
                                    const unsigned int & p_line,
                                    const std::string & p_file);
      private:
    };

    //-------------------------------------------------------------------------
    safe_type_exception::safe_type_exception(const std::string & p_msg,
                                             const unsigned int & p_line,
                                             const std::string & p_file
                                            ):
            quicky_logic_exception(p_msg,
                                   p_line,
                                   p_file
                                  )
    {

    }
}
#endif //QUICKY_UTILS_SAFE_UINT_EXCEPTION_H
//EOF
