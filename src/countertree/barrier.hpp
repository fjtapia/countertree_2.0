//----------------------------------------------------------------------------
/// @file   barrier.hpp
/// @brief  This file contains the implementation of the barriers for the single
///         and the concurrent version of the countertree
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_BARRIER_HPP
#define __COUNTERTREE_FOREST_BARRIER_HPP

#include <memory>
#include <functional>
#include <atomic>
#include <mutex>
#include <thread>


namespace countertree
{

//---------------------------------------------------------------------------
/// @class  barrier_data_cnc
/// @brief  This class implements information for to be used by
///         barrier_read_cnc and barrier_modify_cnc in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
struct barrier_data_cnc
{   std::recursive_mutex M ;
    std::atomic_ulong NR ;
 #ifdef _MSC_VER
	barrier_data_cnc ( void)
	{   NR = 0 ;
	};
#else
    barrier_data_cnc ( void) : NR( 0 ) {};
#endif
};
//---------------------------------------------------------------------------
/// @class  barrier_read_cnc
/// @brief  This class implements the barrier for the function
///         which read the vector_tree\n
/// @remarks
//---------------------------------------------------------------------------
class barrier_read_cnc
{private :
    //--------------- Variables ---------------
    std::unique_lock <std::recursive_mutex> UL ;
    std::atomic_ulong &NR ;

    //------------- Forbidden Functions -----------------------------
    //barrier_read_cnc() = delete ;
    //barrier_read_cnc ( const barrier_read_cnc &) = delete ;
    //barrier_read_cnc & operator = ( const barrier_read_cnc &) = delete ;
    barrier_read_cnc()  ;
    barrier_read_cnc ( const barrier_read_cnc &)  ;
    barrier_read_cnc & operator = ( const barrier_read_cnc &)  ;

 public :
    //------------ Public Functions ------------------------
    barrier_read_cnc( barrier_data_cnc & BDC)
    :UL(BDC.M, std::defer_lock), NR(BDC.NR){ ++NR ;};

    ~barrier_read_cnc ()  { --NR; };
}; // End of class barrier_read

//-------------------------------------------------------------
/// @class  barrier_modify
/// @brief  This class implements the barrier for the function
///         which modify the vector_tree_cnc\n
/// @remarks
//----------------------------------------------------------------
class barrier_modify_cnc
{private :
    //----------------- Variables ---------------------
    std::unique_lock <std::recursive_mutex> UL ;
    std::atomic_ulong &NR ;

    //----------- Forbidden Functions ----------------------------
    //barrier_modify_cnc() = delete ;
    //barrier_modify_cnc ( const barrier_modify_cnc &) = delete ;
    //barrier_modify_cnc & operator = ( const barrier_modify_cnc &) = delete ;
    barrier_modify_cnc()  ;
    barrier_modify_cnc ( const barrier_modify_cnc &)  ;
    barrier_modify_cnc & operator = ( const barrier_modify_cnc &)  ;

 public :
    barrier_modify_cnc (barrier_data_cnc &BDC):UL(BDC.M),NR(BDC.NR){} ;

    void wait_no_readers ()
    {   //while ( NR.load ( std::memory_order_acquire) != 0);
        while ( NR.load ( std::memory_order_acquire) != 0)
            std::this_thread::yield() ;
    };
    ~barrier_modify_cnc() {  };
};

//---------------------------------------------------------------------------
/// @class  barrier_data_empty
/// @brief  This class implements information for to be used by
///         barrier_read_empty and barrier_modify_empty in order to block the code\n
/// @remarks
//---------------------------------------------------------------------------
struct barrier_data_empty {   };
//---------------------------------------------------------------------------
/// @class  barrier_read_empty
/// @brief  This class implements the barrier for the function
///         which read the vector_tree\n
/// @remarks
//---------------------------------------------------------------------------
class barrier_read_empty
{private :
    //------------- Forbidden Functions -------------------------------
    //barrier_read_empty() = delete ;
    //barrier_read_empty ( const barrier_read_empty &) = delete ;
    //barrier_read_empty & operator = ( const barrier_read_empty &) = delete ;
    barrier_read_empty()  ;
    barrier_read_empty ( const barrier_read_empty &)  ;
    barrier_read_empty & operator = ( const barrier_read_empty &)  ;

 public :
    //------------ Public Functions -------------------------
    barrier_read_empty( barrier_data_empty & ) { } ;
    ~barrier_read_empty () { };
}; // End of class barrier_read_empty

//---------------------------------------------------------------------------
/// @class  barrier_modify_empty
/// @brief  This class implements the barrier for the function
///         which modify the vector_tree_cnc_cnc\n
/// @remarks
//---------------------------------------------------------------------------
class barrier_modify_empty
{private :
    //----------- Forbidden Functions -----------------------------
    //barrier_modify_empty() = delete ;
    //barrier_modify_empty ( const barrier_modify_empty &) = delete ;
    //barrier_modify_empty & operator = ( const barrier_modify_empty &) = delete ;
    barrier_modify_empty()  ;
    barrier_modify_empty ( const barrier_modify_empty &)  ;
    barrier_modify_empty & operator = ( const barrier_modify_empty &)  ;

 public :
    barrier_modify_empty (barrier_data_empty &){} ;
    void wait_no_readers () {   };
    ~barrier_modify_empty() {  };
};
//---------------------------------------------------------------------------
/// @class  config_barrier
/// @brief  This class implements the barrier  selector depending of the
///         concurrency ( cnc) of the data structure\n
//
/// @remarks
//---------------------------------------------------------------------------
template <bool is_concurrent> struct config_barrier ;

template < >  struct config_barrier <true>
{   typedef barrier_data_cnc      barrier_data ;
    typedef barrier_read_cnc      barrier_read ;
    typedef barrier_modify_cnc    barrier_modify ;
};
template < > struct config_barrier < false>
{   typedef barrier_data_empty      barrier_data ;
    typedef barrier_read_empty      barrier_read ;
    typedef barrier_modify_empty    barrier_modify ;
};
//***************************************************************************
};//     E N D   N A M E S P A C E   C O U N T E R T R E E
//***************************************************************************
#endif
