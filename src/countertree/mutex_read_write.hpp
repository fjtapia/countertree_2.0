//----------------------------------------------------------------------------
/// @file   mutex_read_write.hpp
/// @brief  This file contains the implementation of the several types of
///         recursive mutex for read and write
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_MUTEX_READ_WRITE_HPP
#define __COUNTERTREE_MUTEX_READ_WRITE_HPP

#include <boost/countertree/mutex_data.hpp>


namespace countertree
{
using countertree::common::spinlock ;
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                       C L A S S                              #     ##
//    #               F A S T M U T E X _ R E A D                    #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  mutex_read
/// @brief  This class implements the mutex for the function
///         which read the vector_tree\n
/// @remarks
//---------------------------------------------------------------------------
template <class mutex_data>
class mutex_read
{private :
    //--------------- Variables ---------------
    mutex_data &r ;
    bool locked ;

    //------------- Forbidden Functions -----------------------------
    mutex_read() = delete ;
    mutex_read ( const mutex_read &) = delete ;
    mutex_read & operator = ( const mutex_read &) = delete ;

 public :
    //------------ Public Functions ------------------------
    mutex_read( mutex_data & mdc, bool lock_now = true):r(mdc),locked(false)
    {   if ( lock_now) lock();
    };

    ~mutex_read ( void)
    {   if ( locked ) unlock() ;
    };

    bool try_lock ( void)
    {   assert ( not locked) ;
        return (locked = r.try_lock_read()) ;
    };

    void lock ( void )
    {   assert ( not locked) ;
        r.lock_read() ;
        locked = true ;
    };

    void unlock ( void)
    {   assert ( locked );
        r.unlock_read();
        locked = false ;
    };

//---------------------------------------------------------------------------
};//                 End of class mutex_read
//---------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                     C L A S S                                #     ##
//    #             F A S T M U T E X _ M O D I F Y                  #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//-------------------------------------------------------------
/// @class  mutex_write
/// @brief  This class implements the mutex for the function
///         which write the vector_tree_cnc\n
/// @remarks
//----------------------------------------------------------------
template <class mutex_data>
class mutex_write
{private :
    //----------------- Variables ---------------------
    mutex_data &r ;
    bool locked ;

    //----------- Forbidden Functions ----------------------------
    mutex_write() = delete ;
    mutex_write ( const mutex_write &) = delete ;
    mutex_write & operator = ( const mutex_write &) = delete ;

 public :
    mutex_write (mutex_data & mm , bool lock_now = true):r(mm),locked (false)
    {   if ( lock_now) lock();
    };

    ~mutex_write ( void)
    {   if ( locked) unlock();
    };

    bool try_lock ( void)
    {   assert ( not locked) ;
        return ( locked= r.try_lock_write() );
    };

    void lock ( void)
    {   assert ( not locked);
        r.lock_write();
        locked = true ;
    };

    void unlock( void)
    {   assert ( locked) ;
        r.unlock_write();
        locked = false ;
    };

    void wait_no_readers ()
    {   assert ( locked) ;
        r.wait_no_readers() ;
    };
//---------------------------------------------------------------------------
};//                   end of class mutex_write
//---------------------------------------------------------------------------

//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                        C L A S S                             #     ##
//    #          F A S T M U T E X _ M O D I F Y _ R E A D           #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  mutex_write_read
/// @brief  This class implements information for to be used by
///         mutex_read_empty and mutex_write_empty in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
template <class mutex_data1 , class mutex_data2>
class mutex_write_read
{private :
    mutex_write<mutex_data1> mtx_w ;
    mutex_read<mutex_data2>  mtx_r ;
    bool equal ;
    bool locked ;

    //------------- Forbidden Functions -------------------------------
    mutex_write_read() = delete ;
    mutex_write_read ( const mutex_write_read &) = delete ;
    mutex_write_read & operator = ( const mutex_write_read &) = delete ;

 public :
    //------------ Public Functions -------------------------
    mutex_write_read ( mutex_data1 &mw,mutex_data2 &mr, bool lock_now=true)
                       : mtx_w(mw,false), mtx_r(mr,false),locked(false)
    {   equal = ((void*) (&mw) == (void*) (&mr));
        if ( lock_now) lock() ;
    };
    ~mutex_write_read ( void)
    {   if ( locked) unlock() ;
    };

    bool try_lock ( void)
    {   assert ( not locked);
        return ( locked=(equal)? mtx_w.try_lock() :std::try_lock ( mtx_w , mtx_r ) == -1);
    };

    void lock ( void)
    {   assert ( not locked);
        (equal)? mtx_w.lock(): std::lock(  mtx_w , mtx_r );
        locked = true ;
    };

    void unlock ( void)
    {   assert ( locked);
        mtx_w.unlock() ;
        if ( not equal) mtx_r.unlock() ;
        locked = false ;
    };

    void wait_no_readers ()
    {   assert ( locked) ;
        mtx_w.wait_no_readers() ;
    };

    mutex_write<mutex_data1>& mtx_write ( void){ return mtx_w; } ;

    mutex_read<mutex_data2> & mtr_read ( void) { return mtx_r ;};
//---------------------------------------------------------------------------
};//              End of class mutex_write_read
//---------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                      C L A S S                               #     ##
//    #            M U T E X _ W R I T E _ W R I T E                 #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  mutex_write_write
/// @brief  This class implements information for to be used by
///         mutex_read_empty and mutex_write_empty in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
template <class mutex_data1 ,class mutex_data2>
class mutex_write_write
{private :
    mutex_write<mutex_data1> mtx_w1 ;
    mutex_write<mutex_data2> mtx_w2 ;
    bool equal , locked;

    //------------- Forbidden Functions -------------------------------
    mutex_write_write() = delete ;
    mutex_write_write ( const mutex_write_write &) = delete ;
    mutex_write_write & operator = ( const mutex_write_write &) = delete ;

 public :
    //------------ Public Functions -------------------------
    mutex_write_write( mutex_data1 &mw1 ,mutex_data2 &mw2, bool lock_now=true )
                       :mtx_w1(mw1,false),mtx_w2(mw2,false),locked ( false)
    {   //----------------------------- begin --------------------------------
        equal = ((void*) (&mw1) == (void*) (&mw2));
        if ( lock_now) lock() ;
    };
    ~mutex_write_write (void)
    {   if(locked) unlock();
    };
    bool try_lock ( void )
    {   assert ( not locked);
        return ( locked = (equal)? mtx_w1.try_lock() :std::try_lock (mtx_w1, mtx_w2 ) == -1);
    };
    void lock ( void)
    {   assert ( not locked );
        if (equal) mtx_w1.lock();
        else std::lock(mtx_w1,mtx_w2 );
        locked =true ;
    };

    void unlock ( void)
    {   assert( locked);
        mtx_w1.unlock() ;
        if ( not equal) mtx_w2.unlock() ;
        locked =false ;
    };
    mutex_write<mutex_data1>& mtx_write_first  ( void) { return mtx_w1; } ;

    mutex_read<mutex_data2> & mtr_write_second ( void) { return mtx_w2 ;};

    void wait_no_readers_first  ()
    {   assert (locked);
        mtx_w1.wait_no_readers() ;
    };

    void wait_no_readers_second ()
    {   assert (locked);
        if ( equal) mtx_w1.wait_no_readers() ;
        else        mtx_w2.wait_no_readers() ;
    };
//---------------------------------------------------------------------------
};//              End of class mutex_write_write
//---------------------------------------------------------------------------
//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                        C L A S S                             #     ##
//    #                M U T E X _ R E A D _ R E A D                 #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  mutex_read_read
/// @brief  This class implements information for to be used by
///         mutex_read_empty and mutex_write_empty in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
template <class mutex_data1 , class mutex_data2>
class mutex_read_read
{private :
    mutex_read<mutex_data1>  mtx_r1 ;
    mutex_read<mutex_data1>  mtx_r2 ;
    bool equal,locked ;

    //------------- Forbidden Functions -------------------------------
    mutex_read_read() = delete ;
    mutex_read_read ( const mutex_read_read &) = delete ;
    mutex_read_read & operator = ( const mutex_read_read &) = delete ;

 public :
    //------------ Public Functions -------------------------
    mutex_read_read( mutex_data1 &mr1 , mutex_data2 &mr2, bool lock_now=true ):mtx_r1(mr1,false),mtx_r2(mr2,false),locked(false)
    {   equal = ((void*) (&mr1) == (void*) (&mr2));
        if ( lock_now) lock() ;
    };
    ~mutex_read_read( void)
    {   if ( locked) unlock() ;

    }
    bool try_lock ( void)
    {   assert ( not locked);
        return ( locked = (equal)? mtx_r1.try_lock() :std::try_lock ( mtx_r1 , mtx_r2 ) == -1);
    };

    void lock ( void)
    {   assert ( not locked) ;
        (equal)? mtx_r1.lock(): std::lock( mtx_r1 , mtx_r2 );
        locked = true ;
    };

    void unlock  ( void)
    {   //----------------------- begin -------------------------------
        assert ( locked );
        mtx_r1.unlock();
        if ( equal ) mtx_r2.unlock();
        locked = false ;
    };
//---------------------------------------------------------------------------
};//               End of class mutex_read_read
//---------------------------------------------------------------------------

//***************************************************************************
};//     E N D   N A M E S P A C E   C O U N T E R T R E E
//***************************************************************************
#endif
