//----------------------------------------------------------------------------
/// @file myallocator.hpp
/// @brief : concurrent allocator
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_COMMON_ALLOCATOR_CNC_HPP
#define __COUNTERTREE_COMMON_ALLOCATOR_CNC_HPP

#include  <boost/countertree/common/config.hpp>
#include  <boost/countertree/common/definitions.hpp>
#include  <boost/countertree/common/spinlock.hpp>
#include  <boost/countertree/common/singleton.hpp>
#include <new>
#include <mutex>
#include <stdexcept>

namespace c_common = countertree::common ;

namespace countertree
{
using  c_common::spinlock;
//##########################################################################
//                                                                        ##
//                          C L A S S                                     ##
//                                                                        ##
//                     A L L O C A T O R                                  ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
/// @class myallocator
/// @brief : Concurrent allocator
//---------------------------------------------------------------------------
template<typename T>
class myallocator
{

//***************************************************************************
//      P R I V A T E    D E F I N I T I O N S  &  V A R I A B L E S
//***************************************************************************
spinlock spl ;
public :

//***************************************************************************
//                 P U B L I C    D E F I N I T I O N S
//***************************************************************************
typedef       T	    value_type; //Element type
typedef       T*	pointer; //Pointer to element
typedef const T*	const_pointer; //Constant pointer to element
typedef       T&	reference; //Reference to element
typedef const T&    const_reference; //Constant reference to element


typedef c_common::size_type		    size_type; //Quantities of elements
typedef c_common::difference_type    difference_type ; //Difference between two pointers
static uint32_t const SizeElem = sizeof (value_type );


//***************************************************************************
// REBIND  STRUCTURE (convert an allocator<T> to allocator<U> )
//
//  template<typename U>  struct rebind
//***************************************************************************
template <class U>
struct rebind { typedef myallocator<U> other ; };


//***************************************************************************
//  C O N S T R U C T O R S , D E S T R U C T O R S , R E B I N D
//
//  explicit myallocator() ;
//  myallocator( myallocator<Allocator> const&) ;
//
//  template<typename U> myallocator(myallocator<U> const&) ;
//
//  virtual ~myallocator() ;
//***************************************************************************
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief constructor of the class
//---------------------------------------------------------------------------
explicit myallocator()NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief Copy constructor
/// @param [in] The parameter is not used
//---------------------------------------------------------------------------
myallocator( const myallocator & ) NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief Copy constructor fron an allocator of other type
/// @param [in] The parameter is not used
//---------------------------------------------------------------------------
template<typename U>
myallocator (const U & )NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : ~myallocator
/// @brief Destructor of the class
//---------------------------------------------------------------------------
virtual ~myallocator ( )
{
};
//***************************************************************************
//           B O O L E A N    O P E R A T O R S
//
//  bool operator==(myallocator const&) ;
//  bool operator!=(myallocator const& ) ;
//
//  template <typename Allocator2>
//  bool operator==(myallocator<Allocator2> const&)
//
//  template <typename Allocator2>
//  bool operator!=(myallocator<Allocator2> const& )
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to compare
/// @return always return true
//---------------------------------------------------------------------------
bool operator==(myallocator const&) NOEXCEPT
{   return true;
};
//---------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to  compare
/// @return always return false
/// @remarks
//---------------------------------------------------------------------------
bool operator!=(myallocator const& ) NOEXCEPT
{   return false;
};
//---------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to compare
/// @return always return true
/// @remarks
//---------------------------------------------------------------------------
template <typename Allocator2>
bool operator==(myallocator<Allocator2> const&) NOEXCEPT
{   return true;
};

//---------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to compare
/// @return always return false
//---------------------------------------------------------------------------
template <typename Allocator2>
bool operator!=(myallocator<Allocator2> const& )NOEXCEPT
{   return false;
};
//***************************************************************************
//     A D D R E S S     A N D    M A X _ S I Z E
//
//  pointer       address ( reference r);
//  const_pointer address ( const_reference r);
//
//  size_type max_size() const;
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : address
/// @brief provide the address of a reference to an object
/// @param [in] r : reference
/// @return Address of the reference
//---------------------------------------------------------------------------
pointer address(reference r) NOEXCEPT
{   return & r;
};
//---------------------------------------------------------------------------
//  function : address
/// @brief provide the address of a const_reference to an object
/// @param [in] r : reference
/// @return Address of the const_reference
//---------------------------------------------------------------------------
const_pointer address(const_reference r)NOEXCEPT
{   return &r;
};

//---------------------------------------------------------------------------
//  function : max_size
/// @brief Maximun size of memory for to allocate
/// @return maximun size of memory
/// @remarks
//---------------------------------------------------------------------------
size_type max_size() const NOEXCEPT
{   return (std::numeric_limits<size_type>::max)() / SizeElem;
};

//***************************************************************************
//    A L L O C A T E , D E A L L O C A T E
//
//  pointer allocate  ( size_type cnt, const_pointer Alfa = NULL);
//  void    deallocate( pointer p, size_type n= 1 );
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate a block of memory
/// @param [in] cnt : number of objects to allocate
/// @param [in] pointer unused
/// @exception : bad_alloc
/// @return pointer to the object allocated
//---------------------------------------------------------------------------
pointer allocate(size_type cnt, const_pointer = NULL)
{   std::unique_lock <spinlock> UL ( spl);
    return  static_cast <pointer> ( ::operator new ( SizeElem * cnt)) ;
};
//---------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate a block of memory
/// @param [in] p : pointer to deallocate
/// @param [in] n : number of objects to deallocate
/// @exception  : bad_alloc
/// @return
//---------------------------------------------------------------------------
void deallocate(pointer p, size_type  n = 1 )
{   std::unique_lock <spinlock> UL ( spl);
    ::operator delete (p) ;
};

//***************************************************************************
//    C O N S T R U C T ,  D E S T R O Y
//
//   void construct(pointer p, const value_type & t);
//   void destroy(pointer p);
//
//***************************************************************************

//---------------------------------------------------------------------------
//  function : construct
/// @brief Construct a new object in the memory pointed by p
/// @param [in] p : pointer to the memory for to construct the object
/// @param [in] args : list of parameters used in the copy constructor
/// @return
//---------------------------------------------------------------------------
template< typename U, typename... Args >
void construct( U * p, Args&&... args ) NOEXCEPT
{   assert ( p != NULL);
    ::new ((void*)p) U ( std::forward <Args>(args)...);
};
//---------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the object without freeing the memory
/// @param [in] p : pointer p to the object to destroy
/// @return
//---------------------------------------------------------------------------
void destroy(pointer p) NOEXCEPT
{   assert ( p != NULL );
    ((T*)p)->~T();
};
//---------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the object without freeing the memory
/// @param [in] p : pointer p to the object to destroy
/// @return
//---------------------------------------------------------------------------
template< class U >
void destroy( U* p ) NOEXCEPT
{   std::unique_lock <spinlock> UL ( spl);
    p->~U() ;
};
//------------------------------------------------------------------------
};//        E N D     A L L O C A T O R _ C N C       C L A S S
//------------------------------------------------------------------------

//##########################################################################
//                                                                        ##
//                          C L A S S                                     ##
//                                                                        ##
//              A L L O C A T O R _ C N C < V O I D >                     ##
//                                                                        ##
//                                                                        ##
//##########################################################################
//--------------------------------------------------------------------------
/// @class myallocator
/// @brief : Concurrent allocator
///
/// @remarks This class is an allocator with a incremental pool
///          of alogaritmic number of elements
//--------------------------------------------------------------------------
template< >
class myallocator <void>
{
//***************************************************************************
//      P R I V A T E    D E F I N I T I O N S  &  V A R I A B L E S
//***************************************************************************
public :
//***************************************************************************
//                 P U B L I C    D E F I N I T I O N S
//***************************************************************************
typedef       void	    value_type; //Element type

typedef c_common::size_type		    size_type; //Quantities of elements
typedef c_common::difference_type    difference_type ; //Difference between two pointers
static uint32_t const SizeElem =0;


//***************************************************************************
//    R E B I N D    S T R U C T U R E
//    (  convert an allocator<T> to allocator<U> )
//
//  template<typename U> struct rebind
//***************************************************************************
template <class U>
struct rebind {   typedef myallocator<U> other ; };


//***************************************************************************
//  C O N S T R U C T O R S , D E S T R U C T O R S , R E B I N D
//
//  explicit myallocator() ;
//  myallocator( myallocator<Allocator> const&) ;
//
//  template<typename U>
//  myallocator(myallocator<U> const&) ;
//
//  virtual ~myallocator() ;
//
//  template<typename U> struct rebind
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief constructor of the class
//---------------------------------------------------------------------------
explicit myallocator() NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief Copy constructor
/// @param [in] The parameter is not used
//---------------------------------------------------------------------------
myallocator( myallocator const& ) NOEXCEPT { };
//---------------------------------------------------------------------------
//  function : myallocator
/// @brief Copy constructor fron an allocator of other type
/// @param [in] The parameter is not used
//---------------------------------------------------------------------------
template<typename U>
myallocator(myallocator<U> const& ) NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : ~myallocator
/// @brief Destructor of the class
//---------------------------------------------------------------------------
virtual ~myallocator() NOEXCEPT { };


//***************************************************************************
//           B O O L E A N    O P E R A T O R S
//
//  bool operator==(myallocator const&) ;
//  bool operator!=(myallocator const& ) ;
//
//  template <typename Allocator2>
//  bool operator==(myallocator<Allocator2> const&)
//
//  template <typename Allocator2>
//  bool operator!=(myallocator<Allocator2> const& )
//
//***************************************************************************

//---------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to the suballocator to compare
/// @return always return true
//---------------------------------------------------------------------------
bool operator==(myallocator const&) NOEXCEPT
{   return true;
};

//---------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to the suballocator to compare
/// @return always return false
//---------------------------------------------------------------------------
bool operator!=(myallocator const& ) NOEXCEPT
{   return false;
};

//---------------------------------------------------------------------------
//  function : operator==
/// @brief equality operator
/// @param [in] reference to the suballocator to compare
/// @return always return true
//---------------------------------------------------------------------------
template <typename Allocator2>
bool operator==(myallocator<Allocator2> const&)
{   return true;
};

//---------------------------------------------------------------------------
//  function : operator !=
/// @brief inequality operator
/// @param [in]reference to the suballocator to compare
/// @return always return false
//---------------------------------------------------------------------------
template <typename Allocator2>
bool operator!=(myallocator<Allocator2> const& ) NOEXCEPT
{   return false;
};

//------------------------------------------------------------------------
//  function : max_size
/// @brief Maximun size of memory for to allocate
/// @return maximun size of memory
/// @remarks
//------------------------------------------------------------------------
size_type max_size() const NOEXCEPT
{   return (std::numeric_limits<size_type>::max)() ;
};

//------------------------------------------------------------------------
};//     E N D    M Y A L L O C A T O R  < V O I D >  C L A S S
//------------------------------------------------------------------------


//------------------------------------------------------------------------
};//              E N D    C O U N T E R T R E E    N A M E S P A C E
///------------------------------------------------------------------------
namespace std
{
template < typename T>
void swap ( countertree::myallocator < T > & A ,
            countertree::myallocator < T > & B   ){ };
};

//---------------------------------------------------------------------------
//  S E L E C T I O N  O F   T H E   C N T R E E _ A L L O C A T O R
//---------------------------------------------------------------------------
#ifndef __MULTITHREAD
#define __MULTITHREAD 1
#endif

#ifdef _MSC_VER
    #if __MULTITHREAD  > 0
        #define cntree_allocator std::allocator
    #else
        #define cntree_allocator std::allocator
    #endif
#else
    #define cntree_allocator std::allocator
#endif

#endif
