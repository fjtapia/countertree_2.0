//----------------------------------------------------------------------------
/// @file bjam_pool_cnc.cpp
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
#include <thread>
#include <mutex>
#define NELEM 1000000

using namespace boost::unit_test;
using namespace countertree::alloc ;
namespace   cntr_cm = countertree::common;

int32_t **K ;
typedef   countertree::alloc::pool32 <4,true,std::allocator<uint8_t> > P32   ;
typedef   countertree::alloc::pool64 <4,true,std::allocator<uint8_t> > P64  ;
P32 A1 ;
P64 A2 ;
typedef countertree::common::spinlock     splock ;

splock spl ;

template <class Pool>
int TestAllocation ( Pool & P)
{   //------------------------------ begin ----------------------------------
    std::once_flag flag;
    //std::thread::id Tid = std::this_thread::get_id() ;

    //std::call_once(flag, [](){ std::cout<<" Begin function1 "<<std::this_thread::get_id()<<"  "<<std::endl;});

    int32_t Pos ;

    while ( P.size() < NELEM)
    {   std::unique_lock<splock> ul( spl);
        if (P.size()>= NELEM) break ;
        Pos = P.size() ;
        if ( K[Pos ]!= NULL )
        {   std::cout<<"Error en la posicion "<<Pos<<std::endl ;
            return 1 ;
        };
        K[Pos ] = (int32_t*) P.allocate();
    };
    return 0 ;
}
template <class Pool>
int TestDeallocation ( Pool & P)
{   //------------------------------ begin ----------------------------------
    std::once_flag flag;
    //std::thread::id Tid = std::this_thread::get_id() ;
    int32_t Pos ;
    //std::call_once(flag, [](){ std::cout<<"Beginning deallocation"<<std::this_thread::get_id()<<"  "<<std::endl;});
    while ( P.size() > 0  )
    {   std::unique_lock<splock> ul( spl);
        Pos = P.size() ;
        if ( Pos == 0) break ;
        if ( K[Pos-1 ]== NULL )
        {   std::cout<<"Error en la posicion "<<Pos<<std::endl ;
            return 1 ;
        };
        P.deallocate((void*) K[Pos-1]);
        //std::cout<<"["<<Tid<<" , "<<(Pos-1)<<"]\n";
    };
    return 0 ;
};

void Test32 ( void)
{   //------------------------------ begin ----------------------------------
    K = new int32_t*[NELEM];
    BOOST_CHECK ( K != NULL);

    for ( int x =0 ; x < 3 ; ++x)
    {   for ( uint32_t i =0 ; i < NELEM ; i++) K[i] = NULL ;

        std::thread  T1( TestAllocation<P32>, std::ref(A1));
        std::thread  T2( TestAllocation<P32>, std::ref(A1));
        std::thread  T3( TestAllocation<P32>, std::ref(A1));
        std::thread  T4( TestAllocation<P32>, std::ref(A1));

        T1.join() ;
        T2.join() ;
        T3.join() ;
        T4.join() ;

        BOOST_CHECK ( A1.check());
        BOOST_CHECK ( A1.size() == NELEM);

        std::thread  T5( TestDeallocation<P32>, std::ref(A1));
        std::thread  T6( TestDeallocation<P32>, std::ref(A1));
        std::thread  T7( TestDeallocation<P32>, std::ref(A1));
        std::thread  T8( TestDeallocation<P32>, std::ref(A1));

        T5.join() ;
        T6.join() ;
        T7.join() ;
        T8.join() ;
        BOOST_CHECK ( A1.check());
        BOOST_CHECK ( A1.size() == 0);
    };
    delete[] K ;
};
void Test64 ( void)
{   //------------------------------ begin ----------------------------------
    K = new int32_t*[NELEM];
    BOOST_CHECK ( K != NULL);

    for ( int x =0 ; x < 3 ; ++x)
    {   for ( uint32_t i =0 ; i < NELEM ; i++) K[i] = NULL ;

        std::thread  T1( TestAllocation<P64>, std::ref(A2));
        std::thread  T2( TestAllocation<P64>, std::ref(A2));
        std::thread  T3( TestAllocation<P64>, std::ref(A2));
        std::thread  T4( TestAllocation<P64>, std::ref(A2));

        T1.join() ;
        T2.join() ;
        T3.join() ;
        T4.join() ;

        BOOST_CHECK ( A2.check());
        BOOST_CHECK ( A2.size() == NELEM);


        std::thread  T5( TestDeallocation<P64>, std::ref(A2));
        std::thread  T6( TestDeallocation<P64>, std::ref(A2));
        std::thread  T7( TestDeallocation<P64>, std::ref(A2));
        std::thread  T8( TestDeallocation<P64>, std::ref(A2));

        T5.join() ;
        T6.join() ;
        T7.join() ;
        T8.join() ;

        BOOST_CHECK ( A2.check());
        BOOST_CHECK ( A2.size() == 0);
    };
    delete[] K ;
};
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test32) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Test64 ) );

    return 0;
}
