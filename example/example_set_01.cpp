//----------------------------------------------------------------------------
/// @file example_set_01.cpp
/// @brief Example program of the class countertree::set
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <boost/countertree/set.hpp>
#include <iostream>

int main ( void )
{   //------------------------ begin --------------------
    countertree::set<int> A ;
    for ( int i = 0 ; i< 100 ; ++i)  A.insert(i);
    countertree::set<int>::iterator Alfa, Beta ;

    Alfa = A.lower_bound( 45 );
    Beta = A.end() - 10 ;
    for ( int i = Alfa.pos() ; i < Beta.pos() ; ++i)
        std::cout<<A.pos(i)<<" , ";
    std::cout<<std::endl;
    return 0 ;
};
