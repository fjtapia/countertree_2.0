//----------------------------------------------------------------------------
/// @file example_multimap_01.cpp
/// @brief Test program of the class countertree::multimap
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <boost/countertree/map.hpp>

typedef std::pair<const int, double> PID ;

std::ostream & operator << ( std::ostream &salida, const PID &P)
{   salida<<"("<<P.first<<" , "<<P.second<<") ";
    return salida ;
};

int  main ( void)
{   //-------------------------- begin--------------------
    countertree::multimap<int, double> M1;
    for ( int i = 1000 ; i < 3000 ; i+= 2) M1.insert (PID(i, rand()));

    countertree::multimap<int,double>::iterator Gamma, Beta  ;
    Gamma = M1.lower_bound( 2000);
    Beta = M1.end() - 50 ;

    for ( int i = Gamma.pos() ; i < Beta.pos() ; ++i)
        std::cout<<M1.pos(i)<<std::endl;
    return 0 ;
};
