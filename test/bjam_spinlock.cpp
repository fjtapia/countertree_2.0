//----------------------------------------------------------------------------
/// @file bjam_spinlock.cpp
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
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/common/spinlock.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <cassert>

using namespace boost::unit_test;
int N =0 ;
int function1() ;
int function2() ;
countertree::common::spinlock s ;
std::chrono::seconds sec(1);

void start ( void)
{   //---------------------- begin ---------------------
    assert ( N ==0 );
    //std::cout<<" Begin main function \n";
    N++ ;
    s.try_lock() ;
    N++ ;
    std::thread T1 ( function1);
    std::thread T2 ( function2);
    //std::cout<<"Inside main function \n";
    std::this_thread::sleep_for( std::chrono::seconds(3) ) ;
    assert ( N == 4 );
    N++ ;
    s.unlock() ;
    T1.join() ;
    T2.join() ;
    assert ( N == 9);
    //std::cout<<"End of main function \n";
}
int function1()
{   //---------------------------- begin -----------------
    //std::cout<<" Begin function1 \n";
    N++ ;
    std::unique_lock<countertree::common::spinlock > ul(s);
    assert ( N == 5 or N == 7 );
    N++;
    //std::cout<<"Inside function1 \n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::cout<<"End of function1 \n";
    N++ ;
    return 0 ;
}
int function2()
{   //---------------------------- begin -----------------
    //std::cout<<" Begin function2 \n";
    N++ ;
    std::unique_lock<countertree::common::spinlock > ul(s);
    assert ( N == 5 or N == 7 );
    N++ ;
    //std::cout<<"Inside function2 \n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::cout<<"End of function2 \n";
    N++;
    return 0 ;
}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &start ) );

    return 0;
}
