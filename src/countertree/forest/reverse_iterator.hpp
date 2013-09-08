//----------------------------------------------------------------------------
/// @file   reverse_iterator.hpp
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
#ifndef __COUNTERTREE_FOREST_REVERSE_ITERATOR_HPP
#define __COUNTERTREE_FOREST_REVERSE_ITERATOR_HPP
#include <boost/countertree/forest/base_iterator.hpp>
#include <iterator>

namespace c_forest = countertree::forest ;
namespace countertree
{
namespace forest
{

template <class tree_type> class const_reverse_iterator ;

//##########################################################################
//                                                                        ##
//                            C L A S S                                   ##
//                                                                        ##
//        R E V E R S E _ I T E R A T O R   < T R E E _ T Y P E >         ##
//                                                                        ##
//##########################################################################
//------------------------------------------------------------------------
/// @class  reverse_iterator
/// @brief  This class represent the iterators of the vector_tree structure
/// @remarks
//------------------------------------------------------------------------
template <typename tree_type>
class reverse_iterator
{
public :
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef c_forest::base_iterator<tree_type>        base_iterator     ;
typedef typename base_iterator::size_type         size_type         ;
typedef typename base_iterator::difference_type   difference_type   ;
typedef typename base_iterator::value_type        value_type        ;
typedef typename base_iterator::pointer           pointer           ;
typedef typename base_iterator::reference         reference         ;
typedef typename base_iterator::const_pointer     const_pointer     ;
typedef typename base_iterator::const_reference   const_reference   ;
typedef std::random_access_iterator_tag           iterator_category ;
typedef c_forest::node <value_type>               node_t            ;
typedef c_forest::const_reverse_iterator<tree_type> const_reverse_iterator ;

//***************************************************************************
//                  F R I E N D   C L A S S
//***************************************************************************
friend class c_forest::const_reverse_iterator<tree_type> ;

private:
//***************************************************************************
//                      V A R I A B L E S
//***************************************************************************
base_iterator B_IT  ;


public :
//***************************************************************************
//  C O N S T R U C T O R , I S _ V A L I D
//
//  reverse_iterator ( void) NOEXCEPT
//  reverse_iterator( node_t*  P1 ,tree_type *  BT1) NOEXCEPT
//  reverse_iterator ( base_iterator A) NOEXCEPT
//  reverse_iterator & operator = ( const reverse_iterator & I) NOEXCEPT
//
//  bool is_valid ( void) const NOEXCEPT
//
//***************************************************************************

//---------------------------------------------------------------------------
//  function : reverse_iterator
/// @brief void constructor
/// @param [in] none
//---------------------------------------------------------------------------
reverse_iterator ( void) NOEXCEPT { };

//---------------------------------------------------------------------------
//  function : reverse_iterator
/// @brief constructor
/// @param [in] P1 : pointer to a node
/// @param [in] BT1 : pointer to a tree_type structure
//---------------------------------------------------------------------------
reverse_iterator( node_t*  P1 ,tree_type *  BT1) NOEXCEPT: B_IT ( P1,BT1){ };

//---------------------------------------------------------------------------
//  function : reverse_iterator
/// @brief copy constructor
/// @param [in] A : base_iterator for to copy
//---------------------------------------------------------------------------
reverse_iterator ( const reverse_iterator &A) NOEXCEPT: B_IT(A.B_IT){};

//---------------------------------------------------------------------------
//  function : reverse_iterator
/// @brief void constructor
/// @param [in] A : base_iterator for to copy
//---------------------------------------------------------------------------
reverse_iterator ( const base_iterator &A) NOEXCEPT: B_IT(A){};

//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] I : reverse_iterator for to copy
/// @return : reference to the object after the asignation
//---------------------------------------------------------------------------
reverse_iterator & operator = ( const reverse_iterator & I) NOEXCEPT
{   B_IT = I.B_IT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : is_valid
/// @brief indicate if the iterator point to this basic_tree
/// @return : true: valid false : invalid
//---------------------------------------------------------------------------
bool is_valid ( void) const NOEXCEPT
{   return ( B_IT.is_valid()) ;
};


//***************************************************************************
//  A R I T H M E T I C    O P E R A T O R S
//
//  reverse_iterator   operator++ ( void  ) NOEXCEPT
//  reverse_iterator   operator++ ( int   ) NOEXCEPT
//  reverse_iterator   operator-- ( void  ) NOEXCEPT
//  reverse_iterator   operator-- ( int   ) NOEXCEPT
//
//  reverse_iterator   operator+= ( signed_type Distance ) NOEXCEPT
//  reverse_iterator   operator-= ( signed_type Distance ) NOEXCEPT
//
//  reverse_iterator   operator + ( signed_type Distance )const NOEXCEPT
//  reverse_iterator   operator - ( signed_type Distance )const NOEXCEPT
//  signed_type  operator - ( const_reverse_iterator<T> I ) const NOEXCEPT
//  signed_type  operator - ( iterator<T> I ) const NOEXCEPT
//
//***************************************************************************

//---------------------------------------------------------------------------
//  function : operator ++
/// @brief pre increment operator
/// @param [in] none
/// @return reference to the iterator incremented
//---------------------------------------------------------------------------
reverse_iterator operator++ ( void  ) NOEXCEPT
{   B_IT.previous();
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator++
/// @brief post increment operator
/// @param [in] int : not used
/// @return iterator before the increment
//---------------------------------------------------------------------------
reverse_iterator  operator++ ( int  )NOEXCEPT
{   reverse_iterator C1 ( *this);
    ++(*this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function . operator--
/// @brief pre decrement operator
/// @param [in] none
/// @return reference to the iterator decremented
//---------------------------------------------------------------------------
reverse_iterator  operator-- ( void  )NOEXCEPT
{   B_IT.next();
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator--
/// @brief post decrement operator
/// @param [in] not used
/// @return iterator before the decrement
//---------------------------------------------------------------------------
reverse_iterator  operator-- ( int  )NOEXCEPT
{   reverse_iterator C1 ( *this);
    --( *this);
    return C1 ;
};

//---------------------------------------------------------------------------
//  function : operator+=
/// @brief self addition operator
/// @param [in] Distance : number of elements to jump forward
/// @return iterator after the addition
//---------------------------------------------------------------------------
reverse_iterator operator+= ( signed_type Distance )NOEXCEPT
{   B_IT.shift ( -Distance);
    return *this ;
};

//---------------------------------------------------------------------------
//  function : operator-=
/// @brief self sustract operator
/// @param [in] Distance : number to elements to jump backward
/// @return iterator after the sustraction
//---------------------------------------------------------------------------
reverse_iterator operator-= ( signed_type Distance )NOEXCEPT
{   B_IT.shift ( Distance) ;
    return *this;
};
//---------------------------------------------------------------------------
//  function : operator+
/// @brief self add operator
/// @param [in] Distance : number to elements to jump forward
/// @return iterator after the addition
//---------------------------------------------------------------------------
reverse_iterator  operator + ( signed_type Distance )const NOEXCEPT
{   reverse_iterator Alfa ( *this);
    Alfa += Distance;
    return Alfa ;
}
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] Distance : number to sustract
/// @return iterator after the decrement
//---------------------------------------------------------------------------
reverse_iterator  operator - ( signed_type Distance )const NOEXCEPT
{   reverse_iterator Alfa ( *this ) ;
    Alfa -= Distance;
    return Alfa ;
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] I : iterator to sustract
/// @return Distance between the two iterators
//---------------------------------------------------------------------------
signed_type operator - ( const_reverse_iterator A ) const NOEXCEPT
{   assert( B_IT.BT == A.B_IT.BT) ;
    return ( B_IT.reverse_pos() - A.B_IT.reverse_pos());
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] Alfa : iterator to sustract
/// @return Distance between the two iterators
//---------------------------------------------------------------------------
signed_type operator - ( reverse_iterator A ) const NOEXCEPT
{   assert ( B_IT.BT == A.B_IT.BT) ;
    return ( B_IT.reverse_pos() - A.B_IT.reverse_pos());
};

//***************************************************************************
//  L O G I C A L     O P E R A T O R S
//
//  bool operator == ( const_reverse_iterator<T> I )const NOEXCEPT
//  bool operator != ( const_reverse_iterator<T> I )const NOEXCEPT
//  bool operator <  ( const_reverse_iterator<T> I )const NOEXCEPT
//  bool operator >  ( const_reverse_iterator<T> I )const NOEXCEPT
//  bool operator <= ( const_reverse_iterator<T> I )const NOEXCEPT
//  bool operator >= ( const_reverse_iterator<T> I )const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] A : iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == ( const_reverse_iterator A )const NOEXCEPT
{   return ( B_IT == A.B_IT);
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != ( const_reverse_iterator I )const NOEXCEPT
{   return not ( *this == I);
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief less than comparison operator
/// @param [in] A : iterator to compare
/// @return true if less
//---------------------------------------------------------------------------
bool operator <  ( const_reverse_iterator A )const NOEXCEPT
{   return ( pos() < A.pos() );
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief greather than comparison operator
/// @param [in] A : iterator to compare
/// @return true if greather
//---------------------------------------------------------------------------
bool operator >  ( const_reverse_iterator A )const NOEXCEPT
{   return ( pos() > A.pos());
};
//---------------------------------------------------------------------------
//  function : operator <=
/// @brief less or equal than  operator
/// @param [in] I : iterator to compare
/// @return true: less or equals
//---------------------------------------------------------------------------
bool operator <= ( const_reverse_iterator A )const NOEXCEPT
{   return (pos() <= A.pos());
};
//---------------------------------------------------------------------------
//  function : operator >=
/// @brief greather or equal   operator
/// @param [in] I : iterator to compare
/// @return true: greather or equal
//---------------------------------------------------------------------------
bool operator >= ( const_reverse_iterator A )const NOEXCEPT
{   return (pos() >= A.pos());
};

//***************************************************************************
//  O P E R A T O R * , O P E R A T O R -> ,
//  P O S , P T R  , P T R _ B A S I C _ T R E E
//
//  T &         operator * ( void ) NOEXCEPT
//  T *         operator-> ( void ) NOEXCEPT
//
//  signed_type   pos ( void ) const NOEXCEPT
//
//  node<T>*   ptr_node ( void ) NOEXCEPT
//  tree   *   ptr_tree ( void ) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator*
/// @brief dereferenced operator
/// @param [in] none
/// @return reference to the data pointed by the iterator
//---------------------------------------------------------------------------
value_type & operator * ( void ) NOEXCEPT
{   return ( B_IT.operator*() ) ;
};
//---------------------------------------------------------------------------
//  function : operator->
/// @brief dereferenced operator
/// @param [in] none
/// @return pointer to the data pointed by the iterator
//---------------------------------------------------------------------------
value_type * operator-> ( void ) NOEXCEPT
{   return B_IT.operator->() ;
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type pos ( void) const NOEXCEPT
{  return (B_IT.reverse_pos() );
};
//---------------------------------------------------------------------------
//  function : ptr_node
/// @brief return the pointer to the node pointed by the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
node_t*  ptr_node ( void ) NOEXCEPT
{   assert( B_IT.BT != NULL) ;
    return B_IT.P;
};
//---------------------------------------------------------------------------
//  function : ptr_tree
/// @brief return the pointer to the basic_tree contained in the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
tree_type * ptr_tree ( void ) NOEXCEPT
{   return B_IT.BT ;
};

//***************************************************************************
//  S P E C I A L    V A L U E S
//
//  static reverse_iterator end     ( tree_type *  BT) NOEXCEPT
//  static reverse_iterator rend    ( tree_type *  BT) NOEXCEPT
//  static reverse_iterator begin   ( tree_type *  BT) NOEXCEPT
//  static reverse_iterator rbegin  ( tree_type *  BT) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] none
/// @return iterator to the end
//---------------------------------------------------------------------------
static reverse_iterator end ( tree_type *  BT) NOEXCEPT
{   return base_iterator::end( BT);
};
//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static reverse_iterator rend(tree_type *  BT) NOEXCEPT
{   return base_iterator::rend( BT );
};
//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static reverse_iterator begin (tree_type *  BT) NOEXCEPT
{   return base_iterator::begin ( BT);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static reverse_iterator rbegin (tree_type *  BT) NOEXCEPT
{   return base_iterator::rbegin ( BT );
};


//***************************************************************************
};//      E N D     C L A S S     R E V E R S E _ I T E R A T O R
//***************************************************************************


//##########################################################################
//                                                                        ##
//                           C L A S S                                    ##
//                                                                        ##
//  C O N S T _ R E V E R S E _ I T E R A T O R   < T R E E _ T Y P E >   ##
//                                                                        ##
//##########################################################################
//------------------------------------------------------------------------
/// @class  const_reverse_iterator
/// @brief  This class represent the iterators of the vector_tree structure
/// @remarks
//------------------------------------------------------------------------
template <class tree_type>
class const_reverse_iterator
{
public:
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef c_forest::base_iterator<tree_type>        base_iterator       ;
typedef c_forest::const_base_iterator<tree_type>  const_base_iterator ;
typedef typename base_iterator::size_type         size_type           ;
typedef typename base_iterator::difference_type   difference_type     ;
typedef typename base_iterator::value_type        value_type          ;
typedef typename base_iterator::pointer           pointer             ;
typedef typename base_iterator::reference         reference           ;
typedef typename base_iterator::const_pointer     const_pointer       ;
typedef typename base_iterator::const_reference   const_reference     ;
typedef std::random_access_iterator_tag           iterator_category   ;
typedef c_forest::node <value_type>               node_t              ;
typedef c_forest::reverse_iterator<tree_type>     reverse_iterator    ;

//***************************************************************************
//                  F R I E N D     C L A S S
//***************************************************************************
friend class c_forest::reverse_iterator<tree_type>;

private:
//***************************************************************************
//                     V A R I A B L E S
//***************************************************************************
const_base_iterator B_IT ;

public :
//***************************************************************************
//  C O N S T R U C T O R , I S _ V A L I D
//
//  const_reverse_iterator(void)( tree_type *  BT) NOEXCEPT
//  const_reverse_iterator ( const node_t* P1,const tree_type *BT1) NOEXCEPT
//
//  const_reverse_iterator ( const reverse_iterator  C) NOEXCEPT
//  const_reverse_iterator ( const_base_iterator A) NOEXCEPT
//
//  const_reverse_iterator & operator=(const const_reverse_iterator & I) NOEXCEPT
//  const_reverse_iterator & operator=(const reverse_iterator & I) NOEXCEPT
//
//  bool is_valid ( void) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : const_reverse_iterator
/// @brief void constructor
/// @param [in] none
//---------------------------------------------------------------------------
const_reverse_iterator(void) NOEXCEPT{};
//---------------------------------------------------------------------------
//  function : const_reverse_iterator
/// @brief constructor
/// @param [in] P1 : pointer to a node
/// @param [in] BT1 : pointer to a basic_tree structure
//---------------------------------------------------------------------------
const_reverse_iterator ( const node_t* P1,const tree_type *BT1) NOEXCEPT : B_IT (P1,BT1){ };

//---------------------------------------------------------------------------
//  function : const_reverse_iterator
/// @brief constructor from an iterator
/// @param [in] C : iterator to copy
//---------------------------------------------------------------------------
const_reverse_iterator ( const const_reverse_iterator  &C) NOEXCEPT :B_IT (C.B_IT){};

//---------------------------------------------------------------------------
//  function : const_reverse_iterator
/// @brief constructor from an iterator
/// @param [in] C : iterator to copy
//---------------------------------------------------------------------------
const_reverse_iterator ( const reverse_iterator  &C) NOEXCEPT :B_IT (C.B_IT){};

//---------------------------------------------------------------------------
//  function : const_reverse_iterator
/// @brief void constructor
/// @param [in] A : const_tree_iter for to copy
//---------------------------------------------------------------------------
const_reverse_iterator ( const const_base_iterator &A) NOEXCEPT: B_IT(A){};

//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] I : const_reverse_iterator for to copy
/// @return : reference to the object after the asignation
//---------------------------------------------------------------------------
const_reverse_iterator & operator = ( const const_reverse_iterator & I) NOEXCEPT
{   B_IT = I.B_IT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] I : reverse_iterator for to copy
/// @return : reference to the object after the asignation
//---------------------------------------------------------------------------
const_reverse_iterator & operator = ( const reverse_iterator & I) NOEXCEPT
{   B_IT = I.B_IT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : is_valid
/// @brief Indicate if the iterator is pointing a any data structure
/// @return true : is valid
//---------------------------------------------------------------------------
bool is_valid ( void) const NOEXCEPT
{   return B_IT.is_valid() ;
};

//***************************************************************************
//  A R I T H M E T I C    O P E R A T O R S
//
//  const_reverse_iterator     operator++ ( void  ) NOEXCEPT
//  const_reverse_iterator     operator++ ( int   ) NOEXCEPT
//  const_reverse_iterator     operator-- ( void  ) NOEXCEPT
//  const_reverse_iterator     operator-- ( int   ) NOEXCEPT
//
//  const_reverse_iterator  operator+= ( signed_type Distance ) NOEXCEPT
//  const_reverse_iterator  operator-= ( signed_type Distance ) NOEXCEPT
//
//  const_reverse_iterator   operator + ( signed_type Distance )const  NOEXCEPT
//  const_reverse_iterator   operator - ( signed_type Distance )const  NOEXCEPT
//  signed_type        operator - ( const_reverse_iterator I   )const  NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator++
/// @brief post increment operator
/// @param [in] int : not used
/// @return iterator before the increment
//---------------------------------------------------------------------------
const_reverse_iterator  operator++ ( int  ) NOEXCEPT
{   const_reverse_iterator C1 ( *this);
    ++( *this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator ++
/// @brief pre increment operator
/// @param [in] none
/// @return reference to the iterator incremented
//---------------------------------------------------------------------------
const_reverse_iterator  operator++ ( void  ) NOEXCEPT
{   B_IT.previous();
    return *this ;
};
//---------------------------------------------------------------------------
//  function . operator--
/// @brief pre decrement operator
/// @param [in] none
/// @return reference to the iterator decremented
//---------------------------------------------------------------------------
const_reverse_iterator  operator-- ( void  ) NOEXCEPT
{   B_IT.next();
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator--
/// @brief post decrement operator
/// @param [in] not used
/// @return iterator before the decrement
//---------------------------------------------------------------------------
const_reverse_iterator  operator-- ( int  ) NOEXCEPT
{   const_reverse_iterator C1 ( *this);
    --( *this);
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator+=
/// @brief self addition operator
/// @param [in] Distance : number of elements to jump forward
/// @return reference to the iterator after the addition
//---------------------------------------------------------------------------
const_reverse_iterator  operator+= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( -Distance) ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator-=
/// @brief self sustract operator
/// @param [in] Distance : number to elements to jump backward
/// @return reference to the iterator after the sustraction
//---------------------------------------------------------------------------
const_reverse_iterator  operator-= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( Distance );
    return (*this );
};
//---------------------------------------------------------------------------
//  function : operator +
/// @brief add operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in]Distance : Number of positions to shift ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
const_reverse_iterator  operator + ( signed_type Distance )const NOEXCEPT
{   const_reverse_iterator Alfa ( *this);
    return Alfa += Distance;
};
//---------------------------------------------------------------------------
//  function : operator -
/// @brief substraction operator. Return the iterator shifted backward Distance
///        positions without modify the iterator
/// @param [in]Distance : Number of positions to shift ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
const_reverse_iterator  operator - ( signed_type Distance )const NOEXCEPT
{   const_reverse_iterator Alfa ( *this ) ;
    return ( Alfa -= Distance);
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief sustraction of two iterators
/// @param [in] I :  iterator to substract
/// @return distance between the two iterators
//---------------------------------------------------------------------------
signed_type  operator - ( const_reverse_iterator Alfa ) const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT ) ;
    return (  pos()- Alfa.pos() ) ;
};

//***************************************************************************
//  L O G I C A L     O P E R A T O R S
//
//  bool operator == ( const_reverse_iterator I )const  NOEXCEPT
//  bool operator != ( const_reverse_iterator I )const  NOEXCEPT
//  bool operator <  ( const_reverse_iterator I )const  NOEXCEPT
//  bool operator >  ( const_reverse_iterator I )const  NOEXCEPT
//  bool operator <= ( const_reverse_iterator I )const  NOEXCEPT
//  bool operator >= ( const_reverse_iterator I )const  NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] I : iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == ( const_reverse_iterator A )const NOEXCEPT
{   return ( B_IT == A.B_IT);
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != ( const_reverse_iterator A )const NOEXCEPT
{   return not ( *this == A);
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief less than comparison operator
/// @param [in] I : iterator to compare
/// @return true if less
//---------------------------------------------------------------------------
bool operator <  ( const_reverse_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT ) ;
    return ( pos()  <  Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief greather than comparison operator
/// @param [in] I : iterator to compare
/// @return ftrue if greather
//---------------------------------------------------------------------------
bool operator >  ( const_reverse_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT ) ;
    return ( pos() > Alfa.pos() );
};
//---------------------------------------------------------------------------
//  function : operator <=
/// @brief less or equal than  operator
/// @param [in] I : iterator to compare
/// @return true: less or equals
//---------------------------------------------------------------------------
bool operator <= ( const_reverse_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT );
    return (pos() <= Alfa.pos() );
};
//---------------------------------------------------------------------------
//  function : operator >=
/// @brief greather or equal   operator
/// @param [in] I : iterator to compare
/// @return true: greather or equal
//---------------------------------------------------------------------------
bool operator >= ( const_reverse_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT ) ;
    return ( pos() >= Alfa.pos() );
};

//***************************************************************************
//  O P E R A T O R * , O P E R A T O R -> ,
//  P O S , P T R  , P T R _ B A S I C _ T R E E
//
//  const value_type &         operator * ( void ) NOEXCEPT
//  const value_type *         operator-> ( void ) NOEXCEPT
//
//  signed_type   pos ( void ) const NOEXCEPT
//
//  const node_t    * ptr_node ( void ) const NOEXCEPT
//  const tree_type * ptr_tree ( void ) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator*
/// @brief dereferenced operator
/// @param [in] none
/// @return reference to the data pointed by the iterator
//---------------------------------------------------------------------------
const value_type & operator * ( void ) const NOEXCEPT
{   return ( B_IT.operator*() ) ;
};
//---------------------------------------------------------------------------
//  function : operator->
/// @brief dereferenced operator
/// @param [in] none
/// @return pointer to the data pointed by the iterator
//---------------------------------------------------------------------------
const  value_type * operator-> ( void ) const NOEXCEPT
{   return (B_IT.operator->());
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type pos ( void) const NOEXCEPT
{   return ( B_IT.reverse_pos() );
};
//---------------------------------------------------------------------------
//  function : ptr_node
/// @brief return the pointer to the node pointed by the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
const  node_t *  ptr_node ( void ) const NOEXCEPT
{   assert ( B_IT.BT != NULL ) ;
    return B_IT.P;
};

//------------------------------------------------------------------------
//  function : ptr_tree
/// @brief return the pointer to the basic_tree contained in the iterator
/// @param [in] none
/// @return pointer
//------------------------------------------------------------------------
const tree_type * ptr_tree ( void ) const NOEXCEPT
{   return B_IT.BT;
};
//***************************************************************************
//  S P E C I A L    V A L U E S
//
//  static const_reverse_iterator end       (const tree_type *  BT) NOEXCEPT
//  static const_reverse_iterator rend      (const tree_type *  BT) NOEXCEPT
//  static const_reverse_iterator begin     (const tree_type *  BT) NOEXCEPT
//  static const_reverse_iterator rbegin    (const tree_type *  BT) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] none
/// @return iterator to the end
//---------------------------------------------------------------------------
static const_reverse_iterator end (const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::end ( BT);
};
//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_reverse_iterator rend(const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::rend( BT);
};
//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_reverse_iterator begin (const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::begin ( BT);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_reverse_iterator rbegin (const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::rbegin ( BT);
};

//***************************************************************************
};//  E N D     C L A S S     C O N S T _ R E V E R S E _ I T E R A T O R
//***************************************************************************


//##########################################################################
//                                                                        ##
//              E X T E R N A L       O P E R A T O R S                   ##
//                                                                        ##
//##########################################################################


//--------------------------------------------------------------------------
//      A R I T H M E T I C A L     O P E R A T O R S
//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  function : operator+
/// @brief Addition operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in] C1 : iterator to add a Distance
/// @param [in] Distance : Number of positions to shift from C1
///                        ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
template <class tree_type>
inline reverse_iterator<tree_type>
operator + (signed_type C2,reverse_iterator<tree_type> C1) NOEXCEPT
{
    return C1+= C2;
};
//---------------------------------------------------------------------------
//  function : operator+
/// @brief Addition operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in] C1 : iterator to add a Distance
/// @param [in] Distance : Number of positions to shift from C1
///                        ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
template <class tree_type>
inline const_reverse_iterator<tree_type>
operator +(signed_type C2, const_reverse_iterator<tree_type> C1) NOEXCEPT
{
    return C1 += C2 ;
};
#if __DEBUG_CNTREE != 0

template <class tree_type>
std::ostream  & operator << ( std::ostream &salida ,
                              const reverse_iterator<tree_type> & I)
{   salida <<"[ "<<I.is_valid()<<" , ";
    if ( I.is_valid()) salida<<"  Pos:"<<I.pos();
    salida<<"] ";
    return salida ;
};
template <class tree_type>
std::ostream  & operator << ( std::ostream &salida ,
                              const const_reverse_iterator<tree_type> & I)
{   salida <<"[ "<<I.is_valid()<<" , ";
    if ( I.is_valid()) salida<<"  Pos:"<<I.pos();
    salida<<"] ";
    return salida ;
};
#endif

//***************************************************************************
};//     E N D     N A M E S P A C E     F O R E S T
//
};//     E N D     N A M E S P A C E     C O U N T E R T R E E
//***************************************************************************
#endif
