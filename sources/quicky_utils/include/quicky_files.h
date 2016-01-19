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
#ifndef QUICKY_FILES_HPP
#define QUICKY_FILES_HPP

#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <string>  
#include <cstring>

namespace quicky_utils
{
    class quicky_files
    {
    public:
      static inline void list_content(const std::string & p_name,
				      std::vector<std::string> & p_list)
	{
	  DIR * l_directory = opendir(p_name.c_str());
     
	  if (l_directory != NULL)
	    {
	      struct dirent * l_item;
         
	      while ((l_item = readdir(l_directory)) != NULL)
		{
                  if(strcmp(l_item->d_name,".") && strcmp(l_item->d_name,".."))
                    {
                      p_list.push_back(l_item->d_name);
                    }
		}
	      
	      closedir(l_directory);
	    }
	}
    };

}
#endif // QUICKY_FILES_HPP
//EOF
