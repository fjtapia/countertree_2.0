//----------------------------------------------------------------------------
/// @file   base_node.hpp
/// @brief  This file contains the implementation of the node in the countertree
///         data structure
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_BASE_NODE_HPP
#define __COUNTERTREE_FOREST_BASE_NODE_HPP

#include <stdexcept>
#include <boost/countertree/common/definitions.hpp>
#include <boost/countertree/common/config.hpp>

#if __DEBUG_CNTREE != 0
    #include <iostream>
#endif

namespace countertree
{
namespace forest
{
using countertree::common::signed_type ;
using countertree::common::unsigned_type ;
using countertree::common::NByte;
using countertree::common::Conf;

enum { red = 0 , black = 1 }    ;

//##########################################################################
//                                                                        ##
//                  C L A S S    B A S E _ N O D E                        ##
//                                                                        ##
//##########################################################################

//-------------------------------------------------------------
/// @class  base_node
/// @brief  This class represent a node of the tree
//
/// @remarks
//----------------------------------------------------------------
struct base_node
{
//**************************************************************************
//                          D E F I N I T I O N S
//**************************************************************************
typedef Conf<NByte>::bitfield_t     bitfield_t ;

//**************************************************************************
//                          V A R I A B L E S
//**************************************************************************
base_node *left, * right,* up   ;
bitfield_t  N : Conf<NByte>::n_bits_number ;
unsigned color :1; // 1: black 0 : red


//***************************************************************************
//  C O N S T R U C T O R , D E S T R U C T O R
//
//  explicit base_node ( void) NOEXCEPT
//  base_node ( const base_node & b) NOEXCEPT
//
//  base_node ( base_node && )= delete ;
//  base_node & operator= ( base_node && )= delete ;
//
//**************************************************************************
//base_node ( base_node && )= delete ;
//base_node & operator= ( base_node && )= delete ;
//base_node ( const base_node & )  = delete;
base_node ( base_node && ) ;
base_node & operator= ( base_node && ) ;
base_node ( const base_node & )  ;

//---------------------------------------------------------------------------
//  function : base_node
/// @brief Constructor
/// @param [in] DT : Value to copy in the node. By default the empty
///                  constructor of the value
//---------------------------------------------------------------------------
explicit base_node ( void) NOEXCEPT
:left(NULL),right(NULL),up(NULL),N(1),color(black){ };

//---------------------------------------------------------------------------
//  function : ~node
/// @brief Destructor
//---------------------------------------------------------------------------
virtual ~base_node ( void  ) NOEXCEPT{ };

//***************************************************************************
//   O P E R A T O R = , I N I T , R E M O V E _ C O N S T
//
//  base_node & operator= ( const base_node & b) NOEXCEPT
//  void init ( void ) NOEXCEPT
//  base_node * remove_const ( void) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator=
/// @brief Asignation operator
/// @param [in] b : node to be copied
/// @return reference to the object after the copy
/// @remarks This function copy the color and counter , but don't
///          copy the pnodes
//---------------------------------------------------------------------------
base_node & operator= ( const base_node & b) NOEXCEPT
{   color = b.color ;
    N = b.N ;
    return *this ;
}
//---------------------------------------------------------------------------
//  function : init
/// @brief Initialize the node, but don't modify the data
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void init ( void ) NOEXCEPT
{   left =right=up=NULL;
    N = 1 ;
    color = red ;
};
//---------------------------------------------------------------------------
//  function : remove_const
/// @brief Generate a base_node * from a const base_node*
/// @param [in] none
/// @return Pointer
//---------------------------------------------------------------------------
base_node * remove_const ( void) const NOEXCEPT
{   return  const_cast < base_node* >(this );
};
//***************************************************************************
//  P R E V I O U S , N E X T , S H I F T
//
//  base_node *  previous  ( void ) NOEXCEPT
//  const base_node *  previous  ( void ) const NOEXCEPT
//
//  base_node * next ( void ) NOEXCEPT
//  const base_node * next ( void ) const NOEXCEPT
//
//  base_node * shift ( signed_type NDesp ) NOEXCEPT
//  const base_node * next ( void ) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : previous
/// @brief Obtain the pnode to the previous node. If don't exist return NULL
/// @param [in] none
/// @return Pointer to the node.
/// @remarks This operation is O ( log N )
//---------------------------------------------------------------------------
base_node *  previous  ( void ) NOEXCEPT
{   //------------- begin ------------------
    base_node *  P = this ;

    // Primero tratamos de buscarlo hacia abajo. Si no fuera asi , lo
    // buscamos hacia arriba
    if ( left != NULL )
    {   P = left ;
        while ( P->right != NULL ) P = P->right ;
    }
    else
    {   // Subir por la dcha todo lo que puedas y luego un salto hacia
        // arriba a la izda
        // Si no es posible saltar a la izda devuelve NULL, porque no
        // tiene nada posterior
        while ( P->up != NULL and P->up->left == P ) P = P->up ;
        P =( P->up != NULL and P->up->right != P ) ?NULL :P->up ;
    };
    return P ;
};
const base_node *  previous  ( void ) const NOEXCEPT
{   return remove_const()->previous();
};
//---------------------------------------------------------------------------
//  function : next
/// @brief Obtain the pnode of the next node. If don't exist return NULL
/// @param [in] none
/// @return pnode
/// @remarks This operation is O ( log N )
//---------------------------------------------------------------------------
base_node * next ( void ) NOEXCEPT
{   //------------- begin ------------------
    base_node *  P = this ;

    // Primero tratamos de buscarlo hacia abajo. Si no fuera asi , lo
    // buscamos hacia arriba
    if ( right != NULL )
    {   P = right;
        while ( P->left != NULL ) P = P->left ;
    }
    else
    {   // Subir todo lo que puedas por la izda, y luego un salto hacia
        // arriba hacia la dcha
        // Si no puede saltar a la dcha devuelve NULL, porque no tiene
        // nodo posterior
        while (P->up != NULL and P->up->right == P) P= P->up;
        P= ( P->up != NULL and P->up->left == P) ?  P->up :NULL;
    };
    return P;
};
const base_node * next ( void ) const NOEXCEPT
{   return remove_const()->next();
};
//---------------------------------------------------------------------------
//  function : shift
/// @brief Obtain the pnode of the node located several positions
///        after or before the node
/// @param [in] NDesp : Number of positions to shift. This value can be
///                     positive  or negative
/// @return Pointer to the node. If don't exist return NULL
/// @remarks This operation is O ( log N )
//---------------------------------------------------------------------------
base_node * shift ( signed_type NDesp ) NOEXCEPT
{   //----------------- begin ---------------
    base_node *  P = this ;
    if ( NDesp == 0 ) return P;
    while ( NDesp != 0)
    {   if (NDesp > 0 )
        {   //               Desplazamiento hacia adelante
            // Trata de bajar por la dcha. Lo maximo que puede avanzar por
            // ese camino está determinado por el contador del nodo a su dcha.
            // Si esto no fuera suficiente, emprende el camino hacia el nodo
            // superior. Si este no existiera quiere decir que no puede
            // alcanzar ese desplazamiento por lo que devuelve NULL
            //
            if ( NDesp > (signed_type)(P->n_right()) )
            {   if ( P->up == NULL ) return NULL ;
                if ( P->up->right == P ) NDesp += P->n_left() + 1;
                else                     NDesp -= P->n_right() + 1;
                P = P->up ;
            }
            else
            {   //          Bajada por la derecha
                P = P->right ;
                NDesp -= P->n_left() +1 ;
            };
        }
        else
        {   //
            //                 Desplazamiento hacia atras
            // Trata de bajar por la left. Lo máximo que puede retroceder por
            // ese camino está determinado por el contador del nodo a su izda.
            // Si esto no fuera suficiente, emprende el camino hacia el nodo
            // superior. Si este no existiera quiere decir que no puede
            // alcanzar ese desplazamiento por lo que devuelve NULL
            //
            if ( -NDesp > (signed_type)(P->n_left()) )
            {   if ( P->up == NULL ) return NULL ;
                if ( P->up->right == P ) NDesp += P->n_left () + 1;
                else                     NDesp -= P->n_right () + 1;
                P = P->up ;
            }
            else
            {   //               Bajada por la izda
                P = P->left ;
                NDesp += P->n_right() +1 ;
            };
        };
    }; // Fin while
    return P;
};
const base_node * shift ( signed_type NDesp )  const NOEXCEPT
{   return remove_const()->shift ( NDesp);

}
//***************************************************************************
//  G E T _ P O S , N _ L E F T , N _ R I G H T , N D
//
//  signed_type get_pos ( void ) const NOEXCEPT
//  signed_type n_left ( void )const NOEXCEPT
//  signed_type n_right ( void )const  NOEXCEPT
//  static signed_type nd( const base_node * P) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : get_pos
/// @brief Get the position of the node in the tree structure
/// @param [in] none
/// @return Position in the structure
/// @remarks This operation is O ( log N )
//---------------------------------------------------------------------------
signed_type get_pos ( void ) const NOEXCEPT
{   const base_node * P1 = up;
    const base_node  * P = this ;
    signed_type Pos = P->n_left () ;
    while ( P1 != NULL)
    {   if ( P == P1->right ) Pos += P1->n_left() +1 ;
        P = P1 ;
        P1 = P1->up ;
    };
    return Pos ;
};
//---------------------------------------------------------------------------
//  function :n_left
/// @brief Counter of the node linked by the left pnode. If the left
///        pnode is NULL return 0
/// @param [in] none
/// @return Number of nodes
/// @remarks
//---------------------------------------------------------------------------
signed_type n_left ( void )const NOEXCEPT
{   return (left == NULL) ? 0 : left->N ;
};
//---------------------------------------------------------------------------
//  function : n_right
/// @brief Counter of the node linked by the right pnode. If the right
///        pnode is NULL return 0
/// @param [in]
/// @return Number of nodes
/// @remarks
//---------------------------------------------------------------------------
signed_type n_right ( void )const  NOEXCEPT
{   return (right==NULL)? 0 : right->N;
};
//---------------------------------------------------------------------------
//  function : nd
/// @brief Counter of a node pointed by P. If P is NULL return 0
/// @param [in] P : pnode to the node to exam
/// @return Counter of the node
//---------------------------------------------------------------------------
static signed_type nd( const base_node * P) NOEXCEPT
{   return ( P == NULL)?0:P->N;
};

//***************************************************************************
//                    S W A P P I N G   N O D E S
//
//  static void swap_node ( base_node ** PP1, base_node ** PP2) NOEXCEPT
//  static void swap_contiguous_left ( base_node  ** PPup) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : swap_node
/// @brief Swap two nodes. They can't be contiguous
/// @param [in] PP1 : Pointer to the base_node pointer to the first node
/// @param [in] PP2 : Pointer to the base_node pointer to the second node
/// @return none
//---------------------------------------------------------------------------
static void swap_node ( base_node ** PP1, base_node ** PP2) NOEXCEPT
{   //------------------------------- Inicio ---------------------
    #if __DEBUG_CNTREE != 0
    assert ( PP1 !=NULL and *PP1 !=NULL and PP2 !=NULL and *PP2 !=NULL);
    #endif
    base_node *P1 = *PP1 , *P2 = *PP2 ;
    *PP1 = P2 ;
    *PP2 = P1 ;

    std::swap ( P1->up ,  P2->up) ;
    std::swap ( P1->left , P2->left);
    if ( P1->left != NULL) P1->left->up = P1 ;
    if ( P2->left != NULL) P2->left->up = P2 ;

    std::swap ( P1->right , P2->right);
    if ( P1->right != NULL) P1->right->up = P1 ;
    if ( P2->right != NULL) P2->right->up = P2 ;

    unsigned color1 = P1->color ;
    P1->color= P2->color  ;
    P2->color = color1 ;

    bitfield_t N1 = P1->N ;
    P1->N = P2->N ;
    P2->N = N1 ;
};
//---------------------------------------------------------------------------
//  function :swap_contiguous_left
/// @brief Swap two nodes contiguous by the left pnode of the upper
///        node.
/// @param [in][out] PPup : address of the pnode to the upper node\n
///                         When finish the function PPup contains the
///                         address  to the new upper node
/// @return none
/// @remarks
//---------------------------------------------------------------------------
static void swap_contiguous_left ( base_node  ** PPup) NOEXCEPT
{   //-------------------begin --------------------
    #if __DEBUG_CNTREE != 0
    assert (PPup != NULL and *PPup != NULL );
    #endif
    base_node  *Pup = *PPup ;

    assert (Pup->left != NULL and Pup->left->right == NULL  );
    base_node  *PInf = Pup->left ;

    // Actualizacion de PPup y Pup
    (*PPup ) = PInf ;
    PInf->up = Pup->up ;

    // left
    Pup->left = PInf->left ;
    if ( Pup->left != NULL ) Pup->left->up = Pup ;
    PInf->left = Pup ;
    Pup->up = PInf ;

    // right
    PInf->right = Pup->right ;
    if ( PInf->right != NULL) PInf->right->up = PInf ;
    Pup->right = NULL ;

    // color
    unsigned color1 = Pup->color ;
    Pup->color  = PInf->color ;
    PInf->color = color1 ;

    // N
    bitfield_t N1 = Pup->N ;
    Pup->N = PInf->N ;
    PInf->N = N1 ;
};
//***************************************************************************
//                       R O T A T I O N S
//
//  static void rotate_left_aligned      ( base_node  ** PPup );
//  static void rotate_left_not_aligned  ( base_node  ** PPup );
//  static void rotate_right_aligned     ( base_node  ** PPup );
//  static void rotate_right_not_aligned ( base_node  ** PPup );
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function :rotate_left_aligned
/// @brief rotate to the left two or three nodes aligned
/// @param [in]PPup : pnode to the pnode to the upper node
/// @return none
/// @remarks
//---------------------------------------------------------------------------
static void rotate_left_aligned    ( base_node  **PPup ) NOEXCEPT
{   //-------------- begin---------------------------
    #if __DEBUG_CNTREE != 0
    assert (PPup != NULL and (*PPup) != NULL );
    #endif
    base_node   *PBlack=*PPup ;

    #if __DEBUG_CNTREE != 0
    assert (PBlack->right != NULL);
    #endif
    base_node  * P1=PBlack->right;

    (*PPup) = P1 ;
    P1->up = PBlack->up ;
    PBlack->up = P1 ;
    P1->N = PBlack->N ;
    PBlack->N -= ( P1->n_right() +1 ) ;
    PBlack->right = P1->left ;
    if ( P1->left != NULL ) P1->left->up = PBlack ;
    P1->left = PBlack ;
};
//---------------------------------------------------------------------------
//  function :rotate_left_not_aligned
/// @brief rotate three nodes not aligned to the left
/// @param [in] PPup : address of the pnode to the upper node
/// @return none
//---------------------------------------------------------------------------
static void rotate_left_not_aligned ( base_node ** PPup ) NOEXCEPT
{   //---------------- begin------------------------
    #if __DEBUG_CNTREE != 0
    assert ( PPup != NULL and (*PPup) != NULL );
    #endif
    base_node  *PBlack = *PPup;

    #if __DEBUG_CNTREE != 0
    assert ( PBlack->right != NULL );
    #endif
    base_node *P1 = PBlack->right ;

    #if __DEBUG_CNTREE != 0
    assert ( P1->left != NULL );
    #endif
    base_node *P2 = P1->left ;

    // Asignaciones
    base_node *  PtrA = P2->left ;
    base_node *  PtrB = P2->right;
    base_node *  PtrC = P1->right;
    base_node *  PtrD = PBlack->left ;
    (*PPup) = P2 ;
    P2->up = PBlack->up ;
    PBlack->up = P1->up = P2 ;
    P2->N = PBlack->N;
    P2->left = PBlack ;
    P2->right = P1 ;
    PBlack->right = PtrA ;
    if ( PtrA != NULL ) PtrA->up = PBlack ;
    PBlack->N = nd(PtrD) + nd(PtrA) + 1 ;
    P1->left = PtrB ;
    if ( PtrB != NULL ) PtrB->up = P1 ;
    P1->N = nd(PtrB) + nd(PtrC) + 1 ;
};
//---------------------------------------------------------------------------
//  function :rotate_right_aligned
/// @brief Rotate two or three aligned nodes to the right
/// @param [in] PPup : address of the pnode to the upper node
/// @return none
//---------------------------------------------------------------------------
static void rotate_right_aligned   ( base_node **PPup ) NOEXCEPT
{   //--------------- begin -------------------
    #if __DEBUG_CNTREE != 0
    assert ( PPup != NULL and (*PPup) != NULL);
    #endif
    base_node *PBlack=*PPup ;

    #if __DEBUG_CNTREE != 0
    assert( (PBlack->left)!= NULL);
    #endif
    base_node * P1=PBlack->left ;

    // Asignaciones
    (*PPup)  = P1 ;
    P1->up = PBlack->up ;
    PBlack->up = P1 ;
    P1->N = PBlack->N ;
    PBlack->N -= ( P1->n_left() + 1 ) ;
    PBlack->left = P1->right ;
    if ( P1->right != NULL ) P1->right->up = PBlack;
    P1->right = PBlack ;
};
//---------------------------------------------------------------------------
//  function :rotate_right_not_aligned
/// @brief Rotate to the right 3 nodes not aligned
/// @param [in] PPup : address to the pnode to the upper node
/// @return none
//---------------------------------------------------------------------------
static void rotate_right_not_aligned ( base_node **PPup ) NOEXCEPT
{   //------------begin---------------
    #if __DEBUG_CNTREE != 0
    assert ( PPup != NULL and  (*PPup) != NULL);
    #endif
    base_node *PBlack = *PPup;

    #if __DEBUG_CNTREE != 0
    assert ( PBlack->left != NULL) ;
    #endif
    base_node * P1 = PBlack->left ;

    #if __DEBUG_CNTREE != 0
    assert ( P1->right != NULL );
    #endif
    base_node *P2 = P1->right ;

    // Asignaciones
    base_node *  PtrA = P1->left;
    base_node *  PtrB = P2->left;
    base_node *  PtrC = P2->right;
    base_node *  PtrD = PBlack->right ;

    (*PPup) = P2 ;

    P2->up = PBlack->up ;
    PBlack->up = P1->up = P2 ;
    P2->N = PBlack->N ;
    P2->left = P1 ;
    P2->right = PBlack ;
    P2->color = black ;
    P1->right = PtrB ;
    if ( PtrB != NULL ) PtrB->up = P1 ;
    P1->N = nd(PtrA) + nd(PtrB) + 1;
    PBlack->left = PtrC ;
    if ( PtrC != NULL) PtrC->up = PBlack ;
    PBlack->N = nd(PtrC) + nd(PtrD)+1 ;
    PBlack->color = red ;
};
//***************************************************************************
};//           E N D      C L A S S      B A S E _ N O D E
//***************************************************************************

//***************************************************************************
//                D E B U G         F U N C T I O N S
//
//***************************************************************************
#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the node
/// @param [in/out] salida : ostream where print
/// @param [in] N : node to print
/// @return reference to salida after the printing
/// @remarks Only for debugger purpose
//---------------------------------------------------------------------------
std::ostream & operator << (std::ostream &salida,const base_node & N )
{   salida<<"["<<( void*) (&N)<<"] ";
    salida<<"left:";
    if( N.left != NULL ) salida<<N.left;
    else                 salida<<"NULL";
    salida<<" right:";
    if ( N.right != NULL ) salida<<N.right;
    else                   salida<<"NULL" ;
    salida<<" up:";
    if ( N.up != NULL )  salida<<N.up;
    else                 salida<<"NULL" ;
    salida<<" N:"<<N.N;
    salida<<" COLOR:";
    if (N.color == black ) salida <<"BLACK";
    else               salida <<"RED";
    return salida ;
};
//---------------------------------------------------------------------------
//  function : internal_print_tree_struct
/// @brief Print all the node struct, with recursive calls
/// @param [in/out] out : ostream where print the information of the tree
///                       structure
/// @param [in] P : Pointer to node
/// @return reference to the ostream after the printing
/// @remarks Only for debugger purpose
//---------------------------------------------------------------------------
std::ostream &  internal_print_tree_struct (std::ostream & out, const base_node *P)
{   //------------ begin --------------------
    if ( P == NULL ) return out;
    if ( P->left == NULL and P->right == NULL) return out;

    out<<(*P)<<std::endl;
    if ( P->left == NULL) out<<"left NULL\n";
    else out<<"left "<<(*P->left)<<std::endl;
    if ( P->right == NULL) out<<"right NULL\n";
    else out<<"right "<<(*P->right)<<std::endl;
    out<<"----------------------------------------------------\n";
    if ( P->left  != NULL) internal_print_tree_struct (out, P->left);
    if ( P->right != NULL) internal_print_tree_struct (out, P->right);
    return out ;
};
//---------------------------------------------------------------------------
//  function :print_tree_struct
/// @brief This function print the node struct beginning in P
/// @param [in/out] out : ostream where print the information of the tree
///                       structure
/// @param [in] P : Pointer to node
/// @return reference to the ostream after the printing
/// @remarks Only for debugger purpose
//---------------------------------------------------------------------------
std::ostream &  print_tree_struct (std::ostream & out, const base_node * P )
{	//------------ Inicio ------------------------
    out<<"                   U P P E R   L E V E L\n";
    out<<"---------------------------------------------------------\n";
    if ( P == NULL ) out<<"NULL\n";
    else
    {   if ( P->left == NULL and P->right == NULL)
            out<<(*P)<<std::endl;
        else internal_print_tree_struct (out, P ) ;
    };
    out<<"\n                   L O W E R   L E V E L \n";
    out<<"----------------------------------------------------------\n";
    return out ;
};
//---------------------------------------------------------------------------
//  function : Colombo
/// @brief Examine  the errors in the node struct
/// @param [in] Father : Pointer to the father node
/// @param [in] P1 : Pointer to the node
/// @param [in] Deep : Deep level
/// @param [in] BlackFather : Indicate if the father is Black
/// @param [in] out : ostream where print the information
/// @return bool (true : OK, false : Error in the struct)
/// @remarks Only for debugger purpose
//---------------------------------------------------------------------------
bool Colombo ( base_node *Father,  base_node *P1,  unsigned Deep,
               bool BlackFather ,  std::ostream & out     )
{   //---------------begin ------------------
   if ( Deep == 0 )
    {   //cout<<"Deep 0 \n" ;
        return ( P1 == NULL ) ;
    };
    if ( P1->up != Father )
    {   out<<"El puntero padre no coincide\n";
        return false ;
    }
    if (P1 == NULL )
    {   out<<"El puntero recibido es NULL \n" ;
        return false ;
    };
    if ( not BlackFather and  P1->color == red  )
    {   out<<"Hay dos nodos rojos seguidos\n";
        out<<(*P1)<<std::endl ;
        return false ;
    };

    // Solo los nodos de profundidad 1 pueden tener punteros NULL
    if ( Deep == 1 )
    {   if (P1->color == red and (P1->left != NULL or P1->right != NULL))
        {   out<<" Un nodo rojo de profundidad 1 no tiene" ;
            out<<" los dos punteros NULL \n" ;
            out<<*P1 ;
            return false ;
        };
    }
    else
    {   if ( P1->left == NULL or P1->right == NULL )
        {   out<<"node de profundidad "<<Deep ;
            out<<"  con punteros NULL \n" ;
            out<<*P1 ;
            return false ;
        };
    };
    if ( Deep == 1 and P1->left == NULL and P1->right == NULL )
        return true ;

    // Llamadas recursivas
    bool is_black =  P1->color == black  ;
    if ( P1->left != NULL )
    {   if ( P1->left->color == black  )
        {   if ( not Colombo( P1,P1->left, Deep-1, is_black,out)) return false ;
        }
        else
        {   if (not Colombo ( P1,P1->left, Deep, is_black,out))   return false ;
        };
    };
    if ( P1->right != NULL )
    {   if ( P1->right->color == black  )
        {   if (not Colombo (P1, P1->right, Deep -1, is_black,out ))
                return false ;
        }
        else
        {   if ( not Colombo ( P1, P1->right, Deep, is_black,out ) )
                return false ;
        };
    };
    return true ;
};
#endif
//***************************************************************************
};//      E N D     F O R E S T    N A M E S P A C E
//
};//      E N D     C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
