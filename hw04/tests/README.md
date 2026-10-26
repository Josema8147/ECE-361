How to build
To compile the events progam, run the following command in the hw04 directory:
make 
This builds the events eecutable using the tally ADT implementation.

How to Test
To compile and run the tally test, run:
make test 
The test check counting, invalid inputs, name length limits, full tallies, maximum simultaneous tallies, reusing desroyed tallies,
independence between tallies, and alphabetical print order.

To remove compiled files, run
make clean

Opaque Type Demonstration 
To demonstrate that tally_t is an opaque type, a temporary C file that inlcuded only tally.h was created. This temporary file
attempted to access a member dierectly using t->size = 10;. This file was then compiled using gcc -std=c11 -Wall -Wextra -c 
test_opaque.c and the compiler produced the following error:
test_opaque.c: In function 'main':
test_opaque.c:6:6: error: invalid use of incomplete typedef 'tally_t' {aka 'struct tally'}
    6 |     t->size = 10;
      |      ^~

The tally_t type is opaque becasue tally.h declares the type without revealing the members of its structure. Therefore, code that
includes only tally.h cannot directly access members such as size or entries. This is useful because it hides its implementation 
details, prevents other parts of the program from directly modifying the tally's internal data, and allows the implementation in
tally.c to change without requiring other files to change as long the public interface stays the same. 