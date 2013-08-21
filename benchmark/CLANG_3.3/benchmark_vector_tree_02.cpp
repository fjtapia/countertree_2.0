///----------------------------------------------------------------------------
// FILE : test_vector_tree_02.cpp
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
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <stack>
#include <set>

#include <boost/countertree/vector_tree.hpp>
#include <boost/countertree/common/time_measure.hpp>

namespace  c_common= countertree::common ;
using c_common::time_point ;
using c_common::now ;
using c_common::subtract_time;

#define NELEM 100000
int A[NELEM];
using namespace countertree ;
using  std::set ;
using std::deque ;
using std::cout;
using std::endl;

template <class DS> void insert_first_last ( DS  & S );

template <class DS> void insert_aleatory ( DS  & S );

// Set STL de 100 elementos
typedef std::set <int , std::less <int> > Sint ;
Sint S1 ;

int  main ( void)
{   //-------------------------- begin -----------------------
    typedef    countertree::vector_tree <Sint > T1 ;
    typedef    std::deque               <Sint > T3 ;

    //---------------------- Variables----------------------------
    int i ,min , nivel ;
    T1 D1 ;
    T3 D3 ;


    for ( i = 0; i < 100 ; i ++ ) S1.insert ( i ) ;
    cout<<"=============================================================================\n";
    cout<<"             INSERTION / DELETION "<<NELEM <<"  OPERATIONS\n";
    cout<<"=============================================================================\n";

    //------------------------ Inicio -----------------------------
    // Carga de los numeros aleatorios en A
    for ( i =0 ; i < NELEM ; i ++ ) A[i] = RANDOM ;

    // Examen de la desviacion máxima
    min = 100 ;
    nivel = 0 ;
    for ( i = 0; i < NELEM ; i ++ )
    {   if ( (A[i] & 1)   == 0 )  nivel++;
        else
        {   nivel--;
            if ( nivel < min )
            {   A[i] &= 1 ;
                nivel += 2 ;
            };
        };
    };
    cout<<endl<<endl;
    cout<<"=============================================================\n";
    cout<<" INSERTION DELETION OF "<<NELEM<<" SET<INT> WITH 100 INTEGERS\n";
    cout<<" INSERT DELETE IN THE FIRST AND LAST POSITION \n";
    cout<<"=============================================================\n";


    //******************************************************************
    //
    //    C O M P A R A T I V A S   C O N    D E Q U E
    //
    //******************************************************************
    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<min <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < min ; i ++ ) D1.push_back(S1) ;
    cout<<"vector_tree :";
    insert_first_last ( D1 );
    D1.clear() ;

    for ( i = 0 ; i < min ; i ++ ) D3.push_back(S1) ;
    cout<<"deque :";
    insert_first_last ( D3 );
    D3.clear() ;

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<NELEM <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < NELEM ; i ++ ) D1.push_back(S1) ;
    cout<<"vector_tree :";
    insert_first_last ( D1 );
    D1.clear() ;

    for ( i = 0 ; i < NELEM ; i ++ ) D3.push_back(S1) ;
    cout<<"deque :";
    insert_first_last ( D3 );
    D3.clear() ;


    //----------------------------------------------------------------
    // Inserción y supresion de 1000000 elementos simples ( enteros)
    // con estructuras con muy pocos datos en posiciones aleatorias
    //----------------------------------------------------------------
    cout<<"=============================================================\n";
    cout<<" INSERTION DELETION OF "<<NELEM<<" SET<INT> WITH 100 INTEGERS\n";
    cout<<" INSERT DELETE IN RANDOM POSITIONs \n";
    cout<<"=============================================================\n";

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with "<<min <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < min ; i ++ ) D1.push_back(S1) ;
    cout<<"vector_tree :";
    insert_aleatory ( D1 );
    D1.clear() ;

    for ( i = 0 ; i < min ; i ++ ) D3.push_back(S1) ;
    cout<<"deque :";
    insert_aleatory ( D3 );
    D3.clear() ;

    cout<<"-----------------------------------------------------\n";
    cout<<" Data structure with  "<<NELEM <<" elements \n";
    cout<<"-----------------------------------------------------\n";

    for ( i = 0 ; i < NELEM ; i ++ ) D1.push_back(S1) ;
    cout<<"vector_tree :";
    insert_aleatory ( D1 );
    D1.clear() ;

    for ( i = 0 ; i < NELEM ; i ++ ) D3.push_back(S1) ;
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
                S.push_front (S1) ;
                break;
            case 1:
                S.pop_front () ;
                break ;
            case 2 :
                S.push_back(S1 ) ;
                break;
            case 3 :
                S.pop_back() ;
                break;
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
            S.insert (S.begin() +(A[i] % S.size()), S1) ;
        else
            S.erase(S.begin() + (A[i]%S.size()) ) ;
    };
    finish = now() ;
	duracion = subtract_time ( finish, start) ;
    cout<<"Time spent :"<<duracion<<" seconds\n";
};
