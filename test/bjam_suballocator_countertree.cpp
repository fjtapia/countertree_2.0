//----------------------------------------------------------------------------
/// @file test_suballocator.cpp
/// @brief Test program of the class suballocator, suballocator32 and
///        suballocator64
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
#define NELEM_VECTOR 10000000
#define NELEM_SET     1000000
#define NELEM_LIST   5000000
using namespace boost::unit_test;



namespace cntree = countertree ;

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
    assert ( S.size() == NELEM_SET);
    for ( uint64_t i =0  ; i < NELEM_SET ; ++i)
    {   S.erase ( i);
    }
    assert ( S.size() == 0);
};
template <class Allocator>
void test_list ( void)
{   //------------------------------ begin ----------------------------------
    std::list<uint64_t,Allocator > S;

    for ( uint64_t i =0  ; i < NELEM_LIST ; ++i)
        S.push_back (i);
    assert ( S.size() == NELEM_LIST);
    for ( uint64_t i =0  ; i < NELEM_LIST ; ++i)
    {   S.pop_front ();
    };
    assert ( S.size() == 0);
}

void test ( void)
{   //---------------------------- begin---------------------------

    typedef std::allocator<uint8_t> S0 ;
    typedef cntree::suballocator32 <S0 > S1 ;
    typedef cntree::suballocator64 <S0 > S2 ;
    typedef cntree::suballocator   <S0 > S3 ;
    typedef cntree::suballocator32 <S1 > S4 ;
    typedef cntree::suballocator32 <S2 > S5 ;
    typedef cntree::suballocator64 <S1 > S6 ;
    typedef cntree::suballocator64 <S2 > S7 ;
    typedef cntree::suballocator   <S3 > S8 ;
    typedef cntree::suballocator   <S8 > S9 ;


    //------------------------------------------------------------
    //                  Invocations
    //------------------------------------------------------------
    test_vector<S0 > () ;
    test_vector<S1 > () ;
    test_vector<S2 > () ;
    test_vector<S3 > () ;
    test_vector<S4 > () ;
    test_vector<S5 > () ;
    test_vector<S6 > () ;
    test_vector<S7 > () ;
    test_vector<S8 > () ;
    test_vector<S9 > () ;

    test_set<S0 > () ;
    test_set<S1 > () ;
    test_set<S2 > () ;
    test_set<S3 > () ;
    test_set<S4 > () ;
    test_set<S5 > () ;
    test_set<S6 > () ;
    test_set<S7 > () ;
    test_set<S8 > () ;
    test_set<S9 > () ;

    test_list<S0 > () ;
    test_list<S1 > () ;
    test_list<S2 > () ;
    test_list<S3 > () ;
    test_list<S4 > () ;
    test_list<S5 > () ;
    test_list<S6 > () ;
    test_list<S7 > () ;
    test_list<S8 > () ;
    test_list<S9 > () ;
}
template < class Allocator>
void concurrent ( void)
{   //------------------------------------------------------------
    //                  Invocations
    //------------------------------------------------------------

    std::thread  T01 ( test_vector<Allocator >  );
    std::thread  T02 ( test_vector<Allocator >  );
    std::thread  T03 ( test_vector<Allocator >  );
    std::thread  T04 ( test_vector<Allocator >  );

    T01.join() ;
    T02.join() ;
    T03.join() ;
    T04.join() ;


    //------- Test set -------------------
    std::thread  T11 ( test_set<Allocator >   );
    std::thread  T12 ( test_set<Allocator >   );
    std::thread  T13 ( test_set<Allocator >   );
    std::thread  T14 ( test_set<Allocator >   );

    T11.join() ;
    T12.join() ;
    T13.join() ;
    T14.join() ;

    //------------ test List -------------
    std::thread  T21 ( test_list<Allocator >   );
    std::thread  T22 ( test_list<Allocator >   );
    std::thread  T23 ( test_list<Allocator >   );
    std::thread  T24 ( test_list<Allocator >   );
    T21.join() ;
    T22.join() ;
    T23.join() ;
    T24.join() ;

}
void test2 ( void)
{   //---------------------------- begin---------------------------
    typedef std::allocator<void> S0 ;
    typedef cntree::suballocator32 <S0 > S1 ;
    typedef cntree::suballocator64 <S0 > S2 ;
    typedef cntree::suballocator   <S0 > S3 ;
    typedef cntree::suballocator32 <S1 > S4 ;
    typedef cntree::suballocator32 <S2 > S5 ;
    typedef cntree::suballocator64 <S1 > S6 ;
    typedef cntree::suballocator64 <S2 > S7 ;
    typedef cntree::suballocator   <S3 > S8 ;
    typedef cntree::suballocator   <S8 > S9 ;


    //------------------------------------------------------------
    //                  Invocations
    //------------------------------------------------------------
    concurrent<S0> ( );
    concurrent<S1> ( );
    concurrent<S2> ( );
    concurrent<S3> ( );
    concurrent<S4> ( );
    concurrent<S5> ( );
    concurrent<S6> ( );
    concurrent<S7> ( );
    concurrent<S8> ( );
    concurrent<S9> ( );

}
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test2 ) );
    return 0;
}
