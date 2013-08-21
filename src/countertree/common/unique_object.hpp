//----------------------------------------------------------------------------
/// @file unique_object.hpp
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
#ifndef __COUNTERTREE__COMMON_UNIQUE_OBJECT_HPP
#define __COUNTERTREE__COMMON_UNIQUE_OBJECT_HPP

#include <memory>
#include <thread>
#include <cassert>

#ifdef  _MSC_VER
    #define THREAD_LOCAL __declspec(thread )
#else
    #define THREAD_LOCAL __thread
#endif

namespace countertree
{
namespace common
{

//---------------------------------------------------------------------------
/// @class seed
///
/// @remarks This a singleton thread_local
//---------------------------------------------------------------------------
template <class T >
struct seed
{   T *P ;
    uint32_t N ;
};


//---------------------------------------------------------------------------
/// @class unique_object
///
/// @remarks This is a singleton thread_local
//---------------------------------------------------------------------------
template <class T >
class unique_object
{
private :
static THREAD_LOCAL seed<T> D;

public:

unique_object ( void)
{   //---------------- begin ------------
    if ( D.N == 0 ) D.P = new T();
    D.N++;
}
~unique_object( void)
{   //------------- begin ---------------
    assert ( D.N != 0 );
    if ( D.N == 1)
    {   delete D.P ;
        D.P = NULL ;
    };
    D.N-- ;
};

T & operator() ( void ){  return  * D.P ;};

T * operator -> () {   return D.P ;};
T & operator * () { return *D.P;};

};// ------------------ end class unique_object ---------------------

template <class T >
THREAD_LOCAL seed<T> unique_object<T>::D = { NULL , 0 } ;
};// -------------------- end namespace alloc ---------------------
};// -------------------- end namespace countertree ------------------
#endif
