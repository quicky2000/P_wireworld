# P_wireworld

P_wireworld is the integration repository of my experiments around wireworld cellular automaton

For more information please refer to https://www.logre.eu/wiki/Projet_Wireworld

Continuous integration with [Travis-Ci](https://travis-ci.org/quicky2000/P_wireworld) : ![Build Status](https://travis-ci.org/quicky2000/P_wireworld.svg?branch=master)

## Requirements
### Library SDL1.2
  Installation on Linux:
*  __sudo apt-get update; sudo apt-get install -y libsdl1.2-dev__

  Installation on MacOS:
*  __brew update; brew install sdl__

### Library SystemC 2.3.1
*  __wget http://accellera.org/images/downloads/standards/systemc/systemc-2.3.1.tgz__
*  __tar -zxvf systemc-2.3.1.tgz__
*  __SYSTEMC_INSTALL=${MY_LOCATION}/systemc_install__
*  __export SYSTEMC_INSTALL__
*  __mkdir $SYSTEMC_INSTALL__
*  __cd systemc-2.3.1__
*  __mkdir objdir__
*  __cd objdir/__
*  __../configure --prefix=$SYSTEMC_INSTALL__
*  __make -j__
*  __make install__



## Setup project
. setup.sh

## Build project
### With quicky_tools
. build.sh

### With CMake
. build_cmake.sh

## Subtrees

Related repositories and version used to create this integration repository:

git@github.com:quicky2000/EXT_systemc.git        v0.3

git@github.com:quicky2000/EXT_xmlParser.git      v0.3

git@github.com:quicky2000/lib_bmp.git            v0.4

git@github.com:quicky2000/parameter_manager.git  v0.3

git@github.com:quicky2000/quicky_exception.git   v0.3

git@github.com:quicky2000/quicky_tools.git       v1.3

git@github.com:quicky2000/quicky_utils.git       v0.3

git@github.com:quicky2000/simple_gui.git         v0.4

git@github.com:quicky2000/wireworld.git          v1.1

git@github.com:quicky2000/wireworld_common.git   v1.1

git@github.com:quicky2000/wireworld_computer.git v1.1

git@github.com:quicky2000/wireworld_systemc.git  v1.1

git@github.com:quicky2000/wireworld_tool.git     v0.2

## Licence
Please see COPYING or LICENSE for info on the license.
