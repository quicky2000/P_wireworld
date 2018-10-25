#!/bin/sh -f
mkdir build
cd build
mkdir wireworld
cd wireworld
cmake $QUICKY_REPOSITORY/wireworld
make
cd ..
mkdir wireworld_systemc
cd wireworld_systemc
cmake $QUICKY_REPOSITORY/wireworld_systemc
make
cd ..
mkdir wireworld_tool
cd wireworld_tool
cmake $QUICKY_REPOSITORY/wireworld_tool
make
cd ..
mkdir wireworld_computer
cd wireworld_computer
cmake $QUICKY_REPOSITORY/wireworld_computer
make
cd ..
cd ..
#EOF

