//----------------------------------------------------------------------------
/// @file : example_vector_tree_cnc.cpp
/// @brief Test program of the class countertree::vector_tree
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks This program store aleatory numbers in a vector_tree, and must delete
///          the non prime numbers,
//-----------------------------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <boost/countertree/vector_tree.hpp>
#define NELEM 5000000

using std::cout ;
using std::endl;
namespace cntree = countertree;

static const uint32_t NC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = (NC >8) ? 8 : NC ;

uint32_t Primo [ 10000] ,Primo2[10000];
uint32_t NPrimo ;
typedef cntree::vector_tree_cnc <uint32_t>          VT;

void Generation ( void)
{	//------------------ Definición de constantes------------
    cout<<"Generation ----------------------------->";
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
    cout<<"End generation \n";
};
void Criba ( VT & VTC ,typename VT::iterator  Alfa , uint32_t NElem)
{   //----------------------- begin--------------------
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
};

int  main ( void)
{   cout<<"----------------------------------------------------------------------------\n";
    cout<<"This program store "<<NELEM<<" numbers of 32 bits in a vector_tree\n"    ;
    cout<<"The time measured is the process of delete the prime numbers ( around 10%)\n";
    cout<<"done with several threads such as cores have the processor\n";
    cout<<"----------------------------------------------------------------------------\n";
    Generation() ;
    std::thread  T [8] ;
    typename VT::iterator Ini[8];
    uint32_t NE [8] ;
    const uint32_t Cupo = NELEM / NCores ;

    VT VTC ;
    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.push_back ( RANDOM | 1 ) ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   Ini[i] = VTC.begin() + ( i * Cupo);
        NE[i]=  ((i*Cupo)> NELEM)?(NELEM-(i-1)* Cupo):Cupo ;
    }


    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Criba,std::ref( VTC), Ini[i], NE[i] ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };
    cout<<VTC.size()<<" elements stored at end of the process\n";

    return 0 ;
};
