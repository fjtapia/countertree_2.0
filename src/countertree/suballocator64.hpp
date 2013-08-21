//----------------------------------------------------------------------------
/// @file suballocator64.hpp
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
#ifndef __CNTREE_SUBALLOCATOR64_HPP
#define __CNTREE_SUBALLOCATOR64_HPP

#include <limits>
#include <type_traits>
#include <boost/countertree/alloc/pool64.hpp>
#include <boost/countertree/filter_suballoc.hpp>
#include <boost/countertree/common/unique_object.hpp>


namespace countertree
{
namespace c_common = countertree::common ;
namespace c_alloc = countertree::alloc ;

//#############################################################################
//                                                                           ##
//     ################################################################      ##
//     #                                                              #      ##
//     #                       C L A S S                              #      ##
//     #                                                              #      ##
//     #      B A S I C _ S U B A L L O C 6 4   < ALLOC_T ,T1 >       #      ##
//     #                                                              #      ##
//     ################################################################      ##
//                                                                           ##
//#############################################################################

//
//-------------------------------------------------------------
/// @class basic_suballoc64
///
/// @remarks This class is an allocator with a incremental pool
///          of logaritmic number of elements
//----------------------------------------------------------------
template<typename Alloc_t, typename T1 >
class basic_suballoc64
{
static_assert(std::is_same<typename Alloc_t::value_type,T1>::value, "Error incoherent types") ;
public :

//***************************************************************************
//                 P U B L I C    D E F I N I T I O N S
//***************************************************************************
typedef Alloc_t                                 Allocator ;

typedef uint64_t    size_type ;//Quantities of elements
typedef int64_t     difference_type ;//Difference between two pointers

typedef  T1     	                value_type; //Element type
typedef  T1 *	                    pointer; //Pointer to element
typedef  T1 &	                    reference; //Reference to element
typedef  const T1 * 	            const_pointer; //Constant pointer to element
typedef  const T1 &                 const_reference; //Constant reference to element
/*
typedef typename Allocator::value_type	    value_type; //Element type
typedef typename Allocator::pointer	        pointer; //Pointer to element
typedef typename Allocator::reference	    reference; //Reference to element
typedef typename Allocator::const_pointer	const_pointer; //Constant pointer to element
typedef typename Allocator::const_reference const_reference; //Constant reference to element
*/

static uint64_t const SizeElem = sizeof (value_type );

typedef typename Allocator::template rebind < uint8_t>::other AllocByte;

typedef c_alloc::pool64 <  (SizeElem), false ,AllocByte>  MyPool ;

protected:
//**************************************************************************
//             P R O T E C T E D    V A R I A B L E S
//**************************************************************************
c_common::unique_object<MyPool> PPila;
Allocator A ;

public:
//-**************************************************************************
//   C O N S T R U C T O R ,  D E S T R U C T O R
//
//  explicit basic_suballoc64 ( void)
//  virtual ~basic_suballoc64 ( void)
//-**************************************************************************
explicit basic_suballoc64 ( void ) { };
basic_suballoc64 ( const Allocator &Alfa ):A(Alfa) { };
basic_suballoc64 ( const basic_suballoc64  &Alfa ):A(Alfa.A) { };

virtual ~basic_suballoc64 ( void) { };

//***************************************************************************
//     A D D R E S S     A N D    M A X _ S I Z E
//
//  pointer       address ( reference r);
//  const_pointer address ( const_reference r);
//
//  size_type max_size() const;
//
//***************************************************************************
//
//------------------------------------------------------------------------
//  function : address
/// @brief provide the address of a reference to an object
/// @param [in] r : reference
/// @return Address of the reference
//------------------------------------------------------------------------
pointer address(reference r) { return &r; };

//------------------------------------------------------------------------
//  function : address
/// @brief provide the address of a const_reference to an object
/// @param [in] r : reference
/// @return Address of the const_reference
//------------------------------------------------------------------------
const_pointer address(const_reference r) {  return &r;  };

//------------------------------------------------------------------------
//  function : max_size
/// @brief Maximun size of memory for to allocate
/// @return maximun size of memory
/// @remarks
//------------------------------------------------------------------------
size_type max_size() const
{   //--------------------------- begin ------------------------
    return (std::numeric_limits<size_type>::max)() / SizeElem;
};

//***************************************************************************
//    A L L O C A T E , D E A L L O C A T E
//
//  pointer allocate  ( size_type cnt, const_pointer Alfa = NULL);
//  void    deallocate( pointer p, size_type n= 1 );
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate a block of memory
/// @param [in] cnt : number of objects to allocate
/// @param [in] pointer unused
/// @return pointer to the object allocated
/// @remarks
//------------------------------------------------------------------------
pointer allocate(size_type cnt, const_pointer Alfa = NULL)
{
    return static_cast<pointer> ( (cnt == 1)?(PPila->allocate()):(A.allocate (cnt)) );
};

//------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate a block of memory
/// @param [in] p : pointer to deallocate
/// @param [in] n : number of objects to deallocate
/// @return
/// @remarks
//------------------------------------------------------------------------
void deallocate(pointer p, size_type n=1 )
{   //----------------------- begin ---------------------------
    assert ( n >= 1);
    if ( n == 1 ) PPila->deallocate ( static_cast< void*> (p) );
    else  A.deallocate ( p , n );
};
//
//***************************************************************************
//    C O N S T R U C T ,  D E S T R O Y
//
//   void construct(pointer p, const value_type & t);
//   void destroy(pointer p);
//
//***************************************************************************
//
//------------------------------------------------------------------------
//  function : construct
/// @brief Construct a new object in the memory pointed by p
/// @param [in] p : pointer to the memory for to construct the object
/// @param [in] t : object used as parameter as copy constructor
/// @return
/// @remarks
//------------------------------------------------------------------------
void construct(pointer p, const value_type & t)
{   ::new ((void*)p) value_type  (t);
    //A.construct (p,t);
};
//------------------------------------------------------------------------
//  function : construct
/// @brief Construct a new object in the memory pointed by p
/// @param [in] p : pointer to the memory for to construct the object
/// @param [in] t : rvalue used as parameter as copy constructor
/// @return
/// @remarks
//------------------------------------------------------------------------
void construct(pointer p, value_type && t)
{   //A.construct (p,std::move (t));
    ::new ((void*)p) value_type (std::move (t) );
};
//------------------------------------------------------------------------
//  function : construct
/// @brief Construct a new object in the memory pointed by p
/// @param [in] p : pointer to the memory for to construct the object
/// @param [in] __args : arguments used for to build the node object
/// @return
/// @remarks
//------------------------------------------------------------------------
template<typename _Up, typename... _Args>
void  construct(_Up* __p, _Args&&... __args)
{   //A.construct(__p,std::forward<_Args>(__args)...);
    ::new ((void*)__p) _Up (std::forward<_Args>(__args)...);
};

//------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the object without freeing the memory
/// @param [in] p : pointer p to the object to destroy
/// @return
/// @remarks
//------------------------------------------------------------------------
void destroy(pointer p)
{   //A.destroy (p);
    ((value_type*)p)->~value_type();
};

//***************************************************************************
};//        E N D     S U B A L L O C A T O R 6 4     C L A S S
//***************************************************************************


//#############################################################################
//                          C L A S S                                        ##
//                                                                           ##
// B A S I C _ S U B A L L O C 6 4  < A L L O C A T O R , C N C ,V O I D >   ##
//              ( Specialization for type void )                             ##
//                                                                           ##
//#############################################################################

//-------------------------------------------------------------
/// @class basic_suballoc64
///
/// @remarks This class is an allocator with a incremental pool
///          of alogaritmic number of elements
//----------------------------------------------------------------
template<typename Allocator >
class basic_suballoc64<Allocator, void >
{
public :
//***************************************************************************
//                 P U B L I C    D E F I N I T I O N S
//***************************************************************************
typedef uint64_t    size_type ;//Quantities of elements
typedef int64_t     difference_type ;//Difference between two pointers
typedef void     	                value_type; //Element type
explicit basic_suballoc64 ( void ) { };
basic_suballoc64 ( const Allocator & ) { };
basic_suballoc64 ( const basic_suballoc64  & ) { };

//***************************************************************************
};//        E N D     B A S I C _ S U B A L L O C 6 4     C L A S S
//***************************************************************************

//##########################################################################
//                                                                        ##
//         C L A S S            S U B A L L O C A T O R 6 4               ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class suballocator64
///
/// @remarks This class is an allocator with a incremental pool
///          of alogaritmic number of elements
//----------------------------------------------------------------
template    <   typename Allocator = std::allocator<uint8_t> >
class suballocator64 :
public basic_suballoc64 < typename filter_suballoc<Allocator>::name ,
                          typename filter_suballoc<Allocator>::name::value_type  >
{
public :
//***************************************************************************
//                  D E F I N I T I O N S
//***************************************************************************
typedef typename filter_suballoc<Allocator>::name   FAllocator ;
typedef typename FAllocator::value_type             value_type ;
typedef basic_suballoc64<FAllocator ,value_type > mybasic_suballoc64 ;

//***************************************************************************
//       C O N S T R U C T O R , D E S T R U C T O R , B I N D
//
//  explicit suballocator64();
//  suballocator64( suballocator64<Allocator> const&) ;
//
//  template<typename U>
//  suballocator64(suballocator64<U> const&) ;
//
//  virtual ~suballocator64() ;
//
//  template<typename U>
//  struct rebind
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : basic_suballoc64
/// @brief constructor of the class
//------------------------------------------------------------------------
explicit suballocator64 ( void ) { };
//------------------------------------------------------------------------
//  function : basic_suballoc64
/// @brief constructor of the class
//------------------------------------------------------------------------
suballocator64 ( const Allocator &Alfa ):mybasic_suballoc64 (Alfa) { };
//------------------------------------------------------------------------
//  function : basic_suballoc64
/// @brief Copy constructor
/// @param [in] Alfa : this parameter is passed to the basic_suballocator
//------------------------------------------------------------------------
suballocator64 ( const suballocator64 &Alfa ):mybasic_suballoc64 (Alfa) { };
//------------------------------------------------------------------------
//  function : basic_suballoc64
/// @brief Copy constructor fron an allocator of other type
/// @param [in] The parameter is not used
//------------------------------------------------------------------------
template<typename U>
suballocator64(suballocator64< U> const&) {};
//------------------------------------------------------------------------
//  function : ~basic_suballoc64
/// @brief Destructor of the class
//------------------------------------------------------------------------
virtual ~suballocator64() { };
//--------------------------------------------------------------------------
//    convert an allocator<T> to allocator<U>
//--------------------------------------------------------------------------
template< typename U>
struct rebind
{   typedef  typename FAllocator::template rebind<U>::other base_other ;
    typedef suballocator64 <base_other> other;
};

//***************************************************************************
//           B O O L E A N    O P E R A T O R S
//
//  bool operator==(suballocator64 const&)
//  bool operator!=(suballocator64 const& )
//
//  template <typename Allocator2>
//  bool operator==(suballocator64<Allocator2> const&)
//
//  template <typename Allocator2 >
//  bool operator!=(suballocator64<Allocator2> const& )
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to the suballocator to compare
/// @return always return true
/// @remarks
//------------------------------------------------------------------------
bool operator==(suballocator64 const&)  {  return true;   };
//------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to the suballocator to compare
/// @return always return false
/// @remarks
//------------------------------------------------------------------------
bool operator!=(suballocator64 const& )  { return false;  };
//------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to the suballocator to compare
/// @return always return true
/// @remarks
//------------------------------------------------------------------------
template <typename Allocator2>
bool operator==(suballocator64<Allocator2> const&) { return true;  };
//------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to the suballocator to compare
/// @return always return false
/// @remarks
//------------------------------------------------------------------------
template <typename Allocator2>
bool operator!=(suballocator64<Allocator2> const& )  { return false; };

//***************************************************************************
};//        E N D     S U B A L L O C A T O R 6 4      C L A S S
//***************************************************************************
//***************************************************************************
};//         E N D    A L L O C   &   C N T R E E    N A M E S P A C E
//***************************************************************************
namespace std
{
template < typename T>
void swap ( countertree::suballocator64 < T > & A ,
            countertree::suballocator64 < T > & B   ){ };
};
#endif
