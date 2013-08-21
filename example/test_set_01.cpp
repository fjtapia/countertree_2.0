//----------------------------------------------------------------------------
/// @file test_set_01.cpp
/// @brief test program of the class countertree::set
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <boost/countertree/set.hpp>
#include <iostream>

#define NELEM   100

using std::ostream ;
using std::endl ;
using std::cout ;


ostream & operator <<( ostream &salida , const countertree::set<int> & S)
{   //---------------------------- begin -----------------------------------
    salida<<"Number of Nodes "<<S.size()<<endl;
    countertree::set<int>::iterator Alfa ;
    for ( Alfa = S.begin() ; Alfa != S.end() ; Alfa ++)
        salida<<(*Alfa)<<"   ";
    salida<<endl ;
    return salida ;
};
std::ostream & operator <<( ostream &salida , const countertree::multiset<int> & S)
{   //---------------------------- begin -----------------------------------
    salida<<"Number of Nodes "<<S.size()<<endl;
    countertree::set<int>::iterator Alfa ;
    for ( Alfa = S.begin() ; Alfa != S.end() ; Alfa ++)
        salida<<(*Alfa)<<"   ";
    salida<<endl ;
    return salida ;
};
void ConRepeticiones ( void );
void SinRepeticiones ( void) ;

int main ( void )
{   SinRepeticiones() ;
    ConRepeticiones() ;
    return 0 ;
};

void SinRepeticiones ( void)
{   //------------------------------------ begin ---------------------------------
    int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    countertree::set<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
        A.insert( V[i] );

    countertree::set<int> B(A) ;
    countertree::set<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    cout<<B<<endl;

    countertree::set<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   if ( (*Alfa) != A.pos(i) )cout<<"Error Discordancia en el set\n";
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);
    cout<<B<<endl;
    for ( int i = 0 ; i < NELEM ; ++i)
    {   if ( A.find( V[i]) == A.end())
            cout<<"Error en la busqueda\n";
    };
    if ( A.find( A.pos(0) -1) != A.end())
        cout<<"Error en la operacion find\n";

    countertree::set<int>::iterator Beta ;
    Alfa = A.lower_bound( *(A.begin() +10)-1 );
    Beta = A.upper_bound ( A.pos ( A.size() -10) +1);
    while ( Alfa != Beta)
    {   cout<<(*Alfa)<<"   " ;
        ++Alfa;
    };
    cout<<endl<<endl;

    std::pair<countertree::set<int>::iterator,countertree::set<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    while ( Gama.first != Gama.second)
    {   cout<<(*Gama.first)<<endl;
        ++ Gama.first;
    };

    Gama = A.equal_range( A.pos(10) );
    while ( Gama.first != Gama.second)
    {   cout<<(*Gama.first)<<endl;
        ++ Gama.first;
    };
    cout<<endl;

};

void ConRepeticiones ( void)
{   //------------------------------------ begin ---------------------------------
    int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    countertree::multiset<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
    {   A.insert( V[i] );
        A.insert( V[i] );
        A.insert( V[i] );
    };

    countertree::multiset<int> B(A) ;
    countertree::multiset<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    cout<<B<<endl;

    countertree::multiset<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   if ( (*Alfa) != A.pos(i) )cout<<"Error Discordancia en el set\n";
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);
    cout<<B<<endl;
    for ( int i = 0 ; i < NELEM ; ++i)
    {   if ( A.find( V[i]) == A.end())
            cout<<"Error en la busqueda\n";
    };
    if ( A.find( A.pos(0) -1) != A.end())
        cout<<"Error en la operacion find\n";

    countertree::multiset<int>::iterator Beta ;
    Alfa = A.lower_bound( *(A.begin() +10)-1 );
    Beta = A.upper_bound ( A.pos ( A.size() -10) +1);
    while ( Alfa != Beta)
    {   cout<<(*Alfa)<<"   " ;
        ++Alfa;
    };
    cout<<endl<<endl;

    std::pair<countertree::multiset<int>::iterator,countertree::multiset<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    while ( Gama.first != Gama.second)
    {   cout<<(*Gama.first)<<endl;
        ++ Gama.first;
    };

    Gama = A.equal_range( A.pos(10) );
    while ( Gama.first != Gama.second)
    {   cout<<(*Gama.first)<<endl;
        ++ Gama.first;
    };
    cout<<endl;

};
