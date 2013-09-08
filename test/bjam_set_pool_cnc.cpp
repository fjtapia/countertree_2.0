//----------------------------------------------------------------------------
/// @file test_set.cpp
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
#define __DEBUG_CNTREE 1
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/set.hpp>
#include <iostream>

#define NELEM   1000000
int V[NELEM];

using namespace boost::unit_test;
namespace cntree = countertree ;

cntree::set_pool_cnc <uint32_t> VTC ;
typedef cntree::set_pool_cnc <uint32_t>::iterator s_iterator ;
static const uint32_t HC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = ( HC > 8 ) ? 8 :HC ;
uint32_t Primo [ 10000] ;
uint32_t NPrimo ;


void prueba1()
{   //------------------ begin ---------------
    cntree::set_pool_cnc<int> s;
    int i ;
    cntree::set_pool_cnc<int>::iterator Alfa, Beta;
    s.insert(1);
    s.insert(3);
    s.insert(5);
    s.insert(7);
    s.insert(9);
    s.insert(11);
    s.insert(13);
    s.insert(15);

    for ( i = 1 , Alfa = s.begin();Alfa != s.end(); ++Alfa, i+=2)
        BOOST_CHECK ( *Alfa == i );
    //---------------------------------------------------------
    // Pruebas con rvalues
    //---------------------------------------------------------
    cntree::set_pool_cnc<int> s2( std::move (s));

    for ( i = 1 , Alfa = s2.begin();Alfa != s2.end(); ++Alfa, i+=2)
        BOOST_CHECK ( *Alfa == i );
    s = std::move(s2);
    s2= s ;
    cntree::set_pool_cnc<int>::reverse_iterator Delta ;

    for ( i = 15 , Delta = s.rbegin();Delta < (s.rend()); ++Delta, i-=2 )
        BOOST_CHECK ( *Delta == i );

    for (  i =1 ; i < 17 ; i+=2)
       BOOST_CHECK (s.find ( i) != s.end() ) ;
    s.erase( 3 );

    BOOST_CHECK ( s.pos(0) == 1);
    BOOST_CHECK ( s.pos(1) == 5);
    BOOST_CHECK ( s.pos(2) == 7);
    BOOST_CHECK ( s.pos(3) == 9);
    BOOST_CHECK ( s.pos(4) == 11);
    BOOST_CHECK ( s.pos(5) == 13);
    BOOST_CHECK ( s.pos(6) == 15);

    s.erase( s.begin() + 2 );
    s.erase( s.begin() + 2 , s.begin() + 5);
    BOOST_CHECK ( s.pos(0) == 1);
    BOOST_CHECK ( s.pos(1) == 5);
    BOOST_CHECK ( s.pos(2) == 15);

    cntree::multiset_pool_cnc<int> ms(s2);
    ms.clear();

    ms.insert(1);
    ms.insert(3);
    ms.insert(5);
    ms.insert(7);
    ms.insert(3);
    ms.insert(9);
    ms.insert(3);
    ms.insert(11);
    ms.insert(13);
    ms.insert(15);

    BOOST_CHECK ( ms.pos(0) == 1);
    BOOST_CHECK ( ms.pos(1) == 3);
    BOOST_CHECK ( ms.pos(2) == 3);
    BOOST_CHECK ( ms.pos(3) == 3);
    BOOST_CHECK ( ms.pos(4) == 5);
    BOOST_CHECK ( ms.pos(5) == 7);
    BOOST_CHECK ( ms.pos(6) == 9);
    BOOST_CHECK ( ms.pos(7) == 11);
    BOOST_CHECK ( ms.pos(8) == 13);
    BOOST_CHECK ( ms.pos(9) == 15);

    //-----------------------------------------------------
    // Pruebas con rvalues
    //-----------------------------------------------------
    cntree::multiset_pool_cnc<int> ms2(std::move (ms));
    BOOST_CHECK ( ms2.pos(0) == 1);
    BOOST_CHECK ( ms2.pos(1) == 3);
    BOOST_CHECK ( ms2.pos(2) == 3);
    BOOST_CHECK ( ms2.pos(3) == 3);
    BOOST_CHECK ( ms2.pos(4) == 5);
    BOOST_CHECK ( ms2.pos(5) == 7);
    BOOST_CHECK ( ms2.pos(6) == 9);
    BOOST_CHECK ( ms2.pos(7) == 11);
    BOOST_CHECK ( ms2.pos(8) == 13);
    BOOST_CHECK ( ms2.pos(9) == 15);

    ms = std::move( ms2);

    ms.erase( 3 );
    ms.erase( ms.begin() + 2 );
    ms.erase( ms.begin() + 2 , ms.begin() + 5);

    BOOST_CHECK ( ms.pos(0) == 1);
    BOOST_CHECK ( ms.pos(1) == 5);
    BOOST_CHECK ( ms.pos(2) == 15);
}
void SinRepeticiones ( void)
{   //------------------- begin -------------------------
    //int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    cntree::set_pool_cnc<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
        A.insert( V[i] );

    cntree::set_pool_cnc<int> B(A) ;
    BOOST_CHECK ( A.size() == B.size());
    cntree::set_pool_cnc<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    BOOST_CHECK ( C.size() == B.size() and A.size() != B.size());

    cntree::set_pool_cnc<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   BOOST_CHECK ( (*Alfa) == A.pos(i) );
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);

    for ( int i = 0 ; i < NELEM ; ++i)
    {   BOOST_CHECK ( A.find( V[i]) != A.end() );
    };

    BOOST_CHECK (  A.find( A.pos(0) -1) == A.end() );

    cntree::set_pool_cnc<int>::iterator Beta ;
    Alfa = A.lower_bound( *(A.begin() +10)-1 );
    Beta = A.upper_bound ( A.pos ( A.size() -10) +1);
    signed_type Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

    std::pair<cntree::set_pool_cnc<int>::iterator,cntree::set_pool_cnc<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    Dif = Gama.second - Gama.first ;
    for ( int32_t i = 0 ; i < Dif ; i++, Gama.first++);
    BOOST_CHECK ( Gama.first == Gama.second);

    Gama = A.equal_range( A.pos(10) );
    Dif = Gama.second - Gama.first ;
    for ( int32_t i = 0 ; i < Dif ; i++, Gama.first++);
    BOOST_CHECK ( Gama.first == Gama.second);

};

void ConRepeticiones ( void)
{   //-------------------- begin -------------------------
    //int V[NELEM];

    for ( int i = 0 ; i < NELEM ; i ++)
        V[i] =rand() ;

    cntree::multiset_pool_cnc<int> A ;
    for ( int i = 0 ; i< NELEM ; ++i)
    {   A.insert( V[i] );
        A.insert( V[i] );
        A.insert( V[i] );
    };

    cntree::multiset_pool_cnc<int> B(A) ;
    BOOST_CHECK  (A.size() == B.size() );
    cntree::multiset_pool_cnc<int> C ( B.begin() + 20 , B.end() -20);
    B = C ;
    BOOST_CHECK  (C.size() == B.size() and A.size() != B.size() );

    cntree::multiset_pool_cnc<int>::iterator Alfa = A.begin() ;
    for (int  i = 0 ; Alfa != A.end() ; ++Alfa, ++i )
    {   BOOST_CHECK ( (*Alfa) == A.pos(i) );;
    };
    B.clear();
    B.insert(C.begin()+10 , C.end() -10);

    for ( int i = 0 ; i < NELEM ; ++i)
    {   BOOST_CHECK (A.find( V[i]) != A.end() );
    };
    BOOST_CHECK (A.find( A.pos(0) -1) == A.end() );

    cntree::multiset_pool_cnc<int>::iterator Beta ;
    Alfa = A.lower_bound( *(A.begin() +10)-1 );
    Beta = A.upper_bound ( A.pos ( A.size() -10) +1);
    signed_type Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

    std::pair<cntree::multiset_pool_cnc<int>::iterator,
              cntree::multiset_pool_cnc<int>::iterator> Gama ;
    Gama = A.equal_range(*(A.begin() +10) -1);
    Dif = Beta - Alfa ;
    for ( int32_t i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );


    Gama = A.equal_range( A.pos(10) );
    Dif = Beta - Alfa ;
    for ( int i =0 ; i < Dif ; Alfa++,i++);
    BOOST_CHECK ( Alfa == Beta );

};
void SinRepeticion2 ( void)
{   //------------------ Variables----------------
    cntree::set_pool_cnc<int> M1;
    int i  ;

    for ( i = 1000 ; i < 3000 ; i+= 2)
    {   M1.insert ( i  );
        M1.insert ( i );
    };
    BOOST_CHECK ( M1.size() == 1000);

    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i) == (1000 + i*2) );
    };

    cntree::set_pool_cnc<int>::iterator Gamma ;
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK (  Gamma == M1.end() );
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK (Gamma != M1.end() and Gamma == M1.begin()  );

    Gamma = M1.find(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == ( M1.end()-1 ) );

    Gamma = M1.find(999);
    BOOST_CHECK (Gamma == M1.end()  );

    Gamma = M1.find(2999);
    BOOST_CHECK ( Gamma == M1.end());


    //---- lower_bound to all existing elements ----------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //--- lower_bound to non existing elements ---------------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) );
    };

    //-- lower_bound : first, last, less than first, greater than last ----
    Gamma = M1.lower_bound(1000);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == ( M1.end() -1 ) );

    Gamma = M1.lower_bound(999);
    BOOST_CHECK (Gamma == M1.begin() and Gamma != ( M1.begin() -1 )  );

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK (  Gamma == M1.end() );


    //------- loop for existing elements ------------------------------
    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2)) );
    };

    // --------- loop for non existing elements ---
    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (*Gamma)  == ( 1000 + i * 2)) );
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK ( (*Gamma) == 1002 );

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK ( Gamma == M1.end() );

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() );

    std::pair < cntree::set_pool_cnc<int>::iterator, cntree::set_pool_cnc<int>::iterator > PI ;

    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ( (PI.second.pos() - PI.first.pos() ) == 1 and PI.first.pos() == i );
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ( (PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i );
    };
};

void ConRepeticion2 ( void)
{   //---------------------- Variables----------------------------
    cntree::multiset_pool_cnc<int> M1;
    int i  ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert ( 1000+ i *2 );
        M1.insert ( 1000+ i *2 );
        M1.insert ( 1000+ i *2 );
    };
    BOOST_CHECK ( M1.size() == 3000);
    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i*3) == (1000 + i*2) and
                      M1.pos(i*3 +1) == (1000 + i*2) and
                      M1.pos(i*3 +2) == (1000 + i*2)  );
    };

    // -------- Loop for find existing elements -------------------
    cntree::multiset_pool_cnc<int>::iterator Gamma ;
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and  (*Gamma) == (1000+i*2) and
                    (*(Gamma++)) == (1000+i*2) and  (*(Gamma++)) == (1000+i*2) );
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK ( Gamma == M1.end() );
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin() );

    Gamma = M1.find(2998);
    BOOST_CHECK (Gamma != M1.end() and Gamma == (M1.end() -3)  );

    Gamma = M1.find(999);
    BOOST_CHECK ( Gamma == M1.end() );

    Gamma = M1.find(2999);
    BOOST_CHECK ( Gamma == M1.end() );

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
                    (*(Gamma++))==(1000+i*2) and (*(Gamma++))==(1000+i*2) );
    };

    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (*Gamma) == (1000+i*2) and
                     (*(Gamma++))==(1000+i*2) and (*(Gamma++))==(1000+i*2) );
    };

    Gamma = M1.lower_bound(1000);
    BOOST_CHECK ( Gamma == M1.begin() and Gamma == M1.begin() );

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK (Gamma != M1.end() and Gamma == (M1.end() -3)  );

    Gamma = M1.lower_bound(999);
    BOOST_CHECK ( Gamma == M1.begin()  );

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK ( Gamma == M1.end() );

    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( *(Gamma -1) == ( 1000 + i * 2)) );
    };

    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK (Gamma != M1.end() and ( (*Gamma) == ( 1000 + i * 2))  );
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK (  (*Gamma) == 1002 );

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK ( Gamma == M1.end( ));

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin() );

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() );

    std::pair < cntree::multiset_pool_cnc<int>::iterator, cntree::multiset_pool_cnc<int>::iterator > PI ;

    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ( (PI.second.pos() - PI.first.pos() ) == 3 and PI.first.pos() == i*3 );
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ( (PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i*3 );
    };

};
void Generation ( void)
{	//------------------ Definición de constantes------------
    Primo[0] = 2 ;
    Primo[1] = 3 ;
    Primo[2] = 5;
    Primo[3] = 7;
    Primo[4] = 11;
    Primo[5] = 13 ;
    NPrimo = 6 ;

    uint64_t Tope =2, Tope2 = 25;

    for ( uint32_t Num = 17 ; Num < 65536 ; Num+=2)
    {   bool EsPrimo = true ;
        if ( Num >= Tope2)
        {   Tope++ ;
            Tope2 = Primo[Tope ]* Primo[Tope];
        };
        for ( uint32_t k = 1 ; k < Tope and EsPrimo; ++k)
        {   if (  ( Num % Primo[k]) == 0 ) EsPrimo = false ;
        };
        if (EsPrimo) Primo [ NPrimo++] = Num;
    };

};
void Criba ( s_iterator  Alfa , uint32_t NElem)
{   //----------------------- begin--------------------
    //std::cout<<"Inicio ----->"<<std::this_thread::get_id()<<"  " ;
    //std::cout<<(*Alfa )<<" "<<NElem<<std::endl ;
    s_iterator Beta = Alfa;
    for ( uint32_t i =0 ; i < NElem ; ++i)
    {   Alfa = Beta ;
        Beta = Alfa +1 ;
        uint32_t N = *Alfa ;
        bool EsPrimo = true ;
        for (uint32_t k = 0 ; k < NPrimo and EsPrimo; ++k)
        {   if ( (N%Primo[k]) == 0) EsPrimo = false ;
        };
        if ( not EsPrimo) VTC.erase ( Alfa);
    };
    //std::cout<<"Fin -------->"<<std::this_thread::get_id()<<std::endl ;
};
void FilterPrime ( void)
{   //--------------------------------- begin ------------------
    Generation() ;
    //std::cout<<"Numeros Primos generados\n";
    //std::cout<<std::endl;

    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.insert ( rand() | 1 ) ;
    //std::cout<<"Numeros Cargados \n";
    //std::cout<<std::endl;

    //for (uint32_t i =0 ; i < NELEM ;++i)
    //    std::cout<<"["<<i<<"] "<<VTC[i]<<" ";
    //std::cout<<std::endl<<std::endl<<std::endl;

    const uint32_t Cupo = VTC.size() / NCores ;
    s_iterator Ini[8];
    uint32_t NE [8] ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   Ini[i] = VTC.begin() + ( i * Cupo);
        NE[i]=  ((i*Cupo)> NELEM)?(NELEM-(i-1)* Cupo):Cupo ;
    }

    std::thread  T [8] ;

    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i] = std::thread ( Criba, Ini[i], NE[i] ) ;
    };
    for (uint32_t i =0 ; i < NCores ; ++i)
    {   T[i].join();
    };

    //for ( uint32_t i  =0 ; i < VTC.size() ; ++i)
    //    std::cout<<VTC[i]<<"  ";
    //std::cout<<std::endl<<std::endl ;

};

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticiones ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticiones ) );
     framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &FilterPrime ) );

    return 0;
}
