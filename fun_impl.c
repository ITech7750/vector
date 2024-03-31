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