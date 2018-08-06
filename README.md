# IsCpp
Find islands of ones in a Matrix of ones and zeroes. Non-recursive C++ version.

This is basically a depth-first-search on a forest of trees. When we find a 1 at any place in the matrix we start a depth first search marking all nodes we visit as zero in the process (this is an alternative to making a "visited" list).

This is a non-recursive version using a std::stack (instead of using the call-stack which we do in recursion).

