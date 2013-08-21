//----------------------------------------------------------------------------
/// @file test_sorted_vector_tree.cpp
/// @brief Test program of the class countertree::sorted_vector_tree
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
#include <boost/countertree/forest/sorted_tree.hpp>

using namespace boost::unit_test;
using std::cout ;
using std::endl ;

namespace cntree = countertree ;
namespace c_forest = countertree::forest ;
typedef c_forest::sorted_tree<int> srt_tree ;
typedef c_forest::sorted_tree <int, int ,
cntree::filter_set <int,int>, std::less<int>, std::allocator<int> > srt_tree2 ;

void prueba0 ( void)
{   //---------------- begin -------------------
    srt_tree ST1 ;
    for ( int i =0 ; i < 10 ; ++i)
        ST1.insert_value_norep ( i );
    BOOST_CHECK ( ST1.size() == 10);
    srt_tree ST2 ( ST1);
    BOOST_CHECK ( ST2.size() == 10);
    srt_tree ST3 ( std::move (ST1) );
    BOOST_CHECK ( ST3.size() == 10);
    BOOST_CHECK ( ST1.empty() );
    ST1 = std::move ( ST3);
    BOOST_CHECK ( ST1.size() == 10);
    BOOST_CHECK ( ST3.empty() );

    srt_tree2 ST4 ( ST1);
    BOOST_CHECK ( ST4.size() == 10);
    ST4.clear() ;
    BOOST_CHECK ( ST4.empty());
    ST4 = ST1;
    BOOST_CHECK ( ST4.size() == 10);
    BOOST_CHECK ( ST1.max_size() == ST4.max_size());

}




void prueba1 ( void)
{   //---------------------- Variables----------------------------
    c_forest::sorted_tree<int> M1 ;
    c_forest::sorted_tree<int>::iterator It1;
    std::pair <c_forest::sorted_tree<int>::iterator, bool > P1 ;
    M1.insert_value_norep(  1003 ) ;
    //cout<<M1<<endl;
    BOOST_CHECK ( M1.check() );

    M1.insert_value_norep(  1001 ) ;
    BOOST_CHECK ( M1.check() );

    M1.insert_value_norep(  1005 ) ;
    BOOST_CHECK ( M1.check() );

    M1.insert_value_norep(  1000 ) ;
    BOOST_CHECK ( M1.check() );

    M1.insert_value_norep(  1002 ) ;
    BOOST_CHECK ( M1.check() );

    M1.emplace_value_norep(  1004 ) ;
    BOOST_CHECK ( M1.check() );

    M1.emplace_value_norep(  1006 ) ;
    BOOST_CHECK ( M1.check() );

    P1 =M1.emplace_value_norep(  1002 ) ;
    BOOST_CHECK ( M1.check() );
    BOOST_CHECK ( *(P1.first) == 1002 );

    for ( int i = 0 ; i < 7 ; i ++)
        BOOST_CHECK (M1.pos(i)== 1000+ i );

    c_forest::sorted_tree<int>  M2(M1);
    BOOST_CHECK ( M2.check() );
    M2.clear() ;
    BOOST_CHECK (M2.size() == 0  );

    M2 = M1 ;
    BOOST_CHECK ( M2.check() );

    M1.erase_pos(6) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(0) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(0) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(3) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(1) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(1) ;
    BOOST_CHECK ( M1.check() );
    M1.erase_pos(0) ;
    BOOST_CHECK ( M1.check() );

    BOOST_CHECK ( M1.size() == 0);
    BOOST_CHECK ( M2.size() == 7);
    M1.swap(M2);
    BOOST_CHECK ( M2.size() == 0);
    BOOST_CHECK ( M1.size() == 7);
    BOOST_CHECK ( M1.check() and  M2.check());

    M2.clear() ;
    M1.clear() ;
    BOOST_CHECK ( M1.check() and  M2.check());

}

void SinRepeticion ( void)
{   //---------------------- Variables----------------------------
    c_forest::sorted_tree<int> M1;
    int i  ;

    for ( i = 1000 ; i < 3000 ; i+= 2)
    {   M1.insert_value_norep ( i  );
        M1.emplace_value_norep ( i );
        BOOST_CHECK ( M1.check() );
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK (M1.pos(i)== (1000 + i*2) );
    };

    c_forest::sorted_tree<int>::const_iterator Gamma ;
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find_norep( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2));
    };

    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find_norep( 1001+ i * 2);
        BOOST_CHECK ( Gamma == M1.end() );
    };

    Gamma = M1.find_norep(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin());

    Gamma = M1.find_norep(2998);
    BOOST_CHECK ( Gamma == (M1.end() - 1 ) and Gamma != M1.end());

    Gamma = M1.find_norep(999);
    BOOST_CHECK (Gamma == M1.end() );

    Gamma = M1.find_norep(2999);
    BOOST_CHECK (Gamma == M1.end() );

    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK (Gamma != M1.end()and  (*Gamma)== (1000+i*2) ) ;
    };

    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK (Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    Gamma = M1.lower_bound(1000);
    BOOST_CHECK (Gamma == M1.begin() and Gamma != M1.end() );

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK (Gamma != M1.end() and Gamma == ( M1.end()-1) ) ;

    Gamma = M1.lower_bound(999);
    BOOST_CHECK ( Gamma == M1.begin() and  Gamma != (M1.begin() -1 ));

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK ( Gamma == M1.end());

    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2)));
    };

    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (*Gamma)  == ( 1000 + i * 2)));
    };

    Gamma = M1.upper_bound ( 1000);     BOOST_CHECK ( (*Gamma) == 1002);
    Gamma = M1.upper_bound ( 2998);     BOOST_CHECK ( Gamma == M1.end() );
    Gamma = M1.upper_bound ( 3000);     BOOST_CHECK ( Gamma == M1.end() )  ;

    std::pair < c_forest::sorted_tree<int>::const_iterator , c_forest::sorted_tree<int>::const_iterator > PI ;

    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ((PI.second.pos() - PI.first.pos())==1 and PI.first.pos()== i);
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ((PI.second.pos() == PI.first.pos()) and PI.first.pos()== i);
    };
};

void ConRepeticion ( void)
{   //---------------------- Variables----------------------------
    c_forest::sorted_tree<int> M1;
    int i  ;
    c_forest::sorted_tree<int>::const_iterator Alfa , Beta ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert_value_rep ( 1000+ i *2 );
        BOOST_CHECK (M1.check())  ;
        M1.insert_value_rep ( 1000+ i *2 );
        BOOST_CHECK (M1.check())  ;
        M1.insert_value_rep ( 1000+ i *2 );
        BOOST_CHECK (M1.check())  ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i*3) == (1000 + i*2)    and
                      M1.pos(i*3 +1) == (1000 + i*2) and
                      M1.pos(i* 3 +2) == (1000 + i*2)   )  ;
    };

    c_forest::sorted_tree<int>::const_iterator Gamma ;
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find_rep( 1000+ i * 2);
        BOOST_CHECK  ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
            (*(Gamma++)) == (1000+i*2) and (*(Gamma++)) == (1000+i*2)) ;
    };

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find_rep( 1001+ i * 2);
        BOOST_CHECK  ( Gamma == M1.end() ) ;
    };

    Gamma = M1.find_rep(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin())  ;

    Gamma = M1.find_rep(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == (M1.end() -3))  ;

    Gamma = M1.find_rep(999);
    BOOST_CHECK ( Gamma == M1.end() )  ;

    Gamma = M1.find_rep(2999);
    BOOST_CHECK ( Gamma == M1.end() )  ;

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK  ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
            (*(Gamma++)) == (1000+i*2) and  (*(Gamma++)) == (1000+i*2)) ;
    };

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
             (*(Gamma++)) == (1000+i*2) and (*(Gamma++)) == (1000+i*2))  ;
    };

    Gamma = M1.lower_bound(1000);
    BOOST_CHECK  ( Gamma == M1.begin() and Gamma != M1.end()) ;

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == (M1.end() - 3))  ;

    Gamma = M1.lower_bound(999);
    BOOST_CHECK  ( Gamma == M1.begin() and Gamma != ( M1.begin() -1 )) ;

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK ( Gamma == M1.end() )  ;

    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK  ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2))) ;
    };

    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (*Gamma)  == ( 1000 + i * 2)))  ;
    };

    Gamma = M1.upper_bound ( 1000);     BOOST_CHECK ( (*Gamma) == 1002)  ;
    Gamma = M1.upper_bound ( 2998);     BOOST_CHECK  ( Gamma == M1.end() ) ;
    Gamma = M1.upper_bound ( 999);      BOOST_CHECK ( Gamma == M1.begin())  ;
    Gamma = M1.upper_bound ( 3000);     BOOST_CHECK  ( Gamma == M1.end() ) ;


    std::pair < c_forest::sorted_tree<int>::const_iterator, c_forest::sorted_tree<int>::const_iterator > PI ;
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ( M1.count (1000 + i *2 ) == 3 );
        BOOST_CHECK  ((PI.second.pos() - PI.first.pos() ) == 3 and PI.first.pos() == i*3) ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK  ((PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i*3) ;
    };

};

void  SinRepeticion2 ( void)
{   //---------------------- Variables----------------------------
    c_forest::sorted_tree<int> M1;
    int i ;
    c_forest::sorted_tree<int>::const_iterator alfa,N1 , N2 ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert_value_norep( 1000+ i *2 );
        BOOST_CHECK (M1.check() );
    };

    for ( i = 0 , N1 = M1.begin(); N1 != M1.end() ; ++N1, i++)
    {   BOOST_CHECK ( *N1 == (1000 + i*2) )   ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   N1 = M1.lower_bound( 1000 + i *2 );
        N2 = M1.upper_bound( 1000 + i *2 );
        BOOST_CHECK ( N1 != N2 and N1.pos() == i)   ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   N1 = M1.lower_bound( 1001 + i *2 );
        N2 = M1.upper_bound( 1001 + i *2 );
        BOOST_CHECK  ( N1 == N2 )  ;
    };

    for ( i = 0 ; i < 1000  ; i++ )
    {   N1 = M1.upper_bound( 999 + i*2 );
        N2 = M1.upper_bound( 1000 + i *2 ) ;
        BOOST_CHECK ( N1.pos() == i and N2.pos() == (i+1 ) )   ;
    };

    for ( i = 0 ; i < 1000  ; i++ )
    {   N1 = M1.lower_bound( 1001 + i*2 );
        N2 = M1.lower_bound( 1002 + i *2 ) ;
        BOOST_CHECK ( N1 == N2  )   ;
    };

};

void  ConRepeticion2 ( void)
{   //---------------------- Funciones -------------------------
    c_forest::sorted_tree<int> M1;
    c_forest::sorted_tree<int>::const_iterator alfa,N1 , N2 ;
    int i ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert_value_rep( 1000+ i *2 );
        BOOST_CHECK  (M1.check())  ;
        M1.insert_value_rep( 1000+ i *2 );
        BOOST_CHECK  (M1.check())  ;
        M1.insert_value_rep( 1000+ i *2 );
        BOOST_CHECK  (M1.check())  ;
    };

    for ( i = 0 , N1 = M1.begin(); N1 != M1.end() ; N1+=3, i++)
    {   BOOST_CHECK  ( *N1 == (1000 + i*2) and
                       *(N1+1) == (1000 + i*2) and
                       *(N1+2) == (1000 + i*2)     )  ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   N1 = M1.find_rep( 1000 + i *2 );
        BOOST_CHECK ( M1.count ( 1000 + i *2 ) == 3 and N1.pos() == i*3)   ;
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   N1 = M1.lower_bound( 1001 + i *2 );
        N2 = M1.upper_bound( 1001 + i *2 );
        BOOST_CHECK   (N1 == N2 )  ;
    };

    for ( i = 0 ; i < 1000  ; i++ )
    {   N1 = M1.upper_bound( 999 + i*2 );
        N2 = M1.upper_bound(1000 + i *2 ) ;
        BOOST_CHECK ( N1.pos() == i*3 and N2.pos() == (i*3+3 ) )   ;
    };
};
void conditional ()
{   //---------------------------- begin -------------------------
    c_forest::sorted_tree<int >  V1, V2 ;
    auto M1 = [] ( const int & k)->bool{ return ((k&1) == 0 );};

    // ---------- insert_norep_if ----------------------
    for ( int i = 0 ; i < 100 ; ++i)
        V1.insert_value_norep ( i);

    BOOST_CHECK ( V1.size() == 100);

    V2.insert_norep_if ( V1.begin(), V1.end() , M1);
    BOOST_CHECK ( V2.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V2.pos(i)  == (i *2));

    // ---------- insert_rep_if ----------------------
    V1.clear();
    V2.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
    {   V1.insert_value_rep ( i);
        V1.insert_value_rep ( i);
    } ;

    BOOST_CHECK ( V1.size() == 200);

    V2.insert_rep_if ( V1.begin(), V1.end() , M1);
    //std::cout<<V2<<std::endl;
    BOOST_CHECK ( V2.size() == 100);
    for ( int i = 0 ; i < 100 ; i+=2)
    {   BOOST_CHECK ( V2.pos(i)  == i );
        BOOST_CHECK ( V2.pos(i+1)  == i );
    }  ;

    //-----------  erase_if ----------------------------
    V1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        V1.insert_value_norep ( i);

    BOOST_CHECK ( V1.size() == 100);
    V1.erase_if (V1.begin(), V1.end(), M1);

    BOOST_CHECK ( V1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V1.pos(i) == (i *2)+1);

    //------------------ erase_pos_if -------------------
    V1.clear() ;
    for ( int i = 0 ; i < 100 ; ++i)
        V1.insert_value_norep ( i);
    BOOST_CHECK ( V1.size() == 100);
    V1.erase_pos_if ( 0, 100 , M1);
    BOOST_CHECK ( V1.size() == 50);
    for ( int i = 0 ; i < 50 ; ++i)
        BOOST_CHECK ( V1.pos(i)  == (i *2)+1);
     V1.erase_pos ( 0, 50 );
    BOOST_CHECK ( V1.size() == 0);

};

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba0 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticion ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticion ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &conditional ) );
    return 0;
}
