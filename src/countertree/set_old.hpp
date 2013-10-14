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
#ifdef _MSC_VER
struct set: cntree_set < value_t, false, comp_key_t, alloc_t >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_set < value_t, false, comp_key_t, alloc_t > vset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit set ( const comp_key_t &C1=comp_key_t(),
                   const alloc_t  &A1= alloc_t ()) : vset( C1,A1){  };

    template <class InputIterator>
    set (   InputIterator first,
            InputIterator last,
            const comp_key_t& C1=comp_key_t(),
            const alloc_t  &A1=alloc_t ()):vset (first,last,C1,A1){ };

    set ( const set & x ):vset (x){};

    set (  set && x ):vset ( std::move(x)){}

    template <bool cnc2 >
    set (  cntree_set <value_t,cnc2,comp_key_t,alloc_t> && x ):vset ( std::move(x)){};

    template < typename alloc_t2 , bool cnc2 >
    set ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vset (x){};

    virtual ~set(void ){} ;

    //-----------------------------------------------------------------------
    //                       O P E R A T O R =
    //-----------------------------------------------------------------------
    set & operator = ( const set &S)
    {   vset::operator= ( S);
        return *this ;
    }
    set & operator = ( set &&S)
    {   vset::operator= ( std::move(S));
        return *this ;
    }

    template < typename alloc_t2 , bool cnc2 >
    set & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    set & operator= (  cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vset::operator= ( std::move (x) );
        return *this ;
    };
};
#else
using set = cntree_set < value_t, false, comp_key_t, alloc_t >;
#endif

//***************************************************************************
//                        S E T _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct set_cnc: cntree_set < value_t, true, comp_key_t, alloc_t >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_set < value_t, true, comp_key_t, alloc_t > vset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit set_cnc ( const comp_key_t &C1=comp_key_t(),
                   const alloc_t  &A1= alloc_t ()) : vset( C1,A1){  };

    template <class InputIterator>
    set_cnc (   InputIterator first,
                InputIterator last,
                const comp_key_t& C1=comp_key_t(),
                const alloc_t  &A1=alloc_t ()):vset (first,last,C1,A1){ };

    set_cnc ( const set_cnc & x ):vset (x){};

    set_cnc (  set_cnc && x ):vset ( std::move(x)){}

    template <bool cnc2 >
    set_cnc (  cntree_set <value_t,cnc2,comp_key_t,alloc_t> && x ):vset ( std::move(x)){};

    template < typename alloc_t2 , bool cnc2 >
    set_cnc ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vset (x){};

    virtual ~set_cnc(void ){} ;

    //-----------------------------------------------------------------------
    //                       O P E R A T O R =
    //-----------------------------------------------------------------------
    set_cnc & operator = ( const set_cnc &S)
    {   vset::operator= ( S);
        return *this ;
    }
    set_cnc & operator = ( set_cnc &&S)
    {   vset::operator= ( std::move(S));
        return *this ;
    }

    template < typename alloc_t2 , bool cnc2 >
    set_cnc & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    set_cnc & operator= (  cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vset::operator= ( std::move (x) );
        return *this ;
    };
};
#else
using set_cnc = cntree_set < value_t, true, comp_key_t, alloc_t >;
#endif


//***************************************************************************
//                      S E T _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct set_pool: cntree_set<value_t,true,comp_key_t,suballocator<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator<alloc_t> set_alloc_t ;
    typedef cntree_set<value_t,true,comp_key_t,set_alloc_t > vset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit set_pool ( const comp_key_t &C1=comp_key_t(),
                        const set_alloc_t  &A1= set_alloc_t ()) : vset( C1,A1){  };

    template <class InputIterator>
    set_pool (  InputIterator first,
                InputIterator last,
                const comp_key_t& C1=comp_key_t(),
                const set_alloc_t  &A1=set_alloc_t ()):vset (first,last,C1,A1){ };

    set_pool ( const set_pool & x ):vset (x){};

    set_pool (  set_pool && x ):vset ( std::move(x)){}

    template <bool cnc2 >
    set_pool (  cntree_set <value_t,cnc2,comp_key_t,set_alloc_t> && x ):vset ( std::move(x)){};

    template < typename alloc_t2 , bool cnc2 >
    set_pool ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vset (x){};

    virtual ~set_pool(void ){} ;

    //-----------------------------------------------------------------------
    //                       O P E R A T O R =
    //-----------------------------------------------------------------------
    set_pool & operator = ( const set_pool &S)
    {   vset::operator= ( S);
        return *this ;
    }
    set_pool & operator = ( set_pool &&S)
    {   vset::operator= ( std::move(S));
        return *this ;
    }

    template < typename alloc_t2 , bool cnc2 >
    set_pool & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    set_pool & operator= (  cntree_set <value_t,cnc2,comp_key_t,set_alloc_t>&& x )
    {   vset::operator= ( std::move (x) );
        return *this ;
    };
};
#else
using set_pool = cntree_set<value_t,true,comp_key_t,suballocator<alloc_t> >;
#endif

//***************************************************************************
//                      S E T _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct set_pool_cnc: cntree_set < value_t, true, comp_key_t, suballocator_cnc< alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator_cnc<alloc_t> set_alloc_t ;
    typedef cntree_set < value_t, true, comp_key_t, suballocator_cnc< alloc_t> > vset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit set_pool_cnc ( const comp_key_t &C1=comp_key_t(),
                   const set_alloc_t  &A1= set_alloc_t ()) : vset( C1,A1){  };

    template <class InputIterator>
    set_pool_cnc (  InputIterator first,
                    InputIterator last,
                    const comp_key_t& C1=comp_key_t(),
                    const set_alloc_t  &A1=set_alloc_t ()):vset (first,last,C1,A1){ };

    set_pool_cnc ( const set_pool_cnc & x ):vset (x){};

    set_pool_cnc (  set_pool_cnc && x ):vset ( std::move(x)){}

    template <bool cnc2 >
    set_pool_cnc (  cntree_set <value_t,cnc2,comp_key_t,set_alloc_t> && x ):vset ( std::move(x)){};

    template < typename alloc_t2 , bool cnc2 >
    set_pool_cnc ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vset (x){};

    virtual ~set_pool_cnc(void ){} ;

    //-----------------------------------------------------------------------
    //                       O P E R A T O R =
    //-----------------------------------------------------------------------
    set_pool_cnc & operator = ( const set_pool_cnc &S)
    {   vset::operator= ( S);
        return *this ;
    }
    set_pool_cnc & operator = ( set_pool_cnc &&S)
    {   vset::operator= ( std::move(S));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    set_pool_cnc & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    set_pool_cnc & operator= (  cntree_set <value_t,cnc2,comp_key_t,set_alloc_t>&& x )
    {   vset::operator= ( std::move (x) );
        return *this ;
    };
};
#else
using set_pool_cnc = cntree_set < value_t, true, comp_key_t, suballocator_cnc< alloc_t> >;
#endif


//***************************************************************************
//                    M U L T I S E T
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multiset : cntree_multiset < value_t, false, comp_key_t, alloc_t >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_multiset <value_t,false,comp_key_t,alloc_t> vmset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multiset ( const comp_key_t &C1=comp_key_t(),
                        const alloc_t  &A1= alloc_t ()): vmset( C1,A1){  };

    template <class InputIterator>
    multiset (  InputIterator first,
                InputIterator last,
                const comp_key_t& C1=comp_key_t(),
                const alloc_t  &A1=alloc_t ()):vmset(first,last,C1,A1){ };

    multiset ( const multiset & x ):vmset( x){ };

    multiset (  multiset && x ): vmset ( std::move( x)){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template <bool cnc2 >
    multiset (cntree_multiset <value_t,cnc2,comp_key_t,alloc_t>&& x ):vmset(std::move(x)){ };

    template <bool cnc2 >
    multiset (cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x ):vmset(std::move(x)){ };

    virtual ~multiset(void ){} ;

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multiset & operator = ( const multiset &S)
    {   vmset::operator= ( S);
        return *this ;
    };
    multiset  & operator = (multiset &&S)
    {   vmset::operator= ( std::move(S));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset & operator = ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    multiset & operator= (  cntree_multiset <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
    template <bool cnc2 >
    multiset & operator= ( cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
};
#else
using multiset = cntree_multiset < value_t, false, comp_key_t, alloc_t >;
#endif


//***************************************************************************
//                        M U L T I S E T _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multiset_cnc : cntree_multiset <value_t,true,comp_key_t,alloc_t>
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_multiset <value_t,true,comp_key_t,alloc_t> vmset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multiset_cnc ( const comp_key_t &C1=comp_key_t(),
                        const alloc_t  &A1= alloc_t ()): vmset( C1,A1){  };

    template <class InputIterator>
    multiset_cnc (  InputIterator first,
                InputIterator last,
                const comp_key_t& C1=comp_key_t(),
                const alloc_t  &A1=alloc_t ()):vmset(first,last,C1,A1){ };

    multiset_cnc ( const multiset_cnc & x ):vmset( x){ };

    multiset_cnc (  multiset_cnc && x ): vmset ( std::move( x)){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_cnc ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_cnc ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template <bool cnc2 >
    multiset_cnc (cntree_multiset <value_t,cnc2,comp_key_t,alloc_t>&& x ):vmset(std::move(x)){ };

    template <bool cnc2 >
    multiset_cnc (cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x ):vmset(std::move(x)){ };

    virtual ~multiset_cnc(void ){} ;

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multiset_cnc & operator = ( const multiset_cnc &S)
    {   vmset::operator= ( S);
        return *this ;
    };
    multiset_cnc  & operator = (multiset_cnc &&S)
    {   vmset::operator= ( std::move(S));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_cnc & operator = ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_cnc & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    multiset_cnc & operator= (  cntree_multiset <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
    template <bool cnc2 >
    multiset_cnc & operator= ( cntree_set <value_t,cnc2,comp_key_t,alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
};
#else
using multiset_cnc = cntree_multiset <value_t,true,comp_key_t,alloc_t>;
#endif

//***************************************************************************
//                      M U L T I S E T _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multiset_pool : cntree_multiset <value_t,false,comp_key_t,suballocator<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator<alloc_t> mset_alloc_t ;
    typedef cntree_multiset <value_t,false,comp_key_t,mset_alloc_t > vmset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multiset_pool ( const comp_key_t &C1=comp_key_t(),
                        const mset_alloc_t  &A1= mset_alloc_t ()): vmset( C1,A1){  };

    template <class InputIterator>
    multiset_pool ( InputIterator first,
                    InputIterator last,
                    const comp_key_t& C1=comp_key_t(),
                    const mset_alloc_t  &A1=mset_alloc_t ()):vmset(first,last,C1,A1){ };

    multiset_pool ( const multiset_pool & x ):vmset( x){ };

    multiset_pool (  multiset_pool && x ): vmset ( std::move( x)){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template <bool cnc2 >
    multiset_pool (cntree_multiset <value_t,cnc2,comp_key_t,mset_alloc_t>&& x ):vmset(std::move(x)){ };

    template <bool cnc2 >
    multiset_pool (cntree_set <value_t,cnc2,comp_key_t,mset_alloc_t>&& x ):vmset(std::move(x)){ };

    virtual ~multiset_pool(void ){} ;

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multiset_pool & operator = ( const multiset_pool &S)
    {   vmset::operator= ( S);
        return *this ;
    };
    multiset_pool  & operator = (multiset_pool &&S)
    {   vmset::operator= ( std::move(S));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool & operator = ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    multiset_pool & operator= (  cntree_multiset <value_t,cnc2,comp_key_t,mset_alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
    template <bool cnc2 >
    multiset_pool & operator= ( cntree_set <value_t,cnc2,comp_key_t,mset_alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
};
#else
using multiset_pool = cntree_multiset <value_t,false,comp_key_t,suballocator<alloc_t> >;
#endif

//***************************************************************************
//                      M U L T I S E T _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename comp_key_t = std::less<value_t>,
    typename alloc_t    = cntree_allocator<void>
>
#ifdef _MSC_VER
struct multiset_pool_cnc : cntree_multiset <value_t,true,comp_key_t,suballocator_cnc<alloc_t> >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef suballocator_cnc<alloc_t>   mset_alloc_t ;
    typedef cntree_multiset <value_t,true,comp_key_t,mset_alloc_t > vmset;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit multiset_pool_cnc ( const comp_key_t &C1=comp_key_t(),
                                const mset_alloc_t  &A1= mset_alloc_t ()): vmset( C1,A1){  };

    template <class InputIterator>
    multiset_pool_cnc (  InputIterator first,
                InputIterator last,
                const comp_key_t& C1=comp_key_t(),
                const mset_alloc_t  &A1=mset_alloc_t ()):vmset(first,last,C1,A1){ };

    multiset_pool_cnc ( const multiset_pool_cnc & x ):vmset( x){ };

    multiset_pool_cnc (  multiset_pool_cnc && x ): vmset ( std::move( x)){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool_cnc ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool_cnc ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2>  & x ):vmset( x){ };

    template <bool cnc2 >
    multiset_pool_cnc (cntree_multiset <value_t,cnc2,comp_key_t,mset_alloc_t>&& x ):vmset(std::move(x)){ };

    template <bool cnc2 >
    multiset_pool_cnc (cntree_set <value_t,cnc2,comp_key_t,mset_alloc_t>&& x ):vmset(std::move(x)){ };

    virtual ~multiset_pool_cnc(void ){} ;

    //-------------------------------------------------------------------------
    //                       O P E R A T O R =
    //-------------------------------------------------------------------------
    multiset_pool_cnc & operator = ( const multiset_pool_cnc &S)
    {   vmset::operator= ( S);
        return *this ;
    };
    multiset_pool_cnc  & operator = (multiset_pool_cnc &&S)
    {   vmset::operator= ( std::move(S));
        return *this ;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool_cnc & operator = ( const cntree_multiset <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template < typename alloc_t2 , bool cnc2 >
    multiset_pool_cnc & operator = ( const cntree_set <value_t,cnc2,comp_key_t,alloc_t2> & S)
    {   vmset::operator= ( S);
        return *this;
    };

    template <bool cnc2 >
    multiset_pool_cnc & operator= (  cntree_multiset <value_t,cnc2,comp_key_t,mset_alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
    template <bool cnc2 >
    multiset_pool_cnc & operator= ( cntree_set <value_t,cnc2,comp_key_t,mset_alloc_t>&& x )
    {   vmset::operator= ( std::move (x) ) ;
        return *this ;
    };
};
#else
using multiset_pool_cnc = cntree_multiset <value_t,true,comp_key_t,suballocator_cnc<alloc_t> >;
#endif

//***************************************************************************
};//              E N D    C N T R E E    N A M E S P A C E
//***************************************************************************
#endif
