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

void* scalar_product_complex(const void* c1, const void* c2) {
    const Complex* complex1 = (const Complex*)c1;
    const Complex* complex2 = (const Complex*)c2;
    Complex* result = malloc(sizeof(Complex));
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    result->real = complex1->real * complex2->real + complex1->imag * complex2->imag;
    result->imag = complex1->imag * complex2->real + complex1->real * complex2->imag;

    return result;
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

void* scalar_product_real(const void* r1, const void* r2) {
    const Real* real1 = (const Real*)r1;
    const Real* real2 = (const Real*)r2;
    Real* result = malloc(sizeof(Real));
    *result = (*real1) * (*real2);
    return result;
}



void input_vectors(Vector** v1, Vector** v2) {
    printf("Введите размер векторов: ");
    int size;
    scanf("%d", &size);

    *v1 = vector_new(size, real_equals, print_real, add_real, scalar_product_real);
    *v2 = vector_new(size, real_equals, print_real, add_real, scalar_product_real);

    printf("Введите элементы первого вектора:\n");
    for (int i = 0; i < size; i++) {
        double value;
        scanf("%lf", &value);

       
        
        double* element = malloc(sizeof(double));
        *element = value;

        vector_push_back(*v1, element);
    }

    printf("Введите элементы второго вектора:\n");
    for (int i = 0; i < size; i++) {
        double value;
        scanf("%lf", &value);


        double* element = malloc(sizeof(double));
        *element = value;

        vector_push_back(*v2, element);
    }
}

void input_complex_vectors(Vector** v1, Vector** v2) {
    printf("Введите размер векторов: ");
    int size;
    scanf("%d", &size);

    *v1 = vector_new(size, complex_equals, print_complex, add_complex, scalar_product_complex);
    *v2 = vector_new(size, complex_equals, print_complex, add_complex, scalar_product_complex);

    printf("Введите элементы первого вектора (вещественная часть, мнимая часть):\n");
    for (int i = 0; i < size; i++) {
        double real, imag;
        scanf("%lf %lf", &real, &imag);

    
        Complex* element = malloc(sizeof(Complex));
        element->real = real;
        element->imag = imag;

        vector_push_back(*v1, element);
    }

    printf("Введите элементы второго вектора (вещественная часть, мнимая часть):\n");
    for (int i = 0; i < size; i++) {
        double real, imag;
        scanf("%lf %lf", &real, &imag);

    
        Complex* element = malloc(sizeof(Complex));
        element->real = real;
        element->imag = imag;

        vector_push_back(*v2, element);
    }
}

void vector_sum(Vector* v1, Vector* v2) {
    if (v1->size != v2->size) {
        printf("Ошибка: векторы должны иметь одинаковый размер\n");
        return;
    }

    if (v1->equals == real_equals) {
        
        Vector* result = vector_new(v1->size, real_equals, print_real, add_real, scalar_product_real);

        for (size_t i = 0; i < v1->size; i++) {
        
            double* r1 = v1->data[i];
            double* r2 = v2->data[i];
            double* sum = add_real(r1, r2);

            vector_push_back(result, sum);
        }

        printf("Сумма векторов:\n");
        vector_print(result);

        vector_free(result);
    } else if (v1->equals == complex_equals) {
       
        Vector* result = vector_new(v1->size, complex_equals, print_complex, add_complex, scalar_product_complex);

        for (size_t i = 0; i < v1->size; i++) {
            
            Complex* c1 = v1->data[i];
            Complex* c2 = v2->data[i];
            Complex* sum = add_complex(c1, c2);

        
            vector_push_back(result, sum);
        }

        printf("Сумма векторов:\n");
        vector_print(result);

        vector_free(result);
    } else {
        printf("Ошибка: неизвестный тип данных\n");
    }
}

void scalar_product(Vector* v1, Vector* v2) {
    if (v1->size != v2->size) {
        printf("Ошибка: векторы должны иметь одинаковый размер\n");
        return;
    }

    void* result = NULL;

    for (size_t i = 0; i < v1->size; i++) {
        void* partial_result = v1->scalar_product(v1->data[i], v2->data[i]);
        if (result == NULL) {
            result = partial_result;
        } else {
            void* new_result = v1->add(result, partial_result);
            //free(result); 
            //free(partial_result); 
            result = new_result;
        }
    }

    if (v1->equals == real_equals) {
        double real_result = *((double*)result);
        printf("Скалярное произведение векторов: %.2f\n", real_result);
    } else if (v1->equals == complex_equals) {
        Complex* complex_result = (Complex*)result;
        printf("Скалярное произведение векторов: %.2f + %.2fi\n", complex_result->real, complex_result->imag);
        //free(complex_result); 
    } else {
        printf("Ошибка: неизвестный тип данных\n");
    }

    //free(result); 
}
