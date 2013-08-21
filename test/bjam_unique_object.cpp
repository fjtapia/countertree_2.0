//----------------------------------------------------------------------------
/// @file bjam_unique_object.cpp
/// @brief Test program of the class spinlock
///
/// @author Copyright (c) 2010 2012 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#define __DEBUG_CNTREE 1
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/common/unique_object.hpp>
#include <cassert>
#include <vector>
#include <thread>
#include <iostream>


namespace c_common = countertree::common ;
using namespace boost::unit_test;

void prueba ( int N)
{   //---------------------- begin ---------------------
    c_common::unique_object<std::vector<int> > V1 ;
    assert ( V1->size() == 0 );

    for ( int i =0 ; i < 1000 ; ++i)
        V1->push_back (N+i);

    c_common::unique_object<std::vector<int> > V2 ;
    for ( int i =0 ; i < 1000 ; ++i)
        (*V2)[i]+= 1000;

    c_common::unique_object<std::vector<int> > V3 ;
    for ( int i =0 ; i < 1000 ; ++i)
        assert ( V1()[i] == V3()[i] and V1()[i] == (i + N + 1000 ));
}
void  start()
{
    std::thread T1 ( prueba,1000);
    std::thread T2 ( prueba,2000);
    std::thread T3 ( prueba,3000);
    std::thread T4 ( prueba,4000);
    prueba (9000) ;

    T1.join() ;
    T2.join() ;
    T3.join() ;
    T4.join() ;

}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &start ) );

    return 0;
}

