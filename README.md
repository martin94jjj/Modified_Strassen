# Modified Strassen

Theoretically, Strassen’s matrix multiplication method has a better asymptotic runtime compared to conventional
matrix multiplication method. Here we test a modified Strassen’s algorithm, which utilizes conventional matrix
multiplication for small enough `n`. The break even point where the conventional method and the modified
Strassen’s method is analyzed analytically and then compared with empirical break even points. Then, the modified
Strassen’s method is applied to compute the cube of a matrix, which is then used for finding the number of
triangles in the graph represented by that matrix.

The modified Strassen's algorithm is implemented in C++
