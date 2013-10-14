//----------------------------------------------------------------------------
/// @file   tree.hpp
/// @brief  This file contains the implementation of the tree
///
/// @author Copyright (c) 2010 2013 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks This class is a container of nodes. This is the base class for other
///          classes with ordered and unordered nodes
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_TREE_HPP
#define __COUNTERTREE_FOREST_TREE_HPP

#include <typeinfo>
#include <type_traits>
#include <functional>
#include <boost/countertree/forest/branch.hpp>
#include <boost/countertree/forest/node.hpp>
#include <boost/countertree/forest/iterator.hpp>
#include <boost/countertree/forest/reverse_iterator.hpp>

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
//                           C L A S S                                    ##
//                C O N N E C T O R   < V A L U E _ T >                   ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
/// @class  connector
/// @brief  This class comprise all the information for to connect a new
///         node in the tree \n
//
/// @remarks
//---------------------------------------------------------------------------
struct connector
{   //---------------------------- variables ---------------------
    base_node * P ;
    bool left_side ;
    //----------------------- functions --------------------------
    connector (base_node * const P1=NULL,bool Left=false):P(P1),left_side(Left){};
};


//##########################################################################
//                                                                        ##
//                           C L A S S                                    ##
//         T R E E   < V A L U E _ T , N O D E _ A L L O C _ T >          ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
/// @class  tree
/// @brief  This class have the same interface than the STL vector,
///         but istead of be a vector is a tree. \n
///         Due to this all the operations ( insert, delete, access)
///         a O( logN). \n
//
/// @remarks
//---------------------------------------------------------------------------
template < typename value_t,
           typename node_alloc_t = std::allocator < node<value_t> >
         >
class tree
{
//***************************************************************************
//                 S T A T I C     A S S E R T
//***************************************************************************
static_assert ( std::is_same < node<value_t>,
                               typename node_alloc_t::value_type >::value ,
               " Bad type in the node allocator" );
public:
//***************************************************************************
//                     D E F I N I T I O N S
//***************************************************************************
typedef c_common::signed_type                     size_type ;
typedef c_common::signed_type                     difference_type ;
typedef       value_t                             value_type;
typedef       value_type *                        pointer;
typedef const value_type *                        const_pointer;
typedef       value_type &                        reference;
typedef const value_type &                        const_reference;
typedef c_forest::node <value_t>                  node_t;
typedef c_forest::base_node                       base_node ;
//typedef c_forest::connector <value_t>             connector_t  ;

typedef  c_forest::iterator              <tree>   iterator;
typedef  c_forest::const_iterator        <tree>   const_iterator;
typedef  c_forest::reverse_iterator      <tree>   reverse_iterator;
typedef  c_forest::const_reverse_iterator<tree>   const_reverse_iterator;
typedef  c_forest::base_iterator         <tree>   base_iterator;
typedef  c_forest::const_base_iterator   <tree>   const_base_iterator;

friend struct c_forest::const_base_iterator   <tree>;
friend struct c_forest::base_iterator         <tree>;
friend class c_forest::iterator              <tree>;
friend class c_forest::const_iterator        <tree> ;
friend class c_forest::reverse_iterator      <tree> ;
friend class c_forest::const_reverse_iterator<tree>;

template < typename value1_t,typename node_alloc_t2> friend class tree;


protected:
//***************************************************************************
//            P R O T E C T E D      V A R I A B L E S
//***************************************************************************
node_alloc_t    node_alloc ;
base_node *root ,*first, *last ;
signed_type     n_level  ;


public:
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
//  C O N S T R U C T O R S , D E S T R U C T O R
//
//  explicit tree ( const node_alloc_t & na = node_alloc_t()) NOEXCEPT
//  tree ( const tree & T)
//
//  template <typename node_alloc2_t >
//  tree ( const tree<value_t, node_alloc2_t> & T)
//
//  tree ( tree &&B) NOEXCEPT
//  ~tree (void)
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : tree
/// @brief  Constructor
/// @param [in] na : node allocator
//---------------------------------------------------------------------------
explicit tree ( const node_alloc_t & na = node_alloc_t()) NOEXCEPT
:node_alloc(na),root(NULL),first(NULL),last(NULL),n_level(0) { };

//---------------------------------------------------------------------------
//  function : tree
/// @brief  copy constructor
/// @param [in] T : tree to copy
//---------------------------------------------------------------------------
tree ( const tree & T)
: node_alloc(),root(NULL),first(NULL),last(NULL),n_level(0)
{   //------------------------ begin ----------------------
    copy ( T) ;
};
//---------------------------------------------------------------------------
//  function : tree
/// @brief  copy constructor
/// @param [in] T : tree to copy
//---------------------------------------------------------------------------
template <typename node_alloc2_t >
tree ( const tree<value_t, node_alloc2_t> & T)
: node_alloc(std::cref(T.node_alloc)),root(NULL),first(NULL),last(NULL),n_level(0)
{   //-------------------------- begin --------------------------------
    copy ( T) ;
};
//---------------------------------------------------------------------------
//  function : tree
/// @brief  constructor from a rvalue
/// @param [in] B : tree  to move
//---------------------------------------------------------------------------
tree ( tree &&B) NOEXCEPT
: node_alloc ( std::move (B.node_alloc)),
root(B.root),first(B.first),last(B.last),n_level (B.n_level)
{   B.root = B.first= B.last = NULL ;
    B.n_level = 0;
};

//---------------------------------------------------------------------------
//  function : ~tree
/// @brief  Destructor
//---------------------------------------------------------------------------
virtual ~tree (void)
{   clear();
    root=first=last=NULL;
    n_level =0 ;
};

//***************************************************************************
//   O P E R A T O R = , A S S I G N
//
//  tree & operator = ( tree &&B)
//  tree & operator = ( const tree & T )
//
//  template <typename node_alloc2_t >
//  tree & operator = ( const tree<value_t, node_alloc2_t> & T )
//
//  template <class InputIterator>
//  void assign ( InputIterator it_first, InputIterator it_last )
//
//  template <class InputIterator>
//  void assign_if ( InputIterator it_first, InputIterator it_last,
//                   std::function < bool ( const value_type & )>  M )
//
//  void assign ( unsigned_type n, const value_t& u )
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in]  B : tree to move
/// @return reference to the actual object
//---------------------------------------------------------------------------
tree & operator = ( tree &&B)
{   //--------------- begin -----------
    if ( this == &B ) return *this ;
    move ( std::move (B));
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T : tree to copy
/// @return reference to the actual object
//---------------------------------------------------------------------------
tree & operator = ( const tree & T )
{   if ( this == &T ) return *this ;
    clear();
    copy ( T);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief asignation operator
/// @param [in] T : tree to copy
/// @return reference to the actual object
//---------------------------------------------------------------------------
template <typename node_alloc2_t >
tree & operator = ( const tree<value_t, node_alloc2_t> & T )
{   //------------------------ begin ---------------------------
    clear();
    copy ( T);
    return *this ;
};

//---------------------------------------------------------------------------
//  function : assign
/// @brief Assign a range of data, dropping all the elements of the
///        container.
///        It's like the assignation operator but with several parameters
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void assign ( InputIterator it_first, InputIterator it_last )
{   //---------------------- begin ---------------------------
    clear() ;
    for (  ; it_first != it_last ; ++it_first)
    {   node_t * PAux = allocate (1);
        construct ( PAux, (*it_first));
        connect( PAux, connector ( last, false));
    };
} ;
//---------------------------------------------------------------------------
//  function : assign_if
/// @brief Assign a range of data, dropping all the elements of the
///        container
///        It's like the assignation operator but with several parameters
/// @param [in] it_first : iterator to the first element to insert
/// @param [in] it_last : Iterator to the end of the range
/// @param [in] M : function which receives an element and when return true
///                 the lement is inserted and when false , not
/// @return none
//---------------------------------------------------------------------------
template <class InputIterator>
void assign_if ( InputIterator it_first, InputIterator it_last,
                 std::function < bool ( const value_type & )>  M )
{   //---------------------- begin ---------------------------
    clear();
    for (  ; it_first != it_last ; ++it_first)
    {   if ( M ( *it_first))
        {   node_t * PAux = allocate (1);
            construct ( PAux , (*it_first));
            connect( PAux, connector_end());
        };
    };
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
void assign ( signed_type n, const value_t& u )
{   //----------------------- begin -------------------
    clear ( );
    for ( signed_type i = 0 ; i < n ; i ++)
    {   node_t * PAux = allocate (1);
        construct( PAux,  u ) ;
        connect( PAux, connector_end());
    };
};
//
//***************************************************************************
//    C O P Y , C L E A R , M O V E , A S S I G N , R E S I Z E
//    C A P A C I T Y , E M P T Y
//
//  template < typename node_alloc_t2 >
//  void copy (const tree< value_t, node_alloc_t2> &T)
//
//  void clear  ( void );
//  void move   ( tree &&B )
//  void resize ( signed_type sz,value_t c = value_t())
//  void swap   ( tree & B )
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : copy
/// @brief Asignation operator
/// @param [in] A : tree from where copy the data
/// @return Reference to the tree after the copy
//---------------------------------------------------------------------------
template < typename node_alloc_t2 >
void copy (const tree< value_t, node_alloc_t2> &T) ;

//---------------------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the tree
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
void clear ( void );

//---------------------------------------------------------------------------
//  function : move
/// @brief Move all the elements of the tree
/// @param [in] none
/// @return none
/// @remarks : this function don't clear the elements in the actual object
//---------------------------------------------------------------------------
void move (tree &&B )
{   //-------------- begin ----------------
    if ( this == &B) return ;
    clear();
    root = B.root ;
    first= B.first ;
    last = B.last ;
    n_level= B.n_level;
    B.root = B.first= B.last = NULL ;
    B.n_level = 0;
}
//---------------------------------------------------------------------------
//  function : resize
/// @brief resize the current vector size and change to sz.\n
///        If sz is smaller than the current size, delete elements to end\n
///        If sz is greater than the current size, insert elements to the
///        end with the value c
/// @param [in] sz : new size of the tree after the resize
/// @param [in] c : Value to insert if sz is greather than the current size
/// @return none
//---------------------------------------------------------------------------
void resize ( signed_type sz,value_t c = value_t())
{   //-------------------- begin ------------------------
    if ( size() >= sz)
    {   while  ( sz != size())
        {   node_t * PAux = (node_t *)last ;
            disconnect ( PAux ) ;
            destroy ( PAux ) ;
            deallocate ( PAux,1 ) ;
        };
    }
    else
    {   for ( signed_type i = size() ; i < sz; ++i)
        {   node_t * PAux = allocate (1);
            construct( PAux,  c ) ;
            connect( PAux, connector_end());
        };
    };
};
//---------------------------------------------------------------------------
//  function : swap
/// @brief swap two trees
/// @param [in] B : tree to swap
//---------------------------------------------------------------------------
void swap  ( tree & B )
{   if ( this ==  &B) return ;
    std::swap ( root, B.root);
    std::swap ( first, B.first) ;
    std::swap ( last , B.last ) ;
    std::swap ( n_level, B.n_level);
};
//
//***************************************************************************
//  C A P A C I T Y , E M P T Y ,  S I Z E  , L E V E L S
//
//  signed_type     capacity( void) const NOEXCEPT
//  bool            empty   ( void) const NOEXCEPT
//  signed_type     size    ( void) const NOEXCEPT
//  signed_type     levels  ( void) const NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : capacity
/// @brief return the maximun size of the container
/// @return maximun size of the container
//---------------------------------------------------------------------------
signed_type capacity ( void) const NOEXCEPT
{   return ( (std::numeric_limits<signed_type>::max)() );
};
//---------------------------------------------------------------------------
//  function : empty
/// @brief indicate if the map is empty
/// @return true if the map is empty, false in any other case
//---------------------------------------------------------------------------
bool empty ( void) const NOEXCEPT
{   return (size() == 0) ;
};
//---------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements in the tree
/// @return number of elements in the tree
//---------------------------------------------------------------------------
signed_type size ( void) const  NOEXCEPT
{   return (signed_type) base_node::nd(root);
};
//---------------------------------------------------------------------------
//  function : levels
/// @brief return the number of levels in the tree
/// @return number of levels in the tree
/// @remarks This function is for debug only
//---------------------------------------------------------------------------
signed_type levels ( void) const NOEXCEPT
{   return n_level;
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
//  A T , O P E R A T O R [ ] , F R O N T , B A C K
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
//
//---------------------------------------------------------------------------
//  function : operator[ ]
/// @brief  Checked access to an element by their position in the tree
/// @param  [in] Pos : Position to read
/// @return Reference to the object selected
/// @remarks This operation is O (log(N))
//---------------------------------------------------------------------------
value_t & operator[] ( signed_type Pos) NOEXCEPT
{   assert ( Pos >= (signed_type)0 and Pos < size() ) ;
    return (upgrade(ptr_pos (Pos)))->data;
};
//---------------------------------------------------------------------------
//  function : operator[ ]
/// @brief  Checked access to an element by their position in the tree
/// @param  [in] Pos : Position to read
/// @return Const reference to the object selected
/// @remarks This operation is  O(log(N))
//---------------------------------------------------------------------------
const value_t & operator[] ( signed_type Pos)const NOEXCEPT
{   assert ( Pos >= (signed_type)0 and Pos < size() ) ;
    return (upgrade(ptr_pos (Pos)))->data;
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a reference to the first element in the tree
/// @param  [in]  none
/// @return reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & front (void ) NOEXCEPT
{   assert ( first != NULL ) ;
    return  upgrade( first)->data ;
};
//---------------------------------------------------------------------------
//  function : front
/// @brief  Return a const_reference to the first element in the tree
/// @param  [in]  none
/// @return const_reference to the first element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & front ( void) const NOEXCEPT
{   assert ( first != NULL ) ;
    return ( upgrade(first)->data) ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a reference to the last element in the tree
/// @param  [in]  none
/// @return reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
value_t & back ( void) NOEXCEPT
{   assert ( last != NULL ) ;
    return ( upgrade(last)->data) ;
};
//---------------------------------------------------------------------------
//  function : back
/// @brief  Return a const_reference to the last element in the tree
/// @param  [in]  none
/// @return const_reference to the last element
/// @remarks This operation is  O(constant))
//---------------------------------------------------------------------------
const value_t & back (void ) const NOEXCEPT
{   assert ( last != NULL ) ;
    return ( upgrade(last)->data) ;
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
//          P U S H _ F R O N T , P U S H _ B A C K
//          I N S E R T _ P O S , I N S E R T
//
//  template <class ... Args>
//  iterator emplace_internal(connector C, Args && ... args)
//
//  iterator push_front ( const value_t &D )
//
//  template <class ... Args>
//  iterator emplace_front ( Args && ... args )
//
//  iterator push_back ( const value_t & D )
//
//  template <class ... Args>
//  iterator  emplace_back( Args && ... args )
//
//  iterator insert_pos(const value_t &D , signed_type Pos)
//
//  template <class ... Args>
//  iterator emplace_pos(signed_type Pos, Args && ... args)
//
//  iterator insert ( iterator  iter , const value_t &D )
//
//  template <class ... Args>
//  iterator emplace ( iterator  iter , Args && ... args )
//
//  template <class ... Args>
//  node_t * insert_value_before_pointer ( node_t * P1 , Args&& ... args )
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
{   //------------------ begin-----------------
    node_t * PAux = allocate (1) ;
    construct ( PAux , std::forward<Args> ( args) ... );
    connect ( PAux , C ) ;
    return iterator ( PAux, this) ;
};
//---------------------------------------------------------------------------
//  function : push_front
/// @brief insert an element in the front of the container
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
iterator push_front ( const value_t &D )
{   return emplace_front ( D);
};
//---------------------------------------------------------------------------
//  function : emplace_front
/// @brief insert an element in the front of the container
/// @param [in] args : arguments for to build the node to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_front ( Args && ... args )
{   return emplace_internal (connector_begin(),std::forward <Args>(args)...);
};
//---------------------------------------------------------------------------
//  function : push_back
/// @brief Insert one element in the back of the container
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
iterator push_back ( const value_t & D )
{   return emplace_back( D);
};
//---------------------------------------------------------------------------
//  function : emplace_back
/// @brief Insert one element in the back of the container
/// @param [in] args : arguments for to build the node to insert
/// @return iterator to the element inserted
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
template <class ... Args>
iterator  emplace_back( Args && ... args )
{   return emplace_internal (connector_end(),std::forward <Args>(args)...);
};
//---------------------------------------------------------------------------
//  function : insert_pos
/// @brief insert an element in a specified position
/// @param [in] D : value to insert
/// @param [in] Pos : Position to insert the value
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
iterator insert_pos( signed_type Pos ,const value_t &D  )
{   return emplace_pos ( Pos, D);
};
//---------------------------------------------------------------------------
//  function : emplace_pos
/// @brief insert an element in a specified position
/// @param [in] args : arguments to build the node to insert
/// @param [in] Pos : Position to insert the value
/// @return iterator to the element inserted
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace_pos(signed_type Pos, Args && ... args)
{   assert ( Pos >= 0 and Pos <= size());
    connector C = connector_pos ( Pos);
    return emplace_internal ( C , std::forward<Args> ( args) ...);
};
//---------------------------------------------------------------------------
//  function : insert
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] P1 : Itera which indicates the position to insert the value
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
iterator insert ( iterator  iter , const value_t &D )
{   return emplace (iter, D);
};
//---------------------------------------------------------------------------
//  function : emplace
/// @brief insert an element in the previous position to the pointed by
///        the iterator
/// @param [in] P1 : Itera which indicates the position to insert the value
/// @param [in] D : value to insert
/// @return iterator to the element inserted
/// @remarks If the iterator is rend() there is an error  because we
///          can't insert before it
//---------------------------------------------------------------------------
template <class ... Args>
iterator emplace ( iterator  iter , Args && ... args )
{   //------------------------ begin -------------------------------
    assert  ( iter.ptr_tree() ==this and iter.ptr_node() != PMIN);
    connector C =(iter==end())?connector_end():connector_pointer (iter.ptr_node());
    return emplace_internal ( C ,std::forward <Args> ( args)... );
};
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
//  function : connector_begin
/// @brief return the connector for to insert an element in the first position
///        of the tree
/// @return connector filled
/// @remarks This operation is Kte
//---------------------------------------------------------------------------
connector connector_begin ( void) NOEXCEPT
{   //assert ( root != NULL);
    return connector ( first, true);
};
//---------------------------------------------------------------------------
//  function : connector_end
/// @brief return the connector for to insert an element in the first position
///        of the tree
/// @return connector filled
/// @remarks This operation is Kte
//---------------------------------------------------------------------------
connector connector_end ( void) NOEXCEPT
{   //assert ( root != NULL);
    return connector ( last, false);
};
//---------------------------------------------------------------------------
//  function : connector_pos
/// @brief return the connector for to insert a new node in the position Pos
/// @param [in] Pos : Position to insert the value
/// @return connector for the insertion
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
connector connector_pos (signed_type Pos ) NOEXCEPT
{   //--------------------------------- begin --------------------------
    assert ( Pos >= 0 and Pos <= size()) ;
    base_node * P2 ;
    if ( Pos == 0 )      return connector_begin () ;
    if ( Pos == size() ) return connector_end() ;

    // Busqueda del puntero para enlazar el node_t
    base_node ** PP1 =  (base_node **)&root;
    P2 = root ;
    signed_type N1 = 0 ;
    while ( *PP1 != NULL )
    {   P2 = *PP1 ;
        if ( Pos > (N1 = P2->n_left()) )
        {   Pos -= ( N1 + 1 ) ;
            PP1 =  (&(P2->right)) ;
        }
        else PP1 =  (&(P2->left)) ;
    };
    bool left_side = (&(P2->left)== PP1 );
    return connector ( P2, left_side);
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
{   //------------------------------ begin -------------------------------------
    assert ( Ptr != PMIN and Ptr != PMAX);
    // We tray to insert the node_t in the right pointer of the previous node_t
    // under it. If it is not possible, insert in the left pointer of P1
    base_node * P2 = Ptr ;
    if ( P2->left  != NULL )
    {   P2 = P2->left ;
        while ( P2->right != NULL) P2 = P2->right ;
    };
    return connector ( P2, ( P2 == Ptr)  );
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
//  D E L E T I O N S    O F   E L E M E N T S
//
//  void erase_internal ( node_t * PAux )
//
//  void        pop_front ( void );
//  void        pop_back  ( void );
//
//  void        erase  ( const_iterator P1);
//  signed_type erase  ( const_iterator first_it, const_iterator last_it);
//
//  signed_type erase_if ( const_iterator first_it, const_iterator last_it,
//                         std::function< bool (const value_type & )>  M1    )
//
//  void        erase_pos   ( signed_type Pos);
//  void        erase_pos   ( signed_type Prim, signed_type Ult);
//
//  void erase_pos_if ( signed_type Prim, signed_type Ult,
//                      std::function < bool(const value_type &)> M)
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : erase_internal
/// @brief erase the first element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O (constant)
//---------------------------------------------------------------------------
void erase_internal ( node_t * PAux )
{   assert ( PAux != NULL);
    disconnect ( PAux) ;
    destroy ( PAux ) ;
    deallocate ( PAux, 1 ) ;
};
//---------------------------------------------------------------------------
//  function : pop_front
/// @brief erase the first element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O (constant)
//---------------------------------------------------------------------------
void pop_front ( void )
{   assert ( root != NULL);
    erase_internal ( upgrade (first));
};
//---------------------------------------------------------------------------
//  function :pop_back
/// @brief erase the last element of the container
/// @param [in] none
/// @return none
/// @remarks This operation is O(constant)
//---------------------------------------------------------------------------
void pop_back ( void)
{   assert ( root != NULL);
    erase_internal ( upgrade( last ));
};
//---------------------------------------------------------------------------
//  function : erase
/// @brief erase the element pointed by the iterator P1
/// @param [in] P1 : iterator to the element to erase
/// @return iterator to the next element
/// @remarks This operation is O ( constant)
//---------------------------------------------------------------------------
const_iterator  erase ( const_iterator iter)
{   //------------------- begin ---------------------------
    assert ( size() > 0 and iter.ptr_tree() == this and
            iter.ptr_node() != PMIN and iter.ptr_node() != PMAX);
    node_t  *P1= const_cast < node_t*> (iter.ptr_node());
    iter++ ;
    erase_internal ( P1);
    return iter ;
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
{   //------------------ begin ---------------------------
    if ( first_it == last_it ) return 0 ;
    signed_type N = last_it - first_it ;
    assert ( is_mine( first_it) and is_mine( last_it) and N > 0) ;
    const_iterator Alfa = first_it, Beta = first_it ;

    while ( Beta != last_it)
    {   Alfa = Beta ;
        Beta++ ;
        node_t * Gamma = const_cast <node_t*> ( Alfa.ptr_node() ) ;
        erase_internal ( Gamma);
    } ;
    return N ;
};
//---------------------------------------------------------------------------
//  function : erase_if
/// @brief erase a range of elements between first_it and last_it
/// @param [in] first_it : iterator to the first element
/// @param [in] last_it : iterator to the final element of the range
/// @return number of elements erased
/// @remarks
//---------------------------------------------------------------------------
signed_type erase_if ( const_iterator first_it, const_iterator last_it,
                       std::function< bool (const value_type & )>  M1    )
{   //------------------ begin ---------------------------
    if ( first_it == last_it ) return 0 ;
    signed_type N = last_it - first_it ;
    assert ( is_mine( first_it) and is_mine( last_it) and N > 0) ;
    N = 0 ;
    const_iterator Alfa = first_it, Beta = first_it ;

    while ( Beta != last_it)
    {   Alfa = Beta ;
        Beta++ ;
        if ( M1 (*Alfa))
        {   node_t * Gamma = const_cast <node_t*> ( Alfa.ptr_node() ) ;
            erase_internal ( Gamma);
            N++;
        };
    } ;
    return N ;
};
//---------------------------------------------------------------------------
//  function : erase_pos
/// @brief erase the element of the position pos
/// @param [in] pos : position to delete
/// @return void
/// @remarks This operation is O ( log(N) )
//---------------------------------------------------------------------------
void erase_pos( signed_type Pos)
{   // The function ptr_pos check the limits
    erase_internal (upgrade(ptr_pos ( Pos)) );
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
{   //--------------------- begin ---------------------------
    assert ( First >= 0 and   NElem >= 0 and First < size() );
    if ( (First + NElem) > size() ) NElem = size() - First ;
    iterator C2 = iterator_pos ( First), C1 ;
    for ( signed_type i = 0 ; i < NElem ; i ++)
    {   C1 = C2 ;
        C2++ ;
        erase_internal ( C1.ptr_node()  );
    };
};
//---------------------------------------------------------------------------
//  function : erase_pos_if
/// @brief erase the NElem elements after  the position First if the function
///        M return true when receives the element as parameter
/// @param [in] First : position to the first element to erase
/// @param [in] NElem : number of elements to erase
/// @param [in] M : function for to evaluate the element to erase
/// @return Number of elements erased
/// @remarks
//---------------------------------------------------------------------------
signed_type erase_pos_if ( signed_type First, signed_type NElem,
                            std::function < bool(const value_type &)> M)
{   //--------------------- begin ---------------------------
    assert ( First >= 0 and   NElem >= 0 and First < size() );
    if ( (First + NElem) > size() ) NElem = size() - First ;
    iterator C2 = iterator_pos ( First), C1 ;
    signed_type N_erase = 0 ;
    for ( signed_type i = 0 ; i < NElem ; i ++)
    {   C1 = C2 ;
        C2++ ;
        if ( M ( *C1))
        {   erase_internal ( C1.ptr_node()  );
            N_erase++ ;
        };
    };
    return N_erase ;
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
{   return node_alloc.allocate ( cnt);
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
{   return node_alloc.deallocate ( p , n);;
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
{   node_alloc.construct (p, std::forward <Args>(args)...);
};
//---------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the object without freeing the memory
/// @param [in] p : pointer p to the object to destroy
/// @return
//---------------------------------------------------------------------------
void destroy( node_t * p) NOEXCEPT
{   node_alloc.destroy ( p);
};

//***************************************************************************
//                  P T R _ P O S
//
//  const node_t * get_root ( void ) NOEXCEPT
//  node_t       * upgrade ( base_node * P ) NOEXCEPT
//  const node_t * upgrade ( const base_node * P ) const NOEXCEPT
//
//  base_node       * ptr_pos ( signed_type Pos) NOEXCEPT
//  const base_node * ptr_pos ( signed_type Pos) const NOEXCEPT
//
//  void insert_first_pointer( base_node * PAux ) NOEXCEPT
//
//  void disconnect ( base_node  * PAux ) NOEXCEPT;
//  void connect (base_node * PAux, connector C ) NOEXCEPT;
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : get_root
/// @brief return a pointer to the root node of the tree
/// @param [in] /// @return Pointer
//---------------------------------------------------------------------------
const node_t *    get_root ( void ) const NOEXCEPT
{   return upgrade (root) ;
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node pointer in a node_t<T> pointer
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
node_t *    upgrade ( base_node * P ) NOEXCEPT
{   return  static_cast < node_t *>      ( P );
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node pointer in a node_t<T> pointer
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
const node_t * upgrade ( const base_node * P ) const NOEXCEPT
{   return  static_cast < const node_t *>( P );
};
//---------------------------------------------------------------------------
//  function : ptr_pos
/// @brief Pointer to the node Pos
/// @param [in] Pos : Position to find
/// @return pointer to the position.
/// @remarks This operation is O ( log N). This function is called by others
///          functions with the position controlled
//---------------------------------------------------------------------------
base_node *  ptr_pos ( signed_type Pos) NOEXCEPT
{   //------------------- begin -----------------------
    assert( Pos >= 0 and Pos < size()) ;
    if ( Pos == 0 ) return first ;
    if ( Pos == size()-1) return last ;
    base_node * PH = root ;
    signed_type NI ;
    while ( ( NI = PH->n_left() ) != Pos)
    {   if ( Pos < NI )  PH = PH->left ;
        else
        {   PH = PH->right;
            Pos -= ( NI +1) ;
        };
    };
    return PH ;
};
//---------------------------------------------------------------------------
//  function : ptr_pos
/// @brief Pointer to the node Pos
/// @param [in] Pos : Position to find
/// @return pointer to the position.
/// @remarks This operation is O ( log N). This function is called by others
///          functions with the position controlled
//---------------------------------------------------------------------------
const base_node * ptr_pos ( signed_type Pos) const NOEXCEPT
{   return const_cast <tree *> ( this)->ptr_pos(Pos);
};
//---------------------------------------------------------------------------
//  function : ptr_first
/// @brief Pointer to the first element of the tree
/// @return pointer to the position.
/// @remarks This operation is O (1).
//---------------------------------------------------------------------------
base_node * ptr_first ( void) NOEXCEPT {  return first ;};
//---------------------------------------------------------------------------
//  function : ptr_first
/// @brief Pointer to the first element of the tree
/// @return pointer to the position.
/// @remarks This operation is O (1).
//---------------------------------------------------------------------------
const base_node * ptr_first ( void) const NOEXCEPT {  return first ;};
//---------------------------------------------------------------------------
//  function : ptr_last
/// @brief Pointer to the last element of the tree
/// @return pointer to the position.
/// @remarks This operation is O (1).
//---------------------------------------------------------------------------
base_node * ptr_last ( void) NOEXCEPT {  return last ;};
//---------------------------------------------------------------------------
//  function : ptr_last
/// @brief Pointer to the first element of the tree
/// @return pointer to the position.
/// @remarks This operation is O (1).
//---------------------------------------------------------------------------
const base_node * ptr_last ( void) const NOEXCEPT {  return last ;};

//---------------------------------------------------------------------------
// function : insert_first_pointer
/// @brief insertion with the node_t constructed
/// @param [in] PAux : pointer to the new node_t
/// @return none
//---------------------------------------------------------------------------
void insert_first_pointer( base_node * PAux ) NOEXCEPT
{   //------------------- begin ---------------------
    assert  ( root == NULL);
    first= last=root = PAux ;
    n_level = 1 ;
    PAux->init() ;
    PAux->color = black ;
};
//---------------------------------------------------------------------------
//  function :disconnect
/// @brief disconnect the node_t from the tree, and leave it balanced
///        and with the nodes actualized
/// @param [in] PAux : pointer to the node_t to delete
/// @return none
//  @remarks The counters are decremented by this function
//---------------------------------------------------------------------------
void disconnect ( base_node  * PAux ) NOEXCEPT;
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
void connect (base_node * PAux, connector C ) NOEXCEPT;

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
//
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this tree
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this tree
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_iterator P1) const  NOEXCEPT
{   return ( P1.ptr_tree () == this);
};
//---------------------------------------------------------------------------
//  function : is_mine
/// @brief Check if the iterator is pointing to this tree
/// @param [in] P1 : iterator to check
/// @return (true/false ) Indicate if it is pointing to this tree
/// @remarks This operation is O ( const )
//---------------------------------------------------------------------------
bool is_mine ( const_reverse_iterator P1) NOEXCEPT
{   return ( P1.ptr_tree () == this);
};
//---------------------------------------------------------------------------
//  function : iterator_pos
/// @brief Find a position in the tree
/// @param [in] Pos : Position to find
/// @return Iterator to the position. If don't exists return end()
/// @remarks This operation is O ( log N)
//---------------------------------------------------------------------------
iterator iterator_pos ( signed_type Pos1) NOEXCEPT
{   if ( Pos1 <  0      ) return it_rend () ;
    if ( Pos1 >= size() ) return it_end  () ;
    return iterator ( (node_t *) ptr_pos (Pos1), this);
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
{   if ( Pos1 <  0      ) return cit_rend() ;
    if ( Pos1 >= size() ) return cit_end () ;
    return const_iterator ( (node_t *) ptr_pos (Pos1), this);
};
//---------------------------------------------------------------------------
//  function : get_it
/// @brief create an iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
iterator get_it  ( node_t * P1) { return iterator (P1, this );};
//---------------------------------------------------------------------------
//  function : get_cit
/// @brief create an const_iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
const_iterator  get_cit ( const node_t * P1){ return const_iterator ( P1, this);};
//---------------------------------------------------------------------------
//  function : get_rit
/// @brief create an reverse_iterator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
reverse_iterator  get_rit( node_t * P1){ return reverse_iterator (P1, this );};
//---------------------------------------------------------------------------
//  function : get_crit
/// @brief create an const_ireverse_terator from a node pointer
/// @param [in] P1 : pointer
/// @return iterator which point this node
//---------------------------------------------------------------------------
const_reverse_iterator  get_crit ( const node_t * P1)
{   return const_reverse_iterator ( P1, this);
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a const_iterator to an iterator
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
iterator upgrade ( const_iterator CT)
{   assert (is_mine(CT) );
    return get_it ( const_cast <node_t*> ( CT.ptr_node()));
}
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
iterator it_begin( void) NOEXCEPT
{   return iterator::begin( this);
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
{   return iterator::end( this);
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
{   return iterator::rbegin( this);
};
//---------------------------------------------------------------------------
//  function : it_rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
iterator it_rend( void) NOEXCEPT
{   return iterator::rend( this);
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
const_iterator cit_begin( void) const NOEXCEPT
{   return const_iterator::begin( this);
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
{   return const_iterator::end( this);
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
{   return const_iterator::rbegin(this);
};
//---------------------------------------------------------------------------
//  function : cit_rend
/// @return const_iterator to the previous elemento to the first
//---------------------------------------------------------------------------
const_iterator cit_rend( void) const NOEXCEPT
{   return const_iterator::rend( this);
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
reverse_iterator rit_begin( void) NOEXCEPT
{   return reverse_iterator::begin( this);
};
//---------------------------------------------------------------------------
//  function : rit_end
/// @return reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
reverse_iterator rit_end( void) NOEXCEPT
{   return reverse_iterator::end( this);
};
//---------------------------------------------------------------------------
//  function : rit_rbegin
/// @return reverse_iterator to the last element
//---------------------------------------------------------------------------
reverse_iterator rit_rbegin( void) NOEXCEPT
{   return reverse_iterator::rbegin( this);
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
{   return reverse_iterator::rend( this);
};
//---------------------------------------------------------------------------
//  function : rend
/// @return iterator to the previous elemento to the first
//---------------------------------------------------------------------------
reverse_iterator rend( void) NOEXCEPT
{   return rit_rend();
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
const_reverse_iterator crit_begin( void) const NOEXCEPT
{   return const_reverse_iterator::begin( this);
};
//---------------------------------------------------------------------------
//  function : crit_end
/// @return const_reverse_iterator to the next element after the last
//---------------------------------------------------------------------------
const_reverse_iterator crit_end( void) const NOEXCEPT
{   return const_reverse_iterator::end( this);
};
//---------------------------------------------------------------------------
//  function : crit_rbegin
/// @return const_reverse_iterator to the last element
//---------------------------------------------------------------------------
const_reverse_iterator crit_rbegin( void) const NOEXCEPT
{   return const_reverse_iterator::rbegin( this);
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
{   return const_reverse_iterator::rend( this);
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
protected :
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #     P R O T E C T E D   F U N C T I O N S        #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################
//***************************************************************************
//  P R O T E C T E D   F U N C T I O N S   O F   T R E E
//
//  base_node ** pointer_father ( base_node * P ) NOEXCEPT
//  base_node ** upper_branch ( branch &R , uint32_t & Cod ) NOEXCEPT
//
//***************************************************************************
//
//---------------------------------------------------------------------------
//  function : pointer_father
/// @brief return a pointer to pointer to the node_t black of the branch
/// @param [in] P : pointer to a node_t
/// @return pointer to pointer to the black node_t of the branch
//---------------------------------------------------------------------------
base_node ** pointer_father ( base_node * P ) NOEXCEPT
{   assert ( P != NULL );
    base_node * Pup = P->up ;
    if ( Pup == NULL )
    {   assert ( root == P ) ;
        return ( &root) ;
    };
    return ((Pup->left == P)?& ( Pup->left ) : &(Pup->right )) ;
};
//---------------------------------------------------------------------------
//  function : upper_branch
/// @brief Take the address of the pointer to the upper branch.\n
///        It provides too, the code of the pointer in the upper branch wich
///        connect the two branch
/// @param [in] R : lower branch
/// @param [in] Cod : code of the pointer which connect the two branchs\n
///             The description of this code is\n
///                 000 : pointer left black node_t\n
///                 001 : pointer right black node_t\n
///                 010 : pointer left  of left node_t\n
///                 011 : pointer right of left node_t\n
///                 100 : pointer left of right node_t\n
///                 101 : pointer right of right node_t
/// @return Address of the pointer to the upper branch
//---------------------------------------------------------------------------
base_node ** upper_branch ( branch &R , uint32_t & Cod ) NOEXCEPT
{   //-------------------begin-------------------
    Cod = 0 ;
    base_node *PBlack = *R.ppblack;
    base_node *up = PBlack->up ;
    base_node *Inf = PBlack ;
    if ( up == NULL ) return NULL ;
    if ( up->right == Inf ) Cod ++ ;
    if ( up->color == red )
    {   Inf = up ;
        up = up->up ;
        Cod += (up->left == Inf ) ? 2 : 4 ;
    };
    if ( up->color == black )
    {   Inf = up ;
        up = up->up ;
        if ( up == NULL ) return  &root ;
        return  ((up->left == Inf)?&(up->left):&(up->right)) ;
    };
    assert(false);
    return NULL ;
};

public:
//***************************************************************************
//   D E B U G   F U N C T I O N S
//
//  bool check (  void ) const;
//  void Imprimir(void)const;
//
//***************************************************************************
#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : check
/// @brief check if the tree is OK
/// @return true : OK    false : Error in the tree
//---------------------------------------------------------------------------
bool check (  void ) const;
//---------------------------------------------------------------------------
//  function : Imprimir
/// @brief print the tree with all the details and pointers
//---------------------------------------------------------------------------
void Imprimir(std::ostream &salida)const
{
    print_tree_struct( salida ,root);
    salida<<"Number of nodes :"<<size() ;
    salida<<"  Number of levels :"<<levels()<<std::endl ;
    for ( signed_type i = 0 ; i < size() ; ++i)
        salida<<operator[ ](i)<<"  ";
    salida<<std::endl;
};
#endif
//***************************************************************************
};//              E N D  T R E E    C L A S S
//***************************************************************************
//
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #     N O N    I N L I N E   F U N C T I O N S     #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
//  function : copy
/// @brief Copy one tree in other
/// @param [in] A : tree from where copy the data
/// @return Reference to the tree after the copy
//---------------------------------------------------------------------------
template < typename value_t, typename node_alloc_t>
template <typename node_alloc2_t>
void tree<value_t,node_alloc_t>::copy (const tree <value_t, node_alloc2_t> & T )
{   //------------- begin -------------------
    if ( (void*)this  == (void*) (&T) ) return ;
    clear() ;
    node_t *P= NULL ;
    const node_t *PT = upgrade(T.root) ;
    node_t * P_dest ;
    const node_t * P_org ;

    if ( PT != NULL )
    {   P = allocate ( 1) ;
        construct (P, PT->data) ;
        P->color = PT->color ;
        P->N = PT->N ;
        P->up = NULL ;
        root = P ;
    };
    while ( PT != NULL )
    {   if ( P->right == NULL and PT->right != NULL )
        {   P->right = allocate (1) ;
            P_dest = upgrade ( P->right);
            P_org = upgrade ( PT->right);
            construct (  P_dest, P_org->data);
            P_dest->color = P_org->color ;
            P_dest->N = P_org->N ;
            P->right->up = P ;
            P = upgrade(P->right) ;
            PT = upgrade(PT->right) ;
        }
        else
        {   if ( P->left == NULL and PT->left != NULL )
            {   P->left = allocate (1) ;
                P_dest = upgrade ( P->left);
                P_org = upgrade ( PT->left);
                construct ( P_dest, P_org->data);
                P_dest->color = P_org->color ;
                P_dest->N = P_org->N ;
                P->left->up = P ;
                P = upgrade(P->left) ;
                PT = upgrade(PT->left );
            }
            else
            {   P = upgrade(P->up) ;
                PT = upgrade(PT->up) ;
            };
        };
    };
    n_level = T.n_level ;
    if (root == NULL) first= last = NULL ;
    else
    {   base_node * P1 = root ;
        while ( P1->left != NULL ) P1 = P1->left ;
        first = P1 ;
        P1 = root ;
        while ( P1->right != NULL ) P1 = P1->right ;
        last = P1 ;
    };
};
//---------------------------------------------------------------------------
//  function : clear
/// @brief Delete all the elements of the tree
/// @param [in] none
/// @return none
//---------------------------------------------------------------------------
template < typename value_t, typename node_alloc_t>
void tree<value_t,node_alloc_t>::clear( void)
{   //------------ begin--------------------
    base_node * P1 = root ;
    base_node * P2 = NULL ;
    while ( P1 != NULL )
    {   P2 = P1 ;
        if ( P1->right != NULL )
        {   P1= P1->right ;
            P2->right = NULL ;
        }
        else
        {   if ( P1->left != NULL )
            {   P1 = P1->left ;
                P2->left = NULL ;
            }
            else
            {   P1 = P1->up ;
                destroy ( upgrade( P2)) ;
                deallocate ( upgrade( P2),1) ;
            };
        };
    };
    root = first = last = NULL ;
    n_level = 0 ;
};

//---------------------------------------------------------------------------
//  function :disconnect
/// @brief disconnect the node_t from the tree, and leave it balanced
///        and with the nodes actualized
/// @param [in] PAux : pointer to the node_t to delete
/// @return none
//  @remarks The counters are decremented by this function
//---------------------------------------------------------------------------
template < typename value_t, typename node_alloc_t>
void tree<value_t,node_alloc_t>::disconnect ( base_node * PAux ) NOEXCEPT
{   //----------------------------- begin -----------------------------
    assert ( PAux != PMIN and PAux != PMAX and size() > 0);
    if ( size() == 1)
    {   root = first = last = NULL ;
        n_level = 0 ;
        return ;
    };
    // Calculo de first y last
    if ( PAux == first)
    {   first= ( first->right != NULL)? first->right:first->up ;
    };
    if ( PAux == last)
    {   last = (last->left != NULL)?last->left : last->up ;
    } ;
    // Busqueda del sustituto para colocarlo en el lugar de PAux
    base_node * P = PAux ;
    if ( P->left != NULL)
    {   P = P->left ;
        if ( P->right == NULL )
            base_node::swap_contiguous_left ( pointer_father(PAux));
        else
        {   while ( P->right != NULL) P = P->right ;
            base_node::swap_node ( pointer_father(PAux), pointer_father(P));
        };
    };
    // En este punto sabemos que el node_t apuntado por PP esta en la
    // ultima hoja y que puede ser desconectado
    P = PAux ;
    //decrement_path ( P);
    while ( P != NULL)
    {   P->N--;
        P = P->up ;
    };
    P = PAux ;

    uint32_t Cod2 = 0 ;
    if ( P->color == red)
    {   Cod2 = ( P->up->left == P ) ? 2 :4 ;
        P = P->up ;
    };
    // Ahora P apunta al node_t negro de la rama
    base_node ** PP = pointer_father ( P) ;
    branch H ( PP);
    uint32_t Cod = 0;
    base_node ** PPup = upper_branch ( H, Cod) ;
    bool Estable = H.disconnect_node( Cod2, PAux);
    if ( Estable ) return ;

    branch RInf ( H ), Rup ( H ) ;
    while ( not Estable)
    {   if ( PPup == NULL)
        {   Estable = true ;
            n_level-- ;
            if ( root != NULL ) root->color = black ;
        }
        else
        {   Rup.ppblack = PPup ;
            Estable = branch::reverse_cake ( Rup, RInf , Cod );
            RInf = Rup ;
            PPup = upper_branch ( RInf, Cod);
        };
    };
    return ;
};
//---------------------------------------------------------------------------
//  function : connect
/// @brief connect a node_t in the tree and make a rebalanced if necessary
/// @param [in] PAux : pointer to the node_t for to be inserted
/// @param [in] P1 : pointer to the node_t where insert PAux
/// @param [in] Left : indicates which node_t of P1 link to PAux
/// @return none
/// @remarks If the tree is empty P1 and Left are not checked\n
///          This function works well when the tree is empty\n
///          All the counters of the nodes from the insertion point to
///          the root must be previously incremented
//---------------------------------------------------------------------------
//template < typename value_t, typename node_alloc_t>
//void tree<value_t,node_alloc_t>::
//connect (base_node * PAux,base_node * P1,bool Left) NOEXCEPT
template < typename value_t, typename node_alloc_t>
void tree<value_t,node_alloc_t>::
connect (base_node * PAux, connector C ) NOEXCEPT
{   //---------------------------- begin -----------------------------
    #if __DEBUG_CNTREE != 0
    assert ( PAux != PMIN and PAux != PMAX );
    #endif
    // Cuando el tree está vacío *PP1 == NULL
    if ( root == NULL)
    {   insert_first_pointer (PAux );
        return  ;
    };
    #if __DEBUG_CNTREE != 0
    assert ( C.P != PMIN and C.P != PMAX and ((C.left_side)?C.P->left:C.P->right) == NULL );
    #endif

    //increment_path ( base_node  * P ) NOEXCEPT
    base_node  * P = C.P;
    while ( P != NULL)
    {   P->N++;
        P = P->up ;
    };

    // Calculo de la direccion al puntero del nodo negro y el codigo del puntero
    uint32_t Cod = ( C.left_side )?0:1 ;
    base_node * PBlack = C.P ;
    if ( PBlack->color == red )
    {   PBlack = PBlack->up ;
        Cod += ((PBlack->left == C.P)?2:4 );
    };
    base_node ** PP1 =  pointer_father( PBlack);

    // Insercion del node_t en la branch
    branch H (PP1);
    H.insert_node( PAux, Cod);
    if ( H.n_nodes() < 4)
    {   if ( first->left != NULL) first = first->left ;
        if ( last->right != NULL) last = last->right;
        return;
    } ;

    // La branch es inestable y hay que Partir Galleta
    branch RInf ( H ), Rup ( H) ;
    signed_type  NInf = RInf.n_nodes() , Nup = 0 ;
    bool Estable = ( NInf != 4 ) ;
    while ( not Estable)
    {   PP1= upper_branch( RInf,Cod) ;
        branch::break_cake( RInf) ;
        if ( PP1 == NULL)
        {   root->color = black ;
            n_level++ ;
            Estable = true ;
        }
        else
        {   Rup = branch ( PP1);
            Nup = Rup.n_nodes() ;
            Estable = (Nup == 4)?false : true ;
            //
            // Si la rama  que ha recibido el node_t de la rotura de galleta de
            // la rama inferior, tiene mas de 3 nodes, Ha de partir galleta y
            // continuar el proceso en la rama superior
            // Si el código del enlace  del que cuelga es menor que 2, sabemos
            // positivamente que la rama no tiene mas de 3 nodes , y que no
            // necesita hacer rotaciones .
            // Si el código es mayor que 2, y no tiene mas de 3 nodes, implica
            // que hay que hacer una rotación. En cada una de las 4 posibles
            // variantes hay una rotación diferente.
            // Despues de esta rotacion la rama y por tanto el tree quedan
            // estables, por lo que el proceso finaliza
            if (  Nup == 3 )
            {   switch ( Cod )
                {   case 2: Rup.rotate_right_aligned()   ; break ;
                    case 3: Rup.rotate_right_not_aligned() ; break ;
                    case 4: Rup.rotate_left_not_aligned() ; break ;
                    case 5: Rup.rotate_left_aligned()   ; break ;
                    default: ;
               };
            };
            RInf = Rup;
            NInf = Nup ;
        }; // end if
    }; // end while

    // Si PP1 == NULL , indica que hemos alcanzado el node_t root.
    // En este punto solo tenemos que incrementar el contador de niveles

    // Calculo de first y last
    if ( PAux ->left == NULL)
    {   if ( first->left == PAux or PAux->right == first)
            first = PAux ;
    };
    if ( PAux->right == NULL)
    {   if ( last->right == PAux or PAux->left == last)
            last = PAux ;
    }
};
//##########################################################################
//                                                                        ##
//              D E B U G   F U N C T I O N S                             ##
//                                                                        ##
//##########################################################################
#if __DEBUG_CNTREE != 0

//---------------------------------------------------------------------------
//  function : check
/// @brief check if the tree is OK
/// @return true : OK    false : Error in the tree
//---------------------------------------------------------------------------
template < typename value_t, typename node_alloc_t>
bool tree<value_t,node_alloc_t>::check (  void ) const
{   //---------------------- begin -----------------------
    if ( root == NULL and first != NULL)
    {   std::cout<<"Error en el puntero first\n";
        return false ;
    };
    if ( root == NULL and last != NULL)
    {   std::cout<<"Error en el puntero last\n";
        return false ;
    };
    if ( root == NULL ) return true ;
    base_node * P1 = root ;
    while ( P1->left != NULL ) P1 = P1->left ;
    if ( P1 != first)
    {   std::cout<<"Error en el puntero first\n";
        return false ;
    };
    P1 = root ;
    while ( P1->right != NULL ) P1 = P1->right ;
    if ( P1 != last)
    {   std::cout<<"Error en el puntero last\n";
        return false ;
    };
    return Colombo( NULL,root, n_level , false, std::cout) ;
};

//---------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the tree
/// @param [in] salida : ostream where write the information
/// @param [in] A : tree to print
/// @return ostream after the printing
//---------------------------------------------------------------------------
template < typename value_t, typename node_alloc_t>
std::ostream & operator<<( std::ostream &salida ,
                           const tree<value_t, node_alloc_t> & A )
{   //------------------------ begin ------------------------------------
    //typename tree<T,cnc, Alloc>::barrier_read BR ( A.BD);
    //salida<<"Number of nodes :"<<A.size() ;
    //salida<<"  Number of levels :"<<A.levels()<<std::endl ;
    //for ( signed_type i = 0 ; i < A.size() ; ++i)
    //    salida<<A[i]<<"  ";
    //salida<<std::endl;
    A.Imprimir ( salida) ;
    return salida ;
};
#endif
//***************************************************************************
};//              E N D    F O R E S T    N A M E S P A C E
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
namespace std
{
template < typename value_t, typename node_alloc_t>
void swap ( countertree::forest::tree<value_t,node_alloc_t> & A ,
            countertree::forest::tree<value_t,node_alloc_t> & B   )
{   //-------------------------------- begin ---------------------
    A.swap(B);
};
}
#endif
