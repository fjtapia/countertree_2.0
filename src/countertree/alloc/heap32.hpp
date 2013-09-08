//----------------------------------------------------------------------------
/// @file heap32.hpp
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
#ifndef __CNTREE_ALLOC_HEAP32_HPP
#define __CNTREE_ALLOC_HEAP32_HPP

#include <boost/countertree/common/algorithms32.hpp>
#include <cassert>
#include <stdexcept>
#include <string.h>
#if __DEBUG_CNTREE != 0
    #include <iostream>
#endif

namespace countertree
{
namespace alloc
{
using namespace countertree::common ;

//***************************************************************************
//           F O R W A R D   D E C L A R A T I O N S
//***************************************************************************
template <typename AllocByte> struct basic_heap32;
template <uint32_t Power2, typename AllocByte> struct heap32;


//##########################################################################
//                                                                        ##
//             C L A S S    N T O T A L W O R D 3 2                       ##
//               ( M e t a p r o g r a m m i n g )                        ##
//                                                                        ##
//##########################################################################

//----------------------------------------------------------------
/// @class NTOTALWORD32
/// @brief This class return the number of 32 bits words needed for
///        the heap
/// @param [in] NLevel number of levels of the heap
/// @param [in] Power2 Power of two which indicates the number of
///                    bits in this row of the heap
/// @remarks This class is for the metaprogramming calculation of
///          the size of the Data matrix of uint32_t elements for
///          the heap manager
///
//----------------------------------------------------------------
template <uint32_t NLevel, uint32_t Power2 >
struct NTOTALWORD32
{   static uint32_t const Data = NTOTALWORD32< NLevel -1, Power2 -5>::Data +
                                 ( 1U << (Power2 -5));
};
template < uint32_t Power2>
struct NTOTALWORD32< 1, Power2>
{   static uint32_t const Data = 1  ;
};

//##########################################################################
//                                                                        ##
//             C L A S S   P R O C R E A T E 3 2                          ##
//             ( M e t a p r o g r a m m i n g )                          ##
//                                                                        ##
//##########################################################################
//----------------------------------------------------------------
/// @class procreate32
/// @brief This class is designed in order to create elemets of double size
///        than the precedents
/// @param [in] SW Indicate if the size is valid
/// @param [in] Power2 Power of two which indicates the number of
///                    bits in this row of the heap
/// @exception bad_alloc when allocate/deallocate memory
/// @remarks
///
//----------------------------------------------------------------
template <bool SW ,uint32_t Power2, typename AllocByte>
struct procreate32 ;


template <uint32_t Power2 ,typename AllocByte>
struct procreate32< true, Power2, AllocByte>
{   //------------------- static assertions --------------------------
    static_assert ( Power2 < 31,"Size too Big");
    typedef typename AllocByte::value_type value_type ;
    static_assert(sizeof(value_type) == 1,"Error AllocByte");

    //------------------------ FUNCTIONS ------------------------------------
    static basic_heap32<AllocByte> * create_son ( AllocByte &GA)
    {   //--------------------- begin --------------------------
        void *PAux = GA.allocate(sizeof (heap32<Power2,AllocByte>) );
        if ( PAux== NULL ) throw std::bad_alloc();
        new ((void*)PAux) heap32 < Power2,AllocByte>;
        return ( basic_heap32<AllocByte> *) PAux ;
    };
};

template <uint32_t Power2 ,typename AllocByte>
struct procreate32< false, Power2,  AllocByte>
{   //------------------------------------------------------------------------
    static_assert ( Power2 < 32,"Size too Big");
    typedef typename AllocByte::value_type value_type ;
    static_assert(sizeof(value_type) == 1,"Error AllocByte");

    static basic_heap32<AllocByte> * create_son ( AllocByte & )
    {   //--------------------- begin --------------------------
        return (basic_heap32<AllocByte> *) NULL ;
    };
};

//##########################################################################
//                                                                        ##
//                        S T R U C T                                     ##
//          B A S I C _ H E A P 3 2  < A L L O C B Y T E >                ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class basic_heap32
/// @param [in] N is the power of 2 which indicates the number
///              of elements
/// @remarks This class is for use the heaps of a pool in a uniform way
///          with the inheritance. This is the interface used by the
///          pool for to manage the heaps
///
//----------------------------------------------------------------
template <typename AllocByte>
struct basic_heap32
{
//***************************************************************************
//     D E F I N I T I O N S    &     S T A T I C _ A S S E R T
//***************************************************************************
typedef typename AllocByte::value_type value_type ;

static_assert(sizeof(value_type) == 1,"Error AllocByte");

//***************************************************************************
//                     V A R I A B L E S
//***************************************************************************
uint32_t * Ptr ; // pointer to the last level
uint32_t ** L ; //vector of pointers to the first elements of each level
uint32_t const NElemMax ; // Number of elements controlled in the heap
uint32_t const NLevel ; // Number of levels in the heap
uint32_t Cursor ; // position for to find the next empty element
uint32_t NElem ; // Number of elements allocated in the heap

//***************************************************************************
//           C O N S T R U C T O R ,  D E S T R U C T O R
//
//  basic_heap32 (uint32_t **L1, uint32_t NElemMax1,uint32_t NLevel1);
//
//  virtual ~basic_heap32 ();
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : basic_heap
/// @brief Constructor of the class
/// @param [in] L1 : vector of pointers to the first elements of each level
/// @param [in] NBitMax1 :Number of elements controlled in the heap
/// @param [in] NLEvel1 : Number of levels in the heap
/// @remarks
//------------------------------------------------------------------------
basic_heap32 (uint32_t **L1, uint32_t NElemMax1,uint32_t NLevel1) NOEXCEPT
              : Ptr(NULL),L(L1), NElemMax( NElemMax1),
                NLevel (NLevel1),Cursor(0),NElem(0){ };

//------------------------------------------------------------------------
//  function :~basic_heap
/// @brief Destructor of the class
/// @remarks
//------------------------------------------------------------------------
virtual ~basic_heap32 () NOEXCEPT {};

//***************************************************************************
//   S I Z E O F ,  C R E A T E _ S O N
//   I S _ E M P T Y , I S _ F U L L , C A P A C I T Y
//
//  virtual uint32_t SIZEOF ()const =0;
//
//  virtual basic_heap32 * create_son (AllocByte & AB) const =0 ;
//
//  bool     is_full  ( void ) const;
//  bool     is_empty ( void ) const;
//  uint32_t capacity ( void ) const;
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : SIZEOF
/// @brief  return the size in bytes of the heap
/// @remarks
//------------------------------------------------------------------------
virtual uint32_t SIZEOF ()const NOEXCEPT =0;

//------------------------------------------------------------------------
//  function : create_son
/// @brief create a heap from the double size than the actual heap
/// @param [in] AB : raw allocator from extract the memory needed for the
///                  new heap
/// @return pointer to the new heap
/// @remarks
//------------------------------------------------------------------------
virtual basic_heap32 * create_son (AllocByte & AB) const =0 ;

//------------------------------------------------------------------------
//  function : is_full
/// @brief Indicate if the heap is full
/// @return true : full false : not full
//------------------------------------------------------------------------
bool is_full ( void ) const NOEXCEPT {   return ( NElem == NElemMax) ; };

//------------------------------------------------------------------------
//  function : is_empty
/// @brief Indicate if the heap is empty
/// @return true : empty false : not empty
//------------------------------------------------------------------------
bool is_empty ( void ) const NOEXCEPT {  return ( NElem == 0) ; };

//------------------------------------------------------------------------
//  function : capacity
/// @brief Return the capacity of the heap
/// @return capacity of the heap
/// @remarks
//------------------------------------------------------------------------
uint32_t capacity ( void ) const NOEXCEPT {   return NElemMax ; };

//***************************************************************************
//  R E A D _ B I T , A L L O C A T E , D E A L L O C A T E , C H E C K
//
//  bool read_bit ( uint32_t Pos) const;
//
//  uint32_t allocate   ( void);
//  void     deallocate ( uint32_t Pos);
//
//  #if __DEBUG_CNTREE != 0
//      virtual bool check( void )const  ;
//  #endif
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : read_bit
/// @brief  Read a bit of the set
/// @param [in] Pos : Position of the bit to read
/// @return true : 1 false : 0
//------------------------------------------------------------------------
bool read_bit ( uint32_t Pos) const NOEXCEPT
{   //------------------------- begin -----------------------
    #if __DEBUG_CNTREE != 0
    assert  ( Pos < NElemMax) ;
    #endif
    return ReadBit32 ( Ptr[Pos >>5], Pos & 31  );
};

//------------------------------------------------------------------------
//  function : allocate
/// @brief find the first position free and allocate an element
/// @param [in] IsFull : Indicate if the heap is full after the allocation
/// @exception  bad:alloc when invocate
/// @return The position of the element allocated. If full return MAX32
//------------------------------------------------------------------------
uint32_t allocate   ( void) NOEXCEPT
{   //------------------------- begin -----------------------------
    if ( is_full() ) return MAX32 ;
    //--------------------------------------------------------------------
    // If the only operations which modify the heap a re allocate and deallocate
    // the cursor can guarantee what the free positions in the heap are from the
    // Cursor position forward
    //---------------------------------------------------------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Cursor < NElemMax) ;
    #endif
    bool Invalid = false ;
    if ( (Invalid = read_bit(Cursor)) )
    {   uint32_t CursorWord = Cursor >>5 ;
        uint32_t Aux = Ptr[ CursorWord ];
        if (  not (Invalid = (Aux == MAX32)) )
            Cursor = (CursorWord <<5)+ LS1B_32 ( ~Aux);
    };
    uint32_t Level ;
    if ( Invalid )
    {   for ( Cursor = 0, Level = 0 ; Level < NLevel ;++Level)
        {   Cursor=(Cursor<<5)+ LS1B_32(~ L[Level][Cursor]);
        };
    };
    //---------------------------------------------------------------------
    // set to one the bit
    //---------------------------------------------------------------------
    uint32_t N1 = Cursor , N2 = 0 ;
    Level = NLevel;
    uint32_t * PAux = NULL ;
    do
    {   N2 = N1 & 31 ;
        PAux = &(L[--Level][N1>>=5]);
        #if __DEBUG_CNTREE != 0
        assert ( not ReadBit32(*PAux , N2)) ;
        #endif
        SetBit32 ( *PAux, N2);
        #if __DEBUG_CNTREE != 0
        assert ( ReadBit32(*PAux , N2)) ;
        #endif
    } while ( (*PAux == MAX32) and Level != 0) ;
    NElem++;
    return ( Cursor++);
 };
//------------------------------------------------------------------------
//  function : deallocate
/// @brief Deallocate an element of the row
/// @param [in] Pos : position of the element to deallocate
/// @return Return if the element was full prior the deallocation
//------------------------------------------------------------------------
void  deallocate ( uint32_t Pos) NOEXCEPT
{   //------------------------ begin -----------------------------
    #if __DEBUG_CNTREE != 0
    assert ( Pos < NElemMax);
    #endif
    uint32_t N1 = Pos , N2 = 0 , Level = NLevel;
    bool SW ;
    do
    {   N2 = N1 &31 ;
        uint32_t & Aux = L[--Level][N1 >>= 5];
        SW = ( Aux == MAX32 );
        #if __DEBUG_CNTREE != 0
        assert ( ReadBit32(Aux , N2)) ;
        #endif
        ResetBit32 ( Aux , N2);
        #if __DEBUG_CNTREE != 0
        assert ( not ReadBit32(Aux , N2)) ;
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
};//              E N D     B A S I C _ H E A P 3 2    C L A S S
//***************************************************************************


//##########################################################################
//                                                                        ##
//                        S T R U C T                                     ##
//           H E A P 3 2 < P O W E R 2 , A L L O C B Y T E >              ##
//                                                                        ##
//##########################################################################

//-------------------------------------------------------------
/// @class heap32
/// @param [in] N is the power of 2 which indicates the number
///              of elements
/// @remarks This class is for the metaprogramming calculation of
///          the size of the Data matrix of uint32_t elements for
///          the heap manager
///
//----------------------------------------------------------------
template <uint32_t Power2, typename AllocByte>
struct heap32: public basic_heap32<AllocByte>
{
//***************************************************************************
//               S T A T I C    V A R I A B L E S
//***************************************************************************

static const uint32_t NLEVEL = ((Power2== 0)?1:((Power2+4)/5) );
static const uint32_t Mask =(Power2==0)? (MAX32<<1):
                               ((Power2%5)==0)?0:(MAX32<< (1U <<(Power2 %5)));
static const uint32_t NTotalWord = NTOTALWORD32< NLEVEL,Power2>::Data ;
static const uint32_t n_bits_max =  Conf<4>::n_bits_max   ;
static_assert ( n_bits_max >= Power2,"Size too Big");

//***************************************************************************
//               P U B L I C     V A R I A B L E S
//***************************************************************************

using basic_heap32 <AllocByte>::Cursor;
using basic_heap32 <AllocByte>::Ptr;
uint32_t * L1[ NLEVEL];
uint32_t P1 [ NTotalWord];

//***************************************************************************
//                P U B L I C    F U N C T I O N S
//
//  heap32 ( void ) ;
//  virtual ~heap32 ();
//
//  uint32_t SIZEOF (  )
//  void clear ( void )
//
//  basic_heap32<AllocByte> * create_son ( AllocByte  & GA  ) const
//
// #if __DEBUG_CNTREE != 0
//     bool check ( void ) const ;
// #endif
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : heap
/// @brief class constructor
/// @remarks
//------------------------------------------------------------------------
heap32 ( void ) NOEXCEPT : basic_heap32<AllocByte> ( L1,(1U << Power2),NLEVEL)
{   //---------------------------- begin -------------------
    L1[0] = P1 ;
    if ( NLEVEL > 1)
    {   L1[1] = P1 + 1 ;
        uint32_t NW1 = ( 1 <<( Power2 - 5 * ( NLEVEL -1)) );
        for ( uint32_t i = 2 ; i < NLEVEL ; i++)
        {   L1[i] = L1[i-1]+ NW1 ;
            NW1 = NW1 <<5 ;
        };
    }
    ::memset ( P1, 0 , NTotalWord << 2);
    P1[0] = Mask ;
    Ptr = L1[ NLEVEL -1];
};
//------------------------------------------------------------------------
//  function :~heap32
/// @brief virtual destructor
/// @remarks
//------------------------------------------------------------------------
virtual ~heap32 ()NOEXCEPT {   };

//------------------------------------------------------------------------
//  function : SIZEOF
/// @brief return the size of the data structure in bytes
/// @remarks
//------------------------------------------------------------------------
uint32_t SIZEOF (  ) const NOEXCEPT { return sizeof ( *this); };

//------------------------------------------------------------------------
//  function : clear
/// @brief clear all the data structure
/// @remarks
//------------------------------------------------------------------------
void clear ( void ) NOEXCEPT
{   //--------------------- begin -----------------------
    ::memset ( P1, 0 , NTotalWord << 2);
    P1[0] = Mask ;
    Cursor =0 ;
};
//------------------------------------------------------------------------
//  function : create_son
/// @brief create a row which template parameter Power2 is plus 1 the actual
/// @return pointer to the new row
/// @remarks
//------------------------------------------------------------------------
basic_heap32<AllocByte> * create_son ( AllocByte  & GA  ) const
{   //---------------------- begin --------------------------------------
    return procreate32 <((Power2+1)< (n_bits_max -2 )),Power2+1,AllocByte>::create_son (GA) ;
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
bool check ( void ) const NOEXCEPT ;
#endif

//***************************************************************************
};//              E N D     H E A P 3 2     C L A S S
//***************************************************************************

//##########################################################################
//                                                                        ##
//            F U N C I O N E S   N O N    I N L I N E                    ##
//                                                                        ##
//##########################################################################

#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief Check if the data structure is OK
/// @return true : OK false : error
/// @remarks
//------------------------------------------------------------------------
template <uint32_t Power2, typename AllocByte>
bool heap32<Power2,AllocByte>::check ( void ) const NOEXCEPT
{   //------------------------- begin ------------------
    bool SW = true ;
    uint32_t Level , i ;

    for ( Level = 1 ; SW and Level < NLEVEL ; Level++)
    {   uint32_t NMaxLevel = ( 1 << (Power2 - 5 * (NLEVEL - Level)));
        for ( i =0 ; SW and i < NMaxLevel ; i++)
        {   SW = ((L1[Level][i]== MAX32)==(ReadBit32(L1[Level-1][i >>5], i& 31)));
        };
    }
    if ( not SW)
    {   std::cout<<"Error  Level :"<<Level-1<<"  Element :"<<i-1<<std::endl;
    };
    return SW ;
};
#endif

#if __DEBUG_CNTREE != 0

//------------------------------------------------------------------------
//  function : operator <<
/// @brief print operator
/// @param [in]
/// @return
/// @remarks
//------------------------------------------------------------------------
template < uint32_t Power2, typename AllocByte>
std::ostream & operator<< ( std::ostream & S,const heap32<Power2,AllocByte> & H )
{   //---------------------------- Begin ------------------------------
    S<<"---------------------------------------------------------------\n";
    S<<"Power2 "<< Power2 <<"  NLevel :"<<H.NLevel<<std::endl;
    S<<"NBitMax :"<< std::hex<<H.NBitMax<<" NTotalWord :"<<H.NTotalWord ;
    S<<" Mask :"<< std::hex<<H.Mask<<std::endl ;
    S<<"[ 0 ] "<<H.L[0][0]<<std::endl;
    for ( uint64_t Level = 1 ; Level < H.NLevel ; Level++)
    {   S<< std::dec<<"[ "<<Level<<" ] ";
        uint64_t NMaxLevel = ( 1 << (Power2 - 5 * (H.NLevel - Level)));
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
