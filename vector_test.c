#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "fun_impl.c"


// Тетирование
void test_vector_complex() {
    Complex c1 = {1.0, 2.0};
    Complex c2 = {3.0, 4.0};

    Vector* v = vector_new(10, complex_equals, print_complex, add_complex, scalar_product_complex);

    vector_push_back(v, &c1);
    vector_push_back(v, &c2);

    // Проверка функции vector_size
    assert(vector_size(v) == 2);

    // Проверка функции vector_get
    assert(complex_equals(vector_get(v, 0), &c1));
    assert(complex_equals(vector_get(v, 1), &c2));

    // Проверка функции vector_print
    printf("Вектор комплексных чисел:\n");
    vector_print(v);

    // Проверка функции vector_scalar_product
    double scalar_product = vector_scalar_product(v, v);
    assert(fabs(scalar_product - 30.0) < 1e-6);

    // Освобождение памяти, занятой вектором (ваще хз надо ли освобождать тутЪ)*
    vector_free(v);
}

void test_vector_real() {
    Real r1 = 1.0;
    Real r2 = 2.0;

    Vector* v = vector_new(10, real_equals, print_real, add_real, scalar_product_real);

    vector_push_back(v, &r1);
    vector_push_back(v, &r2);


    // Проверка функции vector_size
    assert(vector_size(v) == 2);

    // Проверка функции vector_get
    assert(real_equals(vector_get(v, 0), &r1));
    assert(real_equals(vector_get(v, 1), &r2));

    // Проверка функции vector_print
    printf("Вектор действительных чисел:\n");
    vector_print(v);

    // Проверка функции vector_scalar_product
    double scalar_product = vector_scalar_product(v, v);
    assert(fabs(scalar_product - 5.0) < 1e-6);

    // Освобождение памяти, занятой вектором (*)
    vector_free(v);
}


