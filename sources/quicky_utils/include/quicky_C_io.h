/*    This file is part of quicky_utils
      Copyright (C) 2014  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#ifndef QUICKY_C_IO_HPP
#define QUICKY_C_IO_HPP

#include "quicky_exception.h"
#include <cstdio>
#include <sstream>

namespace quicky_utils
{
    class quicky_C_io
    {
    public:
      template<size_t SIZE>
      static inline void my_fread(void *ptr,size_t nmemb, FILE *stream)
	{
	  size_t l_result = fread(ptr,SIZE,nmemb,stream);
	  if(nmemb != l_result)
	    {
	      std::stringstream l_result_str;
	      l_result_str << l_result;
	      std::stringstream sizeof_str;
	      sizeof_str << SIZE;
	      throw quicky_exception::quicky_runtime_exception("Bad fread return value "+l_result_str.str()+" vs expected "+sizeof_str.str(),__LINE__,__FILE__);
	    }
	}

      //------------------------------------------------------------------------
      static inline void my_fread(void *ptr,size_t size,size_t nmemb, FILE *stream)
	{
	  size_t l_result = fread(ptr,size,nmemb,stream);
	  if(nmemb != l_result)
	    {
	      std::stringstream l_result_str;
	      l_result_str << l_result;
	      std::stringstream sizeof_str;
	      sizeof_str << size;
	      throw quicky_exception::quicky_runtime_exception("Bad fread return value "+l_result_str.str()+" vs expected "+sizeof_str.str(),__LINE__,__FILE__);
	    }
	}

    private:
    };

}
#endif // QUICKY_C_IO_HPP
//EOF
