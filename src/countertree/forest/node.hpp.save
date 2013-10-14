//----------------------------------------------------------------------------
/// @file   node.hpp
/// @brief  This file contains the implementation of the node in the countertree
///         data structure
///
/// @author Copyright (c) 2010 2013 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __COUNTERTREE_FOREST_NODE_HPP
#define __COUNTERTREE_FOREST_NODE_HPP

#include <stdexcept>
#include <boost/countertree/forest/base_node.hpp>
#if __DEBUG_CNTREE != 0
    #include <iostream>
#endif


using countertree::common::unsigned_type;
using countertree::common::signed_type;
using countertree::common::NByte;
using countertree::common::Conf;

namespace countertree
{
namespace forest
{

//##########################################################################
//                                                                        ##
//                   C L A S S        N O D E                             ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
/// @class  node
/// @brief  This class represent a node of the tree
//
/// @remarks
//---------------------------------------------------------------------------
template <typename T>
struct node :public base_node
{
//***************************************************************************
//                         V A R I A B L E S
//***************************************************************************
T data ;

//***************************************************************************
//           C O N S T R U C T O R , D E S T R U C T O R
//
//  explicit node ( const T &Dt  = T()) NOEXCEPT
//  node ( const node<T> & N1 ) NOEXCEPT
//  node ( T &&Dt  ) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : node
/// @brief Copy constructor. We copy the data, color and counter, but
///        don't copy the pnodes
/// @param [in] N1 : reference const  to the object to be copied
//---------------------------------------------------------------------------
node ( void ) NOEXCEPT:base_node ( ),data( T()){};

//---------------------------------------------------------------------------
//  function : node
/// @brief Copy constructor. We copy the data, color and counter, but
///        don't copy the pnodes
/// @param [in] N1 : reference const  to the object to be copied
//---------------------------------------------------------------------------
node ( const node & N1 ) NOEXCEPT:base_node ( ),data(N1.data){};

//---------------------------------------------------------------------------
//  function : node
/// @brief Copy constructor. We copy the data, color and counter, but
///        don't copy the pnodes
/// @param [in] N1 : reference const  to the object to be copied
//---------------------------------------------------------------------------
node ( node && N1 ) NOEXCEPT:base_node ( ),data(std::move(N1.data)){};


//---------------------------------------------------------------------------
//  function : node
/// @brief Constructor
/// @param [in] Dt : Value to copy in the node. By default the empty
///                  constructor of the value
//---------------------------------------------------------------------------
node ( const T &Dt ) NOEXCEPT:base_node (),data(Dt){ };

//---------------------------------------------------------------------------
//  function : node
/// @brief Constructor
/// @param [in] Dt : Value to copy in the node. By default the empty
///                  constructor of the value
//---------------------------------------------------------------------------
node ( T &&Dt  ) NOEXCEPT:base_node (),data(std::move(Dt)){ }


//---------------------------------------------------------------------------
//  function : ~node
/// @brief Destructor
//---------------------------------------------------------------------------
virtual ~node ( void  ) NOEXCEPT{ }

//---------------------------------------------------------------------------
//  function : node
/// @brief Constructor
/// @param [in] args : arguments for to build the node
//---------------------------------------------------------------------------
template <class ... Args>
node (Args &&... args  ) NOEXCEPT :base_node(),data(std::forward<Args>(args)... ){ };


//***************************************************************************
// O P E R A T O R = , R E M O V E _ C O N S T , U P G R A D E
//
//  node &  operator = ( const node &Nd) NOEXCEPT
//  node &  operator = ( node<T> &&Nd) NOEXCEPT
//  node  * remove_const ( void) const NOEXCEPT
//  static node *      upgrade ( base_node * P ) NOEXCEPT
//  static const node * upgrade ( const base_node * P ) NOEXCEPT
//
//***************************************************************************
//---------------------------------------------------------------------------
//  function : operator=
/// @brief Asignation operator
/// @param [in] Nd : node to be copied
/// @return reference to the object after the copy
/// @remarks This function copy the data, color and counter , but don't
///          copy the pointers
//---------------------------------------------------------------------------
node &  operator = ( const node &Nd) NOEXCEPT
{   base_node::operator= ( Nd);
    data= Nd.data;
    return *this ;
};
//---------------------------------------------------------------------------
//  function : operator=
/// @brief Asignation operator
/// @param [in] Nd : node to be copied
/// @return reference to the object after the copy
/// @remarks This function copy the data, color and counter , but don't
///          copy the pointers
//---------------------------------------------------------------------------
node &  operator = ( node<T> &&Nd) NOEXCEPT
{   N = Nd.N ;
    color = Nd.color ;
    data= std::move(Nd.data);
    return *this ;
};
//---------------------------------------------------------------------------
//  function : remove_const
/// @brief Generate a pnode from a const node<T>*
/// @param [in] none
/// @return Pointer
//---------------------------------------------------------------------------
node  * remove_const ( void) const NOEXCEPT
{   return  const_cast < node *>(this );
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node pointer in a node<T> pointer
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
static node *      upgrade ( base_node * P ) NOEXCEPT
{   return  static_cast < node *>      ( P );
};
//---------------------------------------------------------------------------
//  function : upgrade
/// @brief Convert a base_node pointer in a node<T> pointer
/// @param [in] P base_node pointer
/// @return Pointer
//---------------------------------------------------------------------------
static const node * upgrade ( const base_node * P ) NOEXCEPT
{   return  static_cast < const node *>( P );
};
//***************************************************************************
};//     E N D     C L A S S    N O D E < T >
//***************************************************************************

//***************************************************************************
//                D E B U G         F U N C T I O N S
//***************************************************************************
#if __DEBUG_CNTREE != 0
//---------------------------------------------------------------------------
//  function : operator<<
/// @brief Print operator for the node
/// @param [in/out] salida : ostream where print
/// @param [in] N : node to print
/// @return reference to salida after the printing
/// @remarks Only for debugger purpose
//---------------------------------------------------------------------------
template <class T>
std::ostream & operator << (std::ostream &salida, const node<T> & N )
{   salida<<base_node (N);
    salida <<" data:"<<N.data ;
    return salida ;
};
#endif

//***************************************************************************
};//      E N D     F O R E S T    N A M E S P A C E
//
};//      E N D     C O U N T E R T R E E   N A M E S P A C E
//***************************************************************************
#endif
