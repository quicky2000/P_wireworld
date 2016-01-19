#include <iostream>
#include <cinttypes>
#include <cassert>
#include <sstream>
#include <map>

int main(int argc, char ** argv)
{
  assert(argc == 2);
  unsigned int l_register_index = atoi(argv[1]);
  
  
  int l_h_x_ref[16] = { 497, 491, 485, 479, 484, 490, 496, 502, 508, 514, 520, 526, 521, 515, 509, 503};
  int l_h_y_ref[16] = {-485,-485,-485,-486,-488,-488,-488,-488,-488,-488,-488,-486,-485,-485,-485,-485};
  int l_q_x_ref[16] = { 496, 490, 484, 479, 485, 491, 497, 503, 509, 515, 521, 525, 520, 514, 508, 502};
  int l_q_y_ref[16] = {-485,-485,-485,-487,-488,-488,-488,-488,-488,-488,-488,-485,-485,-485,-485,-485};

  std::cout << "<!-- Register " << l_register_index << " -->" << std::endl ;
  std::map<unsigned int,std::string> l_values;
  for(unsigned int l_bit_index = 0;l_bit_index < 16 ; ++ l_bit_index)
    {
      int l_h_x = -6 * l_register_index + l_h_x_ref[l_bit_index];
      int l_h_y = 6 * l_register_index + l_h_y_ref[l_bit_index];
      int l_q_x = -6 * l_register_index + l_q_x_ref[l_bit_index];
      int l_q_y = 6 * l_register_index + l_q_y_ref[l_bit_index];
      unsigned int l_real_index = ( l_bit_index + 34 - l_register_index) % 16;
      std::stringstream l_stream;
      l_stream << "<item name=\"R" << l_register_index << "[" << l_real_index << "]\" e_head=\"" << l_h_x << "," << l_h_y << "\" e_queue=\"" << l_q_x << "," << l_q_y << "\"/>" << std::endl ;
      l_values.insert( std::map<unsigned int,std::string>::value_type(l_real_index,l_stream.str()));
    }
  for(auto l_iter : l_values)
    {
      std::cout << l_iter.second;
    }
  /*  
<!-- Register 18 -->
<item name="R18[15]" e_head="395,-377" e_queue="394,-377"/>
<item name="R19[14]" e_head="389,-371" e_queue="388,-371"/>


<item name="R18[0]" e_head="389,-377" e_queue="388,-377"/>
<item name="R19[15]" e_head="383,-371" e_queue="382,-371"/>

<item name="R18[1]" e_head="383,-377" e_queue="382,-377"/>
<item name="R19[0]" e_head="377,-371" e_queue="376,-371"/>

<item name="R18[2]" e_head="377,-377" e_queue="376,-377"/>
<item name="R19[1]" e_head="371,-371" e_queue="370,-371"/>

<item name="R18[3]" e_head="371,-378" e_queue="371,-379"/>
<item name="R19[2]" e_head="365,-372" e_queue="365,-373"/>

<item name="R18[4]" e_head="376,-380" e_queue="377,-380"/>
<item name="R19[3]" e_head="370,-374" e_queue="371,-374"/>

<item name="R18[5]" e_head="382,-380" e_queue="383,-380"/>
<item name="R19[4]" e_head="376,-374" e_queue="377,-374"/>

<item name="R18[6]" e_head="388,-380" e_queue="389,-380"/>
<item name="R19[5]" e_head="382,-374" e_queue="383,-374"/>

<item name="R18[7]" e_head="394,-380" e_queue="395,-380"/>
<item name="R19[6]" e_head="388,-374" e_queue="389,-374"/>

<item name="R18[8]" e_head="400,-380" e_queue="401,-380"/>
<item name="R19[7]" e_head="394,-374" e_queue="395,-374"/>

<item name="R18[9]" e_head="406,-380" e_queue="407,-380"/>
<item name="R19[8]" e_head="400,-374" e_queue="401,-374"/>

<item name="R18[10]" e_head="412,-380" e_queue="413,-380"/>
<item name="R19[9]" e_head="406,-374" e_queue="407,-374"/>

<item name="R18[11]" e_head="418,-378" e_queue="417,-377"/>
<item name="R19[10]" e_head="412,-372" e_queue="411,-371"/>

<item name="R18[12]" e_head="413,-377" e_queue="412,-377"/>
<item name="R19[11]" e_head="407,-371" e_queue="406,-371"/>

<item name="R18[13]" e_head="407,-377" e_queue="406,-377"/>
<item name="R19[12]" e_head="401,-371" e_queue="400,-371"/>

<item name="R18[14]" e_head="401,-377" e_queue="400,-377"/>
<item name="R19[13]" e_head="395,-371" e_queue="394,-371"/>

  */
  return 0;

}
