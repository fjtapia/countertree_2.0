//----------------------------------------------------------------------------
/// @file   cntree_map.hpp
/// @brief  This file contains the implementation of cntree_map and multimap,
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
#ifndef __COUNTERTREE_FOREST_MAP_HPP
#define __COUNTERTREE_FOREST_MAP_HPP

#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/mutex_read_write.hpp>
#include <boost/countertree/filter.hpp>
#include <boost/countertree/forest/sorted_tree.hpp>


namespace countertree
{
namespace c_forest = countertree::forest ;
using c_forest::connector;
//using countertree::common::config_alloc ;
template < class Key ,class Data, bool cnc, class Comp,class Alloc  >
class cntree_multimap  ;
//##########################################################################
//                                                                        ##
//                         C L A S S                                      ##
//                                                                        ##
//          M A P  < KEY_T , DATA_T, CNC, COMP_KEY_T , ALLOC_T >          ##
//                                                                        ##
//##########################################################################

//-------------------------------------------------------------
/// @class  cntree_map
/// @brief  This class have the same interface and functions than the
///         class cntree_map defined in the Standard Template Library ( STL),
///         plus a function  at which permit to access to the elements
///         of the cntree_map by their position
///         This class cntree_map have too, iterators with random access, which
///         permit increment and decrement any value to the iterators
/// @remarks
//----------------------------------------------------------------
template <  typename key_t,
            typename data_t,
            bool cnc         = false ,
            class comp_key_t = std::less<key_t>,
            typename alloc_t = cntree_allocator<void>
         >
class cntree_map
{
public :

//***************************************************************************
//               P U B L I C       D E F I N I T I O N S
//***************************************************************************
typedef typename config_fastmutex<cnc>::fastmutex_data   mtx_data ;
typedef mutex_read <mtx_data>                            mtx_read ;
typedef mutex_write<mtx_data>                            mtx_write ;


typedef key_t                                                    key_type;
typedef data_t                                                   mapped_type ;
typedef std::pair<const key_t,data_t >                           value_type ;
typedef filter_map<key_t , value_type>                           filter_t ;
typedef c_forest::sorted_tree<value_type,key_t,filter_t,comp_key_t,alloc_t>  srt_tree_t ;

typedef typename srt_tree_t::size_type                           size_type ;
typedef typename srt_tree_t::difference_type                     difference_type ;
typedef comp_key_t                                               key_compare ;
typedef alloc_t                                                  allocator_type ;

typedef  value_type &                                            reference ;
typedef  const value_type &                                      const_reference ;
typedef  value_type *                                            pointer ;
typedef  const value_type *                                      const_pointer ;

typedef comp_pair<key_t,data_t,comp_key_t>                       ValueCompare;
typedef filter_map<key_t , value_type>                           filter ;

typedef typename srt_tree_t::tree                                tree ;
typedef typename srt_tree_t::node_t                              node_t;
typedef typename srt_tree_t::iterator                            iterator;
typedef typename srt_tree_t::const_iterator                      const_iterator ;
typedef typename srt_tree_t::reverse_iterator                    reverse_iterator;
typedef typename srt_tree_t::const_reverse_iterator              const_reverse_iterator;
typedef std::pair<iterator, bool >                               mypair ;

private :
//**************************************************************************
//             P R I V A T E       D E F I N I T I O N S
//
//**************************************************************************
//friend class multimap <key_t, data_t,cnc, comp_key_t, alloc_t >;
template <class key_t2, class data_t2, bool cnc2 ,class comp_key_t2 ,class alloc_t2 > friend class cntree_map;
template <class key_t2, class data_t2, bool cnc2 ,class comp_key_t2 ,class alloc_t2 > friend class cntree_multimap;
//***************************************************************************
//                 P R I V A T E        V A R I A B L E S
//***************************************************************************
srt_tree_t st ;

public:
//***************************************************************************
//                 P U B L I C         V A R I A B L E S
//***************************************************************************
mutable mtx_data BD ;
//
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
//   C O N S T R U C T O R , D E S T R U C T O R
//
//  explicit cntree_map ( const comp_key_t& C1 = comp_key_t(),
//                const alloc_t & A= alloc_t() ) ;
//
//  explicit    cntree_map ( const alloc_t & A )
//              cntree_map ( const cntree_map & m )
//              cntree_map ( cntree_map && m )
//
//  template <class InputIterator>
//  cntree_map (   InputIterator first     ,
//                 InputIterator last      ,
//                 const comp_key_t& C1 = comp_key_t() ,
//                 const alloc_t & A1= alloc_t()  )
//
//  cntree_map( const cntree_map & m , const alloc_t & A)
//
//  template < typename alloc_t2 , bool cnc2 >
//  cntree_map ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
//
//  template <  bool cnc2 >
//  cntree_map(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
//
//  virtual ~cntree_map();
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Constructor from an object Comparer and an object Allocator
/// @param [in] C1 : Comparer
/// @param [in] A1 : Allocator
//---------------------------------------------------------------------------
explicit cntree_map ( const comp_key_t& C1 = comp_key_t(),
               const alloc_t & A= alloc_t() ) : st(C1,A){  };

//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Constructor from an object Allocator
/// @param [in] A1 : Allocator
//---------------------------------------------------------------------------
explicit cntree_map ( const alloc_t & A ) : st(comp_key_t(),A){  };

//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Constructor from a pair of iterators and an object
///         Comparer and an object Allocator
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] C1 : Comparer
/// @param [in] A1 : Allocator
//---------------------------------------------------------------------------
template <class InputIterator>
cntree_map ( InputIterator first     ,
             InputIterator last      ,
             const comp_key_t& C1 = comp_key_t() ,
             const alloc_t & A1= alloc_t()  )  : st ( C1, A1 )
{   //---------------------begin ----------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers();
    st.insert_norep ( first, last );
};
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Copy constructor
/// @param [in] m :cntree_map from where copy the data
//---------------------------------------------------------------------------
cntree_map( const cntree_map & m ): st ( m.st.key_comp(),m.st.get_allocator())
{   //-------------------------- begin -------------------------
    mutex_write_read <mtx_data,mtx_data> BM ( BD, m.BD);
    BM.wait_no_readers() ;
    st = m.st ;
};
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Copy constructor
/// @param [in] m :cntree_map from where copy the data
/// @param [in] A : Allocator
//---------------------------------------------------------------------------
cntree_map( const cntree_map & m , const alloc_t & A): st ( m.st.key_comp(),A)
{   //-------------------------- begin -------------------------
    mutex_write_read <mtx_data,mtx_data> BM ( BD, m.BD);
    BM.wait_no_readers() ;
    st = m.st ;
};
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Copy constructor
/// @param [in] m :cntree_map from where copy the data
//---------------------------------------------------------------------------
cntree_map(  cntree_map && m ): st ( m.st.key_comp(),m.st.get_allocator())
{   //-------------------------- begin -------------------------
    mutex_write_write <mtx_data , mtx_data> BM ( BD, m.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move( m.st);
};
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Copy constructor
/// @param [in] m :cntree_map from where copy the data
//---------------------------------------------------------------------------
template < typename alloc_t2 , bool cnc2 >
cntree_map ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
:st ( m.st.key_comp())
{   //------------------------ begin -----------------------------
    typedef typename cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>::mtx_data mtx_data2 ;
    mutex_write_read <mtx_data, mtx_data2> BM ( BD, m.BD)   ;
    BM.wait_no_readers() ;
    st = m.st ;
};
//---------------------------------------------------------------------------
//  function : cntree_map
/// @brief  Copy constructor
/// @param [in] m :cntree_map from where copy the data
//---------------------------------------------------------------------------
template <  bool cnc2 >
cntree_map(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
: st ( m.st.key_comp(),m.st.get_allocator())
{   //-------------------------- begin -------------------------
    typedef typename cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t>::mtx_data mtx_data2 ;
    mutex_write_write < mtx_data, mtx_data2> BM ( BD, m.BD)    ;
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move( m.st);
};
//---------------------------------------------------------------------------
//  function : ~cntree_map
/// @brief  Destructor
//---------------------------------------------------------------------------
virtual ~cntree_map(){ };

//
//***************************************************************************
//  O P E R A T O R = , S W A P , C L E A R
//
//  cntree_map  & operator= ( const cntree_map & m)
//  cntree_map  & operator= (  cntree_map && m)
//
//  template < typename alloc_t2 , bool cnc2 >
//  cntree_map & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
//
//  template <  bool cnc2 >
//  cntree_map & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
//
//  void swap ( cntree_map & mp )
//  void clear ( void)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] m : cntree_map from where copy the data
/// @return Reference to the cntree_map after the copy
//---------------------------------------------------------------------------
cntree_map  & operator= ( const cntree_map &m)
{   //----------------------- begin -----------------------
    if ( this == &m) return *this ;
    mutex_write_read <mtx_data, mtx_data> BM ( BD, m.BD);
    BM.wait_no_readers() ;
    st = m.st;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] m : cntree_map from where move the data
/// @return Reference to the cntree_map after the copy
//---------------------------------------------------------------------------
cntree_map  & operator= (  cntree_map &&m)
{   //----------------------- begin -----------------------
    if ( this == &m) return *this ;
    mutex_write_write <mtx_data, mtx_data> BM ( BD, m.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move(m.st);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] m : cntree_map from where copy the data
/// @return Reference to the cntree_map after the copy
//---------------------------------------------------------------------------
template < typename alloc_t2 , bool cnc2 >
cntree_map & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
{   //------------------------ begin -----------------------------
    if (  (void*)this == (void*)(&m) ) return *this ;
    typedef typename cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>::mtx_data mtx_data2 ;
    mutex_write_read <mtx_data, mtx_data2> BM ( BD, m.BD) ;
    BM.wait_no_readers() ;
    st = m.st ;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] m : cntree_map from where move the data
/// @return Reference to the cntree_map after the copy
//---------------------------------------------------------------------------
template <  bool cnc2 >
cntree_map & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
{   //-------------------------- begin -------------------------
    if (  (void*)this == (void*)(&m) ) return *this ;
    typedef typename cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t>::mtx_data mtx_data2 ;
    mutex_write_write <mtx_data,mtx_data2 > BM ( BD, m.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st = std::move( m.st);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : swap
/// @brief swap the data of the cntree_map st with the actual cntree_map
/// @param [in] mp : cntree_map to swap
/// @return none
//---------------------------------------------------------------------------
void swap ( cntree_map & mp )
{   //--------------- begin -------------
    if ( this == &mp) return ;
    mutex_write_write <mtx_data, mtx_data> BM ( BD, mp.BD);
    BM.wait_no_readers_first() ;
    BM.wait_no_readers_second() ;
    st.swap ( mp.st);
};
//---------------------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the cntree_map
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void clear ( void)
{   //-------------- begin ------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.clear();
};
//***************************************************************************
//                 C A P A C I T Y
//
//  bool        empty    ( void) const ;
//  size_type   size     ( void) const ;
//  size_type   max_size ( void) const ;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : empty
/// @brief indicate if the cntree_map is empty
/// @return true if the cntree_map is empty, false in any other case
//---------------------------------------------------------------------------
bool empty (void) const
{   mtx_read BR ( BD);
    return st.empty();
};
//---------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements in the cntree_map
/// @return number of elements in the cntree_map
//---------------------------------------------------------------------------
size_type size (void) const
{   mtx_read BR ( BD);
    return st.size() ;
};
//---------------------------------------------------------------------------
//  function : max_size
/// @brief return the maximun size of the container
/// @return maximun size of the container
//---------------------------------------------------------------------------
size_type max_size ( void) const
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
//***************************************************************************
//      P O S , I T E R A T O R _ P O S , F R O N T , B A C K
//
//        value_t & pos ( signed_type Pos1)       NOEXCEPT
//  const value_t & pos ( signed_type Pos1) const NOEXCEPT
//
//        iterator iterator_pos ( signed_type Pos1)       NOEXCEPT
//  const_iterator iterator_pos ( signed_type Pos1) const NOEXCEPT
//
//        value_t & front ( void)       NOEXCEPT
//  const value_t & front ( void) const NOEXCEPT
//
//        value_t & back (void )       NOEXCEPT
//  const value_t & back (void ) const NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : pos
/// @brief  Access to an element by their position in the cntree_map
/// @param  in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This is an random access function of the cntree_map.
///          This operation is log(N) \n I didn't use
///          the operator [ ] because it is used in the cntree_map class.\n
///          The function at is used in std cntree_map in C++11\n
///          It is very important to be uniform access method in the
///          four classes ( cntree_set, cntree_multiset, cntree_map and cntree_multimap)
//---------------------------------------------------------------------------
value_type & pos ( signed_type Pos1) NOEXCEPT
{   mtx_read BR ( BD );
    return  ( st.pos(Pos1) );
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief  Access to an element by their position in the cntree_map
/// @param  in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This is an random access function of the cntree_map.
///          This operation is log(N) \n I didn't use
///          the operator [ ] because it is used in the cntree_map class.\n
///          The function at is used in std cntree_map in C++11\n
///          It is very important to be uniform access method in the
///          four classes ( cntree_set, cntree_multiset, cntree_map and cntree_multimap)
//---------------------------------------------------------------------------
const value_type & pos ( signed_type Pos1) const NOEXCEPT
{   mtx_read BR ( BD );
    return  ( st.pos(Pos1) );
};
//---------------------------------------------------------------------------
//  function : iterator_pos
/// @brief Find a position in the sorted_tree
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
iterator iterator_pos ( signed_type Pos1) NOEXCEPT
{   mtx_read BR ( BD );
    return  st.iterator_pos( Pos1);
};
//---------------------------------------------------------------------------
//  function : const_iterator_pos
/// @brief Find a position in the sorted_tree
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
const_iterator const_iterator_pos ( signed_type Pos1) const NOEXCEPT
{   mtx_read BR ( BD );
    return  st.const_iterator_pos( Pos1);
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_type & front ( void) NOEXCEPT
{   mtx_read BR ( BD );
    return st.front() ;
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_type & front ( void) const NOEXCEPT
{   mtx_read BR ( BD );
    return st.front() ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_type & back (void ) NOEXCEPT
{   mtx_read BR ( BD );
    return st.back();
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_type & back (void ) const NOEXCEPT
{   mtx_read BR ( BD );
    return st.back();
};
//
//***************************************************************************
//               F I N D ,  C O U N T , L O W E R _ B O U N D
//              U P P E R _ B O U N D , E Q U A L _ R A N G E
//
//  iterator        find  ( const Key& x );
//  const_iterator  find  ( const Key& x ) const
//  size_type       count ( const Key& x ) const;
//
//  iterator        lower_bound ( const Key & x );
//  const_iterator  lower_bound ( const Key & x ) const;
//
//  iterator        upper_bound ( const Key& x );
//  const_iterator  upper_bound ( const Key& x ) const;
//
//  std::pair<iterator,iterator>     equal_range ( const Key& x );
//
//  std::pair<const_iterator,const_iterator>
//  equal_range (const Key& x )const;
//
//***************************************************************************

//----------------------------------------------------------------------------
//  function : find
/// @brief return the iterator to the element with the key x
/// @param [in] x : key to find in the cntree_map
/// @return iterator to the element with the key x. If don't exist return end()
//------------------------------------------------------------------------------
iterator find ( const key_type& x )
{   mtx_read BR ( BD);
    return st.find_norep(x);
};
//---------------------------------------------------------------------------
//  function : find
/// @brief return the const_iterator to the element with the key x
/// @param [in] x : key to find in the cntree_map
/// @return const_iterator to the element with the key x. If don't
/// exist return end()
//---------------------------------------------------------------------------
const_iterator find ( const key_type& x ) const
{   mtx_read BR ( BD);
    return st.find_norep(x);
};
//---------------------------------------------------------------------------
//  function : read
/// @brief Return an copy of the object in the tree. If exist return true. If
///        don't exist  return false \n
///        This function supouse there is only one element with the key
/// @param [in] V : object where copy the element of the tree
/// @param [in] Key : key to search
/// @return bool true- copy in V false didn't find in the tree
/// @remarks
//---------------------------------------------------------------------------
bool read ( value_type &V,const key_t & K ) const
{   //----------------------------- begin ------------------------------
    mtx_read BR ( BD);
    const_iterator It = find( K);
    if ( It == cit_end()) return false ;
    const_cast <key_t &> ( V.first) = It->first ;
    V.second = It->second ;
    //V = *It ;
    return true ;
};
//---------------------------------------------------------------------------
//  function : count
/// @brief return the number of elements in the cntree_map with the key x
/// @param [in] x : key to find
/// @return number of elements in the set with the key x
/// @remarks This operation is log (N)
//---------------------------------------------------------------------------
size_type count ( const key_type& x ) const
{   mtx_read BR ( BD);
    return st.count (x);
};
//--------------------------------------------------------------------------
//  function : lower_bound
/// @brief return one iterator to the first appearance of the key x
/// if exist and if don't exist return one iterator to the first
/// element greather than x
/// @param [in] x : key to find
/// @return iterator
//--------------------------------------------------------------------------
iterator lower_bound ( const key_type & x )
{   mtx_read BR ( BD);
    return st.lower_bound (x);
};
//--------------------------------------------------------------------------
//  function :lower_bound
/// @brief return one const_iterator to the first appearance of the key x
/// if exist \n and if don't exist return one iterator to the first element
/// greather than x
/// @param [in] x : key to find
/// @return const_iterator
//---------------------------------------------------------------------------
const_iterator lower_bound (const key_type &x) const
{   mtx_read BR ( BD);
    return st.lower_bound (x);
};
//---------------------------------------------------------------------------
//  function : upper_bound
/// @brief return one iterator to the first element greather than x. If
/// don't exist any element greather than x , return end()
/// @param [in] x : key to find
/// @return iterator
//--------------------------------------------------------------------------
iterator upper_bound (const key_type& x)
{   mtx_read BR ( BD);
    return st.upper_bound (x);
};
//--------------------------------------------------------------------------
// function : upper_bound
/// @brief return one const_iterator to the first element greather than x.
/// If don't exist any element greather than x , return end()
/// @param [in] x : key to find
/// @return const_iterator
//------------------------------------------------------------------------
const_iterator upper_bound (const key_type &x) const
{   mtx_read BR ( BD);
    return st.upper_bound (x);
};
//----------------------------------------------------------------------
//  function : equal_range
/// @brief return a pair of iterators, the first is the lower_bound (x)
/// and the second is upper_bound (x)
/// @param [in] X :key to find
/// @return pair of iterators
//----------------------------------------------------------------------
std::pair <iterator,iterator> equal_range ( const key_type& x )
{   mtx_read BR ( BD);
    return st.equal_range (x);
};
//--------------------------------------------------------------------------
//  function : equal_range
/// @brief return a pair of const_iterators, the first is the lower_bound(x)
/// and the second is upper_bound (x)
/// @param [in] X :key to find
/// @return pair of const_iterators
//---------------------------------------------------------------------------
std::pair <const_iterator,const_iterator> equal_range (const key_type& x )const
{   mtx_read BR ( BD);
    return st.equal_range (x);
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
//  O P E R A T O R [ ] , I N S E R T , E M P L A C E
//
//  data_t & operator[] ( const Key  &K );
//
//  template <class P > mypair insert ( P && val )
//
//  template <class P ,class Function>
//  mypair insert_if ( Function &&  M, P && val )
//
//  template <class P >
//  iterator insert ( const_iterator, P && val )
//
//  template <class ... Args>
//  mypair emplace (Args && ... args)
//
//  template <class Function , class ... Args>
//  mypair emplace_if (Function &&  M , Args && ... args)
//
//  template <class ... Args>
//  iterator emplace_hint ( const_iterator , Args && ... args )
//
//  template <class InputIterator>
//  void insert ( InputIterator first, InputIterator last )
//
//  template <cclass InputIterator, class Function >
//  void insert_if ( InputIterator first, InputIterator last,Function && M )
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator[ ]
/// @brief  Return the Data with the key K, if don't exist , inserts a
///         new pair (key, Data) with that key and returns a reference
///         to this pair
/// @param [in] K  key to find in the cntree_map
/// @return reference to the Data of the pair with key K
//---------------------------------------------------------------------------
data_t & operator[] ( const key_type  &K )
{   //------------------------ begin -----------------------------
    mtx_write BM ( BD);
    connector C ;
    node_t *PAux = st.connector_norep( K , C);
    if ( PAux != NULL) return PAux->data.second ;

    PAux = st.allocate (1) ;
    st.construct ( PAux , K, data_t()  );
    BM.wait_no_readers() ;
    st.connect( PAux, C);
    return ( PAux->data.second );
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert a value in the cntree_map. Can ve a value, a reference or an rvalue
/// @param [in] val : value to insert. Can ve a value, a reference or an rvalue
/// @return Pair of elements, the first is one iterator to the element
///         inserted \n and the second is a boolean which indcate if
///         the iterator is end()
//---------------------------------------------------------------------------
template <class P >
mypair insert ( P && val )
{   //---------------------------- begin ---------------------------------
    mtx_write BM ( BD);
    connector C ;
    node_t *PAux = st.connector_norep( st.fltr(std::forward<P> (val)) , C);
    bool SW = ( PAux == NULL);
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , std::forward<P> (val)  );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
    };
    return mypair ( st.get_it (PAux), SW);
};

//---------------------------------------------------------------------------
//  function : insert_if
/// @brief insert a value in the cntree_map. Can ve a value, a reference or an rvalue
/// @param [in] M : function with the format (bool M (value_t &)).
///                  if return true the element is iserted , if false not
/// @param [in] val : value to insert. Can ve a value, a reference or an rvalue
/// @return Pair of elements, the first is one iterator to the element
///         inserted \n and the second is a boolean which indcate if
///         the iterator is end()
//---------------------------------------------------------------------------
template <class P ,class Function>
mypair insert_if ( Function &&  M, P && val )
{   //---------------------------- begin ---------------------------------
    mtx_write BM ( BD);
    connector C ;

    node_t *PAux = st.connector_norep( st.fltr(std::forward<P>(val)) , C);
    bool SW ( PAux == NULL and M (std::forward<P>(val)) );
    iterator I ;
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , std::forward<P>(val)  );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
        I =st.get_it ( PAux);
    }
    else  I = st.end();
    return mypair ( I , SW) ;
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert a value in the cntree_map. Can ve a value, a reference or an rvalue
/// @param [in] val : value to insert. Can ve a value, a reference or an rvalue
/// @return Iterator to the element inserted. If it is not possible return end()
//---------------------------------------------------------------------------
template <class P >
iterator insert ( const_iterator, P && val )
{   //---------------------------- begin ---------------------------------
    return ( insert( std::forward<P>(val)).first);
}
//---------------------------------------------------------------------------
//  function : emplace
/// @brief insert a value in the cntree_map
/// @param [in] args : argument for to compose the element to insert
/// @return Pair of elements, the first is one iterator to the element
///         inserted \n and the second is a boolean which indcate if
///         the iterator is end()
//---------------------------------------------------------------------------
template <class ... Args>
mypair emplace (Args && ... args)
{   //-----------------begin------------------
    mtx_write BM  ( BD);
    connector C ;
    node_t *PAux = st.allocate (1) ;
    st.construct( PAux,  std::forward<Args> (args)... ) ;
    node_t *P2 =  st.connector_norep ( st.fltr(PAux->data), C );

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
    return mypair( st.get_it ( PAux), SW );
};
//---------------------------------------------------------------------------
//  function : emplace_if
/// @brief insert a value in the set
/// @param [in] M : function with the format (bool M (value_t &))
///                  if return true the element is iserted , if false not
/// @param [in] args : argument for to compose the element to insert
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done.
///         When the element is rejected by the function , the itertor of the pair
///         is end() and the bool false
//---------------------------------------------------------------------------
template <class Function , class ... Args>
mypair emplace_if (Function &&   M , Args && ... args)
{   //------------------------begin--------------------------------
    mtx_write BM  ( BD);
    connector C ;

    node_t * PAux = st.allocate (1) ;
    st.construct( PAux,  std::forward<Args> (args)... ) ;
    if ( not M( PAux->data) )
    {   st.destroy ( PAux);
        st.deallocate ( PAux , 1);
        return mypair( st.end(),false );
    };

    node_t * P2 = st.connector_norep ( st.fltr(PAux->data),C);
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
    return mypair( st.get_it ( PAux), SW );
};
//---------------------------------------------------------------------------
//  function : emplace_hint
/// @brief insert a value in the cntree_map
/// @param [in] args : argument for to compose the element to insert
/// @return Pair of elements, the first is one iterator to the element
///         inserted \n and the second is a boolean which indcate if
///         the iterator is end()
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_hint ( const_iterator , Args && ... args )
{   //------------------------ begin -----------------------
    return ( emplace ( std::forward<Args> (args)...)).first ;
};

//---------------------------------------------------------------------------
//  function : insert
/// @brief Insertion of range of elements from two iterators
/// @param [in] first : Iterator to the first element of the range
/// @param [in] last : Iterator to the last lement of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void insert ( InputIterator first, InputIterator last )
{   //------------- begin --------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.insert_norep ( first,last);
};
//---------------------------------------------------------------------------
//  function : insert_if
/// @brief Insertion of range of elements from two iterators
/// @param [in] first : Iterator to the first element of the range
/// @param [in] last : Iterator to the last lement of the range
/// @param [in] M : function with the format (bool M (value_t &))
///                  if return true the element is iserted , if false not
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator , class Function >
void insert_if ( InputIterator first, InputIterator last,Function && M )
{   //--------------------- begin -------------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.insert_norep_if ( first,last, M);
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
//                   P O P _ F R O N T
//
//  void     pop_front ( void )
//
//  template <class Function> uint32_t pop_front_if ( Function &&  M1  )
//
//  uint32_t pop_copy_front ( value_type & V)
//
//  template <class Function>
//  uint32_t pop_copy_front_if ( value_type & V, Function &&  M1)
//
//  uint32_t pop_move_front ( value_type & V)
//
//  template <class Function>
//  uint32_t pop_move_front_if ( value_type & V, Function &&  M1)
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
{   mtx_write BM ( BD);
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
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
uint32_t pop_copy_front ( value_type & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    value_type & VT = st.front() ;
    const_cast <key_t &> ( V.first) = VT.first ;
    V.second = VT.second ;
    BM.wait_no_readers() ;
    st.pop_front();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_front_if
/// @brief erase the first element of the tree and return a copy
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_copy_front_if ( value_type & V, Function &&  M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.front() ) )return 2 ;
    value_type & VT = st.front() ;
    const_cast <key_t &> ( V.first) = VT.first ;
    V.second = VT.second ;
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
uint32_t pop_move_front ( value_type & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    value_type & VT = st.front() ;
    const_cast <key_t &> ( V.first) = std::move(VT.first) ;
    V.second = std::move(VT.second) ;
    BM.wait_no_readers() ;
    st.pop_front();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_front_if
/// @brief erase the first element of the tree and return a copy with rvalues
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_move_front_if ( value_type & V, Function &&  M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.front() ) ) return 2 ;
    value_type & VT = st.front() ;
    const_cast <key_t &> ( V.first) = std::move(VT.first) ;
    V.second = std::move(VT.second) ;
    BM.wait_no_readers() ;
    st.pop_front() ;
    return 0;
};
//***************************************************************************
//                  P O P _ B A C K
//
//  void     pop_back ( void )
//
//  template <class Function> uint32_t pop_back_if ( Function &&  M1  )
//
//  uint32_t pop_copy_back ( value_type & V)
//
//  template <class Function>
//  uint32_t pop_copy_back_if ( value_type & V, Function &&  M1)
//
//  uint32_t pop_move_back ( value_type & V)
//
//  template <class Function>
//  uint32_t pop_move_back_if ( value_type & V, Function &&  M1)
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
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_back_if ( Function &&  M1)
{   mtx_write BM ( BD);
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
uint32_t pop_copy_back ( value_type & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    value_type & VT = st.back() ;
    const_cast <key_t &> ( V.first) = VT.first ;
    V.second = VT.second ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_copy_back_if
/// @brief erase the last element of the tree and return a copy
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
///         2 - Function returns false
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_copy_back_if ( value_type & V, Function && M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.back() ) ) return 2 ;
    value_type & VT = st.back() ;
    const_cast <key_t &> ( V.first) = VT.first ;
    V.second = VT.second ;
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
uint32_t pop_move_back ( value_type & V)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    value_type & VT = st.back() ;
    const_cast <key_t &> ( V.first) = std::move(VT.first) ;
    V.second = std::move(VT.second) ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//---------------------------------------------------------------------------
//  function :pop_move_back_if
/// @brief erase the last element of the tree and return a copy with rvalues
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @param [out] V : reference to a variable where copy the element
/// @return code of the operation
///         0- Element erased
///         1 - Empty tree
/// @remarks This operation is O(1)
//---------------------------------------------------------------------------
template <class Function>
uint32_t pop_move_back_if ( value_type & V, Function &&   M1)
{   //-------------------------- begin -----------------------------
    mtx_write BM ( BD);
    if ( st.size() == 0) return 1 ;
    if ( not  M1 (st.back() ) ) return 2 ;
    value_type & VT = st.back() ;
    const_cast <key_t &> ( V.first) = std::move(VT.first) ;
    V.second = std::move(VT.second) ;
    BM.wait_no_readers() ;
    st.pop_back();
    return 0;
};
//***************************************************************************
//                   E R A S E
//
//  iterator erase    ( const_iterator iter )
//
//  template <class Function>
//  mypair erase_if ( const_iterator iter , Function && M1)
//
//  size_type erase ( const key_type& x )
//
//  template <class Function>
//  signed_type erase_if ( const key_type& x , Function &&  M1)
//
//  iterator erase ( const_iterator first, const_iterator last )
//
//  template <class Function>
//  iterator erase_if ( const_iterator first, const_iterator last, Function && M1)
//
//  void erase_pos( signed_type Pos)
//
//  template <class Function>
//  bool erase_pos_if( signed_type Pos, Function &&  M )
//
//  void erase_pos ( signed_type Prim, signed_type NElem)
//
//  template <class Function>
//  void erase_pos_if ( signed_type Prim, signed_type NElem , Function && M)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase the element pointed by iter
/// @param [in] iter : iterator to the element to erase
/// @return none
//---------------------------------------------------------------------------
iterator erase ( const_iterator iter )
{   //---------- begin -------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    return st.upgrade ( st.erase( iter ) );
};
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase the element pointed by iter if the function return true
/// @param [in] iter : iterator to the element to erase
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return none
//---------------------------------------------------------------------------
template <class Function>
mypair erase_if ( const_iterator iter , Function && M1)
{   //---------- begin -------------
    mtx_write BM ( BD);
    assert (iter != st.it_end() and iter != st.it_rend() );
    iterator Alfa = st.upgrade(iter +1) ;
    bool SW = M1 ( *iter);
    if (SW)
    {   BM.wait_no_readers() ;
        st.erase( iter );
    };
    return mypair(Alfa, SW ) ;
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief Erase all the elements with a key
/// @param [in] x : key of all the elements to erase
/// @return number of elements erased
//---------------------------------------------------------------------------
size_type erase ( const key_type& x )
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator I = st.find_norep(x) ;
    if ( I == end()) return 0 ;
    BM.wait_no_readers() ;
    st.erase( I);
    return 1 ;
} ;
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief Erase all the elements with a key
/// @param [in] x : key of all the elements to erase
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return number of elements erased
//---------------------------------------------------------------------------
template <class Function>
signed_type erase_if ( const key_type& x , Function &&  M1)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator I = st.find_norep(x) ;
    if ( I == end() or not M1(*I)) return 0 ;
    BM.wait_no_readers() ;
    st.erase( I);
    return 1 ;
} ;
//---------------------------------------------------------------------------
//  function :erase
/// @brief erase a range of elements in the range first, last
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @return none
//---------------------------------------------------------------------------
iterator erase ( const_iterator first, const_iterator last )
{   //---------- begin ---------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.erase ( first , last);
    return st.upgrade(last) ;
};
//---------------------------------------------------------------------------
//  function :erase_if
/// @brief erase a range of elements in the range first, last
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] M1 : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return none
//---------------------------------------------------------------------------
template <class Function>
iterator erase_if ( const_iterator first, const_iterator last, Function && M1)
{   //---------- begin ---------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.erase_if ( first , last, M1);
    return st.upgrade(last) ;
};
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
    // The function ptr_pos check the limits
    node_t *P1 = st.upgrade (st.ptr_pos ( Pos) );
    BM.wait_no_readers() ;
    st.disconnect ( P1 ) ;
    st.destroy ( P1 ) ;
    st.deallocate ( P1, 1 ) ;
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
template <class Function>
bool erase_pos_if( signed_type Pos, Function &&  M )
{   //---------------------------- begin ------------------------------------
    mtx_write BM ( BD);
    // The function ptr_pos check the limits
    node_t *P1 = st.upgrade (st.ptr_pos ( Pos));
    bool SW =  M ( P1->data);
    if ( SW )
    {   BM.wait_no_readers() ;
        st.disconnect ( P1 ) ;
        st.destroy ( P1 ) ;
        st.deallocate ( P1, 1 ) ;
    };
    return SW ;
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase  NElem elements beginning in the position Prim
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : number of elements to delete
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
/// @brief erase  NElem elements beginning in the position Prim
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : number of elements to erase
/// @param [in] M : function with the format ( bool M (value_t &))
///                 if return true the element is deleted , if false not
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
void erase_pos_if ( signed_type Prim, signed_type NElem , Function && M)
{   //---------------------- begin ------------------
    mtx_write BM ( BD);
    BM.wait_no_readers() ;
    st.erase_pos_if( Prim, NElem,M);
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
//  void modify ( iterator It , const data_t & D)
//
//  void modify ( iterator It , data_t && D)
//
//  template <class Function>
//  void modify ( iterator It ,Function &&  M )
//
//  bool modify ( const key_type& x ,const data_t & val)
//
//  bool modify ( const key_type& x , data_t && val)
//
//  template <class Function>
//  bool modify ( const key_type& x ,Function &&  M)
//
//  void modify_pos ( signed_type Pos ,const data_t & val)
//
//  void modify_pos ( signed_type Pos , data_t && val)
//
//  template <class Function>
//  void modify_pos ( signed_type Pos ,Function &&  M)
//
//  mypair insert_or_modify ( const key_type& x ,const data_t &D )
//
//  mypair insert_or_modify ( const key_type& x , data_t &&D )
//
//  template <class Function>
//  mypair insert_or_modify (const key_type& x,const data_t &D,Function && M)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : modify
/// @brief  modify the element pointed by the iterator It
/// @param [in] It : iterator which point to the element
/// @param [in] D : new value of the field second
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify ( iterator It , const data_t & D)
{   //------------------------- begin---------------------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    It->second = D;
};
//---------------------------------------------------------------------------
//  function : modify
/// @brief  modify the element pointed by the iterator It
/// @param [in] It : iterator which point to the element
/// @param [in] D : new value of the field second
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify ( iterator It , data_t && D)
{   //------------------------- begin---------------------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    It->second = std::move(D);
};

//---------------------------------------------------------------------------
//  function : modify
/// @brief  modify the element pointed by the iterator It
/// @param [in] It : iterator which point to the element
/// @param [in] M : function for to modify the element ( void M ( value_type &) )
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
void modify ( iterator It ,Function &&  M )
{   //------------------------- begin ----------------------------
    mtx_write BM ( BD);
    assert ( It != end() and It != it_rend() );
    BM.wait_no_readers() ;
    M ( *It);
};
//---------------------------------------------------------------------------
//  function : modify
/// @brief modify the element with the key x
/// @param [in] x : key to search in the map
/// @param [in] val: new value to modify the field second of the element with
///                  the key x
/// @return true : modified false : not
/// @remarks
//---------------------------------------------------------------------------
bool modify ( const key_type& x ,const data_t & val)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator P = st.find_norep(x);
    if ( P == end()) return false ;
    BM.wait_no_readers () ;
    P->second = val;
    return true ;
};
//---------------------------------------------------------------------------
//  function : modify
/// @brief modify the element with the key x
/// @param [in] x : key to search in the map
/// @param [in] val: new value to modify the field second of the element with
///                  the key x
/// @return true : modified false : not
/// @remarks
//---------------------------------------------------------------------------
bool modify ( const key_type& x , data_t && val)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    iterator P = st.find_norep(x);
    if ( P == end()) return false ;
    BM.wait_no_readers () ;
    P->second = std::move(val);
    return true ;
};
//---------------------------------------------------------------------------
//  function : modify
/// @brief modify the element with the key x with the function M
/// @param [in] x : key to search in the map
/// @param [in] M : function for to modify the field second of the element with
///                  the key x with the format (void M (value_type &))
/// @return true : modified false : not
//---------------------------------------------------------------------------
template <class Function>
bool modify ( const key_type& x ,Function &&  M)
{   //------------------- begin --------------------------
    mtx_write BM ( BD);
    iterator P = st.find_norep(x);
    if ( P == end()) return  false;
    BM.wait_no_readers () ;
    M ( *P);
    return true;
};
//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief modify the element of the position pos with the value val
/// @param [in] Pos : position to modify
/// @param [in] val : value to substitute the field second in the element of
///                   the position Pos
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify_pos ( signed_type Pos ,const data_t & val)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    value_type & R = st.pos ( Pos);
    BM.wait_no_readers () ;
    R.second = val;
};
//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief modify the element of the position pos with the value val
/// @param [in] Pos : position to modify
/// @param [in] val : value to substitute the field second in the element of
///                   the position Pos
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void modify_pos ( signed_type Pos , data_t && val)
{   //------------ begin ---------------
    mtx_write BM ( BD);
    value_type & R = st.pos ( Pos);
    BM.wait_no_readers () ;
    R.second = std::move(val);
};
//---------------------------------------------------------------------------
//  function : modify_pos
/// @brief modify the element of the position pos with the function M
/// @param [in] Pos : position to modify
/// @param [in] M : function to modify with the format ( void M ( value_type &) )
/// @return void
/// @remarks
//---------------------------------------------------------------------------
template <class Function>
void modify_pos ( signed_type Pos ,Function &&  M)
{   //------------------- begin --------------------------
    mtx_write BM ( BD);
    value_type & R = st.pos ( Pos);
    BM.wait_no_readers () ;
    M ( R);
};
//---------------------------------------------------------------------------
//  function : insert_or_modify
/// @brief If the element with key x don't exist, it is inserted the pair (x,D)
///        if the element exist, the second part is asigned to the value D
/// @param [in] x : key value
/// @param [in] D : data value
/// @return  pair <iterator,bool> with an iterator to the element inserted or
///          modified, and the value true means inserted and the false modified
/// @remarks
//---------------------------------------------------------------------------
mypair insert_or_modify ( const key_type& x ,const data_t &D )
{   //---------------------------- begin -----------------------------------
    mtx_write BM ( BD);
    connector C ;
    mypair M ;
    node_t *PAux = st.connector_norep( x , C);
    bool SW = ( PAux == NULL);
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , x,D  );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
    }
    else
    {   BM.wait_no_readers() ;
        PAux->data.second = D ;
    }
    return mypair ( st.get_it (PAux), SW);
};
//---------------------------------------------------------------------------
//  function : insert_or_modify
/// @brief If the element with key x don't exist, it is inserted the pair (x,D)
///        if the element exist, the second part is asigned to the value D
/// @param [in] x : key value
/// @param [in] D : data value
/// @return  pair <iterator,bool> with an iterator to the element inserted or
///          modified, and the value true means inserted and the false modified
/// @remarks
//---------------------------------------------------------------------------
mypair insert_or_modify ( const key_type& x , data_t &&D )
{   //---------------------------- begin -----------------------------------
    mtx_write BM ( BD);
    connector C ;
    mypair M ;
    node_t *PAux = st.connector_norep( x , C);
    bool SW = ( PAux == NULL);
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , x,std::move(D)  );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
    }
    else
    {   BM.wait_no_readers() ;
        PAux->data.second = std::move(D) ;
    }
    return mypair ( st.get_it (PAux), SW);
};

//---------------------------------------------------------------------------
//  function : insert_or_modify
/// @brief If the element with key x don't exist, it is inserted the pair (x,D)
///        if the element exist, the function M is executed over the element
/// @param [in] x : key value
/// @param [in] D : data value
/// @param [in] M : function to modify the existing element with the format
///                 ( void M ( value_type & ) )
/// @return  pair <iterator,bool> with an iterator to the element inserted or
///          modified, and the value true means inserted and the false modified
//---------------------------------------------------------------------------
template <class Function>
mypair insert_or_modify ( const key_type& x ,const data_t &D ,Function &&  M)
{   //---------------------------- begin -----------------------------------
    mtx_write BM ( BD);
    connector C ;
    node_t *PAux = st.connector_norep( x , C);
    bool SW = ( PAux == NULL);
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , x,D  );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
    }
    else
    {   BM.wait_no_readers() ;
        M ( PAux->data);
    }
    return mypair ( st.get_it (PAux), SW);
};
//---------------------------------------------------------------------------
//  function : insert_or_modify
/// @brief If the element with key x don't exist, it is inserted the pair (x,D)
///        if the element exist, the function M is executed over the element
/// @param [in] x : key value
/// @param [in] D : data value
/// @param [in] M : function to modify the existing element with the format
///                 ( void M ( value_type & ) )
/// @return  pair <iterator,bool> with an iterator to the element inserted or
///          modified, and the value true means inserted and the false modified
//---------------------------------------------------------------------------
template <class Function>
mypair insert_or_modify ( const key_type& x , data_t &&D ,
                          Function &&   M)
{   //---------------------------- begin -----------------------------------
    mtx_write BM ( BD);
    connector C ;
    node_t *PAux = st.connector_norep( x , C);
    bool SW = ( PAux == NULL);
    if ( SW )
    {   PAux = st.allocate (1) ;
        st.construct ( PAux , x,std::move (D ) );
        BM.wait_no_readers() ;
        st.connect( PAux, C);
    }
    else
    {   BM.wait_no_readers() ;
        M ( PAux->data);
    }
    return mypair ( st.get_it (PAux), SW);
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
ValueCompare value_comp ( ) const
{   mtx_read BR ( BD);
    return comp_pair<key_t,data_t,comp_key_t> ();
};
//---------------------------------------------------------------------------
//  function : get_allocator
/// @brief return the object allocator of the set
/// @param [in] none
/// @return object allocator
//---------------------------------------------------------------------------
allocator_type &get_allocator() const
{   mtx_read BR ( BD);
    return st.get_allocator();
};
//
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
//                     I T E R A T O R S                                  ##
//                                                                        ##
//  I S _ M I N E , B E G I N , E N D , R B E G I N , R E N D             ##
//                                                                        ##
//  bool            is_mine ( iterator it) const;                         ##
//  iterator        begin   ( void ) ;                                    ##
//  const_iterator  begin   ( void ) const ;                              ##
//  iterator        end     ( void ) ;                                    ##
//  const_iterator  end     ( void ) const ;                              ##
//  iterator        rbegin  ( void ) ;                                    ##
//  const_iterator  rbegin  ( void )const ;                               ##
//  iterator        rend    ( void ) ;                                    ##
//  const_iterator  rend    ( void ) const;                               ##
//                                                                        ##
//##########################################################################

//----------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_map
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_map
/// @remarks This operation is O ( const )
//------------------------------------------------------------------------
bool is_mine ( const_iterator it) const
{   mtx_read BR ( BD);
    return st.is_mine(it) ;
};
//----------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this cntree_map
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this cntree_map
/// @remarks This operation is O ( const )
//------------------------------------------------------------------------
bool is_mine ( const_reverse_iterator it) const
{   mtx_read BR ( BD);
    return st.is_mine(it) ;
};
//
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
//
//---------------------------------------------------------------------------
//  function :it_begin
/// @return iterator to the first element
//---------------------------------------------------------------------------
iterator it_begin   ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.it_begin();
};
//---------------------------------------------------------------------------
//  function : begin
/// @return iterator to the first element
//---------------------------------------------------------------------------
iterator begin      ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.begin() ;
};
//---------------------------------------------------------------------------
//  function : it_end
/// @return iterator to the next element after the last
//---------------------------------------------------------------------------
iterator it_end     ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.it_end( );
};
//---------------------------------------------------------------------------
//  function : end
/// @return iterator to the next element after the last
//---------------------------------------------------------------------------
iterator end        ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.end();
};
//---------------------------------------------------------------------------
//  function : it_rbegin
/// @return iterator to the last element
//---------------------------------------------------------------------------
iterator it_rbegin  ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.it_rbegin();
};
//---------------------------------------------------------------------------
//  function : it_rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
iterator it_rend    ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.it_rend ();
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
reverse_iterator rit_begin ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rit_begin();
};
//---------------------------------------------------------------------------
//  function : rit_end
/// @return reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
reverse_iterator rit_end   ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rit_end();
};
//---------------------------------------------------------------------------
//  function : rit_rbegin
/// @return reverse_iterator to the last element
//---------------------------------------------------------------------------
reverse_iterator rit_rbegin( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rit_rbegin();
};
//---------------------------------------------------------------------------
//  function : rbegin
/// @return reverse_iterator to the last element
//---------------------------------------------------------------------------
reverse_iterator rbegin    ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rbegin();
};
//---------------------------------------------------------------------------
//  function : rit_rend
/// @return reverse_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
reverse_iterator rit_rend  ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rit_rend( );
};
//---------------------------------------------------------------------------
//  function : rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
reverse_iterator rend      ( void) NOEXCEPT
{   mtx_read BR ( BD);
    return st.rend();
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
//***************************************************************************
//
//                P R I V A T E     F U N C T I O N S
//
//***************************************************************************

#if __DEBUG_CNTREE != 0

friend std::ostream & operator<<(std::ostream &salida , const value_t & A)
{   salida<<" ["<<A.first<<" , "<<A.second<<"] "
    return salida
}

//------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the set
/// @param [in] salida : ostream where write the information
/// @param [in] A : set to print
/// @return ostream after the printing
//------------------------------------------------------------------------
friend std::ostream & operator<<(std::ostream &salida ,
                                 const cntree_map<key_t, data_t, cnc,comp_key_t,alloc_t>& A)
{   //--------------------------- begin ------------------------------
    mtx_read BR ( A.BD);
    salida<< A.st;
    return salida ;
};
#endif
//***************************************************************************
};//              E N D     M A P     C L A S S
//***************************************************************************
//

//***************************************************************************
};//              E N D    C O U N T E R T R E E     N A M E S P A C E
//***************************************************************************
#endif
