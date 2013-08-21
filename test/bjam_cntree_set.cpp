//----------------------------------------------------------------------------
/// @file test_set.cpp
/// @brief Test program of the classes countertree::set and countertree::multiset
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#define __DEBUG_CNTREE 1
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/cntree_set.hpp>
#include <boost/countertree/cntree_multiset.hpp>
#include <iostream>

#define NELEM   1000000
int V[NELEM];

using namespace boost::unit_test;
namespace c_forest = countertree::forest ;
using namespace countertree;

struct counter
{   int N ;
    counter ( void):N(-1){};
    counter ( int K):N(K){};
    counter ( const counter &c):N( c.N){};
    counter ( counter &&c):N(c.N) { c.N = -1;};
    counter & operator = ( const counter &c)
    {   N = c.N;
        return *this ;
    };
    counter & operator = ( counter &&c)
    {   N = c.N;
        c.N = -1;
        return *this ;
    };

    bool operator < ( const counter & c)const  { return ( this->N < c.N) ;};
    bool operator > ( const counter & c)const  { return ( this->N > c.N) ;};
};


void prueba1()
{   //------------------ begin ---------------
    cntree_set<int> s;
    int i ;
    cntree_set<int>::iterator Alfa, Beta;
    s.insert(1);
    s.insert(3);
    s.insert(5);
    s.insert(7);
    s.insert(9);
    s.insert(11);
    s.insert(13);
    s.insert(15);

    for ( i = 1 , Alfa = s.begin();Alfa != s.end(); ++Alfa, i+=2)
        BOOST_CHECK ( *Alfa == i );
    //---------------------------------------------------------
    // Pruebas con rvalues
    //---------------------------------------------------------
    cntree_set<int> s2( std::move (s));

    for ( i = 1 , Alfa = s2.begin();Alfa != s2.end(); ++Alfa, i+=2)
        BOOST_CHECK ( *Alfa == i );
    s = std::move(s2);
    s2= s ;
    cntree_set<int>::reverse_iterator Delta ;

    for ( i = 15 , Delta = s.rbegin();Delta < (s.rend()); ++Delta, i-=2 )
        BOOST_CHECK ( *Delta == i );

    for (  i =1 ; i < 17 ; i+=2)
       BOOST_CHECK (s.find ( i) != s.end() ) ;
    s.erase( 3 );

    BOOST_CHECK ( s.pos(0) == 1);
    BOOST_CHECK ( s.pos(1) == 5);
    BOOST_CHECK ( s.pos(2) == 7);
    BOOST_CHECK ( s.pos(3) == 9);
    BOOST_CHECK ( s.pos(4) == 11);
    BOOST_CHECK ( s.pos(5) == 13);
    BOOST_CHECK ( s.pos(6) == 15);

    s.erase( s.begin() + 2 );
    s.erase( s.begin() + 2 , s.begin() + 5);
    BOOST_CHECK ( s.pos(0) == 1);
    BOOST_CHECK ( s.pos(1) == 5);
    BOOST_CHECK ( s.pos(2) == 15);

    cntree_multiset<int> ms(s2);

    ms.clear();

    ms.insert(1);
    ms.insert(3);
    ms.insert(5);
    ms.insert(7);
    ms.insert(3);
    ms.insert(9);
    ms.insert(3);
    ms.insert(11);
    ms.insert(13);
    ms.insert(15);

    BOOST_CHECK ( ms.pos(0) == 1);
    BOOST_CHECK ( ms.pos(1) == 3);
    BOOST_CHECK ( ms.pos(2) == 3);
    BOOST_CHECK ( ms.pos(3) == 3);
    BOOST_CHECK ( ms.pos(4) == 5);
    BOOST_CHECK ( ms.pos(5) == 7);
    BOOST_CHECK ( ms.pos(6) == 9);
    BOOST_CHECK ( ms.pos(7) == 11);
    BOOST_CHECK ( ms.pos(8) == 13);
    BOOST_CHECK ( ms.pos(9) == 15);

    //-----------------------------------------------------
    // Pruebas con rvalues
    //-----------------------------------------------------
    cntree_multiset<int> ms2(std::move (ms));
    BOOST_CHECK ( ms2.pos(0) == 1);
    BOOST_CHECK ( ms2.pos(1) == 3);
    BOOST_CHECK ( ms2.pos(2) == 3);
    BOOST_CHECK ( ms2.pos(3) == 3);
    BOOST_CHECK ( ms2.pos(4) == 5);
    BOOST_CHECK ( ms2.pos(5) == 7);
    BOOST_CHECK ( ms2.pos(6) == 9);
    BOOST_CHECK ( ms2.pos(7) == 11);
    BOOST_CHECK ( ms2.pos(8) == 13);
    BOOST_CHECK ( ms2.pos(9) == 15);

    ms = std::move( ms2);

    ms.erase( 3 );
    ms.erase( ms.begin() + 2 );
    ms.erase( ms.begin() + 2 , ms.begin() + 5);

    BOOST_CHECK ( ms.pos(0) == 1);
    BOOST_CHECK ( ms.pos(1) == 5);
    BOOST_CHECK ( ms.pos(2) == 15);
}
void prueba2()
{   //------------------ begin ---------------
    cntree_set<int,true, std::less<int>, std::allocator <int> > SAux;
    for ( int i =0 ; i < 100 ; ++i)
        SAux.insert ( i );
    BOOST_CHECK ( SAux.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SAux.pos(i) == i) ;

    cntree_set<int> S1 ( SAux)    ;
    //cntree_set<int,false, std::less<int>> S1 ( SAux)    ;
    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;
    S1.clear() ;
    S1 = SAux ;
    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;

    //---------------------------------------------------------------
    cntree_set<int, true, std::less<int>,std::allocator<void> > SC ( std::move(S1));
    BOOST_CHECK ( SC.size() == 100 and S1.size() == 0);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SC.pos(i) == i) ;

    S1 = std::move(SC) ;
    BOOST_CHECK ( S1.size() == 100 and SC.size() == 0);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;

    cntree_set<int> S3 ( S1.begin() , S1.end());
    BOOST_CHECK ( S3.size() == 100 );
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i) == i) ;

};

void prueba3()
{   //------------------ begin ---------------
    cntree_multiset<int,true, std::less<int>, std::allocator <int> > SAux;
    for ( int i =0 ; i < 100 ; ++i)
        SAux.insert ( i );
    BOOST_CHECK ( SAux.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SAux.pos(i) == i) ;
    cntree_set<int,false, std::less<int>, std::allocator <int> > SAux2( SAux.begin(), SAux.end());
    cntree_multiset<int,true, std::less<int>, std::allocator <int> > SAux3( SAux2);
    BOOST_CHECK ( SAux3.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SAux3.pos(i) == i) ;
    SAux.clear() ;
    SAux = SAux2 ;
    BOOST_CHECK ( SAux.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SAux.pos(i) == i) ;

    cntree_multiset<int> S1 ( SAux)    ;
    //cntree_set<int,false, std::less<int>> S1 ( SAux)    ;
    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;
    S1.clear() ;
    S1 = SAux ;
    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;
    cntree_set<int,true >  SX (SAux2);
    BOOST_CHECK ( SX.size() == 100);
    cntree_multiset<int> MS1 ( std::move ( SX));
    BOOST_CHECK ( MS1.size() == 100);
     for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( MS1.pos(i) == i) ;
    SX.clear() ;
    SX.insert ( SAux2.begin() , SAux2.end());
    MS1.clear() ;
    MS1 = std::move ( SX );
    BOOST_CHECK ( MS1.size() == 100);
     for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( MS1.pos(i) == i) ;
    //---------------------------------------------------------------
    cntree_multiset<int, true, std::less<int>,std::allocator<void> > SC ( std::move(S1));
    BOOST_CHECK ( SC.size() == 100 and S1.size() == 0);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( SC.pos(i) == i) ;

    S1 = std::move(SC) ;
    BOOST_CHECK ( S1.size() == 100 and SC.size() == 0);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i) == i) ;

    cntree_multiset<int> S3 ( S1.begin() , S1.end());
    BOOST_CHECK ( S3.size() == 100 );
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i) == i) ;

};
void prueba4 ( void)
{   //---------------------------- begin -------------------------

    typedef cntree_set <int,true> VInt ;
    VInt    V1, V2 ;
    unsigned code ;
    int K ;

    for ( int i =0 ; i < 10 ; i++) V1.insert ( i) ;
    V1.insert(100);
    BOOST_CHECK ( V1.size() == 11);
    V2 = V1 ;
    //----------------------------------------------------------------------
    //     back
    //----------------------------------------------------------------------
    V1.pop_move_back( K);
    BOOST_CHECK ( V1.size() == 10 and K == 100);

    V1.pop_copy_back( K);
    BOOST_CHECK ( V1.size() == 9 and K == 9 );


    //-----------------------------------------------------------------------
    //    front
    //-----------------------------------------------------------------------
    V1 = V2 ;
    V1.pop_move_front( K);
    BOOST_CHECK ( V1.size() == 10 and K == 0);

    V1.pop_copy_front( K);
    BOOST_CHECK ( V1.size() == 9 and K == 1);
    //----------------------------------------------------------------------
    // if back
    //----------------------------------------------------------------------

    V1 = V2 ;
    auto M = [] ( const int &A)->bool { return ( A ==100 );};
    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 0 and K == 100 and V1.size() == 10 );

    code = V1.pop_copy_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M2 = [] ( const int &A)->bool { return ( A ==9 );};
    code = V1.pop_copy_back_if (K,M2);
    BOOST_CHECK (code == 0 and K == 9 and V1.size() ==9);

    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

    //----------------------------------------------------------------------
    // if front
    //----------------------------------------------------------------------
    V1 = V2 ;
    auto M3 = [] ( const int &A)->bool { return ( A ==0 );};
    code = V1.pop_move_front_if (K,M3);
    BOOST_CHECK (code == 0 and K == 0 and V1.size() == 10 );

    code = V1.pop_copy_front_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M4 = [] ( const int &A)->bool { return ( A ==1 );};
    code = V1.pop_copy_front_if (K,M4);
    BOOST_CHECK (code == 0 and K == 1 and V1.size() ==9);

    code = V1.pop_move_front_if (K,M4);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

};
void prueba5 ( void)
{   //---------------------------- begin -------------------------

    typedef cntree_multiset <int,true> VInt ;
    VInt    V1, V2 ;
    unsigned code ;
    int K ;

    for ( int i =0 ; i < 10 ; i++) V1.insert ( i) ;
    V1.insert(100);
    BOOST_CHECK ( V1.size() == 11);
    V2 = V1 ;
    //----------------------------------------------------------------------
    //     back
    //----------------------------------------------------------------------
    V1.pop_move_back( K);
    BOOST_CHECK ( V1.size() == 10 and K == 100);

    V1.pop_copy_back( K);
    BOOST_CHECK ( V1.size() == 9 and K == 9 );


    //-----------------------------------------------------------------------
    //    front
    //-----------------------------------------------------------------------
    V1 = V2 ;
    V1.pop_move_front( K);
    BOOST_CHECK ( V1.size() == 10 and K == 0);

    V1.pop_copy_front( K);
    BOOST_CHECK ( V1.size() == 9 and K == 1);
    //----------------------------------------------------------------------
    // if back
    //----------------------------------------------------------------------

    V1 = V2 ;
    auto M = [] ( const int &A)->bool { return ( A ==100 );};
    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 0 and K == 100 and V1.size() == 10 );

    code = V1.pop_copy_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M2 = [] ( const int &A)->bool { return ( A ==9 );};
    code = V1.pop_copy_back_if (K,M2);
    BOOST_CHECK (code == 0 and K == 9 and V1.size() ==9);

    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

    //----------------------------------------------------------------------
    // if front
    //----------------------------------------------------------------------
    V1 = V2 ;
    auto M3 = [] ( const int &A)->bool { return ( A ==0 );};
    code = V1.pop_move_front_if (K,M3);
    BOOST_CHECK (code == 0 and K == 0 and V1.size() == 10 );

    code = V1.pop_copy_front_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M4 = [] ( const int &A)->bool { return ( A ==1 );};
    code = V1.pop_copy_front_if (K,M4);
    BOOST_CHECK (code == 0 and K == 1 and V1.size() ==9);

    code = V1.pop_move_front_if (K,M4);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

};
void conditional_norep ()
{   //---------------------------- begin -------------------------
    cntree_set<int,true >  S1,S2 ;
    auto M1 = [] ( const int & k)->bool{ return ((k&1) == 0 );};

    // ---------- insert_if ----------------------
    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);

    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == i );
    S2.insert ( S1.begin(), S1.end() );
    BOOST_CHECK ( S2.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S2.pos(i)  == i );
    S2.clear() ;

    S2.insert_if ( S1.begin(), S1.end() , M1);
    BOOST_CHECK ( S2.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S2.pos(i)  == (i *2));

    S1.clear() ;
    S2.clear() ;

    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert_if ( M1,i);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i *2));

    S1.clear() ;
    S2.clear() ;

    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);
    S1.pop_front() ;
    S1.pop_back() ;

    BOOST_CHECK ( S1.size() == 98);
    for ( int i = 0 ; i < 98 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == i+1 );

    S1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);
    S2 = S1 ;
    S1.erase ( S1.begin()+50);
    BOOST_CHECK ( S1.pos(50) == 51);
    S1 = S2 ;
    S2.erase_if(S2.begin() +50, M1 );
    S2.erase_if(S2.begin() +49, M1 );
    BOOST_CHECK ( S2.pos(49) == 49)  ;
    BOOST_CHECK ( S2.pos(50) == 51)  ;
    S2 = S1 ;
    S1.erase_pos( 50);
    BOOST_CHECK ( S1.pos(50)== 51 );
    S1 = S2 ;
    S1.erase_pos_if (50, M1 );
    S1.erase_pos_if (49, M1 );
    BOOST_CHECK ( S1.pos(49) == 49)  ;
    BOOST_CHECK ( S1.pos(50) == 51)  ;

    S1 = S2 ;
    S1.erase ( S1.begin() , S1.const_iterator_pos (50));
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i+ 50));

    S1 = S2 ;
    S1.erase_if ( S1.begin() , S1.end(), M1);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i*2)+1);

    S1 = S2 ;
    S1.erase_pos ( 0 , 50);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i+ 50));
    S1 = S2 ;
    S1.erase_pos_if ( 0 , 100, M1);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i*2)+1);

    S1 = S2 ;
    S1.erase ( 50);
    BOOST_CHECK ( S1.pos(50) == 51 );

    S1 = S2 ;
    S1.erase_if (50, M1 );
    S1.erase_if (49, M1 );
    BOOST_CHECK ( S1.pos(49) == 49)  ;
    BOOST_CHECK ( S1.pos(50) == 51)  ;


    //---------------- rvalues --------------------
    cntree_set <counter> S3,S4 ;

    for ( int i =0 ; i < 100 ; ++i)
    {   counter C3 ( i);
        S3.insert ( std::move(C3) );
        BOOST_CHECK ( C3.N == -1);
    }

    BOOST_CHECK ( S3.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == i );
    S3.clear() ;

    auto M2 = [] ( const counter & k)->bool{ return ((k.N&1) == 0 );};
    for ( int i =0 ; i < 100 ; ++i)
    {   counter C3 ( i);
        S3.insert_if (M2, std::move(C3) );
    }
    BOOST_CHECK ( S3.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == (i *2));
    S3.clear();

    for ( int i =0 ; i < 100 ; ++i)
        S3.insert( counter(i));
    BOOST_CHECK ( S3.size() == 100);

    S4.insert_if  ( S3.begin(), S3.end() , M2);
    BOOST_CHECK ( S4.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S4.pos(i).N  == (i *2));
    S3.clear() ;
    for ( int i =0 ; i < 100 ; ++i)
        S3.emplace( i);
    BOOST_CHECK ( S3.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == i );

    S3.clear() ;
    for ( int i =0 ; i < 100 ; ++i)
        S3.emplace_if(M2, i);

    BOOST_CHECK ( S3.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == (i *2));
};
void conditional_rep ()
{   //---------------------------- begin -------------------------
    cntree_multiset<int,true >  S1,S2 ;
    auto M1 = [] ( const int & k)->bool{ return ((k&1) == 0 );};

    // ---------- insert_if ----------------------
    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);

    BOOST_CHECK ( S1.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == i );
    S2.insert ( S1.begin(), S1.end() );
    BOOST_CHECK ( S2.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S2.pos(i)  == i );
    S2.clear() ;

    S2.insert_if ( S1.begin(), S1.end() , M1);
    BOOST_CHECK ( S2.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S2.pos(i)  == (i *2));

    S1.clear() ;
    S2.clear() ;

    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert_if ( M1,i);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i *2));

    S1.clear() ;
    S2.clear() ;

    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);
    S1.pop_front() ;
    S1.pop_back() ;

    BOOST_CHECK ( S1.size() == 98);
    for ( int i = 0 ; i < 98 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == i+1 );

    S1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        S1.insert ( i);
    S2 = S1 ;
    S1.erase ( S1.begin()+50);
    BOOST_CHECK ( S1.pos(50) == 51);
    S1 = S2 ;
    S2.erase_if(S2.begin() +50, M1 );
    S2.erase_if(S2.begin() +49, M1 );
    BOOST_CHECK ( S2.pos(49) == 49)  ;
    BOOST_CHECK ( S2.pos(50) == 51)  ;
    S2 = S1 ;
    S1.erase_pos( 50);
    BOOST_CHECK ( S1.pos(50)== 51 );
    S1 = S2 ;
    S1.erase_pos_if (50, M1 );
    S1.erase_pos_if (49, M1 );
    BOOST_CHECK ( S1.pos(49) == 49)  ;
    BOOST_CHECK ( S1.pos(50) == 51)  ;

    S1 = S2 ;
    S1.erase ( S1.begin() , S1.const_iterator_pos (50));
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i+ 50));

    S1 = S2 ;
    S1.erase_if ( S1.begin() , S1.end(), M1);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i*2)+1);

    S1 = S2 ;
    S1.erase_pos ( 0 , 50);
    BOOST_CHECK ( S1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i+ 50));
    S1 = S2 ;
    S1.erase_pos_if ( 0 , 100, M1);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S1.pos(i)  == (i*2)+1);

    S1 = S2 ;
    S1.erase ( 50);
    BOOST_CHECK ( S1.pos(50) == 51 );

    S1 = S2 ;
    S1.erase_if (50, M1 );
    S1.erase_if (49, M1 );
    BOOST_CHECK ( S1.pos(49) == 49)  ;
    BOOST_CHECK ( S1.pos(50) == 51)  ;


    //---------------- rvalues --------------------
    cntree_set <counter> S3,S4 ;

    for ( int i =0 ; i < 100 ; ++i)
    {   counter C3 ( i);
        S3.insert ( std::move(C3) );
        BOOST_CHECK ( C3.N == -1);
    }

    BOOST_CHECK ( S3.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == i );
    S3.clear() ;

    auto M2 = [] ( const counter & k)->bool{ return ((k.N&1) == 0 );};
    for ( int i =0 ; i < 100 ; ++i)
    {   counter C3 ( i);
        S3.insert_if (M2, std::move(C3) );
    }
    BOOST_CHECK ( S3.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == (i *2));
    S3.clear();

    for ( int i =0 ; i < 100 ; ++i)
        S3.insert( counter(i));
    BOOST_CHECK ( S3.size() == 100);

    S4.insert_if  ( S3.begin(), S3.end() , M2);
    BOOST_CHECK ( S4.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S4.pos(i).N  == (i *2));
    S3.clear() ;
    for ( int i =0 ; i < 100 ; ++i)
        S3.emplace( i);
    BOOST_CHECK ( S3.size() == 100);
    for ( int i = 0 ; i < 100 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == i );

    S3.clear() ;
    for ( int i =0 ; i < 100 ; ++i)
        S3.emplace_if(M2, i);

    BOOST_CHECK ( S3.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( S3.pos(i).N  == (i *2));
};
void SinRepeticiones ( void)
{   //------------------- begin -------------------------
    //int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    cntree_set<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
        A.insert( V[i] );

    cntree_set<int> B(A) ;
    BOOST_CHECK ( A.size() == B.size());
    cntree_set<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    BOOST_CHECK ( C.size() == B.size() and A.size() != B.size());

    cntree_set<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   BOOST_CHECK ( (*Alfa) == A.pos(i) );
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);

    for ( int i = 0 ; i < NELEM ; ++i)
    {   BOOST_CHECK ( A.find( V[i]) != A.end() );
    };

    BOOST_CHECK (  A.find( A.pos(0) -1) == A.end() );

    cntree_set<int>::iterator Beta ;
    Alfa = A.lower_bound( (*(A.begin() +10))-1 );
    Beta = A.upper_bound ( (A.pos ( A.size() -10)) +1);
    signed_type Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

    std::pair<cntree_set<int>::iterator,cntree_set<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    Dif = Gama.second - Gama.first ;
    for (int32_t i = 0 ; i < Dif ; i++, Gama.first++);
    BOOST_CHECK ( Gama.first == Gama.second);

    Gama = A.equal_range( A.pos(10) );
    Dif = Gama.second - Gama.first ;
    for ( int32_t i = 0 ; i < Dif ; i++, Gama.first++);
    BOOST_CHECK ( Gama.first == Gama.second);

};

void ConRepeticiones ( void)
{   //-------------------- begin -------------------------
    //int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    cntree_multiset<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
    {   A.insert( V[i] );
        A.insert( V[i] );
        A.insert( V[i] );
    };

    cntree_multiset<int> B(A) ;
    BOOST_CHECK  (A.size() == B.size() );
    cntree_multiset<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    BOOST_CHECK  (C.size() == B.size() and A.size() != B.size() );

    cntree_multiset<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   BOOST_CHECK ( (*Alfa) == A.pos(i) );;
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);

    for ( int i = 0 ; i < NELEM ; ++i)
    {   BOOST_CHECK (A.find( V[i]) != A.end() );
    };
    BOOST_CHECK (A.find( A.pos(0) -1) == A.end() );

    cntree_multiset<int>::iterator Beta ;
    Alfa = A.lower_bound( *(A.begin() +10)-1 );
    Beta = A.upper_bound ( A.pos ( A.size() -10) +1);
    signed_type Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

    std::pair<cntree_multiset<int>::iterator,cntree_multiset<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );


    Gama = A.equal_range( A.pos(10) );
    Dif = Beta - Alfa ;
    for ( int i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

};
void SinRepeticion2 ( void)
{   //------------------ Variables----------------
    cntree_set<int> M1;
    int i  ;

    for ( i = 1000 ; i < 3000 ; i+= 2)
    {   M1.insert ( i  );
        M1.insert ( i );
    };
    BOOST_CHECK ( M1.size() == 1000);

    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i) == (1000 + i*2) );
    };

    cntree_set<int>::iterator Gamma ;
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK (  Gamma == M1.end() );
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK (Gamma != M1.end() and Gamma == M1.begin()  );

    Gamma = M1.find(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == ( M1.end()-1 ) );

    Gamma = M1.find(999);
    BOOST_CHECK (Gamma == M1.end()  );

    Gamma = M1.find(2999);
    BOOST_CHECK ( Gamma == M1.end());


    //---- lower_bound to all existing elements ----------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //--- lower_bound to non existing elements ---------------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //-- lower_bound : first, last, less than first, greater than last ----
    Gamma = M1.lower_bound(1000);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == ( M1.end() -1 ) );

    Gamma = M1.lower_bound(999);
    BOOST_CHECK (Gamma == M1.begin() and Gamma != ( M1.begin() -1 )  );

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK (  Gamma == M1.end() );


    //------- loop for existing elements ------------------------------
    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2)) );
    };

    // --------- loop for non existing elements ---
    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (*Gamma)  == ( 1000 + i * 2)) );
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK ( (*Gamma) == 1002 );

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK ( Gamma == M1.end() );

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() );

    std::pair < cntree_set<int>::iterator, cntree_set<int>::iterator > PI ;

    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ( (PI.second.pos() - PI.first.pos() ) == 1 and PI.first.pos() == i );
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ( (PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i );
    };
};

void ConRepeticion2 ( void)
{   //---------------------- Variables----------------------------
    cntree_multiset<int> M1;
    int i  ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert ( 1000+ i *2 );
        M1.insert ( 1000+ i *2 );
        M1.insert ( 1000+ i *2 );
    };
    BOOST_CHECK ( M1.size() == 3000);
    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i*3) == (1000 + i*2) and
                      M1.pos(i*3 +1) == (1000 + i*2) and
                      M1.pos(i*3 +2) == (1000 + i*2)  );
    };

    // -------- Loop for find existing elements -------------------
    cntree_multiset<int>::iterator Gamma ;
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and  (*Gamma) == (1000+i*2) and
                    (*(Gamma++)) == (1000+i*2) and  (*(Gamma++)) == (1000+i*2) );
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK ( Gamma == M1.end() );
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin() );

    Gamma = M1.find(2998);
    BOOST_CHECK (Gamma != M1.end() and Gamma == (M1.end() -3)  );

    Gamma = M1.find(999);
    BOOST_CHECK ( Gamma == M1.end() );

    Gamma = M1.find(2999);
    BOOST_CHECK ( Gamma == M1.end() );

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
                    (*(Gamma++))==(1000+i*2) and (*(Gamma++))==(1000+i*2) );
    };

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
                     (*(Gamma++))==(1000+i*2) and (*(Gamma++))==(1000+i*2) );
    };

    Gamma = M1.lower_bound(1000);
    BOOST_CHECK ( Gamma == M1.begin() and Gamma == M1.begin() );

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK (Gamma != M1.end() and Gamma == (M1.end() -3)  );

    Gamma = M1.lower_bound(999);
    BOOST_CHECK ( Gamma == M1.begin()  );

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK ( Gamma == M1.end() );

    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2)) );
    };

    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK (Gamma != M1.end() and ( (*Gamma) == ( 1000 + i * 2))  );
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK (  (*Gamma) == 1002 );

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK ( Gamma == M1.end( ));

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() );

    std::pair < cntree_multiset<int>::iterator, cntree_multiset<int>::iterator > PI ;

    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ( (PI.second.pos() - PI.first.pos() ) == 3 and PI.first.pos() == i*3 );
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ( (PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i*3 );
    };
};
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba3 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba4 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba5 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &conditional_norep ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &conditional_rep ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticiones ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticiones ) );
     framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticion2 ) );
    return 0;
}
