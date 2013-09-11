//----------------------------------------------------------------------------
/// @file : benchmark_vector_tree_cnc_01.cpp
/// @brief Test program of the class countertree::vector_tree
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
#include <boost/countertree/vector_tree.hpp>
#include <boost/countertree/common/time_measure.hpp>
#include <algorithm>
#include <vector>

using std::cout ;
using std::endl;

#define NELEM 5000000
namespace cntree = countertree;
namespace c_common = countertree::common ;

static const uint32_t NC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = (NC >8) ? 8 : NC ;

uint32_t Primo [ 10000] ,Primo2[10000];
uint32_t NPrimo ;
<<<<<<< HEAD
void Generation ( void);
=======

>>>>>>> a638c30ad722b2664968a5babd793174f3466a44

void Generation ( void)
{	//------------------ Definición de constantes------------
    Primo [0] = 2 ;
    Primo [1] = 3 ;
    Primo [2] = 5;
    Primo [3] = 7;
    Primo [4] = 11;
    Primo [5] = 13 ;
    NPrimo = 6 ;

    uint64_t Tope =2, Tope2 = 25;

    for ( uint32_t Num = 17 ; Num < 65536 ; Num+=2)
    {   bool EsPrimo = true ;
        if ( Num >= Tope2)
        {   Tope++ ;
            Tope2 = Primo[Tope ]* Primo[Tope];
        };
        for ( uint32_t k = 1 ; k < Tope and EsPrimo; ++k)
        {   if (  ( Num % Primo[k]) == 0 ) EsPrimo = false ;
        };
        if (EsPrimo) Primo [ NPrimo++] = Num;
    };
    for (uint32_t i =0 ; i < NPrimo ;++i)
        Primo2[ i] = Primo[i]* Primo[i];
};
template <class VT >
void Criba ( VT & VTC ,typename VT::iterator  Alfa , uint32_t NElem)
{   //----------------------- begin--------------------
    //std::cout<<"Inicio ----->"<<std::this_thread::get_id()<<"  " ;
    //std::cout<<(*Alfa )<<" "<<NElem<<std::endl ;
    typename VT::iterator Beta = Alfa;
    for ( uint32_t i =0 ; i < NElem ; ++i)
    {   Alfa = Beta ;
        Beta = Alfa +1 ;
        uint32_t N = *Alfa ;
        bool EsPrimo = true ;
        for (uint32_t k = 0 ; EsPrimo and Primo2[k]<= N; ++k)
        {   if ( (N%Primo[k]) == 0) EsPrimo = false ;
        };
        if ( EsPrimo) VTC.erase ( Alfa);
    };
    //std::cout<<"Fin -------->"<<std::this_thread::get_id()<<std::endl ;
};
template <class VT>
void prueba ( void)
{   //--------------------------------- begin ------------------
    double duracion ;
	c_common::time_point start, finish;
    VT VTC ;

    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.push_back ( RANDOM | 1 ) ;
    cout<<"The memory used by "<<VTC.size()<<" elements stored is \n";
    cout<< (system ( "ps -C benchmark_vector_tree_cnc_01 -o rss"))<<endl;
    start = c_common::now();
    Criba<VT> (std::ref( VTC), VTC.begin(), VTC.size())    ;
    finish = c_common::now() ;

    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<VTC.size()<<" elements stored at end of the process\n";
};

template <class VT>
void prueba_cnc ( void)
{   //--------------------------------- begin ------------------
    double duracion ;
	c_common::time_point start, finish;
    std::thread  T [8] ;
    VT VTC ;

    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.push_back ( RANDOM | 1 ) ;

    cout<<"The memory used by "<<VTC.size()<<" elements stored is \n";
    cout<< (system ( "ps -C benchmark_vector_tree_cnc_01 -o rss"))<<endl;
    const uint32_t Cupo = NELEM / NCores ;
    typename VT::iterator Ini[8];
    uint32_t NE [8] ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   Ini[i] = VTC.begin() + ( i * Cupo);
        NE[i]=  ((i*Cupo)> NELEM)?(NELEM-(i-1)* Cupo):Cupo ;
    }

    start = c_common::now();
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Criba<VT>,std::ref( VTC), Ini[i], NE[i] ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };
    finish = c_common::now() ;
    duracion =  c_common::subtract_time(finish , start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
    cout<<VTC.size()<<" elements stored at end of the process\n";
    VTC.clear() ;
};


int  main ( void)
{   //---------------------- Variables----------------------------
    Generation() ;
    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    typedef cntree::vector_tree <uint32_t>              VT1;
    typedef cntree::vector_tree_pool <uint32_t>         VT2;
    typedef cntree::vector_tree_cnc <uint32_t>          VT3;
    typedef cntree::vector_tree_pool_cnc <uint32_t>     VT4;

    //--------------------------------------------------------------
    //                  P R U E B A S
    //--------------------------------------------------------------
    cout<<"----------------------------------------------------------------------------\n";
    cout<<"This program store "<<NELEM<<" numbers of 32 bits in a vector_tree\n"    ;
    cout<<"The time measured is the process of delete the prime numbers ( around 10%)\n";
    cout<<"done with 1 core or several cores and with and without pools of memory\n";
    cout<<"----------------------------------------------------------------------------\n\n\n";
    uint32_t Option =0 ;

    cout<<"                 MENU   \n";
    cout<<"               ======== \n";
    cout<<"1.-countertree::vector_tree---------------->\n";
    cout<<"2.-countertree::vector_tree_pool----------->\n";
    cout<<"3.-countertree::vector_tree_cnc------------>\n";
    cout<<"4.-countertree::vector_tree_pool_cnc ------>\n";
    cout<<"5.- EXIT\n\n";
    cout<<"Select Option ->";
    std::cin>>Option ;
    switch ( Option)
    {
    case 1: cout<<"1.-countertree::vector_tree---------------->\n";
            prueba <VT1> () ;
            break ;

    case 2: cout<<"2.-countertree::vector_tree_pool----------->\n";
            prueba<VT2> () ;
            break ;

    case 3: cout<<"3.-countertree::vector_tree_cnc------------>\n";
            prueba_cnc<VT3>() ;
            break ;

    case 4: cout<<"4.-countertree::vector_tree_pool_cnc ------>\n";
            prueba_cnc<VT4> () ;
            break ;

    default: break;

    };
    cout<<"The memory used by the data structure empty is \n";
    cout<<(system ( "ps -C benchmark_vector_tree_cnc_01 -o rss"));
    return 0 ;
};
