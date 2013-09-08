//----------------------------------------------------------------------------
/// @file config.hpp
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
#ifndef __COUNTERTREE_COMMON_CONFIG_HPP
#define __COUNTERTREE_COMMON_CONFIG_HPP

#include <boost/config.hpp>
#include <cstdlib>
//#include <boost/thread.hpp>
//#define BOOST_LIB_NAME  boost_thread
#include <limits>
//#include <stdint.h>
#include <boost/cstdint.hpp>
#include <ciso646>
#include <cassert>

//------------------------------------------------------------------
// if __DEBUG_CNTREE is defined , the compilation is done checking all
// the parameters of  every functions, and lost around 20% of speed
// This must be the first line of code in the program
// You have 2 levels of debug
// 1 - Checking  the parameters of  the functions, and if error
//     raise an exception ( default )
// 0 - No debug
//-------------------------------------------------------------------
#ifndef __DEBUG_CNTREE
#define __DEBUG_CNTREE 0
#endif

//------------------------------------------------------------------
// if __CNTREE_MULTITHREAD is defined , the compilation is done with
// the spinlock odf pthread and lost around une half of speed
// This prior to any include  in the program
// You have 2 levels of debug
// 1 - Compile with Pthreads
// 0 - No debug ( default )
//-------------------------------------------------------------------
#ifndef __CNTREE_MULTITHREAD
#define __CNTREE_MULTITHREAD 0
#endif

#if !defined ( BOOST_HAS_THREADS) && __CNTREE_MULTITHREAD != 0
#   undef  __CNTREE_MULTITHREAD
#   define __CNTREE_MULTITHREAD 0
#endif

#if __CNTREE_MULTITHREAD != 0
/*
#   if defined (BOOST_HAS_PTHREADS )
#       include <pthread.h>
#       include <boost/cntree/alloc/spinlock.hpp>
#       define CNTREE_MUTEX cntree::alloc::spinlock
#   else
*/
#include <boost/thread.hpp>
#define BOOST_LIB_NAME  boost_thread
#       include <boost/thread.hpp>
#       include <boost/thread/thread.hpp>
#       include <boost/thread/mutex.hpp>
#       define CNTREE_MUTEX boost::mutex
//#   endif
# endif
namespace countertree
{
namespace common
{

//-----------------------------------------------------------------
// Public data definitions
//-----------------------------------------------------------------
const unsigned NByte = sizeof(size_t) ;
//----------------------------------------------------------
//    32 bits compiler
//----------------------------------------------------------
template <unsigned NByte >
struct Conf
{   //--------------- Type definition--------------
    typedef uint32_t size_type;
    typedef int32_t  difference_type ;
    typedef uint32_t bitfield_t ;
    static const uint32_t  n_bits_number = 31 ;
    static const uint32_t  n_bits_max = 31 ;
    static const uint32_t  MAX = 0xFFFFFFFFU ;
    //enum { n_bits_number = 31 };
};
//----------------------------------------------------------
//    64 bits compiler
//----------------------------------------------------------
template < >
struct Conf<8>
{   //------Type definition -------------
    typedef uint64_t size_type;
    typedef int64_t  difference_type;
    typedef uint64_t bitfield_t ;
    //enum{  n_bits_number = 63 };
    static const uint32_t n_bits_number = 63;
//#if defined (BOOST_MSVC)
#if defined (_MSC_VER)
    static const uint32_t n_bits_max = 31;
#else
    static const uint32_t n_bits_max = 63;
#endif
    static const uint64_t MAX = 0xFFFFFFFFFFFFFFFFULL ;
};
//static const uint64_t MAX64 = std::numeric_limits<uint64_t>::max() ;
//static const uint32_t MAX32 = std::numeric_limits<uint32_t>::max() ;
static const uint64_t MAX64 = Conf<8>::MAX ;
static const uint32_t MAX32 = Conf<4>::MAX ;

typedef Conf<NByte>::size_type       size_type ;
typedef Conf<NByte>::difference_type difference_type ;

typedef Conf<NByte>::size_type       unsigned_type ;
typedef Conf<NByte>::difference_type signed_type ;
static const uint32_t n_bits_max = Conf<NByte>::n_bits_max ;

#if RAND_MAX < 65536
#define RANDOM ( rand() * rand() + rand() + rand() )
#else
#define RANDOM ( rand() )
#endif

}; //------------ End namespace common ------------------------------------
}; //-------------------- End namespace cntree ----------------------------
#endif

