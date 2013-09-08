//----------------------------------------------------------------------------
/// @file mysingleton.hpp
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
#ifndef __COUNTERTREE__COMMON_MYSINGLETON_HPP
#define __COUNTERTREE__COMMON_MYSINGLETON_HPP

#include  <boost/countertree/common/spinlock.hpp>

namespace countertree
{
namespace common
{
//##########################################################################
//                                                                        ##
//        C L A S S     M Y S I N G L E T O N < T , C N C >               ##
//                                                                        ##
//##########################################################################
//---------------------------------------------------------------------------
/// @class mysingleton
///
/// @remarks This is a implementation of the Meyers singleton
//---------------------------------------------------------------------------
template <class T , bool cnc >
class mysingleton : private T
{
private:
//***************************************************************************
//      P R I V A T E    D E F I N I T I O N S  &  V A R I A B L E S
//***************************************************************************
typedef countertree::common::config_lock<cnc>    config_lock;
typedef typename config_lock::lock_data         lock_data ;
typedef typename config_lock::mylock            mylock ;
//lock_data LD ;
//***************************************************************************
//             P R I V A T E      F U N C T I O N S
//***************************************************************************
//---------------------------------------------------------------------------
//  function : constructor
/// @brief
/// @param [in]
//---------------------------------------------------------------------------
mysingleton() { };
//---------------------------------------------------------------------------
//  function : destructor
/// @brief
//---------------------------------------------------------------------------
~mysingleton(){};

public:
//---------------------------------------------------------------------------
//  function : instance
/// @brief return a reference to the unique instance of the class
/// @param [in]
/// @return reference  to the instance
//---------------------------------------------------------------------------
static T &instance()
{   lock_data LD ;
    mylock ML ( LD);
    static mysingleton<T,cnc> msgltn;
    return(msgltn);
};
//***************************************************************************
};// E N D    C L A S S     M Y S I N G L E T O N
//***************************************************************************

//***************************************************************************
};// E N D    N A M E S P A C E    A L L O C
};// E N D    N A M E S P A C E    C O U N T E R T R E E
//***************************************************************************
#endif
