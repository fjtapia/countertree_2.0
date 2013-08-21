//----------------------------------------------------------------------------
/// @file bjam_pool.cpp
/// @brief Test program of the classes pool32 and pool64
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#define __DEBUG_CNTREE  1
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/alloc/pool32.hpp>
#include <boost/countertree/alloc/pool64.hpp>
#include <iostream>
#include <memory>
#include <algorithm>
#define NELEM 2000000

using namespace boost::unit_test;
using namespace countertree::alloc ;

struct archiperre {} ;
void Test32_01 ( void)
{   //------------------------------ begin ----------------------------------
    uint64_t  ** K = new uint64_t *[NELEM];
    pool32 <8,true, std::allocator<uint8_t> > A ;
    BOOST_CHECK ( K != NULL );

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < uint64_t *> ( A.allocate());
            (*K[i]) = i ;
        };
        BOOST_CHECK ( A.size() == NELEM)  ;
        BOOST_CHECK (  A.check());

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if ( (K[i] == NULL ) or  (*K[i]) != i ) BOOST_CHECK ( false);
            if ( (i & 0xfffffU) == 0 and not A.check()) BOOST_CHECK ( false);
            (*K[i]) = 0 ;
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )  ;
    };

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < uint64_t *> ( A.allocate());
            (*K[i]) = i ;
        };

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if ( (K[i] == NULL ) or  (*K[i]) != i ) BOOST_CHECK ( false);
        };

        std::sort ( &K[0] , & K[NELEM]);
        for ( uint32_t i =0 ; i < NELEM-1 ; ++i)
        {   if ( K[i] == K[i+1]) BOOST_CHECK ( false);
        };

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   (*K[i]) = 0 ;
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )    ;
    };
    delete[] K ;

}
void Test64_01 ( void)
{   //------------------------------ begin ----------------------------------
    uint64_t  ** K = new uint64_t *[NELEM];
    pool64 <8,true, std::allocator<uint8_t> > A ;
    BOOST_CHECK ( K != NULL );

    for ( uint64_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < uint64_t *> ( A.allocate());
            (*K[i]) = i ;
        };
        BOOST_CHECK ( A.size() == NELEM)  ;
        BOOST_CHECK (  A.check());

        for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   if ( (K[i] == NULL ) or  (*K[i]) != i ) BOOST_CHECK ( false);
            if ( (i & 0xfffffU) == 0 and not A.check()) BOOST_CHECK ( false);
            (*K[i]) = 0 ;
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )  ;
    };

    for ( uint64_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < uint64_t *> ( A.allocate());
            (*K[i]) = i ;
        };

        for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   if ( (K[i] == NULL ) or  (*K[i]) != i ) BOOST_CHECK ( false);
        };

        std::sort ( &K[0] , & K[NELEM]);
        for ( uint64_t i =0 ; i < NELEM-1 ; ++i)
        {   if ( K[i] == K[i+1]) BOOST_CHECK ( false);
        };

        for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   (*K[i]) = 0 ;
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )    ;
    };
    delete[] K ;

}
void Test32_02 ( void)
{   //------------------------------ begin ----------------------------------
    archiperre  ** K = new archiperre *[NELEM];
    pool32 < 0,true, std::allocator<uint8_t> > A ;
    BOOST_CHECK ( K != NULL );

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < archiperre *> ( A.allocate());
        };
        BOOST_CHECK ( A.size() == NELEM)  ;
        BOOST_CHECK (  A.check());

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if (K[i] == NULL )  BOOST_CHECK ( false);
            if ( (i & 0xfffffU) == 0 and not A.check()) BOOST_CHECK ( false);
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )  ;
    };

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < archiperre *> ( A.allocate());
        };

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if (K[i] == NULL )  BOOST_CHECK ( false);
        };


        for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )    ;
    };
    delete[] K ;

}
void Test64_02 ( void)
{   //------------------------------ begin ----------------------------------
    archiperre  ** K = new archiperre *[NELEM];
    pool64 < 0,true, std::allocator<uint8_t> > A ;
    BOOST_CHECK ( K != NULL );

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < archiperre *> ( A.allocate());
        };
        BOOST_CHECK ( A.size() == NELEM)  ;
        BOOST_CHECK (  A.check());

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if (K[i] == NULL )  BOOST_CHECK ( false);
            if ( (i & 0xfffffU) == 0 and not A.check()) BOOST_CHECK ( false);
            A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )  ;
    };

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   K[i] = NULL ;
            K[i] = static_cast < archiperre *> ( A.allocate());
        };

        for ( uint32_t i =0  ; i < NELEM ; ++i)
        {   if (K[i] == NULL )  BOOST_CHECK ( false);
        };


        for ( uint64_t i =0  ; i < NELEM ; ++i)
        {   A.deallocate(K[i]);
            K[i] = NULL ;
        };
        BOOST_CHECK ( A.size() == 0 )    ;
    };
    delete[] K ;

}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test32_01 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test64_01 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test32_02 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test64_02 ) );
    return 0;
}
