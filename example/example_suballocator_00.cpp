///----------------------------------------------------------------------------
// FILE : example_suballocator_00.cpp
//
// DESCRIPTION : Test program of the class suballocator
//
// MODIFICATIONS (AUTHOR,DATE,REASON) :
//  Copyright (c) 2010 2011 Francisco José Tapia (fjtapia@gmail.com )
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// NOTES : This program allocate 100.000.000 double elements and
//   deallocate measuring the times with the function clock()
//-----------------------------------------------------------------------------
#include <boost/countertree/suballocator.hpp>
#include <iostream>
#include <time.h>

#define NELEM 100000000


int main ( void)
{   //------------------------------ begin ----------------------------------
    double duracion ;
	clock_t start, finish ;
    double ** K = new double* [NELEM];

    //-------- Creating the suballocator --------------------------
    countertree::suballocator< std::allocator<double> >A ;

    //--------------------------------------------------------
    //         Allocate of the elements
    //-------------------------------------------------------
    std::cout<<"Begin  ---------------------->\n";
    start = clock();
    for ( uint32_t i =0  ; i < NELEM ; ++i)
        K[i] = A.allocate(1);
    finish = clock() ;

    duracion = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"Time Alloc  :"<<duracion<<" seconds\n";

    //--------------------------------------------------------
    //         Deallocate of the elements
    //-------------------------------------------------------
    std::cout<<"Full ---------------------->\n";
    start = clock();
    for ( uint32_t i =0  ; i < NELEM ; ++i)
        A.deallocate(K[i],1);
    finish = clock() ;

    duracion = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"Time Dealloc  :"<<duracion<<" seconds\n";

    std::cout<<"Empty ---------------------->\n";

    delete K;
}
