//----------------------------------------------------------------------------
/// @file branch.hpp
/// @brief This class represent the branch of the vector_tree
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_BRANCH_HPP
#define  __COUNTERTREE_FOREST_BRANCH_HPP

#include <boost/countertree/forest/base_node.hpp>

namespace countertree
{
namespace forest
{
//##########################################################################
//                                                                        ##
//                 C L A S S     B R A N C H                              ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class  branch
/// @brief  This class represent a branch of the tree
//
/// @remarks All the pointers of the branch are identified by a code
///  The description of this code is
///         000 : pointer left black node
///         001 : pointer right black node
///         010 : pointer left  of left node
///         011 : pointer right of left node
///         100 : pointer left of right node
///         101 : pointer right of right node
///  This description is valid by all the functions
//----------------------------------------------------------------
class branch
{
public:
//***************************************************************************
//                        V A R I A B L E S
//***************************************************************************
base_node **  ppblack ;

//***************************************************************************
//          C O N S T R U C T O R
//
//      branch ( base_node **  P1);
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : branch
/// @brief Constructor of the class
/// @param [in] P1 : address to the pointer to the black node of the branch
//---------------------------------------------------------------------------
branch ( base_node **  P1): ppblack ( P1)
{   //----------------------------- begin -----------------------
    #if __DEBUG_CNTREE != 0
    assert ( P1 != NULL and *P1 != NULL);
    #endif
};

//***************************************************************************
//  C O N S U L T    I N T E R N A L   I N F O R M A T I O N
//
//  size_type       n_nodes         ( void ) const;
//  base_node **    pointer_Cod     ( unsigned Cod);
//  base_node **    pointer_father  ( base_node *  P );
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : n_nodes
/// @brief provide the number of nodes in the branch. They can
///        be 4 after a break cake
/// @param [in] none
/// @return number of nodes
//---------------------------------------------------------------------------
unsigned  n_nodes ( void ) const
{   //------------------------------- Inicio -----------------------
    unsigned N = 0 ;
    base_node * PBlack = *ppblack ;
    if ( PBlack != NULL )
    {   N++ ;
        base_node *  P1 = PBlack->left ;
        if ( P1 != NULL and P1->color == red )
        {   N++;
            if ( P1->left != NULL and P1->left->color == red ) N++ ;
            if ( P1->right != NULL and P1->right->color == red ) N++ ;
        };

        P1 = PBlack->right ;
        if ( P1 != NULL and P1->color == red)
        {   N++;
            if ( P1->left != NULL and P1->left->color == red ) N++ ;
            if ( P1->right != NULL and P1->right->color == red ) N++ ;
        };
    };
    return N ;
};
//---------------------------------------------------------------------------
//  function : pointer_Cod
/// @brief Obtain the address of a pointer to a node<T> with the code Cod
/// @param [in] Cod : code of the node<T>*
/// @return address of the pointer to a node<T>
//---------------------------------------------------------------------------
base_node **  pointer_Cod ( unsigned Cod)
{   //----------------------- Inicio ------------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Cod < 6 );
    #endif
    base_node **  PP= NULL ;
    base_node * PAux = NULL ;
    base_node *  PBlack = *ppblack ;
    switch ( Cod >>1 )
    {   case 0: PP =  ((Cod == 0)? &(PBlack->left) : &(PBlack->right)) ;
                break;
        case 1:if ( (PAux= PBlack->left) != NULL and PAux->color == red )
                    PP = ((Cod==2)? &(PAux->left) : &(PAux->right)) ;
               break;
        case 2:if ((PAux=PBlack->right) != NULL and PAux->color == red )
                    PP = ((Cod==4)? &(PAux->left) : &(PAux->right)) ;
               break;
        default : assert ( false );
    };
    return PP ;
};
//---------------------------------------------------------------------------
//  function : pointer_father
/// @brief address of the pointer, pointing to the node pointed by P
/// @param [in] P : pointer
/// @return address of the pointer
//---------------------------------------------------------------------------
base_node **   pointer_father ( base_node * P )
{   //----------------------- Inicio --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( P != NULL );
    #endif
    base_node *  Pup = P->up ;
    if ( Pup == NULL ) return ppblack ;
    return (( Pup->left == P ) ?& ( Pup->left ) : &(Pup->right )) ;
};

//***************************************************************************
//  I N S E R T _ N O D E   ,   D I S C O N N E C T _ N O D E
//
//  void insert_node ( base_node *  P1 , unsigned Cod);
//  bool disconnect_node ( unsigned Cod , base_node *  &  PAux);
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function :insert_node
/// @brief Insert a node in the branch. All the counters of the
//         nodes must be incremented from the insertion point to the root.\n
//         Temporally a branch can have 4 nodes after a insertion. In this
//         case the structure of the branch is an V inverted in order to
//         simplify the rotations
/// @param [in] P1 : pointer to the node to insert
/// @param [in] Cod : code of the pointer where connect the node
/// @return none
/// @remarks The counters of the nodes must be incremented, due to this
//           they reflect the number of nodes after the insertion, not
///          before
//---------------------------------------------------------------------------
void insert_node ( base_node *  P1 , unsigned Cod)
{   //---------------------------- Begin ------------------------
    #if __DEBUG_CNTREE != 0
    assert ( P1 != NULL and n_nodes() < 5);
    #endif

    //Preparacion del nodo a insertar
    base_node *  PBlack = *ppblack ;
    P1->init() ;

    switch( Cod)
    {   case 0: PBlack->left = P1 ;
                P1->up = PBlack;
                break ;

        case 1: PBlack->right = P1 ;
                P1->up = PBlack;
                break ;

        case 2: PBlack->left->left = P1  ;
                P1->up = PBlack->left ;
                //PBlack->left->N++ ;
                break ;

        case 3: P1->left = PBlack->left ;
                PBlack->left->up = P1 ;
                PBlack->left = P1 ;
                P1->N =  2 ;
                P1->left->N = 1 ;
                P1->up = PBlack ;
                break ;

        case 4: P1->right = PBlack->right ;
                PBlack->right->up = P1 ;
                PBlack->right = P1 ;
                P1->N = 2 ;
                P1->right->N = 1 ;
                P1->up = PBlack ;
                break ;

        case 5: PBlack->right->right = P1 ;
                P1->up = PBlack->right ;
                //PBlack->right->N++;
                break ;
        default: assert ( false) ;
    };
    PBlack = *ppblack ;
    if ( PBlack->N == 3 )
    {   if ( PBlack->left == NULL ) rotate_left_aligned() ;
        else if ( PBlack->right == NULL ) rotate_right_aligned() ;
    };
};
//---------------------------------------------------------------------------
//  function : disconnect_node
/// @brief disconnect a node of the branch, and leave the branch,
///        if possible , in a stable configuration
/// @param [in] Cod : code of the pointer to the node to disconnect.
/// @param [in] PAux : pointer to the disconnected node
/// @return bool (true : OK branch stable, false : the branch is empty)
/// @remarks The counters to the nodes must be previously decremented
//---------------------------------------------------------------------------
bool disconnect_node ( unsigned Cod , base_node *  & PAux)
{   //--------------------------- Inicio -----------------------
    #if __DEBUG_CNTREE != 0
    unsigned Nnd = n_nodes() ;
    assert ( not ( Nnd > 3 or (Nnd == 3 and Cod < 2)) );
    #endif

    base_node * PBlack = *ppblack ;

    bool Estable = true ;
    Cod = Cod>>1 ;
    switch ( Cod )
    {   case 0 :  // node negro de la hoja
            PAux = PBlack ;
            if (PBlack->left != NULL)
            {   PBlack->left->up = PBlack->up ;
                (*ppblack) = PBlack->left ;
                PBlack->left->color = black ;
            }
            else
            {   if ( PBlack->right != NULL)
                {   PBlack->right->up = PBlack->up ;
                    (*ppblack) = PBlack->right ;
                    PBlack->right->color = black ;
                }
                else
                {   (*ppblack) = NULL;
                    Estable = false ;
                };
            };
            break ;
        case 1 : // node izdo
            PAux = PBlack->left ;
            PBlack->left = NULL ;
            //PBlack->N-- ;
            break ;

        case 2 : // node Dcho
            PAux = PBlack->right ;
            PBlack->right = NULL ;
            //PBlack->N-- ;
            break ;
        default: assert ( false) ;
    };
    PAux->init();
    return Estable;
};

//***************************************************************************
//                      R O T A T I O N S
//
//  void rotate_left_aligned        ( void )
//  void rotate_left_not_aligned    ( void )
//  void rotate_right_aligned       ( void )
//  void rotate_right_not_aligned   ( void )
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : rotate_left_aligned
/// @brief rotate the nodes of the branch to the left, when they are aligned
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void rotate_left_aligned ( void )
{   //-------------------------------Inicio ------------------------
    base_node::rotate_left_aligned( ppblack);
    base_node *  P = *ppblack ;
    P->color = black ;
    P->left->color = red;
};
//---------------------------------------------------------------------------
//  function : rotate_left_not_aligned
/// @brief rotate the nodes of the branch to the left, when they aren't
///        aligned
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void rotate_left_not_aligned(void)
{   //--------------------  begin------------------
    base_node::rotate_left_not_aligned( ppblack);
    base_node *  P = *ppblack ;
    P->color = black ;
    P->left->color = red ;
};
//---------------------------------------------------------------------------
//  function :rotate_right_aligned
/// @brief rotate the nodes of the branch to the right, when they are
///        aligned
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void rotate_right_aligned( void )
{   //--------------- begin----------------------
    base_node::rotate_right_aligned ( ppblack) ;
    base_node *  P = *ppblack ;
    P->color = black ;
    P->right->color = red ;
};

//---------------------------------------------------------------------------
//  function :rotate_right_not_aligned
/// @brief rotate the nodes of the branch to the right, when they aren't
///        aligned
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void rotate_right_not_aligned ( void)
{   //----------- begin -----------------------
    base_node::rotate_right_not_aligned( ppblack);
    base_node *  P = *ppblack ;
    P->color = black ;
    P->right->color = red ;
};

//***************************************************************************
//                 C A K E    O P E R A T I O N S
//
//  static void break_cake   ( branch<T> &  R);
//  static bool reverse_cake ( branch<T> & Rup,branch<T> &RInf,uint32_t CodS) ;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : break_cake
/// @brief This function implement the break cake of the branch
/// @param [in] R : branch to break cake
/// @return none
//---------------------------------------------------------------------------
static void break_cake ( branch & R)
{   //-------------------------- Inicio ---------------------------
    base_node *  PBlack = (*R.ppblack) ;
    PBlack->left->color = black ;
    PBlack->right->color = black ;
    PBlack->color = red ;
};
//---------------------------------------------------------------------------
//  function : reverse_cake
/// @brief Implements the reverse cake mechanism between the
///        Rup and Rinf branches
/// @param [in] Rup : Upper branch
/// @param [in] RInf : lower branch
/// @param [in] CodS : Code of the pointer of Rup which connect the
///                    two branches
/// @return Estability of the branch (true : stable,false : Rup is
///         empty and the branch is not stable)
//---------------------------------------------------------------------------
static bool reverse_cake (branch &Rup, branch &RInf,unsigned CodS) ;

//***************************************************************************
};//             E N D     B R A N C H    C L A S S
//***************************************************************************
#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief print the branch in an outstream
/// @param [in] salida : stream to write
/// @param [in] H : branch to print
/// @return stream after writting
//---------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &salida, const branch & H ) ;
#endif
//***************************************************************************
//
//          F U N C T I O N S  N O N   I N L I N E
//
//***************************************************************************

//---------------------------------------------------------------------------
//  function : reverse_cake
/// @brief Implements the reverse cake mechanism between the
///        Rup and Rinf branches
/// @param [in] Rup : Upper branch
/// @param [in] RInf : lower branch
/// @param [in] CodS : Code of the pointer of Rup which connect the
///                    two branches
/// @return Estability of the branch (true : stable,false : Rup is
///         empty and the branch is not stable)
//---------------------------------------------------------------------------
bool branch::reverse_cake (branch &Rup, branch &RInf,unsigned CodS)
{   //------------------------------- Inicio --------------------------------
    unsigned Nup = Rup.n_nodes() ;
    #if __DEBUG_CNTREE != 0
    assert ( not ( CodS > 5 or ( CodS < 2 and Nup > 2)) );
    #endif
    //
    //                 branch Superior
    // Si Cod > 1 indica que tenemos el nodo listo para el descenso
    // Si Cod < 2 la branch no puede tener mas de 2 nodos
    // Si Cod < 2 y hay mas de un nodo en la rama hay que hacer una rotacion
    // para tener el nodo listo para el descenso
    //
    if ( CodS < 2 and Nup > 1 )
    {   if ( CodS == 0 )
        {   Rup.rotate_left_aligned() ;
            CodS = 2 ;
        }
        else
        {   Rup.rotate_right_aligned() ;
            CodS = 5 ;
        };
    };
    //
    // Presuponemos que RInf esta vacia, por lo que no nos vale para nada.
    // Hay que buscar la rama que cuelga del mismo nodo que RInf.
    // Si dicha rama tiene mas de 1 nodo, mediante una rotacion inserta un
    // nodo en RInf y el sistema queda estable.
    // Si solo tiene 1 nodo , descendemos el nod  de la rama superior.
    // Si dicha rama tiene mas de 1 nodo , el sistema está estable.
    // Si solo tiene un nodo , queda vacía y la inestabilidad se propaga
    // hacia la rama superior
    //
    // El nuevo codigo es el mismo que el anterior con el ultimo bit complementado
    unsigned CodS2 = ( CodS & 6) | ((~CodS) & 1);
    base_node **  PPInf2 = Rup.pointer_Cod( CodS2);
    branch RInf2( PPInf2) ;
    unsigned NInf2 = RInf2.n_nodes() ;

    // Si RInf2 tiene mas de 1 nodo se arregla con una rotación
    if ( NInf2 > 1)
    {   base_node *  PBlack = * RInf2.ppblack ;
        base_node **  PPup2 = Rup.pointer_father ( PBlack->up);
        unsigned color2 = PBlack->up->color ;
        if ( (CodS2 & 1 ) == 0 )
        {   if ( PBlack->right != NULL and PBlack->right->color == red)
                    base_node::rotate_right_not_aligned ( PPup2);
            else  base_node::rotate_right_aligned ( PPup2);
        }
        else
        {   if ( PBlack->left != NULL and PBlack->left->color == red)
                    base_node::rotate_left_not_aligned ( PPup2) ;
            else    base_node::rotate_left_aligned( PPup2) ;
        };
        PBlack = *PPup2 ;
        PBlack->color= color2 ;
        PBlack->left->color = black ;
        PBlack->right->color = black ;
        return true ;
    };
    //
    // El nodo de la rama superior desciende. Si la rama superior tiene
    // mas de 1 nodo, al finalizar el descenso , queda estable.
    // Si solo tenía 1 nodo , queda vacía y por lo tanto inestable
    // En este punto sabemos con certeza que RInf2 tiene 1 solo nodo,
    // por lo que el descenso es trivial
    //
    base_node *  PAux = *RInf2.ppblack ;
    PAux->up->color = black ;
    PAux->color = red ;
    return ( Nup >1);
};

#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief print the branch in an outstream
/// @param [in] salida : stream to write
/// @param [in] H : branch to print
/// @return stream after writting
//---------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &salida, const branch & H )
{	//------------ Inicio ------------------------
	salida<<"["<<( void*)(&H)<< "] ";
	salida<<"ppblack:"<<( void*)(H.ppblack);
	salida<<" PBlack:"<<(*H.ppblack);
	salida<<" N :"<<H.n_nodes()<<std::endl ;
	if (H.n_nodes() == 0 ) return salida ;

    base_node *PAux = *(H.ppblack) ;
    salida<<"Black :"<<(*PAux)<<std::endl;

    if ( PAux->left != NULL and PAux->left->color == red )
    {   PAux = PAux->left ;
        salida<<"left  :"<<( *PAux )<<std::endl;
        if ( PAux->left!= NULL and PAux->left->color == red )
            salida<<"left->left :"<<( * PAux->left)<<std::endl;
        if ( PAux->right!= NULL and PAux->right->color == red )
            salida<<"left->right :"<<( * PAux->right)<<std::endl;
    };
    PAux = *(H.ppblack) ;
    if ( PAux->right != NULL and PAux->right->color == red )
    {   PAux = PAux->right ;
        salida<<"right  :"<<( *PAux )<<std::endl;
        if ( PAux->left!= NULL and PAux->left->color == red )
            salida<<"right->left :"<<( * PAux->left)<<std::endl;
        if ( PAux->right!= NULL and PAux->right->color == red )
            salida<<"right->right :"<<( * PAux->right)<<std::endl;
    };
 	return salida ;
};
#endif
//***************************************************************************
};//              E N D    F O R E S T             N A M E S P A C E
//
};//              E N D    C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
