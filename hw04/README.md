How to build

To compile the events progam, run the following command in the hw04 directory:

make 

This builds the events executable using the tally ADT implementation.

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

AI Usage

AI was used to help gather ideas and brainstorm how to make the files such as events.c, tally.c, test_tally.c, Makefile. AI was also
used to help with some debugging and helping fix some errors that were encountered in the terminal in vs code. These errors inlcude
vs code not being able to find certain files such as the temporary C file that was used to test that tally.h is in fact opaque. This
error was solved thanks to the help of AI that suggested many ways to try and get the terminal in vs code to find the file. When
everuything eneded up not working AI suggested coding the short test code directly from the terminal to ensure that the temporary
would be found and this ended up fixing the issue. In addition AI helped in making and refining the test_tally.c to ensure that as
many relavent test were performed to ensure that the events.c code was in fact working. The last thing that AI was used in was to 
ensure thast the .gitignore file was written correctly to ensure nothing that is not needed will not get pushed to Github. This is the
extent in which AI was used in this homework assignment. 
