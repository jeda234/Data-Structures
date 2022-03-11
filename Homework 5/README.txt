HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Jeda Coward


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Office Hours

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours



TESTING & DEBUGGING STRATEGY:
Please be concise!  

I tested to make sure if the simple tests would work for another T type, so I did chars.
I also added tests to see if my copy list worked since it was not apart of the simple tests.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

size() - O(1) 
empty() - O(1) 
clear() - O(1)
front() - O(1)
back() - O(1)
push_front(const T& v) - O(n) - where n is the number of elements in a node
pop_front() - O(n) - where n is the number of elements in a node
push_back(const T& v) - O(1)
pop_back() - O(1)
print(std::ostream& s) - O(n^2) - where n is the number of elements in a node
erase(iterator itr) - O(n) - where n is the number of elements in a node
insert - O(n^2) - where n is the number of elements in a node
begin() - O(1)
end() - O(1)
copy_list(UnrolledLL<T>& old) - O(n) - where n is the number of elements in a node
destroy_list() - O(1)

The average number of elements in the node is 6.

Erasing an iterator has more memory issues, due to the fact that erasing an iterator
could delete a node, but not the entire list.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

I tried many different ways to get my insert to work. It is mind boggling that the list will actually do the inserting
but there seems to be an issue with how my iterator is working that makes it out of bounds, which gives the segmentation fault.
I have tried to change my iterator++ functions, however then my entire program will not run correctly. I went to office
hours for help and some of the mentors were confused.
