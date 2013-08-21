//----------------------------------------------------------------------------
/// @file sorted_tree.hpp
/// @brief
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_SORTED_TREE_HPP
#define __COUNTERTREE_FOREST_SORTED_TREE_HPP

#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/forest/tree.hpp>
#include <boost/countertree/forest/iterator.hpp>
#include <boost/countertree/forest/reverse_iterator.hpp>
//#include <boost/countertree/forest/barrier.hpp>
#include <boost/countertree/filter.hpp>

namespace c_forest = countertree::forest ;
namespace c_common = countertree::common ;

namespace countertree
{
namespace forest
{

using c_common::signed_type;
using c_common::unsigned_type;
//##########################################################################
//                                                                        ##
//                          C L A S S                                     ##
//                                                                        ##
//                      S O R T E D _ T R E E                             ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class  sorted_tree
/// @brief  This class is a countertree sorted, with all the
///         functions needed for manage the ordered information. \n
///         It has access by position and random access iterators
///         Due to this all the operations ( insert, delete, access)
///         a O( logN). \n
/// @param  value_t : value to store
/// @param  key_t : value used to compare
/// @param  filter_t Object used to obtain a key_t from a value_t
/// @param  comp_key_t : object used to compare two keys
/// @param  alloc_t : object used to allocate the nodes in the memory

/// @remarks
//----------------------------------------------------------------
template < typename value_t,
           typename key_t      = value_t,
           typename filter_t   = filter_set<key_t,value_t>,
           typename comp_key_t = std::less<key_t>,
           typename alloc_t    = std::allocator<void>
        >
class sorted_tree
{
public:
//***************************************************************************
//                     D E F I N I T I O N S
//***************************************************************************
typedef c_common::signed_type                            size_type ;
typedef c_common::signed_type                            difference_type ;
typedef       value_t                                    value_type;
typedef       value_type *                               pointer;
typedef const value_type *                               const_pointer;
typedef       value_type &                               reference;
typedef const value_type &                               const_reference;
typedef       alloc_t                                    allocator_type;
typedef c_forest::node<value_t>                          node_t ;
typedef c_forest::base_node                              base_node_t ;
typedef typename alloc_t::template rebind<node_t>::other node_alloc_t;
typedef c_forest::tree <value_t,node_alloc_t>            tree;
typedef typename tree::iterator                          iterator;
typedef typename tree::const_iterator                    const_iterator;
typedef typename tree::reverse_iterator                  reverse_iterator;
typedef typename tree::const_reverse_iterator            const_reverse_iterator;

protected:
//***************************************************************************
//              P R I V A T E    V A R I A B L E S
//***************************************************************************
alloc_t       value_alloc ;
tree          T           ;
public:
filter_t      fltr        ;
comp_key_t    cmpr        ;


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
//  C O N S T R U C T O R  , D E S T R U C T O R
//
//  explicit sorted_tree( const comp_key_t & comp = comp_key_t (),
//                        const alloc_tr& alloc = alloc_t ()       )NOEXCEPT
//
//  sorted_tree ( const sorted_tree &  VT )
//  sorted_tree (       sorted_tree && VT ) NOEXCEPT
//
//  template < typename alloc_t2 >
//  sorted_tree (const sorted_tree<value_t,key_t,filter_t,comp_key_t,alloc_t2> &VT)
//
//  virtual ~sorted_tree (void)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : sorted_tree
/// @brief This function is the construct of the class
/// @param [in] F1 : object filter_t
/// @param [in] C1 : object comp_key_t
/// @param [in] A : object alloc_t
/// @remarks
//---------------------------------------------------------------------------
explicit sorted_tree( const comp_key_t & comp = comp_key_t (),
                      const alloc_t& alloc = alloc_t ()       ) NOEXCEPT
                     :value_alloc(alloc),fltr(filter_t()),cmpr(comp){ };

//---------------------------------------------------------------------------
//  function : sorted_tree
/// @brief  Copy constructor
/// @param [in] VT : sorted_tree from where copy the data
//---------------------------------------------------------------------------
sorted_tree ( const sorted_tree & VT )
{   T.copy  ( VT.T );
};
//---------------------------------------------------------------------------
//  function : sorted_tree
/// @brief  Copy constructor
/// @param [in] VT : sorted_tree from where copy the data
//---------------------------------------------------------------------------
sorted_tree ( sorted_tree && VT) NOEXCEPT
: value_alloc(std::move (VT.value_alloc)),T(std::move(VT.T)) ,
  fltr( std::move (VT.fltr)) ,  cmpr(std::move (VT.cmpr))    { } ;

//---------------------------------------------------------------------------
//  function : sorted_tree
/// @brief copy constructor
/// @param [in] A : sorted_tree from where copy the data
/// @return Reference to the sorted_tree after the copy
//---------------------------------------------------------------------------
template < typename alloc_t2 >
sorted_tree (const sorted_tree <value_t,key_t,filter_t,comp_key_t,alloc_t2> &VT)
{    T.copy  ( VT.get_tree() );
};
//---------------------------------------------------------------------------
//  function : ~sorted_tree
/// @brief destructor of the class
/// @param [in] none
/// @remarks This function is virtual
//---------------------------------------------------------------------------
virtual ~sorted_tree (void) NOEXCEPT
{   T.clear();
};
//***************************************************************************
//  O P E R A T O R = ,  C L E A R , S W A P
//
//  sorted_tree & operator= (const sorted_tree &VT)
//
//  template < typename alloc_t2 >
//  sorted_tree & operator=
//  (const sorted_tree <value_t,key_t,filter_t,comp_key_t,alloc_t2> &VT)
//
//  sorted_tree & operator= (sorted_tree &&S)
//
//  void clear(void)
//
//  void swap(sorted_tree  & A ) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] A : sorted_tree from where copy the data
/// @return Reference to the sorted_tree after the copy
//---------------------------------------------------------------------------
sorted_tree & operator= (const sorted_tree &VT)
{   T.copy  ( VT.T );
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] A : sorted_tree from where copy the data
/// @return Reference to the sorted_tree after the copy
//---------------------------------------------------------------------------
template < typename alloc_t2 >
sorted_tree & operator=
(const sorted_tree <value_t,key_t,filter_t,comp_key_t,alloc_t2> &VT)
{   //------------- begin ----------
    T.copy  ( VT.get_tree() );
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator =
/// @brief Asignation operator
/// @param [in] A : sorted_tree from where copy the data
/// @return Reference to the sorted_tree after the copy
//---------------------------------------------------------------------------
sorted_tree & operator= (sorted_tree &&S)
{   T = std::move (S.T );
    return *this ;
};
//---------------------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the sorted_tree
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void clear(void)
{   T.clear ( );
};
//---------------------------------------------------------------------------
//  function : swap
/// @brief swap the data between the two sorted_tree
/// @param [in] A : sorted_tree to swap
/// @return none
//---------------------------------------------------------------------------
void swap(sorted_tree  & A ) NOEXCEPT
{   std::swap (T, A.T);
    std::swap( value_alloc, A.value_alloc);
};

//
//***************************************************************************
//  S I Z E , M A X _ S I Z E , E M P T Y , I S _ M I N E
//
//  signed_type     size        ( void  ) const NOEXCEPT
//  signed_type     max_size    ( void  ) const NOEXCEPT
//  bool            empty       ( void  ) const NOEXCEPT
//  bool            is_mine     ( const_iterator P1) const
//  const tree &    get_tree    ( void  ) const
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements in the sorted_tree
/// @return number of elements in the sorted_tree
//---------------------------------------------------------------------------
signed_type size ( void) const NOEXCEPT
{   return T.size() ;
};
//---------------------------------------------------------------------------
//  function :max_size
/// @brief return the maximun size of the container
/// @return maximun size of the container
//---------------------------------------------------------------------------
signed_type max_size (void) const NOEXCEPT
{   return ( (std::numeric_limits<signed_type>::max)() );
};
//---------------------------------------------------------------------------
//  function : empty
/// @brief indicate if the map is empty
/// @return true if the map is empty, false in any other case
//---------------------------------------------------------------------------
bool empty ( void) const NOEXCEPT
{   return (T.size() == 0) ;
};

//---------------------------------------------------------------------------
//  function : get_tree
/// @brief return a const reference to the internal tree
/// @return const reference to the internal tree
/// @remarks
//---------------------------------------------------------------------------
const tree & get_tree ( void)const
{   return T ;
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
//
//***************************************************************************
//   F I N D _ N O D E _ R E P , F I N D _ N O D E _ N O R E P
//   L O W E R _ B O U N D , U P P E R _ B O U N D
//
//  const_iterator find_rep   ( const key_t & K) const
//  const_iterator find_norep ( const key_t & K) const
//
//        iterator        lower_bound ( const key_t & K)       NOEXCEPT
//  const_iterator        lower_bound ( const key_t & K) const NOEXCEPT
//
//        iterator        upper_bound ( const key_t & K)       NOEXCEPT
//  const_iterator        upper_bound ( const key_t & K) const NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : find_rep
/// @brief Return an const_iterator to the first element with this Key
///        if don't exist return end()
/// @param [in] Key : key to search
/// @return const_iterator to the element if exist, or end()
/// @remarks
//---------------------------------------------------------------------------
iterator find_rep ( const key_t & K)
{   //--------------------- begin --------------------------
    node_t * P1 = const_cast <node_t*> (T.get_root()) ;
    iterator C = end();

    // Si encontramos un valor igual, lo apuntamos , y seguimos buscando
    // por la izda
    while ( P1 != NULL)
    {   if ( cmpr ( fltr(P1->data) , K)) P1 = upgrade(P1->right) ;
        else
        {   if (not cmpr(K , fltr(P1->data))) C = iterator( P1, &T ) ;
            P1 = upgrade( P1->left) ;
        };
    };
    return C ;
};
//---------------------------------------------------------------------------
//  function : find_rep
/// @brief Return an const_iterator to the first element with this Key
///        if don't exist return end()
/// @param [in] Key : key to search
/// @return const_iterator to the element if exist, or end()
/// @remarks
//---------------------------------------------------------------------------
const_iterator find_rep ( const key_t & K) const
{   return (const_cast <sorted_tree *> (this))->find_rep(K);
};

//---------------------------------------------------------------------------
//  function : find_norep
/// @brief Return an const_iterator to the element with this Key. If don't exist
///        return end() \n
///        This function supouse there is only one element with the key
/// @param [in] Key : key to search
/// @return iterator to the element if exist, or end()
/// @remarks
//---------------------------------------------------------------------------
iterator find_norep ( const key_t & K)
{   //---------------- begin-----------------
    node_t * P1 = const_cast <node_t*>(T.get_root()) ;
    bool SW = true ;

    // Si encontramos un valor igual, lo apuntamos , y seguimos buscando
    // por la izda
    while ( SW and P1 != NULL)
    {   if ( cmpr ( fltr(P1->data) , K)) P1 = upgrade(P1->right) ;
        else
        {   if (cmpr(K , fltr(P1->data))) P1 = upgrade( P1->left) ;
            else                          SW = false ;
        };
    };
    return ( SW)?end() :iterator( P1, &T ) ;
};
//---------------------------------------------------------------------------
//  function : find_norep
/// @brief Return an const_iterator to the element with this Key. If don't exist
///        return end() \n
///        This function supouse there is only one element with the key
/// @param [in] Key : key to search
/// @return iterator to the element if exist, or end()
/// @remarks
//---------------------------------------------------------------------------
const_iterator find_norep ( const key_t & K) const
{   return (const_cast <sorted_tree *> (this))->find_norep(K);
}
//---------------------------------------------------------------------------
//  function : read_norep
/// @brief Return an copy of the object in the tree. If exist return true. If
///        don't exist  return false \n
///        This function supouse there is only one element with the key
/// @param [in] V : object where copy the element of the tree
/// @param [in] Key : key to search
/// @return bool true- copy in V false didn't find in the tree
/// @remarks
//---------------------------------------------------------------------------
bool read_norep ( value_t &V,const key_t & K ) const
{   //----------------------------- begin ------------------------------
    const_iterator It = find_norep( K);
    if ( It == cit_end()) return false ;
    V = *It ;
    return true ;
};
//---------------------------------------------------------------------------
//  function : read_rep
/// @brief Return an copy of the object in the tree. If exist return true. If
///        don't exist  return false \n
/// @param [in] V : object where copy the element of the tree
/// @param [in] Key : key to search
/// @param [in] shift : shift from the first element with the key K
/// @return bool true- copy in V false didn't find in the tree
/// @remarks
//---------------------------------------------------------------------------
bool read_rep ( value_t &V,const key_t & K , signed_type shift) const
{   //----------------------------- begin ------------------------------
    const_iterator It = find_rep( K);
    if ( It == end()) return false ;
    if ( shift != 0) It += shift ;
    if ( It == cit_end() or It == cit_rend()) return false ;
    V = *It ;
    return true ;
};
//---------------------------------------------------------------------------
//  function : lower_bound
/// @brief find a key in the tree. If there are repeated
///        elements, return an const_iterator to the first of them.
///        If the key don't exist return an iterator to the first element
///        greater than the key
/// @param [in] K : key to search
/// @return const_iterator to the element. If don't exist end()
/// @remarks
//---------------------------------------------------------------------------
iterator lower_bound ( const key_t & K) NOEXCEPT
{   //-------------------- begin ---------------------------
    node_t * P1 = const_cast <node_t*> ( T.get_root() );
    node_t *P2 = P1;
    if ( P1 == NULL ) return end() ;
    iterator C = end() ;
    bool SWR = false ;

    // Si encontramos un valor igual, lo apuntamos , y seguimos buscando
    // por la izda
    while ( P1 != NULL)
    {   P2 = P1 ;
        P1 = (node_t *)((SWR = cmpr(fltr(P1->data),K) )? P1->right :P1->left);
        if ( not SWR)
        {   if ( not cmpr(K , fltr(P2->data)))
                C = iterator(P2,&T);
        };
    };
    if ( C == end())
    {   if (SWR)
        {   P2 = upgrade(P2->next()) ;
            C = ( P2 == NULL)? end() :iterator ( P2, &T)  ;
        }
        else C = iterator( P2 , &T ) ;
    };
    return C ;
};
//---------------------------------------------------------------------------
//  function : lower_bound
/// @brief find a key in the tree. If there are repeated
///        elements, return an const_iterator to the first of them.
///        If the key don't exist return an iterator to the first element
///        greater than the key
/// @param [in] K : key to search
/// @return const_iterator to the element. If don't exist end()
/// @remarks
//---------------------------------------------------------------------------
const_iterator lower_bound ( const key_t & K)const NOEXCEPT
{
    return (const_cast <sorted_tree *> (this))->lower_bound(K);
};
//---------------------------------------------------------------------------
//  function :upper_bound
/// @brief return an const_iterator to the first element greater than K. If
///        don't exist return end()
/// @param [in] K : value to find
/// @return const_iterator to the first element greater than K
///         If don't exist return end()
/// @remarks
//---------------------------------------------------------------------------
iterator upper_bound ( const key_t & K)  NOEXCEPT
{   //----------------------- begin ------------------------
    iterator Alfa = end() ;
    node_t* P1  = const_cast <node_t*> ( T.get_root () );
    while ( P1 != NULL )
    {   if ( cmpr( K , fltr(P1->data)))
        {   Alfa = iterator ( P1, &T);
            P1 = upgrade(P1->left) ;
        }
        else P1 = upgrade(P1->right) ;
    };
    return Alfa ;
};
//---------------------------------------------------------------------------
//  function :upper_bound
/// @brief return an const_iterator to the first element greater than K. If
///        don't exist return end()
/// @param [in] K : value to find
/// @return const_iterator to the first element greater than K
///         If don't exist return end()
/// @remarks
//---------------------------------------------------------------------------
const_iterator upper_bound ( const key_t & K)const NOEXCEPT
{
    return (const_cast <sorted_tree *> (this))->upper_bound(K);
};
//---------------------------------------------------------------------------
//  function : iterator_pos
/// @brief Find a position in the tree
/// @param [in] Pos : Position to find
/// @return Iterator to the position. If don't exists return end()
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
iterator iterator_pos ( signed_type Pos1) NOEXCEPT
{   return T.iterator_pos ( Pos1);
};
//---------------------------------------------------------------------------
//  function : const_iterator_pos
/// @brief Find a position in the tree
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists return end()
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
const_iterator const_iterator_pos ( signed_type Pos1) const NOEXCEPT
{   return T.const_iterator_pos (Pos1);
};
//
//***************************************************************************
//   E Q U A L _ R A N G E , C O U N T , F I N D _ P O S , K E Y _ C O M P
//
//  std::pair<iterator,iterator>
//  equal_range ( const key_t &K) NOEXCEPT
//
//  std::pair<const_iterator, const_iterator>
//  equal_range ( const key_t &K) const NOEXCEPT
//
//  size_type count ( const key_t &K) const NOEXCEPT
//
//  comp_key_t key_comp (void ) const NOEXCEPT
//
//  node_alloc_t & node_alloc ( void)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : equal_range
/// @brief return a pair of const_iterators, lower_bound and upper bound
///        of a key K
/// @param [in] K : key to find
/// @return pair of const_iterators, the first is le lower_bound and the second
//          is the upper bound
/// @remarks
//---------------------------------------------------------------------------
std::pair<iterator, iterator> equal_range ( const key_t &K) NOEXCEPT
{   //------------------------ begin -----------------------------
    return std::pair<iterator,iterator>(lower_bound(K),upper_bound(K));
};
//---------------------------------------------------------------------------
//  function : equal_range
/// @brief return a pair of const_iterators, lower_bound and upper bound
///        of a key K
/// @param [in] K : key to find
/// @return pair of const_iterators, the first is le lower_bound and the second
//          is the upper bound
/// @remarks
//---------------------------------------------------------------------------
std::pair<const_iterator,const_iterator> equal_range (const key_t &K) const NOEXCEPT
{   //--------------------------------- begin ------------------------------------
    return  std::pair<const_iterator,const_iterator>
            (lower_bound(K),upper_bound(K));
};
//---------------------------------------------------------------------------
//  function : count
/// @brief Count the number of elements with the key K
/// @param [in] K : key ti find
/// @return number of repetitions of the key K
/// @remarks
//---------------------------------------------------------------------------
signed_type count ( const key_t &K) const NOEXCEPT
{   //------------------------ begin ----------------------
    const_iterator C1 =lower_bound(K), C2 = upper_bound(K) ;
    if ( C1 == C2 ) return 0 ;
    return ( C2.pos() - C1.pos() );
};
//---------------------------------------------------------------------------
//  function : key_comp
/// @brief return the object used to compare two keys
/// @param [in] none
/// @return object comp_key
/// @remarks
//---------------------------------------------------------------------------
comp_key_t key_comp (void ) const NOEXCEPT
{   return cmpr;
};
//---------------------------------------------------------------------------
//  function : node_alloc
/// @brief This function provides a reference to the node_t allocator of the
///        internal tree object
/// @param [in]
/// @return reference to the node_t allocator
//---------------------------------------------------------------------------
node_alloc_t & node_alloc ( void)
{   return T.node_alloc ;
};
//----------------------------------------------------------------
//  function : get_allocator
/// @brief return the object allocator of the set
/// @param [in] none
/// @return object allocator
//----------------------------------------------------------------
allocator_type  get_allocator() const
{   return value_alloc ;
};
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
/// @brief Find a position in the sorted_tree
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
value_t & pos ( signed_type Pos1) NOEXCEPT
{   return  ( T [Pos1] );
};
//---------------------------------------------------------------------------
//  function : pos
/// @brief Find a position in the sorted_tree
/// @param [in] Pos : Position to find
/// @return const_iterator to the position. If don't exists throws
///         an exception
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
const value_t & pos ( signed_type Pos1) const NOEXCEPT
{   return  ( T [Pos1] );
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & front ( void) NOEXCEPT
{   return T.front() ;
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & front ( void) const NOEXCEPT
{   return T.front() ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & back (void ) NOEXCEPT
{   return T.back();
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element in the sorted_tree
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & back (void ) const NOEXCEPT
{   return T.back();
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
//  I N S E R T _ V A L U E , I N S E R T _ V A L U E _ U N I Q U E
//  K E Y _ C O M P
//
//  iterator    insert_value_rep    ( const value_t &Val) ;
//  iterator    insert_value_norep  (const value_t & Val) ;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : emplace_internal
/// @brief insert an element in a the position specified by the connector
/// @param [in] C : connector which indicate where must insert the node
/// @param [in] args : arguments to build the node to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_internal(connector C, Args && ... args)
{   return T.emplace_internal ( C , std::forward <Args> ( args)...);
};
//---------------------------------------------------------------------------
//  function :insert_value_rep
/// @brief Insert a value Val in the sorted tree
/// @param [in] Val : value to insert
/// @return const_iterator to the node_t inserted.
/// @remarks his function permit the insertion of repeated elements
//---------------------------------------------------------------------------
iterator  insert_value_rep  ( const value_t &Val)
{   return emplace_value_rep (Val);
};
//---------------------------------------------------------------------------
//  function : emplace_value_rep
/// @brief Insert a value Val in the sorted tree
/// @param [in] args: arguments for to build the node to insert
/// @return const_iterator to the node_t inserted.
/// @remarks his function permit the insertion of repeated elements
//---------------------------------------------------------------------------
template <class ... Args>
iterator  emplace_value_rep  (Args && ... args)
{   //---------------begin------------------
    connector C ;
    node_t *PAux = allocate (1) ;
    construct( PAux, std::forward <Args> ( args)... ) ;
    C = connector_rep ( fltr(PAux->data));
    connect(PAux,C);
    return get_it (PAux);
};
//---------------------------------------------------------------------------
//  function :insert_value_norep
/// @brief insert a value in the tree. If the value exist, it
///        is not inserted
/// @param [in] Val : value to insert
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done
/// @remarks
//---------------------------------------------------------------------------
std::pair<iterator,bool> insert_value_norep (const value_t & Val)
{   return emplace_value_norep ( Val);

}
//---------------------------------------------------------------------------
//  function : emplace_value_norep
/// @brief insert a value in the tree. If the value exist, it
///        is not inserted
/// @param [in] args: arguments for to build the node to insert
/// @return pair <iterator,bool> with the iterator to the element inserted or
///         or to the element that prevented the insertion, and a bool indication
///         if the insertion is done
/// @remarks
//---------------------------------------------------------------------------
template <class ... Args>
std::pair<iterator,bool>   emplace_value_norep (Args && ... args)
{   //-----------------begin------------------
    connector C ;
    node_t  *P2, *PAux;
    PAux = allocate (1) ;
    construct( PAux,  std::forward<Args> (args)... ) ;

    P2 = connector_norep ( fltr(PAux->data),C );
    bool SW = ( P2 == NULL);
    if ( SW)    T.connect (PAux, C);
    else
    {   destroy ( PAux);
        deallocate ( PAux , 1);
        PAux = P2 ;
    };
    return std::pair<iterator,bool> (iterator ( PAux , &T), SW ) ;
};
//---------------------------------------------------------------------------
//  function : insert_norep
/// @brief Assign a range of data, dropping all the elements of the
///        container
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void insert_norep ( InputIterator it_first, InputIterator it_last )
{   //---------------------- begin ---------------------------
    for (  ; it_first != it_last ; ++it_first)
    {   insert_value_norep( *it_first);
    };
};
//---------------------------------------------------------------------------
//  function : insert_norep_if
/// @brief Assign a range of data, dropping all the elements of the
///        container
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void insert_norep_if ( InputIterator it_first, InputIterator it_last,
                       std::function < bool ( const value_type & )>  M  )
{   //---------------------- begin ---------------------------
    for (  ; it_first != it_last ; ++it_first)
    {   if ( M ( *it_first))
        {   insert_value_norep( *it_first);
        };
    };
} ;
//---------------------------------------------------------------------------
//  function : insert_rep
/// @brief Assign a range of data, dropping all the elements of the
///        container
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void insert_rep ( InputIterator it_first, InputIterator it_last )
{   //---------------------- begin ---------------------------
    for (  ; it_first != it_last ; ++it_first)
    {   insert_value_rep( *it_first);
    };
} ;
//---------------------------------------------------------------------------
//  function : insert_rep_if
/// @brief Assign a range of data, dropping all the elements of the
///        container
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void insert_rep_if ( InputIterator it_first, InputIterator it_last,
                       std::function < bool ( const value_type & )>  M  )
{   //---------------------- begin ---------------------------
    for (  ; it_first != it_last ; ++it_first)
    {   if ( M ( *it_first))
        {   insert_value_rep( *it_first);
        };
    };
} ;
//
//***************************************************************************
//                C O N N E C T O R
//
//  connector connector_begin       ( void) NOEXCEPT
//  connector connector_end         ( void) NOEXCEPT
//  connector connector_pos         ( signed_type Pos ) NOEXCEPT
//  connector connector_pointer     ( base_node * Ptr ) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : connector_pos
/// @brief return the connector for to insert a new node in the position Pos
/// @param [in] Pos : Position to insert the value
/// @return connector for the insertion
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
connector connector_pos (signed_type Pos ) NOEXCEPT
{   return T.connector_pos ( Pos);
};
//---------------------------------------------------------------------------
//  function : connector_pointer
/// @brief return the connector for to insert the new node in the position
///        before the node pointed by Ptr
/// @param [in] Ptr : Pointer to the node_t, before which we want insert a new node_t
/// @return connector for to insert
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
connector connector_pointer (base_node * Ptr ) NOEXCEPT
{   return T.connector_pointer ( Ptr);
};
//---------------------------------------------------------------------------
//  function :connector_rep
/// @brief Find the pointer and the side in order to insert a node_t in
///        the sorted tree
/// @param [in] Val : value to insert
/// @param [out] P1 : Pointer to the node_t where insert
/// @param [out] left_side : Indicate which side of P1 in the insertion pointer
///                          true: left pointer , false: right pointer
/// @return
/// @remarks his function permit the insertion of repeated elements
//---------------------------------------------------------------------------
connector connector_rep ( const key_t &Val  )const NOEXCEPT
{   //----------------------------- begin -----------------------------------------
    bool SW = false ;
    node_t *P1 = const_cast <node_t*> (T.get_root());
    node_t * P2 = P1 ;

    while ( P2 != NULL)
    {   P1 = P2;
        P2 = (node_t*)( (SW=cmpr(Val,fltr(P2->data)))? P2->left:P2->right);
    };
    return connector ( P1, SW);
};
//---------------------------------------------------------------------------
//  function :connector_norep
/// @brief Find the pointer and the side in order to insert a node_t in
///        the sorted tree
/// @param [in] Val : value to insert
/// @param [out] P1 : Pointer to the node_t where insert
/// @param [out] left_side : Indicate which side of P1 in the insertion pointer
///                          true: left pointer , false: right pointer
/// @return if don't exist return NULL. If exist return the pointer to the node
///          with the key equal to Val
/// @remarks
//---------------------------------------------------------------------------
node_t * connector_norep ( const key_t & Val, connector &C )const NOEXCEPT
{   //--------------------------begin---------------------------------------
    bool SW =false;
    node_t * P1 = NULL;
    node_t * P2 = const_cast <node_t*> (T.get_root());
    while ( P2 != NULL)
    {   P1 = P2;
        //P2 = upgrade((SW=cmpr (Val, fltr(P2->data))) ?P2->left:P2->right );
        SW = cmpr ( Val , fltr(P2->data) ) ;
        P2 = ( SW ) ? upgrade(P2->left) :upgrade( P2->right );
    };
    C = connector( P1,SW) ;
    //if ( not SW) return NULL ;

    // Para saber si existe. Si SW es true buscamos en alterior a P1. Si
    // no es es , quiere decir que no existe
    // Si SW es false, si no es P1 , no existe
    node_t * P3 = P1 ;
    if ( SW)
    {   // Subir por la dcha todo lo que puedas y luego un salto hacia
        // arriba a la izda
        // Si no es posible saltar a la izda devuelve NULL, porque no
        // tiene nada posterior
        node_t *PAux = upgrade ( P3->up);
        while ( PAux != NULL and PAux->left == P3 )
        {   P3 = PAux ;
            PAux = upgrade(PAux->up) ;
        };
        P3 =( PAux != NULL and PAux->right != P3 ) ?NULL :PAux ;
    };

    return  ( P3 != NULL and not cmpr(fltr(P3->data),Val)
                    and not cmpr(Val,fltr(P3->data))  ) ? P3 : NULL;
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
// P O P _ F R O N T , P O P _ B A C K , E R A S E , E R A S E _ P O S
//
//  void pop_front ( void )
//  void pop_back ( void)
//
//  void erase ( const_iterator iter)
//  signed_type erase ( const_iterator first_it, const_iterator last_it)
//
//  signed_type erase_if ( const_iterator first_it, const_iterator last_it,
//                         std::function < bool ( const value_type & )>  M)
//
//  void erase_pos( signed_type Pos)
//  void erase_pos ( signed_type Prim, signed_type NElem )
//
//  void erase_pos_if ( signed_type Prim, signed_type NElem,
//                      std::function < bool(const value_type &)> M)
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
{   T.pop_front() ;
};
//---------------------------------------------------------------------------
//  function :pop_back
/// @brief erase the last element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
void pop_back ( void)
{   T.pop_back();
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase the element pointed by the const_iterator P1
/// @param [in] P1 : const_iterator to the element to erase
/// @return Iterator following the last removed element.
/// @remarks This operation is O ( constant)
//---------------------------------------------------------------------------
const_iterator erase ( const_iterator iter)
{   return T.erase ( iter);
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : const_iterator to the first element
/// @param [in] last_it : const_iterator to the final element of the range
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
signed_type erase ( const_iterator first_it, const_iterator last_it)
{   return T.erase ( first_it, last_it);
};
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : const_iterator to the first element
/// @param [in] last_it : const_iterator to the final element of the range
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
signed_type erase_if ( const_iterator first_it, const_iterator last_it,
                      std::function < bool ( const value_type & )>  M)
{   return T.erase_if ( first_it, last_it,M);
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @return void
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
void erase_pos( signed_type Pos)
{   T.erase_pos ( Pos);
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the elements between the position Prim and the position Ult.
///        The position Ult is deleted
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : number of elements to delete
/// @return void
/// @remarks
//---------------------------------------------------------------------------
void erase_pos ( signed_type Prim, signed_type NElem)
{   T.erase_pos( Prim, NElem);
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the lements between the position Prim and the position Ult.
///        The position Ult is deleted
/// @param [in] Prim : position to the first element to erase
/// @param [in] NElem : Number of elements to delete
/// @return void
/// @remarks
//---------------------------------------------------------------------------
signed_type erase_pos_if ( signed_type Prim, signed_type NElem,
                   std::function < bool(const value_type &)> M)
{   return T.erase_pos_if( Prim,NElem,M);
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
//***************************************************************************
//  O P E R A T I O N S   W I T H   N O D E _ A L L O C A T O R
//
//  node_t * allocate   (size_type cnt, const_pointer = NULL)
//  void     deallocate (node_t * p, size_type n = 1 )
//
//  template< typename U, typename... Args >
//  void construct( U * p, Args&&... args ) NOEXCEPT
//
//  void destroy(pointer p) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate a block of memory
/// @param [in] cnt : number of objects to allocate
/// @param [in]  pointer unused
/// @return pointer to the object allocated
/// @remarks
//---------------------------------------------------------------------------
node_t * allocate (size_type cnt, const_pointer = NULL)
{   return T.allocate ( cnt);
};
//---------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate a block of memory
/// @param [in] p : pointer to deallocate
/// @param [in] n : number of objects to deallocate
/// @exception  : bad_alloc
/// @return
//---------------------------------------------------------------------------
void deallocate (node_t * p, size_type n = 1 )
{   T.deallocate ( p , n);;
};

//---------------------------------------------------------------------------
//  function : construct
/// @brief Construct a new object in the memory pointed by p
/// @param [in] p : pointer to the memory for to construct the object
/// @param [in] args : list of parameters used in the copy constructor
/// @return
//---------------------------------------------------------------------------
template< typename  P , typename... Args >
void construct( P * p, Args&&... args ) NOEXCEPT
{   T.construct (p, std::forward <Args>(args)...);
};
//---------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the object without freeing the memory
/// @param [in] p : pointer p to the object to destroy
/// @return
//---------------------------------------------------------------------------
void destroy( node_t * p) NOEXCEPT
{   T.destroy ( p);
};

//
//***************************************************************************
//     F I N D _ P T R _ I N S E R T _ R E P
//     F I N D _ P T R _ I N S E R T _ N O R E P
//
//  void find_ptr_insert_rep ( const value_t &Val, node_t* & P1,
//                             bool & left_side               )const NOEXCEPT
//
//  bool find_ptr_insert_norep ( const value_t & Val,node_t* & P1,
//                               bool & left_side               )const NOEXCEPT
//
//***************************************************************************
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : ptr_pos
/// @brief Find a position in the tree
/// @param [in] Pos : Position to find
/// @return pointer to the position.
/// @remarks This operation is O ( log N). This function is called by others
///          functions with the position controlled
//---------------------------------------------------------------------------
base_node *  ptr_pos ( signed_type Pos) NOEXCEPT
{   return T.ptr_pos( Pos);
};
//---------------------------------------------------------------------------
//  function : ptr_pos
/// @brief Find a position in the tree
/// @param [in] Pos : Position to find
/// @return pointer to the position.
/// @remarks This operation is O ( log N). This function is called by others
///          functions with the position controlled
//---------------------------------------------------------------------------
const base_node * ptr_pos ( signed_type Pos) const NOEXCEPT
{   return T.ptr_pos(Pos);
};
//---------------------------------------------------------------------------
//  function :disconnect
/// @brief disconnect the node_t from the tree, and leave it balanced
///        and with the nodes actualized
/// @param [in] PAux : pointer to the node_t to delete
/// @return none
//  @remarks The counters are decremented by this function
//---------------------------------------------------------------------------
void disconnect ( base_node  * PAux ) NOEXCEPT
{   T.disconnect ( PAux);
};
//---------------------------------------------------------------------------
//  function : connect
/// @brief Insert a node_t in the tree and make a rebalanced if necessary
/// @param [in] PAux : pointer to the node_t for to be inserted
/// @param [in] P1 : pointer to the node_t where insert PAux
/// @param [in] Left : indicates which node_t of P1 link to PAux
/// @return none
/// @remarks If the tree is empty P1 and Left are not checked\n
///          This function works well when the tree is empty\n
///          All the counters of the nodes from the insertion point to
///          the root must be previously incremented
//---------------------------------------------------------------------------
void connect (base_node * PAux, connector C ) NOEXCEPT
{   T.connect ( PAux, C);
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
//  I S _ M I N E , I T E R A T O R _ P O S , G E T _ I T , U P G R A D E
//
//  bool is_mine ( const_iterator P1) NOEXCEPT
//  bool is_mine ( const_reverse_iterator P1) const NOEXCEPT
//
//  iterator  	    iterator_pos        ( signed_type Pos1) NOEXCEPT
//  const_iterator  const_iterator_pos  ( signed_type Pos1) const NOEXCEPT
//
//  iterator                get_it   ( node_t * P1)
//  const_iterator          get_cit  ( const node_t * P1)
//  reverse_iterator        get_rit  ( node_t * P1)
//  const_reverse_iterator  get_crit ( const node_t * P1)
//
//  iterator upgrade ( const_iterator & CT)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this sorted_tree
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this sorted_tree
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_iterator P1) const
{   return ( T.is_mine( P1));
};
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this sorted_tree
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this sorted_tree
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_reverse_iterator P1) const
{   return ( T.is_mine( P1));
};

//---------------------------------------------------------------------------
//  function : get_it
/// @brief create an iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
iterator get_it  ( node_t * P1) { return T.get_it ( P1);};
//---------------------------------------------------------------------------
//  function : get_cit
/// @brief create an const_iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
const_iterator  get_cit ( const node_t * P1){ return T.get_cit(P1);};
//---------------------------------------------------------------------------
//  function : get_rit
/// @brief create an reverse_iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
reverse_iterator  get_rit( node_t * P1){ return T.get_rit(P1);};
//---------------------------------------------------------------------------
//  function : get_crit
/// @brief create an const_ireverse_terator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
const_reverse_iterator  get_crit ( const node_t * P1){ return T.get_crit( P1);};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a const_iterator to an iterator
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
iterator upgrade ( const_iterator  CT)
{   return T.upgrade ( CT);
}
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
iterator it_begin   ( void) NOEXCEPT    {   return T.it_begin();    };
iterator begin      ( void) NOEXCEPT    {   return T.begin() ;      };
iterator it_end     ( void) NOEXCEPT    {   return T.it_end( );     };
iterator end        ( void) NOEXCEPT    {   return T.end();         };
iterator it_rbegin  ( void) NOEXCEPT    {   return T.it_rbegin();   };
iterator it_rend    ( void) NOEXCEPT    {   return T.it_rend ();    };
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
const_iterator cit_begin  ( void) const NOEXCEPT { return T.cit_begin();  };
const_iterator begin      ( void) const NOEXCEPT { return T.begin();      };
const_iterator cbegin     ( void) const NOEXCEPT { return T.cbegin();     };
const_iterator cit_end    ( void) const NOEXCEPT { return T.cit_end( );   };
const_iterator end        ( void) const NOEXCEPT { return T.end();        };
const_iterator cend       ( void) const NOEXCEPT { return T.cend();       };
const_iterator cit_rbegin ( void) const NOEXCEPT { return T.cit_rbegin(); };
const_iterator cit_rend   ( void) const NOEXCEPT { return T.cit_rend( );  };
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
reverse_iterator rit_begin ( void) NOEXCEPT { return T.rit_begin();     };
reverse_iterator rit_end   ( void) NOEXCEPT { return T.rit_end();       };
reverse_iterator rit_rbegin( void) NOEXCEPT { return T.rit_rbegin();    };
reverse_iterator rbegin    ( void) NOEXCEPT { return T.rbegin();        };
reverse_iterator rit_rend  ( void) NOEXCEPT { return T.rit_rend( );     };
reverse_iterator rend      ( void) NOEXCEPT { return T.rend();          };
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
const_reverse_iterator crit_begin (void) const NOEXCEPT{return T.crit_begin(); };
const_reverse_iterator crit_end   (void) const NOEXCEPT{return T.crit_end();   };
const_reverse_iterator crit_rbegin(void) const NOEXCEPT{return T.crit_rbegin();};
const_reverse_iterator rbegin     (void) const NOEXCEPT{return T.rbegin();     };
const_reverse_iterator crbegin    (void) const NOEXCEPT{return T.crbegin();    };
const_reverse_iterator crit_rend  (void) const NOEXCEPT{return T.crit_rend();  };
const_reverse_iterator rend       (void) const NOEXCEPT{return T.rend() ;      };
const_reverse_iterator crend      (void) const NOEXCEPT{return T.crend();      };
//
//***************************************************************************
//  D E B U G  F U N C T I O N S    ( C H E C K )
//
//  bool check ( void) const
//
//***************************************************************************
//
#if __DEBUG_CNTREE  != 0
//---------------------------------------------------------------------------
//  function : check
/// @brief check if the sorted_tree is OK
/// @return true : OK    false : Error in the sorted_tree
//---------------------------------------------------------------------------
bool check ( void) const
{   //----------------------- begin-----------------------------
    if ( not T.check() ) return false;

    if ( T.size() < 2 ) return true ;
    for ( const_iterator Alfa = begin() +1; Alfa != end() ; ++Alfa)
    {   if ( cmpr (fltr(*Alfa), fltr ( *(Alfa -1))))
        {   std::cout<<"Error in the order of the elements\n";
            return false ;
        };
    };
    return true;
};
//---------------------------------------------------------------------------
//  function : Imprimir
/// @brief print the sorted_tree with all the details and pointers
//---------------------------------------------------------------------------
void Imprimir(std::ostream &salida)const
{
    T.Imprimir(salida) ;
};
#endif

//###########################################################################
//
//        P R O T E C T E D    F U N C T I O N S
//
//###########################################################################
//
//***************************************************************************
//   R E M O V E _ C O N S T
//
//  sorted_tree * remove_const ( void )const;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : remove_const
/// @brief Function for to obtain sorted_tree pointer from  a
///        const sorted_tree
/// @param [in] none
/// @return pointer
/// @remarks
//---------------------------------------------------------------------------
sorted_tree * remove_const ( void )const
{   return const_cast <sorted_tree*> ( this);
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node_t pointer in a node_t<T> pointer
/// @param [in] P base_node_t pointer
/// @return Pointer
//---------------------------------------------------------------------------
static node_t *    upgrade ( base_node_t * P ) NOEXCEPT
{   return  static_cast < node_t *>      ( P );
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node_t pointer in a node_t<T> pointer
/// @param [in] P base_node_t pointer
/// @return Pointer
//---------------------------------------------------------------------------
static const node_t * upgrade ( const base_node_t * P ) NOEXCEPT
{   return  static_cast < const node_t *>( P );
};

//***************************************************************************
};//       E N D  S O R T E D _ T R E E    C L A S S
//***************************************************************************

#if __DEBUG_CNTREE  != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the sorted_tree
/// @param [in] salida : ostream where write the information
/// @param [in] A : sorted_tree to print
/// @return ostream after the printing
//---------------------------------------------------------------------------
template < typename value_t, typename key_t, typename filter_t ,
           typename comp_key_t, typename alloc_t >
std::ostream & operator<<( std::ostream &salida ,
const sorted_tree <value_t,key_t,filter_t,comp_key_t,alloc_t> & A)
{
    salida<<A.T  ;
    return salida ;
};

#endif
//***************************************************************************
};//               E N D    F O R E S T    N A M E S P A C E
//
};//              E N D    C O U N T E R T R E    N A M E S P A C E
//***************************************************************************
#endif
