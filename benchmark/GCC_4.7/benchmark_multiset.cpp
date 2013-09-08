///----------------------------------------------------------------------------
// FILE : benchmark_multiset.cpp
//
// DESCRIPTION : This program is for to compare the speed of the std::multiset
//  with the countertree countertree::multiset
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
    typedef std::multiset<uint64_t> MS ;
    typedef std::multiset<uint64_t,std::less<uint64_t>,cntree::suballocator<std::allocator<void> > > MSA ;
    typedef cntree::multiset<uint64_t> CMS ;
    typedef cntree::multiset_pool<uint64_t> CMSP ;
    typedef cntree::multiset_cnc<uint64_t> CMSC ;
    typedef cntree::multiset_pool_cnc<uint64_t> CMSPC ;



    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-std::multiset--------------------->\n";
    cout<<"2.-std::multiset + suballocator------>\n";
    cout<<"3.-countertree::multiset------------->\n";
    cout<<"4.-countertree::multiset_pool------->\n";
    cout<<"5.-countertree::multiset_cnc-------->\n";
    cout<<"6.-countertree::multiset_pool_cnc--->\n";



    cout<<"7.- EXIT\n\n";
    cout<<"Select Option ->";
    cin>>Option ;
    switch ( Option)
    {

//--------------------------------------------------------------------------------
//                  MULTISET
//--------------------------------------------------------------------------------


    case 1: cout<<"std::multiset---------------------------------------->\n";
            Conjunto<MS > () ;
            break ;

    case 2: cout<<"std::multiset + suballocator ------------------------>\n";
            Conjunto<MSA > () ;
            break ;

    case 3: cout<<"countertree::multiset ------------------------------->\n";
            Conjunto<CMS > () ;
            break ;

    case 4: cout<<"countertree::multiset_pool---------------------------->\n";
            Conjunto<CMSP > () ;
            break ;

    case 5: cout<<"countertree::multiset_cnc ------------------------------>\n";
            Conjunto<CMSC > () ;
            break;

    case 6: cout<<"countertree::multiset_pool_cnc ------------------------->\n";
            Conjunto<CMSPC > () ;
            break;

    default: break;

    };
    delete[] A;
    cout<<(system ( "ps -C benchmark_multiset -o rss"))<<endl;
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
    cout<<(system ( "ps -C benchmark_multiset -o rss"))<<endl;
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

