/*    This file is part of quicky_utils
      Copyright (C) 2018  Julien Thevenon ( julien_thevenon at yahoo.fr )

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

#ifndef QUICKY_UTILS_TEST_FRACT_H
#define QUICKY_UTILS_TEST_FRACT_H

#include "safe_types.h"
#include "ext_int.h"
#include "fract.h"
#include <inttypes.h>
#include <iostream>
#include "quicky_test.h"

namespace quicky_utils
{
    template <unsigned int NB>
    void
    display_NB()
    {
        std::cout << NB << std::endl;
    }

    bool test_fract_normal()
    {
        bool l_ok = true;
        // PGCD
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PGCD(1071, 1029),21, "PGCD(1071,1029)");
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PGCD(1029, 1071),21, "PGCD(1029,1071)");
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PGCD(60, 168),12, "PGCD(60,168)");
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PGCD(168, 60),12, "PGCD(168,60)");

        // PPCM
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PPCM(60, 168), 840, "PPCM(60,168)");
        l_ok &= quicky_test::check_expected<typename quicky_utils::fract<uint32_t>::t_coef_den>(quicky_utils::fract<uint32_t>::PPCM(168, 60), 840, "PPCM(168,60)");
        return l_ok;
    }

    template <typename FRACT_INTERNAL_TYPE>
    bool
    test_fract_generic()
    {
        typedef typename quicky_utils::fract<FRACT_INTERNAL_TYPE>::t_coef_den t_coef_den;
        typedef typename quicky_utils::fract<FRACT_INTERNAL_TYPE>::t_coef_num t_coef_num;
        typedef typename quicky_utils::fract<FRACT_INTERNAL_TYPE> t_fract;
        std::cout << "Testing " << quicky_utils::type_string<t_fract>::name() << std::endl;
        bool l_ok = true;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "- PGCD" << std::endl;
        std::cout << "---------------------------------------" << std::endl;

        auto l_pos_num = (t_coef_den) (unsigned int)3;
        auto l_neg_num = (t_coef_num)-3;
        auto l_pos_den = (t_coef_den) (unsigned int)6;
        auto l_neg_den = (t_coef_num)-6;

	    l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PGCD(l_pos_num, l_pos_den), (t_coef_den)(unsigned int)3, "PGCD( 3, 6)");
	    l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PGCD(l_neg_num, l_pos_den), (t_coef_den)(unsigned int)3, "PGCD(-3, 6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PGCD(l_pos_num, l_neg_den), (t_coef_den)(unsigned int)3, "PGCD( 3,-6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PGCD(l_neg_num, l_neg_den), (t_coef_den)(unsigned int)3, "PGCD(-3,-6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PGCD((t_coef_den)(unsigned int)6
                                                                     ,(t_coef_den)(unsigned int)9
                                                                     )
                                                       ,(t_coef_den)(unsigned int)3
                                                       ,"PGCD(6,9)"
                                                       );

        std::cout << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "- PPCM" << std::endl;
        std::cout << "---------------------------------------" << std::endl;

        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PPCM(l_pos_num, l_pos_den), (t_coef_den)(unsigned int)6, "PPCM( 3, 6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PPCM(l_neg_num, l_pos_den), (t_coef_den)(unsigned int)6, "PPCM(-3, 6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PPCM(l_pos_num, l_neg_den), (t_coef_den)(unsigned int)6, "PPCM( 3,-6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PPCM(l_neg_num, l_neg_den), (t_coef_den)(unsigned int)6, "PPCM(-3,-6)");
        l_ok &= quicky_test::check_expected<t_coef_den>(t_fract::PPCM((t_coef_den)(unsigned int)6
                                                                     ,(t_coef_den)(unsigned int)9
                                                                     )
                                                       , (t_coef_den)(unsigned int)18
                                                       , "PPCM(6,9)"
                                                       );

        std::cout << "---------------------------------------" << std::endl;

        l_ok &= quicky_test::check_expected(t_fract((t_coef_num) -3, (t_coef_den)(unsigned int)1) * t_fract((t_coef_den)(unsigned int)7, (t_coef_den)(unsigned int)1), t_fract((t_coef_num)-21), "-3/1 * 7/1 == -21");
        l_ok &= quicky_test::check_expected(t_fract((t_coef_num)-21, (t_coef_den)(unsigned int)1) / t_fract((t_coef_den)(unsigned int)6, (t_coef_den)(unsigned int)1), t_fract((t_coef_num)-7, (t_coef_den)(unsigned int)2), "-21/1 / 6/1 == -7/2");
        l_ok &= quicky_test::check_expected(t_fract((t_coef_num) -4, (t_coef_den)(unsigned int)1) - t_fract((t_coef_num)-21, (t_coef_den)(unsigned int)6), t_fract((t_coef_num)-1, (t_coef_den)(unsigned int)2), "-4/1 - (-21/6) == -1/2");

        l_ok &= quicky_test::check_expected(t_fract((t_coef_num)-1, (t_coef_num)-2).to_double(),  0.5, "(num,num) constructor");
        l_ok &= quicky_test::check_expected(t_fract((t_coef_num)-1, (t_coef_den)(unsigned int) 2).to_double(), -0.5, "(num,den) constructor");
        l_ok &= quicky_test::check_expected(t_fract((t_coef_den)(unsigned int) 1, (t_coef_num)-2).to_double(), -0.5, "(den,num) constructor");
        l_ok &= quicky_test::check_expected(t_fract((t_coef_den)(unsigned int) 1, (t_coef_den)(unsigned int) 2).to_double(),  0.5, "(den,den) constructor");

        t_fract l_nb1((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)2);
        t_fract l_nb2((t_coef_num)2);
        t_fract l_nb3((t_coef_den)(unsigned int)10, (t_coef_den)(unsigned int)2);
        l_ok &= quicky_test::check_expected(l_nb3, t_fract((t_coef_num)5), "10/2 == 5");
        std::cout << l_nb1 << std::endl;
        std::cout << l_nb2 << std::endl;
        std::cout << l_nb3 << std::endl;

        t_fract l_a((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)3);
        t_fract l_b((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)4);

        l_ok &= quicky_test::check_expected(l_a + l_b, t_fract((t_coef_den)(unsigned int)7, (t_coef_den)(unsigned int)12),std::to_string(l_a) + " + " + std::to_string(l_b));
        l_ok &= quicky_test::check_expected(l_a - l_b, t_fract((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)12),std::to_string(l_a) + " - " + std::to_string(l_b));
        l_ok &= quicky_test::check_expected(l_a * l_b, t_fract((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)12),std::to_string(l_a) + " * " + std::to_string(l_b));
        l_ok &= quicky_test::check_expected(l_a / l_b, t_fract((t_coef_den)(unsigned int)4, (t_coef_den)(unsigned int)3),std::to_string(l_a) + " / " + std::to_string(l_b));
        l_ok &= quicky_test::check_expected(1   + l_a, t_fract((t_coef_den)(unsigned int)4, (t_coef_den)(unsigned int)3), "1 + " + std::to_string(l_a));

        t_fract l_x((t_coef_den)(unsigned int) 1, (t_coef_den)(unsigned int) 2);
        t_fract l_x2(l_x);
        t_fract l_y((t_coef_den)(unsigned int) 2, (t_coef_num)-3);
        t_fract l_y2(l_y);
        t_fract l_z((t_coef_num)-3, (t_coef_den)(unsigned int) 5);
        t_fract l_z2(l_z);
        t_fract l_x_bis((t_coef_num)-1, (t_coef_num)-2);
        t_fract l_x_bis2(l_x_bis);
        t_fract l_y_bis((t_coef_num)-2, (t_coef_den)(unsigned int)3);
        t_fract l_y_bis2(l_y_bis);
        t_fract l_z_bis((t_coef_den)(unsigned int) 3, (t_coef_num)-5);
        t_fract l_z_bis2(l_z_bis);

        // Check equality independantly of - position ( num or den)
        l_ok &= quicky_test::check_expected(l_x == l_x_bis, true, std::to_string(l_x) + " == " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y == l_y_bis, true, std::to_string(l_y) + " == " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z == l_z_bis, true, std::to_string(l_z) + " == " + std::to_string(l_z_bis));
        l_ok &= quicky_test::check_expected(l_x != l_y, true, std::to_string(l_x) + " != " + std::to_string(l_y));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x + l_x, t_fract((t_coef_num)1), std::to_string(l_x) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x + l_y, t_fract((t_coef_num)-1, (t_coef_den)(unsigned int)6), std::to_string(l_x) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x + l_z, t_fract((t_coef_num)-1, (t_coef_den)(unsigned int)10), std::to_string(l_x) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x + l_x_bis, t_fract((t_coef_num)1), std::to_string(l_x) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x + l_y_bis, t_fract((t_coef_num)-1, (t_coef_den)(unsigned int)6), std::to_string(l_x) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x + l_z_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_x) + " + " + std::to_string(l_z_bis));


        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y + l_x, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y + l_y, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y + l_z, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_y) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y + l_x_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y + l_y_bis, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y + l_z_bis, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_y) + " + " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z + l_x, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z + l_y, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_z) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z + l_z, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z + l_x_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z + l_y_bis, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_z) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z + l_z_bis, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " + " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x_bis + l_x, t_fract((t_coef_num)1), std::to_string(l_x_bis) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x_bis + l_y, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x_bis + l_z, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x_bis + l_x_bis, t_fract((t_coef_num)1), std::to_string(l_x_bis) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x_bis + l_y_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x_bis + l_z_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " + " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y_bis + l_x, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_y_bis) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y_bis + l_y, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y_bis + l_z, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_y_bis) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y_bis + l_x_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)6), std::to_string(l_y_bis) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y_bis + l_y_bis, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y_bis + l_z_bis, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_y_bis) + " + " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z_bis + l_x, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " + " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z_bis + l_y, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_z_bis) + " + " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z_bis + l_z, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " + " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z_bis + l_x_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " + " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z_bis + l_y_bis, t_fract((t_coef_num)-19,(t_coef_den)(unsigned int)15), std::to_string(l_z_bis) + " + " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z_bis + l_z_bis, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " + " + std::to_string(l_z_bis));

        //----------------------------------------
        // Operator -
        //----------------------------------------
        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x - l_x2, t_fract((t_coef_num)0), std::to_string(l_x) + " - " + std::to_string(l_x2));
        l_ok &= quicky_test::check_expected(l_x - l_y, t_fract((t_coef_den)(unsigned int)7,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " - " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x - l_z, t_fract((t_coef_den)(unsigned int)11,(t_coef_den)(unsigned int)10), std::to_string(l_x) + " - " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x - l_x_bis, t_fract((t_coef_num)0), std::to_string(l_x) + " - " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x - l_y_bis, t_fract((t_coef_den)(unsigned int)7,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " - " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x - l_z_bis, t_fract((t_coef_den)(unsigned int)11,(t_coef_den)(unsigned int)10), std::to_string(l_x) + " - " + std::to_string(l_z_bis));


        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y - l_x, t_fract((t_coef_num)-7,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " - " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y - l_y2, t_fract((t_coef_num)0), std::to_string(l_y) + " - " + std::to_string(l_y2));
        l_ok &= quicky_test::check_expected(l_y - l_z, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)15), std::to_string(l_y) + " - " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y - l_x_bis, t_fract((t_coef_num)-7,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " - " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y - l_y_bis, t_fract((t_coef_num)0), std::to_string(l_y) + " - " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y - l_z_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)15), std::to_string(l_y) + " - " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z - l_x, t_fract((t_coef_num)-11,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " - " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z - l_y, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)15), std::to_string(l_z) + " - " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z - l_z2, t_fract((t_coef_num)0), std::to_string(l_z) + " - " + std::to_string(l_z2));
        l_ok &= quicky_test::check_expected(l_z - l_x_bis, t_fract((t_coef_num)-11,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " - " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z - l_y_bis, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)15), std::to_string(l_z) + " - " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z - l_z_bis, t_fract((t_coef_num)0), std::to_string(l_z) + " - " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x_bis - l_x, t_fract((t_coef_num)0), std::to_string(l_x_bis) + " - " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x_bis - l_y, t_fract((t_coef_den)(unsigned int)7,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " - " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x_bis - l_z, t_fract((t_coef_den)(unsigned int)11,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " - " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x_bis - l_x_bis2, t_fract((t_coef_num)0), std::to_string(l_x_bis) + " - " + std::to_string(l_x_bis2));
        l_ok &= quicky_test::check_expected(l_x_bis - l_y_bis, t_fract((t_coef_den)(unsigned int)7,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " - " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x_bis - l_z_bis, t_fract((t_coef_den)(unsigned int)11,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " - " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y_bis - l_x, t_fract((t_coef_num)-7,(t_coef_den)(unsigned int)6), std::to_string(l_y_bis) + " - " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y_bis - l_y, t_fract((t_coef_num)0), std::to_string(l_y_bis) + " - " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y_bis - l_z, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)15), std::to_string(l_y_bis) + " - " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y_bis - l_x_bis, t_fract((t_coef_num)-7,(t_coef_den)(unsigned int)6), std::to_string(l_y_bis) + " - " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y_bis - l_y_bis2, t_fract((t_coef_num)0), std::to_string(l_y_bis) + " - " + std::to_string(l_y_bis2));
        l_ok &= quicky_test::check_expected(l_y_bis - l_z_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)15), std::to_string(l_y_bis) + " - " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z_bis - l_x, t_fract((t_coef_num)-11,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " - " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z_bis - l_y, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)15), std::to_string(l_z_bis) + " - " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z_bis - l_z, t_fract((t_coef_num)0), std::to_string(l_z_bis) + " - " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z_bis - l_x_bis, t_fract((t_coef_num)-11,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " - " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z_bis - l_y_bis, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)15), std::to_string(l_z_bis) + " - " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z_bis - l_z_bis2, t_fract((t_coef_num)0), std::to_string(l_z_bis) + " - " + std::to_string(l_z_bis2));


        //----------------------------------------
        // Operator *
        //----------------------------------------
        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x * l_x, t_fract((t_coef_num)1,(t_coef_den)(unsigned int)4), std::to_string(l_x) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x * l_y, t_fract((t_coef_num)-2,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x * l_z, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_x) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x * l_x_bis, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)4), std::to_string(l_x) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x * l_y_bis, t_fract((t_coef_num)-2,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x * l_z_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_x) + " * " + std::to_string(l_z_bis));


        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y * l_x, t_fract((t_coef_num)-2,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y * l_y, t_fract((t_coef_den)(unsigned int)4,(t_coef_den)(unsigned int)9), std::to_string(l_y) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y * l_z, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_y) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y * l_x_bis, t_fract((t_coef_num)-2,(t_coef_den)(unsigned int)6), std::to_string(l_y) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y * l_y_bis, t_fract((t_coef_den)(unsigned int)4,(t_coef_den)(unsigned int)9), std::to_string(l_y) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y * l_z_bis, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_y) + " * " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z * l_x, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z * l_y, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z * l_z, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)25), std::to_string(l_z) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z * l_x_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z * l_y_bis, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z * l_z_bis, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)25), std::to_string(l_z) + " * " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x_bis * l_x, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)4), std::to_string(l_x_bis) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x_bis * l_y, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)3), std::to_string(l_x_bis) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x_bis * l_z, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x_bis * l_x_bis, t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)4), std::to_string(l_x_bis) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x_bis * l_y_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)3), std::to_string(l_x_bis) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x_bis * l_z_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_x_bis) + " * " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y_bis * l_x, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y_bis * l_y, t_fract((t_coef_den)(unsigned int)4,(t_coef_den)(unsigned int)9), std::to_string(l_y_bis) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y_bis * l_z, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_y_bis) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y_bis * l_x_bis, t_fract((t_coef_num)-1,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y_bis * l_y_bis, t_fract((t_coef_den)(unsigned int)4,(t_coef_den)(unsigned int)9), std::to_string(l_y_bis) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y_bis * l_z_bis, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_y_bis) + " * " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z_bis * l_x, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " * " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z_bis * l_y, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " * " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z_bis * l_z, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)25), std::to_string(l_z_bis) + " * " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z_bis * l_x_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " * " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z_bis * l_y_bis, t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " * " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z_bis * l_z_bis, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)25), std::to_string(l_z_bis) + " * " + std::to_string(l_z_bis));

        //----------------------------------------
        // Operator /
        //----------------------------------------
        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x / l_x2, t_fract((t_coef_num)1), std::to_string(l_x) + " / " + std::to_string(l_x2));
        l_ok &= quicky_test::check_expected(l_x / l_y, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)4), std::to_string(l_x) + " / " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x / l_z, t_fract((t_coef_num)-5,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " / " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x / l_x_bis, t_fract((t_coef_num)1), std::to_string(l_x) + " / " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_x / l_y_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)4), std::to_string(l_x) + " / " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x / l_z_bis, t_fract((t_coef_num)-5,(t_coef_den)(unsigned int)6), std::to_string(l_x) + " / " + std::to_string(l_z_bis));


        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y / l_x, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y) + " / " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y / l_y2, t_fract((t_coef_num)1), std::to_string(l_y) + " / " + std::to_string(l_y2));
        l_ok &= quicky_test::check_expected(l_y / l_z, t_fract((t_coef_den)(unsigned int)10,(t_coef_den)(unsigned int)9), std::to_string(l_y) + " / " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y / l_x_bis, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y) + " / " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y / l_y_bis, t_fract((t_coef_num)1), std::to_string(l_y) + " / " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_y / l_z_bis, t_fract((t_coef_den)(unsigned int)10,(t_coef_den)(unsigned int)9), std::to_string(l_y) + " / " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z / l_x, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " / " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z / l_y, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " / " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z / l_z2, t_fract((t_coef_num)1), std::to_string(l_z) + " / " + std::to_string(l_z2));
        l_ok &= quicky_test::check_expected(l_z / l_x_bis, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z) + " / " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z / l_y_bis, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)10), std::to_string(l_z) + " / " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z / l_z_bis, t_fract((t_coef_num)1), std::to_string(l_z) + " / " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_x_bis / l_x, t_fract((t_coef_num)1), std::to_string(l_x_bis) + " / " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x_bis / l_y, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)4), std::to_string(l_x_bis) + " / " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x_bis / l_z, t_fract((t_coef_num)-5,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " / " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_x_bis / l_x_bis2, t_fract((t_coef_num)1), std::to_string(l_x_bis) + " / " + std::to_string(l_x_bis2));
        l_ok &= quicky_test::check_expected(l_x_bis / l_y_bis, t_fract((t_coef_num)-3,(t_coef_den)(unsigned int)4), std::to_string(l_x_bis) + " / " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_x_bis / l_z_bis, t_fract((t_coef_num)-5,(t_coef_den)(unsigned int)6), std::to_string(l_x_bis) + " / " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_y_bis / l_x, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " / " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_y_bis / l_y, t_fract((t_coef_num)1), std::to_string(l_y_bis) + " / " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_y_bis / l_z, t_fract((t_coef_den)(unsigned int)10,(t_coef_den)(unsigned int)9), std::to_string(l_y_bis) + " / " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_y_bis / l_x_bis, t_fract((t_coef_num)-4,(t_coef_den)(unsigned int)3), std::to_string(l_y_bis) + " / " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_y_bis / l_y_bis2, t_fract((t_coef_num)1), std::to_string(l_y_bis) + " / " + std::to_string(l_y_bis2));
        l_ok &= quicky_test::check_expected(l_y_bis / l_z_bis, t_fract((t_coef_den)(unsigned int)10,(t_coef_den)(unsigned int)9), std::to_string(l_y_bis) + " / " + std::to_string(l_z_bis));

        //------------------------------------------------------------------------
        l_ok &= quicky_test::check_expected(l_z_bis / l_x, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " / " + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_z_bis / l_y, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " / " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_z_bis / l_z, t_fract((t_coef_num)1), std::to_string(l_z_bis) + " / " + std::to_string(l_z));
        l_ok &= quicky_test::check_expected(l_z_bis / l_x_bis, t_fract((t_coef_num)-6,(t_coef_den)(unsigned int)5), std::to_string(l_z_bis) + " / " + std::to_string(l_x_bis));
        l_ok &= quicky_test::check_expected(l_z_bis / l_y_bis, t_fract((t_coef_den)(unsigned int)9,(t_coef_den)(unsigned int)10), std::to_string(l_z_bis) + " / " + std::to_string(l_y_bis));
        l_ok &= quicky_test::check_expected(l_z_bis / l_z_bis2, t_fract((t_coef_num)1), std::to_string(l_z_bis) + " / " + std::to_string(l_z_bis2));

        std::cout << "Operator ++" << std::endl;
        l_ok &= quicky_test::check_expected(l_x, t_fract((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)2), "l_x = 1/2");
        ++l_x;
        l_ok &= quicky_test::check_expected(l_x, t_fract((t_coef_den)(unsigned int)3, (t_coef_den)(unsigned int)2), "l_x = 3/2");
        l_x++;
        l_ok &= quicky_test::check_expected(l_x, t_fract((t_coef_den)(unsigned int)5, (t_coef_den)(unsigned int)2), "l_x = 5/2");
        std::cout << "Operator --" << std::endl;
        --l_x;
        l_ok &= quicky_test::check_expected(l_x, t_fract((t_coef_den)(unsigned int)3, (t_coef_den)(unsigned int)2), "l_x = 3/2");
        l_x--;
        l_ok &= quicky_test::check_expected(l_x, t_fract((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)2), "l_x = 1/2");

        t_fract l_zero((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)2);
        assert(l_zero);
        l_zero -= t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)2);
        assert(!l_zero);

        l_x = t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)2);
        l_y = t_fract((t_coef_den)(unsigned int)2,(t_coef_den)(unsigned int)5);
        l_ok &= quicky_test::check_expected(l_x < l_y, false, std::to_string(l_x) + " < " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x > l_y, true, std::to_string(l_x) + " > " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x <= l_y, false, std::to_string(l_x) + " <= " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x >= l_y, true, std::to_string(l_x) + " >= " + std::to_string(l_y));
        l_y = t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)5);
        l_ok &= quicky_test::check_expected(l_x != l_y, true, std::to_string(l_x) + " != " + std::to_string(l_y));
        l_ok &= quicky_test::check_expected(l_x == l_y, false, std::to_string(l_x) + " == " + std::to_string(l_y));


        l_y = -t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)5);
        l_ok &= quicky_test::check_expected(l_y, t_fract((t_coef_num)-1, (t_coef_den)(unsigned int)5), "l_y = -1/5");
        l_y = +t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)5);
        l_ok &= quicky_test::check_expected(l_y, t_fract((t_coef_den)(unsigned int)1, (t_coef_den)(unsigned int)5), "l_y = 1/5");
        l_y += (t_fract)((t_coef_num)3);
        l_ok &= quicky_test::check_expected(l_y, t_fract((t_coef_den)(unsigned int)16, (t_coef_den)(unsigned int)5), "l_y = 16/5");

        l_ok &= quicky_test::check_expected(l_x < 2, true, std::to_string(l_x) + " < 2");
        l_ok &= quicky_test::check_expected(l_x <= 2, true, std::to_string(l_x) + " <= 2");
        l_ok &= quicky_test::check_expected(l_x > 2, false, std::to_string(l_x) + " > 2");
        l_ok &= quicky_test::check_expected(l_x >= 2, false, std::to_string(l_x) + " >= 2");

        /* Test for GCC > 4.9.4 */
#if GCC_VERSION >= 40904
        display_NB<quicky_utils::fract<uint32_t>::PGCD(20,15,nullptr)>();
        display_NB<quicky_utils::fract<uint32_t>::PPCM(20,15,nullptr)>();
#endif // GCC_VERSION

        l_ok &= quicky_test::check_expected(1 != l_x, true, std::string("1 != ") + std::to_string(l_x));
        l_ok &= quicky_test::check_expected(l_x != 1, true, std::to_string(l_x) + std::string(" != 1"));

        std::cout << "---------------------------------------" << std::endl;
        std::cout << "- to_float and to double" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        l_a = t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)2);
        l_b = t_fract((t_coef_den)(unsigned int)1,(t_coef_den)(unsigned int)3);
        l_ok &= quicky_test::check_expected(l_a.to_float(), 1.0f / 2.0f, std::to_string(l_a) + " to float");
        l_ok &= quicky_test::check_expected(l_b.to_float(), 1.0f / 3.0f, std::to_string(l_b) + " to float");
        l_ok &= quicky_test::check_expected(l_a.to_double(), 1.0 / 2.0, std::to_string(l_a) + " to double");
        l_ok &= quicky_test::check_expected(l_b.to_double(), 1.0 / 3.0, std::to_string(l_b) + " to double");

        return l_ok;
    }

    bool test_fract()
    {
        bool l_ok = true;
        l_ok &= test_fract_normal();
        l_ok &= test_fract_generic<uint32_t>();
        l_ok &= test_fract_generic<quicky_utils::safe_int<int32_t>>();
        l_ok &= test_fract_generic<quicky_utils::ext_int<int32_t>>();
        return l_ok;
    }
}
#endif //QUICKY_UTILS_TEST_FRACT_H
// EOF
