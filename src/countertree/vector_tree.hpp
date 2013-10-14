//----------------------------------------------------------------------------
/// @file   vector_tree.hpp
/// @brief  This file contains the implementation of the vector_tree
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_VECTOR_TREE_HPP
#define __COUNTERTREE_VECTOR_TREE_HPP
#include <memory>
#include <functional>
#include <boost/countertree/suballocator.hpp>
#include <boost/countertree/cntree_vector.hpp>
#include <boost/countertree/forest/iterator.hpp>

namespace c_forest = countertree::forest ;

namespace countertree
{
using std::allocator ;
using c_forest::iterator ;
using c_forest::const_iterator;
using c_forest::reverse_iterator;
using c_forest::const_reverse_iterator;


//***************************************************************************
//             V E C T O R _ T R E E
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void >
>
using vector_tree = cntree_vector < value_t, false, alloc_t >;

//***************************************************************************
//             V E C T O R _ T R E E _ C N C
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void >
>
using vector_tree_cnc = cntree_vector <value_t,true,alloc_t >;


//***************************************************************************
//             V E C T O R _ T R E E _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void>
>
using vector_tree_pool = cntree_vector<value_t,false,suballocator<alloc_t> >;


//***************************************************************************
//             V E C T O R _ T R E E _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void>
>
using vector_tree_pool_cnc = cntree_vector<value_t,true,suballocator_cnc<alloc_t> >;


//***************************************************************************
};//            E N D   C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
