///----------------------------------------------------------------------------
// FILE : benchmark_set.cpp
//
// DESCRIPTION : This program is for to compare the speed of the std::set
//  with the countertree::set, and std::multiset with countertree::multiset
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
#include <time.h>

#include <set>
#include <boost/countertree/set.hpp>
#include <boost/countertree/common/time_measure.hpp>

#define NELEM 30000000
namespace c_common = countertree::common ;
namespace cntree = countertree ;
using std::cout ;
using std::cin;
using std::endl;

uint64_t *A;
template <typename  T> void Prueba ( T &T1) ;

template <typename  T> int Conjunto ( void ) ;

int  main ( void)
{   //---------------------- Variables----------------------------
    A = new uint64_t [NELEM];
    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    typedef std::set <uint64_t> S ;
    typedef std::set <uint64_t,std::less<uint64_t>,cntree::suballocator<std::allocator<void> > > SA ;
    typedef cntree::set<uint64_t> CS ;
    typedef cntree::set_pool<uint64_t> CSP ;
    typedef cntree::set_cnc<uint64_t> CSC ;
    typedef cntree::set_pool_cnc<uint64_t> CSPC ;


    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-std::set-------------------------->\n";
    cout<<"2.-std::set + suballocator----------->\n";
    cout<<"3.-countertree::set------------------>\n";
    cout<<"4.-countertree::set_pool------------->\n";
    cout<<"5.-countertree::set_cnc-------------->\n";
    cout<<"6.-countertree::set_pool_cnc--------->\n";

    cout<<"7.- EXIT\n\n";
    cout<<"Select Option ->";
    cin>>Option ;
    switch ( Option)
    {

    case 1: cout<<"std::set ------------------------------------------->\n";
            Conjunto<S > () ;
            break ;

    case 2: cout<<"std::set + suballocator  --------------------------->\n";
            Conjunto<SA > () ;
            break ;

    case 3: cout<<"countertree::set ----------------------------------->\n";
            Conjunto<CS > () ;
            break ;

    case 4: cout<<"countertree::set_pool------------------------------->\n";
            Conjunto<CSP > () ;
            break ;

    case 5: cout<<"countertree::set_cnc--------------------------------->\n";
            Conjunto<CSC > () ;
            break;

    case 6: cout<<"countertree::set_pool_cnc -------------------------->\n";
            Conjunto<CSPC > () ;
            break;

    default: break;

    };
    delete[] A;
    cout<<(system ( "ps -C benchmark_set -o rss"))<<endl;
    return 0 ;
};
template <typename  T>
int  Conjunto ( void)
{   //---------------------- Variables----------------------------
    T T1;
    int i ;
    //------------------------ Inicio -----------------------------
    for (  i = 0 ; i < NELEM; i ++ )
    {    T1.insert( i);
    };
    cout<<(system ( "ps -C benchmark_set -o rss"))<<endl;
    T1.clear();

    cout<<"----------Insertion of "<< NELEM<<" elements---------\n" ;
    cout<<"Many elements , sorted elements\n";
    for ( i = 0 ; i < NELEM ; i ++)
        A[i] = NELEM +i ;
    Prueba<T>(T1) ;

    cout<<"Many elements , few repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++)
        A[i] = RANDOM ;
    Prueba<T>(T1) ;

    cout<<"Many elements , quite repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++)
        A[i] = RANDOM  % (NELEM/2);
    Prueba<T>(T1) ;

    cout<<"Many element many repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++)
        A[i] = RANDOM %10000;
    Prueba<T>(T1) ;

    cout<<"Equal elements\n";
    for ( i = 0 ; i < NELEM  ; i ++)
        A[i] = NELEM;
    Prueba<T>(T1) ;

    return 0 ;
};

template <typename  T>
void Prueba ( T & M1 )
{   //----------------------------- Inicio ------------------------
    double duracion ;
	c_common::time_point start, finish;

    // ----------------------------------------
    start = c_common::now();
    for ( int i = 0 ; i < NELEM; i ++ )
    {    M1.insert( A[i] );
    };
    finish = c_common::now() ;
    M1.clear();
    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";

    cout<<"---------------------------------------------------\n";
};

