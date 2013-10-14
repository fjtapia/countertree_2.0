//----------------------------------------------------------------------------
/// @file   cntree_set.hpp
/// @brief  This file contains the implementation of cntree_set and multiset,
///         based on the vector_tree
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_SET_HPP
#define __COUNTERTREE_FOREST_SET_HPP

#include <type_traits>
#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/mutex_read_write.hpp>
#include <boost/countertree/filter.hpp>
#include <boost/countertree/forest/sorted_tree.hpp>

namespace countertree
{


namespace c_common = countertree::common ;
namespace c_forest = countertree::forest ;
//using c_common::config_alloc ;
using c_common::signed_type;
using c_common::unsigned_type;


//template <class value_t,bool cnc, class comp_key_t ,class alloc_t >
//class cntree_multiset  ;

//##########################################################################
//                                                                        ##
//                         C L A S S                                      ##
//                                                                        ##
//   S E T < V A L U E _ T , C N C , C O M P _ K E Y , A L L O C _ T >    ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
/// @class  cntree_set
/// @brief  This class have the same interface than the STL set,
///         plus access by position with the function at, and random access
///         iterators
/// @remarks
//---------------------------------------------------------------------------
template < typename value_t,
           bool cnc            = false,
           typename comp_key_t = std::less<value_t>,
           typename alloc_t    = cntree_allocator<void>
        >
class cntree_set
{
public :
//***************************************************************************
//               P U B L I C       D E F I N I T I O N S
//***************************************************************************
typedef typename config_fastmutex<cnc>::fastmutex_data   mtx_data ;
typedef mutex_read <mtx_data>                            mtx_read ;
typedef mutex_write<mtx_data>                            mtx_write ;


typedef value_t                                                 key_t ;
typedef filter_set<key_t,value_t>                               filter_t ;

typedef c_forest::sorted_tree<value_t,key_t,filter_t,comp_key_t,alloc_t>  srt_tree_t ;

typedef         key_t                                   key_type;
typedef         value_t                                 value_type ;
typedef         value_t *                                 pointer;
typedef const   value_t *                                 const_pointer;
typedef         value_t &                                 reference ;
typedef const   value_t &                                 const_reference;

typedef comp_key_t                                      key_compare ;
typedef comp_key_t                                      value_compare;
typedef alloc_t                                         allocator_type;

typedef typename srt_tree_t::tree                       tree ;
typedef typename srt_tree_t::node_t                     node_t ;
typedef typename srt_tree_t::node_alloc_t               node_alloc_t ;
typedef typename srt_tree_t::const_iterator             iterator;
typedef typename srt_tree_t::const_iterator             const_iterator ;
typedef typename c_common::signed_type                  size_type ;
typedef typename c_common::signed_type                  difference_type;
typedef typename srt_tree_t::const_reverse_iterator     reverse_iterator;
typedef typename srt_tree_t::const_reverse_iterator     const_reverse_iterator;
typedef std::pair<const_iterator,bool>                  mypair ;
typedef c_forest::connector                             connector ;


private :
//**************************************************************************
//             P R I V A T E       D E F I N I T I O N S
//
//**************************************************************************

template <class value_t2, bool cnc2, typename comp_key_t2 ,typename alloc_t2 >friend class cntree_set ;
template <class value_t2, bool cnc2, typename comp_key_t2 ,typename alloc_t2 >friend class cntree_multiset ;
//**************************************************************************
//                      V A R I A B L E S
//**************************************************************************
srt_tree_t  st ;

public:
//**************************************************************************
//               P U B L I C   V A R I A B L E S
//**************************************************************************
mutable mtx_data BD ;

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
//  C O N S T R U C T O R    &   D E S T R U C T O R
//
//  explicit cntree_set ( const Comp & C1=Comp(),const Alloc & A1 = Alloc());
//
//  template <class InputIterator>
//  cntree_set ( InputIterator first,      InputIterator last,
//         const Comp& C1 = Comp(),  const Alloc & A1= Alloc() );
//
//  cntree_set ( const cntree_set & x );
//  virtual ~cntree_set (void) ;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : cntree_set
/// @brief  Constructor from an object Comparer and an object Allocator
/// @param [in] C1 : Comparer
/// @param [in] A1 : Allocator
//-------------------------------------------------------------------------
explicit cntree_set ( const key_compare &C1=key_compare(),
                      const alloc_t  &A1= alloc_t ())
                      : st( C1,A1){  };

//----------------------------------------------------------------
//  function : cntree_set
/// @brief  Constructor from a pair of iterators and an object
///         Comparer and an object Allocator
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] C1 : Comparer
/// @param [in] A1 : Allocator
//----------------------------------------------------------------
template <class InputIterator>
cntree_set ( InputIterator first,
             InputIterator last,
             const key_compare& C1=key_compare(),
             const alloc_t  &A1=alloc_t ()):st(C1,A1)
{   //-------------------------begin -----------------------------------
    mtx_write BM ( BD) ;
    BM.wait_no_readers () ;
    for ( ; first != last ; first++) st.insert_value_norep ( *first) ;
};
//----------------------------------------------------------------
//  function : cntree_set
/// @brief  Copy constructor
/// @param [in] x : cntree_set from where copy the data
//----------------------------------------------------------------
cntree_set ( const cntree_set & x ):st(x.st.key_comp(),x.st.get_allocator())
{   //---------------------------- begin----------------------
    mutex_write_read <mtx_data, mtx_data > BM ( BD,x.BD);
    BM.wait_no_readers() ;
    st = x.st ;
};
//----------------------------------------------------------------
//  function : cntree_set
/// @brief  Copy constructor
/// @param [in] x : cntree_set from where move the data
//----------------------------------------------------------------
cntree_set (  cntree_set && x ): st( x.st.key_comp(),x.st.get_allocator())
{   //--------------------- begin -----------------
    mutex_write_write <mtx_data, mtx_data> BM ( BD, x.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second();
    st = std::move(x.st);
};
//----------------------------------------------------------------
//  function : cntree_set
/// @brief  Copy constructor
/// @param [in] x : cntree_set from where copy the data
//----------------------------------------------------------------
template <bool cnc2 >
cntree_set (  cntree_set <value_t,cnc2,comp_key_t,alloc_t> && x )
:st( x.st.key_comp(),x.st.get_allocator())
{   //------------------------- begin --------------------
    typedef typename cntree_set <value_t,cnc2,comp_key_t,alloc_t>::mtx_data mtx_data2 ;
    mutex_write_write <mtx_data, mtx_data2> BM ( BD, x.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second();
    st = std::move(x.st);
};
//----------------------------------------------------------------
//  function : cntree_set
/// @brief  Copy constructor
/// @param [in] x : cntree_set from where copy the data
//----------------------------------------------------------------
template < typename alloc_t2 , bool cnc2 >
cntree_set ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x )
:st(x.st.key_comp())
{   //--------------------------- begin--------------------------
    typedef typename cntree_set <value_t,cnc2,comp_key_t,alloc_t2>::mtx_data mtx_data2 ;
    mutex_write_read < mtx_data, mtx_data2> BM ( BD, x.BD);
    BM.wait_no_readers() ;
    st =  x.st ;
};
//----------------------------------------------------------------
//  function : ~cntree_set
/// @brief  Destructor
//----------------------------------------------------------------
virtual ~cntree_set(void ){} ;

//
//***************************************************************************
//  O P E R A T O R = , C L E A R , S W A P
//
//  cntree_set & operator = ( const cntree_set &S);
//
//  template < typename alloc_t2 , bool cnc2 >
//  cntree_set & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
//
//  cntree_set  & operator = (  cntree_set &&S)
//
//  template <bool cnc2 >
//  cntree_set & operator= (  cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
//
//  void clear ( void)
//  void swap ( cntree_set & st )
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] S : cntree_set from where copy the data
/// @return Reference to the cntree_set after the copy
//---------------------------------------------------------------------------
cntree_set & operator = ( const cntree_set &S)
{   //--------- begin --------------
    if ( this == &S ) return *this ;
    mutex_write_read < mtx_data, mtx_data> BM ( BD,S.BD);
    BM.wait_no_readers() ;
    st = S.st;
    return *this ;
};
//----------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] S : cntree_setr from where copy the data
/// @return Reference to the cntree_set after the copy
//----------------------------------------------------------------
template < typename alloc_t2 , bool cnc2 >
cntree_set & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
{   //-------------------------------- begin -------------------------------
    if ( (void*)this == (void*)(&S)  ) return *this ;
    typedef typename cntree_set <value_t,cnc2,comp_key_t,alloc_t2>::mtx_data mtx_data2 ;
    mutex_write_read <mtx_data ,mtx_data2> BM ( BD, S.BD);
    BM.wait_no_readers() ;
    st = S.st;
    return *this;
};
//----------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] S : cntree_setr from where move the data
/// @return Reference to the cntree_set after the copy
//----------------------------------------------------------------
cntree_set  & operator = (  cntree_set &&S)
{   //-------------------------------- begin -------------------------------
    if ( (void*)this == (void*)(&S)  ) return *this ;
    mutex_write_write <mtx_data ,mtx_data> BM ( BD, S.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move (S.st) ;
    return *this ;
};
//----------------------------------------------------------------
//  function : operator=
/// @brief  Copy constructor
/// @param [in] x : cntree_set from where move the data
//----------------------------------------------------------------
template <bool cnc2 >
cntree_set & operator= (  cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
{   //-------------------------- begin-------------------------
    if ( (void*)this == (void*)(&x)  ) return *this ;
    typedef typename cntree_set <value_t,cnc2,comp_key_t,alloc_t>::mtx_data mtx_data2;
    mutex_write_write <mtx_data ,mtx_data2> BM ( BD, x.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move (x.st) ;
    return *this ;
};
//----------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the cntree_set
/// @param [in] none
/// @return none
//----------------------------------------------------------------
void clear ( void)
{   //-------------- begin ------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.clear();
};
//----------------------------------------------------------------
//  function : swap
/// @brief swap the data of the cntree_set st with the actual cntree_set
/// @param [in] st : cntree_set to swap
/// @return none
//----------------------------------------------------------------
void swap ( cntree_set & s1 )
{   //--------------- begin -------------
    if ( this == &s1) return ;
    mutex_write_write<mtx_data,mtx_data> BM ( BD,s1.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st.swap ( s1.st);
};
//
//***************************************************************************
//         C A P A C I T Y
//
//  bool        empty    (void) const ;
//  signed_type size     (void) const ;
//  signed_type max_size (void) const ;
//
//***************************************************************************
//
//----------------------------------------------------------------
//  function : empty
/// @brief indicate if the cntree_set is empty
/// @return true if the cntree_set is empty, false in any other case
//----------------------------------------------------------------
bool empty ( void) const
{   mtx_read BR ( BD);
    return st.size() == 0 ;
};
//----------------------------------------------------------------
//  function : size
/// @brief return the number of elements in the cntree_set
/// @return number of elements in the cntree_set
//----------------------------------------------------------------
signed_type size (void) const
{   mtx_read BR ( BD);
    return st.size() ;
};
//----------------------------------------------------------------
//  function : max_size
/// @brief return the maximun size of the container
/// @return maximun size of the container
//----------------------------------------------------------------
signed_type max_size (void) const
{   mtx_read BR ( BD);
    return st.size_type_max() ;
};
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
//**************************************************************************
//  P O S , I T E R A T O R _ P O S , C O N S T _ I T E R A T O R _ P O S
//
//  const value_t & pos          ( unsigned_type Pos1) const
//  const_iterator  iterator_pos ( signed_type Pos1) const NOEXCEPT
//
//  const value_t & front ( void) const NOEXCEPT
//  const value_t & back (void ) const NOEXCEPT
//
//***************************************************************************
//
//----------------------------------------------------------------
//  function : pos
/// @brief  Access to an element by their position in the cntree_set
/// @param  [in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This is an random access function of the cntree_set.\n
///          I didn't use the operator [ ] because it is used in the
///          map class, and the function at is used in std map in C++11\n
///          It is very important to be uniform access method in
///          the four classes( cntree_set, multiset, map and multimap)\n
///          This operation is O (log(N))
//----------------------------------------------------------------
const value_t & pos ( unsigned_type Pos1) const
{   //----------------------- begin---------------------------
    mtx_read BR ( BD);
    return st.pos (Pos1);
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & front ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.front() ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & back (void ) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.back();
};
//
//**************************************************************************
//  F I N D , C O U N T , L O W E R _ B O U N D ,
//  U P P E R _ B O U N D  , E Q U A L _ R A N G E
//
//  iterator    find        ( const key_type& x ) const;
//  signed_type count       ( const key_type& x ) const;
//  iterator    lower_bound ( const key_type& x ) const;
//  iterator    upper_bound ( const key_type& x ) const;
//
//  std::pair<iterator,iterator> equal_range ( const key_type& x ) const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : find
/// @brief return the iterator to the element with the key x
/// @param [in] x : key to find in the cntree_set
/// @return iterator to the element with the key x. If don't exist return end()
//---------------------------------------------------------------------------
iterator find ( const key_type& x ) const
{   mtx_read BR ( BD);
    return st.find_norep(x);
};
//---------------------------------------------------------------------------
//  function : count
/// @brief return the number of elements in the cntree_set with the key x
/// @param [in] x : key to find
/// @return number of elements in the cntree_set with the key x
/// @remarks This operation is log (N)
//---------------------------------------------------------------------------
signed_type count ( const key_type& x ) const
{   mtx_read BR ( BD);
    return st.count (x);
};
//---------------------------------------------------------------------------
//  function : lower_bound
/// @brief return one iterator to the first appearance of the key x if exist \n
///  and if don't exist return one iterator to the first element greather than x
/// @param [in] x : key to find
/// @return iterator
//---------------------------------------------------------------------------
iterator lower_bound (const key_type& x) const
{   mtx_read BR ( BD);
    return st.lower_bound (x);
};
//---------------------------------------------------------------------------
//  function : upper_bound
/// @brief return one iterator to the first element greather than x. If
///  don't exist any element greather than x , return end()
/// @param [in] x : key to find
/// @return iterator
//---------------------------------------------------------------------------
iterator upper_bound (const key_type& x) const
{   mtx_read BR ( BD);
    return st.upper_bound (x);
};
//---------------------------------------------------------------------------
//  function : equal_range
/// @brief return a pair of iterators, the first is the lower_bound (x) and
///  the second is upper_bound (x)
/// @param [in] X :key to find
/// @return pair of iterators
//---------------------------------------------------------------------------
std::pair<iterator,iterator> equal_range ( const key_type& x ) const
{   mtx_read BR ( BD);
    return st.equal_range (x);
};
//---------------------------------------------------------------------------
//  function : const_iterator_pos
/// @brief Find a position in the cntree_set
/// @param [in] Pos1 : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
const_iterator const_iterator_pos ( signed_type Pos1) const NOEXCEPT
{   mtx_read BR ( BD);
    return  st.const_iterator_pos( Pos1);
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
//**************************************************************************
//  I N S E R T , I N S E R T _ I F , E M P L A C E , E M P L A C E _ H I N T
//
//  template <class ... Args>
//  iterator emplace_internal(mtx_write & BM,connector C, Args && ... args)
//
//  template <class P >
//  mypair insert (  P && Val)
//
//  template <class Function, class P >
//  mypair insert_if (Function && M ,P && Val)
//
//  const_iterator  insert ( const_iterator , const value_type & val )
//
//  const_iterator  insert ( const_iterator , value_type&& val )
//
//  template <class ... Args>
//  mypair emplace (Args && ... args)
//
//  template <class Function , class ... Args>
//  mypair emplace_if ( Function &&  M ,  Args && ... args)
//
//  template <class ... Args>
//  const_iterator   emplace_hint (const_iterator,Args && ... args)
//
//  template <class InputIterator>
//  void insert ( InputIterator first, InputIterator last )
//
//  template <class InputIterator, class Function >
//  void insert_if (InputIterator first, InputIterator last, Function && M)
//
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : emplace_internal
/// @brief insert an element in a the position specified by the connector
/// @param [in] BM : barrier modify needed for to exec the wait_no_readers
///                  inside the function
/// @param [in] C : connector which indicate where must insert the node
/// @param [in] args : arguments to build the node to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) ) This operation don't must be used
///          by the final users
//---------------------------------------------------------------------------
template <class ... Args>
const_iterator emplace_internal(mtx_write & BM,connector C, Args && ... args)
{   //------------------ begin-----------------
    node_t * PAux = st.allocate (1) ;
    st.construct ( PAux , std::forward<Args> ( args) ... );
    BM.wait_no_readers() ;
    st.connect ( PAux , C ) ;
    return st.get_cit ( PAux) ;
};
//---------------------------------------------------------------------
//  function : insert
/// @brief insert a value in the cntree_set
/// @param [in] val : value to insert.It can ve a value , a reference or an rvalue
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done
//----------------------------------------------------------------
template <class P >
mypair insert (  P && Val)
{   //------------------- begin --------------------------
    mtx_write BM  ( BD);
    connector C ;
    node_t *PAux =  st.connector_norep ( std::forward<P>(Val), C );
    bool SW = ( PAux == NULL);
    const_iterator It = (SW)? emplace_internal(BM,C,std::forward<P>(Val)): st.get_cit (PAux);
    return mypair ( It, SW);
};
//---------------------------------------------------------------------
//  function : insert_if
/// @brief insert a value in the cntree_set
/// @param [in] val : value to insert.It can ve a value , a reference or an rvalue
/// @param [in] M : function with the format bool( const value_t &).
///                  if return true the element is iserted , if false not
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done.
///         When the element is rejected by the function , the itertor of the pair
///         is end() and the bool false
//----------------------------------------------------------------
template <class Function, class P >
mypair insert_if (Function && M ,P && Val)
{   //------------------------begin--------------------------------
    mtx_write BM  ( BD);
    connector C ;
    node_t *PAux =  st.connector_norep ( std::forward<P>(Val), C );
    const_iterator It ;
    bool SW = ( PAux == NULL);
    if ( SW)
    {   SW = M( std::forward<P>(Val));
        It = (SW) ?emplace_internal ( BM, C, std::forward<P>(Val)) :cend() ;
    }
    else It = st.get_cit ( PAux);
    return mypair ( It, SW);
};

//---------------------------------------------------------------------------
//  function : insert
/// @brief insert a value in the cntree_set
/// @param [in] val : value to insert
/// @return  returns an iterator to the inserted element, or to the element
///          that prevented the insertion.
//---------------------------------------------------------------------------
const_iterator  insert ( const_iterator , const value_type & val )
{   return ( insert (val).first);
};

//---------------------------------------------------------------------------
//  function : insert
/// @brief insert a value in the cntree_set
/// @param [in] val : value to insert with a move operation
/// @return  returns an iterator to the inserted element, or to the element
///          that prevented the insertion.
//---------------------------------------------------------------------------
const_iterator  insert ( const_iterator , value_type&& val )
{   return ( insert ( std::move( val))).first;
};

//---------------------------------------------------------------------
//  function : emplace
/// @brief insert a value in the cntree_set
/// @param [in] args : arguments needed for to build the node to insert in the cntree_set
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done
//----------------------------------------------------------------
template <class ... Args>
mypair emplace (Args && ... args)
{   //-----------------begin------------------
    mtx_write BM  ( BD);
    connector C ;
    node_t *PAux = st.allocate (1) ;
    st.construct( PAux,  std::forward<Args> (args)... ) ;
    node_t *P2 =  st.connector_norep ( PAux->data, C );

    bool SW = ( P2 == NULL);
    if ( SW)
    {   BM.wait_no_readers() ;
        st.connect (PAux, C);
    }
    else
    {   st.destroy ( PAux);
        st.deallocate ( PAux , 1);
        PAux = P2 ;
    };
    return mypair( st.get_cit ( PAux), SW );
};
//---------------------------------------------------------------------------
//  function : emplace_if
/// @brief insert a value in the cntree_set
/// @param [in] M : function with the format bool( const value_t &).
///                 if return true the element is iserted , if false not
/// @param [in] args : arguments needed for to build the node to insert in the cntree_set
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done.
///         When the element is rejected by the function , the itertor of the pair
///         is end() and the bool false
//---------------------------------------------------------------------------
template <class Function , class ... Args>
mypair emplace_if ( Function &&  M ,  Args && ... args)
{   //------------------------begin--------------------------------
    mtx_write BM  ( BD);
    connector C ;

    node_t * PAux = st.allocate (1) ;
    st.construct( PAux,  std::forward<Args> (args)... ) ;
    if ( not M( PAux->data))
    {   st.destroy ( PAux);
        st.deallocate ( PAux , 1);
        return mypair( cend(),false );
    }

    node_t * P2 = st.connector_norep ( PAux->data,C);
    bool SW = ( P2 == NULL);
    if ( SW)
    {   BM.wait_no_readers() ;
        st.connect(PAux,C);
    }
    else
    {   st.destroy ( PAux);
        st.deallocate ( PAux , 1);
        PAux = P2 ;
    };
    return mypair( st.get_cit ( PAux), SW );
};
//---------------------------------------------------------------------
//  function : emplace_hint
/// @brief insert a value in the cntree_set
/// @param [in] X : value to insert
/// @return iterator to the element inserted or or to the element that
///         prevented the insertion if the insertion is done if not end()
//----------------------------------------------------------------
template <class ... Args>
const_iterator   emplace_hint (const_iterator,Args && ... args)
{   return (emplace (  std::forward<Args> (args)...)).first;
};

//----------------------------------------------------------------
//  function : insert
/// @brief Insertion of range of elements from two iterators
/// @param [in] first : Iterator to the first element of the range
/// @param [in] last : Iterator to the last lement of the range
/// @return none
//----------------------------------------------------------------
template <class InputIterator>
void insert ( InputIterator first, InputIterator last )
{   //------------- begin --------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.insert_norep( first, last) ;
};
//----------------------------------------------------------------
//  function : insert_if
/// @brief Insertion of range of elements from two iterators
/// @param [in] first : Iterator to the first element of the range
/// @param [in] last : Iterator to the last lement of the range
/// @param [in] M : function with the format bool( const value_t &).
///                  if return true the element is iserted , if false not
/// @return none
//----------------------------------------------------------------
template <class InputIterator, class Function >
void insert_if (InputIterator first, InputIterator last, Function && M)
{   //------------- begin --------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.insert_norep_if( first, last, M) ;
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
//                     P O P _ F R O N T
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
//  template <class Function>
//  uint32_t pop_move_front_if ( value_t & V, Function && M1)
//
//***************************************************************************
//
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
    st.pop_front() ;
};
//---------------------------------------------------------------------------
//  function : pop_front_if
/// @brief erase the first element of the container
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O (constant)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_front_if ( Function &&  M1  )
{   //--------------------------- begin ------------------
    mtx_write BM ( BD);
    if ( st.size() == 0 ) return 1 ;
    bool SW =  M1 ( st.front());
    if ( SW)
    {   BM.wait_no_readers() ;
        st.pop_front() ;
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
    if ( st.size() == 0) return 1 ;
    V = st.front();
    BM.wait_no_readers() ;
    st.pop_front();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_front_if
/// @brief erase the first element of the tree and return a copy
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format bool(const value_t &).
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
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.front() ) )return 2 ;   ;
    V = st.front() ;
    BM.wait_no_readers() ;
    st.pop_front();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_front
/// @brief erase the first element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_move_front ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    V = std::move(st.front()) ;
    BM.wait_no_readers() ;
    st.pop_front();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_front_if
/// @brief erase the first element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_move_front_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.front() ) ) return 2 ;   ;
    V = std::move(st.front()) ;
    BM.wait_no_readers() ;
    st.pop_front() ;
    return 0;
};
//
//***************************************************************************
//                    P O P _ B A C K
//
//  void pop_back ( void)
//
//  template <class Function>
//  uint32_t pop_back_if ( Function &&  M1)
//
//  uint32_t pop_copy_back ( value_t & V)
//
//  template <class Function>
//  uint32_t pop_copy_back_if ( value_t & V, Function && M1)
//
//  uint32_t pop_move_back ( value_t & V)
//
//  template <class Function>
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
    st.pop_back() ;
};
//---------------------------------------------------------------------------
//  function :pop_back_if
/// @brief erase the last element of the container
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_back_if ( Function &&  M1)
{   //---------------------- begin ----------------
    mtx_write BM ( BD);
    if ( st.size() == 0 ) return 1 ;
    bool SW = M1 ( st.back());
    if ( SW)
    {   BM.wait_no_readers() ;
        st.pop_back() ;
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
    if ( st.size() == 0) return 1 ;
    V = st.back() ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_back_if
/// @brief erase the last element of the tree and return a copy
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_copy_back_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.back() ) ) return 2 ;   ;
    V = st.back() ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_back
/// @brief erase the last element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
uint32_t pop_move_back ( value_t & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    V = std::move( st.back()) ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_back_if
/// @brief erase the last element of the tree and return a copy with rvalues
/// @param [out] V : reference to a variable where copy the element
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_move_back_if ( value_t & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.back() ) ) return 2 ;   ;
    V = std::move(st.back()) ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//
//***************************************************************************
//                  E R A S E , E R A S E _ P O S
//
//  const_iterator erase ( const_iterator iter )
//
//  template <class Function>
//  const_iterator erase_if ( const_iterator iter, Function && M)
//
//  const_iterator erase ( const_iterator first, const_iterator last )
//
//  template <class Function>
//  signed_type erase_if ( const_iterator first_it, const_iterator last_it,
//                        Function &&  M)
//
//  signed_type erase ( const key_type& x )
//
//  template <class Function>
//  signed_type erase_if ( const key_type& x , Function && M)
//
//  void erase_pos( signed_type Pos)
//
//  template <class Function>
//  void erase_pos_if( signed_type Pos, Function && M)
//
//  void erase_pos ( signed_type Prim, signed_type NElem)
//
//  template <class Function>
//  void erase_pos_if( signed_type Pos, Function && M)
//
//***************************************************************************
//
//----------------------------------------------------------------
//  function : erase
/// @brief erase the element pointed by iter
/// @param [in] iter : iterator to the element to erase
/// @return none
//----------------------------------------------------------------
const_iterator erase ( const_iterator iter )
{   //---------- begin -------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return st.erase( iter );
};

//----------------------------------------------------------------
//  function : erase_if
/// @brief erase the element pointed by iter
/// @param [in] iter : iterator to the element to erase
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return iterator to the next element to iter
//----------------------------------------------------------------
template <class Function>
const_iterator erase_if ( const_iterator iter, Function && M)
{   //---------- begin -------------
    mtx_write BM ( BD);
    const_iterator Alfa = iter +1 ;
    BM.wait_no_readers() ;
    if ( M ( *iter))    st.erase( iter );
    return Alfa ;
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase a range of elements in the range first, last
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @return none
//---------------------------------------------------------------------------
const_iterator erase ( const_iterator first, const_iterator last )
{   //---------- begin ---------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.erase ( first , last);
    return (last) ;
};
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : const_iterator to the first element
/// @param [in] last_it : const_iterator to the final element of the range
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
signed_type erase_if ( const_iterator first_it, const_iterator last_it,
                      Function &&  M)
{   //--------------------------- begin ---------------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return st.erase_if ( first_it, last_it,M);
};
//----------------------------------------------------------------
//  function : erase
/// @brief Erase all the elements with a key
/// @param [in] x : key of all the elements to erase
/// @return number of elements erased
//----------------------------------------------------------------
signed_type erase ( const key_type& x )
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator I = st.find_norep(x) ;
    if ( I == end()) return 0 ;
    BM.wait_no_readers() ;
    st.erase( I);
    return 1 ;
} ;
//----------------------------------------------------------------
//  function : erase_if
/// @brief Erase all the elements with a key
/// @param [in] x : key of all the elements to erase
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return number of elements erased
//----------------------------------------------------------------
template <class Function>
signed_type erase_if ( const key_type& x , Function && M)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator I = st.find_norep(x) ;
    if ( I == end()) return 0 ;
    signed_type N = 0 ;
    if ( M ( *I))
    {   BM.wait_no_readers() ;
        st.erase( I);
        N++;
    };
    return N ;
} ;
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @return void
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
void erase_pos( signed_type Pos)
{   //--------------------- begin --------------
    mtx_write BM ( BD);
    iterator I = st.iterator_pos ( Pos);
    BM.wait_no_readers() ;
    st.erase ( I);
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return void
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class Function>
void erase_pos_if( signed_type Pos, Function && M)
{   //--------------------- begin --------------
    mtx_write BM ( BD);
    iterator I = st.iterator_pos ( Pos);
    if ( M ( *I))
    {   BM.wait_no_readers() ;
        st.erase ( I);
    };
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase  NElem elements beginning in the position Prim
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : Number of elements to delete
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void erase_pos ( signed_type Prim, signed_type NElem)
{   //---------------------- begin ------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.erase_pos( Prim, NElem);
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the lements between the position Prim and the position Ult.
///        The position Ult is deleted
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : Number of elements to delete
/// @param [in] M : function with the format bool(const value_t &).
///                 if return true the element is deleted , if false not
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function >
signed_type erase_pos_if ( signed_type Prim, signed_type NElem,Function && M)
{   //----------------------------- begin -----------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return st.erase_pos_if( Prim,NElem,M);
};
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #       U T I L I T Y     F U N C T I O N S        #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//
//**************************************************************************
//         O B S E R V E R S
//
//  key_compare     key_comp      ( ) const;
//  value_compare   value_comp    ( ) const;
//  allocator_type  get_allocator ( ) const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : key_comp
/// @brief return the object used to compare two keys
/// @param [in] none
/// @return object used to compare two keys
//---------------------------------------------------------------------------
key_compare key_comp ( ) const
{   mtx_read BR ( BD);
    return st.key_comp();
};
//---------------------------------------------------------------------------
//  function : value_comp
/// @brief return the object used to compare two values
/// @param [in] none
/// @return object used to compare two values
//---------------------------------------------------------------------------
value_compare value_comp ( ) const
{   mtx_read BR ( BD);
    return st.key_comp();
};
//---------------------------------------------------------------------------
//  function : get_allocator
/// @brief return the object allocator of the cntree_set
/// @param [in] none
/// @return object allocator
//---------------------------------------------------------------------------
allocator_type &get_allocator() const
{   mtx_read BR ( BD);
    return st.get_allocator();
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
//***************************************************************************
//          I T E R A T O R S
//
//  bool        is_mine ( const_iterator it) const;
//  bool        is_mine ( const_reverse_iterator it) const
//
//***************************************************************************
//
//----------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_set
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_set
/// @remarks This operation is O ( const )
//------------------------------------------------------------------------
bool is_mine ( const_iterator it) const
{   mtx_read BR ( BD);
    return st.is_mine(it) ;
};
//----------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_set
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_set
/// @remarks This operation is O ( const )
//------------------------------------------------------------------------
bool is_mine ( const_reverse_iterator it) const
{   mtx_read BR ( BD);
    return st.is_mine(it) ;
};

//
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
const_iterator cit_begin  ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cit_begin();
};
//---------------------------------------------------------------------------
//  function :begin
/// @return const_iterator to the first element
//---------------------------------------------------------------------------
const_iterator begin      ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.begin();
};
//---------------------------------------------------------------------------
//  function :cbegin
/// @return const_iterator to the first element
//---------------------------------------------------------------------------
const_iterator cbegin     ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cbegin();
};
//---------------------------------------------------------------------------
//  function : cit_end
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator cit_end    ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cit_end( );
};
//---------------------------------------------------------------------------
//  function : end
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator end        ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.end();
};
//---------------------------------------------------------------------------
//  function : cend
/// @return const_iterator to the next element after the last
//---------------------------------------------------------------------------
const_iterator cend       ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cend();
};
//---------------------------------------------------------------------------
//  function : cit_rbegin
/// @return const_iterator to the last element
//---------------------------------------------------------------------------
const_iterator cit_rbegin ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cit_rbegin();
};
//---------------------------------------------------------------------------
//  function : cit_rend
/// @return const_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_iterator cit_rend   ( void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.cit_rend( );
};

//
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
const_reverse_iterator crit_begin (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crit_begin();
};
//---------------------------------------------------------------------------
//  function : crit_end
/// @return const_reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
const_reverse_iterator crit_end   (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crit_end();
};
//---------------------------------------------------------------------------
//  function : crit_rbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator crit_rbegin(void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crit_rbegin();
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator rbegin     (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.rbegin();
};
//---------------------------------------------------------------------------
//  function : crbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator crbegin    (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crbegin();
};
//---------------------------------------------------------------------------
//  function : crit_rend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator crit_rend  (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crit_rend();
};
//---------------------------------------------------------------------------
//  function : rend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator rend  (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.rend() ;
};
//---------------------------------------------------------------------------
//  function : crend
/// @return const_reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_reverse_iterator crend      (void) const NOEXCEPT
{   mtx_read BR ( BD);
    return st.crend();
};
#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the cntree_set
/// @param [in] salida : ostream where write the information
/// @param [in] A : cntree_set to print
/// @return ostream after the printing
//---------------------------------------------------------------------------
friend std::ostream & operator<<(std::ostream &salida ,
                                 const cntree_set<value_t,cnc,comp_key_t,alloc_t>& A)
{   //--------------------------- begin ------------------------------
    mtx_read BR ( A.BD);
    salida<< A.st;
    return salida ;
};
#endif
//***************************************************************************
};//              E N D     S E T      C L A S S
//***************************************************************************

//***************************************************************************
};//              E N D    C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
