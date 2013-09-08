//----------------------------------------------------------------------------
/// @file singleton.hpp
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
#ifndef __COUNTERTREE__COMMON_SINGLETON_HPP
#define __COUNTERTREE__COMMON_SINGLETON_HPP

#include <mutex>

namespace countertree
{
namespace common
{
//##########################################################################
//                                                                        ##
//       ####################################################             ##
//       #                                                  #             ##
//       #                   C L A S S                      #             ##
//       #               S I N G L E T O N  < T >           #             ##
//       #                                                  #             ##
//       ####################################################             ##
//                                                                        ##
//##########################################################################

//---------------------------------------------------------------------------
/// @class singleton
///
/// @remarks This is a implementation of the Meyers singleton fo global static
///           variables
//---------------------------------------------------------------------------
template <class T >
class singleton : private T
{
private:
//***************************************************************************
//             P R I V A T E      F U N C T I O N S
//***************************************************************************
//---------------------------------------------------------------------------
//  function : constructor
/// @brief
/// @param [in]
//---------------------------------------------------------------------------
singleton() { };
//---------------------------------------------------------------------------
//  function : destructor
/// @brief
//---------------------------------------------------------------------------
~singleton(){};

public:
//---------------------------------------------------------------------------
//  function : instance
/// @brief return a reference to the unique instance of the class
/// @param [in]
/// @return reference  to the instance
//---------------------------------------------------------------------------
static T &instance()
{   std::mutex M ;
    std::lock_guard <std::mutex> LG ( M ) ;
    static singleton <T> msgltn;
    return(msgltn);
};
//***************************************************************************
};// E N D    C L A S S    S I N G L E T O N
//***************************************************************************

//***************************************************************************
};// E N D    N A M E S P A C E    A L L O C
};// E N D    N A M E S P A C E    C O U N T E R T R E E
//***************************************************************************
#endif
