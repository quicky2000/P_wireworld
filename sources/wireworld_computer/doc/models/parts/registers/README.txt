controls.txt  : Design of part controling electron burst to select registers
controls.xml  : Description of generic cells used to define delay between electron burst
controls.conf : Configuration of generic cells used to define delay between electron burst

Usage is :
./bin/wireworld_systemc.exe wireworld_computer/doc/models/parts/registers/controls.txt --display_duration=0 --trace=1 --trace_x_origin=212 --trace_y_origin=28 --trace_width=7 --trace_height=1 --generic_file=wireworld_computer/doc/models/parts/registers/controls.xml --config_file=wireworld_computer/doc/models/parts/registers/controls.conf

Interesting cells are 212,28 and 218,28 to illustrate the delay

#EOF
