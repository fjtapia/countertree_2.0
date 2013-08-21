//----------------------------------------------------------------------------
/// @file test_allocator_mc.cpp
/// @brief Test program of the class allocator_mc
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <boost/countertree/myallocator.hpp>
#include <boost/test/included/unit_test.hpp>
#include <cassert>
#include <iostream>
#include <time.h>
#include <thread>
#include <set>
#include <list>
#define NELEM_VECTOR 1000000
#define NELEM_SET    500000
#define NELEM_LIST   1000000

using namespace boost::unit_test;
namespace cntree= countertree ;

template <class Allocator>
void test_vector ( void)
{   //------------------------------ begin ----------------------------------
    double ** K = new double* [NELEM_VECTOR];
    typename Allocator::template rebind<double >::other A;

    for ( uint32_t i =0  ; i < NELEM_VECTOR ; ++i)
        K[i] = A.allocate(1);

    for ( uint32_t i =0  ; i < NELEM_VECTOR ; ++i)
         A.deallocate(K[i],1);
    delete[] K;
};
template <class Allocator>
void test_set ( void)
{   //------------------------------ begin ----------------------------------
    std::set<uint64_t,std::less<uint64_t>,Allocator > S;

    for ( uint64_t i =0  ; i < NELEM_SET ; ++i)
        S.insert(i);
    BOOST_CHECK ( S.size() == NELEM_SET);
    for ( uint64_t i =0  ; i < NELEM_SET ; ++i)
    {   S.erase ( i);
    }
    BOOST_CHECK ( S.size() == 0);
};
template <class Allocator>
void test_list ( void)
{   //------------------------------ begin ----------------------------------
    std::list<uint64_t,Allocator > S;

    for ( uint64_t i =0  ; i < NELEM_LIST ; ++i)
        S.push_back (i);
    BOOST_CHECK ( S.size() == NELEM_LIST);
    for ( uint64_t i =0  ; i < NELEM_LIST ; ++i)
    {   S.pop_front ();
    };
    BOOST_CHECK ( S.size() == 0);
}
void test ( void)
{   //---------------------------- begin---------------------------
    typedef cntree::myallocator<void> S1 ;
    typedef cntree::myallocator<void> S2 ;

    //------------------------------------------------------------
    //                  Invocations
    //------------------------------------------------------------
    for ( int i =0 ; i <5 ; ++i)
    {   std::thread T1 ( test_vector<S1 > ) ;
        std::thread T2 ( test_set<S1 > ) ;
        std::thread T3 ( test_list<S1 > ) ;
        T1.join();
        T2.join() ;
        T3.join();
    };
    for ( int i =0 ; i <5 ; ++i)
    {   std::thread T1 ( test_vector<S2 > ) ;
        std::thread T2 ( test_set<S2 > ) ;
        std::thread T3 ( test_list<S2 > ) ;
        T1.join();
        T2.join() ;
        T3.join();
    };
}

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test ) );
    return 0;
}

