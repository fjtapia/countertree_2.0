//----------------------------------------------------------------------------
/// @file test_sort_02.cpp
/// @brief Program to test the sort and binary search funcion over a 
///       vector_tree
///
/// @author Copyright (c) 2010 2012Francisco José Tapia (fjtapia@gmail.com )\n
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
#define NELEM 1000000

int main ( void)
{   //---------------------------- begin -------------------------
    double duracion ;
	clock_t start, finish;
    countertree::vector_tree<int >  V1, V2, V3 ;
    std::vector<int> V4 ;

    V1.push_back (111111111);
    for ( int i = 0 ; i < NELEM ; ++i) V1.push_back ( rand());

    std::random_shuffle( V1.begin(), V1.end());

    start = clock() ;
    std::sort ( V1.begin(), V1.end());
    finish = clock() ;
	duracion = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"sort of vector_tree - Time spent :"<<duracion<<" seconds\n";

    //for ( int i = 0 ; i < V1.size() ; ++i) std::cout<<V1[i]<<"    ";
    //std::cout<<std::endl;

    if ( std::binary_search ( V1.begin() , V1.end(), 111111111) )
        std::cout<<"found "<<std::endl;
    else std::cout<<"not found"<<std::endl;

    for ( int i = 0 ; i < 1000000 ; ++i) V2.push_back ( rand());
    std::sort ( V2.begin(), V2.end());

    std::cout<<"set_union ---------------------------->"<<std::endl;
    std::set_union ( V1.begin(), V1.end() , V2.begin(), V2.end() , std::back_inserter (V3));
    std::set_union ( V1.begin(), V1.end() , V2.begin(), V2.end() , std::back_inserter (V4));
    std::sort ( V3.begin(), V3.end());
    for ( int i =0   ; i < V4.size() ; ++i)
    {   if ( not std::binary_search ( V3.begin() , V3.end(), V4[i]) )
            std::cout<<"error in binary search \n";

    };

    //for ( int i = 0 ; i < V3.size() ; ++i)    std::cout<<V3[i]<<"    ";
    //std::cout<<std::endl;
    return 0 ;

}
