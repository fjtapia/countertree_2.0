//----------------------------------------------------------------------------
/// @file test_cntree_vector.cpp
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
namespace c_forest = countertree::forest ;
namespace c_common = countertree::common ;
namespace cntree = countertree ;

using c_common::size_type ;


int InsercionBinaria ( const cntree::cntree_vector<int> &A , int Valor) ;
int BusquedaBinaria ( const cntree::cntree_vector<int> &A , int Valor);


void prueba1 (void)
{   //------------------------ Inicio -----------------------------
	//std::cout<<"Prueba1\n";
    cntree::cntree_vector<int32_t > A ;

    A.insert_pos( 0,9 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,8 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,7 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,6 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,5 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,4 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,3 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,2 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0,1 ) ;      BOOST_CHECK (A.check() );
    A.insert_pos( 0, 0 ) ;     BOOST_CHECK (A.check() );

    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(A[i] == i );

    cntree::cntree_vector<int32_t> B ( A.begin(), A.end());
    BOOST_CHECK (B.check() );

    for ( int i =0  ; i < 10 ;++i)  BOOST_CHECK(B[i] == i );

    cntree::cntree_vector <int32_t> C ( (signed_type) 10, (int32_t)7 );
    BOOST_CHECK (C.check() );
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(C[i] == 7 );

    //std::cout<<A<<std::endl ;
    cntree::cntree_vector<int32_t> D( A);
    BOOST_CHECK (D.check() );
    //std::cout<<D<<std::endl ;
    for ( int i =0  ; i < 10 ;++i)
        BOOST_CHECK(D[i] == i );

    cntree::cntree_vector <int32_t,true,std::allocator<uint32_t> > K (D);
    BOOST_CHECK ( K.size() == 10);
    K.clear() ;
    K = D ;
    BOOST_CHECK ( K.size() == 10);

    cntree::cntree_vector <int32_t,true,std::allocator<void> > Q ( std::move ( D));
    BOOST_CHECK ( Q.size() == 10 and D.size() == 0 );
    D = std::move( Q);
    BOOST_CHECK ( Q.size() == 0 and D.size() == 10 );

    //-------------------------------------------------------------------
    // rvalue test and swap
    //-------------------------------------------------------------------
    cntree::cntree_vector<int32_t> H( std::move(A));
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

    D.assign( A.begin() , A.end());
    for ( int i =0  ; i < 10 ;++i)  BOOST_CHECK(D[i] == i );
    BOOST_CHECK (D.check() );
    BOOST_CHECK (A.check() );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        BOOST_CHECK (A[i] == i );

    for ( int32_t i = 0 ; i<A.size() ; i ++)
        BOOST_CHECK (A.at( i) == i );

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

    BOOST_CHECK ( D.capacity() == D.max_size() );
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

    cntree::cntree_vector<int32_t>::iterator PAux  ;
    for ( int32_t i = 0 ; i < 10 ; i ++ )
    {   PAux = A.iterator_pos( 0);
        BOOST_CHECK ( *PAux == i  );
        A.erase (PAux);
        BOOST_CHECK (A.check() );
    };
    cntree::cntree_vector<int32_t>::reverse_iterator Alfa , Beta ;

    int i ;
    //for ( Alfa = A.begin() ,  i = 0  ; Alfa != A.end() ; --Alfa,++i)
    //    BOOST_CHECK (*Alfa == i);

    for ( i = 9 , Alfa = A.rbegin() ; Alfa != A.rend() ; ++Alfa,--i)
        BOOST_CHECK (*Alfa == i);

}


void prueba2 ( void)
{   //---------------------- Variables----------------------------
	//std::cout<<"Prueba2\n";
    cntree::cntree_vector<int> M1 , M2;

    M1.insert_pos( 0, 1003) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 0, 1001) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 2, 1005) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 0, 1000) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 2, 1002) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 4, 1004) ;       BOOST_CHECK (M1.check()  );
    M1.insert_pos( 6, 1006) ;       BOOST_CHECK (M1.check()  );

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
    {   M2.push_front( 10 + 9 -i  );
        BOOST_CHECK ( M2.check());
    };
    for (int i = 0 ; i < 10; i ++ )
    {   M2.push_back ( 20 + i  );
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

    M1.insert ( M1.begin() +1, 50);

    BOOST_CHECK (M1.check()  );
    M1.insert ( M1.begin(), (size_type)10 , 1000);
    BOOST_CHECK (M1.check()  );

    M1.insert ( M1.begin()+ 10, M2.begin() , M2.end());
    BOOST_CHECK (M1.check()  );

    for ( int i =0 ; i < 10 ; ++i)
        BOOST_CHECK ( M1[i] == 1000);
    for ( int i = 10 ; i < 20 ; i++)
        BOOST_CHECK ( M1[i] == i +4);
    BOOST_CHECK ( M1[20] == 100);
    BOOST_CHECK ( M1[21] == 50);
    BOOST_CHECK ( M1[22] == 0);
    BOOST_CHECK ( M1.size() == 23);

};


void prueba3 ( void)
{   //---------------------- Variables----------------------------
	//std::cout<<"Prueba3\n";
    int Numero [1000];

    //------------------------ Inicio -----------------------------
    int Aux[1000] ;
    unsigned i ;

    for (  i = 0 ; i < 1000; i ++ )
        Numero[i] = rand() % 100000 ;

    cntree::cntree_vector<int> M1 ;
    for ( i = 0 ; i < 1000; i ++ )
    {   M1.insert_pos (   InsercionBinaria ( M1, Numero[i] ),Numero[i]  );
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

int InsercionBinaria ( const cntree::cntree_vector<int> &A , int Valor)
{   if ( A.size() == 0 ) return 0 ;
    int li = -1,ls = A.size(), p;
    while ( (ls -li) > 1 )
    {   p= ( ls +li) /2 ;
        if ( A[p] > Valor ) ls = p ;
        else                li = p ;
    };
    return ls ;
};
int BusquedaBinaria ( const cntree::cntree_vector<int> &A , int Valor)
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
	//std::cout<<"Prueba4\n";
    cntree::cntree_vector<int> M1, M2, M3 ;
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
	//std::cout<<"Prueba5\n";
    cntree::cntree_vector<int >  V1, V2, V3 ;
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
    //std::cout<<"Prueba6\n";
    typedef cntree::cntree_vector <int,true> VInt ;
    VInt    V1, V2 ;
    cntree::cntree_vector< VInt,true > VT1 ;

    for ( int i =0 ; i < 10 ; i++) V1.push_back ( i) ;

    //----------------------------------------------------------------------
    //     back
    //----------------------------------------------------------------------
    VT1.push_back ( V1 );
    V1.push_back (100);
    VT1.push_back ( V1);
    VT1.pop_move_back( V2);
    BOOST_CHECK ( V2.size() == 11);
    V2.clear() ;
    VT1.push_back ( V1 );
    VT1.pop_copy_back( V2);
    BOOST_CHECK ( V2.size() == 11);
    VT1.push_back ( V2);

    //-----------------------------------------------------------------------
    //    front
    //-----------------------------------------------------------------------
    VT1.pop_move_front( V2);
    BOOST_CHECK ( V2.size() == 10);

    VT1.push_front ( V2 );
    VT1.pop_copy_front( V2);
    BOOST_CHECK ( V2.size() == 10);
    //----------------------------------------------------------------------
    // if back
    //----------------------------------------------------------------------
    unsigned code ;
    int K ;
    V2 = V1 ;
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
void prueba7 ( void)
{   //--------------------------- begin --------------------------------------
	//std::cout<<"Prueba7\n";
    cntree::cntree_vector<int,false> V1, V2,V3,V4 ;

    for ( int i =0 ; i < 10 ; ++i)
    {   V1.push_back ( i) ;
        V2.push_front(i);
        V3.emplace_back(i);
        V4.emplace_front(i);
    };
    BOOST_CHECK ( V1.size() == 10 and V2.size() == 10 and
                  V3.size() == 10 and V4.size() == 10 );
    for ( int i = 0 ; i < 10 ;++i)
    {   BOOST_CHECK ( V1[i] == i  and V1[i]== V2[9-i]);
        BOOST_CHECK ( V3[i] == i  and V3[i]== V4[9-i]);
    };
    V1.clear() ;
    V2.clear() ;
    V3.clear() ;
    V4.clear() ;

    auto M = [] ( const int &A)->bool { return ( (A&1)==0 );};

    for ( int i =0 ; i < 10 ; ++i)
    {   V1.push_back_if     (i, M) ;
        V2.push_front_if    (i, M);
        V4.emplace_front_if (M, i);
        V3.emplace_back_if  (M, i);

    };
    BOOST_CHECK ( V1.size() == 5 and V2.size() == 5 and
                  V3.size() == 5 and V4.size() == 5 );

    for ( int i = 0 ; i < 5 ;++i)
    {   BOOST_CHECK ( V1[i] == i*2  and V1[i]== V2[4-i]);
        BOOST_CHECK ( V3[i] == i*2  and V3[i]== V4[4-i]);
    };
    V1.clear() ;
    V2.clear() ;
    V3.clear() ;
    V4.clear() ;

    for ( int i =0 ; i < 10 ; i+=2)
    {   V1.push_back ( i);
        V2.push_back( i);
    };
    for ( int i =1 ; i < 10 ; i+=2)
    {   V1.insert_pos( i,i);
        V2.emplace_pos(i , i);
    };
    BOOST_CHECK ( V1.size() == 10 and V2.size() == 10);
    for ( int i = 0 ; i < 10 ;++i)
    {   BOOST_CHECK ( V1[i] == i  and V2[i] == i );
    };
    V1.clear() ;
    V2.clear() ;
    for ( int i =0 ; i < 10 ; i+=2)
    {   V1.push_back ( i);
        V2.push_back( i);
    };
    auto M3 = [] ( const int &A )->bool { return ( A<10) ;};
    for ( int i =1 ; i < 10 ; i+=2)
    {   V1.insert_pos_if( i,i,M3);
        V1.insert_pos_if( i,i+100, M3);
        V2.emplace_pos_if(i , M3,i);
        V2.emplace_pos_if(i , M3,i+100);
    };
    BOOST_CHECK ( V1.size() == 10 and V2.size() == 10);
    for ( int i = 0 ; i < 10 ;++i)
    {   BOOST_CHECK ( V1[i] == i  and V2[i] == i );
    };

    V1.clear() ;
    V2.clear() ;
    V3.clear() ;
    V4.clear() ;
    for ( int i =0 ; i < 10 ; i+=2)
    {   V1.push_back ( i);
        V2.push_back( i);
    };
    for ( int i =1 ; i < 10 ; i+=2)
    {   V1.insert_if( V1.iterator_pos(i),i,M3);
        V1.insert_if( V1.iterator_pos(i),i+100, M3);
        V2.emplace_if(V2.iterator_pos(i) , M3,i);
        V2.emplace_if(V2.iterator_pos(i) , M3,i+100);
    };
    BOOST_CHECK ( V1.size() == 10 and V2.size() == 10);
    for ( int i = 0 ; i < 10 ;++i)
    {   BOOST_CHECK ( V1[i] == i  and V2[i] == i );
    };
    V1.clear() ;
    //-----------------------------------------------------------------------
    //     ERASE
    //-----------------------------------------------------------------------
    for ( int i =0 ; i <100 ; ++i)
        V1.push_back ( i);
    V2 = V1 ;
    BOOST_CHECK ( V1.size() == 100);
    for ( int i =0  ; i < 100 ; ++i)
        BOOST_CHECK ( V1[i] == i );

    V1.pop_back() ;
    BOOST_CHECK ( V1.size() == 99 and V1[98] == 98) ;
    V1.pop_front() ;
    BOOST_CHECK ( V1.size() == 98 and V1[97] == 98 and V1[0] == 1 ) ;

    V1 = V2 ;
    BOOST_CHECK ( V1.size() == 100);
    V1.pop_back_if ( M);
    BOOST_CHECK ( V1.size() == 100);
    V1.pop_front_if ( M)     ;
    BOOST_CHECK ( V1.size() == 99 and V1[0] == 1 );

    V1 = V2 ;
    V1.erase ( V1.cbegin() +50);
    BOOST_CHECK ( V1.size() == 99 and V1[50] == 51 );
    V1.erase_if ( V1.cbegin() +41, M);
    BOOST_CHECK ( V1.size() == 99  );
    V1.erase_if ( V1.cbegin() +40, M);
    BOOST_CHECK ( V1.size() == 98 and V1[40] == 41 );
    V1.erase_pos ( 20);
    BOOST_CHECK ( V1.size() == 97 and V1[20] == 21 );
    V1.erase_pos_if ( 11,M);
    BOOST_CHECK ( V1.size() == 97 and V1[20] == 21 );
    V1.erase_pos_if ( 10,M);
    BOOST_CHECK ( V1.size() == 96 and V1[10] == 11 );
    V1 = V2 ;
    V1.erase ( V1.cbegin() +50, V1.cbegin() +70 );
    BOOST_CHECK ( V1.size() == 80 and V1[ 50] == 70);
    V1.erase_pos ( 40 , 40) ;
    BOOST_CHECK ( V1.size() == 40 );
    for ( int i =0  ; i < 40 ;++i)
        BOOST_CHECK ( V1[i] == i);
    V1 = V2 ;
    V1.erase_if ( V1.begin() +50, V1.end(), M);
    BOOST_CHECK ( V1.size() == 75);
    for ( int i =50 ; i < 75 ; ++i )
        BOOST_CHECK ( V1[i] == 51 + ( i-50)*2 ) ;
    V1.erase_pos_if ( 0 , 50 , M);
    BOOST_CHECK ( V1.size() == 50);
    for ( int i = 0  ; i < 50 ; ++i)
        BOOST_CHECK ( V1[i] == i*2+1);

    //-----------------------------------------------------------------------
    //                              MODIFICATIONS
    //-----------------------------------------------------------------------
    V1 = V2 ;
    V1.modify ( V1.begin() + 50, 70);
    BOOST_CHECK ( V1[50] == 70 );

    V1.modify_pos ( 20, 40 );
    BOOST_CHECK ( V1[20] == 40  );

    auto suma10 = [] ( int &A) { A+=10;};
    V1.modify ( V1.begin() + 11,suma10);
    BOOST_CHECK ( V1[11] == 21);
    V1.modify ( V1.begin() + 10,suma10);
    BOOST_CHECK ( V1[10] == 20);
    V1.modify_pos ( 60, suma10);
    BOOST_CHECK ( V1[60] == 70 );


}
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
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba7 ) );
    return 0;
}
