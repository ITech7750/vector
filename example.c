#include "vector.h"
#include "vector_impl.c"


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

int main() {
    Vector* v = vector_new(2, complex_equals, print_complex, add_complex, scalar_product_complex);
    Complex c1 = {1.0, 2.0};
    Complex c2 = {3.0, 4.0};
    vector_push_back(v, &c1);
    vector_push_back(v, &c2);

    vector_print(v);

    double scalar = vector_scalar_product(v, v);
    printf("Скалярное пр-е: %.2f\n", scalar);


    vector_free(v);

    return 0;
}
