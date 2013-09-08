//----------------------------------------------------------------------------
/// @file bjam_node.cpp
/// @brief Test program of the class node
///
/// @author Copyright (c) 2010 2012 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#define  __DEBUG_CNTREE 1
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <boost/countertree/forest/node.hpp>

using namespace boost::unit_test;
using namespace std ;
using namespace countertree::forest;

void prueba_nodo_01( void);
void prueba_nodo_02 ( void );
void  prueba_nodo_03 ( void);
test_suite* init_unit_test_suite( int argc, char* argv[] );

void prueba_nodo_01( void )
{
    //-----------------------------------------------------------------------
    // Constructors
    //-----------------------------------------------------------------------
    node<int> N1(3) ,N2(5),N3,N4;
    N3 = N1 ;
    BOOST_CHECK ( N1.data == 3 );
    BOOST_CHECK ( N2.data == 5 );
    BOOST_CHECK ( N1.data == N3.data );

	N3.data = 7;
    BOOST_CHECK ( N3.data == 7 );
	N2.color = red ;
	BOOST_CHECK ( N1.color  == black);
	BOOST_CHECK ( N2.color == red);

	BOOST_CHECK ( N4.color == black);
	BOOST_CHECK ( N4.N == 1);
	BOOST_CHECK ( N4.data == 0);
    N4 = N1 ;
    BOOST_CHECK ( N4.N == N1.N);
    BOOST_CHECK ( N4.color == N1.color);

	N2.color = black ;
	BOOST_CHECK ( N2.color == black);

	node<int> *p1( &N1), *p3(&N3) ;
	BOOST_CHECK (p1->data == N1.data );
	BOOST_CHECK (p3->data == N3.data);

	const node<int> *cp1( & N1 ) , *cp3 ( & N3) ;
	BOOST_CHECK (cp1->data == p1->data );
	BOOST_CHECK (cp3->data == p3->data);

    node<int> *Alfa = cp1->remove_const();
    Alfa->N = 3 ;
    BOOST_CHECK (N1.N == 3 );

    N1.up = NULL ;
	N1.right = &N2 ;
	N2.up = &N1 ;
	N2.left = &N3 ;
	N3.up = & N2 ;
	N1.N = 3 ;
	N2.N = 2 ;
	BOOST_CHECK( N2.up->right == &N2);
	BOOST_CHECK( N3.up->left == &N3);
	BOOST_CHECK	( node<int>::upgrade(N3.up)->data == N2.data);
	BOOST_CHECK ( node<int>::upgrade(N2.up)->data == N1.data);

	p1 = node<int>::upgrade(N3.previous() );
	BOOST_CHECK ( p1->data == N1.data);
	p1 = node<int>::upgrade(p1->next()) ;
	BOOST_CHECK ( p1->data == N3.data);

	p1 = node<int>::upgrade(N1.shift(2)) ;
	BOOST_CHECK ( p1->data == N2.data);
	p1 = node<int>::upgrade(p1->shift ( -2)) ;
	BOOST_CHECK ( p1->data == N1.data);

	node <int> N[15] ;
	node<int>  *Padre = NULL ;
    for ( uint32_t i = 0 ; i < 15 ; i ++ )
    {   N[i].init() ;
        N[i].data = i ;
    };


    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;
    Padre = &N[2] ;
    N[2].N= 5 ;
    N[2].left = &N[1] ;
    N[1].up  = &N[2] ;
    N[2].right = &N[4] ;
    N[4].up  = &N[2] ;

    N[1].N = 2 ;
    N[1].left = &N[0] ;
    N[0].up  = &N[1] ;
    N[4].N = 2 ;
    N[4].left = &N[3] ;
    N[3].up  = &N[4] ;

    N[0].color = red;
    N[1].color = black ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;

    BOOST_CHECK (Colombo ( NULL , Padre , 2 , true, cout)) ;
    base_node::swap_contiguous_left( (base_node ** )&Padre);
    BOOST_CHECK (Colombo ( NULL , Padre , 2 , true,cout));

    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;
    Padre = &N[3] ;
    N[3].color = black ;
    N[3].N= 5 ;
    N[3].left = &N[1] ;
    N[1].up  = &N[3] ;
    N[3].right = &N[4] ;
    N[4].up  = &N[3] ;

    N[1].color = red ;
    N[1].N = 3 ;
    N[1].left = &N[0] ;
    N[0].up  = &N[1] ;
    N[1].right = &N[2] ;
    N[2].up  = &N[1] ;
    N[0].color  = black;
    N[2].color  = black ;
    N[4].color  = black ;

    base_node ** PPup = (base_node**) &Padre ;
    base_node** PPInf =  &(N[1].right) ;
    BOOST_CHECK ( Colombo ( NULL , Padre , 2 , true,cout));

    base_node::swap_node(PPup, PPInf);
    BOOST_CHECK (Colombo ( NULL , Padre , 2 , true,cout));

}


void prueba_nodo_02 ( void )
{   //------------------------ Inicio ----------------------------------
	node <int> N[15] ;
	node<int>  *Father = NULL ;
    int32_t i ;

    for ( i = 0 ; i < 15 ; i ++ )
    {   N[i].init() ;
        N[i].data = i ;
        BOOST_CHECK ( N[i].data == i);
    };

    Father = &N[5] ;
    N[5].up = NULL ;
    N[5].N = 9 ;
    N[5].color  = black;

    N[5].left = &N[3] ;
    N[3].up = &N[5] ;
    N[3].N = 5 ;
    N[3].color = red;

    N[3].left = &N[1] ;
    N[1].up = &N[3] ;
    N[1].N = 3 ;
    N[1].color  = black;

    N[1].left = & N[0] ;
    N[0].up = &N[1] ;
    N[0].N = 1 ;
    N[0].color = red;

    N[1].right= & N[2] ;
    N[2].up = &N[1] ;
    N[2].N = 1 ;
    N[2].color = red ;

    N[3].right = &N[4] ;
    N[4].up = &N[3] ;
    N[4].N = 1 ;
    N[4].color  = black;

    N[5].right = &N[7] ;
    N[7].up = & N[5] ;
    N[7].N = 3 ;
    N[7].color  = black ;

    N[7].left = &N[6] ;
    N[6].up = &N[7] ;
    N[6].N = 1 ;
    N[6].color = red;

    N[7].right = & N[8] ;
    N[8].up = &N[7] ;
    N[8].N = 1 ;
    N[8].color = red;

    BOOST_CHECK ( N[5].color == black);
    BOOST_CHECK ( N[6].color == red);
    BOOST_CHECK (N[5].n_left()  == 5 );
    BOOST_CHECK (N[5].n_right()  == 3 );
    BOOST_CHECK (node<int>::nd(N[5].left) == 5 );
    BOOST_CHECK (node<int>::nd (N[5].right) == 3 ) ;

    BOOST_CHECK( Colombo( NULL,Father,2,false,cout));


    node<int> *Alfa;

    for ( i = 0,Alfa = &N[0] ; Alfa != NULL; Alfa = node<int>::upgrade( Alfa->next()), i++)
    {   BOOST_CHECK (Alfa->data == i);
        BOOST_CHECK ( Alfa->get_pos() == i);
    };
    for ( i =0,Alfa=&N[0];Alfa != NULL; i+= 2,Alfa = node<int>::upgrade(Alfa->shift(2)) )
    {   BOOST_CHECK (Alfa->data == i);
    };

    for ( i = 8, Alfa = &N[8] ; Alfa != NULL ;i--,Alfa = node<int>::upgrade( Alfa->previous() ) )
    {   BOOST_CHECK (Alfa->data == i);
    };

    for ( i = 8 ,Alfa = &N[8] ; Alfa != NULL ;i-=2,Alfa = node<int>::upgrade( Alfa->shift(-2) ) )
    {   BOOST_CHECK (Alfa->data == i);
    };
    Alfa = &N[0] ;

    BOOST_CHECK ( (Alfa =node<int>::upgrade(Alfa->shift(6)))->data == 6     );
    BOOST_CHECK ( ( Alfa = node<int>::upgrade(Alfa->shift(-2)) )->data == 4);
    BOOST_CHECK (Alfa->get_pos() == 4);


    node<int> *Beta;
    for ( i =0 ,Beta = &N[0] ; Beta != NULL; i++,Beta =node<int>::upgrade (Beta->next()) )
    {   BOOST_CHECK ( Beta->data == i);
    };

    for (i =0, Beta=&N[0];Beta != NULL; i+=2, Beta = node<int>::upgrade( Beta->shift(2)))
    {   BOOST_CHECK ( Beta->data == i);
    };

    for ( i = 8, Beta = &N[8] ; Beta != NULL ;i--,Beta = node<int>::upgrade(Beta->previous() ))
    {   BOOST_CHECK ( Beta->data == i);
    };

    for ( i = 8 ,Beta = &N[8] ; Beta != NULL ;i-= 2, Beta = node<int>::upgrade(Beta->shift(-2) ))
    {   BOOST_CHECK ( Beta->data == i);
    };
    Beta = &N[0] ;
    BOOST_CHECK ( (Beta =node<int>::upgrade(Beta->shift(6)) )->data == 6     );
    BOOST_CHECK ( ( Beta = node<int>::upgrade( Beta->shift(-2)) )->data == 4);
    BOOST_CHECK (Beta->get_pos() == 4);

}


void  prueba_nodo_03 ( void)
{   //------------------------- Inicio ----------------------------------
    node <int> N[15] ;
	base_node  *Padre = NULL ;

    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].data = i ;

    //----------------------------------------------------------
    //   RotateLeftAligned and RotateRightAligned with 2 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[1] ;
    N[1].color  = black;
    N[1].N = 5 ;

    N[1].left = &N[0] ;
    N[0].up = &N[1] ;
    N[0].color  = black ;
    N[0].N = 1 ;

    N[1].right = &N[3] ;
    N[3].up = &N[1] ;
    N[3].color = red ;
    N[3].N = 3 ;

    N[3].left = &N[2] ;
    N[2].up =&N[3] ;
    N[2].color  = black ;
    N[2].N = 1 ;

    N[3].right = &N[4] ;
    N[4].up = &N[3] ;
    N[4].color  = black ;
    N[4].N = 1 ;

    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true, cout));
    base_node::rotate_left_aligned(  & Padre );

    N[3].color  = black;
    N[1].color = red ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true,cout));
    N[1].color  = black;
    N[3].color = red ;

    base_node::rotate_right_aligned(& Padre ) ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true,cout));


    //----------------------------------------------------------
    //   RotateLeftAligned with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )   N[i].init() ;
    Padre = &N[1] ;
    N[1].color  = black;
    N[1].N = 7 ;

    N[1].left = &N[0] ;
    N[0].up = &N[1] ;
    N[0].color  = black ;
    N[0].N = 1 ;

    N[1].right = &N[3] ;
    N[3].up = &N[1] ;
    N[3].color = red ;
    N[3].N = 5 ;

    N[3].left = &N[2] ;
    N[2].up =&N[3] ;
    N[2].color  = black ;
    N[2].N = 1 ;

    N[3].right = &N[5] ;
    N[5].up = &N[3] ;
    N[5].color  = black ;
    N[5].N = 3 ;

    N[5].left = &N[4] ;
    N[4].up = &N[5] ;
    N[4].color = red;
    N[4].N = 1 ;

    N[5].right = & N[6] ;
    N[6].up = &N[5] ;
    N[6].color = red;
    N[6].N = 1 ;

    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));
    base_node::rotate_left_aligned( &Padre) ;
    N[3].color  = black;
    N[0].color = red;
    N[2].color = red ;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));
    N[3].color = red;
    N[0].color  = black;
    N[2].color  = black ;

    base_node::rotate_right_aligned( &Padre) ;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));


    //-----------------------------------------------------------
    //  RotateRightAligned with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )  N[i].init() ;

    Padre = &N[5] ;
    N[5].color  = black;
    N[5].N = 7 ;

    N[5].left = &N[3] ;
    N[3].up = &N[5] ;
    N[3].color = red ;
    N[3].N = 5 ;

    N[5].right = &N[6] ;
    N[6].up = &N[5] ;
    N[6].color  = black;
    N[6].N = 1 ;

    N[3].left = &N[1] ;
    N[1].up = &N[3] ;
    N[1].color  = black ;
    N[1].N = 3 ;

    N[3].right = &N[4] ;
    N[4].up = &N[3] ;
    N[4].color  = black;
    N[4].N = 1 ;

    N[1].left = &N[0] ;
    N[0].up = &N[1] ;
    N[0].color = red ;
    N[0].N = 1 ;

    N[1].right = &N[2] ;
    N[2].up = &N[1] ;
    N[2].color = red ;
    N[2].N = 1 ;

    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));

    base_node::rotate_right_aligned(&Padre) ;
    N[3].color  = black;
    N[4].color = red;
    N[6].color = red;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));
    N[3].color = red;
    N[4].color  = black;
    N[6].color  = black;

    base_node::rotate_left_aligned(&Padre) ;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));

    //-----------------------------------------------------------
    //   RotateLeftNotAligned with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[1] ;
    N[1].color  = black;
    N[1].N = 7 ;

    N[1].left = &N[0] ;
    N[0].up = &N[1] ;
    N[0].color  = black ;
    N[0].N = 1 ;

    N[1].right = &N[5] ;
    N[5].up = &N[1] ;
    N[5].color = red ;
    N[5].N = 5 ;

    N[5].left = &N[3] ;
    N[3].up = &N[5] ;
    N[3].color  = black ;
    N[3].N = 3 ;

    N[3].left = &N[2] ;
    N[2].up =&N[3] ;
    N[2].color = red ;
    N[2].N = 1 ;

    N[3].right = &N[4] ;
    N[4].up = &N[3] ;
    N[4].color = red;
    N[4].N = 1 ;

    N[5].right = & N[6] ;
    N[6].up = &N[5] ;
    N[6].color  = black;
    N[6].N = 1 ;

    BOOST_CHECK ( Colombo( NULL, Padre, 2 , true,cout));
    base_node::rotate_left_not_aligned(&Padre) ;
    N[4].color  = black;
    N[0].color = red ;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));


    //----------------------------------------------------------
    //  RotateRightNotAligned with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )  N[i].init() ;

    Padre = &N[5] ;
    N[5].color  = black;
    N[5].N = 7 ;

    N[5].left = &N[1] ;
    N[1].up = &N[5] ;
    N[1].color = red ;
    N[1].N = 5 ;

    N[5].right = &N[6] ;
    N[6].up = &N[5] ;
    N[6].color  = black;
    N[6].N = 1 ;

    N[1].left = &N[0] ;
    N[0].up = &N[1] ;
    N[0].color  = black ;
    N[0].N = 1 ;

    N[1].right = &N[3] ;
    N[3].up = &N[1] ;
    N[3].color = red ;
    N[3].N = 3 ;

    N[3].right = &N[4] ;
    N[4].up = &N[3] ;
    N[4].color  = black;
    N[4].N = 1 ;

    N[3].left = &N[2] ;
    N[2].up = &N[3] ;
    N[2].color  = black ;
    N[2].N = 1 ;

    base_node::rotate_right_not_aligned(&Padre) ;
    BOOST_CHECK ( Colombo ( NULL, Padre, 2 , true,cout));
}

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba_nodo_01 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba_nodo_02 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba_nodo_03 ) );

    return 0;
}
