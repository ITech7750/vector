#include "vector.h"
#include "vector_impl.c"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void test_new_vector_real() {
    Vector *v = new_vector(5, REAL);

    assert(v->size == 0);
    assert(v->capacity == 5);
    assert(v->data != NULL);
    assert(v->type == REAL);

    free_vector(v);
}


void test_push_back_real() {
    Vector *v = new_vector(5, REAL);

    double x = 12.0;
    double y = 15.0;

    push_back(v, &x);
    push_back(v, &y);

    assert(v->size == 2);
    assert(v->capacity == 5);
    assert(*(double *) v->data[0] == 12.0);
    assert(*(double *) v->data[1] == 15.0);

    free_vector(v);
}


void test_get_real() {
    Vector *v = new_vector(5, REAL);

    double x = 12.0;
    double y = 15.0;

    push_back(v, &x);
    push_back(v, &y);

    assert(*(double *) get(v, 0) == 12.0);
    assert(*(double *) get(v, 1) == 15.0);

    free_vector(v);
}


void test_vector_add_real() {
    Vector *v1 = new_vector(2, REAL);
    Vector *v2 = new_vector(2, REAL);

    double x1 = 12.0;
    double x2 = 15.0;
    double y1 = 17.0;
    double y2 = 19.0;

    push_back(v1, &x1);
    push_back(v1, &x2);
    push_back(v2, &y1);
    push_back(v2, &y2);

    Vector *result = vector_add(v1, v2);

    assert(result->size == 2);
    assert(result->capacity == 2);
    assert(*(double *) result->data[0] == 29.0);
    assert(*(double *) result->data[1] == 34.0);

    free_vector(v1);
    free_vector(v2);
    free_vector(result);
}


void test_scalar_product_real() {
    Vector *v1 = new_vector(2, REAL);
    Vector *v2 = new_vector(2, REAL);

    double x1 = 12.0;
    double x2 = 15.0;
    double y1 = 17.0;
    double y2 = 19.0;

    push_back(v1, &x1);
    push_back(v1, &x2);
    push_back(v2, &y1);
    push_back(v2, &y2);

    Complex product = scalar_product(v1, v2);
    double tmp = product.real;
    assert(tmp == 391.0);
    free_vector(v1);
    free_vector(v2);
}




