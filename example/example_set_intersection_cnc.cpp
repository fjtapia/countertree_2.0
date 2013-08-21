///----------------------------------------------------------------------------
// FILE : example_set_intersection_cnc.cpp
//
// DESCRIPTION : This program is an example of the concurrent intersection of two
//     set of ints
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
#include <thread>
#include <boost/countertree/set.hpp>

#define NELEM1 5000000
#define NELEM2 5000000

static const uint32_t NC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = (NC >8) ? 8 : NC ;

using std::cout ;
using std::cin;
using std::endl;
namespace cntree= countertree ;


void Process ( typename cntree::set<uint32_t>::const_iterator It1,
               uint32_t NElem,
               const cntree::set<uint32_t> & S2,
               cntree::set_cnc<uint32_t> & S3                        )
{   //---------------------------- begin---------------------------------------
    typename cntree::set<uint32_t>::const_iterator It2;

    for ( uint32_t i =0 ; i < NElem ;++i, ++It1)
    {   It2 = S2.find( *It1);
        if ( It2 != S2.end())  S3.insert ( *It1);
    };
};

int  main ( void)
{   cout<<"----------------------------------------------------------------------\n";
    cout<<"This program make the intersection of two cntree::sets<uint32_t> \n";
    cout<<"with 5000000 elements each. The result is on S3\n";
    cout<<"The process is done using so much threads as cores have the processor\n";
    cout<<"----------------------------------------------------------------------\n";

    cntree::set<uint32_t> S1 , S2 ;
    cntree::set_cnc<uint32_t> S3 ;

    cout<<"Generation------------------->\n";
    for ( uint32_t i =0 ; i< NELEM1 ; ++i)
        S1.insert ( RANDOM );

    for ( uint32_t i =0 ; i < NELEM2 ; ++i)
        S2.insert ( RANDOM);
    cout<<"End Generation-------------------->\n";
    cout<<" S1.size() :"<<S1.size()<<"   S2.size() : "<<S2.size()<<endl;

    std::thread  T [8] ;
    uint32_t NE [8] ;
    typename cntree::set<uint32_t>::const_iterator It[8];
    const uint32_t Cupo = S1.size() / NCores ;

    for (uint32_t i =0 ; i < NCores-1 ; ++i)
    {   NE[i]= Cupo ;
        It[i]= S1.begin() + ( i * Cupo);
    };
    NE[NCores -1]=  S1.size()-((NCores-1)* Cupo) ;
    It[NCores-1]= S1.begin() + ( Cupo * (NCores-1));


    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Process, It[i], NE[i], std::cref(S2), std::ref(S3) ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };

    cout<<"S3.size() :"<<S3.size()<<" elements stored \n";

    return 0 ;
};
