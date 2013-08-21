///----------------------------------------------------------------------------
// FILE : example_vector_tree_01.cpp
//
// DESCRIPTION : Test program of the class vector_tree
//
// MODIFICATIONS (AUTHOR,DATE,REASON) :
//  Copyright (c) 2010 Francisco José Tapia (fjtapia@gmail.com )
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// NOTES :
//-----------------------------------------------------------------------------

#include <boost/countertree/vector_tree.hpp>
#include <iostream>


int main ( void )
{   //---------------------------- begin -------------------------
    countertree::vector_tree<int> V ;
    for ( int i = 0 ; i < 10 ; i ++)   V.push_back( ( (i+1) * 10));
    countertree::vector_tree<int>::iterator Alfa, Beta ;
    Alfa = V.begin() + 3 ; // Iterator to the position 3
    Beta = V.end() - 2 ;   // iterator to the position 8

    // We insert two elements at the beginning of the vector_tree V
    // and the positions of the elements pointed by Alfa and Beta, change.
    V.push_front ( 2 );
    V.push_front ( 1) ;

    //-------------------------------------------------------------------------
    // All the iterators retrieve the correct position, even end() and rend()
    // The position of end() is the size of the data stucture and rend() is -1
    //------------------------------------------------------------------------------
    std::cout<<"Expecting [5,10] -----> ";
    std::cout<<"["<<Alfa.pos()<<" , "<<Beta.pos()<<"]"<<std::endl ;

    std::cout<<"Expecting :  (40 , 50 , 60 , 70 , 80 )------->";
    for ( int i = (int) Alfa.pos() ; i < Beta.pos() ; i ++)
        std::cout<<V[i]<<"  ";
    std::cout<<std::endl ;
    return 0 ;
};



