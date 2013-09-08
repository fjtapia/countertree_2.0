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
#ifndef __CNTREE_SUBALLOCATOR_HPP
#define __CNTREE_SUBALLOCATOR_HPP

#include <boost/countertree/alloc/suballocator.hpp>
#include <boost/countertree/myallocator.hpp>

namespace countertree
{
namespace c_alloc = countertree::alloc ;


//***************************************************************************
//                  S U B A L L O C A T O R
//***************************************************************************
using c_alloc::suballocator ;
//template
// < typename Allocator = myallocator<void> >
// using suballocator = typename c_alloc::select<false,Allocator>::my_suballoc ;

//***************************************************************************
//                 S U B A L L O C A T O R _ C N C
//***************************************************************************
using c_alloc::suballocator_cnc ;
//template
// < typename Allocator = myallocator_cnc<void> >
// using suballocator_cnc = typename c_alloc::select<true,Allocator>::my_suballoc ;

//***************************************************************************
//                  S U B A L L O C A T O R 3 2
//***************************************************************************
using c_alloc::suballocator32 ;
//template
// < typename Allocator = myallocator<void> >
// using suballocator32 = typename c_alloc::suballocator32<false,Allocator> ;

//***************************************************************************
//                  S U B A L L O C A T O R 3 2 _ C N C
//***************************************************************************
using c_alloc::suballocator32_cnc ;
// template
// < typename Allocator = myallocator_cnc<void> >
// using suballocator32_cnc = typename c_alloc::suballocator32<true,Allocator> ;

//***************************************************************************
//                  S U B A L L O C A T O R 6 4
//***************************************************************************
using c_alloc::suballocator64 ;
// template
// < typename Allocator = myallocator<void> >
// using suballocator64 = typename c_alloc::suballocator64<false,Allocator> ;

//***************************************************************************
//                  S U B A L L O C A T O R 6 4 _ C N C
//***************************************************************************
using c_alloc::suballocator64_cnc ;
// template
// < typename Allocator = myallocator_cnc<void> >
// using suballocator64_cnc = typename c_alloc::suballocator64<true,Allocator> ;

//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
