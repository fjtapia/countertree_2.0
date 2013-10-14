//----------------------------------------------------------------------------
/// @file bjam_fastmutex.cpp
/// @brief Test program of the classes countertree::set and countertree::multiset
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------

#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/mutex_read_write.hpp>

#include <iostream>
#include <atomic>
#define NBITS 18


namespace cntree = countertree ;
using namespace boost::unit_test;

typedef cntree::rw_fastmutex_data                           mutex_data ;
typedef cntree::mutex_read        < mutex_data>             mutex_read ;
typedef cntree::mutex_write       < mutex_data>             mutex_write ;
typedef cntree::mutex_write_read  < mutex_data, mutex_data> mutex_write_read ;
typedef cntree::mutex_write_write < mutex_data, mutex_data> mutex_write_write ;
typedef cntree::mutex_read_read   < mutex_data, mutex_data> mutex_read_read ;
struct counter
{   //------------------------- variables -------------------
    mutable mutex_data mdc ;
    int N ;

    //------------------------ functions ---------------------
    counter ( void):N(-1){};

    counter ( int K):N(K){};

    counter ( const counter &c)
    {   mutex_read MR ( mdc);
        //std::unique_lock<mutex_read> UL ( MR);
        N = c.N ;
    };

    counter ( counter &&c)
    {   mutex_write MM(mdc);
        //std::unique_lock<mutex_write> UL (MM);
        N = c.N;
        MM.wait_no_readers() ;
        c.N = -1;
    };

    int read ( void) const
    {   mutex_read MR ( mdc);
        //std::unique_lock<mutex_read> UL ( MR);
        return N ;

    }
    counter & operator = ( const counter &c)
    {   mutex_write_read MRM ( mdc, c.mdc);
        //std::unique_lock<mutex_write_read> UL ( MRM);
        MRM.wait_no_readers() ;
        N = c.N;
        return *this ;
    };
    counter & operator = ( int c)
    {   mutex_write MRM ( mdc);
        //std::unique_lock<mutex_write> UL ( MRM);
        MRM.wait_no_readers() ;
        N = c;
        return *this ;
    };
    counter & operator = ( counter &&c)
    {   mutex_write_write MMM( mdc, c.mdc);
        //std::unique_lock<mutex_write_write> UL (MMM);
        MMM.wait_no_readers_first() ;
        MMM.wait_no_readers_second() ;
        N = c.N;
        c.N = -1;
        return *this ;
    };

    bool operator < ( const counter & c)const
    {   mutex_read_read MR ( mdc, c.mdc) ;
        //std::unique_lock <mutex_read_read> UL ( MR );
        return ( this->N < c.N) ;
    };
    bool operator > ( const counter & c)const
    {   mutex_read_read MR ( mdc, c.mdc) ;
        //std::unique_lock <mutex_read_read> UL ( MR );
        return ( this->N > c.N) ;
    };
};
counter Center( rand() >>NBITS) ;

counter C ;
std::atomic_uint N ;

void Funcion11 ( void)
{   //------------------------- begin ------------------------
    assert ( N.load() == 0);
    mutex_read MR (C.mdc);
    //std::unique_lock <mutex_read> UL ( MR);
    N++ ;assert ( N.load() == 1);
    std::chrono::seconds S ( 5 ) ;
    std::this_thread::sleep_for ( S);
    N++ ;assert ( N.load() == 4);

}

void Funcion12 ( void)
{   //------------------------- begin -------------------------
    std::chrono::seconds S ( 1 ) ;
    std::this_thread::sleep_for ( S);
    mutex_write MW (C.mdc);
    //std::unique_lock <mutex_write> UL ( MW);
    N++ ; assert ( N.load() == 2);
    S= std::chrono::seconds (3);
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 3);
    MW.wait_no_readers() ;
    N++ ; assert ( N.load() == 5);
    C.N = 5 ;
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 6);

}

void Funcion21 ( void)
{   //------------------------- begin ------------------------
    assert ( N.load() == 0);
    mutex_write MW (C.mdc);
    //std::unique_lock <mutex_write> UL ( MW);
    N++ ; assert ( N.load() == 1 );
    std::chrono::seconds S ( 3 ) ;
    std::this_thread::sleep_for ( S);

    N++ ; assert ( N.load() == 3 );
    MW.wait_no_readers() ;
    N++ ; assert ( N.load() == 4 );

    C.N = 10 ;
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 5 );

}
void Funcion22 ( void)
{   //------------------------- begin -------------------------
    std::chrono::seconds S ( 1 ) ;
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 2);
    mutex_write MW (C.mdc);
    //std::unique_lock <mutex_write> UL ( MW);
    N++ ; assert ( N.load() == 6 );
    S= std::chrono::seconds (3);
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 7 );
    MW.wait_no_readers() ;
    N++ ; assert ( N.load() == 8 );
    C.N = 5 ;
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 9 );
}
void Funcion31 ( void)
{   //------------------------- begin ------------------------
    assert ( N.load() == 0);
    mutex_read MR (C.mdc);
    //std::unique_lock <mutex_read> UL ( MR);
    N++ ; assert ( N.load() == 1 );
    std::chrono::seconds S ( 8 ) ;
    std::this_thread::sleep_for ( S);
    N++ ; assert ( N.load() == 9 );
    C.N = 10 ;

}
void Funcion32 ( void)
{   //------------------------- begin -------------------------
    std::chrono::seconds S1 ( 1 ) ;
    std::chrono::seconds S2 ( 2 ) ;

    std::this_thread::sleep_for ( S1);
    N++ ; assert ( N.load() == 2);
    mutex_write MW (C.mdc);
    //std::unique_lock <mutex_write> UL ( MW);
    std::this_thread::sleep_for ( S1);


    {   mutex_read MR(C.mdc);
        //std::unique_lock <mutex_read> UL2 ( MR);
        N++ ; assert ( N.load() == 3);
        std::this_thread::sleep_for ( S2);
    }
    N++ ; assert ( N.load() == 4);
    std::this_thread::sleep_for ( S1);
    N++ ; assert ( N.load() == 5);
    {   mutex_write MW2 (C.mdc);
        //std::unique_lock <mutex_write> UL2 ( MW2);
        N++ ; assert ( N.load() == 6);
        std::this_thread::sleep_for ( S2);
        N++ ; assert ( N.load() == 7);
        N++ ; assert ( N.load() == 8);
        MW2.wait_no_readers() ;
        N++ ; assert ( N.load() == 10);
        std::this_thread::sleep_for ( S2);
        N++ ; assert ( N.load() == 11);
    };
    MW.wait_no_readers() ;
    N++ ; assert ( N.load() == 12 );
    C.N = 5 ;
    std::this_thread::sleep_for ( S2);
    N++ ; assert ( N.load() == 13 );
}

void Prueba1 ( void)
{   //--------------------------------- begin ----------------------------------
    N.store(0) ;
    std::thread T1( Funcion11) ;
    std::thread T2( Funcion12) ;
    T1.join() ;
    T2.join();
    N++ ; assert ( N.load() == 7);
}
void Prueba2 ( void)
{   //--------------------------------- begin ----------------------------------
    N.store(0);
    std::thread T1( Funcion21) ;
    std::thread T2( Funcion22) ;
    T1.join() ;
    T2.join();
    N++ ; assert ( N.load() == 10);
}
void Prueba3 ( void)
{   //--------------------------------- begin ----------------------------------
    N.store(0);
    std::thread T1( Funcion31) ;
    std::thread T2( Funcion32) ;
    T1.join() ;
    T2.join();
    N++ ; assert ( N.load() == 14);
}

void Bingo()
{   //-------------------------------------------- begin-------------------------
    //std::thread::id tid  =std::this_thread::get_id();
    //std::cout<<"Bingo "<<tid<<std::endl;
    uint64_t NCasos =0 ;
    int N  =0 ;
    int C ( rand()>>NBITS);
    while ( N < 50)
    {   if ( Center.read() ==C )   N++ ;
        Center = C ;
        C = (rand()>>NBITS) ;
        NCasos ++;
    };
};

void Prueba4 ( void)
{   //--------------------------------- begin ----------------------------------
    std::thread T[4];
    for ( int i =0 ; i < 4 ; ++i)
        T[i] = std::thread ( Bingo);
    for ( int i = 0 ; i < 4 ; ++i)
        T[i].join() ;
};

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba3 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba4 ) );

    return 0;
}

