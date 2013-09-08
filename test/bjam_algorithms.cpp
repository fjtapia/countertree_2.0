//----------------------------------------------------------------------------
/// @file bjam_algorithms.cpp
/// @brief Test program of several routines containes in the files
///        algorithms32.hpp and algorithms64.hpp
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
#include <iostream>
#include <time.h>
#include <boost/countertree/common/algorithms32.hpp>
#include <boost/countertree/common/algorithms64.hpp>
#define NELEM 10000000


using namespace boost::unit_test;
using namespace countertree::common;

void prueba32 ( void)
{   //------------------------------- begin ----------------------------

    //------------------------------------------------------------------
    // Test SetBit32, ResetBit32 and ReadBit32
    //------------------------------------------------------------------
    uint32_t N =0 ;
    SetBit32 ( N, 8 );
    BOOST_CHECK ( N  == 256 and ReadBit32 ( N, 8 ));
    SetBit32 ( N, 16) ;
    BOOST_CHECK (  N == 65792 and ReadBit32 ( N, 16));
    ResetBit32 ( N , 8 );
    BOOST_CHECK ( N == 65536 and not ReadBit32 ( N, 8));
    ResetBit32 ( N , 16 )  ;
    BOOST_CHECK ( N == 0  and not ReadBit32 ( N , 16));

    //------------------------------------------------------------------
    // Test LS1B_32 ( Least Significant 1 Bit )
    // Test MS1B_32 ( Most  Significant 1 Bit )
    //-----------------------------------------------------------------
    BOOST_CHECK ( LS1B_32 (0x5324) == 2 );
    BOOST_CHECK ( LS1B_32 (0x5320U) == 5 );
    BOOST_CHECK ( LS1B_32 (0x80000000U) == 31);
    BOOST_CHECK ( LS1B_32 (0x80001000U) == 12);

    BOOST_CHECK ( MS1B_32 (0x5324) == 14);
    BOOST_CHECK ( MS1B_32 (0x80000000U) == 31);
    BOOST_CHECK ( MS1B_32 (1U) == 0);

    //------------------------------------------------------------------
    // Test SizeAligned32
    //------------------------------------------------------------------
    BOOST_CHECK (SizeAligned32 ( 0) == 1  );

    BOOST_CHECK (SizeAligned32 ( 1) == 1  );

    BOOST_CHECK (SizeAligned32 ( 2) == 2  );

    BOOST_CHECK (SizeAligned32 ( 3) == 4  );
    BOOST_CHECK (SizeAligned32 ( 4) == 4  );

    BOOST_CHECK (SizeAligned32 ( 5) == 8  );
    BOOST_CHECK (SizeAligned32 ( 6) == 8  );
    BOOST_CHECK (SizeAligned32 ( 7) == 8  );
    BOOST_CHECK (SizeAligned32 ( 8) == 8  );

    BOOST_CHECK (SizeAligned32 ( 9) == 16 );
    BOOST_CHECK (SizeAligned32 (10) == 16 );
    BOOST_CHECK (SizeAligned32 (11) == 16 );
    BOOST_CHECK (SizeAligned32 (12) == 16 );
    BOOST_CHECK (SizeAligned32 (13) == 16 );
    BOOST_CHECK (SizeAligned32 (14) == 16 );
    BOOST_CHECK (SizeAligned32 (15) == 16 );
    BOOST_CHECK (SizeAligned32 (16) == 16 );


    BOOST_CHECK (SizeAligned32 (17) == 32 );
    BOOST_CHECK (SizeAligned32 (18) == 32 );
    BOOST_CHECK (SizeAligned32 (19) == 32 );
    BOOST_CHECK (SizeAligned32 (20) == 32 );
    BOOST_CHECK (SizeAligned32 (21) == 32 );
    BOOST_CHECK (SizeAligned32 (22) == 32 );
    BOOST_CHECK (SizeAligned32 (23) == 32 );
    BOOST_CHECK (SizeAligned32 (24) == 32 );
    BOOST_CHECK (SizeAligned32 (25) == 32 );
    BOOST_CHECK (SizeAligned32 (26) == 32 );
    BOOST_CHECK (SizeAligned32 (27) == 32 );
    BOOST_CHECK (SizeAligned32 (28) == 32 );
    BOOST_CHECK (SizeAligned32 (29) == 32 );
    BOOST_CHECK (SizeAligned32 (30) == 32 );
    BOOST_CHECK (SizeAligned32 (31) == 32 );
    BOOST_CHECK (SizeAligned32 (32) == 32 );

    BOOST_CHECK (SizeAligned32 (33) == 48 );
    BOOST_CHECK (SizeAligned32 (34) == 48 );
    BOOST_CHECK (SizeAligned32 (35) == 48 );
    BOOST_CHECK (SizeAligned32 (36) == 48 );
    BOOST_CHECK (SizeAligned32 (37) == 48 );
    BOOST_CHECK (SizeAligned32 (38) == 48 );
    BOOST_CHECK (SizeAligned32 (39) == 48 );
    BOOST_CHECK (SizeAligned32 (40) == 48 );
    BOOST_CHECK (SizeAligned32 (41) == 48 );
    BOOST_CHECK (SizeAligned32 (42) == 48 );
    BOOST_CHECK (SizeAligned32 (43) == 48 );
    BOOST_CHECK (SizeAligned32 (44) == 48 );
    BOOST_CHECK (SizeAligned32 (45) == 48 );
    BOOST_CHECK (SizeAligned32 (46) == 48 );
    BOOST_CHECK (SizeAligned32 (47) == 48 );
    BOOST_CHECK (SizeAligned32 (48) == 48 );

    BOOST_CHECK (SizeAligned32 (49) == 64 );

    BOOST_CHECK (SizeAligned32 (127) == 128 );
    BOOST_CHECK (SizeAligned32 (128) == 128 );
    BOOST_CHECK (SizeAligned32 (129) == 144 );

    BOOST_CHECK (SizeAligned32 (145) == 160 );

    BOOST_CHECK (SizeAligned32 (256) == 256);
    BOOST_CHECK (SizeAligned32 (257) == 272);

    BOOST_CHECK (SizeAligned32 (1023) == 1024);
    BOOST_CHECK (SizeAligned32 (1024) == 1024);
    BOOST_CHECK (SizeAligned32 (1025) == 1280);

    BOOST_CHECK (SizeAligned32 (0xB9800) == 0xC0000);
};
void prueba64 ( void)
{   //------------------------------- begin ----------------------------
    //------------------------------------------------------------------
    // Test SetBit64, ResetBit64 and ReadBit64
    //------------------------------------------------------------------
    uint64_t N =0 ;
    SetBit64 ( N, 8 );
    BOOST_CHECK ( N  == 256 and ReadBit64 ( N, 8 ));
    SetBit64 ( N, 16) ;
    BOOST_CHECK (  N == 65792 and ReadBit64 ( N, 16));
    ResetBit64 ( N , 8 );
    BOOST_CHECK ( N == 65536 and not ReadBit64 ( N, 8));
    ResetBit64 ( N , 16 )  ;
    BOOST_CHECK ( N == 0  and not ReadBit64 ( N , 16));

    //------------------------------------------------------------------
    // Test LS1B_64 ( Least Significant 1 Bit )
    // Test MS1B_64 ( Most  Significant 1 Bit )
    //-----------------------------------------------------------------
    BOOST_CHECK ( LS1B_64 (0x5324ULL) == 2 );
    BOOST_CHECK ( LS1B_64 (0x5320ULL) == 5 );
    BOOST_CHECK ( LS1B_64 (0x80000000ULL) == 31);
    BOOST_CHECK ( LS1B_64 (0x80001000ULL) == 12);

    BOOST_CHECK ( MS1B_64 (0x5324) == 14);
    BOOST_CHECK ( MS1B_64 (0x80000000U) == 31);
    BOOST_CHECK ( MS1B_64 (1U) == 0);

    //------------------------------------------------------------------
    // Test SizeAligned64
    //------------------------------------------------------------------
    BOOST_CHECK (SizeAligned64 ( 0) == 1  );

    BOOST_CHECK (SizeAligned64 ( 1) == 1  );

    BOOST_CHECK (SizeAligned64 ( 2) == 2  );

    BOOST_CHECK (SizeAligned64 ( 3) == 4  );
    BOOST_CHECK (SizeAligned64 ( 4) == 4  );

    BOOST_CHECK (SizeAligned64 ( 5) == 8  );
    BOOST_CHECK (SizeAligned64 ( 6) == 8  );
    BOOST_CHECK (SizeAligned64 ( 7) == 8  );
    BOOST_CHECK (SizeAligned64 ( 8) == 8  );

    BOOST_CHECK (SizeAligned64 ( 9) == 16 );
    BOOST_CHECK (SizeAligned64 (10) == 16 );
    BOOST_CHECK (SizeAligned64 (11) == 16 );
    BOOST_CHECK (SizeAligned64 (12) == 16 );
    BOOST_CHECK (SizeAligned64 (13) == 16 );
    BOOST_CHECK (SizeAligned64 (14) == 16 );
    BOOST_CHECK (SizeAligned64 (15) == 16 );
    BOOST_CHECK (SizeAligned64 (16) == 16 );


    BOOST_CHECK (SizeAligned64 (17) == 32 );
    BOOST_CHECK (SizeAligned64 (18) == 32 );
    BOOST_CHECK (SizeAligned64 (19) == 32 );
    BOOST_CHECK (SizeAligned64 (20) == 32 );
    BOOST_CHECK (SizeAligned64 (21) == 32 );
    BOOST_CHECK (SizeAligned64 (22) == 32 );
    BOOST_CHECK (SizeAligned64 (23) == 32 );
    BOOST_CHECK (SizeAligned64 (24) == 32 );
    BOOST_CHECK (SizeAligned64 (25) == 32 );
    BOOST_CHECK (SizeAligned64 (26) == 32 );
    BOOST_CHECK (SizeAligned64 (27) == 32 );
    BOOST_CHECK (SizeAligned64 (28) == 32 );
    BOOST_CHECK (SizeAligned64 (29) == 32 );
    BOOST_CHECK (SizeAligned64 (30) == 32 );
    BOOST_CHECK (SizeAligned64 (31) == 32 );
    BOOST_CHECK (SizeAligned64 (32) == 32 );

    BOOST_CHECK (SizeAligned64 (33) == 48 );
    BOOST_CHECK (SizeAligned64 (34) == 48 );
    BOOST_CHECK (SizeAligned64 (35) == 48 );
    BOOST_CHECK (SizeAligned64 (36) == 48 );
    BOOST_CHECK (SizeAligned64 (37) == 48 );
    BOOST_CHECK (SizeAligned64 (38) == 48 );
    BOOST_CHECK (SizeAligned64 (39) == 48 );
    BOOST_CHECK (SizeAligned64 (40) == 48 );
    BOOST_CHECK (SizeAligned64 (41) == 48 );
    BOOST_CHECK (SizeAligned64 (42) == 48 );
    BOOST_CHECK (SizeAligned64 (43) == 48 );
    BOOST_CHECK (SizeAligned64 (44) == 48 );
    BOOST_CHECK (SizeAligned64 (45) == 48 );
    BOOST_CHECK (SizeAligned64 (46) == 48 );
    BOOST_CHECK (SizeAligned64 (47) == 48 );
    BOOST_CHECK (SizeAligned64 (48) == 48 );

    BOOST_CHECK (SizeAligned64 (49) == 64 );

    BOOST_CHECK (SizeAligned64 (127) == 128 );
    BOOST_CHECK (SizeAligned64 (128) == 128 );
    BOOST_CHECK (SizeAligned64 (129) == 144 );

    BOOST_CHECK (SizeAligned64 (145) == 160 );

    BOOST_CHECK (SizeAligned64 (256) == 256);
    BOOST_CHECK (SizeAligned64 (257) == 272);

    BOOST_CHECK (SizeAligned64 (1023) == 1024);
    BOOST_CHECK (SizeAligned64 (1024) == 1024);
    BOOST_CHECK (SizeAligned64 (1025) == 1280);

    BOOST_CHECK (SizeAligned64 (0xB9800) == 0xC0000);

}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba32 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba64 ) );

    return 0;
}
