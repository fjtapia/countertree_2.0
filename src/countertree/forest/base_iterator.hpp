//----------------------------------------------------------------------------
/// @file   base_iterator.hpp
/// @brief  This file contains the Iterator and const_iterator definition
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_BASE_ITERATOR_HPP
#define __COUNTERTREE_FOREST_BASE_ITERATOR_HPP

#include <boost/countertree/forest/node.hpp>
#include <boost/countertree/forest/tree.hpp>
#include <iterator>

namespace countertree
{
namespace forest
{
void * const PMIN = (void* ) (size_t) 0 ;
void * const PMAX = ( void*)(~ ((size_t) 0));

template <typename tree_type> struct const_base_iterator;

//##########################################################################
//                                                                        ##
//          C L A S S      B A S E _ I T E R A T O R                      ##
//                                                                        ##
//##########################################################################
//------------------------------------------------------------------------
/// @class  base_iterator
/// @brief  This class represent the iterators of the tree structure
/// @remarks
//------------------------------------------------------------------------
template <typename tree_type>
struct base_iterator
{
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef countertree::common::signed_type        size_type         ;
typedef countertree::common::signed_type        difference_type   ;
typedef typename tree_type::value_type          value_type        ;
typedef       value_type *                      pointer           ;
typedef       value_type &                      reference         ;
typedef const value_type *                      const_pointer     ;
typedef const value_type &                      const_reference   ;
typedef std::random_access_iterator_tag         iterator_category ;
typedef countertree::forest::node <value_type>  node_t              ;

//***************************************************************************
//                      V A R I A B L E S
//***************************************************************************
node_t *  P  ;
tree_type *  BT ;

//***************************************************************************
// B A S E _ I T E R A T O R , O P E R A T O R = , I S _ V A L I D , I S _ M I N E
//
//  base_iterator ( void )NOEXCEPT
//  base_iterator (node_t * P1, tree_type *BT1 ) NOEXCEPT
//  base_iterator ( const base_iterator  &BI) NOEXCEPT
//
//  base_iterator & operator = ( const base_iterator  &BI) NOEXCEPT
//
//  bool is_valid ( void) const NOEXCEPT
//  bool is_mine ( const tree_type * PT) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : base_iterator
/// @brief void constructor
//---------------------------------------------------------------------------
base_iterator ( void )NOEXCEPT: P(NULL), BT ( NULL) {};
//---------------------------------------------------------------------------
//  function : base_iterator
/// @brief  constructor
/// @param [in] P1 : pointer to the node_t
/// @param [in] BT1 : pointer to the tree_type
//---------------------------------------------------------------------------
base_iterator (node_t * P1, tree_type *BT1 ) NOEXCEPT :P ( P1) ,BT ( BT1)
{   //----------------------------- begin -------------------------
     if ( BT == NULL) P = ( node_t*)PMAX;
};
//---------------------------------------------------------------------------
//  function : base_iterator
/// @brief copy constructor
/// @param [in] BI: reference to a const base_iterator
//---------------------------------------------------------------------------
base_iterator ( const base_iterator  &BI) NOEXCEPT :P (BI.P) ,BT ( BI.BT)
{   //----------------------------- begin -------------------------
     if ( BT == NULL) P = ( node_t *)PMAX;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T1 : base_iterator from we copy a base_iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
base_iterator & operator = ( const base_iterator  &BI) NOEXCEPT
{   //--------------------------- begin ------------------------
    P = BI.P ;
    BT = BI.BT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : is_valid
/// @brief indicate if the  pointer to this basic_tree is valid
/// @return : true: valid false : invalid
//---------------------------------------------------------------------------
bool is_valid ( void) const NOEXCEPT
{   return ( BT != NULL) ;
};
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief indicate if the  pointer to this tree is equal to the
///        pointer PT
/// @return : true: equal false : not equal
//---------------------------------------------------------------------------
bool is_mine ( const tree_type * PT) const NOEXCEPT
{   return ( BT == PT) ;
};
//
//***************************************************************************
//  O P E R A T O R *   ,    O P E R A T O R ->
//
//  T &         operator * ( void );
//  T *         operator-> ( void );
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator*
/// @brief dereferenced operator
/// @param [in] none
/// @return reference to the data pointed by the base_iterator
//---------------------------------------------------------------------------
value_type &  operator * ( void ) NOEXCEPT
{   //-------------------- begin ---------------------
    assert ( BT != NULL and P != PMAX and P != PMIN );
    return ( P->data ) ;
};
//---------------------------------------------------------------------------
//  function : operator->
/// @brief dereferenced operator
/// @param [in] none
/// @return pointer to the data pointed by the base_iterator
//---------------------------------------------------------------------------
value_type * operator-> ( void ) NOEXCEPT
{   //-------------------- begin ---------------------
    assert ( BT != NULL and P != PMAX and P != PMIN );
    return (& (P->data)) ;
};
//
//***************************************************************************
//        O P E R A T O R ==  ,   O P E R A T O R !=
//
//  bool operator == ( const_base_iterator<T>  I )const ;
//  bool operator != ( const_base_iterator<T>  I )const ;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] I : iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == ( const_base_iterator<tree_type> I )const NOEXCEPT
{   //------------------------- begin -----------------
    return ( BT == I.BT and P == I.P);
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != ( const_base_iterator<tree_type> I )const NOEXCEPT
{   //------------- begin --------------
    return not ( *this == I);
};
//
//***************************************************************************
//        S I Z E , P O S , R E V E R S E _ P O S
//
//  size_type   size        ( void               ) const;
//  size_type   pos         ( const node_t<T> * P1 ) const;
//  size_type   reverse_pos ( const node_t<T> * P1 ) const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type size ( void ) const NOEXCEPT
{   //------begin-----------
    assert ( BT != NULL );
    return   BT->size();
}
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type pos (  void) const NOEXCEPT
{   //------------ begin -------------------
    assert ( BT != NULL ) ;
    if ( P == PMIN ) return  -1 ;
    return ( P == PMAX ) ? BT->size() : P->get_pos () ;
};
//---------------------------------------------------------------------------
//  function : reverse_pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type reverse_pos ( void ) const NOEXCEPT
{   //------------------------ begin -------------------
    assert ( BT != NULL );
    if ( P == PMIN ) return  BT->size() ;
    return ( P == PMAX ) ? -1 :BT->size() - P->get_pos () -1;
};
//
//***************************************************************************
//           E N D , R E N D , R B E G I N , R E N D
//
//  static base_iterator end     ( basic_tree<T> *  BT )
//  static base_iterator rend    ( basic_tree<T> *  BT )
//  static base_iterator rbegin  ( basic_tree<T> *  BT )
//  static base_iterator begin   ( basic_tree<T> *  BT )
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] none
/// @return iterator to the end
//---------------------------------------------------------------------------
static base_iterator end (tree_type *  BT ) NOEXCEPT
{   //-------------- begin -------------------------
    assert  ( BT != NULL ) ;
    return base_iterator ( (node_t*)PMAX , BT) ;
};
//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static base_iterator rend ( tree_type *  BT ) NOEXCEPT
{   //----------------- begin --------------------------
    assert  ( BT != NULL );
    return base_iterator ( (node_t*)PMIN , BT) ;
};
//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static base_iterator begin ( tree_type  *  BT ) NOEXCEPT
{   //----------------------- begin -----------------------------
    assert ( BT != NULL ) ;
    node_t *  P = node_t::upgrade(BT->first);
    P =  ( P == NULL )? (node_t *)PMAX :P ;
    return base_iterator (  P ,BT);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static base_iterator rbegin ( tree_type *  BT ) NOEXCEPT
{   //----------------------- begin ------------------------
    assert ( BT != NULL ) ;
    node_t *  P = node_t::upgrade(BT->last);
    P = ( P == NULL )? ( node_t *)PMIN :P ;
    return base_iterator ( P , BT );
};
//
//***************************************************************************
//         N E X T , P R E V I O U S ,   S H I F T
//
//  base_iterator next       ( void);
//  base_iterator previous   ( void);
//  base_iterator shift      ( size_type Distance);
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : next
/// @brief Return a pointer to the next element in the container
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
base_iterator next ( void ) NOEXCEPT
{   //-------- begin ------------
    assert ( BT != NULL  and  P != PMAX ) ;
    P = (node_t *) (( P == PMIN ) ? BT->first : P->next() );
    if ( P == NULL ) P = (node_t *)PMAX ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : previous
/// @brief Return a pointer to the previous element in the container
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
base_iterator  previous ( void ) NOEXCEPT
{   //---------------- begin ------------------
    assert ( BT != NULL  and P != PMIN);
    P = ( node_t *)((P == PMAX)? BT->last : P->previous());
    if  ( P == NULL ) P = ( node_t*)PMIN  ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : shift
/// @brief Shift the iterator forward positions
/// @param [in] Distance : positions to go shift ( it can be negative)
/// @return none
//---------------------------------------------------------------------------
base_iterator  shift ( signed_type Distance) NOEXCEPT
{   //--------------------- Inicio -------------------------
    assert ( BT != NULL ) ;
    if ( Distance != 0 )
    {   if (Distance > 0 )
        {
            #if __DEBUG_CNTREE != 0
            assert ( P != PMAX ) ;
            #endif
            if (P == PMIN)
            {   next() ;
                --Distance ;
            };
            if ( Distance != 0 and P != PMAX )
            {   if ((P = (node_t*)P->shift(Distance))== NULL )
                    P = (node_t*)PMAX;
            };
        }
        else
        {
            #if __DEBUG_CNTREE != 0
            assert ( P != PMIN) ;
            #endif
            if (P == PMAX)
            {   previous();
                ++Distance;
            };
            if ( Distance != 0 and P != PMIN)
            {   if ( (P = (node_t*)P->shift(Distance)) == NULL)
                    P = (node_t*)PMIN ;
            };
        };
    };
    return *this ;
};

//**************************************************************************
};//         E N D     C L A S S    B A S E _ I T E R A T O R
//**************************************************************************


//##########################################################################
//                                                                        ##
//     C L A S S     C O N S T _ B A S E _ I T E R A T O R                ##
//                                                                        ##
//##########################################################################
//
//------------------------------------------------------------------------
/// @class  base_iteratorator
/// @brief  This class represent the iterators of the vector_tree structure
/// @remarks
//------------------------------------------------------------------------
template <typename tree_type>
struct const_base_iterator
{
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef typename base_iterator<tree_type>::size_type         size_type         ;
typedef typename base_iterator<tree_type>::difference_type   difference_type   ;
typedef typename base_iterator<tree_type>::value_type        value_type        ;
typedef typename base_iterator<tree_type>::pointer           pointer           ;
typedef typename base_iterator<tree_type>::reference         reference         ;
typedef typename base_iterator<tree_type>::const_pointer     const_pointer     ;
typedef typename base_iterator<tree_type>::const_reference   const_reference   ;
typedef std::random_access_iterator_tag                      iterator_category ;
typedef countertree::forest::node <value_type>               node_t ;

//***************************************************************************
//                      V A R I A B L E S
//***************************************************************************
const node_t * P ;
const tree_type *  BT ;


//***************************************************************************
// C O N S T R U C T O R , O P E R A T O R = , I S _ V A L I D , I S _ M I N E
//
//  const_base_iterator ( void ) NOEXCEPT
//  const_base_iterator(const node_t * P1,const tree_type *BT1) NOEXCEPT
//  const_base_iterator(const const_base_iterator & TI) NOEXCEPT
//  const_base_iterator (const base_iterator<tree_type> &TI) NOEXCEPT
//
//  const_base_iterator & operator =
//                        ( const base_iterator<tree_type> & TI) NOEXCEPT
//  const_base_iterator & operator =
//                        ( const const_base_iterator<tree_type> & TI) NOEXCEPT
//
//  bool is_valid ( void) const ;
//  bool is_mine ( const tree_type * PT) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : const_base_iterator
/// @brief empty constructor
/// @param [in] none
//---------------------------------------------------------------------------
const_base_iterator ( void ) NOEXCEPT:P ( NULL), BT ( NULL) { };
//---------------------------------------------------------------------------
//  function : const_base_iterator
/// @brief  constructor
/// @param [in] P1 : pointer to the node_t
/// @param [in] BT1 : pointer to the basic_tree
//---------------------------------------------------------------------------
const_base_iterator(const node_t * P1,const tree_type *BT1) NOEXCEPT:P (P1),BT (BT1)
{   //----------------------------- begin -------------------------
     if ( BT == NULL) P = (const  node_t*)PMAX;
};
//---------------------------------------------------------------------------
//  function : const_base_iterator
/// @brief copy constructor
/// @param [in] T1 : base_iterator from we generate a const_base_iterator
//---------------------------------------------------------------------------
const_base_iterator(const const_base_iterator & TI) NOEXCEPT:P(TI.P),BT(TI.BT){};

//---------------------------------------------------------------------------
//  function : const_base_iterator
/// @brief void constructor
/// @param [in] T1 : base_iterator from we generate a const_base_iterator
//---------------------------------------------------------------------------
const_base_iterator (const base_iterator<tree_type> &TI) NOEXCEPT
: P ( TI.P ) , BT ( TI.BT ) {  };

//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T1 : base_iterator from we copy a const_base_iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
const_base_iterator & operator = ( const base_iterator<tree_type> & TI) NOEXCEPT
{   //------------------------------ begin ------------------------------
    P = TI.P ;
    BT = TI.BT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T1 : const_base_iterator from we copy a const_base_iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
const_base_iterator & operator = ( const const_base_iterator<tree_type> & TI) NOEXCEPT
{   //------------------------------ begin ------------------------------
    P = TI.P ;
    BT = TI.BT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : is_valid
/// @brief indicate if the iterator point to this basic_tree
/// @return : true: valid false : invalid
//---------------------------------------------------------------------------
bool is_valid ( void) const NOEXCEPT
{   return ( BT != NULL) ;
};
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief indicate if the  pointer to this tree is equal to the
///        pointer PT
/// @return : true: equal false : not equal
//---------------------------------------------------------------------------
bool is_mine ( const tree_type * PT) const NOEXCEPT
{   return ( BT == PT) ;
};
//***************************************************************************
//         O P E R A T O R *   ,  O P E R A T O R ->
//
//  T &         operator * ( void );
//  T *         operator-> ( void );
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator*
/// @brief dereferenced operator
/// @param [in] none
/// @return reference to the data pointed by the iterator
//---------------------------------------------------------------------------
const value_type &  operator * ( void ) const NOEXCEPT
{   //------------------- Begin --------------
    assert (BT != NULL and P != PMAX and P != PMIN) ;
    return (P->data ) ;
};
//---------------------------------------------------------------------------
//  function : operator->
/// @brief dereferenced operator
/// @param [in] none
/// @return pointer to the data pointed by the iterator
//---------------------------------------------------------------------------
const value_type * operator-> ( void ) const NOEXCEPT
{   //------------------- Begin --------------
    assert (BT != NULL and P != PMAX and P != PMIN) ;
    return (& (P->data)) ;
};

//***************************************************************************
//         L O G I C A L     O P E R A T O R S
//
//  bool operator == ( const_base_iterator<T>  I )const ;
//  bool operator != ( const_base_iterator<T>  I )const ;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] I : const_base_iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == (const const_base_iterator &I )const NOEXCEPT
{   //------------------------- begin -----------------
    return ( BT == I.BT and P == I.P);
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : const_base_iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != (const   const_base_iterator &I )const NOEXCEPT
{   //--------------------------- begin --------------------
    return not ( *this == I);
};

//***************************************************************************
//           S I Z E , P O S , R E V E R S E _ P O S
//
//  size_type   size        ( void               ) const;
//  size_type   pos         ( const node_t<T> * P1 ) const;
//  size_type   reverse_pos ( const node_t<T> * P1 ) const;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : size
/// @brief return the of elements
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type size ( void ) const NOEXCEPT
{   //------begin-----------
    assert ( BT != NULL );
    return   BT->size();
}
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type pos (  void) const NOEXCEPT
{   //------------ begin -------------------
    assert ( BT != NULL ) ;
    if ( P == PMIN ) return  -1 ;
    return ( P == PMAX ) ? BT->size() : P->get_pos () ;
};
//---------------------------------------------------------------------------
//  function : reverse_pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type reverse_pos ( void ) const NOEXCEPT
{   //------------------------ begin -------------------
    assert ( BT != NULL );
    if ( P == PMIN ) return  BT->size() ;
    return ( P == PMAX ) ? -1 :BT->size() - P->get_pos () -1;
};

//***************************************************************************
//            E N D , R E N D , R B E G I N , B E G I N
//
//  static const_base_iterator end     ( basic_tree<T> *  BT );
//  static const_base_iterator rend    ( basic_tree<T> *  BT );
//  static const_base_iterator rbegin  ( basic_tree<T> *  BT );
//  static const_base_iterator begin   ( basic_tree<T> *  BT );
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] none
/// @return iterator to the end
//---------------------------------------------------------------------------
static const_base_iterator end ( const tree_type *  BT ) NOEXCEPT
{   //-------------------------- begin -------------------------
    assert ( BT != NULL );
    return const_base_iterator( (const node_t *)PMAX,  BT) ;;
};

//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_base_iterator  rend ( const tree_type *  BT ) NOEXCEPT
{   //------------------------------- begin --------------------------
    assert ( BT != NULL );
    return const_base_iterator ( (const node_t*)PMIN , BT);
};

//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_base_iterator begin ( const tree_type *  BT ) NOEXCEPT
{   //----------------------- begin -----------------------------
    assert ( BT != NULL );
    const node_t *  P = (const node_t *)(BT->first);
    P =  ( P == NULL )? (const node_t *)PMAX :P ;
    return const_base_iterator ( P , BT);
};

//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_base_iterator rbegin ( const tree_type *  BT  ) NOEXCEPT
{   //----------------------- begin ------------------------
    assert ( BT != NULL );
    const node_t*  P = node_t::upgrade(BT->last);
    P = ( P == NULL )? ( const node_t * ) PMIN :P ;
    return const_base_iterator ( P , BT);
};

//***************************************************************************
//            N E X T , P R E V I O U S ,   S H I F T
//
//  void next       ( void);
//  void previous   ( void);
//  void shift      ( size_type Distance);
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : next
/// @brief Return a pointer to the next element in the container
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
const_base_iterator next ( void ) NOEXCEPT
{   //-------- begin ------------
    assert ( BT != NULL  and  P != PMAX ) ;
    P = (const node_t*)((P == PMIN ) ? BT->first : P->next()) ;
    if ( P == NULL ) P = (const node_t*)PMAX ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : previous
/// @brief Return a pointer to the previous element in the container
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
const_base_iterator  previous ( void ) NOEXCEPT
{   //---------------- begin ------------------
    assert ( BT != NULL  and P != PMIN);
    P = ( const node_t*)((P == PMAX)? BT->last : P->previous());
    if  ( P == NULL ) P = ( const node_t*)PMIN  ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : shift
/// @brief Shift the iterator forward positions
/// @param [in] Distance : positions to go shift ( it can be negative)
/// @return none
//---------------------------------------------------------------------------
const_base_iterator shift ( signed_type Distance) NOEXCEPT
{   //--------------------- Inicio -------------------------
    assert  ( BT != NULL );
    if ( Distance != 0 )
    {   if (Distance > 0 )
        {
            #if __DEBUG_CNTREE != 0
            assert ( P != PMAX ) ;
            #endif
            if (P == PMIN)
            {   next() ;
                --Distance ;
            };
            if ( Distance != 0 and P != PMAX )
            {   if ((P = (const node_t*)(P->shift(Distance)))== NULL )
                    P = (const node_t*)PMAX;
            };
        }
        else
        {
            #if __DEBUG_CNTREE != 0
            assert ( P != PMIN) ;
            #endif
            if (P == PMAX)
            {   previous();
                ++Distance;
            };
            if ( Distance != 0 and P != PMIN)
            {   if ( (P = (const node_t*)(P->shift(Distance)) ) == NULL)
                    P = (const node_t*)PMIN ;
            };
        };
    };
    return *this ;
};
//***************************************************************************
};//   E N D     S T R U C T   C O N S T _ B A S E _ I T E R A T O R
//***************************************************************************

//***************************************************************************
};//     E N D     N A M E S P A C E     F O R E S T
//
};//     E N D     N A M E S P A C E     C O U N T E R T R E E
//***************************************************************************
#endif
