//----------------------------------------------------------------------------
/// @file test_map.cpp
/// @brief Test program of the clases countertree::map and countertree::multimap
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#define __CNTREE_DEBUG 1
#include <boost/test/included/unit_test.hpp>
#include <boost/countertree/map.hpp>
#include <iostream>


using namespace boost::unit_test;
namespace cntree = countertree ;
using namespace std ;


#define NELEM 10000000

cntree::map_cnc <uint32_t,uint32_t> VTC ;
typedef cntree::map_cnc <uint32_t,uint32_t>::iterator myiterator ;

typedef std::pair<const uint32_t, uint32_t> mypair ;
static const uint32_t HC = std::thread::hardware_concurrency() ;
static const uint32_t NCores = (HC > 8 )?8:HC ;
uint32_t Primo [ 10000] ;
uint32_t NPrimo ;


typedef std::pair<const int, double> PID ;


ostream & operator << ( ostream &salida, const PID &P);
ostream & operator <<( ostream & salida , const cntree::map_cnc<int,double> &M);
ostream & operator <<( ostream & salida , const cntree::multimap_cnc<int,double> &M);
void SinRepeticiones( void) ;
void ConRepeticiones ( void);

ostream & operator << ( ostream &salida, const PID &P)
{   //------------------- begin -----------------------
    salida<<"("<<P.first<<" , "<<P.second<<")  ";
    return salida ;
};
ostream & operator <<( ostream & salida , const cntree::map_cnc<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};
ostream & operator <<( ostream & salida , const cntree::multimap_cnc<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};



void SinRepeticiones ( void )
{   //---------------------------- begin ------------------------
    cntree::map_cnc<int, double> M1 ;
    int i ;

    PID A ( 3 , 7.3), B ( 5 , 8.4), C (7, 9.4), D(9,0.7);
    M1.insert( A) ;
    M1.insert( B) ;
    M1.insert( C) ;
    M1[8]= 6.3;
    M1[5] = 4.8 ;
    M1.insert (D) ;
    BOOST_CHECK ( M1.size() == 5);
    BOOST_CHECK ( M1.pos(0 ) == A);
    BOOST_CHECK ( M1.pos(1 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M1.pos(2 ) == C);
    BOOST_CHECK ( M1.pos(3 ) == PID ( 8 , 6.3));
    BOOST_CHECK ( M1.pos(4 ) == D);
    //----------------------------------------------------------
    //
    //----------------------------------------------------------
    cntree::map_cnc<int, double> M4 ( std::move( M1)) ;
    BOOST_CHECK ( M4.size() == 5);
    BOOST_CHECK ( M4.pos(0 ) == A);
    BOOST_CHECK ( M4.pos(1 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M4.pos(2 ) == C);
    BOOST_CHECK ( M4.pos(3 ) == PID ( 8 , 6.3));
    BOOST_CHECK ( M4.pos(4 ) == D);

    M1 = std::move ( M4);
    cntree::map_cnc <int,double> M2 ( M1 );
    BOOST_CHECK ( M2.size() == 5);
    for ( i = 0 ; i < M2.size() ; ++i)
        BOOST_CHECK ( M1.pos(i) == M2.pos(i));

    cntree::map_cnc<int,double>::iterator Alfa,Beta;

    for ( i = 0 ,Alfa = M1.begin() ; Alfa != M1.end() ; i++,Alfa ++)
        BOOST_CHECK ( (*Alfa) == M1.pos(i) );

    cntree::map_cnc<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
    BOOST_CHECK ( M3.size() == 3 ) ;
    BOOST_CHECK ( M3.pos(0 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M3.pos(1 ) == C);
    BOOST_CHECK ( M3.pos(2 ) == PID ( 8 , 6.3));

    M2 = M3 ;
    BOOST_CHECK ( M2.size() == 3 ) ;
    BOOST_CHECK ( M2.pos(0 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M2.pos(1 ) == C);
    BOOST_CHECK ( M2.pos(2 ) == PID ( 8 , 6.3));

    M2 = M1 ;
    Alfa = M2.begin() +2 ;
    M2.erase ( Alfa);
    BOOST_CHECK ( M2.size() == 4);
    BOOST_CHECK ( M2.pos(0 ) == A);
    BOOST_CHECK ( M2.pos(1 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M2.pos(2 ) == PID ( 8 , 6.3));
    BOOST_CHECK ( M2.pos(3 ) == D);

    M2 = M1 ;
    M2.erase ( M2.begin() +1 , M2.end() -1);
    BOOST_CHECK ( M2.size() == 2);
    BOOST_CHECK ( M2.pos(0 ) == A);
    BOOST_CHECK ( M2.pos(1 ) == D);

    M2 = M1 ;
    M2.erase (8);
    BOOST_CHECK ( M2.size() == 4);
    BOOST_CHECK ( M2.pos(0 ) == A);
    BOOST_CHECK ( M2.pos(1 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M2.pos(2 ) == C);
    BOOST_CHECK ( M2.pos(3 ) == D);

    M2.swap ( M3 ) ;
    BOOST_CHECK ( M2.size() == 3 ) ;
    BOOST_CHECK ( M2.pos(0 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M2.pos(1 ) == C);
    BOOST_CHECK ( M2.pos(2 ) == PID ( 8 , 6.3));

    Alfa = M1.find( 5);
    BOOST_CHECK ( Alfa != M1.end() and *Alfa == PID ( 5, 4.8));
    Alfa = M1.lower_bound (4);
    Beta = M1.upper_bound (9);
    signed_type Dif = Beta - Alfa ;
    for (  i =0 ; i < Dif ; Alfa++,i++ );
    BOOST_CHECK ( Alfa == Beta );
};

void ConRepeticiones ( void )
{   //---------------------------- begin ------------------------
    cntree::multimap_cnc<int, double> M1 ;
    int i ;

    PID A ( 3 , 7.3), B ( 5 , 8.4), C (7, 9.4), D(9,0.7);
    M1.insert( A) ;
    M1.insert( B) ;
    M1.insert( C) ;
    M1.insert( D) ;
    M1.insert( PID ( 3 , 7.3)) ;
    M1.insert( PID ( 5 , 8.4) );
    M1.insert ( C);
    M1.insert( D) ;
    BOOST_CHECK ( M1.size() == 8 );
    BOOST_CHECK ( M1.pos (0) == A );
    BOOST_CHECK ( M1.pos (1) == A );
    BOOST_CHECK ( M1.pos (2) == B );
    BOOST_CHECK ( M1.pos (3) == B );
    BOOST_CHECK ( M1.pos (4) == C );
    BOOST_CHECK ( M1.pos (5) == C );
    BOOST_CHECK ( M1.pos (6) == D );
    BOOST_CHECK ( M1.pos (7) == D );

    cntree::multimap_cnc<int, double> M4( std::move(M1)) ;
    BOOST_CHECK ( M1.size() ==0 );
    BOOST_CHECK ( M4.size() == 8 );
    BOOST_CHECK ( M4.pos (0) == A );
    BOOST_CHECK ( M4.pos (1) == A );
    BOOST_CHECK ( M4.pos (2) == B );
    BOOST_CHECK ( M4.pos (3) == B );
    BOOST_CHECK ( M4.pos (4) == C );
    BOOST_CHECK ( M4.pos (5) == C );
    BOOST_CHECK ( M4.pos (6) == D );
    BOOST_CHECK ( M4.pos (7) == D );

    M1 = std::move ( M4);
    BOOST_CHECK ( M1.size() == 8 );
    BOOST_CHECK ( M1.pos (0) == A );
    BOOST_CHECK ( M1.pos (1) == A );
    BOOST_CHECK ( M1.pos (2) == B );
    BOOST_CHECK ( M1.pos (3) == B );
    BOOST_CHECK ( M1.pos (4) == C );
    BOOST_CHECK ( M1.pos (5) == C );
    BOOST_CHECK ( M1.pos (6) == D );
    BOOST_CHECK ( M1.pos (7) == D );

    cntree::map_cnc <int,double> M5 ;
    M5.insert( A) ;
    M5.insert( B) ;
    M5.insert( C) ;
    M5.insert( D) ;
    M5.insert( PID ( 3 , 7.3)) ;
    M5.insert( PID ( 5 , 8.4) );
    M5.insert ( C);
    M5.insert( D) ;
    cntree::multimap_cnc <int,double> M2 ( M5 );
    M2 = M1 ;
    //countertree::multimap <int,double> M2 ( M1 );
    BOOST_CHECK ( M2.size() == 8 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == A );
    BOOST_CHECK ( M2.pos (2) == B );
    BOOST_CHECK ( M2.pos (3) == B );
    BOOST_CHECK ( M2.pos (4) == C );
    BOOST_CHECK ( M2.pos (5) == C );
    BOOST_CHECK ( M2.pos (6) == D );
    BOOST_CHECK ( M2.pos (7) == D );


    cntree::multimap_cnc<int,double>::iterator Alfa,Beta;

    for ( i =0, Alfa = M1.begin() ; Alfa != M1.end() ; i++,Alfa ++)
        BOOST_CHECK (*Alfa == M1.pos(i) );

    cntree::multimap_cnc<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
    BOOST_CHECK ( M3.size() == 6 );
    BOOST_CHECK ( M3.pos (0) == A );
    BOOST_CHECK ( M3.pos (1) == B );
    BOOST_CHECK ( M3.pos (2) == B );
    BOOST_CHECK ( M3.pos (3) == C );
    BOOST_CHECK ( M3.pos (4) == C );
    BOOST_CHECK ( M3.pos (5) == D );

    M2 = M3 ;
    M2 = M1 ;
    Alfa = M2.begin() +2 ;
    M2.erase ( Alfa);
    BOOST_CHECK ( M2.size() == 7 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == A );
    BOOST_CHECK ( M2.pos (2) == B );
    BOOST_CHECK ( M2.pos (3) == C );
    BOOST_CHECK ( M2.pos (4) == C );
    BOOST_CHECK ( M2.pos (5) == D );
    BOOST_CHECK ( M2.pos (6) == D );


    M2 = M1 ;
    M2.erase ( M2.begin() +1 , M2.end() -1);
    BOOST_CHECK ( M2.size() == 2 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == D );

    M2 = M1 ;
    M2.erase (8);
    BOOST_CHECK ( M2.size() == 8 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == A );
    BOOST_CHECK ( M2.pos (2) == B );
    BOOST_CHECK ( M2.pos (3) == B );
    BOOST_CHECK ( M2.pos (4) == C );
    BOOST_CHECK ( M2.pos (5) == C );
    BOOST_CHECK ( M2.pos (6) == D );
    BOOST_CHECK ( M2.pos (7) == D );

    M2.erase (7);
    BOOST_CHECK ( M2.size() == 6 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == A );
    BOOST_CHECK ( M2.pos (2) == B );
    BOOST_CHECK ( M2.pos (3) == B );
    BOOST_CHECK ( M2.pos (4) == D );
    BOOST_CHECK ( M2.pos (5) == D );

    M2.swap ( M3 ) ;
    BOOST_CHECK ( M2.size() == 6 );
    BOOST_CHECK ( M2.pos (0) == A );
    BOOST_CHECK ( M2.pos (1) == B );
    BOOST_CHECK ( M2.pos (2) == B );
    BOOST_CHECK ( M2.pos (3) == C );
    BOOST_CHECK ( M2.pos (4) == C );
    BOOST_CHECK ( M2.pos (5) == D );

    Alfa = M1.find( 5);
    BOOST_CHECK ( Alfa->first == 5);

    Alfa = M1.lower_bound (4);
    Beta = M1.upper_bound (9);
    signed_type Dist  = Beta - Alfa ;
    for ( i = 0 ; i < Dist ; i++, Alfa++);
    BOOST_CHECK ( Alfa == Beta );
};
void SinRepeticion2 ( void)
{   //---------------------- Variables----------------------------
    cntree::map_cnc<int, double> M1;
    int i  ;
    for ( i = 1000 ; i < 3000 ; i+= 2)
    {   M1.insert (PID(i, rand())  );
        M1.insert (PID(i, rand())  );
    };

    //cout<<"Examen de contenidos ( operator[] ) : " ;
    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i).first == (1000 + i*2));
    };

    // -------- Loop for find existing elements -------------------
    cntree::map_cnc<int,double>::iterator Gamma ;
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (Gamma->first) == (1000+i*2))   ;
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK ( Gamma == M1.end() ) ;
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin())  ;

    Gamma = M1.find(2998);
    BOOST_CHECK  ( Gamma != M1.end() and Gamma == ( M1.end() - 1 )) ;

    Gamma = M1.find(999);
    BOOST_CHECK  ( Gamma == M1.end() ) ;

    Gamma = M1.find(2999);
    BOOST_CHECK  ( Gamma == M1.end() ) ;


    //---- lower_bound to all existing elements ----------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK  ( Gamma != M1.end() and (Gamma->first) == (1000+i*2)) ;
    };

    //--- lower_bound to non existing elements ---------------------------
    for ( i = 0 ; i < M1.size() ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK  ( Gamma != M1.end() and (Gamma->first) == (1000+i*2)) ;
    };

    //-- lower_bound : first, last, less than first, greater than last ----
    Gamma = M1.lower_bound(1000);
    BOOST_CHECK  ( Gamma == M1.begin() and Gamma != M1.end()) ;

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == ( M1.end() -1 )) ;

    Gamma = M1.lower_bound(999);
    BOOST_CHECK ( Gamma == M1.begin() or Gamma != M1.end());

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK ( Gamma == M1.end() ) ;

    //------- loop for existing elements ------------------------------
    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK (Gamma != M1.end() and ((Gamma-1)->first == (1000+i*2)));
    };

    // --------- loop for non existing elements ---
    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK (Gamma != M1.end() and ((Gamma->first)==(1000+i*2))) ;
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK ( (Gamma->first) == 1002) ;

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK  ( Gamma == M1.end() );

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin()) ;

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() );

    std::pair <cntree::map_cnc<int, double>::iterator,
               cntree::map_cnc<int, double>::iterator > PI ;
    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK  ((PI.second.pos() - PI.first.pos() ) == 1 and PI.first.pos() == i);
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK ((PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i);
    };
};

void ConRepeticion2 ( void)
{   //---------------------- Variables----------------------------
    cntree::multimap_cnc<int, double> M1;
    int i  ;

    for ( i = 0 ; i < 1000 ; i ++)
    {   M1.insert (PID( 1000+ i *2, rand() ) );
        M1.insert (PID( 1000+ i *2, rand() ) );
        M1.insert (PID( 1000+ i *2, rand() ) );
    };

    for ( i = 0 ; i < 1000 ; i ++ )
    {   BOOST_CHECK ( M1.pos(i*3).first == (1000 + i*2)    and
                      M1.pos(i*3 +1).first == (1000 + i*2) and
                      M1.pos(i* 3 +2).first == (1000 + i*2)   );
    };

    // -------- Loop for find existing elements -------------------
    cntree::multimap_cnc<int, double>::iterator Gamma ;
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (Gamma->first) == (1000+i*2) and
                    ((Gamma++)->first) == (1000+i*2) and ((Gamma++)->first)== (1000+i*2));
    };

    //--------- Loop for to find  non existing elements  ----------------
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.find( 1001+ i * 2);
        BOOST_CHECK ( Gamma == M1.end() ) ;
    };

    //----- find first, last, lower than first, greater than last --------
    Gamma = M1.find(1000);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == M1.begin());

    Gamma = M1.find(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == (M1.end() -3));

    Gamma = M1.find(999);
    BOOST_CHECK ( Gamma == M1.end() ) ;

    Gamma = M1.find(2999);
    BOOST_CHECK  ( Gamma == M1.end() ) ;

    //---- lower_bound to all existing elements ----------------------
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 1000+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (Gamma->first)== (1000+i*2) and
                    ((Gamma++)->first) == (1000+i*2) and ((Gamma++)->first) == (1000+i*2))  ;
    };

    //--- lower_bound to non existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; ++i)
    {   Gamma = M1.lower_bound( 999+ i * 2);
        BOOST_CHECK ( Gamma != M1.end() and (Gamma->first)== (1000+i*2) and
             ((Gamma++)->first) == (1000+i*2) and ((Gamma++)->first)== (1000+i*2));
    };

    //-- lower_bound : first, last, less than first, greater than last ----
    Gamma = M1.lower_bound(1000);
    BOOST_CHECK  ( Gamma == M1.begin() and Gamma != M1.end()) ;

    Gamma = M1.lower_bound(2998);
    BOOST_CHECK ( Gamma != M1.end() and Gamma == (M1.end() -3)) ;

    Gamma = M1.lower_bound(999);
    BOOST_CHECK ( Gamma == M1.begin() and  Gamma != M1.end()) ;

    Gamma = M1.lower_bound(2999);
    BOOST_CHECK  ( Gamma == M1.end() ) ;

    //------- loop for existing elements ------------------------------
    for ( i = 0 ; i  <999 ; ++i)
    {   Gamma = M1.upper_bound ( 1000 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (Gamma -1)->first == ( 1000 + i * 2))) ;
    };

    // --------- loop for non existing elements ---
    for ( i = 0 ; i  <1000 ; ++i)
    {   Gamma = M1.upper_bound ( 999 + i *2);
        BOOST_CHECK ( Gamma != M1.end() and ( (Gamma->first) == ( 1000 + i * 2)));
    };

    Gamma = M1.upper_bound ( 1000);
    BOOST_CHECK ( (Gamma->first) == 1002) ;

    Gamma = M1.upper_bound ( 2998);
    BOOST_CHECK  ( Gamma == M1.end() );

    Gamma = M1.upper_bound ( 999);
    BOOST_CHECK ( Gamma == M1.begin()) ;

    Gamma = M1.upper_bound ( 3000);
    BOOST_CHECK ( Gamma == M1.end() ) ;

    std::pair < cntree::multimap_cnc<int, double>::iterator,
                cntree::multimap_cnc<int,double>::iterator > PI ;
    //--------------- loop for existing elements ---------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(1000 + i *2 );
        BOOST_CHECK ((PI.second.pos() - PI.first.pos() ) == 3 and PI.first.pos() == i*3) ;
    };

    //------------- loop for non existing elements -------------------------
    for ( i = 0 ; i < 1000 ; i ++ )
    {   PI = M1.equal_range(999 + i *2 );
        BOOST_CHECK  ((PI.second.pos() == PI.first.pos() ) and PI.first.pos() == i*3);
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
void Criba ( myiterator  Alfa , uint32_t NElem)
{   //----------------------- begin--------------------
    //std::cout<<"Inicio ----->"<<std::this_thread::get_id()<<"  " ;
    //std::cout<<(*Alfa )<<" "<<NElem<<std::endl ;
    myiterator Beta = Alfa;
    for ( uint32_t i =0 ; i < NElem ; ++i)
    {   Alfa = Beta ;
        Beta = Alfa +1 ;
        uint32_t N = Alfa->second; ;
        bool EsPrimo = true ;
        for (uint32_t k = 0 ; k < NPrimo and EsPrimo; ++k)
        {   if ( (N%Primo[k]) == 0) EsPrimo = false ;
        };
        if ( not EsPrimo) VTC.erase ( Alfa);
    };
    //std::cout<<"Fin -------->"<<std::this_thread::get_id()<<std::endl ;
};
void FilterPrime( void)
{   //--------------------------------- begin ------------------
    Generation() ;
    //std::cout<<"Numeros Primos generados\n";
    //std::cout<<std::endl;

    for (uint32_t i =0 ; i < NELEM ;++i)
        VTC.insert (mypair ( i, rand() | 1 )) ;
    //std::cout<<"Numeros Cargados \n";
    //std::cout<<std::endl;

    //for (uint32_t i =0 ; i < NELEM ;++i)
    //    std::cout<<"["<<i<<"] "<<VTC[i]<<" ";
    //std::cout<<std::endl<<std::endl<<std::endl;

    const uint32_t Cupo = VTC.size() / NCores ;
    myiterator Ini[8];
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
