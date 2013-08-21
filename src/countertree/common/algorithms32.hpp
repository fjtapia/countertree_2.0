//----------------------------------------------------------------------------
/// @file algorithms32.hpp
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
#ifndef __CNTREE_ALLOC_ALGORITHMS32_HPP
#define __CNTREE_ALLOC_ALGORITHMS32_HPP

#include <boost/countertree/common/definitions.hpp>
#include <boost/countertree/common/config.hpp>
#include <cassert>

namespace countertree
{
namespace common
{

//##########################################################################
//                                                                        ##
//                A L G O R I T H M S     3 2  B i t s                    ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
//  function : ResetBit32
/// @brief Set to zero the bit Pos in a uint32_t element N
/// @param [in] N : word where set the bit to zero
/// @param [in] Pos : position of the bit in  set to zero
//---------------------------------------------------------------------------
inline void ResetBit32 ( uint32_t &N , uint32_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 32 ) ;
    #endif
    ( N &= (~(1U<<Pos)));
};
//---------------------------------------------------------------------------
//  function : SetBit32
/// @brief Set to one the bit Pos in a uint32_t element N
/// @param [in] N : word where set  the bit to one
/// @param [in] Pos : position of the bit in  set to one
//---------------------------------------------------------------------------
inline void SetBit32 ( uint32_t &N , uint32_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 32 ) ;
    #endif
    ( N |= (1U<<Pos));
};
//---------------------------------------------------------------------------
//  function :ReadBit32
/// @brief Return the content of the bit Pos in the uint32_t element N
/// @param [in] N : uint32_t element from read the birt
/// @param [in] Pos : Position of the bit readed
/// @return Value of the bit (true :1 , false :0)
//---------------------------------------------------------------------------
inline bool ReadBit32 ( uint32_t N , uint32_t Pos ) NOEXCEPT
{   //------------------ begin --------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < 32 ) ;
    #endif
    return (  (N & (1U<<Pos )) != 0 );
};

static const int DeBruijn_32[32] =
{
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};
//---------------------------------------------------------------------------
//  function :bitScanForward32
/// @author Martin Läuter(1997),Charles E.Leiserson,Harald Prokop,Keith H.Randall
/// @brief return the least significant one bit
/// @param [in]V1 bitboard to scan
/// @return index (0..31) of least significant one bit
/// @remarks "Using de Bruijn Sequences to Index a 1 in a Computer Word"
//---------------------------------------------------------------------------
inline int LS1B_32(uint32_t V) NOEXCEPT
{   //------------------------- begin --------------------------------
    #if __DEBUG_CNTREE != 0
    assert (V != 0);
    #endif
    return DeBruijn_32[((uint32_t)((V & ((~V)+1)) * 0x077CB531U)) >> 27];
};
//---------------------------------------------------------------------------
//  function : Mask32
/// @brief Calculate the mask for a number of bits
/// @param [in] NBits : Number to examine
/// @exception none
/// @return Mask
/// @remarks
//---------------------------------------------------------------------------
inline uint32_t Mask32 ( uint32_t NBits) NOEXCEPT
{   //--------------------------- begin ---------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 32 );
    #endif
    return ((1U<<NBits)-1);
};

//---------------------------------------------------------------------------
//  function : MS1B_32
/// @brief Obtain the position of the most significant one in N
/// @param [in] N : Number to examine
/// @exception none
/// @return Position of the first one
/// @remarks
//---------------------------------------------------------------------------
template <uint32_t NBits = 16 >
inline uint32_t MS1B_32 ( uint32_t N , uint32_t Pos =0) NOEXCEPT
{   //------------------ begin ----------------------------
    static_assert ( NBits < 32, " NBits too big ");
    return (((N>>Pos)& (~Mask32(NBits)))== 0 )?
              MS1B_32<(NBits>>1)>(N,Pos):
              MS1B_32<(NBits>>1)>(N,Pos+NBits);
};
template<>
inline uint32_t MS1B_32<0> ( uint32_t  , uint32_t Pos) NOEXCEPT
{   return Pos ;
};
//---------------------------------------------------------------------------
//  function : AlignSize32
/// @brief Return the aligned size of the size received as parameter
/// @param [in] NBits :  2^NBits Is the size of the alignment
/// @param [in] N : size without alignment
/// @exception none
/// @return New size alligned
//---------------------------------------------------------------------------
inline uint32_t AlignSize32 ( uint32_t N, uint32_t NBits ) NOEXCEPT
{   //--------------------------- begin ---------------------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 32);
    #endif
    //return (N == 0)?0:(N<=(1U<<NBits))?(1<<NBits):((N+Mask32(NBits))&(~Mask32(NBits)));
    return (N<=(1U<<NBits))?(1<<NBits):((N+Mask32(NBits))&(~Mask32(NBits)));
};
//---------------------------------------------------------------------------
//  function : BitsAlign32
/// @brief return the number of bits of the alignment of a block
/// @param [in] NBits : Number of bits of the element
/// @exception none
/// @return The block alignmen is 2 ^ result
//---------------------------------------------------------------------------
inline uint32_t BitsAlign32 ( uint32_t NBits ) NOEXCEPT
{   //-------------------------- begin -----------------------------
    #if __DEBUG_CNTREE != 0
    assert ( NBits < 32);
    #endif
    return (NBits <5)?NBits:((NBits&3) >1 or NBits < 8)?NBits-(NBits&3):(NBits-(NBits&3)-4);
};
//---------------------------------------------------------------------------
//  function : SizeAligned_32
/// @brief Return the aligned size of the size received as parameter
/// @param [in] N : size without alignment
/// @exception none
/// @return New size alligned
//---------------------------------------------------------------------------
inline uint32_t SizeAligned32 ( uint32_t  N) NOEXCEPT
{   return AlignSize32 (N , BitsAlign32 (MS1B_32 (N)));
};
//------------------------------------------------------------------------
};//              E N D    C O M M O N      N A M E S P A C E
//
};//              E N D   C O U N T E R T R E E    N A M E S P A C E
//-------------------------------------------------------------------------
#endif
