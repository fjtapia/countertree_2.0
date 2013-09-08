//----------------------------------------------------------------------------
/// @file test_iterator.cpp
/// @brief Test program of the classes iterator and const_iterator
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
#include <boost/countertree/forest/tree.hpp>


using std::cout;
using std::endl;
using namespace boost::unit_test;

namespace c_forest = countertree::forest ;

void iterator0 ( void )
{   //------------------------ begin ----------------------------------
    typedef c_forest::tree<int>::base_iterator biterator ;
    typedef c_forest::tree<int>::const_base_iterator const_biterator ;
    c_forest::tree<int> T ;

    for ( int i =0 ; i < 9 ; i++)
        T.push_back ( i );


    //------------------------------------------------------------
    // base_iterators functions
    //------------------------------------------------------------
    biterator  C1, C2 ( biterator::begin(&T) ), C3(C2), C4( C2.P,C2.BT);
    C1 = C2 ;
    BOOST_CHECK ( C1 == C2 and C2 == C3 and *C1 == 0);
    BOOST_CHECK ( C2.is_valid());
    BOOST_CHECK ( C2.is_mine(&T));
    BOOST_CHECK ( C2.size() == T.size());

    C1 = biterator::begin(&T);
    BOOST_CHECK ( *C1 == 0);
    C1.next();
    BOOST_CHECK ( *C1 == 1);
    BOOST_CHECK ( *(C1.next()) == 2);
    C1.previous() ;
    BOOST_CHECK ( *C1 == 1);
    BOOST_CHECK ( * (C1.previous()) == 0 );

    C1 = biterator::begin(&T).shift( 3);

    BOOST_CHECK ( *C1 == 3 )   ;
    C1.shift( -1) ;
    BOOST_CHECK ( *C1 == 2 )   ;

    C1.shift(1 );
    BOOST_CHECK ( *C1 == 3 )   ;
    C1.shift( -2) ;
    BOOST_CHECK ( *C1 == 1);

    C1 = biterator::begin(&T).shift(1);
    C1.next() ;
    BOOST_CHECK ( *C1 == 2 )   ;
    C1.previous() ;
    BOOST_CHECK ( *C1 == 1 )   ;

    C2 = biterator::begin(&T).shift( 5) ;
    BOOST_CHECK ( (C2.pos() - C1.pos() ) == 4);

    C1 = biterator::rend(&T);
    C2 = biterator::begin(&T);
    C3 = biterator::end(&T);
    C4 = biterator::rbegin(&T) ;

    BOOST_CHECK ( (C3.pos()-C2.pos()) == 9 ) ;
    BOOST_CHECK ( (C3.pos()-C1.pos()) == 10 ) ;
    BOOST_CHECK ( (C4.pos()-C2.pos()) == 8 ) ;
    BOOST_CHECK ( (C2.reverse_pos()- C3.reverse_pos()) == 9 );

    //------------------------------------------------------------
    // const_base_iterators functions
    //------------------------------------------------------------
    const_biterator  CC1, CC2 ( const_biterator::begin(&T)), CC3(CC2), CC4(CC2.P,CC2.BT);
    CC1 = CC2 ;
    BOOST_CHECK ( CC1 == CC2 and CC2 == CC3 and (*CC1) == 0);
    BOOST_CHECK ( CC2.is_valid());
    BOOST_CHECK ( CC2.is_mine(&T));
    BOOST_CHECK ( CC2.size() == T.size());

    CC1 = const_biterator::begin(&T);
    BOOST_CHECK ( *CC1 == 0);
    CC1.next() ;
    BOOST_CHECK ( *CC1 == 1);
    BOOST_CHECK ( *(CC1.next()) == 2);


    CC1.previous() ;
    BOOST_CHECK ( *CC1 == 1);
    BOOST_CHECK ( * (CC1.previous()) == 0 );

    CC1 = const_biterator::begin(&T);
    CC1.shift ( 3 );
    BOOST_CHECK ( *CC1 == 3 )   ;
    CC1.previous() ;
    BOOST_CHECK ( *CC1 == 2 )   ;

    CC1.shift(1) ;
    BOOST_CHECK ( *CC1 == 3 )   ;
    CC1.shift( -2 );
    BOOST_CHECK ( *CC1 == 1);

    CC1 = const_biterator::begin(&T).shift (1) ;
    CC1.next()  ;
    BOOST_CHECK ( *CC1 == 2 )   ;
    CC1.previous() ;
    BOOST_CHECK ( *CC1 == 1 )   ;

    CC2 = const_biterator::begin(&T).shift(5);
    BOOST_CHECK ( (CC2.pos() - CC1.pos() ) == 4);

    CC1 = const_biterator::rend(&T) ;
    CC2 = const_biterator::begin(&T);
    CC3 = const_biterator::end(&T);
    CC4 = const_biterator::rbegin(&T);

    BOOST_CHECK ( (CC3.pos()-CC2.pos()) == 9 ) ;
    BOOST_CHECK ( (CC3.pos()-CC1.pos()) == 10 ) ;
    BOOST_CHECK ( (CC4.pos()-CC2.pos()) == 8 ) ;
    BOOST_CHECK ( (CC2.reverse_pos()-CC3.reverse_pos()) == 9 );

}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &iterator0 ) );

    return 0;
}
