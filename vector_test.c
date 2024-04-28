#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "vector.h"
#include "fun_impl.c"

double randt() {
    srand(time(0) + sleep(1));
    return (double)rand() / RAND_MAX * 100.0;
}

void test_vector_complex() {
    double n1 = randt();
    double n2 = randt();
    double n3 = randt();
    double n4 = randt();

    Complex c1 = {n1, n2};
    Complex c2 = {n3, n4};
    Complex* stored_c1 = malloc(sizeof(Complex));
    Complex* stored_c2 = malloc(sizeof(Complex));
    stored_c1 = &c1;
    stored_c2 = &c2;

    Vector* v = vector_new(2, complex_equals, print_complex, add_complex, scalar_product_complex);
    vector_push_back(v, stored_c1);
    vector_push_back(v, stored_c2);

    assert(vector_size(v) == 2);
    assert(complex_equals(vector_get(v, 0), stored_c1));
    assert(complex_equals(vector_get(v, 1), stored_c2));

    vector_print(v);

    Complex* result = (Complex*) vector_scalar_product(v, v);
    printf("Скалярное произведение векторов: %.2f + %.2fi\n", result->real, result->imag);

    assert(fabs((n1 * n3+ n2 * n4) - result->real) < 10e6);
    assert(fabs((n2 * n3 + n4 * n1) - result->imag) < 10e6);

    free(result);
    vector_free(v);
}

void test_vector_real() {
    double r1 = randt();
    double r2 = randt();
    double* stored_r1 = malloc(sizeof(double));
    double* stored_r2 = malloc(sizeof(double));
    *stored_r1 = r1;
    *stored_r2 = r2;

    Vector* v = vector_new(2, real_equals, print_real, add_real, scalar_product_real);
    vector_push_back(v, stored_r1);
    vector_push_back(v, stored_r2);

    assert(vector_size(v) == 2);
    assert(real_equals(vector_get(v, 0), stored_r1));
    assert(real_equals(vector_get(v, 1), stored_r2));

    vector_print(v);

    double* result = (double*) vector_scalar_product(v, v);
    printf("Скалярное произведение векторов: %.2f\n", *result);
    printf("ожидание: %.5f, получено: %.5f\n", (r1 * r1 + r2 * r2 ), *result);

    assert(fabs((r1 * r1 + r2 * r2 ) - *result) < 1e-6);

    free(result);
    vector_free(v);
}

void test() {
    test_vector_complex();
    test_vector_real();
}
