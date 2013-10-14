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


//***************************************************************************
//                 S U B A L L O C A T O R _ C N C
//***************************************************************************
using c_alloc::suballocator_cnc ;

//***************************************************************************
//                  S U B A L L O C A T O R 3 2
//***************************************************************************
using c_alloc::suballocator32 ;

//***************************************************************************
//                  S U B A L L O C A T O R 3 2 _ C N C
//***************************************************************************
using c_alloc::suballocator32_cnc ;


//***************************************************************************
//                  S U B A L L O C A T O R 6 4
//***************************************************************************
using c_alloc::suballocator64 ;


//***************************************************************************
//                  S U B A L L O C A T O R 6 4 _ C N C
//***************************************************************************
using c_alloc::suballocator64_cnc ;


//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
