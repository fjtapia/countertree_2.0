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
#ifdef _MSC_VER
struct map : cntree_map<key_t, data_t,false, comp_key_t, alloc_t>
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_map<key_t, data_t,false, comp_key_t, alloc_t> vmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit map ( const comp_key_t& C1 = comp_key_t(),
                   const alloc_t & A= alloc_t() ) : vmap(C1,A){  };

    explicit map ( const alloc_t & A ) : vmap(A){  };

    template <class InputIterator>
    map (   InputIterator first     ,
            InputIterator last      ,
            const comp_key_t& C1 = comp_key_t() ,
            const alloc_t & A1= alloc_t()  )  :vmap (first,last, C1, A1 ){ };

    map( const map & m ): vmap ( m){};

    map(  map && m ):vmap ( std::move( m )){ };

    map( const map & m , const alloc_t & A): vmap ( m,A){ };

    template < typename alloc_t2 , bool cnc2 >
    map ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmap ( m){ };

    template <  bool cnc2 >
    map(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmap ( std::move( m)){ };

    virtual ~map(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    map  & operator= ( const map & m )
    {   vmap::operator= ( m);
        return *this ;
    };

    map  & operator= (  map && m )
    {   vmap::operator= ( std::move(m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    map & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    map & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmap::operator= ( std::move( m) );
        return *this ;
    };
};
#else
using map = cntree_map<key_t, data_t,false, comp_key_t, alloc_t> ;
#endif


//***************************************************************************
//                        M A P _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct map_cnc : cntree_map<key_t, data_t,true, comp_key_t, alloc_t>
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_map<key_t, data_t,true, comp_key_t, alloc_t>  vmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit map_cnc ( const comp_key_t& C1 = comp_key_t(),
                   const alloc_t & A= alloc_t() ) : vmap(C1,A){  };

    explicit map_cnc ( const alloc_t & A ) : vmap(A){  };

    template <class InputIterator>
    map_cnc (   InputIterator first     ,
            InputIterator last      ,
            const comp_key_t& C1 = comp_key_t() ,
            const alloc_t & A1= alloc_t()  )  :vmap (first,last, C1, A1 ){ };

    map_cnc( const map_cnc & m ): vmap ( m){};

    map_cnc(  map_cnc && m ):vmap ( std::move( m )){ };

    map_cnc( const map_cnc & m , const alloc_t & A): vmap ( m,A){ };

    template < typename alloc_t2 , bool cnc2 >
    map_cnc ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmap ( m){ };

    template <  bool cnc2 >
    map_cnc(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmap ( std::move( m)){ };

    virtual ~map_cnc(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    map_cnc  & operator= ( const map_cnc & m )
    {   vmap::operator= ( m);
        return *this ;
    };

    map_cnc  & operator= (  map_cnc && m )
    {   vmap::operator= ( std::move(m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    map_cnc & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    map_cnc & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmap::operator= ( std::move( m) );
        return *this ;
    };
};
#else
using map_cnc = cntree_map<key_t, data_t,true, comp_key_t, alloc_t>  ;
#endif


//***************************************************************************
//                      M A P _ P O O L
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct map_pool : cntree_map<key_t,data_t,false,comp_key_t,suballocator<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator<alloc_t>  map_alloc_t ;
    typedef cntree_map<key_t,data_t,false,comp_key_t,suballocator<alloc_t> > vmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit map_pool ( const comp_key_t& C1 = comp_key_t(),
                   const map_alloc_t & A= map_alloc_t() ) : vmap(C1,A){  };

    explicit map_pool ( const alloc_t & A ) : vmap(A){  };

    template <class InputIterator>
    map_pool (   InputIterator first     ,
            InputIterator last      ,
            const comp_key_t& C1 = comp_key_t() ,
            const map_alloc_t & A1= map_alloc_t()  )  :vmap (first,last, C1, A1 ){ };

    map_pool( const map_pool & m ): vmap ( m){};

    map_pool(  map_pool && m ):vmap ( std::move( m )){ };

    map_pool( const map_pool & m , const alloc_t & A): vmap ( m,A){ };

    template < typename alloc_t2 , bool cnc2 >
    map_pool ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmap ( m){ };

    template <  bool cnc2 >
    map_pool(  cntree_map<key_t,data_t,cnc2,comp_key_t,map_alloc_t> && m ):vmap ( std::move( m)){ };

    virtual ~map_pool(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    map_pool  & operator= ( const map_pool & m )
    {   vmap::operator= ( m);
        return *this ;
    };

    map_pool  & operator= (  map_pool && m )
    {   vmap::operator= ( std::move(m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    map_pool & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    map_pool & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,map_alloc_t> && m )
    {   vmap::operator= ( std::move( m) );
        return *this ;
    };
};
#else
using map_pool = cntree_map<key_t,data_t,false,comp_key_t,suballocator<alloc_t> > ;
#endif


//***************************************************************************
//                      M A P _ P O O L _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct map_pool_cnc : cntree_map<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator_cnc<alloc_t>  map_alloc_t ;
    typedef cntree_map<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> > vmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit map_pool_cnc ( const comp_key_t& C1 = comp_key_t(),
                   const map_alloc_t & A= map_alloc_t() ) : vmap(C1,A){  };

    explicit map_pool_cnc ( const alloc_t & A ) : vmap(A){  };

    template <class InputIterator>
    map_pool_cnc (   InputIterator first     ,
            InputIterator last      ,
            const comp_key_t& C1 = comp_key_t() ,
            const map_alloc_t & A1= map_alloc_t()  )  :vmap (first,last, C1, A1 ){ };

    map_pool_cnc( const map_pool_cnc & m ): vmap ( m){};

    map_pool_cnc(  map_pool_cnc && m ):vmap ( std::move( m )){ };

    map_pool_cnc( const map_pool_cnc & m , const alloc_t & A): vmap ( m,A){ };

    template < typename alloc_t2 , bool cnc2 >
    map_pool_cnc ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmap ( m){ };

    template <  bool cnc2 >
    map_pool_cnc(  cntree_map<key_t,data_t,cnc2,comp_key_t,map_alloc_t> && m ):vmap ( std::move( m)){ };

    virtual ~map_pool_cnc(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    map_pool_cnc  & operator= ( const map_pool_cnc & m )
    {   vmap::operator= ( m);
        return *this ;
    };

    map_pool_cnc  & operator= (  map_pool_cnc && m )
    {   vmap::operator= ( std::move(m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    map_pool_cnc & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    map_pool_cnc & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,map_alloc_t> && m )
    {   vmap::operator= ( std::move( m) );
        return *this ;
    };
};
#else
using map_pool_cnc = cntree_map<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> > ;
#endif

//***************************************************************************
//                             M U L T I M A P
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multimap : cntree_multimap<key_t, data_t,false, comp_key_t, alloc_t>
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_multimap<key_t, data_t,false, comp_key_t, alloc_t> vmmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multimap ( const comp_key_t& C1 = comp_key_t(),
                        const alloc_t & A= alloc_t() ) : vmmap(C1,A){  };

    explicit multimap ( const alloc_t & A ) : vmmap (A){  };

    multimap( const multimap & m ): vmmap ( m){ };

    multimap(  multimap && m ): vmmap ( std::move ( m)){ };

    template <class InputIterator>
    multimap ( InputIterator first  ,
               InputIterator last ,
               const comp_key_t& C1 = comp_key_t() ,
               const alloc_t & A1= alloc_t()  )  : vmmap (first, last, C1, A1 ){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template <  bool cnc2 >
    multimap(  cntree_multimap<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmmap (std::move (m)){ };

    template <  bool cnc2 >
    multimap(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmmap (std::move (m)){ };

    virtual ~multimap(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multimap  & operator= ( const multimap &m)
    {   vmmap::operator= ( m);
        return *this ;
    };

    multimap  & operator= (  multimap &&m)
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap & operator= ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    multimap & operator= ( cntree_multimap<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template <  bool cnc2 >
    multimap & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };
};
#else
using multimap = cntree_multimap<key_t, data_t,false, comp_key_t, alloc_t>;
#endif

//***************************************************************************
//                     M U L T I M A P _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multimap_cnc : cntree_multimap<key_t, data_t,true, comp_key_t, alloc_t>
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_multimap<key_t, data_t,true, comp_key_t, alloc_t> vmmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multimap_cnc ( const comp_key_t& C1 = comp_key_t(),
                        const alloc_t & A= alloc_t() ) : vmmap(C1,A){  };

    explicit multimap_cnc ( const alloc_t & A ) : vmmap (A){  };

    multimap_cnc( const multimap_cnc & m ): vmmap ( m){ };

    multimap_cnc(  multimap_cnc && m ): vmmap ( std::move ( m)){ };

    template <class InputIterator>
    multimap_cnc ( InputIterator first  ,
               InputIterator last ,
               const comp_key_t& C1 = comp_key_t() ,
               const alloc_t & A1= alloc_t()  )  : vmmap (first, last, C1, A1 ){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_cnc ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_cnc ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template <  bool cnc2 >
    multimap_cnc(  cntree_multimap<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmmap (std::move (m)){ };

    template <  bool cnc2 >
    multimap_cnc(  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m ):vmmap (std::move (m)){ };

    virtual ~multimap_cnc(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multimap_cnc  & operator= ( const multimap_cnc &m)
    {   vmmap::operator= ( m);
        return *this ;
    };

    multimap_cnc  & operator= (  multimap_cnc &&m)
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_cnc & operator= ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_cnc & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    multimap_cnc & operator= ( cntree_multimap<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template <  bool cnc2 >
    multimap_cnc & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };
};
#else
using multimap_cnc = cntree_multimap<key_t, data_t,true, comp_key_t, alloc_t>;
#endif

//***************************************************************************
//                      M U L T I M A P _ P O O L
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multimap_pool : cntree_multimap<key_t,data_t,false,comp_key_t,suballocator<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator<alloc_t> mmap_alloc_t ;
    typedef cntree_multimap<key_t,data_t,false,comp_key_t,suballocator<alloc_t> > vmmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multimap_pool ( const comp_key_t& C1 = comp_key_t(),
                        const mmap_alloc_t & A= mmap_alloc_t() ) : vmmap(C1,A){  };

    explicit multimap_pool ( const alloc_t & A ) : vmmap (A){  };

    multimap_pool( const multimap_pool & m ): vmmap ( m){ };

    multimap_pool(  multimap_pool && m ): vmmap ( std::move ( m)){ };

    template <class InputIterator>
    multimap_pool ( InputIterator first  ,
               InputIterator last ,
               const comp_key_t& C1 = comp_key_t() ,
               const mmap_alloc_t & A1= mmap_alloc_t()  )  : vmmap (first, last, C1, A1 ){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template <  bool cnc2 >
    multimap_pool(  cntree_multimap<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m ):vmmap (std::move (m)){ };

    template <  bool cnc2 >
    multimap_pool(  cntree_map<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m ):vmmap (std::move (m)){ };

    virtual ~multimap_pool(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multimap_pool  & operator= ( const multimap_pool &m)
    {   vmmap::operator= ( m);
        return *this ;
    };

    multimap_pool  & operator= (  multimap_pool &&m)
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool & operator= ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    multimap_pool & operator= ( cntree_multimap<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template <  bool cnc2 >
    multimap_pool & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };
};
#else
using multimap_pool = cntree_multimap<key_t,data_t,false,comp_key_t,suballocator<alloc_t> >;
#endif

//***************************************************************************
//                      M U L T I M A P _ P O O L _ C N C
//***************************************************************************
template
<   typename key_t,
    typename data_t,
    class comp_key_t = std::less<key_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multimap_pool_cnc : cntree_multimap<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator_cnc<alloc_t> mmap_alloc_t ;
    typedef cntree_multimap<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> > vmmap;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multimap_pool_cnc ( const comp_key_t& C1 = comp_key_t(),
                        const mmap_alloc_t & A= mmap_alloc_t() ) : vmmap(C1,A){  };

    explicit multimap_pool_cnc ( const alloc_t & A ) : vmmap (A){  };

    multimap_pool_cnc( const multimap_pool_cnc & m ): vmmap ( m){ };

    multimap_pool_cnc(  multimap_pool_cnc && m ): vmmap ( std::move ( m)){ };

    template <class InputIterator>
    multimap_pool_cnc ( InputIterator first  ,
                        InputIterator last ,
                        const comp_key_t& C1 = comp_key_t() ,
                        const mmap_alloc_t & A1= mmap_alloc_t()  )  : vmmap (first, last, C1, A1 ){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool_cnc ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool_cnc ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m ):vmmap (m){ };

    template <  bool cnc2 >
    multimap_pool_cnc(  cntree_multimap<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m ):vmmap (std::move (m)){ };

    template <  bool cnc2 >
    multimap_pool_cnc(  cntree_map<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m ):vmmap (std::move (m)){ };

    virtual ~multimap_pool_cnc(){ };

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multimap_pool_cnc  & operator= ( const multimap_pool_cnc &m)
    {   vmmap::operator= ( m);
        return *this ;
    };

    multimap_pool_cnc  & operator= (  multimap_pool_cnc &&m)
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool_cnc & operator= ( const cntree_multimap <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multimap_pool_cnc & operator= ( const cntree_map <key_t,data_t,cnc2,comp_key_t,alloc_t2>& m )
    {   vmmap::operator= ( m);
        return *this ;
    };

    template <  bool cnc2 >
    multimap_pool_cnc & operator= ( cntree_multimap<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };

    template <  bool cnc2 >
    multimap_pool_cnc & operator= (  cntree_map<key_t,data_t,cnc2,comp_key_t,mmap_alloc_t> && m )
    {   vmmap::operator= ( std::move ( m));
        return *this ;
    };
};
#else
using multimap_pool_cnc = cntree_multimap<key_t, data_t,true,comp_key_t,suballocator_cnc<alloc_t> >;
#endif

//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
