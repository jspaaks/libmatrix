# libmatrix

Matrix data type and operations on instances of that type.

For instructions on building, formatting, testing, etc, see [`README.dev.md`](README.dev.md).

## Executables

- `test_matrix` Criterion-based unit tests program

## Libraries

- `matrix`: Matrix data type and operations on instances of that type.

## `man` pages

```console
$ man -l ./dist/share/man/man3/matrix.3

matrix(3)             Library Functions Manual             matrix(3)

NAME
       matrix  -  Operations on 2-D arrays, which are implemented as
       dope vectors.

LIBRARY
       matrix (libmatrix, -lmatrix)

DESCRIPTION
       Available API man pages:

       matrix_accall    Calculate the sum of all matrix elements
       matrix_accdwn    Calculate the sum of each column of a matrix
       matrix_accrgt    Calculate the sum of each row of a matrix
       matrix_addsca    Add a scalar value to a matrix
       matrix_avgall    Calculate the average of all matrix elements
       matrix_avgdwn    Calculate the average of each column of a matrix
       matrix_avgrgt    Calculate the average of each row of a matrix
       matrix_bctdwn    Broadcast a row matrix down
       matrix_bctrgt    Broadcast a column matrix right
       matrix_create    Create a matrix object in memory
       matrix_destroy   Free the memory associated with a matrix object
       matrix_divsca    Divide a matrix by a scalar value
       matrix_dotpro    Calculate the dot product of two matrices
       matrix_ebeadd    Element-by-element addition of two matrices
       matrix_ebediv    Element-by-element division of two matrices
       matrix_ebemap    Apply a function to each element of a matrix
       matrix_ebesub    Element-by-element subtraction of two matrices
       matrix_hadpro    Element-by-element multiplication (Hadamard product) of two matrices
       matrix_hstack    Stack one matrix to the left of another
       matrix_ident     Set the elements of a matrix such that it represents the
                        identity matrix
       matrix_maxall    Calculate the maximum of all matrix elements
       matrix_maxdwn    Calculate the maximum of each column of a matrix
       matrix_maxrgt    Calculate the maximum of each row of a matrix
       matrix_minall    Calculate the minimum of all elements of a matrix
       matrix_mindwn    Calculate the minimum of each column of a matrix
       matrix_minrgt    Calculate the minimum of each row of a matrix
       matrix_ones      Set all elements of a matrix to 1
       matrix_readnc    TODO
       matrix_readnr    TODO
       matrix_readxs    TODO
       matrix_print     Print a matrix
       matrix_scapro    Multiply a matrix with a scalar
       matrix_sdvall    Calculate the standard deviation of all elements of a matrix
       matrix_sdvdwn    Calculate the standard deviation of each column of a matrix
       matrix_sdvrgt    Calculate the standard deviation of each row of a matrix
       matrix_stzall    TODO
       matrix_stzdwn    Scale and translate each column of a matrix to have zero mean and
                        unit variance
       matrix_stzrgt    TODO
       matrix_subsca    Subtract a scalar from a matrix
       matrix_testeq    Test whether two matrices are equal within a tolerance
       matrix_transp    Transpose a matrix
       matrix_ustzall   TODO
       matrix_ustzdwn   TODO
       matrix_ustzrgt   TODO
       matrix_varall    Calculate the variance of all elements of a matrix
       matrix_vardwn    Calculate the variance of each column of a matrix
       matrix_varrgt    Calculate the variance of each row of a matrix
       matrix_vstack    Stack one matrix one top of another
       matrix_write     Write a matrix to file
       matrix_zeros     Set all elements of a matrix to 0

                                                                               matrix(3)
```

## Example

```c
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "matrix/matrix.h"

void populate_with_rand_int (Matrix * mat);

int main (void) {

    srand(time(nullptr));

    Matrix * a = matrix_create(3, 2);
    Matrix * b = matrix_create(2, 4);
    Matrix * c = matrix_create(3, 4);

    populate_with_rand_int(a);
    populate_with_rand_int(b);

    matrix_print(stdout, "a", a);
    matrix_print(stdout, "b", b);

    matrix_dotpro(a, b, c);
    matrix_print(stdout, "c", c);

    matrix_destroy(&a);
    matrix_destroy(&b);
    matrix_destroy(&c);

    assert(a == nullptr);
    assert(b == nullptr);
    assert(c == nullptr);
}

void populate_with_rand_int (Matrix * mat) {
    for (size_t ir = 0; ir < mat->nr; ir++) {
        for (size_t ic = 0; ic < mat->nc; ic++) {
            size_t i = ir * mat->nc + ic;
            mat->xs[i] = rand() % 10;
        }
    }
}
```

```console
$ ./dist/bin/example_matrix
a (3x2):
         9,          1
         0,          9
         2,          6
b (2x4):
         1,          0,          5,          2
         4,          7,          2,          5
c (3x4):
        13,          7,         47,         23
        36,         63,         18,         45
        26,         42,         22,         34
```

## Acknowledgements

_This project was initialized using [Copier](https://pypi.org/project/copier)
and the [Copier template for C projects](https://github.com/jspaaks/copier-template-for-c-projects)._
