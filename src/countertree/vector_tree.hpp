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
#ifdef _MSC_VER

struct  vector_tree : cntree_vector < value_t, false, alloc_t >
{   //-----------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef cntree_vector <value_t,false,alloc_t > vtree;

    //-----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //-----------------------------------------------------------------------
    explicit vector_tree ( const alloc_t &ALLC = alloc_t ()):vtree ( ALLC){ };

    vector_tree ( const vector_tree & VT ):vtree ( VT){};

    vector_tree ( vector_tree && VT) : vtree ( std::move ( VT)){};

    template < typename alloc_t2 =alloc_t , bool cnc2=false >
    vector_tree (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT):vtree ( VT){};

    template < bool cnc2>
    vector_tree ( cntree_vector<value_t,cnc2,alloc_t> && VT):vtree ( std::move ( VT )){};

    template < typename alloc_t2 =alloc_t  >
    vector_tree (const vector_tree<value_t,alloc_t2> &VT):vtree ( VT){};

    vector_tree( unsigned_type n,
                 const value_t& Val=value_t(),
                 const alloc_t &A= alloc_t()) : vtree ( n, Val , A ){};

    template <class InputIterator>
    vector_tree ( InputIterator it_first ,
                  InputIterator it_last,
                  const alloc_t& A = alloc_t() ): vtree (it_first ,it_last,A  ){};

    //-----------------------------------------------------------------------
    //                       O P E R A T O R =
    //-----------------------------------------------------------------------
    vector_tree & operator= (const vector_tree &VT)
    {   vtree::operator= ( VT) ;
        return *this ;
    };
    vector_tree & operator= (vector_tree &&VT)
    {   vtree::operator= ( std::move(VT)) ;
        return *this ;
    };
    template < typename alloc_t2 , bool cnc2>
    vector_tree & operator=  (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
    {  vtree::operator = ( VT) ;
        return *this ;
    };

    template <bool cnc2>
    vector_tree & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
    {   vtree::operator= ( std::move(A ));
        return *this ;
    };

};
#else
using vector_tree = cntree_vector < value_t, false, alloc_t >;
#endif


//***************************************************************************
//             V E C T O R _ T R E E _ C N C
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void >
>
#ifdef _MSC_VER
struct  vector_tree_cnc : cntree_vector < value_t, true, alloc_t >
{   //--------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //--------------------------------------------------------------------
    typedef cntree_vector <value_t,true,alloc_t > vtree;

    //----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //----------------------------------------------------------------------
    explicit vector_tree_cnc ( const alloc_t &ALLC = alloc_t ()):vtree ( ALLC){ };

    vector_tree_cnc ( const vector_tree_cnc & VT ):vtree ( VT){};

    vector_tree_cnc ( vector_tree_cnc && VT) : vtree ( std::move ( VT)){};

    template < typename alloc_t2 =alloc_t , bool cnc2=true >
    vector_tree_cnc (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT):vtree ( VT){};

    template < bool cnc2>
    vector_tree_cnc ( cntree_vector<value_t,cnc2,alloc_t> && VT):vtree ( std::move ( VT )){};

    template < typename alloc_t2 =alloc_t  >
    vector_tree_cnc (const vector_tree_cnc<value_t,alloc_t2> &VT):vtree ( VT){};

    vector_tree_cnc( unsigned_type n,
                 const value_t& Val=value_t(),
                 const alloc_t &A= alloc_t()) : vtree ( n, Val , A ){};

    template <class InputIterator>
    vector_tree_cnc ( InputIterator it_first ,
                  InputIterator it_last,
                  const alloc_t& A = alloc_t() ): vtree (it_first ,it_last,A  ){};

    //----------------------------------------------------------------------
    //                       O P E R A T O R =
    //--------------------------------------------------------------------
    vector_tree_cnc & operator= (const vector_tree_cnc &VT)
    {   vtree::operator= ( VT) ;
        return *this ;
    };
    vector_tree_cnc & operator= (vector_tree_cnc &&VT)
    {   vtree::operator= ( std::move(VT)) ;
        return *this ;
    };
    template < typename alloc_t2 , bool cnc2>
    vector_tree_cnc & operator=  (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
    {  vtree::operator = ( VT) ;
        return *this ;
    };

    template <bool cnc2>
    vector_tree_cnc & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
    {   vtree::operator= ( std::move(A ));
        return *this ;
    };

};
#else
using vector_tree_cnc = cntree_vector <value_t,true,alloc_t >;
#endif


//***************************************************************************
//             V E C T O R _ T R E E _ P O O L
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void>
>
#ifdef _MSC_VER
struct  vector_tree_pool : cntree_vector < value_t,false,suballocator<alloc_t> >
{   //--------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //--------------------------------------------------------------------
    typedef suballocator<alloc_t>  vt_alloc_t ;
    typedef cntree_vector < value_t,false,vt_alloc_t > vtree;

    //----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //----------------------------------------------------------------------
    explicit vector_tree_pool ( const vt_alloc_t &ALLC = vt_alloc_t ()): vtree ( ALLC){ };

    vector_tree_pool ( const vector_tree_pool & VT ):vtree ( VT){};

    vector_tree_pool ( vector_tree_pool && VT) : vtree ( std::move ( VT)){};

    template < typename alloc_t2 =alloc_t , bool cnc2=false >
    vector_tree_pool (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT):vtree ( VT){};

    template < bool cnc2>
    vector_tree_pool ( cntree_vector<value_t,cnc2,vt_alloc_t> && VT):vtree ( std::move ( VT )){};

    template < typename alloc_t2 =alloc_t  >
    vector_tree_pool (const vector_tree_pool<value_t,alloc_t2> &VT):vtree ( VT){};

    vector_tree_pool(   unsigned_type n,
                        const value_t& Val=value_t(),
                        const vt_alloc_t &A= vt_alloc_t()) : vtree ( n, Val , A ){};

    template <class InputIterator>
    vector_tree_pool ( InputIterator it_first ,
                  InputIterator it_last,
                  const vt_alloc_t& A = vt_alloc_t() ): vtree (it_first ,it_last,A  ){};

    //----------------------------------------------------------------------
    //                       O P E R A T O R =
    //--------------------------------------------------------------------
    vector_tree_pool & operator= (const vector_tree_pool &VT)
    {   vtree::operator= ( VT) ;
        return *this ;
    };
    vector_tree_pool & operator= (vector_tree_pool &&VT)
    {   vtree::operator= ( std::move(VT)) ;
        return *this ;
    };
    template < typename alloc_t2 , bool cnc2>
    vector_tree_pool & operator=  (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
    {  vtree::operator = ( VT) ;
        return *this ;
    };

    template <bool cnc2>
    vector_tree_pool & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
    {   vtree::operator= ( std::move(A ));
        return *this ;
    };

};
#else
using vector_tree_pool = cntree_vector<value_t,false,suballocator<alloc_t> >;
#endif


//***************************************************************************
//             V E C T O R _ T R E E _ P O O L _ C N C
//***************************************************************************
template
<   typename value_t,
    typename alloc_t= cntree_allocator<void>
>
#ifdef _MSC_VER
struct  vector_tree_pool_cnc : cntree_vector<value_t,true,suballocator_cnc<alloc_t> >
{   //--------------------------------------------------------------------
    //                        D E F I N I T I O N S
    //--------------------------------------------------------------------
    typedef  suballocator_cnc<alloc_t>  vt_alloc_t ;
    typedef cntree_vector<value_t,true,vt_alloc_t > vtree;


    //----------------------------------------------------------------------
    //                     C O N S T R U C T O R S
    //----------------------------------------------------------------------
    explicit vector_tree_pool_cnc ( const vt_alloc_t &ALLC = vt_alloc_t ()):vtree ( ALLC){ };

    vector_tree_pool_cnc ( const vector_tree_pool_cnc & VT ):vtree ( VT){};

    vector_tree_pool_cnc ( vector_tree_pool_cnc && VT) : vtree ( std::move ( VT)){};

    template < typename alloc_t2 =alloc_t , bool cnc2=true >
    vector_tree_pool_cnc (const cntree_vector<value_t,cnc2 ,alloc_t2> &VT):vtree ( VT){};

    template < bool cnc2>
    vector_tree_pool_cnc ( cntree_vector<value_t,cnc2,vt_alloc_t> && VT):vtree ( std::move ( VT )){};

    template < typename alloc_t2 =alloc_t  >
    vector_tree_pool_cnc (const vector_tree_pool_cnc<value_t,alloc_t2> &VT):vtree ( VT){};

    vector_tree_pool_cnc(   unsigned_type n,
                            const value_t& Val=value_t(),
                            const vt_alloc_t &A= vt_alloc_t()) : vtree ( n, Val , A ){};

    template <class InputIterator>
    vector_tree_pool_cnc (  InputIterator it_first ,
                            InputIterator it_last,
                            const vt_alloc_t & A = vt_alloc_t() ): vtree (it_first ,it_last,A  ){};

    //----------------------------------------------------------------------
    //                       O P E R A T O R =
    //--------------------------------------------------------------------
    vector_tree_pool_cnc & operator= (const vector_tree_pool_cnc &VT)
    {   vtree::operator= ( VT) ;
        return *this ;
    };
    vector_tree_pool_cnc & operator= (vector_tree_pool_cnc &&VT)
    {   vtree::operator= ( std::move(VT)) ;
        return *this ;
    };
    template < typename alloc_t2 , bool cnc2>
    vector_tree_pool_cnc & operator=  (const cntree_vector<value_t,cnc2, alloc_t2> &VT)
    {   vtree::operator = ( VT) ;
        return *this ;
    };

    template <bool cnc2>
    vector_tree_pool_cnc & operator= ( cntree_vector<value_t,cnc2,alloc_t> &&A)
    {   vtree::operator= ( std::move(A ));
        return *this ;
    };

};
#else
using vector_tree_pool_cnc = cntree_vector<value_t,true,suballocator_cnc<alloc_t> >;
#endif

//***************************************************************************
};//            E N D   C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
