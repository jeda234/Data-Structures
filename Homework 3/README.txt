HOMEWORK 3: JAGGED ARRAY


NAME: Jeda Coward


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.cplusplus.com/reference/cstdlib/exit/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked: O(1)
 packed: O(1)

numBins
 unpacked: O(1)
 packed: O(1)

numElementsInBin
 unpacked: O(1)
 packed: O(e+b*k)

getElement
 unpacked: O(1)
 packed: O(e+b*k)

isPacked
 unpacked: O(1)
 packed: O(1)

clear
 unpacked: O(b*k)
 packed: O(e+b)

addElement
 unpacked: O(k)
 packed: O(1)

removeElement
 unpacked: O(k)
 packed: O(1)

pack
 unpacked:O(e+b*k)
 packed:O(1)

unpack
 unpacked: O(1)
 packed: O(b*k+e)

print 
 unpacked: O(b*k)
 packed: O(b+e)

constructor w/ integer argument
 unpacked: O(b)
 packed: N/A

copy constructor
 unpacked: O(b*k)
 packed: O(b+e)

destructor
 unpacked: O(b*k)
 packed: O(b+e)

assignment operator
 unpacked: O(b*k)
 packed: O(b+e)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
