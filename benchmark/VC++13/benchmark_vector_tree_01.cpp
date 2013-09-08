///----------------------------------------------------------------------------
// FILE : test_vector_tree_01.cpp
//
// DESCRIPTION :
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
#include <deque>
#include <time.h>
#include <boost/countertree/vector_tree.hpp>
#include <boost/countertree/common/time_measure.hpp>

namespace  c_common= countertree::common ;
using c_common::time_point ;
using c_common::now ;
using c_common::subtract_time;


#define NELEM 1000000
uint64_t A[NELEM];

template <class DS>
void insert_first_last ( DS  & S );

template <class DS>
void insert_aleatory ( DS  & S );

using std::cout ;
using std::endl;

int  main ( void)
{   //---------------------typedef ------------------------------
    typedef    countertree::vector_tree      <uint64_t > T2 ;
    typedef    std::deque                    <uint64_t > T3 ;

    //---------------------- Variables----------------------------
    int i ,min , nivel ;
    T2 D2 ;
    T3 D3 ;
    //------------------------ Inicio -----------------------------
    // Carga de los numeros aleatorios en A
    for ( i =0 ; i < NELEM ; i ++ ) A[i] = RANDOM ;

    // Examen de la desviacion máxima
    min = 100 ;
    nivel = 0 ;
    for ( i = 0; i < NELEM ; i ++ )
    {   if ( (A[i] & 1ULL)   == 0 )  nivel++;
        else
        {   nivel--;
            if ( nivel < min )
            {   A[i] &= ~1ULL ;
                nivel += 2 ;
            };
        };
    };


    //******************************************************************
    //
    //    C O M P A R A T I V A S   C O N    D E Q U E
    //
    //******************************************************************
    cout<<"=============================================================\n";
    cout<<"  INSERTION  AND DELETION OF "<<NELEM<<" INTEGERS OF 64 BITS\n";
    cout<<"  INSERTION AND DELETION IN THE FIRST AND LAST POSITION\n";
    cout<<"=============================================================\n";

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<min <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < min ; i ++ ) D2.push_back(i) ;
    cout<<"vector_tree :";
    insert_first_last ( D2 );
    D2.clear() ;

    for ( i = 0 ; i < min ; i ++ ) D3.push_back(i) ;
    cout<<"deque :";
    insert_first_last ( D3 );
    D3.clear() ;

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<NELEM <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < NELEM ; i ++ ) D2.push_back(i) ;
    cout<<"vector_tree :";
    insert_first_last ( D2 );
    D2.clear() ;

    for ( i = 0 ; i < NELEM ; i ++ ) D3.push_back(i) ;
    cout<<"deque :";
    insert_first_last ( D3 );
    D3.clear() ;

    cout<<endl<<endl;
    //----------------------------------------------------------------
    // Inserción y supresion de 1000000 elementos simples ( enteros)
    // con estructuras con muy pocos datos en posiciones aleatorias
    //----------------------------------------------------------------
    cout<<"=============================================================\n";
    cout<<"  INSERTION  AND DELETION OF "<<NELEM<<" INTEGERS OF 64 BITS\n";
    cout<<"  INSERTION AND DELETION IN RANDOM POSITION\n";
    cout<<"=============================================================\n";
    cout<<"-----------------------------------------------------\n";
    cout<<" Data structures with "<<min <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < min ; i ++ ) D2.push_back(i) ;
    cout<<"vector_tree :";
    insert_aleatory<T2> ( D2 );
    D2.clear() ;

    for ( i = 0 ; i < min ; i ++ ) D3.push_back(i) ;
    cout<<"deque :";
    insert_aleatory ( D3 );
    D3.clear() ;

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<NELEM <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < NELEM ; i ++ ) D2.push_back(i) ;
    cout<<"vector_tree :";
    insert_aleatory ( D2 );
    D2.clear() ;

    for ( i = 0 ; i < NELEM ; i ++ ) D3.push_back(i) ;
    cout<<"deque :";
    insert_aleatory ( D3 );
    D3.clear() ;

    return 0 ;
};

template <class DS>
void insert_first_last ( DS  & S )
{   //-------------------- begin ---------------------------------
    double duracion ;
	time_point start, finish;

    //----------- Definicion de los datos------------------------
    //cout<<" Insertion and deltetion if the first and last position-->";

    start = now() ;
    for ( int i = 0 ; i < NELEM ; i ++ )
    {   switch ( A[i] & 3)
        {   case 0:
                S.push_front (A[i]) ;
                break;
            case 1:
                S.pop_front () ;
                break ;
            case 2 :
                S.push_back(A[i] ) ;
                break;
            case 3 :
                S.pop_back() ;
                break;

            default:;
        };
    };
    finish = now() ;
	duracion = subtract_time ( finish, start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
};
template <class DS>
void insert_aleatory ( DS  & S )
{   //------------------------------- begin --------------------------------
    double duracion ;
	time_point start, finish;
    //----------------------------------------------------------------
    // Inserción y supresion de 1000000 elementos simples ( enteros)
    // con estructuras con muy pocos datos en posiciones aleatorias
    //----------------------------------------------------------------
    //cout<<" Insertion and deletion in random positions -->";

    //----------- Definicion de los datos------------------------
    start = now() ;
    for (int i = 0 ; i < NELEM ; i ++ )
    {   if ( A[i] %2==0)
            S.insert (S.begin() +(A[i] % S.size()), A[i]) ;
        else
            S.erase(S.begin() + (A[i]%S.size()) ) ;
    };
    finish = now() ;
	duracion = subtract_time ( finish, start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
};
