//----------------------------------------------------------------------------
/// @file filter.hpp
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
#ifndef __COUNTERTREE_FOREST_FILTER_HPP
#define __COUNTERTREE_FOREST_FILTER_HPP

#include <functional>
#include <utility>

namespace countertree
{

//-------------------------------------------------------------
/// @class  filter_set
/// @brief This class is a filter for to extract the key from
///        the value
///        Consideer 1 value_t = 1 key_t + 1 data_t
///        In the set the data_t don't exist and 1 value_t = 1 key_t
///
/// @remarks
//----------------------------------------------------------------
template <class key_t , class value_t >
struct filter_set
{   inline const key_t & operator () ( const value_t &V)const
    {   return V ;
    };
};


//-------------------------------------------------------------
/// @class  filter_map
/// @brief This class is a filter for to extract the key from
///        the value
///        Consideer 1 value_t = 1 key_t + 1 data_t
///        In the map the value_t is a pair<const key_t, data_t>
///        and  the key_ is value_t.first
/// @remarks
//----------------------------------------------------------------
template <class key_t , class value_t >
struct filter_map
{   inline const key_t & operator () ( const value_t &V)const
    {   return V.first ;
    };
};

//-------------------------------------------------------------
/// @class  comp_pair
/// @brief This class is only for to provide an object to compare
///        two objects value_type (pair<const class1, class2> of
///        the map and multimap
/// @remarks It is used by the function value_comp
//----------------------------------------------------------------
template <class key_t,class data_t,class comp_t=std::less<key_t> >
struct comp_pair
{
    //--------------------- Definitions ----------------------
    typedef std::pair <const key_t , data_t > value_type ;
    //--------------------- Variables-------------------------
    comp_t C ;
    //--------------------- Functions ------------------------
    comp_pair ( const comp_t &C1 = comp_t()):C(C1){} ;

    inline bool operator ()( const value_type &V1,const value_type &V2)
    {   return C ( V1.first, V2.first);
    };
};

};//----------------------------------- end namespace cntree -----------------
#endif
