//----------------------------------------------------------------------------
/// @file   set.hpp
/// @brief  This file contains the implementation of set and multiset,
///         based on the vector_tree
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_SET_HPP
#define __COUNTERTREE_SET_HPP

#include <memory>
#include <functional>
#include <boost/countertree/myallocator.hpp>
#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/cntree_set.hpp>
#include <boost/countertree/cntree_multiset.hpp>


namespace countertree
{

namespace c_forest = countertree::forest ;
namespace c_common = countertree::common ;

//***************************************************************************
//                        S E T
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>

using set = cntree_set < value_t, false, comp_key_t, alloc_t >;


//***************************************************************************
//                        S E T _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
using set_cnc = cntree_set < value_t, true, comp_key_t, alloc_t >;



//***************************************************************************
//                      S E T _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
using set_pool = cntree_set<value_t,true,comp_key_t,suballocator<alloc_t> >;


//***************************************************************************
//                      S E T _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
using set_pool_cnc = cntree_set < value_t, true, comp_key_t, suballocator_cnc< alloc_t> >;


//***************************************************************************
//                    M U L T I S E T
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
using multiset = cntree_multiset < value_t, false, comp_key_t, alloc_t >;


//***************************************************************************
//                        M U L T I S E T _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>

using multiset_cnc = cntree_multiset <value_t,true,comp_key_t,alloc_t>;

//***************************************************************************
//                      M U L T I S E T _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>

using multiset_pool = cntree_multiset <value_t,false,comp_key_t,suballocator<alloc_t> >;

//***************************************************************************
//                      M U L T I S E T _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>
using multiset_pool_cnc = cntree_multiset <value_t,true,comp_key_t,suballocator_cnc<alloc_t> >;

//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
