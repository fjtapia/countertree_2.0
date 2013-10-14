//----------------------------------------------------------------------------
/// @file   cntree_vector.hpp
/// @brief  This file contains the implementation of the cntree_vector
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_CNTREE_VECTOR_HPP
#define __COUNTERTREE_FOREST_CNTREE_VECTOR_HPP

#include <memory>
#include <functional>
#include <atomic>
#include <mutex>
#include <thread>
#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/forest/tree.hpp>
#include <boost/countertree/forest/iterator.hpp>
#include <boost/countertree/forest/reverse_iterator.hpp>
#include <boost/countertree/mutex_read_write.hpp>

namespace c_forest = countertree::forest ;
namespace countertree
{

using c_forest::red;
using c_forest::black;
using c_forest::connector ;
using c_forest::PMIN ;
using c_forest::PMAX ;
using std::allocator ;

//***************************************************************************
/// @class  cntree_vector
/// @brief  This class have the same interface than the STL vector,
///         but istead of be a vector is a tree. \n
///         Due to this all the operations ( insert, delete, access)
///         a O( logN). \n
//
/// @remarks
//***************************************************************************
template < typename value_t,
           bool cnc = false,
           typename alloc_t= cntree_allocator<void>
         >
class cntree_vector
{
public:
//***************************************************************************
//                     D E F I N I T I O N S
//***************************************************************************
typedef typename config_fastmutex<cnc>::fastmutex_data   mtx_data ;
typedef mutex_read <mtx_data>                            mtx_read ;
typedef mutex_write<mtx_data>                            mtx_write ;

typedef  countertree::forest::node<value_t>              node_t ;
typedef typename alloc_t::template rebind<node_t>::other node_alloc_t;
typedef c_forest::tree <value_t, node_alloc_t>           tree_t ;

typedef typename tree_t::size_type                       size_type ;
typedef typename tree_t::difference_type                 difference_type ;
typedef       value_t                                    value_type;
typedef       value_type *                               pointer;
typedef const value_type *                               const_pointer;
typedef       value_type &                               reference;
typedef const value_type &                               const_reference;
typedef       alloc_t                                    allocator_type;

typedef typename tree_t::iterator                        iterator;
typedef typename tree_t::const_iterator                  const_iterator;
typedef typename tree_t::reverse_iterator                reverse_iterator;
typedef typename tree_t::const_reverse_iterator          const_reverse_iterator;
typedef std::pair < iterator, bool>                      mypair ;

protected:
//***************************************************************************
//              P R O T E C T E D      V A R I A B L E S
//***************************************************************************
alloc_t       value_alloc ;
node_alloc_t  node_alloc ;
tree_t T ;

public:
//***************************************************************************
//              P U B L I C   V A R I A B L E S
//***************************************************************************
mutable mtx_data BD ;
template <class value_t2, bool cnc2 ,class alloc_t2 > friend class cntree_vector;

//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #  C O N S T R U C T O R , D E S T R U C T O R     #             ##
//       #  O P E R A T O R =    S W A P                    #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//***************************************************************************
//  C O N S T R U C T O R S     A N D    D E S T R U C T O R
//
//  explicit cntree_vector ( const alloc_t &ALLC = alloc_t ())
//
//  cntree_vector ( const cntree_vector & VT )
//  cntree_vector ( cntree_vector && VT)
//
//  template < typename alloc_t2 =alloc_t , bool cnc2=cnc >
//  cntree_vector (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT)
//
//  template < bool cnc2>
//  cntree_vector ( cntree_vector<value_t,cnc2,alloc_t> && VT)
//
//  cntree_vector(unsigned_type n,
//              const value_t& Val=value_t(),
//              const alloc_t &A= alloc_t())
//
//  template <class InputIterator>
//  cntree_vector ( InputIterator it_first ,
//                  InputIterator it_last,
//                  const alloc_t& A = alloc_t() )
//
//  virtual ~cntree_vector (void)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Constructor from an object Allocator
/// @param [in] A : Allocator
//---------------------------------------------------------------------------
explicit cntree_vector ( const alloc_t &ALLC = alloc_t ())
:value_alloc(ALLC),T ( node_alloc){  } ;
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Copy constructor
/// @param [in] VT : cntree_vector from where copy the data
//---------------------------------------------------------------------------
cntree_vector ( const cntree_vector & VT )
{   //----------------------- begin ---------------------
    mtx_read  BR ( VT.BD);
    T.copy  ( VT.T );
};
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Move constructor
/// @param [in] VT : cntree_vector from where copy the data
//---------------------------------------------------------------------------
cntree_vector ( cntree_vector && VT)
:value_alloc( std::move ( VT.value_alloc)), T ( std::move(VT.T)) {  } ;
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief Copy constructor from a vector of different allocator
/// @param [in] VT : cntree_vector from where copy the data
/// @return Reference to the cntree_vector after the copy
//---------------------------------------------------------------------------
template < typename alloc_t2 =alloc_t , bool cnc2=cnc >
cntree_vector (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT)
{   //------------------------- begin ------------------------------------
    typedef typename cntree_vector<value_t,cnc2 ,alloc_t2>::mtx_data mtx_data2 ;
    mutex_read <mtx_data2>  BR (VT.BD);
    T.copy ( VT.T );
};
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Move constructor from a vector with the same allocator and different
//          concurrency
/// @param [in] VT : cntree_vector from where copy the data
//---------------------------------------------------------------------------
template < bool cnc2>
cntree_vector ( cntree_vector<value_t,cnc2,alloc_t> && VT)
: value_alloc( std::move ( VT.value_alloc)),T ( std::move ( VT.T)) { } ;

//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Constructor from a value repeated a number of times and
///         an object Allocator
/// @param [in] n : Number of repetitions
/// @param [in] Val : Value to insert
/// @param [in] A : Allocator
//---------------------------------------------------------------------------
cntree_vector( unsigned_type n,
               const value_t& Val=value_t(),
               const alloc_t &A= alloc_t()) : value_alloc (A)
{   //----------------------------- begin ----------------------------
    T.assign ( n, Val);
} ;
//---------------------------------------------------------------------------
//  function : cntree_vector
/// @brief  Constructor from a pair of iterators and an object
///         Allocator
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] A1 : Allocator
//---------------------------------------------------------------------------
template <class InputIterator>
cntree_vector ( InputIterator it_first ,
                InputIterator it_last,
                const alloc_t& A = alloc_t() ): value_alloc (A)
{   //------------------------- begin ------------------------
    T.assign ( it_first, it_last);
} ;
//---------------------------------------------------------------------------
//  function : ~cntree_vector
/// @brief  Destructor
//---------------------------------------------------------------------------
virtual ~cntree_vector (void)
{   mtx_write BM ( BD);
    BM.wait_no_readers();
    T.clear();
};

//
//***************************************************************************
//  O P E R A T O R = , A S S I G N , C L E A R , S W A P
//
//  cntree_vector & operator= (const cntree_vector &VT)
//
//  template < typename alloc_t2 , bool cnc2>
//  cntree_vector & operator= (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
//
//  template <bool cnc2>
//  cntree_vector & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
//
//  template <class InputIterator>
//  void assign ( InputIterator it_first, InputIterator it_last )
//
//  void assign ( unsigned_type n, const value_t& u )
//
//  template <class InputIterator>
//  void assign_if ( InputIterator it_first, InputIterator it_last,
//                   std::function < bool ( const value_type & )>  M )
//
//  void clear(void)
//  void swap ( cntree_vector  & A ) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] VT : cntree_vector from where copy the data
/// @return Reference to the cntree_vector after the copy
//---------------------------------------------------------------------------
cntree_vector & operator= (const cntree_vector &VT)
{   //--------------------- begin ---------------------
    if ( this == &VT ) return *this ;
    mutex_write_read<mtx_data, mtx_data > MWR ( BD, VT.BD);
    MWR.wait_no_readers();
    T.clear( );
    T.copy  ( VT.T );
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] VT : cntree_vector from where copy the data
/// @return Reference to the cntree_vector after the copy
//---------------------------------------------------------------------------
template < typename alloc_t2 , bool cnc2>
cntree_vector & operator= (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
{   //-------------------------- begin ------------------------------
    //if ( this == &VT ) return *this ;

    typedef typename cntree_vector<value_t,cnc2, alloc_t2>::mtx_data  mtx_data2 ;
    mutex_write_read<mtx_data, mtx_data2 >  MWR ( BD, VT.BD);
    MWR.wait_no_readers();
    T.clear( );
    T.copy  ( VT.T );
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] A : cntree_vector from where move the data
/// @return Reference to the cntree_vector after the copy
//---------------------------------------------------------------------------
template <bool cnc2>
cntree_vector & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
{   //------------------------ begin -------------------------
    //if ( this == &A) return *this ;

    typedef typename cntree_vector<value_t,cnc2, alloc_t>::mtx_data  mtx_data2 ;
    mutex_write_write<mtx_data, mtx_data2 >  MWW ( BD, A.BD);
    MWW.wait_no_readers_first();
    T.clear() ;
    MWW.wait_no_readers_second();
    T.move ( std::move (A.T) );
    return *this ;
}
//---------------------------------------------------------------------------
//  function : assign
/// @brief Assign a range of data,
///        It's like the assignation operator but with several parameters
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void assign ( InputIterator it_first, InputIterator it_last )
{   mtx_write BM ( BD);
    BM.wait_no_readers();
    T.assign ( it_first,it_last) ;
} ;
//---------------------------------------------------------------------------
//  function : assign
/// @brief Assign a range of data, dropping all the elements of the
///        container
///        It's like the assignation operator but with several parameters
/// @param [in] n : number of elements to insert
/// @param [in] u : value to insert
/// @return none
//---------------------------------------------------------------------------
void assign ( unsigned_type n, const value_t& u )
{   mtx_write BM ( BD);
    BM.wait_no_readers();
    T.assign ( n, u );
};
//---------------------------------------------------------------------------
//  function : assign_if
/// @brief Assign a range of data, dropping all the elements of the
///        container
///        It's like the assignation operator but with several parameters
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @param [in] M : function which receives an element and when return true
///                 the element is inserted and when false , not
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator, class Function>
void assign_if ( InputIterator it_first, InputIterator it_last, Function && M )
{   //------------------------------ begin ------------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers();
    T.assign ( it_first,it_last, M ) ;
}
//---------------------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the cntree_vector. It's a function O(N)
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void clear(void)
{   mtx_write BM ( BD);
    BM.wait_no_readers();
    T.clear ( );
};
//---------------------------------------------------------------------------
//  function : swap
/// @brief swap the data between the two cntree_vector
/// @param [in] A : cntree_vector to swap
/// @return none
//---------------------------------------------------------------------------
void swap ( cntree_vector  & A ) NOEXCEPT
{   //------------------ begin ------------------
    if ( this == &A ) return ;
    mutex_write_write<mtx_data, mtx_data > MWW ( BD, A.BD);
    MWW.wait_no_readers_first();
    MWW.wait_no_readers_second();
    T.swap( A.T);
};
//
//***************************************************************************
//  S I Z E , M A X _ S I Z E , R E S I Z E
//  C A P A C I T Y , E M P T Y , R E S E R V E
//
//  signed_type size        ( void  ) const NOEXCEPT
//  signed_type max_size    ( void  ) const NOEXCEPT
//  void        resize      ( unsigned_type sz,value_t c = value_t())
//  signed_type capacity    ( void  ) const NOEXCEPT
//  bool        empty       ( void  ) const NOEXCEPT
//  void        reserve     ( signed_type n ) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements in the cntree_vector
/// @return number of elements in the cntree_vector
//---------------------------------------------------------------------------
signed_type size ( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return T.size() ;
};
//---------------------------------------------------------------------------
//  function :max_size
/// @brief return the maximun size of the container
/// @return maximun size of the container
//---------------------------------------------------------------------------
signed_type max_size (void) const NOEXCEPT
{   mtx_read LM ( BD);
    return ( (std::numeric_limits<signed_type>::max)() );
};
//---------------------------------------------------------------------------
//  function : resize
/// @brief resize the current vector size and change to sz.\n
///        If sz is smaller than the current size, delete elements to end\n
///        If sz is greater than the current size, insert elements to the
///        end with the value c
/// @param [in] sz : new size of the cntree_vector after the resize
/// @param [in] c : Value to insert if sz is greather than the current size
/// @return none
//---------------------------------------------------------------------------
void resize ( signed_type sz,value_t c = value_t())
{   mtx_write BM ( BD);
    BM.wait_no_readers () ;
    T.resize ( sz,c );
};
//---------------------------------------------------------------------------
//  function : capacity
/// @brief return the maximun size of the container
/// @return maximun size of the container
//---------------------------------------------------------------------------
signed_type capacity ( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return ( (std::numeric_limits<signed_type>::max)() );
};
//---------------------------------------------------------------------------
//  function : empty
/// @brief indicate if the map is empty
/// @return true if the map is empty, false in any other case
//---------------------------------------------------------------------------
bool empty ( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return (T.size() == 0) ;
};
//---------------------------------------------------------------------------
//  function : reserve
/// @brief Change the capacity for to contain , at least n elements
/// @param [in] n : number of elements for the new capacity
/// @return none
/// @remarks This function has not utility. It is provided only for
///          compatibility with the STL vector interface
//---------------------------------------------------------------------------
void reserve ( signed_type n ) NOEXCEPT {};
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #   A C C E S S    T O   T H E   E L E M E N T S   #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//***************************************************************************
//  A T , O P E R A T O R [ ] , F R O N T , B A C K
//
//  value_t       &     at ( signed_type Pos ) NOEXCEPT
//  const value_t &     at ( signed_type Pos)const NOEXCEPT
//
//  value_t       &     operator[] ( signed_type Pos) NOEXCEPT
//  const value_t &     operator[] ( signed_type Pos)const NOEXCEPT
//
//  value_t       &     front (void ) NOEXCEPT
//  const value_t &     front ( void) const NOEXCEPT
//
//  value_t       &     back ( void) NOEXCEPT
//  const value_t &     back (void ) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : at
/// @brief  Checked access to an element by their position in the cntree_vector
/// @param  [in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This operation is  O (log(N))
//---------------------------------------------------------------------------
value_t & at  ( signed_type Pos ) NOEXCEPT
{   mtx_read LM ( BD);
    return T [Pos];
};
//---------------------------------------------------------------------------
//  function : at
/// @brief  Checked access to an element by their position in the cntree_vector
/// @param  [in] Pos : Position to read
/// @return Const reference to the object selected
/// @remarks This operation is O (log(N))
//---------------------------------------------------------------------------
const value_t & at ( signed_type Pos)const NOEXCEPT
{   mtx_read LM ( BD);
    return T[Pos];
};
//---------------------------------------------------------------------------
//  function : operator[ ]
/// @brief  Checked access to an element by their position in the cntree_vector
/// @param  [in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This operation is O (log(N))
//---------------------------------------------------------------------------
value_t & operator[] ( signed_type Pos) NOEXCEPT
{   mtx_read LM ( BD);
    return T[Pos];
};
//---------------------------------------------------------------------------
//  function : operator[ ]
/// @brief  Checked access to an element by their position in the cntree_vector
/// @param  [in] Pos : Position to read
/// @return Const reference to the object selected
/// @remarks This operation is  O(log(N))
//---------------------------------------------------------------------------
const value_t & operator[] ( signed_type Pos)const NOEXCEPT
{   mtx_read LM ( BD);
    return T[Pos];
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a reference to the first element in the cntree_vector
/// @param  [in]  none
/// @return reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & front (void ) NOEXCEPT
{   mtx_read LM ( BD);
    return T.front() ;
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element in the cntree_vector
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & front ( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return T.front() ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a reference to the last element in the cntree_vector
/// @param  [in]  none
/// @return reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & back ( void) NOEXCEPT
{   mtx_read LM ( BD);
    return T.back() ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element in the cntree_vector
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & back (void ) const NOEXCEPT
{   mtx_read LM ( BD);
    return T.back() ;
};
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #    I N S E R T I O N   O F    E L E M E N T S    #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//***************************************************************************
//          P U S H _ F R O N T
//
//  template <class P >
//  iterator push_front ( P && D )
//
//  template <class P , class Function>
//  iterator push_front_if ( P && D , Function && M )
//
//  template <class ... Args>
//  iterator emplace_front ( Args && ... args )
//
//  template <class Function , class ... Args>
//  iterator emplace_front_if ( Function &&  M ,Args && ... args )
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : push_front
/// @brief insert an element in the front of the container
/// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class P >
iterator push_front ( P && D )
{   return emplace_front ( std::forward<P>( D));
};
//---------------------------------------------------------------------------
//  function : push_front_if
/// @brief insert an element in the front of the container
/// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
/// @param [in] M : function with the format bool(  value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted, if not return end()
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class P , class Function>
iterator push_front_if ( P && D , Function && M )
{   return emplace_front_if (M, std::forward<P>( D ));
};
//---------------------------------------------------------------------------
//  function : emplace_front
/// @brief insert an element in the front of the container
/// @param [in] args : group of arguments for to build the object to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_front ( Args && ... args )
{   //----------------------- begin -----------------
    mtx_write BM ( BD );
    return emplace_internal (BM,T.connector_begin(),std::forward <Args>(args) ...);
};
//---------------------------------------------------------------------------
//  function : emplace_front_if
/// @brief insert an element in the front of the container
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @param [in] args : group of arguments for to build the object to insert
/// @return iterator to the element inserted, if not return end()
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class Function , class ... Args>
iterator emplace_front_if ( Function &&  M ,Args && ... args )
{   //--------------------------------- begin ------------------------
    mtx_write BM ( BD );
    return emplace_internal_if (BM,T.connector_begin(),M,std::forward <Args>(args) ...);
};
//***************************************************************************
//          P U S H _ B A C K
//
//  template <class P >
//  iterator push_back (  P && D )
//
//  template <class P ,class Function>
//  iterator push_back_if ( P && D , Function && M )
//
//  template <class ... Args>
//  iterator emplace_back ( Args && ... args )
//
//  template <class Function , class ... Args>
//  iterator emplace_back_if ( Function && M , Args && ... args )
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : push_back
/// @brief Insert one element in the back of the container
/// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class P >
iterator push_back (  P && D )
{   return emplace_back( std::forward<P> ( D ) );
};
//---------------------------------------------------------------------------
//  function : push_back_if
/// @brief Insert one element in the back of the container
/// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
/// @param [in] M : function with the format bool(  value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted, if not return end()
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class P ,class Function>
iterator push_back_if ( P && D , Function && M )
{   return emplace_back_if( M, std::forward<P>(D) );
};
//---------------------------------------------------------------------------
//  function : emplace_back
/// @brief Insert one element in the back of the container
/// @param [in] args :group of arguments for to build the object to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_back ( Args && ... args )
{   mtx_write BM ( BD );
    return emplace_internal (BM,T.connector_end(),std::forward <Args>(args) ...);
};
//---------------------------------------------------------------------------
//  function : emplace_back_if
/// @brief Insert one element in the back of the container
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @param [in] args :group of arguments for to build the object to insert
/// @return iterator to the element inserted, if not return end()
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class Function , class ... Args>
iterator emplace_back_if ( Function && M , Args && ... args )
{   mtx_write BM ( BD );
    return emplace_internal_if (BM,T.connector_end(),M,std::forward <Args>(args) ...);
};
//***************************************************************************
//          I N S E R T _ P O S , I N S E R T
//
//  template <class P >
//  iterator insert_pos(signed_type Pos, P && D )
//
//  template <class P , class Function >
//  iterator insert_pos_if(signed_type Pos, P && D, Function && M )
//
//  template <class ... Args>
//  iterator emplace_pos(signed_type Pos, Args && ... args)
//
//  template <class Function, class ... Args>
//  iterator emplace_pos_if ( signed_type Pos, Function && M, Args && ... args)
//
//  template <class P >
//  iterator insert ( iterator  iter , P && D )
//
//  template <class P , class Function>
//  iterator insert_if ( iterator  iter , P && D, Function && M )
//
//  template < class ... Args>
//  iterator emplace ( iterator  iter , Args && ... args )
//
//  template < class Function , class ... Args>
//  iterator emplace_if (iterator  iter ,Function && M, Args && ... args )
//
//  template <class P >
//  void  insert ( iterator  iter , unsigned_type n , const P & D )
//
//  template <typename InputIterator >
//  void  insert (iterator iter, InputIterator A_first ,InputIterator A_last )
//
//  template <class InputIterator, class Function >
//  void insert_if (iterator iter, InputIterator A_first, InputIterator A_last,
//                  Function &&  M )
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : insert_pos
/// @brief insert an element in a specified position
/// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
/// @param [in] Pos : Position to insert the value
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class P >
iterator insert_pos(signed_type Pos, P && D )
{   //-------------------------- begin -----------------------
    return emplace_pos ( Pos, std::forward<P>(D));
};
//---------------------------------------------------------------------------
//  function : insert_pos_if
/// @brief insert an element in a specified position
/// @param [in] Pos : Position to insert the value
/// @param [in] D : value to insert Can ve a value, a reference or an rvalue
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class P , class Function >
iterator insert_pos_if(signed_type Pos, P && D, Function && M )
{   //-------------------------- begin -----------------------
    return emplace_pos_if ( Pos,M, std::forward<P>(D));
}
//---------------------------------------------------------------------------
//  function : emplace_pos
/// @brief insert an element in a specified position
/// @param [in] args :group of arguments for to build the object to insert
/// @param [in] Pos : Position to insert the value
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_pos(signed_type Pos, Args && ... args)
{   //-------------------------- begin -----------------------
    mtx_write BM ( BD );
    connector C = T.connector_pos ( Pos);
    return emplace_internal (BM , C ,std::forward<Args> ( args) ...  );
};
//---------------------------------------------------------------------------
//  function : emplace_pos_if
/// @brief insert an element in a specified position
/// @param [in] args :group of arguments for to build the object to insert
/// @param [in] Pos : Position to insert the value
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted if not end()
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class Function, class ... Args>
iterator emplace_pos_if ( signed_type Pos, Function && M, Args && ... args)
{   //-------------------------- begin -----------------------
    mtx_write BM ( BD );
    connector C = T.connector_pos ( Pos);
    return emplace_internal_if (BM , C ,M, std::forward<Args> ( args) ...  );
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] iter : Iterator which indicates the position to insert the value
/// @param [in] D : value to insert Can ve a value, a reference or an rvalue
/// @return iterator to the element inserted
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <class P >
iterator insert ( iterator  iter , P && D )
{   return emplace ( iter, std::forward<P>(D));
};
//---------------------------------------------------------------------------
//  function : insert_if
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] iter : Iterator which indicates the position to insert the value
/// @param [in] D : value to insert Can ve a value, a reference or an rvalue
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted if not false()
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <class P , class Function>
iterator insert_if ( iterator  iter , P && D, Function && M )
{   return emplace_if ( iter,M, std::forward<P>(D));
};

//---------------------------------------------------------------------------
//  function : emplace
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] iter : Iterator indicating the position to insert the value
/// @param [in] args :group of arguments for to build the object to insert
/// @return iterator to the element inserted
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template < class ... Args>
iterator emplace ( iterator  iter , Args && ... args )
{   //------------------------- begin --------------------------------
    mtx_write BM ( BD);
    assert  ( iter.ptr_tree() == &T and iter.ptr_node() != PMIN);
    connector C ;
    if ( iter == T.end() ) C = T.connector_end() ;
    else                   C = T.connector_pointer (iter.ptr_node());
    return emplace_internal ( BM, C , std::forward<Args> ( args) ... );
};
//---------------------------------------------------------------------------
//  function : emplace_if
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] iter : Itera which indicates the position to insert the value
/// @param [in] args :group of arguments for to build the object to insert
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @return iterator to the element inserted
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template < class Function , class ... Args>
iterator emplace_if (iterator  iter ,Function && M, Args && ... args )
{   //------------------------------ begin------------------------------
    mtx_write BM ( BD);
    assert  ( iter.ptr_tree() == &T and iter.ptr_node() != PMIN);
    connector C ;
    if ( iter == T.end() ) C = T.connector_end() ;
    else                   C = T.connector_pointer (iter.ptr_node());
    return emplace_internal_if ( BM, C ,M, std::forward<Args> ( args) ... );
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert n elements with the value D element in the position
///        specified by an iterator
/// @param [in] iter : Iterator which indicates the position to insert the value
/// @param [in] n : Number of elements to insert
/// @param [in] D : value to insert
/// @return none
/// @remarks If the iterator is rend()  there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <class P >
void  insert ( iterator  iter , unsigned_type n , const P & D )
{   //---------------------- begin -----------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    for ( unsigned_type i = 0 ; i < n ; ++i)
    {   T.insert ( iter, D);
    };
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert a range of lements defined by the pair of iterators A_first, A_last
///        in the position defined by the iterator iter.
/// @param [in] iter : Iterator which indicates the position to insert the value
/// @param [in] A_first : InputIterator to the first element
/// @param [in] A_last : InputIterator to the next element of the last
/// @return none
/// @remarks If the iterator is rend()  there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <typename InputIterator >
void  insert (iterator iter, InputIterator A_first ,InputIterator A_last )
{   //------------------ begin ----------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    for ( ; A_first != A_last ; ++A_first)
    {   T.insert ( iter , *A_first);
    }
};
//---------------------------------------------------------------------------
//  function : insert_if
/// @brief insert a range of lements defined by the pair of iterators A_first, A_last
///        in the position defined by the iterator iter. But insert only the elements
///        which make true the function M
/// @param [in] iter : Iterator which indicates the position to insert the value
/// @param [in] A_first : InputIterator to thje first element
/// @param [in] A_last : InputIterator to the next element of the last
/// @param [in] M : function with the format bool( value_t &).
///                  if return true the element is iserted , if false not
/// @return none
/// @remarks If the iterator is rend()  there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <class InputIterator, class Function >
void insert_if (iterator iter, InputIterator A_first, InputIterator A_last,
                 Function &&  M )
{   //------------------ begin ----------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    for ( ; A_first != A_last ; ++A_first)
    {   if ( M ( *A_first))
            T.insert ( iter , *A_first);
    };
};
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #    D E L E T I O N S    O F   E L E M E N T S    #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//***************************************************************************
//                      P O P _ F R O N T
//
//  void pop_front ( void )
//
//  template <class Function>
//  uint32_t pop_front_if ( Function &&  M1  )
//
//  uint32_t pop_copy_front ( value_t & V)
//
//  template <class Function>
//  uint32_t pop_copy_front_if ( value_t & V, Function && M1)
//
//  uint32_t pop_move_front ( value_t & V)
//
//  template <class Function >
//  uint32_t pop_move_front_if ( value_t & V, Function && M1)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : pop_front
/// @brief erase the first element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O (constant)
//---------------------------------------------------------------------------
void pop_front ( void )
{   mtx_write BM ( BD);
    BM.wait_no_readers() ;
    T.pop_front() ;
};
//---------------------------------------------------------------------------
//  function : pop_front_if
/// @brief erase the first element of the container
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O (constant)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_front_if ( Function &&  M1  )
{   //----------------------- begin ------------------
    mtx_write BM ( BD);
    if ( T.size() == 0 ) return 1 ;
    bool SW =  M1 ( T.front());
    if ( SW)
    {   BM.wait_no_readers() ;
        T.pop_front() ;
    };
    return (SW?0:2 );
};

//---------------------------------------------------------------------------
//  function :pop_copy_front
/// @brief erase the first element of the tree and return a copy
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_copy_front ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PFirst = T.upgrade ( T.ptr_first() );
    V = PFirst->data ;
    BM.wait_no_readers() ;
    T.erase_internal ( PFirst);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_front_if
/// @brief erase the first element of the tree and return a copy
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_copy_front_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PFirst = T.upgrade ( T.ptr_first() );
    if ( not  M1 (PFirst->data ) ) return 2 ;   ;
    V = PFirst->data ;
    BM.wait_no_readers() ;
    T.erase_internal ( PFirst);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_front
/// @brief erase the first element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where move the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_move_front ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PFirst = T.upgrade ( T.ptr_first() );
    V = std::move(PFirst->data) ;
    BM.wait_no_readers() ;
    T.erase_internal ( PFirst);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_front_if
/// @brief erase the first element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where move the element
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function >
uint32_t pop_move_front_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PFirst = T.upgrade ( T.ptr_first() );
    if ( not  M1 (PFirst->data ) ) return 2 ;   ;
    V = std::move(PFirst->data) ;
    BM.wait_no_readers() ;
    T.erase_internal ( PFirst);
    return 0;
};
//
//***************************************************************************
//                  P O P _ B A C K
//
//  void pop_back ( void)
//
//  template <class Function >
//  uint32_t pop_back_if ( Function &&  M1)
//
//  uint32_t pop_copy_back ( value_t & V)
//
//  template <class Function >
//  uint32_t pop_copy_back_if ( value_t & V, Function && M1)
//
//  uint32_t pop_move_back ( value_t & V)
//
//  template <class Function >
//  uint32_t pop_move_back_if ( value_t & V, Function && M1)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function :pop_back
/// @brief erase the last element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
void pop_back ( void)
{   mtx_write BM ( BD);
    BM.wait_no_readers() ;
    T.pop_back() ;
};
//---------------------------------------------------------------------------
//  function :pop_back_if
/// @brief erase the last element of the container
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
template <class Function >
uint32_t pop_back_if ( Function &&  M1)
{   //----------- begin ------------------
    mtx_write BM ( BD);
    if ( T.size() == 0 ) return 1 ;
    bool SW = M1 ( T.back());
    if ( SW)
    {   BM.wait_no_readers() ;
        T.pop_back() ;
    };
    return SW?0:2 ;
};
//---------------------------------------------------------------------------
//  function :pop_copy_back
/// @brief erase the last element of the tree and return a copy
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_copy_back ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PLast = T.upgrade ( T.ptr_last() );
    V = PLast->data ;
    BM.wait_no_readers() ;
    T.erase_internal ( PLast);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_back_if
/// @brief erase the last element of the tree and return a copy in V
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function >
uint32_t pop_copy_back_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PLast = T.upgrade ( T.ptr_last() );
    if ( not  M1 (PLast->data ) ) return 2 ;   ;
    V = PLast->data ;
    BM.wait_no_readers() ;
    T.erase_internal ( PLast);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_back
/// @brief erase the last element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where move the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_move_back ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PLast = T.upgrade ( T.ptr_last() );
    V = std::move(PLast->data) ;
    BM.wait_no_readers() ;
    T.erase_internal ( PLast);
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_back_if
/// @brief erase the last element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where move the element
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function >
uint32_t pop_move_back_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( T.size() == 0) return 1 ;
    node_t * PLast = T.upgrade ( T.ptr_last() );
    if ( not  M1 (PLast->data ) ) return 2 ;   ;
    V = std::move(PLast->data) ;
    BM.wait_no_readers() ;
    T.erase_internal ( PLast);
    return 0;
};
//
//***************************************************************************
//                         E R A S E
//
//  iterator erase ( const_iterator iter )
//
//  template <class Function>
//  iterator erase_if ( const_iterator iter , Function &&  M1)
//
//  void erase_pos( signed_type Pos)
//
//  template <class Function >
//  bool erase_pos_if( signed_type Pos, Function && M )
//
//  signed_type erase ( const_iterator first_it, const_iterator last_it)
//
//  template <class Function >
//  signed_type erase_if ( const_iterator first_it,  const_iterator last_it,
//                         Function &&  M1    )
//
//  void erase_pos ( signed_type First, signed_type NElem)
//
//  template <class Function>
//  void erase_pos_if ( signed_type First, signed_type NElem, Function && M)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase the element pointed by iter
/// @param [in] iter : iterator to the element to erase
/// @return return the iterator to the next element
//---------------------------------------------------------------------------
iterator erase ( const_iterator iter )
{   //---------- begin -------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return T.upgrade( T.erase( iter ));
};
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase the element pointed by iter if the function return true
/// @param [in] iter : iterator to the element to erase
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return iterator to the next element to iter
//---------------------------------------------------------------------------
template <class Function>
iterator erase_if ( const_iterator iter , Function &&  M1)
{   //---------- begin -------------
    mtx_write BM ( BD);
    iterator Alfa = T.upgrade (iter +1) ;
    if (M1 ( *iter))
    {   BM.wait_no_readers() ;
        T.erase( iter );
    }

    return Alfa ;
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @return void
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
void erase_pos( signed_type Pos)
{   //----------------- begin ----------------
    mtx_write BM ( BD);
    // The function ptr_pos check the limits
    node_t *Ptr1 = T.upgrade( T.ptr_pos( Pos));
    BM.wait_no_readers() ;
    T.disconnect ( Ptr1);
    T.destroy ( Ptr1 ) ;
    T.deallocate ( Ptr1, 1 ) ;
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return true ->deleted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class Function >
bool erase_pos_if( signed_type Pos, Function && M )
{   //---------------------------- begin ------------------------------------
    mtx_write BM ( BD);
    // The function ptr_pos check the limits
    node_t *P1 = T.upgrade (T.ptr_pos ( Pos));
    bool SW =  M ( P1->data);
    if ( SW )
    {   BM.wait_no_readers() ;
        T.disconnect ( P1 ) ;
        T.destroy ( P1 ) ;
        T.deallocate ( P1, 1 ) ;
    };
    return SW ;
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : iterator to the first element
/// @param [in] last_it : iterator to the final element of the range
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
signed_type erase ( const_iterator first_it, const_iterator last_it)
{   mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return T.erase ( first_it , last_it);
};

//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : iterator to the first element
/// @param [in] last_it : iterator to the final element of the range
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
template <class Function >
signed_type erase_if ( const_iterator first_it,
                       const_iterator last_it,
                       Function &&  M1    )
{   //--------------------- begin -----------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return T.erase_if ( first_it , last_it, M1 );
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the NElem elements after  the position First
/// @param [in] First : position to the first element to erase
/// @param [in] NElem : number of elements to erase
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void erase_pos ( signed_type First, signed_type NElem)
{   //----------------------- begin ---------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    T.erase_pos( First, NElem);
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the NElem elements after  the position First if the function
///        M return true when receives the element as parameter
/// @param [in] First : position to the first element to erase
/// @param [in] NElem : number of elements to erase
/// @param [in] M : function with the format( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
void erase_pos_if ( signed_type First, signed_type NElem, Function && M)
{   //----------------------- begin ---------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    T.erase_pos_if( First, NElem, M );
};
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       # M O D I F I C A T I O N   O F   E L E M E N T S  #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//***************************************************************************
//                       M O D I F Y
//
//  void modify ( iterator It , const value_type & D)
//
//  void modify ( iterator It , value_type && D)
//
//  template <class Function >
//  void modify ( iterator It , Function && M )
//
//  void modify_pos ( signed_type Pos ,const value_type & D)
//
//  void modify_pos ( signed_type Pos , value_type && D)
//
//  template <class Function>
//  void modify_pos ( signed_type Pos ,Function &&  M)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : modify
/// @brief copy D to the element pointed by It
/// @param [in] It : iterator to the element
/// @param [in] D : new value
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify ( iterator It , const value_type & D)
{   //------------------------- begin---------------------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    (*It) =  D;
};

//---------------------------------------------------------------------------
//  function : modify
/// @brief move D to the element pointed by It
/// @param [in] It : iterator to the element
/// @param [in] D : new value
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify ( iterator It , value_type && D)
{   //------------------------- begin---------------------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    *It = std::move(D);
};

//---------------------------------------------------------------------------
//  function : modify
/// @brief modify the element pointed by It with a function M
/// @param [in] It ; iterator to the element to modify
/// @param [in] M : function with the format (void M (value_type &))
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function >
void modify ( iterator It , Function && M )
{   //------------------------- begin ----------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    M ( *It);
};
//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief assign D to the element of the position Pos
/// @param [in] Pos : position to modify
/// @param [in] D : new value to assign
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify_pos ( signed_type Pos ,const value_type & D)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    value_type & R = T[Pos];
    BM.wait_no_readers () ;
    R = D;
};

//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief move D to the element of the position Pos
/// @param [in] Pos : position to modify
/// @param [in] D : new value to assign
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify_pos ( signed_type Pos , value_type && D)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    value_type & R = T[Pos];
    BM.wait_no_readers () ;
    R = std::move (D);
};

//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief modify the element of the position Pos with the function M
/// @param [in] Pos : position to modify
/// @param [in] M : function to modify the element with the format
///                 (void M (value_type &))
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
void modify_pos ( signed_type Pos ,Function &&  M)
{   //------------------- begin --------------------------
    mtx_write BM ( BD);
    value_type & R = T[Pos];
    BM.wait_no_readers () ;
    M ( R);
};

//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #               I T E R A T O R S                  #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//
//***************************************************************************
//  I S _ M I N E
//  F I N D _ P O S , B E G I N , E N D , R B E G I N , R E N D
//
//  bool is_mine ( iterator P1) const;
//  bool is_mine ( const_iterator P1) const;
//
//  iterator  	    iterator_pos        ( signed_type Pos1);
//  const_iterator  const_iterator_pos  ( signed_type Pos1) const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_vector
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_vector
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_iterator P1) const
{   mtx_read LM ( BD);
    return T.is_mine (P1);
};
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_vector
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_vector
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_reverse_iterator P1) const
{   mtx_read LM ( BD);
    return T.is_mine (P1);
};
//---------------------------------------------------------------------------
//  function : iterator_pos
/// @brief Find a position in the cntree_vector
/// @param [in] Pos : Position to find
/// @return Iterator to the position. If don't exists throw an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
iterator iterator_pos ( signed_type Pos1)
{   mtx_read LM ( BD);
    return T.iterator_pos ( Pos1);
};
//---------------------------------------------------------------------------
//  function : const_iterator_pos
/// @brief Find a position in the cntree_vector
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
const_iterator const_iterator_pos ( signed_type Pos1) const
{   mtx_read LM ( BD);
    return T.const_iterator_pos ( Pos1);
};
//***************************************************************************
//                      I T E R A T O R S
//
//  iterator it_begin   ( void) NOEXCEPT
//  iterator begin      ( void) NOEXCEPT
//  iterator it_end     ( void) NOEXCEPT
//  iterator end        ( void) NOEXCEPT
//  iterator it_rbegin  ( void) NOEXCEPT
//  iterator it_rend    ( void) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function :it_begin
/// @return iterator to the first element
//---------------------------------------------------------------------------
iterator it_begin( void) NOEXCEPT
{   mtx_read LM ( BD);
    return iterator::begin( &T);
};
//---------------------------------------------------------------------------
//  function : begin
/// @return iterator to the first element
//---------------------------------------------------------------------------
iterator begin ( void) NOEXCEPT
{   return it_begin() ;
};
//---------------------------------------------------------------------------
//  function : it_end
/// @return iterator to the next element after the last
//---------------------------------------------------------------------------
iterator it_end( void) NOEXCEPT
{   mtx_read LM ( BD);
    return iterator::end( &T);
};
//---------------------------------------------------------------------------
//  function : end
/// @return iterator to the next element after the last
//---------------------------------------------------------------------------
iterator end ( void) NOEXCEPT
{   return  it_end();
};
//---------------------------------------------------------------------------
//  function : it_rbegin
/// @return iterator to the last element
//---------------------------------------------------------------------------
iterator it_rbegin( void) NOEXCEPT
{   mtx_read LM ( BD);
    return iterator::rbegin( &T);
};
//---------------------------------------------------------------------------
//  function : it_rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
iterator it_rend( void) NOEXCEPT
{   mtx_read LM ( BD);
    return iterator::rend( &T);
};

//***************************************************************************
//                C O N S T _ I T E R A T O R
//
//  const_iterator cit_begin    ( void) const NOEXCEPT
//  const_iterator begin        ( void) const NOEXCEPT
//  const_iterator cbegin       ( void) const NOEXCEPT
//  const_iterator cit_end      ( void) const NOEXCEPT
//  const_iterator end          ( void) const NOEXCEPT
//  const_iterator cend         ( void) const NOEXCEPT
//  const_iterator cit_rbegin   ( void) const NOEXCEPT
//  const_iterator cit_rend     ( void) const NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function :cit_begin
/// @return const_iterator to the first element
//---------------------------------------------------------------------------
const_iterator cit_begin( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_iterator::begin( &T);
};
//---------------------------------------------------------------------------
//  function :begin
/// @return const_iterator to the first element
//---------------------------------------------------------------------------
const_iterator begin( void) const NOEXCEPT
{   return cit_begin();
};
//---------------------------------------------------------------------------
//  function :cbegin
/// @return const_iterator to the first element
//---------------------------------------------------------------------------
const_iterator cbegin( void) const NOEXCEPT
{   return cit_begin();
};
//---------------------------------------------------------------------------
//  function : cit_end
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator cit_end( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_iterator::end( &T);
};
//---------------------------------------------------------------------------
//  function : end
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator end( void) const NOEXCEPT
{   return cit_end();
};
//---------------------------------------------------------------------------
//  function : cend
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator cend( void) const NOEXCEPT
{   return cit_end();
};
//---------------------------------------------------------------------------
//  function : cit_rbegin
/// @return const_iterator to the last element
//---------------------------------------------------------------------------
const_iterator cit_rbegin( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_iterator::rbegin( &T);
};
//---------------------------------------------------------------------------
//  function : cit_rend
/// @return const_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_iterator cit_rend( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_iterator::rend( &T);
};

//***************************************************************************
//             R E V E R S E _ I T E R A T O R
//
//  reverse_iterator rit_begin  ( void) NOEXCEPT
//  reverse_iterator rit_end    ( void) NOEXCEPT
//  reverse_iterator rit_rbegin ( void) NOEXCEPT
//  reverse_iterator rbegin     ( void) NOEXCEPT
//  reverse_iterator rit_rend   ( void) NOEXCEPT
//  reverse_iterator rend       ( void) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function :rit_begin
/// @return reverse_iterator to the first element
//---------------------------------------------------------------------------
reverse_iterator rit_begin( void) NOEXCEPT
{   mtx_read LM ( BD);
    return reverse_iterator::begin( &T);
};
//---------------------------------------------------------------------------
//  function : rit_end
/// @return reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
reverse_iterator rit_end( void) NOEXCEPT
{   mtx_read LM ( BD);
    return reverse_iterator::end( &T);
};
//---------------------------------------------------------------------------
//  function : rit_rbegin
/// @return reverse_iterator to the last element
//---------------------------------------------------------------------------
reverse_iterator rit_rbegin( void) NOEXCEPT
{   mtx_read LM ( BD);
    return reverse_iterator::rbegin( &T);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @return reverse_iterator to the last element
//---------------------------------------------------------------------------
reverse_iterator rbegin( void) NOEXCEPT
{   return rit_rbegin();
};
//---------------------------------------------------------------------------
//  function : rit_rend
/// @return reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
reverse_iterator rit_rend( void) NOEXCEPT
{   mtx_read LM ( BD);
    return reverse_iterator::rend( &T);
};
//---------------------------------------------------------------------------
//  function : rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
reverse_iterator rend( void) NOEXCEPT
{   return rit_rend();
};

//***************************************************************************
//          C O N S T _ R E V E R S E _ I T E R A T O R
//
//  const_reverse_iterator crit_begin   ( void) const NOEXCEPT
//  const_reverse_iterator crit_end     ( void) const NOEXCEPT
//  const_reverse_iterator crit_rbegin  ( void) const NOEXCEPT
//  const_reverse_iterator rbegin       ( void) const NOEXCEPT
//  const_reverse_iterator crbegin      ( void) const NOEXCEPT
//  const_reverse_iterator crit_rend    ( void) const NOEXCEPT
//  const_reverse_iterator rend         ( void) const NOEXCEPT
//  const_reverse_iterator crend        ( void) const NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : crit_begin
/// @return const_reverse_iterator to the first element
//---------------------------------------------------------------------------
const_reverse_iterator crit_begin( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_reverse_iterator::begin( &T);
};
//---------------------------------------------------------------------------
//  function : crit_end
/// @return const_reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
const_reverse_iterator crit_end( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_reverse_iterator::end( &T);
};
//---------------------------------------------------------------------------
//  function : crit_rbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator crit_rbegin( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_reverse_iterator::rbegin( &T);
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator rbegin( void) const NOEXCEPT
{   return crit_rbegin();
};
//---------------------------------------------------------------------------
//  function : crbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator crbegin( void) const NOEXCEPT
{   return crit_rbegin();
};
//---------------------------------------------------------------------------
//  function : crit_rend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator crit_rend( void) const NOEXCEPT
{   mtx_read LM ( BD);
    return const_reverse_iterator::rend( &T);
};
//---------------------------------------------------------------------------
//  function : rend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator rend( void) const NOEXCEPT
{   return crit_rend() ;
};
//---------------------------------------------------------------------------
//  function : crend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator crend( void) const NOEXCEPT
{   return crit_rend() ;
};

//***************************************************************************
//  O T H E R S        F U N C T I O N S
//
//#if __DEBUG_CNTREE != 0
//   void Imprimir(void)const;
//#endif
//   alloc_t get_allocator() const;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : get_allocator
/// @brief return the object allocator of the cntree_vector
/// @param [in] none
/// @return object allocator
//---------------------------------------------------------------------------
alloc_t get_allocator() const
{   mtx_read LM ( BD);
    return value_alloc ; ;
};

//***************************************************************************
//                P R I V A T E     F U N C T I O N S
//***************************************************************************
private :
//---------------------------------------------------------------------------
//  function : emplace_internal
/// @brief insert an element in the front of the container
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_internal (mtx_write &BM, connector C , Args && ... args )
{   //----------------------- begin -----------------
    node_t * PAux = T.allocate (1) ;
    T.construct ( PAux , std::forward <Args>(args) ...  );
    BM.wait_no_readers() ;
    T.connect( PAux, C);
    return iterator ( PAux, &T );

};
//---------------------------------------------------------------------------
//  function : emplace_internal_if
/// @brief insert an element in the front of the container
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_internal_if ( mtx_write &BM, connector C ,
                               std::function < bool(const value_type &)> M ,
                               Args && ... args )
{   //--------------------------------- begin ------------------------
    node_t * PAux = T.allocate (1) ;
    T.construct ( PAux , std::forward <Args>(args) ...  );
    iterator I ;
    if ( M ( PAux->data))
    {   BM.wait_no_readers() ;
        T.connect( PAux, C);
        I = iterator ( PAux, &T );
    }
    else
    {   T.destroy ( PAux);
        T.deallocate ( PAux , 1);
        I = end();
    } ;
    return I ;
};

//***************************************************************************
//   D E B U G   F U N C T I O N S
//
//  bool check (  void ) const;
//  void Imprimir(void)const;
//
//***************************************************************************
#if __DEBUG_CNTREE != 0
public:
bool check (  void ) const{ return T.check();};
std::ostream & Imprimir ( std::ostream &salida) const
{   salida<<T<<std::endl ;
    return salida ;
}

#endif
//***************************************************************************
};//              E N D  V E C T O R _ T R E E    C L A S S
//***************************************************************************
template  <class T, bool cnc,class Alloc>
std::ostream & operator<< ( std::ostream & salida, const cntree_vector <T,cnc,Alloc> &VT)
{   return VT.Imprimir (salida) ;
}
//***************************************************************************
};//              E N D   C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
namespace std
{
template  <class T, bool cnc,class Alloc>
void swap ( countertree::cntree_vector<T,cnc,Alloc> &A ,
            countertree::cntree_vector<T,cnc,Alloc> & B   )
{   //-------------------------------- begin ---------------------
    A.swap(B);
};
}
#endif
