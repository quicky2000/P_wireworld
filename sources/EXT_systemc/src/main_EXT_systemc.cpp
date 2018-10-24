/*    This file is part of EXT_systemc
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
#ifdef EXT_SYSTEMC_SELF_TEST

#include "systemc.h"
#include <iostream>

class top: public sc_module
{
  public:
    SC_HAS_PROCESS(top);
    top(const sc_module_name & p_name):
            sc_module(p_name),
            m_input0("input0"),
            m_input1("input1"),
            m_output("output")
    {
        SC_THREAD(generate_input0);
        SC_THREAD(generate_input1);
        SC_THREAD(control_simu);

        SC_THREAD(compute);
        sensitive << m_input0;
        sensitive << m_input1;
    }

    void control_simu(void)
    {
        wait(80,SC_NS);
        sc_stop();
    }
    void compute(void)
    {
        while (1)
        {
            std::cout << sc_time_stamp() << "\tInput0 : " << m_input0 << "\tInput1 : " << m_input1 << std::endl;
            bool l_output = m_input0 & m_input1;
            std::cout << "==> output : " << l_output << std::endl;
            m_output.write(l_output);
            wait();
        }
    }

    void generate_input0(void)
    {
        for(unsigned int l_i =0;
            l_i < 4;
            ++l_i)
        {
            m_input0.write(false);
            wait(10,
                 SC_NS
                );
            m_input0.write(true);
            wait(10,
                 SC_NS
                );
        }
    }

    void generate_input1(void)
    {
        for(unsigned int l_i =0;
            l_i < 2;
            ++l_i)
        {
            m_input1.write(false);
            wait(20,
                 SC_NS
                );
            m_input1.write(true);
            wait(20,
                 SC_NS
                );
        }
    }
  private:
    sc_signal<bool> m_input0;
    sc_signal<bool> m_input1;
    sc_signal<bool> m_output;
};

//------------------------------------------------------------------------------
int sc_main(int argc,char ** argv)
{
    top l_top("top");
    std::cout << "Starting simulation" << std::endl;
    sc_start();
    return 0;
}
#endif // EXT_SYSTEMC_SELF_TEST
//EOF
