//----------------------------------------------------------------------------
/// @file   map.hpp
/// @brief  This file contains the implementation of map and multimap,
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
#ifndef __COUNTERTREE_MAP_HPP
#define __COUNTERTREE_MAP_HPP

#include <memory>
#include <functional>
#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/cntree_map.hpp>
#include <boost/countertree/cntree_multimap.hpp>

namespace countertree
{
namespace c_common = countertree::common ;
namespace c_forest = countertree::forest ;


//***************************************************************************
//                             M A P
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using map = cntree_map<key_t, data_t,false, comp_key_t, alloc_t> ;


//***************************************************************************
//                        M A P _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>

using map_cnc = cntree_map<key_t, data_t,true, comp_key_t, alloc_t>  ;


//***************************************************************************
//                      M A P _ P O O L
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using map_pool = cntree_map<key_t,data_t,false,comp_key_t,suballocator<alloc_t> > ;


//***************************************************************************
//                      M A P _ P O O L _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using map_pool_cnc = cntree_map<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> > ;


//***************************************************************************
//                             M U L T I M A P
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using multimap = cntree_multimap<key_t, data_t,false, comp_key_t, alloc_t>;

//***************************************************************************
//                     M U L T I M A P _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using multimap_cnc = cntree_multimap<key_t, data_t,true, comp_key_t, alloc_t>;


//***************************************************************************
//                      M U L T I M A P _ P O O L
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using multimap_pool = cntree_multimap<key_t,data_t,false,comp_key_t,suballocator<alloc_t> >;


//***************************************************************************
//                      M U L T I M A P _ P O O L _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
using multimap_pool_cnc = cntree_multimap<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> >;


//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
