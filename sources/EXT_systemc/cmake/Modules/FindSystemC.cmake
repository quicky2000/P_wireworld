#
#  This file is part of EXT_systemc
#  Copyright (C) 2017  Julien Thevenon ( julien_thevenon at yahoo.fr )
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>
#
#.rst:
# FindSystemC
# -------------
#
# Module to locate SystemC library
#
# This module define the following variables
#    SystemC_FOUND
#    SystemC_VERSION
#    SystemC_LIBRARIES
#    SystemC_INCLUDE_DIRS
#
find_package(PkgConfig)
pkg_check_modules(PC_SYSTEMC QUIET libsystemc)
if("${PC_SYSTEMC}" STREQUAL "")
    set(SYSTEMC_HINTS $ENV{SYSTEMC_INSTALL})

    set(SYSTEMC_PATHS /usr/local/systemc-${SystemC_FIND_VERSION}
        /usr/lib/systemc-${SystemC_FIND_VERSION}
        /usr/local/lib/systemc-${SystemC_FIND_VERSION}
        /usr/local/share/systemc-${SystemC_FIND_VERSION}
        /usr/share/systemc-${SystemC_FIND_VERSION})
    find_path(SystemC_INCLUDE_DIR
              NAMES systemc.h
              PATHS ${SYSTEMC_PATHS}
              HINTS {SYSTEMC_HINTS}
              PATH_SUFFIXES include
              DOC "Variable storing the location of SystemC header")

    find_library(SystemC_LIBRARY
              NAMES systemc
              PATHS ${SYSTEMC_PATHS}
              HINTS {SYSTEMC_HINTS}
              PATH_SUFFIXES lib-linux64
              DOC "Variable storing the location of SystemC library")
    set(SystemC_VERSION ${SystemC_FIND_VERSION})
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(SystemC
                                      FOUND_VAR SystemC_FOUND
                                      REQUIRED_VARS
                                      SystemC_LIBRARY
                                      SystemC_INCLUDE_DIR
                                      VERSION_VAR SystemC_VERSION
                                      )
    if(SystemC_FOUND)
        set(SystemC_LIBRARIES ${SystemC_LIBRARY})
        set(SystemC_INCLUDE_DIRS ${SystemC_INCLUDE_DIR})
        #set(SystemC_DEFINITIONS ${PC_SystemC_CFLAGS_OTHER})
    endif()
    if(SystemC_FOUND AND NOT TARGET SystemC::SystemC)
        add_library(SystemC::SystemC UNKNOWN IMPORTED)
        set_target_properties(SystemC::SystemC PROPERTIES
        IMPORTED_LOCATION "${SystemC_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS ""
        INTERFACE_INCLUDE_DIRECTORIES "${SystemC_INCLUDE_DIR}")
    endif()
endif("${PC_SYSTEMC}" STREQUAL "")
