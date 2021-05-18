# Persistent-BST-in-Cplusplus
A Generic Library for persistent Binary Search Tree in C++  
 
This project is aimed at creating a generic Binary Search Tree library which
creates generic binary search tree on the hard disk which is dumped into a file 
and the entire tree is generic and the pointers of the tree nodes are managed by 
carefully using file offsets instead of pointers this is the way we deal with the
task of storing the BST .

This library provides us with the following 

1. Create tree nodes of a generic type. 
2. Insert and Delete nodes. 
3. Dump them onto a file. 
4. Name that file
5. Extract inorder traversal of the tree . 
6. Extract preorder traversal of the tree. 
7. Extract postorder traversal of the tree. 
8. Get the traversals in the form of the vector.  


The library is inside the Namespace of tree
the name of the header file is tree.h  

FAQs

Q1 ) Why to use this library tree.h ? 
Ans : Because if you want to access your generic - binary search tree even after you terminate your program. 

Q2 ) What kind of Data types can this generic work with ?  
Ans : Any data type which supports 
        (i)   <  operator
        (ii)  >  operator
        (iii) == operator
        (iv)  != operator
        (v)    copy constructor.
        (vi)   copy assignment operator.
        (vii)  put to operator or operator<< 

Q3 ) How to use it 
Ans : Include the header file and start using it ! 
