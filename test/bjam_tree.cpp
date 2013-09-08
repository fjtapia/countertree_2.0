//----------------------------------------------------------------------------
/// @file test_vector_tree.cpp
/// @brief Test program of the class countertree::vetor_tree
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
#include <iostream>
#include <stdlib.h>
#include <boost/countertree/forest/tree.hpp>
#include <boost/countertree/myallocator.hpp>
#include <algorithm>
#include <vector>

using std::cout ;
using std::endl;
using namespace boost::unit_test;
using namespace countertree::forest ;
using namespace countertree::common ;
int InsercionBinaria ( const tree<int> &A , int Valor) ;
int BusquedaBinaria ( const tree<int> &A , int Valor);
/*
void prueba0 ( void)
{   //--------------------- begin ------------------------
    typedef tree<int32_t, myallocator <node<int32_t>, false> > tree2 ;
    tree<int32_t> T1 ;
    for ( int32_t i =0 ; i < 10 ; ++i)
        T1.push_back ( i);
    BOOST_CHECK ( T1.size() == 10  );
    tree2 T2 ( T1);
    BOOST_CHECK ( T2.size() == 10  );
    tree<int32_t> T3 ( std::move(T1));
    BOOST_CHECK ( T3.size() == 10  );
    BOOST_CHECK ( T1.empty()  );
    T1 = std::move (T3);
    BOOST_CHECK ( T1.size() == 10  );
    BOOST_CHECK ( T3.empty()  );
    T2.clear() ;
    T2 = T1;
    BOOST_CHECK ( T2.size() == 10  );
    T3.assign( T2.begin(), T2.end());
    BOOST_CHECK ( T3.size() == 10  );
    T3.clear() ;
    T3.assign ( (unsigned_type)10,(int32_t)5);
    BOOST_CHECK ( T3.size() == 10  );
    T3= T1;
}
*/

void prueba1 (void)
{   //------------------------ Inicio -----------------------------
    tree<int32_t > A ;

    //A.push_back ( 100 );

    A.insert_pos( 0,9 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,8 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0, 7 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,6 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,5 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,4 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,3 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,2 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0,1 ) ;
    BOOST_CHECK (A.check() );
    A.insert_pos( 0, 0 ) ;
    BOOST_CHECK (A.check() );

    A = A ;
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(A[i] == i );

    A = std::move ( A );
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(A[i] == i );

    tree<int32_t > B ( A);
    BOOST_CHECK (B.check() );

    for ( int i =0  ; i < 10 ;++i)  BOOST_CHECK(B[i] == i );

    tree<int32_t > C ;
    C.assign( (signed_type) 10, (int32_t)7 );
    BOOST_CHECK (C.check() );
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(C[i] == 7 );

    //std::cout<<A<<std::endl ;
    tree<int32_t> D( A);
    BOOST_CHECK (D.check() );
    //std::cout<<D<<std::endl ;
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(D[i] == i );

    //-------------------------------------------------------------------
    // rvalue test and swap
    //-------------------------------------------------------------------
    tree<int32_t> H( std::move(A));
    BOOST_CHECK (H.check() );
    BOOST_CHECK (A.check() );
    BOOST_CHECK (A.size() == 0 and H.size() == 10 );
    A = std::move ( H)  ;
    BOOST_CHECK (H.check() );
    BOOST_CHECK (A.check() );
    BOOST_CHECK (H.size() == 0 and A.size() == 10 );

    std::swap ( A, H)   ;
    BOOST_CHECK (H.check() );
    BOOST_CHECK (A.check() );
    BOOST_CHECK (A.size() == 0 and H.size() == 10 );
    std::swap ( A, H)   ;
    BOOST_CHECK (H.check() );
    BOOST_CHECK (A.check() );
    BOOST_CHECK (H.size() == 0 and A.size() == 10 );

    //------------ end test rvalue --------------------------
    D.resize (5) ;
    BOOST_CHECK (D.check() );
    for ( int i =0  ; i < 5 ;++i)   BOOST_CHECK(D[i] == i );

    D.resize(10);
    BOOST_CHECK (D.check() );
    for ( int i =0  ; i < 5 ;++i)   BOOST_CHECK(D[i] == i );
    for ( int i =5  ; i < 10 ;++i)  BOOST_CHECK(D[i] == 0 );

    //D.assign( A.begin() , A.end());
    D = A ;
    //std::cout<<D<<std::endl;
    for ( int i =0  ; i < 10 ;++i)  BOOST_CHECK( D[i] == i );
    BOOST_CHECK (D.check() );
    BOOST_CHECK (A.check() );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        BOOST_CHECK (A[i] == i );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        BOOST_CHECK (A[i] == i );

    BOOST_CHECK( A.front() == 0 );
    BOOST_CHECK ( A.back() == 9  );

    std::vector<int>  E ;

    for ( int i =0  ; i < 10 ; ++i )
        E.push_back ( i );

    BOOST_CHECK ( E.size() == 10);
    for ( int32_t i = 0 ; i<10 ; i ++)
        BOOST_CHECK (E[i] == i );

    D.clear() ;
    BOOST_CHECK ( D.empty() );

    //BOOST_CHECK ( D.capacity() == D.max_size() );
    D.assign ( E.begin(), E.end());

    BOOST_CHECK ( D.size() == 10);
    for ( int32_t i = 0 ; i<10 ; i ++)
        BOOST_CHECK (D[i] == i );


    C.clear() ;
    BOOST_CHECK ( C.empty() and A.size() == 10 );
    C.swap ( A );
    BOOST_CHECK ( A.empty() and C.size() == 10 );
    C.swap ( A );
    C = A ;
    BOOST_CHECK ( C.size() == 10);

    tree<int32_t>::iterator PAux  ;
    for ( int32_t i = 0 ; i < 10 ; i ++ )
    {   PAux = A.iterator_pos( 0);
        BOOST_CHECK ( *PAux == i  );
        A.erase (PAux);
        BOOST_CHECK (A.check() );
    };
    tree<int32_t>::reverse_iterator Alfa , Beta ;

    int i ;
    //for ( Alfa = A.begin() ,  i = 0  ; Alfa != A.end() ; --Alfa,++i)
    //    BOOST_CHECK (*Alfa == i);
    A = D ;
    for ( i = 9 , Alfa = A.rbegin() ; Alfa != A.rend() ; ++Alfa,--i)
        BOOST_CHECK (*Alfa == i);
    auto M1 = [] ( const int & k)->bool{ return (k&1) == 0 ;};
    //std::cout<<A<<std::endl;
    A.erase_pos_if ( 0, A.size(), M1);
    BOOST_CHECK ( A.check());
    BOOST_CHECK ( A.size() == 5 );
    //std::cout<<A<<std::endl;
}

void prueba2 ( void)
{   //---------------------- Variables----------------------------
    countertree::forest::tree<int> M1 , M2;

    M1.emplace_pos( 0, 1003) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 0, 1001) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 2, 1005) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 0, 1000) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 2, 1002) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 4, 1004) ;       BOOST_CHECK (M1.check()  );
    M1.emplace_pos( 6, 1006) ;       BOOST_CHECK (M1.check()  );

    for ( int i =0 ; i < 7 ; i++)
        BOOST_CHECK ( M1[i] == 1000+i );

    M2 = M1 ;
    BOOST_CHECK (M2.check()  );
    for ( int i =0 ; i < 7 ; i++)
        BOOST_CHECK ( M2[i] == 1000+i );

    M1.erase_pos(6) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(0) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(0) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(3) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(1) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(1) ;       BOOST_CHECK (M1.check()  );
    M1.erase_pos(0) ;       BOOST_CHECK (M1.check()  );
    BOOST_CHECK ( M1.size() == 0);

    M2.clear() ;
    M1.clear() ;
    BOOST_CHECK (M1.check() and M2.check()  );

    for (int i = 0 ; i < 10; i ++ )
    {   M2.emplace_front( 10 + 9 -i  );
        BOOST_CHECK ( M2.check());
    };
    for (int i = 0 ; i < 10; i ++ )
    {   M2.emplace_back ( 20 + i  );
        BOOST_CHECK ( M2.check());
    };
    for ( int i = 0 ; i < 4; i ++ )
    {   M2.pop_front( );
        BOOST_CHECK ( M2.check());
    };
    for ( int i = 0 ; i < 6; i ++ )
    {   M2.pop_back ( );
        BOOST_CHECK ( M2.check());
    };

    M1.clear() ;
    M1.push_front (100);
    BOOST_CHECK (M1.check()  );
    M1.push_back(0 );
    BOOST_CHECK (M1.check()  );

    M1.emplace ( M1.begin() +1, 50);

    BOOST_CHECK (M1.check()  );
    for ( int i =0 ; i < 10 ; ++i)
        M1.push_front(1000);
    //M1.insert ( M1.begin(), (size_type)10 , 1000);
    BOOST_CHECK (M1.check()  );
    //std::cout<<M1<<std::endl;
    //std::cout<<M2<<std::endl;
    //M1.insert ( M1.begin()+ 10, M2.begin() , M2.end());
    countertree::forest::tree<int>::iterator Alfa = M1.begin()+ 10 , Beta = M2.begin() ;

    for (  ; Beta != M2.end() ; ++Beta)
        M1.insert ( Alfa , *Beta);
    //std::cout<<M1<<std::endl;
    BOOST_CHECK (M1.check()  );

    for ( int i =0 ; i < 10 ; ++i)
        BOOST_CHECK ( M1[i] == 1000);
    for ( int i = 10 ; i < 20 ; i++)
        BOOST_CHECK ( M1[i] == i +4);
    BOOST_CHECK ( M1[20] == 100);
    BOOST_CHECK ( M1[21] == 50);
    BOOST_CHECK ( M1[22] == 0);
    BOOST_CHECK ( M1.size() == 23);
    M1.erase_pos ( 0, M1.size());
    BOOST_CHECK ( M1.size() == 0);
};


void prueba3 ( void)
{   //---------------------- Variables----------------------------
    int Numero [1000];

    //------------------------ Inicio -----------------------------
    int Aux[1000] ;
    unsigned i ;

    for (  i = 0 ; i < 1000; i ++ )
        Numero[i] = rand() % 100000 ;

    tree<int> M1 ;
    for ( i = 0 ; i < 1000; i ++ )
    {   M1.insert_pos (   InsercionBinaria ( M1, Numero[i] ) ,Numero[i]  );
        BOOST_CHECK (M1.check());
     };
    for ( i = 0 ; i < 1000 ; i ++) Aux[i] = Numero[i] ;

    bool SW;
    do
    {   SW = false ;
        for ( i = 0 ; i < 999 ; i ++ )
        {   if ( Aux[i] > Aux [i+1] )
            {   int pp = Aux[i] ;
                Aux[i] = Aux[i+1] ;
                Aux[i+1] = pp ;
                SW = true ;
            };
        };
    }while ( SW );
    BOOST_CHECK (M1.check());

    for ( i = 0; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1[i] == Aux[i]);
    };
    for ( i = 0 ; i < 1000 ; i ++ )
    {   M1.erase_pos ( BusquedaBinaria ( M1,Numero[i] ) ) ;
        BOOST_CHECK (M1.check());
    };
    BOOST_CHECK (M1.check());
};

int InsercionBinaria ( const tree<int> &A , int Valor)
{   if ( A.size() == 0 ) return 0 ;
    int li = -1,ls = A.size(), p;
    while ( (ls -li) > 1 )
    {   p= ( ls +li) /2 ;
        if ( A[p] > Valor ) ls = p ;
        else                li = p ;
    };
    return ls ;
};
int BusquedaBinaria ( const tree<int> &A , int Valor)
{   if ( A.size() == 0 ) return -1 ;
    int li = 0, ls = A.size() -1, p ;
    while ( ls > li)
    {   p = (li + ls +1) /2 ;
        if ( A[p] > Valor) ls = p -1 ;
        else               li = p ;
    };
    if ( A[ls] == Valor ) return ls ;
    else                  return -1 ;
};

void prueba4 ( void)
{   //---------------------- Variables----------------------------
    countertree::forest::tree<int> M1, M2, M3 ;
    int i ;

    //------------------------ Inicio -----------------------------
    //------------------------ Inicio -----------------------------
    for ( i = 0 ; i < 50 ; i++ )
    {   M1.push_back (i +1000) ;
        BOOST_CHECK (M1.check() );
        M2.push_front ((49 -i) +2000 );
        BOOST_CHECK (M2.check() );
        M3.push_back (i +3000 );
        BOOST_CHECK (M3.check() );
    };
    for ( i = 0 ; i < 50 ; ++i)
    {   BOOST_CHECK ( M1[i] == 1000 + i );
        BOOST_CHECK ( M2[i] == 2000 + i );
        BOOST_CHECK ( M3[i] == 3000 + i );
    };

    M1.erase_pos ( 0, 50) ;
    M2.erase_pos ( 0, 50) ;
    M3.erase_pos ( 0, 50) ;
    BOOST_CHECK (M1.check() );
    BOOST_CHECK (M2.check() );
    BOOST_CHECK (M3.check() );

    for ( i = 0 ; i < 10 ; i++ )
    {   M1.push_back ( i +100 );
        BOOST_CHECK (M1.check() );
        M2.push_back ( i +200 );
        BOOST_CHECK (M2.check() );
        M3.push_back ( i +300 );
        BOOST_CHECK (M3.check() );
    };
    for ( i = 0 ; i < 10 ; ++i)
    {   BOOST_CHECK ( M1[i] == 100 + i );
        BOOST_CHECK ( M2[i] == 200 + i );
        BOOST_CHECK ( M3[i] == 300 + i );
    };

    M1.erase_pos( 1,5);
    M1.push_back( 111) ;
    BOOST_CHECK (M1[0] == 100 );
    BOOST_CHECK (M1[1] == 106 );
    BOOST_CHECK (M1[2] == 107 );
    BOOST_CHECK (M1[3] == 108 );
    BOOST_CHECK (M1[4] == 109 );
    BOOST_CHECK (M1[5] == 111 );

    M2.erase_pos (M2.size() -1 , M2.size() -1) ;
    M2.push_back(222) ;

    for ( int i =0 ; i < 9 ; i++)
        BOOST_CHECK ( M2[i] == 200 + i);
    BOOST_CHECK ( M2[9] == 222);

    M1.erase_pos ( 2, 4 ) ;
    M2.erase_pos(2,6) ;
    BOOST_CHECK (M1.check() and  M2.check());

    for ( i = 0 ; i < M2.size() ; i ++ )
    {   M1.push_back ( M2[i] ) ;
    };

    BOOST_CHECK (M1[0] == 100 );
    BOOST_CHECK (M1[1] == 106 );
    BOOST_CHECK (M1[2] == 200 );
    BOOST_CHECK (M1[3] == 201 );
    BOOST_CHECK (M1[4] == 208 );
    BOOST_CHECK (M1[5] == 222 );
    BOOST_CHECK (M1.check() );

    M1.clear() ;

    for ( i = 0 ; i < 1000000; i++ )
    {   M1.push_back( i) ;
        if ((i%1000) == 0) BOOST_CHECK ( M1.check() ) ;
    };

    for ( i = 0 ; i < 1000000; i += 100000)
    {   M1.erase_pos ( (900001 - i),  99999  );
        BOOST_CHECK ( M1.check() ) ;
    };
    for ( i = 0 ; i < M1.size(); i ++)
    {   BOOST_CHECK ( M1[i] == (i*100000) ) ;
    };
    M1.erase ( M1.begin(), M1.end());
    BOOST_CHECK ( M1.size() == 0);
    BOOST_CHECK ( M1.check());
};

void prueba5 ( void)
{   //---------------------------- begin -------------------------
    tree<int >  V1, V2, V3 ;
    std::vector<int> V4 ;

    for ( int i = 3998 ; i >= 2000 ; i-=2 )
        V1.push_back ( i);
    BOOST_CHECK ( V1.size() == 1000);

    std::sort ( V1.begin(), V1.end());
    for ( int i =0 ; i < 999 ; ++i)
    {   if ( V1[i] > V1[i+1]) BOOST_CHECK ( false );
    };

    for ( int i = 2000 ; i < 4000 ; i += 2)
    {   if ( not std::binary_search ( V1.begin() , V1.end(), i) )
            BOOST_CHECK ( false );
    };

    for ( int i = 3999 ; i >= 2000 ; i-=2)
        V2.push_back ( i);

    std::sort ( V2.begin(), V2.end());

    std::set_union(V1.begin(),V1.end(),V2.begin(),V2.end(),std::back_inserter(V3));
    BOOST_CHECK ( V3.size() == 2000);
    std::sort ( V3.begin(), V3.end());
    for ( int i =0 ; i < 1999 ; ++i)
    {   if ( V3[i] > V3[i+1]) BOOST_CHECK ( false );
    };

    std::set_union(V1.begin(),V1.end(),V2.begin(),V2.end(),std::back_inserter(V4));
    BOOST_CHECK ( V4.size() == 2000);
};
void prueba6 ( void)
{   //---------------------------- begin -------------------------
    tree<int >  V1, V2 ;

    for ( int i = 0 ; i < 100 ; ++i)
        V1.push_back ( i);
    BOOST_CHECK ( V1.size() == 100);
    tree<int>::iterator Alfa = V1.end() -1 ;
    auto M1 = [] ( const int & k)->bool{ return (k&1) == 0 ;};
    //std::cout<<( *Alfa)<<"  "<<( M1 ( *Alfa))<<std::endl;
    V1.erase_if (V1.begin(), V1.end(), M1);
    BOOST_CHECK ( V1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V1[i]  == (i *2)+1);

    V1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        V1.push_back ( i);
    BOOST_CHECK ( V1.size() == 100);
    V1.erase_pos_if ( 0, 99 , M1);
    BOOST_CHECK ( V1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V1[i]  == (i *2)+1);

    V1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        V1.push_back ( i);

    V2.assign_if ( V1.begin(), V1.end() , M1);
    BOOST_CHECK ( V2.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V2[i]  == (i *2));
};


test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    //framework::master_test_suite().
    //    add( BOOST_TEST_CASE( &prueba0 ) );
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
        add( BOOST_TEST_CASE( &prueba6 ) );
    return 0;
}
