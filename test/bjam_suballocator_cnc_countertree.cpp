//----------------------------------------------------------------------------
/// @file test_suballocator_cnc.cpp
/// @brief Test program of the class suballocator_cnc, suballocator32_cnc and
///        suballocator64_cnc
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
//#define __DEBUG_CNTREE 1
#include <boost/countertree/suballocator.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <time.h>
#include <thread>
#include <vector>
#include <list>
#include <set>
#define NELEM_VECTOR 1000000
#define NELEM_SET     100000
#define NELEM_LIST   500000
using namespace boost::unit_test;
namespace cntree= countertree ;



template <class Allocator>
void test_vector ( void)
{   //------------------------------ begin ----------------------------------
    double ** K = new double* [NELEM_VECTOR];
    typename Allocator::template rebind<double >::other A;

    for ( uint32_t Alfa = 0 ; Alfa < 5 ; ++Alfa)
    {   for ( uint32_t i =0  ; i < NELEM_VECTOR ; ++i)
            K[i] = A.allocate(1);

        for ( uint32_t i =0  ; i < NELEM_VECTOR ; ++i)
            A.deallocate(K[i],1);
    };
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
    typedef std::allocator<void> S0 ;
    typedef cntree::suballocator32_cnc <S0 > S1 ;
    typedef cntree::suballocator64_cnc <S0 > S2 ;
    typedef cntree::suballocator_cnc   <S0 > S3 ;
    typedef cntree::suballocator32_cnc <S1 > S4 ;
    typedef cntree::suballocator32_cnc <S2 > S5 ;
    typedef cntree::suballocator64_cnc <S1 > S6 ;
    typedef cntree::suballocator64_cnc <S2 > S7 ;
    typedef cntree::suballocator_cnc   <S3 > S8 ;
    typedef cntree::suballocator_cnc   <S8 > S9 ;


    //------------------------------------------------------------
    //                  Invocations
    //------------------------------------------------------------

    std::thread  T01 ( test_vector<S0 >  );
    std::thread  T02 ( test_vector<S1 >  );
    std::thread  T03 ( test_vector<S2 >  );
    std::thread  T04 ( test_vector<S3 >  );

    T01.join() ;
    T02.join() ;
    T03.join() ;
    T04.join() ;

    std::thread  T05 ( test_vector<S4 >  );
    std::thread  T06 ( test_vector<S5 >  );
    std::thread  T07 ( test_vector<S6 >  );

    T05.join() ;
    T06.join() ;
    T07.join() ;

    std::thread  T08 ( test_vector<S7 >  );
    std::thread  T09 ( test_vector<S8 >  );
    std::thread  T10 ( test_vector<S9 >  );
    T08.join() ;
    T09.join() ;
    T10.join() ;

    //------- Test set -------------------
    std::thread  T11 ( test_set<S0 >   );
    std::thread  T12 ( test_set<S1 >   );
    std::thread  T13 ( test_set<S2 >   );
    std::thread  T14 ( test_set<S3 >   );

    T11.join() ;
    T12.join() ;
    T13.join() ;
    T14.join() ;

    std::thread  T15 ( test_set<S4 >   );
    std::thread  T16 ( test_set<S5 >   );
    std::thread  T17 ( test_set<S6 >   );

    T15.join() ;
    T16.join() ;
    T17.join() ;

    std::thread  T18 ( test_set<S7 >   );
    std::thread  T19 ( test_set<S8 >   );
    std::thread  T20 ( test_set<S9 >   );

    T18.join() ;
    T19.join() ;
    T20.join() ;

    //------------ test List -------------
    std::thread  T21 ( test_list<S0 >   );
    std::thread  T22 ( test_list<S1 >   );
    std::thread  T23 ( test_list<S2 >   );
    std::thread  T24 ( test_list<S3 >   );
    T21.join() ;
    T22.join() ;
    T23.join() ;
    T24.join() ;

    std::thread  T25 ( test_list<S4 >   );
    std::thread  T26 ( test_list<S5 >   );
    std::thread  T27 ( test_list<S6 >   );
    T25.join() ;
    T26.join() ;
    T27.join() ;

    std::thread  T28 ( test_list<S7 >   );
    std::thread  T29 ( test_list<S8 >   );
    std::thread  T30 ( test_list<S9 >   );

    T28.join() ;
    T29.join() ;
    T30.join() ;


}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test ) );
    return 0;
}
