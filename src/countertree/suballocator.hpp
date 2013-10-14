//----------------------------------------------------------------------------
/// @file suballocator.hpp
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
#ifndef __CNTREE_ALLOC_SUBALLOCATOR_HPP
#define __CNTREE_ALLOC_SUBALLOCATOR_HPP


#include <boost/countertree/suballocator32.hpp>
#include <boost/countertree/suballocator64.hpp>
#include <boost/countertree/suballocator32_cnc.hpp>
#include <boost/countertree/suballocator64_cnc.hpp>

namespace countertree
{

//##########################################################################
//                                                                        ##
//              C L A S S E S     F O R   T H E                           ##
//                                                                        ##
//                M E T A P R O G R A M M I N G                           ##
//                                                                        ##
//##########################################################################
//
//---------------------------------------------------------------------------
/// @class select
/// @brief : This class is for the automatic selection of the suballocator32
///          or suballocator64 depending if we a re in a 32 or 64 bits
///          environment
/// @remarks
//---------------------------------------------------------------------------
template <  class Alloc, unsigned NByte  = alloc::NByte >
struct select
{   typedef suballocator32<typename filter_suballoc<Alloc>::name> my_suballoc ;
};

template < class Alloc >
struct select<Alloc,8>
{   typedef suballocator64 <typename filter_suballoc<Alloc>::name> my_suballoc ;
};

//##########################################################################
//                                                                        ##
//               C L A S S    S U B A L L O C A T O R                     ##
//                                                                        ##
//##########################################################################
//
//---------------------------------------------------------------------------
/// @class suballocator
/// @brief : This class an alias of the automatic selection of the suballocator32
///          or suballocator64 depending if we a re in a 32 or 64 bits
///          environment
/// @remarks
//-------------------------------------------------------------------------
template <  typename Allocator = std::allocator<void> >
using suballocator = typename select<Allocator>::my_suballoc ;




//##########################################################################
//                                                                        ##
//              C L A S S E S     F O R   T H E                           ##
//                                                                        ##
//                M E T A P R O G R A M M I N G                           ##
//                                                                        ##
//##########################################################################
//
//---------------------------------------------------------------------------
/// @class select_cnc
/// @brief : This class is for the automatic selection of the suballocator32
///          or suballocator64 depending if we a re in a 32 or 64 bits
///          environment
/// @remarks
//---------------------------------------------------------------------------
template <  class Alloc, unsigned NByte  = alloc::NByte >
struct select_cnc
{   typedef suballocator32_cnc<typename filter_suballoc<Alloc>::name> my_suballoc ;
};

template < class Alloc >
struct select_cnc<Alloc,8>
{   typedef suballocator64_cnc <typename filter_suballoc<Alloc>::name> my_suballoc ;
};

//##########################################################################
//                                                                        ##
//               C L A S S    S U B A L L O C A T O R                     ##
//                                                                        ##
//##########################################################################
//
//---------------------------------------------------------------------------
/// @class suballocator
/// @brief : This class an alias of the automatic selection of the suballocator32
///          or suballocator64 depending if we a re in a 32 or 64 bits
///          environment
/// @remarks
//---------------------------------------------------------------------------
template < typename Allocator = std::allocator<void> >
using suballocator_cnc = typename select_cnc<Allocator>::my_suballoc ;

//***************************************************************************
}; //     E N D    A L L O C    &  C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
