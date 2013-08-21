//----------------------------------------------------------------------------
/// @file   iterator.hpp
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
#ifndef __COUNTERTREE_FOREST_ITERATOR_HPP
#define __COUNTERTREE_FOREST_ITERATOR_HPP
#include <boost/countertree/forest/base_iterator.hpp>
#include <iterator>

namespace c_forest = countertree::forest;
namespace countertree
{
namespace forest
{

template <class tree_type> class const_iterator ;
//##########################################################################
//                                                                        ##
//                        C L A S S                                       ##
//                                                                        ##
//               I T E R A T O R  < T R E E _ T Y P E >                   ##
//                                                                        ##
//##########################################################################

//------------------------------------------------------------------------
/// @class  iterator
/// @brief  This class represent the iterators of the vector_tree structure
/// @remarks
//------------------------------------------------------------------------
template <typename tree_type>
class iterator
{
public :
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef c_forest::base_iterator<tree_type>          base_iterator       ;
typedef c_forest::const_iterator<tree_type>         const_iterator      ;
typedef typename base_iterator::size_type           size_type           ;
typedef typename base_iterator::difference_type     difference_type     ;
typedef typename base_iterator::value_type          value_type          ;
typedef typename base_iterator::pointer             pointer             ;
typedef typename base_iterator::reference           reference           ;
typedef typename base_iterator::const_pointer       const_pointer       ;
typedef typename base_iterator::const_reference     const_reference     ;
typedef std::random_access_iterator_tag             iterator_category   ;
typedef c_forest::node <value_type>                 node_t                ;

//***************************************************************************
//                  F R I E N D   C L A S S
//***************************************************************************
friend class c_forest::const_iterator<tree_type>  ;

private:
//***************************************************************************
//                      V A R I A B L E S
//***************************************************************************
base_iterator B_IT ;


public :
//***************************************************************************
//  C O N S T R U C T O R , I S _ V A L I D
//
//  iterator              ( void                                ) NOEXCEPT
//  iterator              ( node*  P1 ,tree_type *  BT1         ) NOEXCEPT
//  iterator              ( const base_iterator <tree_type>  &K ) NOEXCEPT
//  iterator & operator = ( const iterator & I                  ) NOEXCEPT
//  bool       is_valid   ( void                                ) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : iterator
/// @brief void constructor
/// @param [in] none
//---------------------------------------------------------------------------
iterator ( void) NOEXCEPT{ };
//---------------------------------------------------------------------------
//  function : iterator
/// @brief constructor
/// @param [in] P1 : pointer to a node_t
/// @param [in] BT1 : pointer to a basic_tree structure
//---------------------------------------------------------------------------
iterator( node_t*  P1 ,tree_type *  BT1) NOEXCEPT:B_IT ( P1,BT1)
{   //--------------------- begin -----------------------
    if ( B_IT.BT == NULL) B_IT. P = ( node_t*)PMAX;
};
//---------------------------------------------------------------------------
//  function : iterator
/// @brief constructor from an iterator
/// @param [in] C : iterator to copy
//---------------------------------------------------------------------------
iterator (const  iterator  &C) NOEXCEPT :B_IT ( C.B_IT){};
//---------------------------------------------------------------------------
//  function : iterator
/// @brief copy constructor
/// @param [in] K : tree_iter for to create an iterator
//---------------------------------------------------------------------------
iterator( const base_iterator   &K ) NOEXCEPT:B_IT ( K) {};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T1 : terator from we copy a base_iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
iterator & operator = ( const iterator & I ) NOEXCEPT
{   B_IT = I.B_IT ;
    return *this ;
}
//---------------------------------------------------------------------------
//  function : is_valid
/// @brief indicate if the iterator point to this basic_tree
/// @return : true: valid false : invalid
//---------------------------------------------------------------------------
bool is_valid ( void) const NOEXCEPT
{   return B_IT.is_valid() ;
};
//
//***************************************************************************
//  A R I T H M E T I C    O P E R A T O R S
//
//  iterator   operator++ ( void  );
//  iterator   operator++ ( int   );
//  iterator   operator-- ( void  );
//  iterator   operator-- ( int   );
//
//  iterator   operator+= ( signed_type Distance );
//  iterator   operator-= ( signed_type Distance );
//
//  iterator   operator + ( signed_type Distance )const ;
//  iterator   operator - ( signed_type Distance )const ;
//  signed_type  operator - ( const_iterator<T> I ) const;
//  signed_type  operator - ( iterator<T> I ) const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator ++
/// @brief pre increment operator
/// @param [in] none
/// @return reference to the iterator incremented
//---------------------------------------------------------------------------
iterator operator++ ( void  ) NOEXCEPT
{   B_IT.next() ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator++
/// @brief post increment operator
/// @param [in] int : not used
/// @return iterator before the increment
//---------------------------------------------------------------------------
iterator operator++ ( int  ) NOEXCEPT
{   iterator C1 ( *this);
    ++(*this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator--
/// @brief pre decrement operator
/// @param [in] none
/// @return reference to the iterator decremented
//---------------------------------------------------------------------------
iterator  operator-- ( void  ) NOEXCEPT
{   B_IT.previous();
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator--
/// @brief post decrement operator
/// @param [in] not used
/// @return iterator before the decrement
//---------------------------------------------------------------------------
iterator  operator-- ( int  ) NOEXCEPT
{   iterator C1 ( *this);
    --(*this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator+=
/// @brief self addition operator
/// @param [in] Distance : number of elements to jump forward
/// @return iterator after the addition
//---------------------------------------------------------------------------
iterator operator+= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( Distance);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator-=
/// @brief self sustract operator
/// @param [in] Distance : number to elements to jump backward
/// @return iterator after the sustraction
//---------------------------------------------------------------------------
iterator operator-= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( -Distance) ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator+
/// @brief self add operator
/// @param [in] Distance : number to elements to jump forward
/// @return iterator after the addition
//---------------------------------------------------------------------------
iterator operator + ( signed_type Distance )const NOEXCEPT
{   iterator Alfa ( *this);
    return ( Alfa += Distance);
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] Distance : number to sustract
/// @return iterator after the decrement
//---------------------------------------------------------------------------
iterator  operator - ( signed_type Distance )const NOEXCEPT
{   iterator Alfa ( *this ) ;
    return (Alfa -= Distance);
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] I : iterator to sustract
/// @return Distance between the two iterators
//---------------------------------------------------------------------------
signed_type operator - (const_iterator Alfa ) const NOEXCEPT
{   return ( B_IT.pos() - Alfa.B_IT.pos() ) ;
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief post sustract operator
/// @param [in] Alfa : iterator to sustract
/// @return Distance between the two iterators
//---------------------------------------------------------------------------
signed_type operator - ( iterator Alfa ) const NOEXCEPT
{   return ( B_IT.pos() - Alfa.B_IT.pos() ) ;
};

//
//***************************************************************************
//  L O G I C A L     O P E R A T O R S
//
//  bool operator == ( const_iterator I )const NOEXCEPT
//  bool operator != ( const_iterator I )const NOEXCEPT
//  bool operator <  ( const_iterator I )const NOEXCEPT
//  bool operator >  ( const_iterator I )const NOEXCEPT
//  bool operator <= ( const_iterator I )const NOEXCEPT
//  bool operator >= ( const_iterator I )const NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] Alfa : iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == ( const_iterator Alfa )const NOEXCEPT
{  return ( B_IT == Alfa.B_IT);
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != (const_iterator I )const NOEXCEPT
{   return not (*this == I);
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief less than comparison operator
/// @param [in] Alfa : iterator to compare
/// @return true if less
//---------------------------------------------------------------------------
bool operator <  ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() < Alfa.pos() );
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief greather than comparison operator
/// @param [in] Alfa : iterator to compare
/// @return ftrue if greather
//---------------------------------------------------------------------------
bool operator >  ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT== Alfa.B_IT.BT) ;
    return ( pos() > Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator <=
/// @brief less or equal than  operator
/// @param [in] Alfa : iterator to compare
/// @return true: less or equals
//---------------------------------------------------------------------------
bool operator <= ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() <= Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator >=
/// @brief greather or equal   operator
/// @param [in] Alfa : iterator to compare
/// @return true: greather or equal
//---------------------------------------------------------------------------
bool operator >= ( const_iterator Alfa )const NOEXCEPT
{   assert( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() >= Alfa.pos());
};

//***************************************************************************
//  O P E R A T O R * , O P E R A T O R -> ,
//  P O S , P T R  , P T R _ B A S I C _ T R E E
//
//  T &         operator * ( void )NOEXCEPT
//  T *         operator-> ( void )NOEXCEPT
//
//  signed_type   pos ( void ) const NOEXCEPT
//
//  node_t<T>*   ptr_node ( void ) NOEXCEPT
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
{   return ( B_IT.operator-> ()) ;
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position counting from the first element
//---------------------------------------------------------------------------
signed_type pos ( void) const  NOEXCEPT
{   return  B_IT.pos();
};
//---------------------------------------------------------------------------
//  function : ptr_node
/// @brief return the pointer to the node_t pointed by the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
node_t *  ptr_node ( void ) NOEXCEPT
{   assert ( B_IT.BT != NULL ) ;
    return B_IT.P;
};
//---------------------------------------------------------------------------
//  function : ptr_tree
/// @brief return the pointer to the basic_tree contained in the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
tree_type * ptr_tree ( void ) NOEXCEPT
{   return B_IT.BT;
};

//***************************************************************************
//              S P E C I A L    V A L U E S
//
//  static iterator end     ( tree_type *  BT) NOEXCEPT
//  static iterator rend    ( tree_type *  BT) NOEXCEPT
//  static iterator begin   ( tree_type *  BT) NOEXCEPT
//  static iterator rbegin  ( tree_type *  BT) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] V : iterator for to extract the address of the basic_tree
/// @return iterator to the end
//---------------------------------------------------------------------------
static iterator end ( tree_type *  BT) NOEXCEPT
{   return base_iterator::end ( BT);
};
//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] V : iterator for to extract the address of the basic_tree
/// @return iterator
//---------------------------------------------------------------------------
static iterator rend(tree_type *  BT) NOEXCEPT
{   return base_iterator::rend (BT);
};
//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] V : iterator for to extract the address of the basic_tree
/// @return iterator
//---------------------------------------------------------------------------
static iterator begin (tree_type *  BT) NOEXCEPT
{   return base_iterator::begin ( BT);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] V : iterator for to extract the address of the basic_tree
/// @return iterator
//---------------------------------------------------------------------------
static iterator rbegin (tree_type *  BT) NOEXCEPT
{   return base_iterator::rbegin ( BT);
};

//***************************************************************************
};//         E N D     C L A S S     I T E R A T O R
//***************************************************************************


//##########################################################################
//                                                                        ##
//                              C L A S S                                 ##
//                                                                        ##
//           C O N S T _ I T E R A T O R < T R E E _ T Y P E >            ##
//                                                                        ##
//##########################################################################
//------------------------------------------------------------------------
/// @class  const_iterator
/// @brief  This class represent the iterators of the vector_tree structure
/// @remarks
//------------------------------------------------------------------------
template <typename  tree_type>
class const_iterator
{
public:
//***************************************************************************
//                    D E F I N I T I O N S
//***************************************************************************
typedef c_forest::base_iterator<tree_type>           base_iterator       ;
typedef c_forest::const_base_iterator<tree_type>     const_base_iterator ;
typedef c_forest::iterator<tree_type>                iterator            ;
typedef typename base_iterator::size_type           size_type           ;
typedef typename base_iterator::difference_type     difference_type     ;
typedef typename base_iterator::value_type          value_type          ;
typedef typename base_iterator::pointer             pointer             ;
typedef typename base_iterator::reference           reference           ;
typedef typename base_iterator::const_pointer       const_pointer       ;
typedef typename base_iterator::const_reference     const_reference     ;
typedef std::random_access_iterator_tag             iterator_category   ;
typedef c_forest::node <value_type>                           node_t                ;

//***************************************************************************
//                  F R I E N D     C L A S S
//***************************************************************************
friend class c_forest::iterator<tree_type>;


private:
//***************************************************************************
//                     V A R I A B L E S
//***************************************************************************
const_base_iterator B_IT ;


public :
//***************************************************************************
//  C O N S T R U C T O R , I S _ V A L I D
//
//  const_iterator(void) NOEXCEPT
//  const_iterator (const node_t* P1,const tree_type *BT1) NOEXCEPT
//  const_iterator (const  iterator  &C) NOEXCEPT
//  const_iterator (const  const_iterator &C) NOEXCEPT
//  const_iterator ( const_base_iterator  CB_IT ) NOEXCEPT
//
//  const_iterator & operator = ( const const_iterator & I) NOEXCEPT
//  const_iterator & operator = ( const iterator & I) NOEXCEPT
//
//  bool is_valid ( void) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : const_iterator
/// @brief void constructor
/// @param [in] none
//---------------------------------------------------------------------------
const_iterator(void) NOEXCEPT {  };
//---------------------------------------------------------------------------
//  function : const_iterator
/// @brief constructor
/// @param [in] P1 : pointer to a node_t
/// @param [in] BT1 : pointer to a basic_tree structure
//---------------------------------------------------------------------------
const_iterator (const node_t* P1,const tree_type *BT1) NOEXCEPT:B_IT (P1,BT1)
{   if ( B_IT.BT == NULL ) B_IT.P = (const node_t*) PMAX;
};
//---------------------------------------------------------------------------
//  function : const_iterator
/// @brief constructor from an iterator
/// @param [in] C : iterator to copy
//---------------------------------------------------------------------------
const_iterator (const  iterator  &C) NOEXCEPT :B_IT ( C.B_IT){};
//---------------------------------------------------------------------------
//  function : const_iterator
/// @brief copy constructor
/// @param [in] C : iterator to copy
//---------------------------------------------------------------------------
const_iterator (const  const_iterator &C) NOEXCEPT :B_IT ( C.B_IT){};
//---------------------------------------------------------------------------
//  function : const_iterator
/// @brief void constructor
/// @param [in] CB_IT : const_tree_iter for to construct the const_iterator
//---------------------------------------------------------------------------
const_iterator( const_base_iterator CB_IT ) NOEXCEPT:B_IT ( CB_IT ){};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] I : const_iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
const_iterator & operator = ( const const_iterator & I) NOEXCEPT
{   B_IT = I.B_IT ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator from an iterator
/// @param [in] I : iterator
/// @return reference to the actual object
//---------------------------------------------------------------------------
const_iterator & operator = ( const iterator & I) NOEXCEPT
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
//  const_iterator     operator++ ( void  );
//  const_iterator     operator++ ( int   );
//  const_iterator     operator-- ( void  );
//  const_iterator     operator-- ( int   );
//
//  const_iterator  operator+= ( signed_type Distance );
//  const_iterator  operator-= ( signed_type Distance );
//
//  const_iterator   operator + ( signed_type Distance )const ;
//  const_iterator   operator - ( signed_type Distance )const ;
//  signed_type        operator - ( const_iterator I   )const ;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator++
/// @brief post increment operator
/// @param [in] int : not used
/// @return const_iterator before the increment
//---------------------------------------------------------------------------
const_iterator  operator++ ( int  ) NOEXCEPT
{   const_iterator C1 ( *this);
    ++(*this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator ++
/// @brief pre increment operator
/// @param [in] none
/// @return reference to the const_iterator incremented
//---------------------------------------------------------------------------
const_iterator  operator++ ( void  ) NOEXCEPT
{   B_IT.next() ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function . operator--
/// @brief pre decrement operator
/// @param [in] none
/// @return reference to the const_iterator decremented
//---------------------------------------------------------------------------
const_iterator  operator-- ( void  ) NOEXCEPT
{   B_IT.previous();
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator--
/// @brief post decrement operator
/// @param [in] not used
/// @return const_iterator before the decrement
//---------------------------------------------------------------------------
const_iterator  operator-- ( int  ) NOEXCEPT
{   const_iterator C1 ( *this);
    --(*this) ;
    return C1 ;
};
//---------------------------------------------------------------------------
//  function : operator+=
/// @brief self addition operator
/// @param [in] Distance : number of elements to jump forward
/// @return reference to the const_iterator after the addition
//---------------------------------------------------------------------------
const_iterator  operator+= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( Distance);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator-=
/// @brief self sustract operator
/// @param [in] Distance : number to elements to jump backward
/// @return reference to the const_iterator after the sustraction
//---------------------------------------------------------------------------
const_iterator  operator-= ( signed_type Distance ) NOEXCEPT
{   B_IT.shift ( -Distance);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator +
/// @brief add operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in]Distance : Number of positions to shift ( it can be negative)
/// @return const_iterator
//---------------------------------------------------------------------------
const_iterator  operator + ( signed_type Distance )const NOEXCEPT
{   const_iterator Alfa ( *this);
    return Alfa += Distance;
};
//---------------------------------------------------------------------------
//  function : operator -
/// @brief substraction operator. Return the iterator shifted backward Distance
///        positions without modify the iterator
/// @param [in]Distance : Number of positions to shift ( it can be negative)
/// @return const_iterator
//---------------------------------------------------------------------------
const_iterator  operator - ( signed_type Distance )const NOEXCEPT
{   const_iterator Alfa ( *this ) ;
    return ( Alfa -= Distance);
};
//---------------------------------------------------------------------------
//  function : operator-
/// @brief sustraction of two iterators
/// @param [in] I :  iterator to substract
/// @return distance between the two const_iterators
//---------------------------------------------------------------------------
signed_type  operator - ( const_iterator Alfa ) const NOEXCEPT
{   assert ( B_IT.BT ==  Alfa.B_IT.BT ) ;
    return ( pos() - Alfa.pos() ) ;
};

//***************************************************************************
//  L O G I C A L     O P E R A T O R S
//
//  bool operator == ( const_iterator I )const ;
//  bool operator != ( const_iterator I )const ;
//  bool operator <  ( const_iterator I )const ;
//  bool operator >  ( const_iterator I )const ;
//  bool operator <= ( const_iterator I )const ;
//  bool operator >= ( const_iterator I )const ;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equal comparison operator
/// @param [in] I : iterator to compare
/// @return true if equals
//---------------------------------------------------------------------------
bool operator == ( const_iterator Alfa )const NOEXCEPT
{   return ( B_IT == Alfa.B_IT );
};
//---------------------------------------------------------------------------
//  function : operator!=
/// @brief not equal comparison operator
/// @param [in] I : iterator to compare
/// @return false if equals
//---------------------------------------------------------------------------
bool operator != ( const_iterator I )const NOEXCEPT
{   return not ( *this == I);
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief less than comparison operator
/// @param [in] I : iterator to compare
/// @return true if less
//---------------------------------------------------------------------------
bool operator <  ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT)  ;
    return ( pos() < Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator<
/// @brief greather than comparison operator
/// @param [in] I : iterator to compare
/// @return ftrue if greather
//---------------------------------------------------------------------------
bool operator >  ( const_iterator Alfa )const NOEXCEPT
{   //----------------------- begin ----------------------
    assert ( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() > Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator <=
/// @brief less or equal than  operator
/// @param [in] I : iterator to compare
/// @return true: less or equals
//---------------------------------------------------------------------------
bool operator <= ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() <= Alfa.pos());
};
//---------------------------------------------------------------------------
//  function : operator >=
/// @brief greather or equal   operator
/// @param [in] I : iterator to compare
/// @return true: greather or equal
//---------------------------------------------------------------------------
bool operator >= ( const_iterator Alfa )const NOEXCEPT
{   assert ( B_IT.BT == Alfa.B_IT.BT) ;
    return ( pos() >= Alfa.pos());
};

//***************************************************************************
//  O P E R A T O R * , O P E R A T O R -> ,
//  P O S , P T R  , P T R _ B A S I C _ T R E E
//
//  const T &         operator * ( void );
//  const T *         operator-> ( void );
//
//  signed_type   pos ( void ) const;
//
//  const node_t<T>*       ptr_node ( void ) const;
//  const basic_tree<T> *   ptr_tree ( void ) const;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator*
/// @brief dereferenced operator
/// @param [in] none
/// @return reference to the data pointed by the iterator
//---------------------------------------------------------------------------
const value_type & operator * ( void )  NOEXCEPT
{   return ( B_IT.operator*() ) ;
};
//---------------------------------------------------------------------------
//  function : operator->
/// @brief dereferenced operator
/// @param [in] none
/// @return pointer to the data pointed by the iterator
//---------------------------------------------------------------------------
const value_type * operator-> ( void )  NOEXCEPT
{   return (B_IT.operator->());
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief return the position of the iterator in the data structure
/// @param [in] none
/// @return position
//---------------------------------------------------------------------------
signed_type pos ( void) const NOEXCEPT
{  return B_IT.pos() ;
};
//---------------------------------------------------------------------------
//  function : ptr_node
/// @brief return the pointer to the node_t pointed by the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
const  node_t *  ptr_node ( void ) const NOEXCEPT
{   assert ( B_IT.BT != NULL ) ;
    return B_IT.P;
};

//---------------------------------------------------------------------------
//  function : ptr_tree
/// @brief return the pointer to the basic_tree contained in the iterator
/// @param [in] none
/// @return pointer
//---------------------------------------------------------------------------
const tree_type * ptr_tree ( void ) const NOEXCEPT
{   return B_IT.BT;
};
//***************************************************************************
//  S P E C I A L    V A L U E S
//
//  static const_iterator end       (const basic_tree<T> *  BT );
//  static const_iterator rend      (const basic_tree<T> *  BT);
//  static const_iterator begin     (const basic_tree<T> *  BT);
//  static const_iterator rbegin    (const basic_tree<T> *  BT);
//
//  static const_iterator end       (const_iterator  V);
//  static const_iterator rend      (const_iterator  V);
//  static const_iterator begin     (const_iterator  V);
//  static const_iterator rbegin    (const_iterator  V);
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : end
/// @brief return the iterator to the next position after the last in
///        the data structure
/// @param [in] none
/// @return iterator to the end
//---------------------------------------------------------------------------
static const_iterator end (const tree_type *  BT) NOEXCEPT
{   return  const_base_iterator::end(BT );
};
//---------------------------------------------------------------------------
//  function : rend
/// @brief return the iterator to the previous element to the first in
///        the data structure
/// @param [in] none
/// @return iterator
//
static const_iterator rend(const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::rend ( BT);
};
//---------------------------------------------------------------------------
//  function : begin
/// @brief iterator to the first element in the data structure. If the
///        data structure is empty return end()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_iterator begin (const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::begin ( BT);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @brief iterator to the last  element of the data structure. If the
///        data structure is empty return rend()
/// @param [in] none
/// @return iterator
//---------------------------------------------------------------------------
static const_iterator rbegin (const tree_type *  BT) NOEXCEPT
{   return const_base_iterator::rbegin ( BT);
};

//***************************************************************************
};//     E N D     C L A S S     C O N S T _ I T E R A T O R
//***************************************************************************


//##########################################################################
//                                                                        ##
//              E X T E R N A L       O P E R A T O R S                   ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
//  function : operator+
/// @brief Addition operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in] C1 : iterator to add a Distance
/// @param [in] Distance : Number of positions to shift from C1 ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
template <class tree_type>
inline iterator<tree_type> operator + ( signed_type C2, iterator<tree_type> C1) NOEXCEPT
{   return C1+= C2;
};
//---------------------------------------------------------------------------
//  function : operator+
/// @brief Addition operator. Return the iterator shifted forward Distance
///        positions without modify the iterator
/// @param [in] C1 : iterator to add a Distance
/// @param [in] Distance : Number of positions to shift from C1 ( it can be negative)
/// @return iterator
//---------------------------------------------------------------------------
template <class tree_type>
inline const_iterator<tree_type> operator + ( signed_type C2,
                                              const_iterator<tree_type> C1) NOEXCEPT
{   return C1 += C2 ;
};

#if __DEBUG_CNTREE != 0
template <class tree_type>
std::ostream  & operator << ( std::ostream &salida , const iterator<tree_type> & I)
{   salida <<"[ "<<I.is_valid()<<" , ";
    if ( I.is_valid()) salida<<"  Pos:"<<I.pos();
    salida<<"] ";
    return salida ;
};
template <class tree_type>
std::ostream  & operator << ( std::ostream &salida , const const_iterator<tree_type> & I)
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
//****************************************************************************
#endif
