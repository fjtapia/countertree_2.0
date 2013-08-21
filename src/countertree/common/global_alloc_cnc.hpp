//----------------------------------------------------------------------------
/// @file global_alloc_cnc.hpp
/// @brief : This class provide  allocate y deallocate of global memory
///          concurrently
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_COMMON_GLOBAL_ALLOC_CNC_HPP
#define __COUNTERTREE_COMMON_GLOBAL_ALLOC_CNC_HPP

#include  <boost/countertree/common/config.hpp>
#include  <boost/countertree/common/definitions.hpp>
#include  <boost/countertree/common/spinlock.hpp>
#include  <boost/countertree/common/mysingleton.hpp>
#include <new>
#include <mutex>


namespace countertree
{
namespace common
{
//##########################################################################
//                                                                        ##
//         C L A S S     G L O B A L _ A L L O C _ C N C                  ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class global_alloc_cnc
///
/// @remarks This class provide global memory, accesible to all the
///          threads, with a spinlock in order to provide concurrency
//----------------------------------------------------------------
class global_alloc_cnc
{
//*****************************************************************
//            Private data
//*****************************************************************
spinlock spl ;

//*****************************************************************
//            Private Functions
//*****************************************************************
global_alloc_cnc ( const global_alloc_cnc &) = delete;
global_alloc_cnc & operator= ( const global_alloc_cnc &) = delete;

public:
//***************************************************************************
//     Public Definitions
//***************************************************************************
typedef common::size_type		  size_type; //Quantities of elements
typedef common::difference_type   difference_type ; //Difference between two pointers

//---------------------------------------------------------------------------
//  function :global_alloc_cnc
/// @brief Constructor of the class
//---------------------------------------------------------------------------
explicit global_alloc_cnc() NOEXCEPT {};
//---------------------------------------------------------------------------
//  function : allocate
/// @brief Allocate memory
/// @param [in] cnt : Number of Bytes to alloc
/// @exception std::bad_alloc :
/// @return pointer to the allocate memory
//---------------------------------------------------------------------------
void * allocate ( size_t cnt)
{   std::unique_lock<spinlock>  ul (spl) ;
    return (void*) ::new uint8_t[cnt] ;
};
//---------------------------------------------------------------------------
//  function : deallocate
/// @brief deallocate memory
/// @param [in] p : pointer to the memory to dealloc
/// @exception std::bad_alloc
/// @return
//---------------------------------------------------------------------------
void deallocate ( void * p)
{   std::unique_lock<spinlock>  ul (spl) ;
    assert ( p != NULL);
    ::delete[] ((uint8_t *) p);
    p = NULL ;
};
//***************************************************************************
};//        E N D    G L O B A L _ A L L O C _ C N C
//***************************************************************************
//static global_alloc_cnc  glb;
static global_alloc_cnc & glb = mysingleton< global_alloc_cnc,true>::instance();
//***************************************************************************
};//              E N D    A L L O C     N A M E S P A C E
};//              E N D    C O U N T E R T R E E     N A M E S P A C E
//***************************************************************************
#endif
