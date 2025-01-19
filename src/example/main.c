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
