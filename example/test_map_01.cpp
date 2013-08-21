///----------------------------------------------------------------------------
// FILE : testMap_01.cpp
//
// DESCRIPTION : Test program of the class map
//
// MODIFICATIONS (AUTHOR,DATE,REASON) :
//  Copyright (c) 2010 Francisco José Tapia (fjtapia@gmail.com )
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// NOTES :
//-----------------------------------------------------------------------------
#include <boost/countertree/map.hpp>
#include <iostream>

using std::endl;
using std::ostream ;
using std::cout ;

typedef std::pair<const int, double> PID ;

ostream & operator << ( ostream &salida, const PID &P)
{   //------------------- begin -----------------------
    salida<<"("<<P.first<<" , "<<P.second<<")  ";
    return salida ;
};
ostream & operator <<( ostream & salida , const countertree::map<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};
ostream & operator <<( ostream & salida , const countertree::multimap<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};
void SinRepeticiones( void) ;
void ConRepeticiones ( void);

int main ( void)
{   SinRepeticiones( ) ;
    ConRepeticiones ( );
};


void SinRepeticiones ( void )
{   //---------------------------- begin ------------------------
    cout<<"-------------------------------------------------------\n";
    cout<<"                 Pruebas con map\n";
    cout<<"-------------------------------------------------------\n";
    countertree::map<int, double> M1 ;
    //typedef std::pair<const int, double> PID ;

    PID A ( 3 , 7.3), B ( 5 , 8.4), C (7, 9.4), D(9,0.7);
    M1.insert( A) ;
    M1.insert( B) ;
    M1.insert( C) ;
    M1[8]= 6.3;
    M1[5] = 4.8 ;
    M1.insert (D) ;
    countertree::map <int,double> M2 ( M1 );

    cout<<M2;
    countertree::map<int,double>::iterator Alfa,Beta;

    for ( Alfa = M1.begin() ; Alfa != M1.end() ; Alfa ++)
        cout<<(*Alfa);
    cout<<endl;
    countertree::map<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
    cout<<M3 ;
    M2 = M3 ;
    cout<<M2 ;
    M2 = M1 ;
    Alfa = M2.begin() +2 ;
    M2.erase ( Alfa);
    cout<<M2;
    M2 = M1 ;
    M2.erase ( M2.begin() +1 , M2.end() -1);
    cout<<M2 ;
    M2 = M1 ;
    M2.erase (8);
    cout<<M2 ;
    M2.swap ( M3 ) ;
    cout<<M2 ;
    Alfa = M1.find( 5);
    cout<<(*Alfa)<<endl;
    Alfa = M1.lower_bound (4);
    Beta = M1.upper_bound (9);
    while ( Alfa != Beta)
    {   cout<<(*Alfa)<<"  ";
        ++Alfa;
    };
    cout<<endl ;
};

void ConRepeticiones ( void )
{   //---------------------------- begin ------------------------
    cout<<"-------------------------------------------------------\n";
    cout<<"                 Pruebas con multimap\n";
    cout<<"-------------------------------------------------------\n";
    countertree::multimap<int, double> M1 ;
    //typedef std::pair<int, double> PID ;

    PID A ( 3 , 7.3), B ( 5 , 8.4), C (7, 9.4), D(9,0.7);
    M1.insert( A) ;
    M1.insert( B) ;
    M1.insert( C) ;
    M1.insert( D) ;


    M1.insert( A) ;
    M1.insert( B) ;
    M1.insert( C) ;
    M1.insert( D) ;


    countertree::multimap <int,double> M2 ( M1 );
    cout<<M1<<endl;
    cout<<M2;
    countertree::multimap<int,double>::iterator Alfa,Beta;

    for ( Alfa = M1.begin() ; Alfa != M1.end() ; Alfa ++)
        cout<<(*Alfa);
    cout<<endl;
    countertree::multimap<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
    cout<<M3 ;
    M2 = M3 ;
    cout<<M2 ;
    M2 = M1 ;
    Alfa = M2.begin() +2 ;
    M2.erase ( Alfa);
    cout<<M2;
    M2 = M1 ;
    M2.erase ( M2.begin() +1 , M2.end() -1);
    cout<<M2 ;
    M2 = M1 ;
    M2.erase (8);
    cout<<M2 ;
    M2.swap ( M3 ) ;
    cout<<M2 ;

    cout<<"--------------------------- find------------------\n";
    cout<<M1<<endl;
    Alfa = M1.find( 5);
    cout<<(*Alfa)<<endl;

    Alfa = M1.lower_bound (4);
    Beta = M1.upper_bound (9);
    while ( Alfa != Beta)
    {   cout<<(*Alfa)<<"  ";
        ++Alfa;
    };
    cout<<endl;

};
