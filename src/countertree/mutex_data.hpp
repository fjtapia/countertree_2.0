//----------------------------------------------------------------------------
/// @file   mutex_data.hpp
/// @brief  This file contains the implementation of the several types of
///         recursive fastmutex for read and write
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_MUTEX_DATA_HPP
#define __COUNTERTREE_MUTEX_DATA_HPP

#include <boost/countertree/common/spinlock.hpp>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <iostream>

namespace countertree
{
using countertree::common::spinlock ;
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                      C L A S S                               #     ##
//    #             E M P T Y _ M U T E X _ D A T A                  #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  empty_mutex_data
/// @brief  This class implements information for to be used by
///         fast_read_cnc and fastmutex_write_cnc in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
class empty_mutex_data
{
public:
//------------------------ functions ----------------------
empty_mutex_data ( const empty_mutex_data &){};
empty_mutex_data ( void){};

empty_mutex_data & operator= ( const empty_mutex_data &){ return *this ;};
//
//**************************************************************************
//         L O C K  /  U N L O C K     M O D I F Y
//**************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_write
/// @brief  This function  try to lock for the write operation.
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_write ( void) { return true ;}

//---------------------------------------------------------------------------
//  function : lock_write
/// @brief  This function  lock for the write operation.
//---------------------------------------------------------------------------
void lock_write ( void) { };
//---------------------------------------------------------------------------
//  function : unlock_write
/// @brief this function unlock for the write operation
//---------------------------------------------------------------------------
void unlock_write( void){ };
//
//***************************************************************************
//          L O C K  /  U N L O C K     R E A D
//***************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_read
/// @brief  This function try to lock for the read operation.
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_read ( void){ return true;};
//---------------------------------------------------------------------------
//  function : lock_read
/// @brief  This function lock for the read operation.
//---------------------------------------------------------------------------
void lock_read ( void){ };
//---------------------------------------------------------------------------
//  function :  unlock_read
/// @brief this function unlock for the read operation
//---------------------------------------------------------------------------
void unlock_read ( void){}

//---------------------------------------------------------------------------
//  function : no_readers
/// @brief This function return true when the number of functions with
///        lock_read reading over the data structure is zero
/// @return true: no readers false : readers
//---------------------------------------------------------------------------
bool no_readers ( void) const { return true ;};
//---------------------------------------------------------------------------
//  function : n_readers
/// @brief This function return the number of functions with lock_read  reading
///         over the data structure
/// @return number
//---------------------------------------------------------------------------
uint32_t n_readers ( void) const { return 0 ;};
//---------------------------------------------------------------------------
//  function : wait_no_readers
/// @brief This function wait until the number of readers over the data
///         structure is 0
//---------------------------------------------------------------------------
void wait_no_readers () {};
//---------------------------------------------------------------------------
};//                end of class empty_mutex_data
//--------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                      C L A S S                               #     ##
//    #          R W _ F A S T M U T E X _ D A T A                   #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  rw_fastmutex_data
/// @brief  This class implements information for to be used by
///         fastmutex_read_cnc and fastmutex_write_cnc in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
class rw_fastmutex_data
{
private:
//------------------------- variables --------------------
mutable spinlock spl ;
uint32_t nmutex;
uint32_t nread ;
std::thread::id tid ;

public:
//------------------------ functions ----------------------
rw_fastmutex_data ( const rw_fastmutex_data &):nmutex(0),nread(0){};
rw_fastmutex_data ( void):nmutex(0),nread(0){};

rw_fastmutex_data & operator= ( const rw_fastmutex_data &)
{   return *this ;
};
static std::thread::id this_id ( void)
{   return std::this_thread::get_id();
};
//
//**************************************************************************
//         L O C K  /  U N L O C K     M O D I F Y
//**************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_write
/// @brief  This function lock for the write operation. It's atomic
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_write ( void)
{   //---------------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    bool SW = ( nmutex == 0 or tid == this_id() );
    if ( SW)
    {   nmutex++ ;
        tid = this_id() ;
    };
    return SW ;
}
//---------------------------------------------------------------------------
//  function : lock_write
/// @brief  This function lock for the write operation. It's atomic
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
void lock_write(void)
{   while ( not try_lock_write() )
        std::this_thread::yield();
};
//---------------------------------------------------------------------------
//  function : unlock_write
/// @brief this function unlock the write operation
//---------------------------------------------------------------------------
void unlock_write( void)
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    assert ( nread== 0 and tid == this_id() and nmutex > 0)  ;
    nmutex --    ;
};
//
//***************************************************************************
//          L O C K  /  U N L O C K     R E A D
//***************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_read
/// @brief  This function lock for the read operation. It's atomic
/// @param [in]
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_read ( void)
{   //---------------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    bool SW = ( nmutex == 0 or tid == this_id ());
    if ( SW)   nread++ ;
    return SW ;
};
//---------------------------------------------------------------------------
//  function : lock_read
/// @brief  This function lock for the read operation. It's atomic
/// @param [in]
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
void lock_read(void)
{   //--------------------- begin ----------------------------
    while ( not try_lock_read() )
        std::this_thread::yield();
};
//---------------------------------------------------------------------------
//  function :  unlock_read
/// @brief This function unlock the read operation
//---------------------------------------------------------------------------
void unlock_read ( void)
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    if ( not( nread > 0 and ( nmutex == 0 or tid == this_id () )))

    assert ( nread > 0 );
    nread--;
};
//---------------------------------------------------------------------------
//  function : no_readers
/// @brief This function return true when the number of functions with
///        lock_read reading over the data structure is zero
/// @return true: no readers false : readers
//---------------------------------------------------------------------------
bool no_readers ( void) const
{   std::unique_lock <spinlock> UL ( spl);
    assert ( nmutex > 0);
    return ( nread == 0) ;
};
//---------------------------------------------------------------------------
//  function : n_readers
/// @brief This function return the number of functions with lock_read  reading
///         over the data structure
/// @return number
//---------------------------------------------------------------------------
uint32_t n_readers ( void) const
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    assert ( nmutex > 0);
    return nread ;
};
//---------------------------------------------------------------------------
//  function : wait_no_readers
/// @brief This function wait until the number of readers over the data
///         structure is 0
//---------------------------------------------------------------------------
void wait_no_readers ()
{   while (not no_readers()) std::this_thread::yield() ;
};
//---------------------------------------------------------------------------
};//                 end of class rw_fastmutex_data
//---------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                      C L A S S                               #     ##
//    #             R W _ M U T E X _ D A T A                        #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  rw_mutex_data
/// @brief  This class implements information for to be used by
///         fastmutex_read_cnc and fastmutex_write_cnc in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
class rw_mutex_data
{
private:
//------------------------- variables --------------------
mutable spinlock spl ;
uint32_t nwrite,nread ;
std::condition_variable_any cv_no_readers, cv_read, cv_write ;
std::mutex mtx_read, mtx_write,  mtx_no_readers;
std::thread::id tid ;

public:
//------------------------ functions ----------------------
rw_mutex_data ( const rw_mutex_data &):nwrite(0),nread(0){};
rw_mutex_data ( void):nwrite(0),nread(0){};

rw_mutex_data & operator= ( const rw_mutex_data &)
{   return *this ;
};
static std::thread::id this_id ( void)
{   return std::this_thread::get_id();
};
//
//**************************************************************************
//         L O C K  /  U N L O C K     W R I T E
//**************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_write
/// @brief  This function lock for the write operation. It's atomic
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_write ( void)
{   //---------------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    bool SW = ( nwrite == 0 or tid == this_id ());
    if ( SW)
    {   nwrite++ ;
        tid = this_id() ;
    };
    return SW ;
}
//---------------------------------------------------------------------------
//  function : lock_write
/// @brief  This function lock for the write operation. It's atomic
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
void lock_write(void)
{   //----------------------- begin ----------------------------
    struct shuttle
    {   rw_mutex_data &r ;
        shuttle ( rw_mutex_data & Alfa):r(Alfa){ };
        bool operator( )( void) { return (r.try_lock_write());};
    } S ( *this);
    cv_write.wait ( mtx_write, S );

}
//---------------------------------------------------------------------------
//  function : unlock_write
/// @brief this function unlock the write operation
//---------------------------------------------------------------------------
void unlock_write( void)
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    assert ( tid == this_id() and nwrite > 0)  ;
    nwrite -- ;
    if ( nwrite == 0 )
    {   cv_write.notify_all() ;
        cv_read.notify_all() ;
    };
};
//---------------------------------------------------------------------------
//  function : no_readers
/// @brief This function return true when the number of functions with
///        lock_read reading over the data structure is zero
/// @return true: no readers false : readers
//---------------------------------------------------------------------------
bool no_readers ( void) const
{   std::unique_lock <spinlock> UL ( spl);
    return ( nread == 0) ;
};
//---------------------------------------------------------------------------
//  function : n_readers
/// @brief This function return the number of functions with lock_read  reading
///         over the data structure
/// @return number
//---------------------------------------------------------------------------
uint32_t n_readers ( void) const
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    return nread ;
};
//---------------------------------------------------------------------------
//  function : wait_no_readers
/// @brief This function wait until the number of readers over the data
///         structure is 0
//---------------------------------------------------------------------------
void wait_no_readers ()
{
    struct shuttle
    {   rw_mutex_data &r ;
        shuttle ( rw_mutex_data & Alfa):r(Alfa){ };
        bool operator( )( void) { return (r.no_readers() );};
    } S ( *this);
    cv_no_readers.wait ( mtx_no_readers,S );
};
//
//***************************************************************************
//          L O C K  /  U N L O C K     R E A D
//***************************************************************************
//---------------------------------------------------------------------------
//  function : try_lock_read
/// @brief  This function lock for the read operation. It's atomic
/// @param [in]
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
bool try_lock_read ( void)
{   //---------------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    bool SW = ( nwrite == 0 or tid == this_id () );
    if ( SW)  nread++ ;
    return SW ;
};
//---------------------------------------------------------------------------
//  function : lock_read
/// @brief  This function lock for the read operation. It's atomic
/// @param [in]
/// @return true : locked     false : unlocked
//---------------------------------------------------------------------------
void lock_read(void)
{   //--------------------- begin ----------------------------
    struct shuttle
    {   rw_mutex_data &r ;
        shuttle ( rw_mutex_data & Alfa):r(Alfa){ };
        bool operator( )( void) { return (r.try_lock_read());};
    } S ( *this);
    cv_read.wait ( mtx_read,S );

};
//---------------------------------------------------------------------------
//  function :  unlock_read
/// @brief This function unlock the read operation
//---------------------------------------------------------------------------
void unlock_read ( void)
{   //-------------------------- begin --------------------
    std::unique_lock <spinlock> UL ( spl);
    assert ( nread > 0  );
    nread--;
    if ( nread == 0 ) cv_no_readers.notify_all() ;
};

//---------------------------------------------------------------------------
};//                 end of class rw_mutex_data
//---------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                        S T R U C T                           #     ##
//    #                  C O N F I G _ M U T E X                     #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  config_mutex
/// @brief  This class implements the fastmutex  selector depending of the
///         concurrency ( cnc) of the data structure\n
//
/// @remarks
//---------------------------------------------------------------------------
template <bool is_concurrent> struct config_mutex ;

template < >  struct config_mutex <true>
{   typedef rw_mutex_data       mutex_data ;
};
template < > struct config_mutex < false>
{   typedef empty_mutex_data     mutex_data ;
};
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                        S T R U C T                           #     ##
//    #             C O N F I G _ F A S T M U T E X                  #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  config_fastmutex
/// @brief  This class implements the fastmutex  selector depending of the
///         concurrency ( cnc) of the data structure\n
//
/// @remarks
//---------------------------------------------------------------------------
template <bool is_concurrent> struct config_fastmutex ;

template < >  struct config_fastmutex <true>
{   typedef rw_fastmutex_data      fastmutex_data ;
};
template < > struct config_fastmutex < false>
{   typedef empty_mutex_data      fastmutex_data ;
};
//***************************************************************************
};//     E N D   N A M E S P A C E   C O U N T E R T R E E
//***************************************************************************
#endif
