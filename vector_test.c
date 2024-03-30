#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "vector_impl.c"



// Функции для работы с комплексными числами
typedef struct Complex {
    double real;
    double imag;
} Complex;

bool complex_equals(const void* c1, const void* c2) {
    const Complex* complex1 = c1;
    const Complex* complex2 = c2;
    return complex1->real == complex2->real && complex1->imag == complex2->imag;
}

void print_complex(const void* c) {
    const Complex* complex = c;
    printf("(%.2f + %.2fi)", complex->real, complex->imag);
}

void* add_complex(const void* c1, const void* c2) {
    const Complex* complex1 = c1;
    const Complex* complex2 = c2;
    Complex* result = malloc(sizeof(Complex));
    result->real = complex1->real + complex2->real;
    result->imag = complex1->imag + complex2->imag;
    return result;
}

double scalar_product_complex(const void* c1, const void* c2) {
    const Complex* complex1 = c1;
    const Complex* complex2 = c2;
    return complex1->real * complex2->real + complex1->imag * complex2->imag;
}

// Функции для работы с действительными числами
typedef double Real;

bool real_equals(const void* r1, const void* r2) {
    const Real* real1 = r1;
    const Real* real2 = r2;
    return *real1 == *real2;
}

void print_real(const void* r) {
    const Real* real = r;
    printf("%.2f", *real);
}

void* add_real(const void* r1, const void* r2) {
    const Real* real1 = r1;
    const Real* real2 = r2;
    Real* result = malloc(sizeof(Real));
    *result = *real1 + *real2;
    return result;
}

double scalar_product_real(const void* r1, const void* r2) {
    const Real* real1 = r1;
    const Real* real2 = r2;
    return *real1 * *real2;
}


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


