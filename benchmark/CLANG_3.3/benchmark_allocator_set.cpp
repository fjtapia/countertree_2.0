///----------------------------------------------------------------------------
// FILE : benchmark_set_allocator.cpp
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
#include <set>
#include <time.h>

#include <ext/typelist.h>
#include <ext/array_allocator.h>
#include <ext/new_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/pool_allocator.h>
#include <boost/pool/pool_alloc.hpp>
#include <boost/countertree/set.hpp>
#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/common/time_measure.hpp>


#define NELEM 15000000

using std::cout ;
using std::endl;
namespace cntree = countertree;
namespace c_common = countertree::common ;
//uint64_t A[NELEM];
uint64_t * A ;
template <typename  Structure> void Prueba ( Structure &S  ) ;

template <typename  Alloc> int Conjunto ( void ) ;
template <class Structure> void Muestreo ( void);

int  main ( void)
{   //---------------------- Variables----------------------------
    A = new uint64_t [ NELEM];

    //typedef __gnu_cxx::__common_pool_policy<__gnu_cxx::__pool, Thread> pool_policy;
    typedef std::allocator<uint64_t>                                     T1 ;
    typedef cntree::suballocator< std::allocator<uint64_t> >             T2 ;
    typedef __gnu_cxx::malloc_allocator<uint64_t> 		                 T3;
    typedef __gnu_cxx::__mt_alloc<uint64_t>          	                 T4;
    typedef __gnu_cxx::__pool_alloc<uint64_t> 		                     T5;
    typedef boost::fast_pool_allocator<uint64_t>                         T6 ;
    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-std::allocator--------------------->\n";
    cout<<"2.-std::allocator + suballocator------>\n";
    cout<<"3.-malloc_allocator------------------->\n";
    cout<<"4.-mt_allocator----------------------->\n";
    cout<<"5.-pool_allocator--------------------->\n";
    cout<<"6.-boost::fast_pool_allocator -------->\n";
    cout<<"7.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {   case 1 :    cout<<"1.-std::allocator--------------------->\n";
                    Conjunto<T1 > () ;
                    break ;

        case 2 :    cout<<"2.-std::allocator + suballocator------>\n";
                    Conjunto<T2 > () ;
                    break ;

        case 3 :    cout<<"3.-malloc_allocator------------------->\n";
                    Conjunto<T3 > () ;
                    break;

        case 4 :    cout<<"4.-mt_allocator----------------------->\n";
                    Conjunto<T4 > () ;
                    break;

        case 5 :    cout<<"5.-pool_allocator--------------------->\n";
                    Conjunto<T5 > () ;
                    break;

        case 6 :    cout<<"6.-boost::fast_pool_allocator -------->\n";
                    Conjunto<T6 > () ;
                    break ;

        default : break ;
    };
    delete[] A ;
    cout<<(system ( "ps -C benchmark_allocator_set -o rss"))<<endl;
    return 0 ;
};
template <typename  Alloc>
int  Conjunto ( void)
{   //---------------------- Variables----------------------------
    uint32_t Option =0 ;
    cout<<"\n\n         SELECCIONE ESTRUCTURA  \n";
    cout<<"      ============================== \n";
    cout<<"1.-std::set ------------------------->\n";
    cout<<"2.-countertree::set ----------------->\n";
    cout<<"3.-std::multiset--------------------->\n";
    cout<<"4.-countertree::multiset------------->\n";
    cout<<"5.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {   case 1 :    cout<<"std::set-------------------------------------------->\n";
                    Muestreo<std::set<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break ;

        case 2 :    cout<<"countertree::set-------------------------------------------->\n";
                    Muestreo<cntree::set<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break;

        case 3 :    cout<<"std::multiset-------------------------------------------->\n";
                    Muestreo<std::multiset<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break ;

        case 4 :    cout<<"countertree::multiset-------------------------------------------->\n";
                    Muestreo<cntree::multiset<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break;

        default :   std::cout<<"error en la seleccion de estructura --->\n";
    };

    return 0 ;
};


template <class Structure>
void Muestreo ( void)
{   //------------------------ Inicio -----------------------------
    Structure S ;
    int i ;
    //------------------------ Inicio -----------------------------
    for (  i = 0 ; i < NELEM; i ++ )
    {    S.insert( i);
    };
    cout<<(system ( "ps -C benchmark_allocator_set -o rss"))<<endl;
    S.clear();

    cout<<"----------Insertion of "<< NELEM<<" elements---------\n" ;
    cout<<"Many elements , sorted elements\n";
    for ( i = 0 ; i < NELEM ; i ++) A[i] = NELEM +i ;
    Prueba<Structure>( S ) ;

    cout<<"Many elements , few repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++) A[i] = RANDOM ;
    Prueba<Structure>( S ) ;

    cout<<"Many elements , quite repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++) A[i] = RANDOM  % (NELEM/2);
    Prueba<Structure>( S ) ;

    cout<<"Many element many repeated\n";
    for ( i = 0 ; i < NELEM  ; i ++) A[i] =  RANDOM %10000;
    Prueba<Structure>( S ) ;

    cout<<"Equal elements\n";
    for ( i = 0 ; i < NELEM  ; i ++) A[i] = NELEM;
    Prueba<Structure>( S ) ;
    //cout<<(system ( "ps -C benchmark_set_allocator -o size"))<<endl;
};

template <typename  Structure>
void Prueba ( Structure & S )
{   //----------------------------- Inicio ------------------------
    double duracion ;
	c_common::time_point start, finish;
    int i;

    start = c_common::now();
    for ( i = 0 ; i < NELEM; i ++ )
    {    S.insert( A[i] );
    };
    finish = c_common::now();
    duracion = c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    S.clear() ;

    cout<<"---------------------------------------------------\n";
};
