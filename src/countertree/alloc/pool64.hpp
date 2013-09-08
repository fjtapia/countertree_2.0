//----------------------------------------------------------------------------
/// @file   pool64.hpp
/// @brief  This file contains the implementation of the non contiguous memory
///         vector formed with blocks of different size
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_ALLOC_POOL64_HPP
#define __COUNTERTREE_ALLOC_POOL64_HPP


#include <stdexcept>
#include <memory>
#include <iostream>
#include <boost/countertree/alloc/heap64.hpp>
#include <boost/countertree/common/spinlock.hpp>
#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/common/mysingleton.hpp>

namespace cnt_alloc = countertree::alloc ;
namespace countertree
{
namespace alloc
{
namespace c_common = countertree::common ;
//
//##########################################################################
//                                                                        ##
//                   C L A S S    N B I T S  6 4                          ##
//                 ( M e t a p r o g r a m m i n g )                      ##
//                                                                        ##
//##########################################################################
//
//----------------------------------------------------------------
/// @class NBits64
/// @brief This class is for to calculate the minimalnumber of bits
//         needed for to represent a number
///
//----------------------------------------------------------------
template <uint64_t Number64, uint64_t NB = 0, bool SW = true >
struct NBits64 ;

template <uint64_t Number64, uint64_t NB >
struct NBits64 < Number64, NB, true>
{   static_assert( NB < 64, "Error in parameter NB ");
    static const uint64_t N = NBits64 <Number64,NB+1,((1ULL<<(NB+1))<= Number64) >::N ;
};
template <uint64_t Number64, uint64_t NB  >
struct NBits64 <Number64 , NB , false >
{   static_assert( NB <= 64, "Error in parameter NB ");
    static const uint64_t N = NB ;
};
//
//##########################################################################
//                                                                        ##
//                          C L A S S                                     ##
//                                                                        ##
//                         P O O L 6 4                                    ##
//                                                                        ##
//##########################################################################
//
//-------------------------------------------------------------
/// @class  pool64
/// @brief  This class represent a vector of pointers to rows with
///         crescend size
//
/// @remarks
//----------------------------------------------------------------
template <  uint64_t SizeElem,
            bool cnc = false,
            typename AllocByte = myallocator <uint8_t>
         >
class pool64
{

//***************************************************************************
//                 S T A T I C _ A S S E R T
//***************************************************************************
static_assert(sizeof(typename AllocByte::value_type) == 1,"Error AllocByte");
static_assert( SizeElem != 0 , "Error in SizeElem") ;
public:
//***************************************************************************
//                     D E F I N I T I O N S
//***************************************************************************
typedef countertree::alloc::config_lock<cnc>    config_lock;
typedef typename config_lock::lock_data         lock_data ;
typedef typename config_lock::mylock            mylock ;
typedef uint64_t      size_type ;//Quantities of elements
typedef int64_t       difference_type ;//Difference between two pointers
typedef c_common::mysingleton <AllocByte,cnc>   singleton ;

static const uint64_t MaxElemRow = ( MAX64 >> 1 ) / SizeElem ;
static uint64_t const MaskPos = (1ULL << 58)-1 ;

static const uint64_t Power2Max =  c_common::n_bits_max - NBits64<SizeElem>::N ;


private:
//***************************************************************************
//                P R I V A T E        V A R I A B L E S
//***************************************************************************
basic_heap64<AllocByte> * V[Power2Max];
uint8_t* Ptr [Power2Max] [2];
AllocByte &AB ;
uint64_t NMax, NElem ;
uint64_t NRow, Mask, Cursor;
mutable lock_data LD;

//***************************************************************************
//                 F O R B I D D E N    F U N C T I O N S
//
//  pool64 ( const pool64 &);
//  pool64 & operator = ( const pool64 &);
//
//***************************************************************************
//explicit pool64 ( const pool64 &) = delete;
//pool64 & operator = ( const pool64 &) = delete;
explicit pool64 ( const pool64 &) ;
pool64 & operator = ( const pool64 &) ;

//***************************************************************************
//         P R I V A T E      F U N C T I O N S
//
//  void create_row (void);
//  void delete_row (void)
//
//***************************************************************************
//------------------------------------------------------------------------
//  function : create_row
/// @brief create a new row with double size than the previous
/// @exception  std::bad_alloc  when fails the allocation
/// @remarks
//------------------------------------------------------------------------
void create_row (void)
{   //--------------begin------------------------------------
    if ( NRow == Power2Max )throw std::bad_alloc();

    V[NRow]= NULL ;
    if (NRow == 0)
    {   void * PAux = AB.allocate ( sizeof (heap64<0,AllocByte> ) );
        if ( PAux == NULL ) throw std::bad_alloc();
        ::new ((void*)PAux) heap64 < 0,AllocByte>;
        V[0]= ( basic_heap64<AllocByte> *) PAux ;
    }
    else V[NRow] =V[NRow-1]->create_son(AB);

    ResetBit64 ( Mask , NRow);
    NMax += V[NRow]->capacity();

    Ptr[NRow][0] = NULL;
    Ptr[NRow][0] =  AB.allocate ( V[NRow]->NElemMax * SizeElem);
    if ( Ptr[NRow][0] == NULL )
    {   AB.deallocate ( (uint8_t*)V[NRow],V[NRow]->SIZEOF() );
        V[NRow ] = NULL ;
        throw std::bad_alloc();
    };
    Ptr[NRow][1] = Ptr[NRow][0] + (V[NRow]->NElemMax * SizeElem) ;
    NRow ++ ;
};
//------------------------------------------------------------------------
//  function : delete_row
/// @brief delete the last row
/// @exception  std::bad_alloc  when fails the deallocation
/// @remarks
//------------------------------------------------------------------------
void delete_row (void)
{   //--------------------------------- begin ---------------------------
    while ( (NRow >1) and NElem <= ((NMax+1) >> 2) and (V[NRow-1]->is_empty()) )
    {   NRow -- ;
        NMax -= V[NRow]->capacity();
        AB.deallocate ( (uint8_t*)Ptr[NRow][0], ( V[NRow]->NElemMax * SizeElem));
        AB.deallocate ((uint8_t*)V[NRow], (V[NRow]->SIZEOF()) );
        V[NRow ] = NULL ;

        Ptr[NRow][0] = Ptr[NRow][1] = NULL ;
        if ( Cursor >= NRow) Cursor = NRow -1 ;
        SetBit64( Mask ,NRow);
    };
};
public:
//***************************************************************************
//                P U B L I C      F U N C T I O N S
//
//  pool64  ( void)
//  virtual ~pool64 ( void )
//
//  uint64_t     size( void)
//  uint64_t     capacity ( void)
//  void         clear ( void )
//
//  void * allocate ( void )
//  void deallocate ( void *P1)
//
// #if __DEBUG_CNTREE != 0
//    bool check( void) const;
// #endif
//
//***************************************************************************
//
//------------------------------------------------------------------------
//  function : pool
/// @brief class constructor
/// @remarks
//------------------------------------------------------------------------
pool64  ( void)
:AB( singleton::instance()), NMax(0),NElem(0),NRow(0),Mask(MAX64), Cursor(0)
{   //--------------------------- begin -------------------------
    mylock ML ( LD);
    for ( uint64_t i = 0 ; i < Power2Max ; ++i)
    {   Ptr[i][0]= Ptr[i][1] = NULL ;
        V[i] = NULL;
    };
} ;
//------------------------------------------------------------------------
//  function : ~pool
/// @brief class destructor
/// @remarks
//------------------------------------------------------------------------
virtual ~pool64 ( void ){ clear() ;};

//------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements allocated by the IncVector
/// @return number of elements allocated
/// @remarks
//------------------------------------------------------------------------
uint64_t size( void )const
{   mylock ML ( LD);
    return NElem ;
};
//------------------------------------------------------------------------
//  function : capacity
/// @brief return the actual capacity of the IncVector
/// @return capacity
/// @remarks
//------------------------------------------------------------------------
uint64_t capacity ( void) const
{   return NMax;
};
//------------------------------------------------------------------------
//  function : clear
/// @brief : clean the IncVector
/// @remarks
//------------------------------------------------------------------------
void clear ( void ) ;

//------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate an element
/// @return pointer to the object allocated
/// @remarks
//------------------------------------------------------------------------
void * allocate ( void )
{   //----------------------------------- begin --------------------------
    mylock ML ( LD);
    if ( NElem == NMax) create_row();
    if ( V[Cursor]->is_full())
        Cursor = LS1B_64 (~Mask ) ;
    uint64_t Pos = V[Cursor]->allocate( ) ;
    if ( V[Cursor]->is_full())  SetBit64 (Mask , Cursor);
    NElem ++ ;
    return (Ptr[Cursor][0] + ( Pos * SizeElem)) ;
};
//------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate an object
/// @param [in]
/// @return
/// @remarks
//------------------------------------------------------------------------
void deallocate ( void *P1)
{   //-------------------------------------- begin --------------------------
    mylock ML ( LD);
    if ( NElem == 0) throw std::bad_alloc();
    bool Found = false ;
    uint64_t i = NRow ;
    uint8_t * PAux = (uint8_t*) P1;
    do
    {   i--;
        Found = (Ptr[i][0]<= PAux and Ptr[i][1]> PAux);
    } while ( not Found and i != 0 )    ;
    if ( not Found)  throw std::bad_alloc();
    V[i]->deallocate ( (PAux - Ptr[i][0])/SizeElem );
    if ( i < Cursor) Cursor = i ;
    ResetBit64 ( Mask , i );
    NElem -- ;

    if (NElem<=((NMax+1)>>2) and (V[NRow-1]->is_empty()))
        delete_row() ;
};
#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief check if the internal structure of the pool is OK
/// @param [in]
/// @return  true : correct  false: fail
/// @remarks
//------------------------------------------------------------------------
bool check( void)  ;
#endif

//***************************************************************************
};//              E N D     P O O L 6 4     C L A S S
//***************************************************************************

//***************************************************************************
//                   C L A S S    P O O L 6 4
//
//              N O N   I N L I N E    F U N C T I O N S
//***************************************************************************

//------------------------------------------------------------------------
//  function : clear
/// @brief : clean the IncVector
/// @remarks
//------------------------------------------------------------------------
template <uint64_t SizeElem, bool cnc, typename AllocByte >
void pool64<SizeElem,cnc,AllocByte>::clear ( void )
{   //-------------------------- begin ---------------------
    mylock ML ( LD);
    for ( uint64_t i = 0 ; i < NRow ; ++i)
    {   AB.deallocate ( Ptr[i][0], (V[i]->NElemMax * SizeElem));
        Ptr[i][0]= Ptr[i][1] = NULL ;
        AB.deallocate (( uint8_t *) V[i], (V[i]->SIZEOF()) ) ;
        V[i] = NULL ;
    };
    NElem = NMax = NRow = Cursor= 0 ;
    Mask = MAX64 ;
};

#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief check if the internal structure of the pool is OK
/// @param [in]
/// @return  true : correct  false: fail
/// @remarks
//------------------------------------------------------------------------
template <uint64_t SizeElem, bool cnc, typename AllocByte >
bool pool64<SizeElem,cnc,AllocByte>::check( void)
{   //------------------------------ begin -----------------------------
    mylock ML ( LD);
    if ( NElem > NMax or ( ( NElem > 0 or NMax > 0) and NRow == 0 ) )
        std::cout<<"Error en los parametros basicos\n";
    for ( uint64_t i =0 ; i < NRow ; i++)
    {   if ( Ptr[i][0] >= Ptr[i][1] )
        {   std::cout<<"Error en los cachos de memoria\n";
            return false ;
        };
        if ( V[i]->capacity() != ( 1ULL<<i ))
        {   std::cout<<"Pila de un tamaño erroneo\n";
            return false ;
        };
        if ( not V[i]->check() ) return false ;
    };
    return true ;
};
#endif

#if __DEBUG_CNTREE != 0
template < uint64_t SizeElem, bool cnc,typename AllocByte >
std::ostream & operator<< ( std::ostream & S , const pool64<SizeElem,cnc,AllocByte> & P )
{   //--------------------------------------- begin ------------------------
    S<<"Capacity :"<<P.capacity()<<"  Size :"<<P.size() <<std::endl;
    //S<<" Number of rows "<<P.NRow<<std::endl;
    //S<<"Mask of rows filled "<< std::hex<<P.Mask<< std::dec ;
    //S<<"  CursorRow "<<P.Cursor<<std::endl;
    for ( uint64_t i  =0  ; i < P.NRow ; ++i )
    {   S<<"["<<i<<" ] "<< std::hex<<(void*)(P.Ptr[i][0])<<" - "<<(void*)(P.Ptr[i][1]);
        //S<< std::dec<< (*P.V[i] );
    };
    return S ;
};
#endif

//
//##########################################################################
//                                                                        ##
//                             C L A S S                                  ##
//                                                                        ##
//                P O O L 6 4 < 0 , A L L O C B Y T E >                   ##
//                                                                        ##
//##########################################################################
//
//-------------------------------------------------------------
/// @class  pool64
/// @brief  This class is for to provide allocation to the elements of
///         zero bytes of size
//
/// @remarks
//----------------------------------------------------------------
template <  bool cnc  ,
            typename AllocByte
         >
class pool64 < 0 ,cnc, AllocByte>
{
//***************************************************************************
//                    S T A T I C _ A S S E R T
//***************************************************************************
static_assert(sizeof(typename AllocByte::value_type) == 1,"Error AllocByte");

public:
//***************************************************************************
//                 D E F I N I T I O N S
//***************************************************************************
typedef countertree::alloc::config_lock<cnc>    config_lock;
typedef typename config_lock::lock_data         lock_data ;
typedef typename config_lock::mylock            mylock ;

typedef uint64_t    size_type ;//Quantities of elements
typedef int64_t     difference_type ;//Difference between two pointers

static uint64_t const MaskPos = (1ULL << 58)-1 ;

private:
//***************************************************************************
//                P R I V A T E        V A R I A B L E S
//***************************************************************************
AllocByte AB ;
void * Ptr;
uint64_t NElem ;
mutable lock_data LD ;

//**************************************************************************
//                 F O R B I D D E N    F U N C T I O N S
//
//  pool64 ( const pool64 &);
//  pool64 & operator = ( const pool64 &);
//
//***************************************************************************
//pool64 ( const pool64 &) = delete;
//pool64 & operator = ( const pool64 &) = delete;
pool64 ( const pool64 &) ;
pool64 & operator = ( const pool64 &);

public:
//***************************************************************************
//                P U B L I C      F U N C T I O N S
//
//  pool64  ( void)
//  virtual ~pool64 ( void )
//
//  uint64_t     size( void)
//  uint64_t     capacity ( void)
//  void         clear ( void )
//
//  void * allocate ( void )
//  void deallocate ( void *P1)
//
// #if __DEBUG_CNTREE != 0
//    bool check( void) const;
// #endif
//
//***************************************************************************

//------------------------------------------------------------------------
//  function : pool
/// @brief class constructor
/// @remarks
//------------------------------------------------------------------------
explicit pool64  ( void): NElem(0)
{   mylock ML ( LD);
    Ptr = static_cast <void*> ( AB.allocate(1) );
} ;

//------------------------------------------------------------------------
//  function : ~pool
/// @brief class destructor
/// @remarks
//------------------------------------------------------------------------
virtual ~pool64 ( void )
{   mylock ML ( LD);
    AB.deallocate (static_cast <uint8_t*> (Ptr), 1) ;
};

//------------------------------------------------------------------------
//  function : size
/// @brief return the number of elements allocated by the IncVector
/// @return number of elements allocated
/// @remarks
//------------------------------------------------------------------------
uint64_t size( void )const
{   mylock ML ( LD);
    return NElem ;
};

//------------------------------------------------------------------------
//  function : capacity
/// @brief return the actual capacity of the IncVector
/// @return capacity
/// @remarks
//------------------------------------------------------------------------
uint64_t capacity ( void) const { return MaskPos; };

//------------------------------------------------------------------------
//  function : clear
/// @brief : clean the IncVector
/// @remarks
//------------------------------------------------------------------------
void clear ( void )
{   mylock ML ( LD);
    NElem =0;
};

//------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate an element from the IncVector
/// @return pointer to the object allocated
/// @remarks
//------------------------------------------------------------------------
void * allocate ( void )
{   mylock ML ( LD);
    NElem ++ ;
    return (Ptr) ;
};
//------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate an object
/// @param [in]
/// @return
/// @remarks
//------------------------------------------------------------------------
void deallocate ( void *P1)
{   mylock ML ( LD);
    if ( P1 == Ptr ) NElem-- ;
    else throw std::bad_alloc();
};
#if __DEBUG_CNTREE != 0
//------------------------------------------------------------------------
//  function : check
/// @brief check if the internal structure of the pool is OK
/// @param [in]
/// @return  true : correct  false: fail
/// @remarks
//------------------------------------------------------------------------
bool check( void) const { return true ;};
#endif

//***************************************************************************
};//              E N D     P O O L 6 4     C L A S S
//***************************************************************************

#if __DEBUG_CNTREE != 0
template <bool cnc, typename AllocByte >
std::ostream & operator<< ( std::ostream & S , const pool64<0,cnc,AllocByte> & P )
{   //--------------------------------------- begin ------------------------
    S<<"Capacity :"<<P.capacity()<<"  Size :"<<P.size() <<std::endl;
    S<< std::hex<<(void*)(P.Ptr)<<std::dec;
    return S ;
};
#endif
//***************************************************************************
};//              E N D    A L L O C     N A M E S P A C E
//
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
