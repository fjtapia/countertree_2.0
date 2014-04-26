//----------------------------------------------------------------------------
/// @file : benchmark_map_cnc_01.cpp
/// @brief Test program of the class countertree::map
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks This program store aleatory numbers in a vector_tree, and must delete
///          the non prime numbers, testing the speed with different configurations
//-----------------------------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <boost/countertree/map.hpp>
#include <boost/countertree/common/time_measure.hpp>
#include <algorithm>
#include <vector>

using std::cout ;
using std::endl;

#define NELEM 50000000
namespace cntree = countertree;
namespace c_common = countertree::common ;

static const uint32_t NCores = std::thread::hardware_concurrency() ;

typedef cntree::map_pool<uint32_t , float> map_t ;
typedef typename map_t::const_iterator c_iter_t ;
map_t M ;
uint32_t Cnt[100];



void Generation ( void);

void Generation ( void)
{	//-----------------------------------------------------
    // filling the data structures
    //-----------------------------------------------------
    for ( uint32_t i = 0 ; i < 100 ; ++i) Cnt[i]= 0;
    for ( uint32_t i = 0 ; i < NELEM ; ++i)
    {   uint32_t key = rand();
        float val =  (rand() %10000) / 100.0;
        M.emplace ( key, val);
    }
};


void Criba ( c_iter_t   Alfa , uint32_t N)
{   //--------------------------------- begin ------------------
    uint32_t C[100];

    for (uint32_t i = 0 ; i < 100 ; ++i) C[i]= 0;

    for ( uint32_t i = 0 ; i <N ; ++i, ++Alfa )
    {   uint32_t R = ( uint32_t)Alfa->second ;
        C[R]++;
    };
    for (uint32_t i = 0 ; i < 100 ; ++i) Cnt[i] += C[i];
};


void prueba ( void)
{   //--------------------------------- begin ------------------
    double duracion ;
	c_common::time_point start, finish;

    start = c_common::now();
    Criba (M.begin(), M.size()) ;
    finish = c_common::now() ;

    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<"The number of elements stored in the map is :"<<M.size()<<endl;
    cout<<"The percents obtained are :\n";
    for ( uint32_t i =0 ; i < 100 ; ++i )
    {   if ( (i%5) == 0) cout<<"\n";
        cout<<"["<<i<<", "<<i+1<<"]->"<<( (Cnt[i]* 100.0) / NELEM)<<" %\t";
    };
    cout<<"\n\n";
};

void prueba_cnc ( void)
{   //--------------------------------- begin ------------------
    double duracion ;
	c_common::time_point start, finish;

    start = c_common::now();

    std::vector<std::thread>  T (NCores) ;
    const uint32_t Cupo = M.size() / NCores ;
    std::vector<c_iter_t> Ini(NCores);
    std::vector<uint32_t> NE (NCores);

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   Ini[i] = M.begin() + ( i * Cupo);
        NE[i]=  ((i*Cupo)> NELEM)?(NELEM-(i-1)* Cupo):Cupo ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Criba, Ini[i], NE[i] ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };
    finish = c_common::now() ;
    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";

    cout<<"The number of elements stored in the map is :"<<M.size()<<endl;
    cout<<"The percents obtained are :\n";
    for ( uint32_t i =0 ; i < 100 ; ++i )
    {   if ( (i%5) == 0) cout<<"\n";
        cout<<"["<<i<<", "<<i+1<<"]->"<<( (Cnt[i]* 100.0) / NELEM)<<" %\t";
    };
    cout<<"\n\n";
};


int  main ( void)
{   //---------------------- Variables----------------------------
    Generation() ;

    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    cout<<"----------------------------------------------------------------------------\n";
    cout<<"This program store  in a map pairs of [key, value] the key is uint32_t and \n"    ;
    cout<<"the value is a double with a a value betwenn 0 and 100 \n";
    cout<<"The program count the percentage of numbers between [0 -1], [1,2] ....\n";
    cout<<"printing the final result done with 1 core or several cores \n";
    cout<<"----------------------------------------------------------------------------\n\n\n";
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.- single thread ---------------->\n";
    cout<<"2.-"<<NCores<<" threads----------->\n";
    cout<<"3.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {
    case 1: cout<<"1.- single thread ---------------->\n";
            prueba  () ;
            break ;

    case 2: cout<<"2.-"<<NCores<<" threads----------->\n";
            prueba_cnc () ;
            break ;


    default: break;

    };

    return 0 ;
};
