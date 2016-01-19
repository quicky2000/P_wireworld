#!/bin/sh -f
mkdir build
cd build
mkdir wireworld
cd wireworld
generate_makefile wireworld
make
cd ..
mkdir wireworld_systemc
cd wireworld_systemc
generate_makefile wireworld_systemc
make
cd ..
mkdir wireworld_tool
cd wireworld_tool
generate_makefile wireworld_tool
make
cd ..
mkdir wireworld_computer
cd wireworld_computer
generate_makefile wireworld_computer
make
cd ..
cd ..
#EOF

