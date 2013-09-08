///----------------------------------------------------------------------------
// FILE : benchmark_allocator_set.cpp
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
#include <memory>
#include <set>

#include <boost/pool/pool_alloc.hpp>
#include <boost/countertree/set.hpp>
#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/common/time_measure.hpp>



#define NELEM 15000000

using std::cout ;
using std::endl;
char comando[] = "tasklist /FI \"IMAGENAME eq benchmark_allocator_set.exe\" ";

uint64_t A[NELEM];
template <typename  Alloc> void Prueba ( void ) ;
template <typename  Alloc> int Conjunto ( void ) ;


int  main ( void)
{   //---------------------- Variables----------------------------
    typedef std::allocator<uint64_t>                            T1 ;
    typedef countertree::suballocator <std::allocator<uint64_t> >    T2 ;
    typedef boost::fast_pool_allocator<uint64_t>                T3 ;


    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    uint32_t Option =0 ;
    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-std::allocator--------------------------->\n";
    cout<<"2.-std::allocator + suballocator------------>\n";
    cout<<"3.-boost::fast_pool_allocator--------------->\n";
    cout<<"4.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {   case 1 :    cout<<"std::allocator-------------------------------------------->\n";
                    Conjunto<T1 > () ;
                    break ;

         case 2 :   cout<<"std::allocator + SubAllocator ---------------------------------->\n";
                    Conjunto<T2 > () ;
                    break;

        case 3 :    cout<<"fast_pool_allocator -------------------------------------------->\n";
                    Conjunto<T3 > () ;
                    break ;

        default : break ;
    };

    return 0 ;

};
template <typename  Alloc>
int  Conjunto ( void)
{   //---------------------- Variables----------------------------
    uint32_t Option =0 ;
    cout<<"\n\n\n\n";
    cout<<"\n\n       SELECT DATA STRUCTURE  \n";
    cout<<"      ============================== \n";
    cout<<"1.-std::set -------------------->\n";
    cout<<"2.-std::multiset---------------->\n";
    cout<<"3.-countertree::set ----------------->\n";
    cout<<"4.-countertree::multiset------------->\n";
    cout<<"5.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {   case 1 :    cout<<"std::set-------------------------------------------->\n";
                    Muestreo<std::set<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break ;

        case 2 :    cout<<"std::multiset-------------------------------------------->\n";
                    Muestreo<std::multiset<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break ;

        case 3 :    cout<<"countertree::set-------------------------------------------->\n";
                    Muestreo<countertree::set<uint64_t,std::less<uint64_t>,Alloc> > () ;
                    break;

        case 4 :    cout<<"countertree::multiset-------------------------------------------->\n";
                    Muestreo<countertree::multiset<uint64_t,std::less<uint64_t>,Alloc> > () ;
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
    cout<<(system ( comando))<<endl;
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
    cout<<(system ( comando))<<endl;
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

