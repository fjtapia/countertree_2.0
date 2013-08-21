///----------------------------------------------------------------------------
// FILE : benchmark_set_01.cpp
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
#include <thread>
#include <algorithm>

#include <set>
#include <boost/countertree/set.hpp>
#include <boost/countertree/common/time_measure.hpp>

#define NELEM1 25000000
#define NELEM2 25000000


static const uint32_t NC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = (NC >8) ? 8 : NC ;

uint32_t NPrimo ;

using std::cout ;
using std::cin;
using std::endl;

namespace cntree= countertree ;
namespace c_common = countertree::common ;

//---------------------------------------------------------------------------
//            DEFINITION OF FUNCTIONS
//---------------------------------------------------------------------------
template <class set1_t , class set2_t>
void Process ( typename set1_t::const_iterator It1,uint32_t NElem, const set1_t & S2, set2_t & S3 );

void  MultipleCore ( void);
void  SingleCore ( void);
void  Algorithm ( void);
template <class set_t1 , class set_t2 >
void Generation ( set_t1 & S1 , set_t2 &S2 );
int  main ( void);

//---------------------------------------------------------------------------
//                     F U N C T I O N S
//---------------------------------------------------------------------------
template <class set1_t , class set2_t>
void Process ( typename set1_t::const_iterator It1,uint32_t NElem, const set1_t & S2, set2_t & S3 )
{   //----------------------- begin--------------------
    typename set1_t::const_iterator It2;

    for ( uint32_t i =0 ; i < NElem ;++i, ++It1)
    {   It2 = S2.find( *It1);
        if ( It2 != S2.end())
            S3.insert ( *It1);
    };
    //std::cout<<"Fin -------->"<<std::this_thread::get_id()<<std::endl ;
};

void  MultipleCore ( void)
{   //---------------------- Variables----------------------------
    typedef cntree::set<uint32_t> S1_t;
    typedef cntree::set_cnc<uint32_t> S3_t ;
    S1_t S1 , S2;
    S3_t S3;

    Generation ( S1,S2);
    cout<<" S1.size() :"<<S1.size()<<"   S2.size() : "<<S2.size()<<endl;

    double duracion ;
	c_common::time_point start, finish;

    std::thread  T [8] ;
    uint32_t NE [8] ;
    typename S1_t::const_iterator It[8];
    const uint32_t Cupo = S1.size() / NCores ;

    for (uint32_t i =0 ; i < NCores-1 ; ++i)
    {   NE[i]= Cupo ;
        It[i]= S1.begin() + ( i * Cupo);
    };
    NE[NCores -1]=  S1.size()-((NCores-1)* Cupo) ;
    It[NCores-1]= S1.begin() + ( Cupo * (NCores-1));

	start = c_common::now();
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Process<S1_t, S3_t>, It[i], NE[i], std::cref(S2), std::ref(S3) ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };

    finish = c_common::now() ;
    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<"S3.size() :"<<S3.size()<<" elements stored \n";

 };
void  Algorithm ( void)
{   //---------------------- Variables----------------------------
    cntree::set<uint32_t> S1 , S2, S3 ;
    Generation ( S1,S2);
    S3.clear() ;
    cout<<" S1.size() :"<<S1.size()<<"   S2.size() : "<<S2.size()<<endl;

    double duracion ;
	c_common::time_point start, finish;
	start = c_common::now();
	std::set_intersection( S1.cbegin(), S1.cend(), S2.cbegin(), S2.cend(),
                           std::insert_iterator<cntree::set<uint32_t> > ( S3, S3.begin()) );
    finish = c_common::now() ;

    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<"S3.size() :"<<S3.size()<<" elements stored \n";

};
void  SingleCore ( void)
{   //---------------------- Variables----------------------------
    cntree::set<uint32_t> S1 , S2, S3 ;
    Generation ( S1,S2);
    S3.clear() ;
    cout<<" S1.size() :"<<S1.size()<<"   S2.size() : "<<S2.size()<<endl;

    double duracion ;
	c_common::time_point start, finish;
	start = c_common::now();
    Process ( S1.begin(), S1.size(), S2, S3);

    finish = c_common::now() ;

    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<"S3.size() :"<<S3.size()<<" elements stored \n";

};
template <class set_t1 , class set_t2 >
void Generation ( set_t1 & S1 , set_t2 &S2 )
{	//------------------ Definición de constantes------------
    cout<<"Generation   ";
    for ( uint32_t i =0 ; i< NELEM1 ; ++i)
        S1.insert ( RANDOM );

    for ( uint32_t i =0 ; i < NELEM2 ; ++i)
        S2.insert ( RANDOM);
    cout<<"End Generation\n";
};

int  main ( void)
{   //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    cout<<"----------------------------------------------------------------------\n";
    cout<<"This program make the intersection of two sets ( S1,S2) of elelments uint32_t\n";
    cout<<"The result is on S3\n";
    cout<<" The menu permit to do with a 1 core, with several cores  and with the \n";
    cout<<" set_intersection function of  <algorithm> \n";
    cout<<"----------------------------------------------------------------------\n";
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.- single core intersection ------------------>\n";
    cout<<"2.- many core intersection--------------------->\n";
    cout<<"3.- <algorithm> set_intersection -------------->\n";
    cout<<"4.- EXIT\n\n";
    cout<<"Select Option ->";
    cin>>Option ;
    switch ( Option)
    {
    case 1: cout<<"1.- single core intersection ------------------>\n";
            SingleCore () ;
            break ;

    case 2: cout<<"2.- many core intersection--------------------->\n";
            MultipleCore () ;
            break ;

    case 3: cout<<"3.- <algorithm> set_intersection -------------->\n";
            Algorithm () ;
            break ;

    default: break;

    };
    return 0 ;
};
