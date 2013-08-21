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
    typedef c_forest::tree<int>::iterator t_iterator ;
    typedef c_forest::tree<int>::const_iterator t_const_iterator ;

    c_forest::tree<int> T ;
    for ( int i =0 ; i < 9 ; ++i)
        T.push_back( i);

    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);

    //------------------------------------------------------------
    // iterators functions
    //------------------------------------------------------------
    t_iterator  C1;
    t_iterator C2 ( T.begin());
    t_iterator C3(C2), C4;
    C1 = C2 ;
    BOOST_CHECK ( C1 == C2 and C2 == C3 and *C1 == 0);

    C1 = t_iterator::begin( &T);
    BOOST_CHECK ( *C1 == 0);
    BOOST_CHECK ( *(C1++) == 0);
    BOOST_CHECK ( *C1 == 1);
    BOOST_CHECK ( *(++C1) == 2);

    BOOST_CHECK ( * (C1--) == 2 );
    BOOST_CHECK ( *C1 == 1);
    BOOST_CHECK ( * (--C1) == 0 );

    C1 = t_iterator::begin( &T) + 3;

    BOOST_CHECK ( *C1 == 3 )   ;
    C1+= -1 ;
    BOOST_CHECK ( *C1 == 2 )   ;

    C1 -= -1 ;
    BOOST_CHECK ( *C1 == 3 )   ;
    C1-= 2 ;
    BOOST_CHECK ( *C1 == 1);

    C1 = t_iterator::begin( &T ) + 1;
    C1 = 1 + C1  ;
    BOOST_CHECK ( *C1 == 2 )   ;
    C1 = C1 - 1 ;
    BOOST_CHECK ( *C1 == 1 )   ;

    C2 = t_iterator::begin (&T) + 5 ;
    BOOST_CHECK ( (C2 - C1 ) == 4);

    C1 = t_iterator::rend ( &T);
    C2 = t_iterator::begin ( &T);
    C3 = t_iterator::end ( &T);
    C4 = t_iterator::rbegin ( &T);

    BOOST_CHECK ( (C3-C2) == 9 ) ;
    BOOST_CHECK ( (C3-C1) == 10 ) ;
    BOOST_CHECK ( (C4-C2) == 8 ) ;


    //------------------------------------------------------------
    // const_iterators functions
    //------------------------------------------------------------
    t_const_iterator  CC1, CC2 ( T.cit_begin()), CC3(CC2), CC4( C1);
    CC1 = CC2 ;
    BOOST_CHECK ( CC1 == CC2 and CC2 == CC3 and (*CC1) == 0);

    CC1 = t_const_iterator::begin( &T);
    BOOST_CHECK ( *CC1 == 0);
    BOOST_CHECK ( *(CC1++) == 0);
    BOOST_CHECK ( *CC1 == 1);
    BOOST_CHECK ( *(++CC1) == 2);

    BOOST_CHECK ( * (CC1--) == 2 );
    BOOST_CHECK ( *CC1 == 1);
    BOOST_CHECK ( * (--CC1) == 0 );

    CC1 = t_const_iterator::begin( &T);
    CC1 += 3 ;
    BOOST_CHECK ( *CC1 == 3 )   ;
    CC1+= -1 ;
    BOOST_CHECK ( *CC1 == 2 )   ;

    CC1 -= -1 ;
    BOOST_CHECK ( *CC1 == 3 )   ;
    CC1-= 2 ;
    BOOST_CHECK ( *CC1 == 1);

    CC1 = t_const_iterator::begin(&T) +1 ;
    CC1 = 1 + CC1  ;
    BOOST_CHECK ( *CC1 == 2 )   ;
    CC1 = CC1 - 1 ;
    BOOST_CHECK ( *CC1 == 1 )   ;

    CC2 = t_const_iterator::begin ( &T) + 5 ;
    BOOST_CHECK ( (CC2 - CC1 ) == 4);

    CC1 = t_const_iterator::rend ( &T);
    CC2 = t_const_iterator::begin ( &T);
    CC3 = t_const_iterator::end ( &T);
    CC4 = t_const_iterator::rbegin ( &T);

    BOOST_CHECK ( (CC3-CC2) == 9 ) ;
    BOOST_CHECK ( (CC3-CC1) == 10 ) ;
    BOOST_CHECK ( (CC4-CC2) == 8 ) ;


};
void iterator1 ( void )
{   //------------------------ begin ----------------------------------
    typedef c_forest::tree<int>::iterator t_iterator ;
    typedef c_forest::tree<int>::const_iterator t_const_iterator ;

    c_forest::tree<int> T ;
    int i ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);

    //===============================================================
    {   t_iterator  CIni=  T.begin();
        t_iterator  C1(CIni);

        t_const_iterator CEnd, CREnd ;
        CEnd = t_const_iterator::end( &T) ;
        CREnd = t_const_iterator::rend(&T);
        C1 = C1 -1 ;

        for ( i =0, C1=CIni ;C1 != CEnd; i++, C1++)
        {   BOOST_CHECK ( C1.pos() == (*C1));
            BOOST_CHECK ( i == *C1);
        };

        for ( i =0,C1=CIni;C1 != CEnd;i+=2, C1+= 2)
        {   BOOST_CHECK ( i == *C1);
        };

        for ( i = 8 , C1=8 +CIni ;C1 != CREnd;i--, C1--)
        {   BOOST_CHECK ( i == *C1);
        };

        for ( i = 8 , C1=CIni+8;C1 != CREnd;i -= 2, C1-= 2)
        {   BOOST_CHECK ( i == *C1);
        };

        t_iterator  Alfa (T.begin()), Beta (Alfa );

        Alfa = t_iterator::begin( &T) + 12  ;
        BOOST_CHECK ( std::distance (Beta ,Alfa) == 9 );

        BOOST_CHECK ( Alfa == t_iterator::end(&T));
        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK ( Alfa == t_iterator::end(&T));
    };

    //===============================================================
    {   t_const_iterator C2,C2Ini, C2End, C2REnd;
        C2Ini = t_const_iterator::begin ( &T);
        C2End = t_const_iterator::end( &T) ;
        C2REnd = t_const_iterator::rend( &T);

        for (i = 0 ,C2= C2Ini ; C2 != C2End; i++,C2++)
        {   BOOST_CHECK ( i == *C2 and i == C2.pos() );
        };

        for (i =0, C2= C2Ini ;C2 != C2End; i+=2,C2+= 2)
        {   BOOST_CHECK ( i == *C2 and i == C2.pos() );
        };

        for (i =8 ,C2=C2Ini +8 ;C2 != C2REnd;i--, C2--)
        {   BOOST_CHECK ( i == *C2 and i == C2.pos() );
        };

        for (i = 8 ,C2= C2Ini+8;C2 != C2REnd;i-=2, C2-= 2)
        {   BOOST_CHECK ( i == *C2 and i == C2.pos() );
        };

        //============================================================
        t_const_iterator  Alfa ( T.cbegin()), Beta (Alfa );

        Alfa = t_const_iterator::begin(&T)+ 12 ;
        BOOST_CHECK (std::distance (Beta ,Alfa)  == 9);

        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK (Alfa == t_const_iterator::end(&T)) ;
    };

} ;

void iterator2 ( void )
{   //------------------------ Inicio ----------------------------------
    int32_t i ;
    typedef c_forest::tree<int>::iterator t_iterator ;
    typedef c_forest::tree<int>::const_iterator t_const_iterator ;

    c_forest::tree<int> T ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);
    //===============================================================
    {   t_iterator  C1 = t_iterator::begin ( &T);
        t_iterator  CBegin(C1);
        BOOST_CHECK (CBegin.pos() == 0 and C1.pos() == 0 );
        t_iterator CRBegin ( t_iterator::rbegin ( &T));
        BOOST_CHECK (CRBegin.pos() == 8);
        t_iterator CEnd    ( t_iterator::end (&T));
        BOOST_CHECK(CEnd.pos() == 9);
        t_iterator CREnd   ( t_iterator::rend  (&T));
        BOOST_CHECK(CREnd.pos() == -1);
        C1 = CEnd -2 ;

        for ( i = 0 ,C1=CBegin ;C1 < CEnd;i++, C1++)
        {   BOOST_CHECK (C1.pos() == *C1 and i == *C1) ;
        };

        for (i = 0,C1=CREnd ;C1 != (CBegin+8);++i )
        {   BOOST_CHECK( *(++C1) == i  ) ;
        };

        for (i = 0,C1=CBegin;C1 != CEnd;i+=2, C1+= 2)
        {   BOOST_CHECK( *C1 == i) ;
        };

        for (i = 8,C1=CBegin+8 ;C1 > CREnd;i--, C1--)
        {   BOOST_CHECK( *C1 == i) ;
        };

        for ( i = 8 , C1=CEnd ;( C1-( CEnd - 9 )) != 0 ;--i )
        {   BOOST_CHECK( *(--C1) == i) ;
        };

        for ( i = 8 ,C1=CBegin+8;C1 != CREnd; i-=2,C1-= 2)
        {   BOOST_CHECK( *C1 == i) ;
        };

        //============================================================
        t_iterator  Alfa ( T.begin()), Beta (Alfa );

        Alfa = t_iterator::begin( &T) + 12 ;
        BOOST_CHECK ( std::distance (Beta ,Alfa) == 9);
        BOOST_CHECK (Alfa == t_iterator::end(&T)) ;

        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK (Alfa == t_iterator::end(&T)) ;

        c_forest::tree<int> T2  ;
        t_iterator Delta (NULL, &T2);
        BOOST_CHECK(Delta.pos() == -1);

        t_iterator DBegin ( t_iterator::begin( &T2));
        BOOST_CHECK( DBegin.pos() == 0);

        t_iterator DEnd   ( t_iterator::end(&T2));
        BOOST_CHECK ( DEnd.pos() == 0) ;

        t_iterator DRBegin( t_iterator::rbegin(&T2));
        BOOST_CHECK ( DRBegin.pos() == -1);

        t_iterator DREnd  ( t_iterator::rend(&T2));
        BOOST_CHECK( DREnd.pos() == -1);
    };

    //===============================================================
    {   t_const_iterator  C1 =  T.begin();
        t_const_iterator  CBegin(C1);

        t_const_iterator CRBegin (t_const_iterator::rbegin(&T)) ;
        t_const_iterator CEnd    (t_const_iterator::end(&T)) ;
        t_const_iterator CREnd   (t_const_iterator::rend(&T));

        for (i =0 ,C1=CBegin ;C1 < CEnd;i++, C1++)
        {   BOOST_CHECK ( C1.pos() == *C1 and i == *C1) ;
        };

        for (i =0,C1=CREnd ;C1 != (8+CBegin);++i )
        {   BOOST_CHECK(* (++C1) == i) ;
        };

        for ( i = 0 ,C1=CBegin;C1 != CEnd;i += 2, C1+= 2)
        {   BOOST_CHECK ( *C1 == i) ;
        };

        for ( i =8 ,C1=CBegin+8 ;C1 > CREnd;i--, C1--)
        {   BOOST_CHECK( *C1 == i) ;
        };

        for ( i = 8 ,C1=CEnd ;( C1 -(CEnd -9 )) != 0 ;--i )
        {   BOOST_CHECK(* (--C1) == i);
        };

        for ( i = 8 ,C1=CBegin+8;C1 != CREnd;i -=2, C1-= 2)
        {   BOOST_CHECK( *C1 == i);
        };

        //============================================================
        t_const_iterator  Alfa ( T.cbegin()), Beta (Alfa );

        Alfa = t_const_iterator::begin( &T) + 12 ;
        BOOST_CHECK (std::distance (Beta ,Alfa) == 9) ;
        BOOST_CHECK(Alfa == t_const_iterator::end(&T)) ;

        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK(Alfa == t_const_iterator::end(&T)) ;

        c_forest::tree<int> T2 ;
        t_const_iterator Delta (NULL, &T2);
        t_const_iterator DBegin ( t_const_iterator::begin(&T2));
        t_const_iterator DEnd   ( t_const_iterator::end(&T2));
        t_const_iterator DRBegin( t_const_iterator::rbegin(&T2));
        t_const_iterator DREnd  ( t_const_iterator::rend(&T2));
    };

} ;
void logic_iterator ( void )
{   //------------------------ Inicio ----------------------------------
    int32_t i ;
    typedef c_forest::tree<int>::iterator t_iterator ;
    typedef c_forest::tree<int>::const_iterator t_const_iterator ;

    c_forest::tree<int> T ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);
    //===============================================================
    t_iterator  C1 = T.begin() , C2 = T.end() ;
    BOOST_CHECK ( C2 > C1);
    BOOST_CHECK ( C1 < C2);
    BOOST_CHECK ( C2 != C1);
    BOOST_CHECK ( not(C2 == C1) );
    BOOST_CHECK ( C2 >= C1);
    BOOST_CHECK ( C1 <= C2);
    BOOST_CHECK ( C1 <= C1);
    BOOST_CHECK ( C1 >= C1);

    t_const_iterator  CC1 = T.begin() , CC2 = T.end() ;
    BOOST_CHECK ( CC2 > CC1);
    BOOST_CHECK ( CC1 < CC2);
    BOOST_CHECK ( CC2 != CC1);
    BOOST_CHECK ( not(CC2 == CC1) );
    BOOST_CHECK ( CC2 >= CC1);
    BOOST_CHECK ( CC1 <= CC2);
    BOOST_CHECK ( CC1 <= CC1);
    BOOST_CHECK ( CC1 >= CC1);

    BOOST_CHECK ( C2 > CC1);
    BOOST_CHECK ( CC1 < C2);
    BOOST_CHECK ( C2 != CC1);
    BOOST_CHECK ( not(C2 == CC1) );
    BOOST_CHECK ( C2 >= CC1);
    BOOST_CHECK ( CC1 <= C2);
    BOOST_CHECK ( C1 <= CC1);
    BOOST_CHECK ( C1 >= CC1);


};
void reverse_iterator0 ( void )
{   //------------------------ begin ----------------------------------
    int32_t i ;
    typedef c_forest::tree<int>::reverse_iterator t_riterator ;
    typedef c_forest::tree<int>::const_reverse_iterator t_const_riterator ;

    c_forest::tree<int> T ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);

    //------------------------------------------------------------
    // iterators functions
    //------------------------------------------------------------
    t_riterator  C1, C2 ( T.rit_begin()), C3(C2), C4;
    C1 = C2 ;
    BOOST_CHECK ( C1 == C2 and C2 == C3 and *C1 == 0);

    C1 = t_riterator::rbegin(&T);
    BOOST_CHECK ( *C1 == 8);
    BOOST_CHECK ( *(C1++) == 8);
    BOOST_CHECK ( *C1 == 7);
    BOOST_CHECK ( *(++C1) == 6);

    BOOST_CHECK ( * (C1--) == 6 );
    BOOST_CHECK ( *C1 == 7);
    BOOST_CHECK ( * (--C1) == 8 );

    C1 = t_riterator::rbegin( &T) + 3;

    BOOST_CHECK ( *C1 == 5 )   ;
    C1+= -1 ;
    BOOST_CHECK ( *C1 == 6 )   ;

    C1 -= -1 ;
    BOOST_CHECK ( *C1 == 5 )   ;
    C1-= 2 ;
    BOOST_CHECK ( *C1 == 7);

    C1 = t_riterator::rbegin( &T ) + 1;
    C1 = 1 + C1  ;
    BOOST_CHECK ( *C1 == 6 )   ;
    C1 = C1 - 1 ;
    BOOST_CHECK ( *C1 == 7 )   ;

    C2 = t_riterator::rbegin (&T) + 5 ;
    BOOST_CHECK ( (C2 - C1 ) == 4);

    C1 = t_riterator::end ( &T);
    C2 = t_riterator::rbegin ( &T);
    C3 = t_riterator::rend ( &T);
    C4 = t_riterator::begin ( &T);

    BOOST_CHECK ( (C3-C2) == 9 ) ;
    BOOST_CHECK ( (C3-C1) == 10 ) ;
    BOOST_CHECK ( (C4-C2) == 8 ) ;


    //------------------------------------------------------------
    // const_iterators functions
    //------------------------------------------------------------
    t_const_riterator  CC1, CC2 ( T.crit_begin()), CC3(CC2), CC4( C1);
    CC1 = CC2 ;
    BOOST_CHECK ( CC1 == CC2 and CC2 == CC3 and *CC1 == 0);

    CC1 = t_const_riterator::rbegin( &T);
    BOOST_CHECK ( *CC1 == 8);
    BOOST_CHECK ( *(CC1++) == 8);
    BOOST_CHECK ( *CC1 == 7);
    BOOST_CHECK ( *(++CC1) == 6);

    BOOST_CHECK ( * (CC1--) == 6 );
    BOOST_CHECK ( *CC1 == 7);
    BOOST_CHECK ( * (--CC1) == 8 );

    CC1 = t_const_riterator::rbegin( &T);
    CC1 += 3 ;
    BOOST_CHECK ( *CC1 == 5 )   ;
    CC1+= -1 ;
    BOOST_CHECK ( *CC1 == 6 )   ;

    CC1 -= -1 ;
    BOOST_CHECK ( *CC1 == 5 )   ;
    CC1-= 2 ;
    BOOST_CHECK ( *CC1 == 7);

    CC1 = t_const_riterator::rbegin( &T) +1 ;
    CC1 = 1 + CC1  ;
    BOOST_CHECK ( *CC1 == 6 )   ;
    CC1 = CC1 - 1 ;
    BOOST_CHECK ( *CC1 == 7 )   ;

    CC2 = t_const_riterator::rbegin ( &T) + 5 ;
    BOOST_CHECK ( (CC2 - CC1 ) == 4);

    CC1 = t_const_riterator::end ( &T);
    CC2 = t_const_riterator::rbegin ( &T);
    CC3 = t_const_riterator::rend ( &T);
    CC4 = t_const_riterator::begin ( &T);

    BOOST_CHECK ( (CC3-CC2) == 9 ) ;
    BOOST_CHECK ( (CC3-CC1) == 10 ) ;
    BOOST_CHECK ( (CC4-CC2) == 8 ) ;

};



void reverse_iterator1 ( void )
{   //------------------------ begin ----------------------------------
    int32_t i ;
    typedef c_forest::tree<int>::reverse_iterator t_riterator ;
    typedef c_forest::tree<int>::const_reverse_iterator t_const_riterator ;

    c_forest::tree<int> T ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);

    //===============================================================
    {   t_riterator  CIni= T.rit_begin();
        t_riterator  C1(CIni);

        t_const_riterator CEnd, CREnd ;
        CEnd = t_const_riterator::end( &T ) ;
        CREnd = t_const_riterator::rend(&T);
        C1 = C1 -1 ;

        for ( i =0, C1=t_riterator::rbegin(&T) ;C1 < CREnd; i++, C1++)
        {   BOOST_CHECK ( ( 8 - C1.pos() )== (*C1));
            BOOST_CHECK ( (8-i) == *C1);
        };

        for ( i =0,C1=t_riterator::rbegin(&T);C1 < CREnd;i+=2, C1+= 2)
        {   BOOST_CHECK ( (8-i) == *C1);
        };

        for ( i = 8 , C1=8 +CIni ;C1 < CREnd;i--, C1--)
        {   BOOST_CHECK ( i == *C1);
        };

        for ( i = 8 , C1=CIni+8;C1 < CREnd;i -= 2, C1-= 2)
        {   BOOST_CHECK ( i == *C1);
        };

        t_riterator  Alfa (T.rit_begin() -8), Beta (Alfa );

        Alfa = t_riterator::rbegin( &T) + 12  ;
        BOOST_CHECK ( std::distance (Beta ,Alfa) == 9 );

        BOOST_CHECK ( Alfa == t_riterator::rend(&T));
        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK ( Alfa == t_riterator::rend(&T));
    };

    //===============================================================
    {   t_const_riterator  C2(NULL, &T),C2Ini, C2End, C2REnd;
        C2Ini = t_const_riterator::rbegin(&T);
        C2End = t_const_riterator::end( &T) ;
        C2REnd = t_const_riterator::rend( &T);

        for (i = 0 ,C2= C2Ini ; C2 != C2REnd; i++,C2++)
        {   BOOST_CHECK ( ( 8 - C2.pos() )== (*C2));
            BOOST_CHECK ( (8-i) == *C2);
        };

        for (i =0, C2= C2Ini ;C2 != C2REnd; i+=2,C2+= 2)
        {   BOOST_CHECK ( (8-i) == *C2 and i == C2.pos() );
        };

        for (i =0 ,C2=t_const_riterator::begin( &T); C2 != C2End;i++, C2--)
        {   BOOST_CHECK ( i == *C2 and (8- i) == C2.pos() );
        };

        for (i = 0 ,C2= C2Ini+8;C2 != C2End;i+=2, C2-= 2)
        {   BOOST_CHECK ( i == *C2 and ( 8 - i) == C2.pos() );
        };

        //============================================================
        t_const_riterator  Alfa (T.crit_begin() - 8), Beta (Alfa );

        Alfa = t_const_riterator::rbegin(&T)+ 12 ;
        BOOST_CHECK (std::distance (Beta ,Alfa)  == 9);

        Alfa -= 2 ;
        Alfa = Beta ;
        std::advance(Alfa , 9 );
        BOOST_CHECK (Alfa == t_const_riterator::rend(&T)) ;
    };
} ;
void logic_reverse_iterator ( void )
{   //------------------------ Inicio ----------------------------------
    int32_t i ;
    typedef c_forest::tree<int>::reverse_iterator t_iterator ;
    typedef c_forest::tree<int>::const_reverse_iterator t_const_iterator ;

    c_forest::tree<int> T ;
    for ( i = 0 ; i < 9 ; ++i ) T.push_back ( i);
    BOOST_CHECK ( T.check());

    BOOST_CHECK ( T.size() == 9);
    //===============================================================
    t_iterator  C1 = T.rbegin() , C2 = T.rend() ;
    BOOST_CHECK ( C2 > C1);
    BOOST_CHECK ( C1 < C2);
    BOOST_CHECK ( C2 != C1);
    BOOST_CHECK ( not(C2 == C1) );
    BOOST_CHECK ( C2 >= C1);
    BOOST_CHECK ( C1 <= C2);
    BOOST_CHECK ( C1 <= C1);
    BOOST_CHECK ( C1 >= C1);

    t_const_iterator  CC1 = T.rbegin() , CC2 = T.rend() ;
    BOOST_CHECK ( CC2 > CC1);
    BOOST_CHECK ( CC1 < CC2);
    BOOST_CHECK ( CC2 != CC1);
    BOOST_CHECK ( not(CC2 == CC1) );
    BOOST_CHECK ( CC2 >= CC1);
    BOOST_CHECK ( CC1 <= CC2);
    BOOST_CHECK ( CC1 <= CC1);
    BOOST_CHECK ( CC1 >= CC1);

    BOOST_CHECK ( C2 > CC1);
    BOOST_CHECK ( CC1 < C2);
    BOOST_CHECK ( C2 != CC1);
    BOOST_CHECK ( not(C2 == CC1) );
    BOOST_CHECK ( C2 >= CC1);
    BOOST_CHECK ( CC1 <= C2);
    BOOST_CHECK ( C1 <= CC1);
    BOOST_CHECK ( C1 >= CC1);


};

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &iterator0 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &iterator1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &iterator2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &logic_iterator ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &reverse_iterator0 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &reverse_iterator1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &logic_reverse_iterator ) );
    return 0;
}
