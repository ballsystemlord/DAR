/*********************************************************************/
// dar - disk archive - a backup/restoration program
// Copyright (C) 2002-2052 Denis Corbin
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// to contact the author : dar.linux@free.fr
/*********************************************************************/
// $Id: test_path.cpp,v 1.6 2003/10/18 14:43:07 edrusb Rel $
//
/*********************************************************************/

#include "../my_config.h"
#include <iostream>

#include "path.hpp"
#include "test_memory.hpp"

using namespace libdar;
using namespace std;

void f2();

int main()
{
    MEM_BEGIN;
    MEM_IN;
    try
    {
        path p1 = "/";
        path p2 = "toto";
        path p3 = "/titi";
        path p4 = "toto/titi/tutu/tata";
        path p5 = "/zozo/zizi/zuzu/zaza";

        cout << p2.display() << endl;
        
        path *p[5] = { &p1, &p2, &p3, &p4, &p5 };

        for(S_I i = 0; i < 5; i++)
        {
            string s;

            cout << "base name = " << p[i]->basename() << endl;
            p[i]->reset_read();
            cout << "reading  : ";
            while(p[i]->read_subdir(s))
                cout << " | " << s;
            cout << endl;

            cout << (p[i]->is_relative() ? "relative" : "absolute") << endl;
            cout << "display = [" << p[i]->display() << "]" << endl;

            if(p[i]->pop(s))
                cout << "pop = [" << p[i]->display() << "] [" << s << "]" << endl;
            else
                cout << "no popable" << endl;
        }
        path tmp = p1 + p2;
        cout << tmp.display() << endl;
        tmp = p5 + p4;
        cout << tmp.display() << endl;
        bool res = p1 == p2;
        res = p1 == p1;
        res = p4 == p5;
        res = p5 == p5;
    }
    catch(Egeneric & e)
    {
        e.dump();
    }
    
    try
    {
        path tmp = "";
    }
    catch(Egeneric & e)
    {
        e.dump();
    }
    
    try
    {
        path t1 = "/toto/tutu";
        path t2 = "zozo/zuzu";
        path t3 = t2 + t1;
    }
    catch(Egeneric & e)
    {
        e.dump();
    }
    f2();
    Egeneric::clear_last_destroyed();
    MEM_OUT;
    MEM_END;
}

void f2()
{
    char *src[] = { "toto", "/titi", "toto/./titi", "/./titi",
                    "toto/titi/tutu/../../..", "/toto/titi/tutu/../../..",
                    "././././toto/././././..", "/././././toto/././././..",
                    "../../../titi/./tutu", "/../../../../toto/../../tutu",
                    NULL };
    path conv = "/";

    for(S_I i = 0; src[i] != NULL; i++)
    {
        conv = path(src[i]);
        cout << string(src[i]) << " --> " << conv.display() << endl;
    }
}
