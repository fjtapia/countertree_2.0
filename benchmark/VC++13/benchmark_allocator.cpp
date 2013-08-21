///----------------------------------------------------------------------------
// FILE : benchmark_allocator.cpp
//
// DESCRIPTION : This program is for to compare the speed of the several
//              allocators
//
// MODIFICATIONS (AUTHOR,DATE,REASON) :
//  Copyright (c) 2010 Francisco José Tapia (fjtapia@gmail.com )
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// NOTES :
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <set>

#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/common/time_measure.hpp>
#include <boost/pool/pool_alloc.hpp>


#define NELEM 50000000

using std::cout ;
using std::endl;
using std::cin ;
namespace cntree = countertree ;
namespace c_common = countertree::common ;

uint64_t * * K ;
template <typename  Alloc> void Prueba ( void ) ;



char comando[] = "tasklist /FI \"IMAGENAME eq benchmark_allocator.exe\" ";

int  main ( void)
{   //---------------------- Variables----------------------------
    K = new uint64_t* [NELEM];

    typedef std::allocator<uint64_t>                             T1 ;
    typedef cntree::suballocator< std::allocator<uint64_t> >     T2 ;
    typedef cntree::suballocator_cnc< std::allocator<uint64_t> > T3 ;
    typedef boost::fast_pool_allocator<uint64_t>                 T4 ;

    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    cout<<"                     DESCRIPTION\n";
    cout<<"                   =================\n";
    cout<<"This program allocate and deallocate several sets of elements checking the\n";
    cout<<"time needed ( less is better)\n";
    cout<<"The program check, too, the RAM used ( the number under the RSS label is\n";
    cout<<"the size of RAM used in Kb) in three moments :\n";
    cout<<"    1.-with all the elements allocated\n";
    cout<<"    2.-with all the elements deallocated \n";
    cout<<"    3.-all the elements deallocated and data structures cleared before\n";
    cout<<"       finish the program\n\n\n";
    //cout<<(system (comando))<<endl;
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-std::allocator----------------------------->\n";
    cout<<"2.-std::allocator + suballocator-------------->\n";
    cout<<"3.-std::allocator + suballocator_cnc---------->\n";
    cout<<"4.-boost::fast_pool_allocator ---------------->\n";
    cout<<"5.- EXIT\n\n";
    cout<<"Select Option ->";
    cin>>Option ;
    switch ( Option)
    {
    case 1: cout<<"std::allocator----------------------------------------------->\n";
            Prueba<T1 > () ;
            break ;

    case 2: cout<<"std::allocator + suballocator ------------------------------->\n";
            Prueba<T2 > () ;
            break;

    case 3: cout<<"std::allocator + suballocator_cnc ------------------------------->\n";
            Prueba<T3 > () ;
            break;

    case 4: cout<<"boost::fast_pool_allocator------------------------------------>\n";
            Prueba<T4 > () ;
            break;


    default: break;

    };
    delete [] K ;
    cout<<(system (comando))<<endl;
    return 0 ;
};


template <typename  Alloc>
void Prueba ( void )
{   //----------------------------- Inicio ------------------------
    double duracion ;
	c_common::time_point start, finish;

    Alloc  A  ;
    for (uint64_t i = 0 ; i < NELEM ; ++i)  K[i] = NULL ;

    //------------------------------------------------------------------
    cout<<"Starting ------------>\n";
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
        A.construct (K[i], i) ;
    };
    cout<<(system (comando))<<endl;
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   if ( *(K[i] ) != i )
            std::cout<<"Error en "<<i<<std::endl;
        A.deallocate ( K[i],1);
    };
    cout<<(system (comando))<<endl;

    //------------------------------------------------------------------
    cout<<"Allocate of "<<NELEM<<" elements ------------>";
    start = c_common::now();
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
    };
    finish = c_common::now();
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   A.deallocate ( K[i],1);
    };
	duracion = c_common::subtract_time ( finish, start);
    cout<<"Time spent :"<<duracion<<" seconds\n";

    //------------------------------------------------------------------

    //------------------------------------------------------------------
    cout<<"deallocate all from the first to the last -->";
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
    };
    start = c_common::now();
    for (uint64_t i = 0 ; i < NELEM ; i++ )
    {   A.deallocate (K[i],1);
    };
    finish = c_common::now();
	duracion = c_common::subtract_time ( finish, start);
    cout<<"Time spent :"<<duracion<<" seconds\n";
    //----------------------------------------------------

    //------------------------------------------------------------------
    cout<<"deallocate all from the last to the first -->";
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
    };
    start = c_common::now();
    for (uint64_t i = 1 ; i <= NELEM ; i++ )
    {   A.deallocate (K[NELEM -i],1);
    };
    finish = c_common::now();
	duracion = c_common::subtract_time ( finish, start);
    cout<<"Time spent :"<<duracion<<" seconds\n";
    //----------------------------------------------------

    //----------------------------------------------------
    cout<<"deallocate odd elements -------------->";
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
    };
    start = c_common::now();
    for (uint64_t i = 0 ; i < NELEM ; i+= 2 )
    {   A.deallocate (K[i],1);
    };
    finish = c_common::now();
    for (uint64_t i = 1 ; i < NELEM ; i+= 2 )
    {   A.deallocate (K[i],1);
    };
	duracion = c_common::subtract_time ( finish, start);
    cout<<"Time spent :"<<duracion<<" seconds\n";
    //-------------------------------------------------------

    cout<<"deallocate odd elements and reallocate -------->";
    for (uint64_t i = 0 ; i < NELEM ; ++i )
    {   K[i] = A.allocate (1);
    };
    start = c_common::now();
    for (uint64_t i = 0 ; i < NELEM ; i+= 2 )
    {   A.deallocate (K[i],1);
    };
    for (uint64_t i = 0 ; i < NELEM ; i+= 2 )
    {   K[i] = A.allocate (1);
    };
    finish = c_common::now();
    for (uint64_t i = 1 ; i < NELEM ; i++ )
    {   A.deallocate (K[i],1);
    };
	duracion = c_common::subtract_time ( finish, start);
    cout<<"Time spent :"<<duracion<<" seconds\n";

    //-------------------------------------------------------
    cout<<"---------------------------------------------------\n";
};

