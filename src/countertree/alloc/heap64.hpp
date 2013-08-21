//----------------------------------------------------------------------------
/// @file heap64.hpp
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
#ifndef __CNTREE_ALLOC_HEAP64_HPP
#define __CNTREE_ALLOC_HEAP64_HPP

#include <boost/countertree/common/algorithms64.hpp>
#include <boost/countertree/common/config.hpp>
#include <cassert>
#include <stdexcept>
#include <string.h>

#if __DEBUG_CNTREE != 0
    #include <iostream>
#endif

namespace c_common = countertree::common ;

namespace countertree
{
namespace alloc
{
//##########################################################################
//                                                                        ##
//             F O R W A R D   D E C L A R A T I O N S                    ##
//                                                                        ##
//##########################################################################
template <typename AllocByte> struct basic_heap64;
template <uint64_t Power2, typename AllocByte> struct heap64;


//##########################################################################
//                                                                        ##
//               C L A S S    N T O T A L W O R D 6 4                     ##
//                 ( M e t a p r o g r a m m i n g )                      ##
//                                                                        ##
//##########################################################################

//----------------------------------------------------------------
/// @class NTOTALWORD64
/// @brief This class return the number of 64 bits words needed for
///        the heap
/// @param [in] NLevel number of levels of the heap
/// @param [in] Power2 Power of two which indicates the number of
///                    bits in this row of the heap
/// @remarks This class is for the metaprogramming calculation of
///          the size of the Data matrix of uint32_t elements for
///          the heap manager
///
//----------------------------------------------------------------
template <uint64_t NLevel, uint64_t Power2 >
struct NTOTALWORD64
{   static uint64_t const Data = NTOTALWORD64< NLevel -1, Power2 -6>::Data +
                                 ( 1ULL << (Power2 -6));
};
template < uint64_t Power2>
struct NTOTALWORD64< 1ULL, Power2>
{   static uint64_t const Data = 1  ;
};

//##########################################################################
//                                                                        ##
//               C L A S S   P R O C R E A T E 6 4                        ##
//               ( M e t a p r o g r a m m i n g )                        ##
//                                                                        ##
//##########################################################################
//----------------------------------------------------------------
/// @class procreate64_cnc
/// @brief This class is designed in order to create elemets of double size
///        than the precedents
/// @param [in] SW Indicate if the size is valid
/// @param [in] Power2 Power of two which indicates the number of
///                    bits in this row of the heap
/// @exception bad_alloc
/// @remarks
///
//----------------------------------------------------------------
template <bool SW ,uint64_t Power2 , typename AllocByte>
struct procreate64 ;

template <uint64_t Power2 ,typename AllocByte>
struct procreate64< true, Power2, AllocByte>
{   //------------------- static assertions --------------------------
    static_assert ( Power2 < 61,"Size too Big");
    typedef typename AllocByte::value_type value_type ;
    static_assert(sizeof(value_type) == 1,"Error AllocByte");

    static basic_heap64<AllocByte> * create_son ( AllocByte &GA)
    {   //--------------------- begin --------------------------
        void *PAux = GA.allocate (sizeof ( heap64<Power2,AllocByte>) );
        if ( PAux == NULL )  throw std::bad_alloc();
        new ((void*)PAux) heap64 <Power2,AllocByte>;
        return ( basic_heap64<AllocByte> *) PAux ;
    };
};

template <uint64_t Power2, typename AllocByte >
struct procreate64< false, Power2, AllocByte>
{   //------------------------------------------------------------------------
    static_assert ( Power2 < 62,"Size too Big");
    typedef typename AllocByte::value_type value_type ;
    static_assert(sizeof(value_type) == 1,"Error AllocByte");

    static basic_heap64<AllocByte> * create_son ( AllocByte &)
    {   //--------------------- begin --------------------------
        return (basic_heap64<AllocByte> *) NULL ;
    };
};

//##########################################################################
//                                                                        ##
//                        S T R U C T                                     ##
//         B A S I C _ H E A P 6 4 < A L L O C B Y T E >                  ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class basic_heap64
/// @param [in] N is the power of 2 which indicates the number
///              of elements
/// @remarks This class is for use the heaps of a pool in a uniform way
///          with the inheritance. This is the interface used by the
///          pool for to manage the heaps
///
//----------------------------------------------------------------
template <typename AllocByte>
struct basic_heap64
{
//***************************************************************************
//     D E F I N I T I O N S    &     S T A T I C _ A S S E R T
//***************************************************************************
//------------------------------------------------------------------------
typedef typename AllocByte::value_type value_type ;
static_assert(sizeof(value_type) == 1,"Error AllocByte");

//***************************************************************************
//                     V A R I A B L E S
//***************************************************************************
uint64_t * Ptr ; // pointer to the last level
uint64_t ** L ; //vector of pointers to the first elements of each level
uint64_t const NElemMax ; // Number of elements controlled in the heap
uint64_t const NLevel ; // Number of levels in the heap
uint64_t Cursor ; // position for to find the next empty element
uint64_t NElem ; // Number of elements allocated in the heap

//***************************************************************************
//           C O N S T R U C T O R ,  D E S T R U C T O R
//
//  basic_heap64 (uint64_t **L1, uint64_t NElemMax1,uint64_t NLevel1);
//  virtual ~basic_heap64 ();
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : basic_heap
/// @brief Constructor of the class
/// @param [in] L1 : vector of pointers to the first elements of each level
/// @param [in] NElemMax1 :Number of elements controlled in the heap
/// @param [in] NLEvel1 : Number of levels in the heap
/// @remarks
//------------------------------------------------------------------------
basic_heap64 (uint64_t **L1, uint64_t NElemMax1,uint64_t NLevel1) NOEXCEPT
              : Ptr(NULL),L(L1), NElemMax( NElemMax1),
                NLevel (NLevel1),Cursor(0),NElem(0){ };

//------------------------------------------------------------------------
//  function :~basic_heap
/// @brief Destructor of the class
/// @remarks
//------------------------------------------------------------------------
virtual ~basic_heap64 () NOEXCEPT {};

//***************************************************************************
//   S I Z E O F ,  C R E A T E _ S O N
//   I S _ E M P T Y , I S _ F U L L , C A P A C I T Y
//
//  virtual uint64_t SIZEOF ()const =0;
//  virtual basic_heap64 * create_son (AllocByte & AB) const =0 ;
//
//  bool     is_full  ( void ) const;
//  bool     is_empty ( void ) const;
//  uint64_t capacity ( void ) const;
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : SIZEOF
/// @brief  return the size in bytes of the heap
/// @remarks
//------------------------------------------------------------------------
virtual uint64_t SIZEOF () const NOEXCEPT =0;

//------------------------------------------------------------------------
//  function : create_son
/// @brief create a heap from the double size than the actual heap
/// @param [in] AB : raw allocator from extract the memory needed for the
///                  new heap
/// @return pointer to the new heap
/// @remarks
//------------------------------------------------------------------------
virtual basic_heap64 * create_son (AllocByte & AB) const =0 ;

//------------------------------------------------------------------------
//  function : is_full
/// @brief Indicate if the heap is full
/// @return true : full false : not full
//------------------------------------------------------------------------
bool is_full ( void ) const NOEXCEPT{   return ( NElem == NElemMax) ; };

//------------------------------------------------------------------------
//  function : is_empty
/// @brief Indicate if the heap is empty
/// @return true : empty false : not empty
//------------------------------------------------------------------------
bool is_empty ( void ) const NOEXCEPT { return ( NElem == 0) ; };

//------------------------------------------------------------------------
//  function : capacity
/// @brief Return the capacity of the heap
/// @return capacity of the heap
/// @remarks
//------------------------------------------------------------------------
uint64_t capacity ( void ) const NOEXCEPT {   return NElemMax ; };

//***************************************************************************
//  R E A D _ B I T , A L L O C A T E , D E A L L O C A T E , C H E C K
//
//  bool        read_bit    ( uint64_t Pos) const;
//  uint64_t    allocate    ( void);
//  void        deallocate  ( uint64_t Pos);
//
//  #if __DEBUG_CNTREE != 0
//      virtual bool check( void )const
//  #endif
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : read_bit
/// @brief  Read a bit of the set
/// @param [in] Pos : Position of the bit to read
/// @return true : 1 false : 0
//------------------------------------------------------------------------
bool read_bit ( uint64_t Pos) const NOEXCEPT
{   //----------------------- begin --------------
    #if __DEBUG_CNTREE != 0
    assert  ( Pos < NElemMax) ;
    #endif
    return ReadBit64 ( Ptr[Pos >>6], Pos & 63  );
};
//------------------------------------------------------------------------
//  function : allocate
/// @brief find the first position free and allocate an element
/// @param [in] IsFull : Indicate if the heap is full after the allocation
/// @return The position of the element allocated. If full return MAX64
//------------------------------------------------------------------------
uint64_t allocate   ( void) NOEXCEPT
{   //------------------------- begin -----------------------------
    if ( is_full() ) return MAX64 ;
    //--------------------------------------------------------------------
    // If the only operations which modify the heap a re allocate and deallocate
    // the cCursor can guarantee what the free positions in the heap are from the
    // Cursor position forward
    //---------------------------------------------------------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Cursor < NElemMax) ;
    #endif
    bool Invalid = false ;
    if ( (Invalid = read_bit(Cursor)) )
    {   uint64_t CursorWord = Cursor >>6 ;
        uint64_t Aux = Ptr[ CursorWord ];
        if (  not (Invalid = (Aux == MAX64)) )
            Cursor = (CursorWord <<6)+ LS1B_64 ( ~Aux);
    };
    uint64_t Level ;
    if ( Invalid )
    {   for ( Cursor = 0, Level = 0 ; Level < NLevel ;++Level)
        {   Cursor=(Cursor<<6)+ LS1B_64(~ L[Level][Cursor]);
        };
    };
    //---------------------------------------------------------------------
    // set to one the bit
    //---------------------------------------------------------------------
    uint64_t N1 = Cursor , N2 = 0 ;
    Level = NLevel;
    uint64_t * PAux = NULL ;
    do
    {   N2 = N1 & 63 ;
        PAux = &(L[--Level][N1>>=6]);
        #if __DEBUG_CNTREE != 0
        assert ( not ReadBit64(*PAux , N2)) ;
        #endif
        SetBit64 ( *PAux, N2);
        #if __DEBUG_CNTREE != 0
        assert ( ReadBit64(*PAux , N2)) ;
        #endif
    } while ( (*PAux == MAX64) and Level != 0) ;
    NElem++;
    return ( Cursor++);
};
//------------------------------------------------------------------------
//  function : deallocate
/// @brief Deallocate an element of the row
/// @param [in] Pos : position of the element to deallocate
//  @return Return if the element was full prior the deallocation
//------------------------------------------------------------------------
void  deallocate ( uint64_t Pos) NOEXCEPT
{   //------------------------ begin -----------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < NElemMax);
    #endif
    uint64_t N1 = Pos , N2 = 0 , Level = NLevel;
    bool SW ;
    do
    {   N2 = N1 &63 ;
        uint64_t & Aux = L[--Level][N1 >>= 6];
        SW = ( Aux == MAX64 );
        #if __DEBUG_CNTREE != 0
        assert ( ReadBit64(Aux , N2)) ;
        #endif
        ResetBit64 ( Aux , N2);
        #if __DEBUG_CNTREE != 0
        assert ( not ReadBit64(Aux , N2)) ;
        #endif
    } while ( SW and Level != 0) ;
    if ( Pos < Cursor) Cursor = Pos ;
    NElem-- ;
};
#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief check all the lements of the heap trying to detect the errors
/// @return true : correct false :error
/// @remarks
//------------------------------------------------------------------------
virtual bool check( void )const { return true ;} ;

#endif

//***************************************************************************
};//              E N D     B A S I C _ H E A P 6 4    C L A S S
//***************************************************************************


//##########################################################################
//                                                                        ##
//                        S T R U C T                                     ##
//        H E A P 6 4  < P O W E R 2 , A L L O C B Y T E >                ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class heap64
/// @param [in] Power2 is the power of 2 which indicates the number
///              of elements
/// @param [in] Allocator : Allocator of elements uint8_t
/// @remarks This class is for the metaprogramming calculation of
///          the size of the Data matrix of uint32_t elements for
///          the heap manager
///
//----------------------------------------------------------------
template <uint64_t Power2, typename AllocByte>
struct heap64: public basic_heap64<AllocByte>
{
//***************************************************************************
//               S T A T I C    V A R I A B L E S
//***************************************************************************

static const uint64_t NLEVEL = ((Power2== 0)?1:((Power2+5)/6) );
static const uint64_t Mask =(Power2==0)? (MAX64<<1):
                            ((Power2%6)==0)?0:(MAX64<< (1ULL<<(Power2 %6)));

static const uint64_t NTotalWord = NTOTALWORD64< NLEVEL,Power2>::Data ;
static_assert ( c_common::n_bits_max >= Power2,"Size too Big");

//***************************************************************************
//               P U B L I C     V A R I A B L E S
//***************************************************************************
using basic_heap64 <AllocByte>::Cursor;
using basic_heap64 <AllocByte>::Ptr;
uint64_t * L1[ NLEVEL];
uint64_t P1 [ NTotalWord];

//***************************************************************************
//                P U B L I C    F U N C T I O N S
//
//  heap64 ( void )
//  virtual ~heap64 ()
//
//  uint64_t SIZEOF (  )
//  void clear ( void )
//
//  basic_heap64<AllocByte> * create_son ( AllocByte  & GA  ) const
//
// #if __DEBUG_CNTREE != 0
//     bool check ( void ) const
// #endif
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : heap
/// @brief class constructor
/// @param [in]
/// @return
/// @remarks
//------------------------------------------------------------------------
heap64 ( void ) NOEXCEPT: basic_heap64<AllocByte> ( L1,(1ULL <<Power2), NLEVEL)
{   //---------------------------- begin -------------------
    L1[0] = P1 ;
    if ( NLEVEL > 1)
    {   L1[1] = P1 + 1 ;
        uint64_t NW1 = ( 1ULL <<( Power2 - 6 * ( NLEVEL -1)) );
        for ( uint64_t i = 2 ; i < NLEVEL ; i++)
        {   L1[i] = L1[i-1]+ NW1 ;
            NW1 = NW1 <<6 ;
        };
    }
    ::memset ( P1, 0 , NTotalWord << 3);
    P1[0] = Mask ;
    Ptr = L1[ NLEVEL -1];
};
//------------------------------------------------------------------------
//  function : ~heap64
/// @brief virtual destructor of the class
/// @remarks
//------------------------------------------------------------------------
~heap64 ()NOEXCEPT{   };

//------------------------------------------------------------------------
//  function : SIZEOF
/// @brief return the size of the data structure in bytes
/// @remarks
//------------------------------------------------------------------------
uint64_t SIZEOF (  ) const NOEXCEPT
{   //----------------------------------- begin ----------------
    return sizeof ( *this);
};

//------------------------------------------------------------------------
//  function : clear
/// @brief clear all the data structure
/// @remarks
//------------------------------------------------------------------------
void clear ( void ) NOEXCEPT
{   //----------------------------------- begin ----------------
    ::memset ( P1, 0 , NTotalWord << 3);
    P1[0] = Mask ;
    Cursor =0 ;
};

//------------------------------------------------------------------------
//  function : create_son
/// @brief create a row which template parameter Power2 is plus 1 the actual
/// @return pointer to the new row
/// @remarks
//------------------------------------------------------------------------
basic_heap64<AllocByte> * create_son ( AllocByte & GA  ) const
{   //---------------------- begin --------------------------------------
    //return procreate64 <((Power2+1)<61),Power2+1,AllocByte>::create_son (GA) ;
    return procreate64 <((Power2+1)< (n_bits_max -2 )),Power2+1,AllocByte>::create_son (GA) ;
};
//***************************************************************************
//        F U N C T I O N S   F O R    D E B U G
//***************************************************************************

#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief Check if the data structure is OK
/// @return true : OK false : error
/// @remarks
//------------------------------------------------------------------------
bool check ( void ) const NOEXCEPT;
#endif

//***************************************************************************
};//              E N D     H E A P 6 4     C L A S S
//***************************************************************************


//##########################################################################
//                                                                        ##
//              F U N C I O N E S   N O N    I N L I N E                  ##
//                                                                        ##
//##########################################################################

#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief Check if the data structure is OK
/// @return true : OK false : error
/// @remarks
//------------------------------------------------------------------------
template <uint64_t Power2, typename AllocByte>
bool heap64<Power2,AllocByte>::check ( void ) const NOEXCEPT
{   //------------------------- begin ------------------
    bool SW = true ;
    uint64_t Level , i ;

    for ( Level = 1 ; SW and Level < NLEVEL ; Level++)
    {   uint64_t NMaxLevel = ( 1 << (Power2 - 6 * (NLEVEL - Level)));
        for ( i =0 ; SW and i < NMaxLevel ; i++)
        {   SW =((L1[Level][i]== MAX64)==(ReadBit64(L1[Level-1][i >>6],i&63)));
        };
    }
    if ( not SW)
    {   std::cout<<"Error  Level :"<<Level-1<<"  Element :"<<i-1<<std::endl;
    };
    return SW ;
};

//------------------------------------------------------------------------
//  function : operator <<
/// @brief print operator
/// @param [in]
/// @return
/// @remarks
//------------------------------------------------------------------------

template <uint64_t Power2, typename AllocByte>
std::ostream & operator<< ( std::ostream & S , const heap64<Power2,AllocByte> & H )
{   //---------------------------- Begin ------------------------------
    S<<"---------------------------------------------------------------\n";
    S<<"Power2 "<< Power2 <<"  NLevel :"<<H.NLevel<<std::endl;
    S<<"NBitMax :"<< std::hex<<H.NBitMax<<" NTotalWord :"<<H.NTotalWord ;
    S<<" Mask :"<< std::hex<<H.Mask<<std::endl ;
    S<<"[ 0 ] "<<H.L[0][0]<<std::endl;
    for ( uint64_t Level = 1 ; Level < H.NLevel ; Level++)
    {   S<< std::dec<<"[ "<<Level<<" ] ";
        uint64_t NMaxLevel = ( 1 << (Power2 - 6 * (H.NLevel - Level)));
        for ( uint64_t i =0 ;  i < NMaxLevel ; i++)
        {   S<< std::hex<<H.L[Level][i]<<" " ;
        };
        S<< std::dec<<std::endl;
    };
    S<<"---------------------------------------------------------------\n";
    return S ;
};
#endif

//***************************************************************************
};//              E N D    A L L O C     N A M E S P A C E
//
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
