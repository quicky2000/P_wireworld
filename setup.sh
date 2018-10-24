#!/bin/sh
chmod a+x sources/quicky_tools/bin/*
QUICKY_REPOSITORY=$PWD/sources
export QUICKY_REPOSITORY
cd $QUICKY_REPOSITORY/quicky_tools/setup
. setup.sh
cd $QUICKY_REPOSITORY/../

# SystemC part
SYSTEMC_INSTALL=/usr/local/systemc-2.3.1
export SYSTEMC_INSTALL
LD_LIBRARY_PATH=$SYSTEMC_INSTALL/lib-linux64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
#EOF
