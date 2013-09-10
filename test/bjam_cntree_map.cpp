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
#include <boost/countertree/cntree_map.hpp>
#include <boost/countertree/cntree_multimap.hpp>
#include <iostream>


using namespace boost::unit_test;
namespace c_forest = countertree::forest ;
using namespace std ;
using namespace countertree ;

typedef std::pair<const int, double> PID ;
ostream & operator << ( ostream &salida, const PID &P);
ostream & operator <<( ostream & salida , const cntree_map<int,double> &M);
ostream & operator <<( ostream & salida , const cntree_multimap<int,double> &M);
void SinRepeticiones( void) ;
void ConRepeticiones ( void);

ostream & operator << ( ostream &salida, const PID &P)
{   //------------------- begin -----------------------
    salida<<"("<<P.first<<" , "<<P.second<<")  ";
    return salida ;
};
ostream & operator <<( ostream & salida , const cntree_map<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};
ostream & operator <<( ostream & salida , const cntree_multimap<int,double> &M)
{   //--------------------------- begin -------------------------
    salida<<"Numero de Nodos  "<<M.size()<<endl ;
    for ( int i = 0 ; i < M.size() ; ++i)
        salida<<M.pos(i) ;

    salida<<endl<<endl;
    return salida ;
};
void Prueba1 ( void)
{   //---------------------------- begin -------------------------

    typedef cntree_map <int,double,true> VInt ;
    VInt    V1, V2 ;
    unsigned code ;
    PID K ;

    for ( int i =0 ; i < 10 ; i++) V1.insert (PID( i,i)) ;
    V1.insert(PID(100,100));
    BOOST_CHECK ( V1.size() == 11);
    V2 = V1 ;
    //----------------------------------------------------------------------
    //     back
    //----------------------------------------------------------------------
    V1.pop_move_back( K);
    BOOST_CHECK ( V1.size() == 10 and K.first == 100);

    V1.pop_copy_back( K);
    BOOST_CHECK ( V1.size() == 9 and K.first == 9 );


    //-----------------------------------------------------------------------
    //    front
    //-----------------------------------------------------------------------
    V1 = V2 ;
    V1.pop_move_front( K);
    BOOST_CHECK ( V1.size() == 10 and K.first == 0);

    V1.pop_copy_front( K);
    BOOST_CHECK ( V1.size() == 9 and K.first == 1);
    //----------------------------------------------------------------------
    // if back
    //----------------------------------------------------------------------

    V1 = V2 ;
    auto M = [] ( const PID &A)->bool { return ( A.first ==100 );};
    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 0 and K.first == 100 and V1.size() == 10 );

    code = V1.pop_copy_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M2 = [] ( const PID &A)->bool { return ( A.first ==9 );};
    code = V1.pop_copy_back_if (K,M2);
    BOOST_CHECK (code == 0 and K.first == 9 and V1.size() ==9);

    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

    //----------------------------------------------------------------------
    // if front
    //----------------------------------------------------------------------
    V1 = V2 ;
    auto M3 = [] ( const PID &A)->bool { return ( A.first ==0 );};
    code = V1.pop_move_front_if (K,M3);
    BOOST_CHECK (code == 0 and K.first == 0 and V1.size() == 10 );

    code = V1.pop_copy_front_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M4 = [] ( const PID &A)->bool { return ( A.first ==1 );};
    code = V1.pop_copy_front_if (K,M4);
    BOOST_CHECK (code == 0 and K.first == 1 and V1.size() ==9);

    code = V1.pop_move_front_if (K,M4);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

};
void Prueba2 ( void)
{   //---------------------------- begin -------------------------

    typedef cntree_multimap <int,double,true> VInt ;
    VInt    V1, V2 ;
    unsigned code ;
    PID K ;

    for ( int i =0 ; i < 10 ; i++) V1.insert (PID( i,i)) ;
    V1.insert(PID(100,100));
    BOOST_CHECK ( V1.size() == 11);
    V2 = V1 ;
    //----------------------------------------------------------------------
    //     back
    //----------------------------------------------------------------------
    V1.pop_move_back( K);
    BOOST_CHECK ( V1.size() == 10 and K.first == 100);

    V1.pop_copy_back( K);
    BOOST_CHECK ( V1.size() == 9 and K.first == 9 );


    //-----------------------------------------------------------------------
    //    front
    //-----------------------------------------------------------------------
    V1 = V2 ;
    V1.pop_move_front( K);
    BOOST_CHECK ( V1.size() == 10 and K.first == 0);

    V1.pop_copy_front( K);
    BOOST_CHECK ( V1.size() == 9 and K.first == 1);
    //----------------------------------------------------------------------
    // if back
    //----------------------------------------------------------------------

    V1 = V2 ;
    auto M = [] ( const PID &A)->bool { return ( A.first ==100 );};
    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 0 and K.first == 100 and V1.size() == 10 );

    code = V1.pop_copy_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M2 = [] ( const PID &A)->bool { return ( A.first ==9 );};
    code = V1.pop_copy_back_if (K,M2);
    BOOST_CHECK (code == 0 and K.first == 9 and V1.size() ==9);

    code = V1.pop_move_back_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

    //----------------------------------------------------------------------
    // if front
    //----------------------------------------------------------------------
    V1 = V2 ;
    auto M3 = [] ( const PID &A)->bool { return ( A.first ==0 );};
    code = V1.pop_move_front_if (K,M3);
    BOOST_CHECK (code == 0 and K.first == 0 and V1.size() == 10 );

    code = V1.pop_copy_front_if (K,M);
    BOOST_CHECK (code == 2 and V1.size() ==10);

    auto M4 = [] ( const PID &A)->bool { return ( A.first ==1 );};
    code = V1.pop_copy_front_if (K,M4);
    BOOST_CHECK (code == 0 and K.first == 1 and V1.size() ==9);

    code = V1.pop_move_front_if (K,M4);
    BOOST_CHECK (code == 2 and V1.size() == 9 );

};
void SinRepeticiones ( void )
{   //---------------------------- begin ------------------------
    cntree_map<int, double> M1 ;
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
    cntree_map<int,double,true,std::less<int>, std::allocator<int> > MX (M1);
    BOOST_CHECK ( MX.size() == 5);
    MX.clear() ;
    MX = M1 ;
    BOOST_CHECK ( MX.size() == 5);
    cntree_map<int,double,false,std::less<int>, std::allocator<int> > MY (std::move( MX));;
    BOOST_CHECK ( MY.size() == 5 and MX.size() == 0);
    MX = std::move ( MY);
    BOOST_CHECK ( MY.size() == 0 and MX.size() == 5);
    //----------------------------------------------------------
    //
    //----------------------------------------------------------
    cntree_map<int, double> M4 ( std::move( M1)) ;
    BOOST_CHECK ( M4.size() == 5);
    BOOST_CHECK ( M4.pos(0 ) == A);
    BOOST_CHECK ( M4.pos(1 ) == PID ( 5, 4.8));
    BOOST_CHECK ( M4.pos(2 ) == C);
    BOOST_CHECK ( M4.pos(3 ) == PID ( 8 , 6.3));
    BOOST_CHECK ( M4.pos(4 ) == D);

    M1 = std::move ( M4);
    cntree_map <int,double> M2 ( M1 );
    BOOST_CHECK ( M2.size() == 5);
    for ( i = 0 ; i < M2.size() ; ++i)
        BOOST_CHECK ( M1.pos(i) == M2.pos(i));

    cntree_map<int,double>::iterator Alfa,Beta;

    for ( i = 0 ,Alfa = M1.begin() ; Alfa != M1.end() ; i++,Alfa ++)
        BOOST_CHECK ( (*Alfa) == M1.pos(i) );

    cntree_map<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
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
    cntree_multimap<int, double> M1 ;
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

    cntree_multimap<int, double> M4( std::move(M1)) ;
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

    cntree_map <int,double> M5 ;
    M5.insert( A) ;
    M5.insert( B) ;
    M5.insert( C) ;
    M5.insert( D) ;
    M5.insert( PID ( 3 , 7.3)) ;
    M5.insert( PID ( 5 , 8.4) );
    M5.insert ( C);
    M5.insert( D) ;
    cntree_multimap <int,double> M2 ( M5 );
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

    cntree_multimap <int,double,true,std::less<int>,std::allocator<int> > MMX ( M2);
    BOOST_CHECK ( MMX.size() == 8 );
    MMX.clear() ;
    MMX= M2 ;
    BOOST_CHECK ( MMX.size() == 8 );
    cntree_map <int,double,true,std::less<int>,std::allocator<int> > MX ( M1.begin(), M1.end());
    BOOST_CHECK (MX.size() == 4 )    ;
    cntree_multimap <int,double> MN ( MX);
    BOOST_CHECK ( MN.size() == 4 );

    //------------------- rvalues -------------------------------------
    cntree_multimap<int,double,true, std::less<int> ,std::allocator<void> > MMZ ( std::move(M2));
    BOOST_CHECK ( MMZ.size() == 8  and M2.size() == 0);
    M2 = std::move ( MMZ);
    BOOST_CHECK ( MMZ.size() == 0  and M2.size() == 8);

    cntree_multimap<int,double>::iterator Alfa,Beta;

    for ( i =0, Alfa = M1.begin() ; Alfa != M1.end() ; i++,Alfa ++)
        BOOST_CHECK (*Alfa == M1.pos(i) );

    cntree_multimap<int,double> M3 ( M1.begin() +1, M1.end() -1 ) ;
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
    cntree_map<int, double> M1;
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
    cntree_map<int,double>::iterator Gamma ;
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

    std::pair <cntree_map<int, double>::iterator, cntree_map<int, double>::iterator > PI ;
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
    cntree_multimap<int, double> M1;
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
    cntree_multimap<int, double>::iterator Gamma ;
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

    std::pair < cntree_multimap<int, double>::iterator, cntree_multimap<int,double>::iterator > PI ;
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

void SinRepeticiones_if()
{   //---------------------------- begin ------------------------
    //typedef std::pair<const int, double> value_t ;
    typedef  cntree_map<int, double,true>::iterator iterator ;
    typedef  cntree_map<int, double,true>::value_type value_t ;
    //typedef typename cntree_map<int, double,true>::const_iterator const_iterator ;
    //typedef typename cntree_map<int, double,true>::mypair    mypair ;

    cntree_map<int, double,true> M1,M2;

    //--------------------------- operator [ ] ------------------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1[i] == 0.0);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        M1[i] = ( double ) i ;
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1[i] == (double)i);
    M1.clear() ;

    //--------------------------- insert-------------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert ( PID ( i , i));
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert ( PID ( i , i));
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);
    M1.clear() ;

    //---------------------------------- insert_if ------------------------
    auto inserta_pares = [] ( const value_t & Alfa)->bool { return ( (Alfa.first & 1) == 0 ); };
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert_if ( inserta_pares, PID ( i , i));
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 );
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert_if ( inserta_pares, PID ( i , i));
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 );
    M1.clear();

    //-------------------- insert with rvalues ---------------------------
    M1.insert ( std::move( PID(100, 200)));
    BOOST_CHECK ( M1.front().first == 100 and M1.back().second == 200);
    M1.clear();

    //-------------------- insert_if with rvalues ---------------------------
    M1.insert_if (inserta_pares, std::move( PID(100, 200)));
    M1.insert_if (inserta_pares, std::move( PID(101, 201)));
    M1.insert_if (inserta_pares, std::move( PID(100, 200)));
    BOOST_CHECK ( M1.size() == 1)     ;
    BOOST_CHECK ( M1.front().first == 100 and M1.back().second == 200);
    M1.clear();

    //--------------------------- emplace -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);
    M1.clear();

    //--------------------------- emplace_if -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace_if (inserta_pares,  i ,(double) i);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 );
     M1.clear();

    //--------------------------- emplace_hint -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace_hint ( M1.begin(), i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);


    //-------------------------------- insert -----------------
    M2.insert ( M1.begin() , M1.end());
    BOOST_CHECK ( M2.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M2.pos(i).second == (double)i);
    M2.clear() ;

    //-------------------------------- insert_if -----------------
    M2.insert_if ( M1.begin() , M1.end(), inserta_pares);
    BOOST_CHECK ( M2.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M2.pos(i).first == i*2);
    M2.clear() ;
    M1.clear();

    //------------------- pop_front  pop_back ----------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 50 ; ++i)
    {   M1.pop_front() ;
        M1.pop_back() ;
    }
    BOOST_CHECK ( M1.size() == 0);
    M1.clear() ;

    //------------------------- erase ( const_iterator ) erase_if---------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase ( M1.begin() +50);
    BOOST_CHECK ( M1.pos(50).first ==51);
    //------- Borra los pares--------------------
    M1.erase_if ( M1.begin() + 21, inserta_pares);
    M1.erase_if ( M1.begin() + 20, inserta_pares);
    BOOST_CHECK ( M1.pos(20).first ==21);
    M1.clear() ;

    //------------------------- erase ( key)------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase ( 50);
    M1.erase (1000);
    BOOST_CHECK ( M1.pos(50).first == 51);
    M1.clear() ;
    //------------------------- erase_if ( key)------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_if ( 50, inserta_pares);
    M1.erase_if ( 51, inserta_pares);
    M1.erase_if (1000, inserta_pares);
    BOOST_CHECK ( M1.pos(50).first == 51);
    M1.clear() ;

    //----------------------- erase_pos --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_pos ( 50) ;
    BOOST_CHECK ( M1.pos(50).first == 51 );
    M1.emplace (50, 50 );
    M1.erase_pos_if ( 50, inserta_pares);
    M1.erase_pos_if ( 51, inserta_pares);
    BOOST_CHECK ( M1.pos(50).first == 51);
    M1.clear() ;

    //--------------------------- erase ranges -----------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase (M1.begin() , M1.begin() +50);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == 50 +i );
    M1.erase_pos ( 20, 30);
    for ( int i =0 ; i < 20 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == 50 +i );
    M1.clear() ;

    //--------------------- erase_if ranges --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_if (M1.begin() , M1.begin() +50, inserta_pares);
    BOOST_CHECK ( M1.size() == 75);
    M1.erase_pos_if ( 25 , 50, inserta_pares);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 +1 );
     M1.clear();

    //-----------------------------------------------------------------------
    //        MODIFICATIONS
    //-------------------------------------------------------------------------

    //--------------------------------- modify --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.modify ( M1.begin() +50 , 75.0);
    BOOST_CHECK ( M1.pos(50).second == 75.0 );

    auto suma10 = [] ( value_t & D)->void { D.second += 10 ; };
    M1.modify ( M1.begin() +50 , suma10);
    BOOST_CHECK ( M1.pos(50).second == 85.0 );

    M1.pos(50).second = 50.0 ;
    M1.modify ( 50 , 75.0);
    BOOST_CHECK ( M1.pos(50).second == 75.0 );
    M1.modify ( 50 , suma10);
    BOOST_CHECK ( M1.pos(50).second == 85.0 );

    M1.modify_pos ( 20, 30.0);
    BOOST_CHECK ( M1.pos(20).second == 30.0 );
    M1.modify_pos ( 20, suma10);
    BOOST_CHECK ( M1.pos(20).second == 40.0 );
    M1.clear() ;

    //----------------------------- modify ---------------------------------
    M1.insert_or_modify ( 100, 50);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 50.0) ;
    M1.insert_or_modify ( 100, 60);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 60.0) ;
    M1.clear() ;
    M1.insert_or_modify ( 100, 50 , suma10);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 50.0) ;
    M1.insert_or_modify ( 100, 50 , suma10);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 60.0) ;
    M1.clear() ;

    //----------------------------------------------------------------------
    auto nada = [] ( value_t & D)->void { };
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert_or_modify ( i , double (i),nada  );
    //std::cout<<M1<<std::endl;
    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == i );
    };

    auto incremento = [] ( PID & D)->void {D.second += 1.0; };
    for ( int i =0 ; i < 100 ; ++i)
       M1.modify ( i, incremento);
    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == (i+1) );
    };

    //std::cout<<M1<<std::endl;
    for ( iterator Alfa = M1.begin() ; Alfa != M1.end() ; ++Alfa)
       M1.modify ( Alfa  , double (Alfa->first));
    //std::cout<<M1<<std::endl;
    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == i );
    };

    auto condicion1 = [] (const  PID & H)->bool { return ((H.first & 1) == 0 );};
    //auto condicion1 = [] (const  PID & H)->bool { return true;};
    M2.insert_if ( M1.begin(), M1.end(),condicion1 );
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2 and M2.pos(i).second == i*2 );
    };

    M2 = M1 ;
    //std::cout<<M2<<std::endl;
    M2.erase_if (M2.begin(), M2.end(), condicion1);
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2+1 and M2.pos(i).second == i*2+1 );
    };

    M2 = M1 ;
    //std::cout<<M2<<std::endl;
    M2.erase_pos_if (0, 99, condicion1);
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2+1 and M2.pos(i).second == i*2+1 );
    };

};
void ConRepeticiones_if()
{   //---------------------------- begin ------------------------
    typedef std::pair<const int, double> value_t ;
    typedef typename cntree_multimap<int, double>::iterator iterator ;
    //typedef typename cntree_multimap<int, double>::const_iterator const_iterator ;

    cntree_multimap<int, double> M1,M2;


    //--------------------------- insert-------------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert ( PID ( i , i));
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert ( PID ( i , i));
    BOOST_CHECK ( M1.size() == 200);
    for ( int i =0 ; i < 200 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i >>1  );
    M1.clear() ;

    //---------------------------------- insert_if ------------------------
    auto inserta_pares = [] ( const value_t & Alfa)->bool { return ( (Alfa.first & 1) == 0 ); };
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert_if ( inserta_pares, PID ( i , i));
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 );
    for ( int i =0 ; i < 100 ; ++i)
        M1.insert_if ( inserta_pares, PID ( i , i));
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == (i& (~1) ) );
    M1.clear();

    //-------------------- insert with rvalues ---------------------------
    M1.insert ( std::move( PID(100, 200)));
    BOOST_CHECK ( M1.front().first == 100 and M1.back().second == 200);
    M1.clear();

    //-------------------- insert_if with rvalues ---------------------------
    M1.insert_if (inserta_pares, std::move( PID(100, 200)));
    M1.insert_if (inserta_pares, std::move( PID(101, 201)));
    M1.insert_if (inserta_pares, std::move( PID(100, 200)));
    BOOST_CHECK ( M1.size() == 2)     ;
    BOOST_CHECK ( M1.front().first == 100 and M1.back().second == 200);
    M1.clear();

    //--------------------------- emplace -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);
    M1.clear();

    //--------------------------- emplace_if -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace_if (inserta_pares,  i ,(double) i);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 );
     M1.clear();

    //--------------------------- emplace_hint -----------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace_hint ( M1.begin(), i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M1.pos(i).second == (double)i);


    //-------------------------------- insert -----------------
    M2.insert ( M1.begin() , M1.end() );
    BOOST_CHECK ( M2.size() == 100);
    for ( int i =0 ; i < 100 ; ++i)
        BOOST_CHECK ( M2.pos(i).second == (double)i);
    M2.clear() ;

    //-------------------------------- insert_if -----------------
    M2.insert_if ( M1.begin() , M1.end(), inserta_pares);
    BOOST_CHECK ( M2.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M2.pos(i).first == i*2);
    M2.clear() ;
    M1.clear();

    //------------------- pop_front  pop_back ----------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    BOOST_CHECK ( M1.size() == 100);
    for ( int i =0 ; i < 50 ; ++i)
    {   M1.pop_front() ;
        M1.pop_back() ;
    }
    BOOST_CHECK ( M1.size() == 0);
    M1.clear() ;

    //------------------------- erase ( const_iterator ) erase_if---------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase ( M1.begin() +50);
    BOOST_CHECK ( M1.pos(50).first ==51);
    //------- Borra los pares--------------------
    M1.erase_if ( M1.begin() + 21, inserta_pares);
    M1.erase_if ( M1.begin() + 20, inserta_pares);
    BOOST_CHECK ( M1.pos(20).first ==21);
    M1.clear() ;

    //------------------------- erase ( key)------------------------
    for ( int i =0 ; i < 100 ; ++i)
    {   M1.emplace (  i ,(double) i);
        M1.emplace (  i ,(double) i);
    };

    M1.erase ( 50);
    M1.erase (1000);
    BOOST_CHECK ( M1.pos(100).first == 51);
    BOOST_CHECK ( M1.pos(101).first == 51);
    M1.clear() ;
    //------------------------- erase_if ( key)------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_if ( 50, inserta_pares);
    M1.erase_if ( 51, inserta_pares);
    M1.erase_if (1000, inserta_pares);
    BOOST_CHECK ( M1.pos(50).first == 51);
    M1.clear() ;

    //----------------------- erase_pos --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_pos ( 50) ;
    BOOST_CHECK ( M1.pos(50).first == 51 );
    M1.emplace (50, 50 );
    M1.erase_pos_if ( 50, inserta_pares);
    M1.erase_pos_if ( 51, inserta_pares);
    BOOST_CHECK ( M1.pos(50).first == 51);
    M1.clear() ;

    //--------------------------- erase ranges -----------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase (M1.begin() , M1.begin() +50);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == 50 +i );
    M1.erase_pos ( 20, 30);
    for ( int i =0 ; i < 20 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == 50 +i );
    M1.clear() ;

    //--------------------- erase_if ranges --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
        M1.emplace (  i ,(double) i);
    M1.erase_if (M1.begin() , M1.begin() +50, inserta_pares);
    BOOST_CHECK ( M1.size() == 75);
    M1.erase_pos_if ( 25 , 50, inserta_pares);
    BOOST_CHECK ( M1.size() == 50);
    for ( int i =0 ; i < 50 ; ++i)
        BOOST_CHECK ( M1.pos(i).first == i*2 +1 );
     M1.clear();

    //-----------------------------------------------------------------------
    //        MODIFICATIONS
    //-------------------------------------------------------------------------

    //--------------------------------- modify --------------------------------
    for ( int i =0 ; i < 100 ; ++i)
    {   M1.emplace (  i ,(double) i);
        M1.emplace (  i ,(double) i);
    };

    M1.modify ( M1.begin() +50 , 75.0);
    BOOST_CHECK ( M1.pos(50).second == 75.0 );

    auto suma10 = [] ( value_t & D)->void { D.second += 10 ; };
    M1.modify ( M1.begin() +50 , suma10);
    BOOST_CHECK ( M1.pos(50).second == 85.0 );

    M1.pos(50).second = 50.0 ;
    M1.modify ( 50 , 75.0);
    BOOST_CHECK ( M1.pos(100).second == 75.0 );
    BOOST_CHECK ( M1.pos(101).second == 75.0 );
    M1.modify ( 50 , suma10);
    BOOST_CHECK ( M1.pos(100).second == 85.0 );
    BOOST_CHECK ( M1.pos(101).second == 85.0 );

    M1.modify_pos ( 20, 30.0);
    BOOST_CHECK ( M1.pos(20).second == 30.0 );
    M1.modify_pos ( 20, suma10);
    BOOST_CHECK ( M1.pos(20).second == 40.0 );
    M1.clear() ;

    //----------------------------- modify ---------------------------------
    M1.insert_or_modify ( 100, 50);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 50.0) ;
    M1.insert_or_modify ( 100, 60);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 60.0) ;
    M1.clear() ;
    M1.insert_or_modify ( 100, 50 , suma10);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 50.0) ;
    M1.insert_or_modify ( 100, 50 , suma10);
    BOOST_CHECK ( M1.pos(0).first == 100 and M1.pos(0).second == 60.0) ;
    M1.clear() ;

    //-----------------------------------------------------------------------------
    auto nada = [] ( value_t & D)->void { };
    for ( int i =0 ; i < 100 ; ++i)
    {   M1.insert_or_modify ( i , double (i), nada  );
    };
    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == i );
    };

    //std::cout<<M1<<std::endl;

    auto incremento = [] ( PID & D)->void {D.second += 1.0; };
    for ( int i =0 ; i < 100 ; ++i)
       M1.modify ( i, incremento);
    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == (i+1) );
    };

    //std::cout<<M1<<std::endl;
    for ( iterator Alfa = M1.begin() ; Alfa != M1.end() ; ++Alfa)
       M1.modify ( Alfa  , double (Alfa->first));
    //std::cout<<M1<<std::endl;

    for ( int i =0 ; i < 100 ; ++i)
    {   assert( M1.pos(i).first == i and M1.pos(i).second == i );
    };

    auto condicion1 = [] (const  PID & H)->bool { return ((H.first & 1) == 0 );};
    //auto condicion1 = [] (const  PID & H)->bool { return true;};
    M2.insert_if ( M1.begin(), M1.end(),condicion1 );
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2 and M2.pos(i).second == i*2 );
    };

    M2 = M1 ;
    //std::cout<<M2<<std::endl;
    M2.erase_if (M2.begin(), M2.end(), condicion1);
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2+1 and M2.pos(i).second == i*2+1 );
    };

    M2 = M1 ;
    //std::cout<<M2<<std::endl;
    M2.erase_pos_if (0, 99, condicion1);
    //std::cout<<M2<<std::endl;
    for ( int i =0 ; i < 50 ; ++i)
    {   assert( M2.pos(i).first == i*2+1 and M2.pos(i).second == i*2+1 );
    };
};



test_suite* init_unit_test_suite( int argc, char* argv[] )
{

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Prueba2 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticiones ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticiones ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticion2 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &SinRepeticiones_if ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &ConRepeticiones_if ) );
    return 0;
}
