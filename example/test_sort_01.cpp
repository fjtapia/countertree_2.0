//----------------------------------------------------------------------------
/// @file test_sort_01.cpp
/// @brief Program to test the sort funcion  and binary_search 
///        over a countertree::vector_tree
///
/// @author Copyright (c) 2010 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/countertree/vector_tree.hpp>

int main ( void)
{   //---------------------------- begin -------------------------
    double duracion ;
	clock_t start, finish;
    countertree::vector_tree<int >  V1, V2, V3 ;
    std::vector<int> V4 ;

    for ( int i = 0 ; i < 1000000 ; ++i) V1.push_back ( rand());
    V2 = V1 ;
    std::random_shuffle( V1.begin(), V1.end());

    start = clock() ;
    std::sort ( V1.begin(), V1.end());
    finish = clock() ;
	duracion = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"std::sort of vector_tree :"<<duracion<<" seconds\n";

    start = clock() ;
    for ( int i =0 ; i < 1000000 ; ++i )
    {   if ( not  std::binary_search ( V1.begin() , V1.end(), V2[i]) )
            std::cout<<"not found"<<std::endl;
    };
    finish = clock() ;
	duracion = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"std::binary_search :"<<duracion<<" seconds\n";

    for ( int i = 0 ; i < 1000000 ; ++i) V2.push_back ( rand());
    std::sort ( V2.begin(), V2.end());
    return 0 ;
}
