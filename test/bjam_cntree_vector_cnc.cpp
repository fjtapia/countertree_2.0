//----------------------------------------------------------------------------
/// @file test_cntree_vector_cnc.cpp
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
#include <boost/countertree/cntree_vector.hpp>
#include <algorithm>
#include <vector>

using std::cout ;
using std::endl;
using namespace boost::unit_test;
#define NELEM 1000000
namespace c_forest = countertree::forest;
namespace cntree = countertree;
cntree::cntree_vector <uint32_t, true> VTC ;
using countertree::common::size_type ;

typedef typename cntree::cntree_vector <uint32_t,true>::iterator vt_iterator ;
static const uint32_t HC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = ( HC > 4)?4 :HC ;
uint32_t Primo [ 10000] ;
uint32_t NPrimo ;

int InsercionBinaria ( const cntree::cntree_vector<int,true> &A , int Valor) ;
int BusquedaBinaria ( const cntree::cntree_vector<int,true> &A , int Valor);

void prueba1 (void)
{   //------------------------ Inicio -----------------------------
    cntree::cntree_vector<int32_t, true> A ;

    A.insert_pos( 0,9 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,8 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,7 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,6 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,5 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,4 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,3 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,2 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,1 ) ;
    ASSERT (A.check() );
    A.insert_pos( 0,0 ) ;
    ASSERT (A.check() );

    for ( int i =0  ; i < 10 ;++i)
    {   ASSERT(A[i] == i );
        //std::cout<<A[i]<<"  ";
    } ;
    //std::cout<<std::endl;

    cntree::cntree_vector<int32_t,true> B ( A.begin(), A.end());
    ASSERT (B.check() );

    for ( int i =0  ; i < 10 ;++i)  ASSERT(B[i] == i );

    cntree::cntree_vector <int32_t,true> C ( (signed_type)10, (int32_t)7 );
    ASSERT (C.check() );
    for ( int i =0  ; i < 10 ;++i)  ASSERT(C[i] == 7 );


    cntree::cntree_vector<int32_t,true> D( A);
    ASSERT (D.check() );
    for ( int i =0  ; i < 10 ;++i)  ASSERT(D[i] == i );

    //-------------------------------------------------------------------
    // rvalue test and swap
    //-------------------------------------------------------------------
    cntree::cntree_vector<int32_t,true> H( std::move(A));
    ASSERT (H.check() );
    ASSERT (A.check() );
    ASSERT (A.size() == 0 and H.size() == 10 );
    A = std::move ( H)  ;
    ASSERT (H.check() );
    ASSERT (A.check() );
    ASSERT (H.size() == 0 and A.size() == 10 );

    std::swap ( A, H)   ;
    ASSERT (H.check() );
    ASSERT (A.check() );
    ASSERT (A.size() == 0 and H.size() == 10 );
    std::swap ( A, H)   ;
    ASSERT (H.check() );
    ASSERT (A.check() );
    ASSERT (H.size() == 0 and A.size() == 10 );

    //------------ end test rvalue --------------------------
    D.resize (5) ;
    ASSERT (D.check() );
    for ( int i =0  ; i < 5 ;++i)   ASSERT(D[i] == i );

    D.resize(10);
    ASSERT (D.check() );
    for ( int i =0  ; i < 5 ;++i)   ASSERT(D[i] == i );
    for ( int i =5  ; i < 10 ;++i)  ASSERT(D[i] == 0 );

    D.assign( A.begin() , A.end());
    for ( int i =0  ; i < 10 ;++i)  ASSERT(D[i] == i );
    ASSERT (D.check() );
    ASSERT (A.check() );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        ASSERT (A[i] == i );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        ASSERT (A.at( i) == i );

    ASSERT( A.front() == 0 );
    ASSERT ( A.back() == 9  );

    std::vector<int>  E ;

    for ( int i =0  ; i < 10 ; ++i )
        E.push_back ( i );

    ASSERT ( E.size() == 10);
    for ( int32_t i = 0 ; i<10 ; i ++)
        ASSERT (E[i] == i );

    D.clear() ;
    ASSERT ( D.empty() );

    ASSERT ( D.capacity() == D.max_size() );
    D.assign ( E.begin(), E.end());
    ASSERT ( D.size() == 10);
    for ( int32_t i = 0 ; i<10 ; i ++)
        ASSERT (D[i] == i );


    C.clear() ;
    ASSERT ( C.empty() and A.size() == 10 );
    C.swap ( A );
    ASSERT ( A.empty() and C.size() == 10 );
    C.swap ( A );
    C = A ;
    ASSERT ( C.size() == 10);

    cntree::cntree_vector<int32_t,true>::iterator PAux  ;
    for ( int32_t i = 0 ; i < 10 ; i ++ )
    {   PAux = A.iterator_pos( 0);
        ASSERT ( *PAux == i  );
        A.erase (PAux);
        ASSERT (A.check() );
    };
    cntree::cntree_vector<int32_t,true>::reverse_iterator Alfa , Beta ;

    int i ;
    //for ( Alfa = A.begin() ,  i = 0  ; Alfa != A.end() ; --Alfa,++i)
    //    ASSERT (*Alfa == i);

    for ( i = 9 , Alfa = A.rbegin() ; Alfa != A.rend() ; ++Alfa,--i)
        ASSERT (*Alfa == i);

};


void prueba2 ( void)
{   //---------------------- Variables----------------------------
    cntree::cntree_vector<int,true> M1 , M2;

    M1.insert_pos( 0, 1003) ;       assert (M1.check()  );
    M1.insert_pos( 0, 1001) ;       assert (M1.check()  );
    M1.insert_pos( 2, 1005) ;       assert (M1.check()  );
    M1.insert_pos( 0, 1000) ;       assert (M1.check()  );
    M1.insert_pos( 2, 1002) ;       assert (M1.check()  );
    M1.insert_pos( 4, 1004) ;       assert (M1.check()  );
    M1.insert_pos( 6, 1006) ;       assert (M1.check()  );

    for ( int i =0 ; i < 7 ; i++)
        assert ( M1[i] == 1000+i );

    M2 = M1 ;
    assert (M2.check()  );
    for ( int i =0 ; i < 7 ; i++)
        assert ( M2[i] == 1000+i );

    M1.erase_pos(6) ;       assert (M1.check()  );
    M1.erase_pos(0) ;       assert (M1.check()  );
    M1.erase_pos(0) ;       assert (M1.check()  );
    M1.erase_pos(3) ;       assert (M1.check()  );
    M1.erase_pos(1) ;       assert (M1.check()  );
    M1.erase_pos(1) ;       assert (M1.check()  );
    M1.erase_pos(0) ;       assert (M1.check()  );
    assert ( M1.size() == 0);

    M2.clear() ;
    M1.clear() ;
    assert (M1.check() and M2.check()  );

    for (int i = 0 ; i < 10; i ++ )
    {   M2.push_front( 10 + 9 -i  );
        assert ( M2.check());
    };
    for (int i = 0 ; i < 10; i ++ )
    {   M2.push_back ( 20 + i  );
        assert ( M2.check());
    };
    for ( int i = 0 ; i < 4; i ++ )
    {   M2.pop_front( );
        assert ( M2.check());
    };
    for ( int i = 0 ; i < 6; i ++ )
    {   M2.pop_back ( );
        assert ( M2.check());
    };

    M1.clear() ;
    M1.push_front (100);
    assert (M1.check()  );
    M1.push_back(0 );
    assert (M1.check()  );

    M1.insert ( M1.begin() +1, 50);

    assert (M1.check()  );
    M1.insert ( M1.begin(), (size_type)10 , 1000);
    assert (M1.check()  );

    M1.insert ( M1.begin()+ 10, M2.begin() , M2.end());
    assert (M1.check()  );

    for ( int i =0 ; i < 10 ; ++i)
        assert ( M1[i] == 1000);
    for ( int i = 10 ; i < 20 ; i++)
        assert ( M1[i] == i +4);
    assert ( M1[20] == 100);
    assert ( M1[21] == 50);
    assert ( M1[22] == 0);
    assert ( M1.size() == 23);
};

void prueba3 ( void)
{   //---------------------- Variables----------------------------
    int Numero [1000];

    //------------------------ Inicio -----------------------------
    int Aux[1000] ;
    unsigned i ;

    for (  i = 0 ; i < 1000; i ++ )
        Numero[i] = rand() % 100000 ;

    cntree::cntree_vector<int,true> M1 ;
    for ( i = 0 ; i < 1000; i ++ )
    {   M1.insert_pos (  InsercionBinaria ( M1, Numero[i] ), Numero[i]  );
        assert (M1.check());
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
    assert (M1.check());

    for ( i = 0; i < 1000 ; i ++ )
    {   assert ( M1[i] == Aux[i]);
    };
    for ( i = 0 ; i < 1000 ; i ++ )
    {   M1.erase_pos ( BusquedaBinaria ( M1,Numero[i] ) ) ;
        assert (M1.check());
    };
    assert (M1.check());
};

int InsercionBinaria ( const cntree::cntree_vector<int,true> &A , int Valor)
{   if ( A.size() == 0 ) return 0 ;
    int li = -1,ls = A.size(), p;
    while ( (ls -li) > 1 )
    {   p= ( ls +li) /2 ;
        if ( A[p] > Valor ) ls = p ;
        else                li = p ;
    };
    return ls ;
};
int BusquedaBinaria ( const cntree::cntree_vector<int,true> &A , int Valor)
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
    cntree::cntree_vector<int,true> M1, M2, M3 ;
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

};

void prueba5 ( void)
{   //---------------------------- begin -------------------------
    cntree::cntree_vector<int,true >  V1, V2, V3 ;
    std::vector<int> V4 ;

    for ( int i = 3998 ; i >= 2000 ; i-=2 )
        V1.push_back ( i);
    assert ( V1.size() == 1000);

    std::sort ( V1.begin(), V1.end());
    for ( int i =0 ; i < 999 ; ++i)
    {   if ( V1[i] > V1[i+1]) assert ( false );
    };

    for ( int i = 2000 ; i < 4000 ; i += 2)
    {   if ( not std::binary_search ( V1.begin() , V1.end(), i) )
            assert ( false );
    };

    for ( int i = 3999 ; i >= 2000 ; i-=2)
        V2.push_back ( i);

    std::sort ( V2.begin(), V2.end());

    std::set_union(V1.begin(),V1.end(),V2.begin(),V2.end(),std::back_inserter(V3));
    assert ( V3.size() == 2000);
    std::sort ( V3.begin(), V3.end());
    for ( int i =0 ; i < 1999 ; ++i)
    {   if ( V3[i] > V3[i+1]) assert ( false );
    };

    std::set_union(V1.begin(),V1.end(),V2.begin(),V2.end(),std::back_inserter(V4));
    assert ( V4.size() == 2000);
};
void Generation ( void)
{	//------------------ Definición de constantes------------
    Primo[0] = 2 ;
    Primo[1] = 3 ;
    Primo[2] = 5;
    Primo[3] = 7;
    Primo[4] = 11;
    Primo[5] = 13 ;
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

};
void Criba ( vt_iterator  Alfa , uint32_t NElem)
{   //----------------------- begin--------------------
    //std::cout<<"Inicio ----->"<<std::this_thread::get_id()<<"  " ;
    //std::cout<<(*Alfa )<<" "<<NElem<<std::endl ;
    vt_iterator Beta = Alfa;
    for ( uint32_t i =0 ; i < NElem ; ++i)
    {   Alfa = Beta ;
        Beta = Alfa +1 ;
        uint32_t N = *Alfa ;
        bool EsPrimo = true ;
        for (uint32_t k = 0 ; k < NPrimo and EsPrimo; ++k)
        {   if ( (N%Primo[k]) == 0) EsPrimo = false ;
        };
        if ( not EsPrimo) VTC.erase ( Alfa);
    };
    //std::cout<<"Fin -------->"<<std::this_thread::get_id()<<std::endl ;
};
void prueba6 ( void)
{   //--------------------------------- begin ------------------
    Generation() ;
    //std::cout<<"Numeros Primos generados\n";
    //std::cout<<std::endl;

    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.push_back ( rand() | 1 ) ;
    //std::cout<<"Numeros Cargados \n";
    //std::cout<<std::endl;

    //for (uint32_t i =0 ; i < NELEM ;++i)
    //    std::cout<<"["<<i<<"] "<<VTC[i]<<" ";
    //std::cout<<std::endl<<std::endl<<std::endl;

    const uint32_t Cupo = NELEM / NCores ;
    vt_iterator Ini[4];
    uint32_t NE [4] ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   Ini[i] = VTC.begin() + ( i * Cupo);
        NE[i]=  ((i*Cupo)> NELEM)?(NELEM-(i-1)* Cupo):Cupo ;
    }

    std::thread  T [4] ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Criba, Ini[i], NE[i] ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };

    //for ( uint32_t i  =0 ; i < VTC.size() ; ++i)
    //    std::cout<<VTC[i]<<"  ";
    //std::cout<<std::endl<<std::endl ;
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
        add( BOOST_TEST_CASE( &prueba6 ) );
    return 0;
}
