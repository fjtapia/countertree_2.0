//----------------------------------------------------------------------------
/// @file definitions.hpp
/// @brief This file contains the data and type definitions needed
///        adapted to the specific compiler
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_COMMON_DEFINITIONS_HPP
#define __COUNTERTREE_COMMON_DEFINITIONS_HPP

//#include <stdint>
#include <limits>
#include <ciso646>
#include <malloc.h>

//##########################################################################
//                                                                        ##
//                   V I S U A L  C + +                                   ##
//                                                                        ##
//##########################################################################

#ifdef _MSC_VER
//---------------------------------------------------------------------------
//        __declspec(noalias)
// noalias means that a function call does not modify or reference visible
// global state and only modifies the memory pointed to directly by pointer
// parameters (first-level indirections).
//----------------------------------------------------------------------------
#define NOALIAS __declspec(noalias)
//#define NOALIAS
//----------------------------------------------------------------------------
//   __declspec(restrict)
//Applied to a function declaration or definition that returns a pointer type
//and tells the compiler that the function returns an object that will not be
//aliased with any other pointers.
//---------------------------------------------------------------------------
#define RESTRICT __declspec(restrict)
//#define RESTRICT
//---------------------------------------------------------------------------
//               throw ()
// tells the compiler that the function does not throw any exceptions. It is
// the equivalent to using __declspec(nothrow).
//----------------------------------------------------------------------------
#define NOEXCEPT  _NOEXCEPT

//---------------------------------------------------------------------------
//               constexpr
// tells the compiler that the function always return the same result with
// the same input and can be used in the metaprogramming.
// The compiler generate two copies of the function, one for the compiler in the
// metaprogramming process and other for the program when invoque the function
//----------------------------------------------------------------------------
#define CONSTEXPR constexpr

//---------------------------------------------------------------------------
//               assert
// make an assert, posibiliting the susbtitution by any other format af assert
// like the BOOST_ASSERT
//----------------------------------------------------------------------------
#define ASSERT assert

//##########################################################################
//                                                                        ##
//                      G N U     G C C                                   ##
//                                                                        ##
//##########################################################################

#else
#ifdef __GNUC__
//#include <inttypes.h>
//---------------------------------------------------------------------------
//        __declspec(noalias)
// noalias means that a function call does not modify or reference visible
// global state and only modifies the memory pointed to directly by pointer
// parameters (first-level indirections).
//----------------------------------------------------------------------------
#define NOALIAS __restrict

//----------------------------------------------------------------------------
//   __declspec(restrict)
//Applied to a function declaration or definition that returns a pointer type
//and tells the compiler that the function returns an object that will not be
//aliased with any other pointers.
//---------------------------------------------------------------------------
#define RESTRICT __restrict

//---------------------------------------------------------------------------
//               NOEXCEPT
// tells the compiler that the function does not throw any exceptions. It is
// the equivalent to using __declspec(nothrow).
//----------------------------------------------------------------------------
//#define NOEXCEPT  
#define NOEXCEPT  noexcept


//---------------------------------------------------------------------------
//               constexpr
// tells the compiler that the function always return the same result with
// the same input and can be used in the metaprogramming.
// The compiler generate two copies of the function, one for the compiler in the
// metaprogramming process and other for the program when invoque the function
//----------------------------------------------------------------------------
#define CONSTEXPR constexpr

//---------------------------------------------------------------------------
//               assert
// make an assert, posibiliting the susbtitution by any other format af assert
// like the BOOST_ASSERT
//----------------------------------------------------------------------------
#define ASSERT assert

//##########################################################################
//                                                                        ##
//                      G E N E R I C O                                   ##
//                                                                        ##
//##########################################################################

#else
//---------------------------------------------------------------------------
//        __declspec(noalias)
// noalias means that a function call does not modify or reference visible
// global state and only modifies the memory pointed to directly by pointer
// parameters (first-level indirections).
//----------------------------------------------------------------------------
#define NOALIAS

//----------------------------------------------------------------------------
//   __declspec(restrict)
//Applied to a function declaration or definition that returns a pointer type
//and tells the compiler that the function returns an object that will not be
//aliased with any other pointers.
//---------------------------------------------------------------------------
#define RESTRICT

//---------------------------------------------------------------------------
//               throw ()
// tells the compiler that the function does not throw any exceptions. It is
// the equivalent to using __declspec(nothrow).
//----------------------------------------------------------------------------
//#define NOTHROW  throw ()
#define NOEXCEPT  noexcept

//---------------------------------------------------------------------------
//               constexpr
// tells the compiler that the function always return the same result with
// the same input and can be used in the metaprogramming.
// The compiler generate two copies of the function, one for the compiler in the
// metaprogramming process and other for the program when invoque the function
//----------------------------------------------------------------------------
#define CONSTEXPR constexpr

//---------------------------------------------------------------------------
//               assert
// make an assert, posibiliting the susbtitution by any other format af assert
// like the BOOST_ASSERT
//----------------------------------------------------------------------------
#define ASSERT assert

#endif
#endif

/*
#ifdef _MSC_VER

//------------------------------------------------------------------------//
//                                                                        //
//       //-----------------------------------------------------//        //
//       //         D E F I N I C I O N E S                     //        //
//       //                   D E                               //        //
//       //                 D A T O S                           //        //
//       //-----------------------------------------------------//        //
//                                                                        //
//------------------------------------------------------------------------//

//-------------------------------------------------------------------
//                  T I P O S     E N T E R O S
//-------------------------------------------------------------------
typedef           __int8   int8_t;
typedef unsigned  __int8   uint8_t;

typedef           __int16  int16_t;
typedef unsigned  __int16  uint16_t;

typedef           __int32  int32_t;
typedef unsigned  __int32  uint32_t;

typedef           __int64 int64_t;
typedef unsigned  __int64 uint64_t;

//--------------------------------------------------------------------
//         L I M I T E S      T I P O S     E N T E R O S
//--------------------------------------------------------------------
#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN  (-9223372036854775807LL - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 0xff // 255U
#define UINT16_MAX 0xffff // 65535U
#define UINT32_MAX 0xffffffff  // 4294967295U
#define UINT64_MAX 0xffffffffffffffffULL // 18446744073709551615ULL

#else
//-------------------------------------------------------------------------
// Definiciones de tipos  y limites en Linux
//-------------------------------------------------------------------------
#include <stdint.h>
#endif
*/
#endif
