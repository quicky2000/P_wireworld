/*
  This file is part of wireworld_computer
  Copyright (C) 2010  Julien Thevenon ( julien_thevenon at yahoo.fr )

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
#include "wireworld_computer.h"
#include "simple_register.h"
#include "display_register.h"
#include "rotate_left_register.h"
#include "rotate_right_register.h"
#include "bitwise_and_not_register.h"
#include "return_zero_register.h"
#include "conditional_register.h"
#include "sum_register.h"
#include "sum_operand_register.h"
#include "not_register.h"
#include "quicky_exception.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
using namespace std;

namespace wireworld_computer
{
  //----------------------------------------------------------------------------
  wireworld_computer::wireworld_computer(const wireworld_computer_utils::t_register_informations & p_informations,
					 const std::string & p_output_file,
					 bool p_detailled_display,
					 const uint32_t & p_instruction_delay):
    m_instruction_delay(p_instruction_delay)
  {

    //Creating registers
    m_registers[0] = new display_register(p_detailled_display);
    for(uint32_t l_index = 1; l_index <= 52 ; ++l_index)
      {
	m_registers[l_index] = new simple_register();
      }
    simple_register * const l_reg_53 = new simple_register();
    simple_register * const l_reg_54 = new simple_register();
    m_registers[53] = new bitwise_and_not_register(l_reg_53,l_reg_54);
    m_registers[54] = new bitwise_and_not_register(l_reg_54,l_reg_53);
    return_zero_register * const l_reg_55 = new return_zero_register();
    return_zero_register * const l_reg_57 = new return_zero_register();
    m_registers[55] = l_reg_55;
    m_registers[56]= new conditional_register(l_reg_55,l_reg_57);
    m_registers[57] = l_reg_57;
    m_registers[58] = new rotate_right_register();
    m_registers[59] = new rotate_left_register();
    sum_operand_register * l_sum_operand_register = new sum_operand_register();
    m_registers[60] = l_sum_operand_register;
    sum_register* l_sum_register = new sum_register(m_registers[60]);
    m_registers[61] = l_sum_register;
    l_sum_operand_register->set_sum_register(*l_sum_register);
    m_registers[62] = new not_register();
    m_registers[63] = new simple_register();

    // Load code in registers
    unsigned int l_max_label_size = 0;
    for(auto l_register_iter:p_informations)
      {
	unsigned int l_register_id = l_register_iter.first;
	if(l_register_id > 63)
	  {
	    std::stringstream l_stream;
	    l_stream << l_register_id;
	    throw quicky_exception::quicky_logic_exception("Register Id " + l_stream.str() + " is greater then max register id 63",__LINE__,__FILE__);
	  }
	if(l_register_iter.second.get_label().size() > l_max_label_size)
	  {
	    l_max_label_size = l_register_iter.second.get_label().size();
	  }
	m_registers[l_register_id]->write(l_register_iter.second.get_initial_value());
      }

    // Pretty print of software and generation of computer configuration
    ofstream l_output_file;
    if("" != p_output_file)
      {
	l_output_file.open(p_output_file.c_str());
	if(!l_output_file.is_open())
	  {
	    throw quicky_exception::quicky_logic_exception("Unable to create file \""+p_output_file+"\"",__LINE__,__FILE__);
	  }
      }
    std::string l_empty_label = l_max_label_size ?  std::string(4 + l_max_label_size, ' ') : "";
    for(unsigned int l_index=0 ; l_index < 64 ; ++l_index)
      {
	std::stringstream l_line_stream;
	l_line_stream << setfill(' ') << setw(2) << l_index << " : ";
	wireworld_computer_utils::t_register_informations::const_iterator l_info_iter = p_informations.find(l_index);
	unsigned int l_initial_value = 0;
	if(p_informations.end() != l_info_iter)
	  {
	    l_initial_value = l_info_iter->second.get_initial_value();
	    if("" != l_info_iter->second.get_label())
	      {
		l_line_stream << "<" << l_info_iter->second.get_label() << ">";
		if(l_info_iter->second.get_label().size() < l_max_label_size)
		  {
		    l_line_stream << std::string(l_max_label_size - l_info_iter->second.get_label().size(),' ');
		  }
		l_line_stream << ": ";
	      }
	    else
	      {
		l_line_stream << l_empty_label;
	      }
	    std::stringstream l_stream;
	    if(l_info_iter->second.is_instruction())
	      {
		uint16_t l_destination = decodeDestination(l_initial_value);
		std::stringstream l_dest_stream;
		l_dest_stream << l_destination;
		std::string l_dest_str = l_dest_stream.str();
		if(l_dest_str.size() != 2)
		  {
		    l_dest_str += ' ';
		  }
		uint16_t l_source = decodeSource(l_initial_value);
		l_stream << "MOV R" << l_dest_str << ", R" << l_source;
	      }
	    else
	      {
		l_stream << "0x" << setfill('0') << setw(4) << hex << l_initial_value << dec;
	      }
	    std::string l_content = l_stream.str();
	    l_line_stream << l_content;
	    if("" != l_info_iter->second.get_comment())
	      {
		if(l_content.size() < 12)
		  {
		    l_line_stream << std::string(12 - l_content.size(),' ');
		  }
		l_line_stream << " ; " << l_info_iter->second.get_comment();
	      }
	  }
	else
	  {
	    if(l_max_label_size)
	      {
		l_line_stream << l_empty_label;
	      }
	    if((l_index >= 1 && l_index <= 52) || 60 == l_index || 63 == l_index)
	      {
		l_line_stream << "0x" << setfill('0') << setw(4) << hex << m_registers[l_index]->read() << dec;
	      }
	    else
	      {
		l_line_stream << "SPECIAL REG";
	      }
	  }
	if(l_output_file.is_open())
	  {
	    l_output_file << "# Register " << l_line_stream.str() << std::endl ;
	    for(unsigned int l_bit_index = 0 ; l_bit_index < 16 ; ++l_bit_index)
	      {
		l_output_file << "R" << l_index << "[" << l_bit_index << "]:" << (l_initial_value & 0x1) << std::endl ;
		l_initial_value = l_initial_value >> 1;
	      }
		l_output_file << std::endl;
	  }
	std::cout << l_line_stream.str() << std::endl ;
      }
    if(l_output_file.is_open())
      {
	l_output_file << "#EOF" << std::endl;
	l_output_file.close();
      }
  }

  //----------------------------------------------------------------------------
  uint8_t wireworld_computer::decodeDestination(uint16_t p_instr)
  {
    return (0x3F00 & p_instr) >> 8;
  }

  //----------------------------------------------------------------------------
  uint8_t wireworld_computer::decodeSource(uint16_t p_instr)
  {
    return 0x3F & p_instr;
  }

  //----------------------------------------------------------------------------
  uint16_t wireworld_computer::getInstruction(void)
  {
    cout << "PC value :" ;
    uint16_t l_pc = m_registers[63]->read();
    cout << "=> PC = 0x" << hex << l_pc << dec << endl ;
    m_registers[63]->write(l_pc+1);
    return m_registers[l_pc]->read();
  }

  //----------------------------------------------------------------------------
  void wireworld_computer::execInstruction(uint16_t p_instr)
  {
    cout << "=> Instruction = 0x" << hex << p_instr << dec << endl ;
    uint16_t l_destination = decodeDestination(p_instr);
    uint16_t l_source = decodeSource(p_instr);
    cout << "=> MOV R" << l_destination << ", R" << l_source <<  endl ;
    cout << "R" << l_source << " => " ;
    uint16_t l_value = m_registers[l_source]->read();
    cout << "0x" << hex << l_value << dec << " => " ;
    cout << "R" << l_destination << endl ;
    m_registers[l_destination]->write(l_value);
  }

  //----------------------------------------------------------------------------
  void wireworld_computer::run(void)
  {
    cout << "Start running" << endl ;
    uint32_t l_nb_cycle = 0;
    uint16_t l_instr = getInstruction();
    while(1)
      {
	cout << "***** Starting cycle " << l_nb_cycle << "*****" << endl ;
	uint16_t l_new_instr = getInstruction();
	execInstruction(l_instr);
	l_instr = l_new_instr;
	usleep(m_instruction_delay);
	++l_nb_cycle;
      }
    cout << "Run finished" << endl ;
  }

}
//EOF
