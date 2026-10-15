Computer model: Dell XPS 16 DA16260
Compiler:GCC 16.2.0 (MSYS2 UCRT64, MinGW-w64)

Table:
Function	Optimization	Largest successful n
stats_max	-O0	approximately 32,300
stats_max	-O2	approximately 255,000
stats_max_tail	-O0	approximately 43,250
stats_max_tail	-O2	greater than 21,000,000

Explanation:
The original stats_max function makes a recursive call and then compares the returned results with the current values. Since it still has work to do after the recusive call returns , the call is not a tail call and each call can require its own stack frame. So the function eventually runs out of stack space. The new stats_max_tail function carries the best value found so far as a parameter. The recursive call is the final operation in the helper function, so there is no additional work to perform after the call returns. 

At -O2, GCC can optimize the tail-recursive function into a loop. This allows the function to reuse the same stack frame instead of creating a new frame for every value. This explains why it can process more than 21 million values however it is important to note that since the code uses a float it only represents values up to 16,777216. Which is why when attempting to process mroe than 21 million values the output which is 20,999,999 rounds up and shows 21,000,000. At -O0 the compiler generally does not perform the optimization but the tail-recursive function can still create a stack frame for each call and eventually exhasut the stack.

The original stats_max_function is not helped in the same way by -O2 because it needs to compare the current value with the recursive result after the recusive call return this prevents the usual tail-call optimization. For a binary search tree, recursive depth depends on the tree's height. A balanced tree has a height proportional to log n, so recursion generally requires fewer stack frames. An unbalanced tree can have a height proportional ot n, which can cuase stack overflow for large trees. Tail-call optimization only helps when the recursive call is in a suitable position; many tree operations still need to do work after recursive calls return. 