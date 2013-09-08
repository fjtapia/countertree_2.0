//----------------------------------------------------------------------------
/// @file test_heap.cpp
/// @brief Test program of the classes heap32 and heap64
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
#include <boost/countertree/alloc/heap32.hpp>
#include <boost/countertree/alloc/heap64.hpp>
#include <iostream>
using namespace boost::unit_test;


namespace cna = countertree::alloc ;
typedef std::allocator<uint8_t> AllocByte ;
AllocByte A ;

template <typename H >
H * create ( void)
{   void * PAux = A.allocate ( sizeof ( H));
    if (PAux == NULL) throw std::bad_alloc();
    new (PAux)  H ;
    return (H*) PAux ;
};
template <typename H >
void destroy ( H * PtrH)
{   uint32_t SizeElem =  sizeof( H );
    A.deallocate ( (uint8_t*)PtrH, SizeElem);
};

//------------------- prototypes ----------------------------
test_suite* init_unit_test_suite( int argc, char* argv[] );
void Test64 ( void);
void Test32 ( void);

template <typename H>
void fill_empty ( void);

template <typename H, uint32_t N>
void fill_test ( void);

void Test32 ( void)
{   //-------------------- begin-------------------------------
    typedef cna::heap32 <0,  AllocByte>   A0 ;
    typedef cna::heap32 <1,  AllocByte>   A1 ;
    typedef cna::heap32 <2,  AllocByte>   A2 ;
    typedef cna::heap32 <3,  AllocByte>   A3 ;
    typedef cna::heap32 <4,  AllocByte>   A4 ;
    typedef cna::heap32 <5,  AllocByte>   A5 ;

    typedef cna::heap32 <6,  AllocByte>   A6 ;
    typedef cna::heap32 <7,  AllocByte>   A7 ;
    typedef cna::heap32 <8,  AllocByte>   A8 ;
    typedef cna::heap32 <9,  AllocByte>   A9 ;
    typedef cna::heap32 <10, AllocByte>  A10 ;

    typedef cna::heap32 <11, AllocByte>   A11 ;
    typedef cna::heap32 <12, AllocByte>   A12 ;
    typedef cna::heap32 <13, AllocByte>   A13 ;
    typedef cna::heap32 <14, AllocByte>   A14 ;
    typedef cna::heap32 <15, AllocByte>   A15 ;

    typedef cna::heap32 <16, AllocByte>   A16 ;
    typedef cna::heap32 <17, AllocByte>   A17 ;
    typedef cna::heap32 <18, AllocByte>   A18 ;
    typedef cna::heap32 <19, AllocByte>   A19 ;
    typedef cna::heap32 <20, AllocByte>   A20 ;

    typedef cna::heap32 <21, AllocByte>   A21 ;
    typedef cna::heap32 <22, AllocByte>   A22 ;
    typedef cna::heap32 <23, AllocByte>   A23 ;
    typedef cna::heap32 <24, AllocByte>   A24 ;

    typedef cna::heap32 <25, AllocByte>   A25 ;
    typedef cna::heap32 <26, AllocByte>   A26 ;
    typedef cna::heap32 <27, AllocByte>   A27 ;
    typedef cna::heap32 <28, AllocByte>   A28 ;
    typedef cna::heap32 <29, AllocByte>   A29 ;
    typedef cna::heap32 <30, AllocByte>   A30 ;

    fill_empty<A0>() ;
    fill_empty<A1>() ;
    fill_empty<A2>() ;
    fill_empty<A3>() ;
    fill_empty<A4>() ;
    fill_empty<A5>() ;

    fill_empty<A6>() ;
    fill_empty<A7>() ;
    fill_empty<A8>() ;
    fill_empty<A9>() ;
    fill_empty<A10>() ;

    fill_empty<A11>() ;
    fill_empty<A12>() ;
    fill_empty<A13>() ;
    fill_empty<A14>() ;
    fill_empty<A15>() ;

    fill_empty<A16>() ;
    fill_empty<A17>() ;
    fill_empty<A18>() ;
    fill_empty<A19>() ;
    fill_empty<A20>() ;

    fill_empty<A21>() ;
    fill_empty<A22>() ;
    fill_empty<A23>() ;
    fill_empty<A24>() ;

    fill_empty<A25>() ;
    fill_empty<A26>() ;
    fill_empty<A27>() ;
    fill_empty<A28>() ;
    fill_empty<A29>() ;
    fill_empty<A30>() ;

    fill_test<A0,1>() ;
    fill_test<A1,1>() ;
    fill_test<A2,1>() ;
    fill_test<A3,1>() ;
    fill_test<A4,1>() ;
    fill_test<A5,1>() ;

    fill_test<A6,1>() ;
    fill_test<A7,1>() ;
    fill_test<A8,1>() ;
    fill_test<A9,1>() ;
    fill_test<A10,1>() ;

    fill_test<A11,1>() ;
    fill_test<A12,2>() ;
    fill_test<A13,3>() ;
    fill_test<A14,4>() ;
    fill_test<A15,5>() ;

    fill_test<A16,6>() ;
    fill_test<A17,7>() ;
    fill_test<A18,8>() ;
    fill_test<A19,9>() ;
    fill_test<A20,10>() ;

    fill_test<A21,11>() ;
    fill_test<A22,12>() ;
    fill_test<A23,13>() ;
    fill_test<A24,14>() ;
/*
    fill_test<A25,20>() ;
    fill_test<A26,20>() ;
    fill_test<A27,21>() ;
    fill_test<A28,22>() ;
    fill_test<A29,23>() ;
    fill_test<A30,24>() ;
*/
};
void Test64 ( void)
{   //-------------------- begin-------------------------------
    typedef cna::heap64 <0,  AllocByte>   A0 ;
    typedef cna::heap64 <1,  AllocByte>   A1 ;
    typedef cna::heap64 <2,  AllocByte>   A2 ;
    typedef cna::heap64 <3,  AllocByte>   A3 ;
    typedef cna::heap64 <4,  AllocByte>   A4 ;
    typedef cna::heap64 <5,  AllocByte>   A5 ;

    typedef cna::heap64 <6,  AllocByte>   A6 ;
    typedef cna::heap64 <7,  AllocByte>   A7 ;
    typedef cna::heap64 <8,  AllocByte>   A8 ;
    typedef cna::heap64 <9,  AllocByte>   A9 ;
    typedef cna::heap64 <10, AllocByte>  A10 ;

    typedef cna::heap64 <11, AllocByte>   A11 ;
    typedef cna::heap64 <12, AllocByte>   A12 ;
    typedef cna::heap64 <13, AllocByte>   A13 ;
    typedef cna::heap64 <14, AllocByte>   A14 ;
    typedef cna::heap64 <15, AllocByte>   A15 ;

    typedef cna::heap64 <16, AllocByte>   A16 ;
    typedef cna::heap64 <17, AllocByte>   A17 ;
    typedef cna::heap64 <18, AllocByte>   A18 ;
    typedef cna::heap64 <19, AllocByte>   A19 ;
    typedef cna::heap64 <20, AllocByte>   A20 ;

    typedef cna::heap64 <21, AllocByte>   A21 ;
    typedef cna::heap64 <22, AllocByte>   A22 ;
    typedef cna::heap64 <23, AllocByte>   A23 ;
    typedef cna::heap64 <24, AllocByte>   A24 ;

    typedef cna::heap64 <25, AllocByte>   A25 ;
    typedef cna::heap64 <26, AllocByte>   A26 ;
    typedef cna::heap64 <27, AllocByte>   A27 ;
    typedef cna::heap64 <28, AllocByte>   A28 ;
    typedef cna::heap64 <29, AllocByte>   A29 ;
    typedef cna::heap64 <30, AllocByte>   A30 ;

    fill_empty<A0>() ;
    fill_empty<A1>() ;
    fill_empty<A2>() ;
    fill_empty<A3>() ;
    fill_empty<A4>() ;
    fill_empty<A5>() ;

    fill_empty<A6>() ;
    fill_empty<A7>() ;
    fill_empty<A8>() ;
    fill_empty<A9>() ;
    fill_empty<A10>() ;


    fill_empty<A11>() ;
    fill_empty<A12>() ;
    fill_empty<A13>() ;
    fill_empty<A14>() ;
    fill_empty<A15>() ;

    fill_empty<A16>() ;
    fill_empty<A17>() ;
    fill_empty<A18>() ;
    fill_empty<A19>() ;
    fill_empty<A20>() ;

    fill_empty<A21>() ;
    fill_empty<A22>() ;
    fill_empty<A23>() ;
    fill_empty<A24>() ;

    fill_empty<A25>() ;
    fill_empty<A26>() ;
    fill_empty<A27>() ;
    fill_empty<A28>() ;
    fill_empty<A29>() ;
    fill_empty<A30>() ;

    fill_test<A0,1>() ;
    fill_test<A1,1>() ;
    fill_test<A2,1>() ;
    fill_test<A3,1>() ;
    fill_test<A4,1>() ;
    fill_test<A5,1>() ;

    fill_test<A6,1>() ;
    fill_test<A7,1>() ;
    fill_test<A8,1>() ;
    fill_test<A9,1>() ;
    fill_test<A10,1>() ;

    fill_test<A11,1>() ;
    fill_test<A12,2>() ;
    fill_test<A13,3>() ;
    fill_test<A14,4>() ;
    fill_test<A15,5>() ;

    fill_test<A16,6>() ;
    fill_test<A17,7>() ;
    fill_test<A18,8>() ;
    fill_test<A19,9>() ;
    fill_test<A20,10>() ;

    fill_test<A21,11>() ;
    fill_test<A22,12>() ;
    fill_test<A23,13>() ;
    fill_test<A24,14>() ;
/*
    fill_test<A25,20>() ;
    fill_test<A26,20>() ;
    fill_test<A27,21>() ;
    fill_test<A28,22>() ;
    fill_test<A29,23>() ;
    fill_test<A30,24>() ;
*/
};
template <typename H, uint32_t N>
void fill_test ( void)
{   //---------------------- begin ------------------
    H * Alfa = create <H> ();
    //std::cout<<"[ NElemMax: "<<NElemMax<<" ]"<<std::endl;
    const uint32_t Mask = ( 1<<N)-1 ;

    for ( uint32_t i = 0 ; i < Alfa->NElemMax ; ++i)
    {   if ( (i & Mask) != Mask) Alfa->allocate() ;
        else
        {   if ( Alfa->is_full()) BOOST_CHECK ( false );
            if ( Alfa->read_bit (i)) BOOST_CHECK ( false );
            if ( Alfa->allocate() != i) BOOST_CHECK ( false );
            if ( not Alfa->read_bit (i)) BOOST_CHECK ( false );
            Alfa->deallocate (i);
            if ( Alfa->read_bit (i)) BOOST_CHECK ( false );
            if ( Alfa->allocate() != i) BOOST_CHECK ( false );
            if ( not Alfa->read_bit (i)) BOOST_CHECK ( false );
            if ( not Alfa->check()) BOOST_CHECK ( false );
        };
    };
    if ( not Alfa->is_full())  BOOST_CHECK ( false );

    Alfa->clear();
    for ( uint32_t i = 0 ; i < Alfa->NElemMax ; ++i)
    {   if ( Alfa->read_bit (i))  BOOST_CHECK ( false );
    };
    destroy < H>  (Alfa);
};
template <typename H>
void fill_empty ( void)
{   //---------------------- begin ------------------
    H * Alfa = create <H> ();

    for ( uint32_t i = 0 ; i < Alfa->NElemMax ; ++i)
    {   if ( Alfa->allocate() != i) BOOST_CHECK ( false ) ;
    };
    BOOST_CHECK(  Alfa->is_full());

    for ( uint32_t i = 0 ; i < Alfa->NElemMax ; ++i)
    {   Alfa->deallocate(i)  ;
    };
    BOOST_CHECK(  Alfa->is_empty());
    destroy < H>  (Alfa);
};

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test32 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test64 ) );

    return 0;
}
