PROJECT DESCRIPTION
--------------------------

BRIEF

This library provide a concurrent and thread safe implementation of the 
tree based data structures (set, multiset, map and multimap, plus a new data 
structure named vector_tree)  with random access iterators and access by 
position like a vector. 

This permit to distribute the elements stored in the trees, between an 
arbitrary number of threads, identically as do with the vectors, making 
easy the design of parallel algorithms applied to the tree based data 
structures (as you can see in 2.3.- Examples and 3.6.- Examples), and their 
use by the multicore development tools as OpenMP, Threading Building Blocks ...

These data structures are based on a kind of red-black trees (Counter Tree) 
which  permit the access by position, like in a vector, to the elements stored 
in the tree, and random access iterators. 

Based on this trees this library provide, in the namespace countertree,  
classes set, multiset, map and multimap, compatible with the class with the 
same name in the Standard Library, plus a new data structure (vector_tree) 
which is a vector, built over this kind of tree, compatible with the vector 
and deque of the Standard Library.

All these classes have access by position, like the vectors , and random 
access iterators.You can subtract two iterators for to know the number of 
elements between them. These classes have a concurrent version, which is 
thread-safe with all the operations of the class, and other version non 
concurrent for to work only with 1 thread.

The library present too, the suballocators. They are pools for to improve 
the allocation and deallocation of fixed size elements, like in the trees 
and lists. 

They are compatible with the allocator's definition of the Standard Library. 
They can be used by any class which need an allocator. The advantage of the 
suballocators  are

     1.-Improve the speed ( around 30% in a heavy use with a std::set )
     2.-Reduce the memory consumption.
     3.-Improve the memory management, returning to the operating system the 
        unused memory, reducing dynamically the amount of memory used by the 
        program (Many allocators don't return well the unused chucks of memory 
        to the Operating System  and the memory  used by the allocator is the 
        maximum used and never decrease)



Francisco José Tapia
fjtapia@gmail.com
