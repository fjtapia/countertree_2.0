//----------------------------------------------------------------------------
/// @file algorithms64.hpp
/// @brief This file contains the description of the classes heap_fixed_node
///        and heap_node
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_COMMON_ALGORITHMS64_HPP
#define __COUNTERTREE_COMMON_ALGORITHMS64_HPP

#include <boost/countertree/common/definitions.hpp>
#include <boost/countertree/common/config.hpp>
#include <cassert>


namespace countertree
{
namespace common
{
//##########################################################################
//                                                                        ##
//                A L G O R I T H M S     6 4  B i t s                    ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
//  function : ResetBit64
/// @brief Set to zero the bit Pos in a uint64_t element N
/// @param [in] N : word where set the bit to zero
/// @param [in] Pos : position of the bit  set to zero
//---------------------------------------------------------------------------
inline void ResetBit64 ( uint64_t &N , uint64_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 64 ) ;
    #endif
    ( N &= (~(1ULL<<Pos)));
};
//---------------------------------------------------------------------------
//  function : SetBit64
/// @brief Set to one the bit Pos in a uint64_t element N
/// @param [in] N : word where set  the bit to one
/// @param [in] Pos : position of the bit in  set to one
//---------------------------------------------------------------------------
inline void SetBit64 ( uint64_t &N , uint64_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 64 ) ;
    #endif
    ( N |= (1ULL<<Pos));
};
//---------------------------------------------------------------------------
//  function : ReadBit64
/// @brief Return the content of the bit Pos in the uint64_t element N
/// @param [in] N : uint64_t element from read the bit
/// @param [in] Pos : Position of the bit readed
/// @return Value of the bit (true :1 , false :0)
//---------------------------------------------------------------------------
inline bool ReadBit64 ( uint64_t N , uint64_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 64 ) ;
    #endif
    return (  (N & (1ULL<<Pos )) != 0 );
};
static  const int DeBruijn_64[64] =
{   63,  0, 58,  1, 59, 47, 53,  2,
    60, 39, 48, 27, 54, 33, 42,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5
};
//---------------------------------------------------------------------------
//  function :bitScanForward64
/// @author Martin Läuter(1997),Charles E.Leiserson,Harald Prokop,Keith H.Randall
/// @brief return the least significant one bit
/// @param [in] bb bitboard to scan
/// @return index (0..63) of least significant one bit
/// @remarks "Using de Bruijn Sequences to Index a 1 in a Computer Word"
//---------------------------------------------------------------------------
inline int LS1B_64(uint64_t bb) NOEXCEPT
{   //------------------------- begin --------------------------------
    #if __DEBUG_CNTREE != 0
    assert (bb != 0);
    #endif
    return DeBruijn_64[((bb & ((~bb)+1)) * 0x07EDD5E59A4E28C2ULL) >> 58];
};
//---------------------------------------------------------------------------
//  function : Mask64
/// @brief Calculate the mask for a number of bits
/// @param [in] NBits : Number to examine
/// @exception none
/// @return Mask
/// @remarks
//---------------------------------------------------------------------------
inline uint64_t Mask64 ( uint64_t NBits) NOEXCEPT
{   //------------------------------- begin -------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 64) ;
    #endif
    return ((1ULL<<NBits)-1);
};

//---------------------------------------------------------------------------
//  function : MS1B_64
/// @brief Obtain the position of the most significant one in N
/// @param [in] N : Number to examine
/// @exception none
/// @return Position of the first one
//---------------------------------------------------------------------------
template <uint64_t NBits = 16 >
inline uint64_t MS1B_64 ( uint64_t N , uint64_t Pos =0) NOEXCEPT
{   //------------------ begin ----------------------------
    static_assert ( NBits < 64, " NBits too big ");
    return (((N>>Pos)& (~Mask64(NBits)))== 0 )?
              MS1B_64<(NBits>>1)>(N,Pos):
              MS1B_64<(NBits>>1)>(N,Pos+NBits);
};
template<>
inline uint64_t MS1B_64<0> ( uint64_t  , uint64_t Pos) NOEXCEPT
{   return Pos ;
};
//---------------------------------------------------------------------------
//  function : AlignSize64
/// @brief Return the aligned size of the size received as parameter
/// @param [in] NBits :  2^NBits Is the size of the alignment
/// @param [in] N : size without alignment
/// @exception none
/// @return New size alligned
//---------------------------------------------------------------------------
inline uint64_t AlignSize64 ( uint64_t N, uint64_t NBits ) NOEXCEPT
{   //--------------------------- begin ---------------------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 64);
    #endif
    //return (N == 0)?0:(N<=(1ULL<<NBits))?(1ULL<<NBits):((N+Mask64(NBits))&(~Mask64(NBits)));
    return (N<=(1ULL<<NBits))?(1ULL<<NBits):((N+Mask64(NBits))&(~Mask64(NBits)));
};
//---------------------------------------------------------------------------
//  function : BitsAlign64
/// @brief return the number of bits of the alignment of a block
/// @param [in] NBits : Number of bits of the element
/// @exception none
/// @return The block alignmen is 2 ^ result
//---------------------------------------------------------------------------
inline uint64_t BitsAlign64 ( uint64_t NBits ) NOEXCEPT
{   //-------------------------- begin -----------------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 64);
    #endif
    return (NBits <5)?NBits:((NBits&3) > 1 or NBits < 8)?NBits-(NBits&3):(NBits-(NBits&3)-4);
};
//---------------------------------------------------------------------------
//  function : SizeAligned_64
/// @brief Return the aligned size of the size received as parameter
/// @param [in] N : size without alignment
/// @exception none
/// @return New size alligned
//---------------------------------------------------------------------------
inline uint64_t SizeAligned64 ( uint64_t  N) NOEXCEPT
{   return AlignSize64 (N , BitsAlign64 (MS1B_64 (N)));
};
//---------------------------------------------------------------------------
}; };//  E N D    C O M M O N   &  C O U N T E R T R E E   N A M E S P A C E
//----------------------------------------------------------------------------
#endif
