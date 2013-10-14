//----------------------------------------------------------------------------
/// @file filter_allocator.hpp
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
#ifndef __COUNTERTREE_ALLOC_FILTER_SUBALLOC_HPP
#define __COUNTERTREE_ALLOC_FILTER_SUBALLOC_HPP

//#include <boost/countertree/suballocator32.hpp>
//#include <boost/countertree/suballocator64.hpp>
//#include <boost/countertree/suballocator32_cnc.hpp>
//#include <boost/countertree/suballocator64_cnc.hpp>


namespace countertree
{

template < typename Allocator > class suballocator32 ;
template < typename Allocator > class suballocator64 ;
template < typename Allocator > class suballocator32_cnc ;
template < typename Allocator > class suballocator64_cnc ;

//##########################################################################
//                                                                        ##
//          C L A S S       F I L T E R _ S U B A L L O C                 ##
//               ( M e t a p r o g r a m m i n g )                        ##
//                                                                        ##
//##########################################################################
//-------------------------------------------------------------
/// @class filter_suballoc
///
/// @remarks This class is for prevent the passing of a suballocator
///          as template parameter for other suballocator
//----------------------------------------------------------------
template < class Allocator >
struct filter_suballoc
{   typedef Allocator name ;
};

template <class U_allocator >
struct filter_suballoc <suballocator32_cnc <U_allocator > >
{   typedef U_allocator name ;
};

template <class U_allocator >
struct filter_suballoc <suballocator32 <U_allocator > >
{   typedef U_allocator name ;
};

template <class U_allocator >
struct filter_suballoc < suballocator64_cnc < U_allocator > >
{   typedef U_allocator name ;
};

template <class U_allocator >
struct filter_suballoc < suballocator64 < U_allocator > >
{   typedef U_allocator name ;
};


//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
