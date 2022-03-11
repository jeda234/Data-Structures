HOMEWORK 6: CROSSWORD BLACKOUT


NAME: Jeda Coward


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 40



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Etc. 


My program has many small functions that lead up and help to find given solutions, update
the grid, and finally print out the solved crossword puzzle. The final o-notation is 
pretty big, but its the only way I could think to tackle this.

-> My update_board function has a o-notation of O(w*h*l), since i look through all points of 
the board, and also looking for spaces with letters.
-> My find_word function has an o-notation of O(s), where s is the size of the word in the 
solution set we ar elooking for
-> My solve function has an o-notation of O(w*h*sol), where sol is the number of words in a 
solution set
-> My findValidSolutions function has an o-notation of O(w*h*d)
-> My findSolutions function has an o-notation of O(d)

All of these functions get called at least once, so my total o-notation is O(w*h*l).


DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).


I have one test case that includes words in the dictionary that are not on the board
and not a length of any of the constraints. This was to make sure that when I am finding
solutions, at the least all of the lengths should be matching.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.


reverse_ell and blackout1 take about 1 second to compile and run and the number of 
solutions outputted for both are what is expected in the output.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

I tried to make the hidden test cases work, and to get the other two points in the 
initial autograding, but I believe that there is a flaw in my findSolutions method
that is preventing this solutions to be printed/solved correctly.

