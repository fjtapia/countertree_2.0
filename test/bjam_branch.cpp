//----------------------------------------------------------------------------
/// @file test_branch.cpp
/// @brief Test program of the class branch
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
#include <boost/countertree/forest/branch.hpp>


using namespace boost::unit_test;
using namespace std ;
using namespace countertree::forest;


typedef       base_node *    pnode         ;
typedef const base_node      const_pnode   ;
typedef       base_node **   address_pnode ;
typedef       base_node &    refnode       ;
typedef const base_node      const_refnode ;
//-----------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------
void prueba1 ( void);
void Rotacion ( void );
void Galleta ( void );
void GalletaInversa ( void );
void galletainversa02 ( void);
test_suite* init_unit_test_suite( int argc, char* argv[] );


void prueba1 ( void)
{   //------------------------ Inicio ----------------------------------
    base_node  N[20] ;
	base_node * PAux = NULL;

	//Insertion of 3 nodes in V inverted ( 1, 0 ,2)----------------->
	base_node *Padre1 = &N[0] ;
	N[0].N = 2 ;
	N[0].color  = black;
	branch  H1( &Padre1)  ;
	BOOST_CHECK ( Colombo ( NULL, Padre1, 1 , true, cout));
	H1.insert_node ( &N[1], 0 ) ;
	N[0].N = 3 ;
	H1.insert_node ( &N[2] ,1) ;
	BOOST_CHECK ( H1.n_nodes() == 3);
	BOOST_CHECK ( *(H1.pointer_Cod(0)) == &N[1]);
	BOOST_CHECK ( *(H1.pointer_Cod(1)) == &N[2]);
	BOOST_CHECK ( H1.pointer_father( &N[2] ) == &(N[0].right)   );

	BOOST_CHECK ( Colombo ( NULL, Padre1, 1 , true, cout));
	BOOST_CHECK ( Padre1 == &N[0]);
	BOOST_CHECK ( Padre1->left == &N[1]);
	BOOST_CHECK ( Padre1->right == &N[2]);


	//Insertion of 3 nodes left aligned ( 5 , 4 , 3)---------------->
	base_node *Padre2 = &N[3] ;
	branch H2(& Padre2)  ;
	N[3].N = 2 ;
	N[3].color  = black ;
	H2.insert_node ( &N[4], 0 ) ;
	BOOST_CHECK ( Colombo ( NULL, Padre2, 1 , true, cout));
	N[3].N = 3 ;
	N[4].N = 2 ;
	H2.insert_node ( &N[5] ,2) ;

	BOOST_CHECK ( Colombo ( NULL, Padre2, 1 , true, cout));
	BOOST_CHECK ( Padre2 == &N[4]);
	BOOST_CHECK ( Padre2->left == &N [5]);
	BOOST_CHECK ( Padre2->right == &N[3]);


	//Insertion of 3 nodes right aligned (6,7,8)---------------->
	base_node *Padre3 = &N[6] ;
	branch H3( &Padre3)  ;
	N[6].N = 2;
	N[6].color  = black ;
	H3.insert_node ( &N[7], 1 ) ;
	BOOST_CHECK ( Colombo ( NULL, Padre3, 1 , true, cout));
	N[6].N = 3;
	N[7].N = 2 ;
	H3.insert_node ( &N[8] ,5) ;
	BOOST_CHECK ( Colombo ( NULL, Padre3, 1 , true, cout));
	BOOST_CHECK ( Padre3 ==&N[ 7]);
	BOOST_CHECK ( Padre3->left == &N[6]);
	BOOST_CHECK ( Padre3->right == &N[8]);


    //Insertion of 3 nodes not aligned to the left( 10 ,11, 9 )---------------->
	base_node *Padre4 = &N[9] ;
	branch H4( &Padre4)  ;
	N[9].N = 2 ;
	H4.insert_node ( &N[10], 0 ) ;
	BOOST_CHECK ( Colombo ( NULL, Padre4, 1 , true, cout));
	N[10].N = 2 ;
	N[9].N = 3 ;
	H4.insert_node ( &N[11] ,3) ;
	BOOST_CHECK ( Colombo ( NULL, Padre4, 1 , true, cout));
	BOOST_CHECK ( Padre4 == &N[11]);
	BOOST_CHECK ( Padre4->left == &N[10]);
	BOOST_CHECK ( Padre4->right == &N[9]);


	//Insertion of 3 nodes not aligned to the right (12, 14 , 13 )---------------->
	base_node *Padre5 = &N[12] ;
	branch  H5( &Padre5)  ;
	N[12].N = 2 ;
	H5.insert_node ( &N[13], 1 ) ;
	BOOST_CHECK ( Colombo ( NULL, Padre5, 1 , true, cout));
	N[12].N = 3 ;
	N[13].N = 2 ;
	H5.insert_node ( &N[14] ,4) ;
	BOOST_CHECK ( Colombo ( NULL, Padre5, 1 , true, cout));
	BOOST_CHECK ( Padre5 == &N[14]);
	BOOST_CHECK ( Padre5->left == &N[12]);
	BOOST_CHECK ( Padre5->right == &N[13]);


	//Insertion of 4 nodes (15,1,0,2)-------------------------->
	N[0].N++ ;
	N[1].N++ ;
	H1.insert_node( &N[15] ,2 ) ;
	BOOST_CHECK ( Padre1 == &N[0]);
	BOOST_CHECK ( Padre1->left == &N[1]);
	BOOST_CHECK ( Padre1->right == &N[2]);
	BOOST_CHECK ( Padre1->left->left == &N[15]);

	//Insertion of 4 nodes (5,16,4,3)-------------------------->
	N[4].N++ ;
	N[5].N++ ;
	H2.insert_node( &N[16] ,3 ) ;
	BOOST_CHECK ( Padre2 == &N[4]);
	BOOST_CHECK ( Padre2->left == &N[16]);
	BOOST_CHECK ( Padre2->left->left == &N[5]);
	BOOST_CHECK ( Padre2->right == &N[3]);

	//Insertion of 4 nodes (6,7,17,8)-------------------------->
	N[7].N++ ;
	N[8].N++ ;
	H3.insert_node( &N[17] ,4 ) ;
	BOOST_CHECK ( Padre3 == &N[7]);
	BOOST_CHECK ( Padre3->left == &N[6]);
	BOOST_CHECK ( Padre3->right == &N[17]);
	BOOST_CHECK ( Padre3->right->right == &N[8]);

	//Insertion of 4 nodes (10,11,9,18)-------------------------->
	N[11].N++ ;
	N[9].N ++ ;
	H4.insert_node( &N[18] ,5 ) ;
	BOOST_CHECK ( Padre4 == &N[11]);
	BOOST_CHECK ( Padre4->left == &N[10]);
	BOOST_CHECK ( Padre4->right == &N[9]);
	BOOST_CHECK ( Padre4->right->right == &N[18]);


	//---------------------------------------------------------
	//          DISCONNECT NODES
	//---------------------------------------------------------
    for ( uint32_t  i = 0 ; i < 20 ; i ++ )
    {   N[i].init() ;
    };

    N[0].N = 2 ;
	N[0].color  = black;
	H1.insert_node ( &N[1], 0 ) ;
	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));
	N[0].N = 3 ;
	H1.insert_node ( &N[2] ,1) ;

	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));
	BOOST_CHECK ( N[0].left == &N[1]);
	BOOST_CHECK ( N[0].right == &N[2]);

	//Branch of  3 nodes->Disconnect cod 2 ->
	N[0].N = 2 ;
	BOOST_CHECK ( H1.disconnect_node( 2, PAux ));
	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));
	BOOST_CHECK ( N[0].left  == NULL);
	BOOST_CHECK ( N[0].right == &N[2]);

	//Branch of  2 nodes->Disconnect cod 4 ->
	N[0].N = 1 ;
	BOOST_CHECK ( H1.disconnect_node( 4, PAux ));
	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));
	BOOST_CHECK ( N[0].left  == NULL);
	BOOST_CHECK ( N[0].right == NULL);

	N[0].init();
	N[1].init();
	N[2].init();

    N[0].N = 2 ;
	N[0].color  = black;
	H1.insert_node ( &N[1], 0 ) ;
	N[0].N = 3 ;
	H1.insert_node ( &N[2] ,1) ;

	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));
	BOOST_CHECK ( N[0].left == &N[1]);
	BOOST_CHECK ( N[0].right == &N[2]);

	//Branch of  3 nodes->Disconnect cod 4 ->
	N[0].N = 2 ;
	BOOST_CHECK (H1.disconnect_node( 4, PAux ));

	//Branch of  2 nodes->Disconnect cod 2 ->
	N[0].N = 1 ;
	BOOST_CHECK (H1.disconnect_node( 2, PAux ));

	N[0].init();
	N[1].init();
	N[2].init();
    N[0].N = 2 ;
	N[0].color  = black;
	H1.insert_node ( &N[1], 0 ) ;
	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));

	//Branch of 2 nodes->Disconnect cod 0 ->
	N[0].N = 1 ;
	BOOST_CHECK ( H1.disconnect_node( 0, PAux ));

	BOOST_CHECK ( Colombo ( NULL, &N[1], 1 , true, cout));
	BOOST_CHECK ( N[1].left == NULL);
	BOOST_CHECK ( N[1].right == NULL);

	N[0].init();
	N[1].init();
	N[2].init();
    N[0].N = 2 ;
    N[0].color  = black;
	H1.insert_node ( &N[2], 1 ) ;
	BOOST_CHECK ( Colombo ( NULL, &N[0], 1 , true, cout));

	N[0].N = 1 ;
	BOOST_CHECK ( H1.disconnect_node( 0, PAux ));
	BOOST_CHECK ( Colombo ( NULL, &N[2], 1 , true, cout));

	//Branch of 1 node->Disconnect cod 0 ->
	N[0].N = 1 ;
	BOOST_CHECK (H1.disconnect_node( 0, PAux )  != true  );


};
void Rotacion ( void )
{   //------------------------- Inicio ----------------------------------
    base_node N[15] ;
	pnode Padre = NULL ;

    //-----------------------------------------------------------
    //   RotateLeftAligned and RotateRightAligned with 2 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[1] ;
    branch H ((address_pnode) &Padre) ;
    N[1].N++ ;
    H.insert_node( &N[0], 0);

    N[1].N++ ;
    H.insert_node ( &N[3], 1) ;

    N[3].color = black ;
    branch H2 ((address_pnode) &  N[1].right ) ;
    N[1].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[4], 1 ) ;

    N[1].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[2], 0 );

    N[0].color = black ;
    N[1].color = black ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    branch R (H);
    R.rotate_left_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    R.rotate_right_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    //-----------------------------------------------------------
    //   RotateLeftAligned with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )   N[i].init() ;

    Padre = &N[1] ;
    H = branch((address_pnode) &Padre) ;
    N[1].N++ ;
    H.insert_node( &N[0], 0);
    N[1].N++ ;
    H.insert_node ( &N[3], 1) ;
    N[0].color = black ;
    N[3].color = black ;
    H2 = branch( (address_pnode)&N[1].right ) ;

    N[1].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[2], 0 );
    N[1].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[5], 1 ) ;
    N[5].color = black ;

    branch H3 ((address_pnode) &N[3].right) ;
    N[1].N++ ;
    N[3].N++ ;
    N[5].N++;
    H3.insert_node (&N[4], 0 ) ;
    N[1].N++ ;
    N[3].N++ ;
    N[5].N++;
    H3.insert_node ( &N[6] , 1 ) ;

    N[0].color = black ;
    N[1].color = black ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = red ;
    N[6].color = black ;

    R = H;
    R.rotate_left_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    //-----------------------------------------------------------
    // RotateRightAligned wioth 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )  N[i].init() ;

    Padre = &N[5] ;
    N[5].N++ ;
    H.insert_node( &N[3], 0);
    N[5].N++ ;
    H.insert_node ( &N[6], 1) ;

    N[3].color = black ;
    H2 = branch((address_pnode) &N[5].left ) ;
    N[5].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[1], 0 );
    N[5].N++ ;
    N[3].N++ ;
    H2.insert_node ( &N[4], 1 ) ;

    N[1].color = black ;
    H3 = branch((address_pnode) &N[3].left) ;
    N[5].N++ ;
    N[3].N++ ;
    N[1].N++ ;
    H3.insert_node (&N[0], 0 ) ;
    N[5].N++ ;
    N[3].N++ ;
    N[1].N++ ;
    H3.insert_node ( &N[2] , 1 ) ;

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = black ;
    N[6].color = black ;

    R = H;
    R.rotate_right_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    //-----------------------------------------------------------
    //   RotateLeftNotAligned with 3 nodescout
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[1] ;
    N[1].N++ ;
    H.insert_node( &N[0], 0);
    N[1].N++ ;
    H.insert_node ( &N[5], 1) ;
    N[5].color = black ;

    H2 = branch((address_pnode)&N[1].right ) ;
    N[1].N++ ;
    N[5].N++;
    H2.insert_node ( &N[3], 0 );
    N[1].N++ ;
    N[5].N++;
    H2.insert_node ( &N[6], 1 ) ;

    N[3].color = black ;
    H3 = branch ((address_pnode) &N[5].left) ;
    N[1].N++ ;
    N[5].N++;
    N[3].N++ ;
    H3.insert_node (&N[2], 0 ) ;
    N[1].N++ ;
    N[5].N++;
    N[3].N++ ;
    H3.insert_node ( &N[4] , 1 ) ;

    N[0].color = black ;
    N[1].color = black ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = red ;
    N[6].color = black ;

    R = H;
    R.rotate_left_not_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    //-----------------------------------------------------------
    //       ROtateRightNOtAligned with 3 nodes
    //----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ )  N[i].init() ;

    Padre = &N[5] ;
    N[5].N++ ;
    H.insert_node( &N[1], 0);
    N[5].N++ ;
    H.insert_node ( &N[6], 1) ;

    N[1].color = black ;
    H2 = branch ((address_pnode) &N[5].left ) ;
    N[5].N++ ;
    N[1].N++;
    H2.insert_node ( &N[0], 0 );
    N[5].N++ ;
    N[1].N++;
    H2.insert_node ( &N[3], 1 ) ;

    N[3].color = black ;
    H3 = branch ((address_pnode) &N[1].right) ;
    N[5].N++ ;
    N[1].N++;
    N[3].N++;
    H3.insert_node (&N[2], 0 ) ;
    N[5].N++ ;
    N[1].N++;
    N[3].N++;
    H3.insert_node ( &N[4] , 1 ) ;

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = black ;
    N[6].color = black ;

    R = H;
    R.rotate_right_not_aligned() ;
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

};


void Galleta ( void )
{   //------------------------------ Inicio -----------------------
    base_node N[15] ;
	base_node  *Padre = NULL ;
    //-----------------------------------------------------------
    //   BreakCake with 3 nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[3] ;
    branch H ((address_pnode) &Padre) ;
    N[3].N++ ;
    H.insert_node( &N[1], 0);
    N[3].N++ ;
    H.insert_node( &N[5], 1);

    N[1].color = black;
    branch H2 ( (address_pnode)&N[3].left);
    N[3].N++ ;
    N[1].N++ ;
    H2.insert_node ( &N[0], 0 ) ;
    N[3].N++ ;
    N[1].N++ ;
    H2.insert_node ( &N[2], 1 ) ;

    N[5].color = black ;
    branch H3 ((address_pnode) & N[3].right)   ;
    N[3].N++ ;
    N[5].N++ ;
    H3.insert_node ( &N[4], 0 )  ;
    N[3].N++ ;
    N[5].N++ ;
    H3.insert_node ( &N[6], 1 )  ;

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = black ;
    N[4].color = black ;
    N[5].color = red ;
    N[6].color = black ;

    branch R (H);
    branch::break_cake ( R);
    BOOST_CHECK (Colombo ( NULL, Padre, 3 , true, cout));

    //-----------------------------------------------------------
    //     BreakCake with 4 Nodes
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[5] ;
    N[5].N++;
    H.insert_node( &N[1], 0);
    N[5].N++;
    H.insert_node( &N[7], 1);
    N[7].color = black;
    H2 = branch ((address_pnode) &N[5].right)   ;
    N[5].N++;
    N[7].N++;
    H2.insert_node( &N[6], 0);
    N[5].N++;
    N[7].N++;
    H2.insert_node( &N[8], 1);
    N[1].color = black ;
    H3 = branch( (address_pnode)& N[5].left);
    N[5].N++;
    N[1].N++;
    H3.insert_node( &N[0], 0 );
    N[5].N++;
    N[1].N++;
    H3.insert_node( &N[3], 1 );
    N[3].color = black ;
    branch H4 ((address_pnode) &N[1].right);
    N[5].N++;
    N[1].N++;
    N[3].N++ ;
    H4.insert_node( &N[2], 0);
    N[5].N++;
    N[1].N++;
    N[3].N++ ;
    H4.insert_node( &N[4], 1);

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = black ;
    N[6].color = black ;
    N[7].color = red ;
    N[8].color = black ;

    R =H;
    branch::break_cake ( R);
    BOOST_CHECK (Colombo ( NULL, Padre, 3 , true, cout));

};


void GalletaInversa ( void )
{   //------------------------------ Inicio -----------------------
    base_node  N[15] ;
	base_node  *Padre = NULL , *PAux = NULL;



    //-----------------------------------------------------------
    //       ReverseCake with 2 Nodes in HSup
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[3] ;
    branch H ((address_pnode) &Padre) ;
    N[3].N++ ;
    H.insert_node( &N[1], 0);
    N[3].N++ ;
    H.insert_node( &N[4], 1);
    N[1].color = black ;
    branch H2 ((address_pnode) &N[3].left);
    N[3].N++ ;
    N[1].N++ ;
    H2.insert_node (&N[0], 0 )  ;
    N[3].N++ ;
    N[1].N++ ;
    H2.insert_node (&N[2], 1 )  ;

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = black ;
    N[4].color = black ;
    branch RSup ((address_pnode)H.ppblack);
    branch HInf ((address_pnode) & N[1].right);
    N[3].N-- ;
    N[1].N-- ;
    HInf.disconnect_node(0 , PAux);
    branch::reverse_cake( RSup, HInf, 3);
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

    branch RAux ((address_pnode) &N[3].left);

    //-----------------------------------------------------------
    //    ReverseCake with 2 Nodes in HSup
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Padre = &N[5] ;
    H = branch ((address_pnode) &Padre) ;
    N[5].N++ ;
    H.insert_node( &N[3], 0);
    N[5].N++ ;
    H.insert_node( &N[6], 1);

    N[3].color = black ;
    H2 = branch ((address_pnode) &N[5].left);
    N[5].N++ ;
    N[3].N++ ;
    H2.insert_node (&N[1], 0 )  ;
    N[5].N++ ;
    N[3].N++ ;
    H2.insert_node (&N[4], 1 )  ;

    N[1].color = black ;
    branch H3( (address_pnode)&N[3].left);
    N[5].N++ ;
    N[3].N++ ;
    N[1].N++ ;
    H3.insert_node ( &N[0], 0 );
    N[5].N++ ;
    N[3].N++ ;
    N[1].N++ ;
    H3.insert_node ( &N[2], 1 );

    N[0].color = red ;
    N[1].color = black ;
    N[2].color = red ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = black ;
    N[6].color = black ;

    RSup = branch ((address_pnode)H.ppblack);
    HInf =branch ((address_pnode) & N[3].right);
    RAux = branch ((address_pnode) &N[3].left);
    N[3].N-- ;
    N[5].N-- ;
    HInf.disconnect_node( 0 , PAux);

    branch::reverse_cake( RSup, HInf, 3);
    BOOST_CHECK (Colombo ( NULL, Padre, 2 , true, cout));

}

void galletainversa02 ( void)
{   //----------------------------------------------------------------
    //  REVERSE CAKE TEST
    //----------------------------------------------------------------
	base_node  N[15] ;
	pnode Father = NULL ;
    for ( uint32_t i = 0 ; i < 15 ; i ++ )
    {   N[i].init() ;
    };
    Father = &N[0] ;
    branch H ((address_pnode) &Father), H2( (address_pnode)&Father);
    branch RInf( (address_pnode)&Father),RSup( (address_pnode)&Father);

	//-----------------------------------------------------------
    //                  Case 01
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Father = &N[3] ;
    H.ppblack = (address_pnode) &Father ;
    N[3].color = black ;
    N[3].N++ ;
    H.insert_node( &N[1], 0);
    N[3].N++ ;
    H.insert_node( &N[4], 1);

    N[1].color = black ;
    H.ppblack = (address_pnode)&N[3].left ;
    N[3].N++ ;
    N[1].N++ ;
    H.insert_node( &N[0], 0);

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;
    N[3].color = black ;
    N[4].color = black ;

    RInf.ppblack= (address_pnode) &N[1].right;
    BOOST_CHECK (branch::reverse_cake ( RSup, RInf,3) );

    BOOST_CHECK ( Colombo ( NULL, Father, 2 , true,cout));

	//-----------------------------------------------------------
    //                  Case 02
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Father = &N[5] ;
    H.ppblack = (address_pnode)&Father ;
    N[5].color = black ;

    N[5].N++ ;
    H.insert_node( &N[3], 0);
    N[5].N++ ;
    H.insert_node( &N[6], 1);

    N[3].color = black ;
    H.ppblack = (address_pnode)&N[5].left ;
    N[3].N++ ;
    N[5].N++ ;
    H.insert_node( &N[1], 0);

    N[1].color = black ;
    H.ppblack = (address_pnode)&N[3].left ;
    N[3].N++ ;
    N[5].N++ ;
    N[1].N++;
    H.insert_node( &N[0], 0);
    N[3].N++ ;
    N[5].N++ ;
    N[1].N++;
    H.insert_node( &N[2], 1);

    N[0].color = red ;
    N[1].color = black ;
    N[2].color = red ;
    N[3].color = red ;
    N[4].color = black ;
    N[5].color = black ;
    N[6].color = black ;
    N[7].color = black ;
    N[8].color = black ;

    RInf.ppblack = (address_pnode)&N[3].right;
    BOOST_CHECK( branch::reverse_cake ( RSup, RInf,3));
    BOOST_CHECK( Colombo ( NULL, Father, 2 , true,cout));

	//-----------------------------------------------------------
    //              Case 03
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Father = &N[2] ;
    H.ppblack = (address_pnode)&Father ;
    N[2].N++ ;
    H.insert_node( &N[0], 0);

    N[0].color = black ;
    H.ppblack =(address_pnode) &N[2].left ;
    N[2].N++ ;
    N[0].N++;
    H.insert_node ( &N[1], 1) ;

    N[0].color = black ;
    N[1].color = red ;
    N[2].color = black ;

    RInf.ppblack =(address_pnode) &N[2].left;
    BOOST_CHECK( branch::reverse_cake ( RSup, RInf,1));
    BOOST_CHECK ( Colombo ( NULL, Father, 2 , true,cout));

	//-----------------------------------------------------------
    //              Case 04
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Father = &N[3] ;
    H.ppblack = (address_pnode)&Father ;
    N[3].N++ ;
    H.insert_node( &N[1], 0);

    N[1].color = black ;
    H.ppblack =(address_pnode)&N[3].left ;
    N[1].N++ ;
    N[3].N++;
    H.insert_node ( &N[0], 0) ;

    N[1].N++ ;
    N[3].N++;
    H.insert_node ( &N[2], 1) ;

    N[0].color = red ;
    N[1].color = black ;
    N[2].color = red ;
    N[3].color = black ;

    RInf.ppblack = (address_pnode)&N[3].left;
    BOOST_CHECK (branch::reverse_cake ( RSup, RInf,1) );
    BOOST_CHECK (Colombo ( NULL, Father, 2 , true, cout) );

	//-----------------------------------------------------------
    //              C A S E     0 5
    //-----------------------------------------------------------
    for ( uint32_t i = 0 ; i < 15 ; i ++ ) N[i].init() ;

    Father = &N[1] ;
    H.ppblack =(address_pnode)&Father ;
    N[1].N++ ;
    H.insert_node( &N[0], 0);
    N[0].color = black ;
    N[1].color = black ;

    RInf.ppblack = (address_pnode)&N[1].left;
    BOOST_CHECK (not branch::reverse_cake ( RSup, RInf,1));

}


test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &prueba1 ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Rotacion ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &Galleta ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &GalletaInversa ) );
    framework::master_test_suite().
        add( BOOST_TEST_CASE( &galletainversa02 ) );

    return 0;
}
