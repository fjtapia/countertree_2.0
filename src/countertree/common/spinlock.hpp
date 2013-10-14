//----------------------------------------------------------------------------
/// @file spinlock.hpp
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
#ifndef __COUNTERTREE_COMMON_SPIN_LOCK_HPP
#define __COUNTERTREE_COMMON_SPIN_LOCK_HPP

#include <atomic>
#include <boost/countertree/common/definitions.hpp>
#include <memory>
#include <functional>
#include <mutex>
#include <thread>

namespace countertree
{
namespace common
{
//##########################################################################
//                                                                        ##
//                 C L A S S     S P I N L O C K                          ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
/// @class spinlock
///
/// @remarks
//---------------------------------------------------------------------------
class spinlock
{
private:
//***************************************************************************
//             P R I V A T E      V A R I A B L E S
//***************************************************************************
std::atomic_flag af ;

public :
//---------------------------------------------------------------------------
//  function : spinlock
/// @brief  class constructor
/// @param [in]
//---------------------------------------------------------------------------
#ifdef _MSC_VER
explicit spinlock ( ) NOEXCEPT
{    af.clear() ;
}
#else
explicit spinlock ( ) NOEXCEPT : af ( ATOMIC_FLAG_INIT ){ };
#endif

//---------------------------------------------------------------------------
//  function : lock
/// @brief  Lock the spinlock
//---------------------------------------------------------------------------
void lock() NOEXCEPT
{   while ( af.test_and_set(std::memory_order_acquire) );
};
//---------------------------------------------------------------------------
//  function : try_lock
/// @brief Try to lock the spinlock, if not, return false
/// @param [in]
/// @return true :locked false: not previous locked
//---------------------------------------------------------------------------
bool try_lock() NOEXCEPT
{   return not af.test_and_set(std::memory_order_acquire);
};
//---------------------------------------------------------------------------
//  function : unlock
/// @brief  unlock the spinlock
//---------------------------------------------------------------------------
void unlock() NOEXCEPT
{   //----------------------- begin -----------------
    af.clear(std::memory_order_release );
};
//***************************************************************************
};// E N D    C L A S S     S P I N L O C K
//***************************************************************************

//##########################################################################
//                                                                        ##
//            C L A S S      L O C K _ D A T A _ C N C                    ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class  lock_data_cnc
/// @brief  This class implements the data  for the lock
//
/// @remarks
//----------------------------------------------------------------
struct lock_data_cnc
{   countertree::common::spinlock SL ;
};

//##########################################################################
//                                                                        ##
//             C L A S S        L O C K _ C N C                           ##
//                                                                        ##
//##########################################################################

//-------------------------------------------------------------
/// @class  lock_cnc
/// @brief  This class implements the barrier for the function
///         which modify the vector_tree_cnc_cnc\n
//
/// @remarks
//----------------------------------------------------------------
class lock_cnc
{private :
    //-------------- Variables ---------------------------
    std::unique_lock <spinlock> UL ;

    //------------ Forbidden Functions -------------------
    lock_cnc()  ;
    lock_cnc ( const lock_cnc &)  ;
    lock_cnc & operator = ( const lock_cnc &)  ;
    //lock_cnc() = delete ;
    //lock_cnc ( const lock_cnc &) = delete ;
    //lock_cnc & operator = ( const lock_cnc &) = delete ;

 public :
    lock_cnc (lock_data_cnc &BDC):UL(BDC.SL){} ;
    ~lock_cnc() {  };
};

//##########################################################################
//                                                                        ##
//         C L A S S        L O C K _ D A T A _ E M P T Y                 ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class  lock_data_empty
/// @brief  This class implements the data  for the lock
//
/// @remarks
//----------------------------------------------------------------
struct lock_data_empty {  };


//##########################################################################
//                                                                        ##
//             C L A S S        L O C K _ E M P T Y                       ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class  lock_empty
/// @brief  This class implements the barrier for the function
///         which modify the vector_tree_cnc_cnc\n
//
/// @remarks
//----------------------------------------------------------------
class lock_empty
{private :
    //------------------- Forbidden Functions --------------------
    //lock_empty() = delete ;
    //lock_empty ( const lock_empty &) = delete ;
    //lock_empty & operator = ( const lock_empty &) = delete ;
    lock_empty()  ;
    lock_empty ( const lock_empty &)  ;
    lock_empty & operator = ( const lock_empty &) ;
 public :
    lock_empty (lock_data_empty &){} ;
    ~lock_empty() {  };
};

//##########################################################################
//                                                                        ##
//    C L A S S   C O N F I G _ L O C K < I S _ C O N C U R R E N T  >    ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
/// @class config_lock
/// @brief : Template for to select the lock depending if is concurrent
///          or not
///
/// @remarks
//---------------------------------------------------------------------------
template <bool is_concurrent>
struct config_lock ;

template < >
struct config_lock <true>
{   typedef lock_data_cnc      lock_data ;
    typedef lock_cnc           mylock ;
};
template < >
struct config_lock < false>
{   typedef lock_data_empty      lock_data ;
    typedef lock_empty           mylock ;
};

//***************************************************************************
};// E N D    N A M E S P A C E    A L L O C
};// E N D    N A M E S P A C E    C O U N T E R T R E E
//***************************************************************************
#endif
