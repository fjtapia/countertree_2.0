//----------------------------------------------------------------------------
/// @file bjam_mysingleton.cpp
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
#include <boost/countertree/common/singleton.hpp>
#include <cassert>

#include <iostream>


namespace c_common = countertree::common ;
using namespace boost::unit_test;

struct chapuza
{   int N ;
    ~chapuza () { N =0 ;};
};

struct glb_chapuza
{
    static chapuza & ch  ;

    glb_chapuza ( ) {}
    ~glb_chapuza ()
    {   assert ( ch.N == 17); // This can't be BOOST_CHECK because fail
    };
};
chapuza & glb_chapuza::ch = c_common::singleton <chapuza>::instance()  ;

static glb_chapuza &gch = c_common::singleton <glb_chapuza>::instance() ;



void prueba ( void)
{   //---------------------- begin ---------------------
    gch.ch.N = 17 ;
    chapuza & ch1 ( c_common::singleton <chapuza>::instance());
    BOOST_CHECK ( ch1.N == 17);
    //glb_chapuza & gch1 ( c_common::singleton <glb_chapuza>::instance() );
    glb_chapuza gch1 ;
    BOOST_CHECK ( gch1.ch.N == 17);
    gch1.ch = ch1 ;
    BOOST_CHECK ( gch1.ch.N == 17);
    {   chapuza & ch2 ( c_common::singleton <chapuza>::instance());
        BOOST_CHECK ( ch1.N == 17);
        ch1 = ch2 ;
    }
    BOOST_CHECK ( ch1.N == 17);
    BOOST_CHECK ( gch1.ch.N == 17);
}

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba ) );

    return 0;
}
