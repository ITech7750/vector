#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>


typedef struct Vector {

    size_t size; // размер вектора.

    size_t capacity; // емкость вектора.

    void** data; // указатель на массив элементов вектора.

    //  ф-я сравнения, которая возвращает true, если два элемента равны, и false в противном случае.

    bool (*equals)(const void*, const void*); 

    //ф-я которая печатает указанный элемент.

    void (*print)(const void*);

    // ф-я сложения, которая возвращает новый элемент, являющийся суммой двух указанных элементов.
    void* (*add)(const void*, const void*);

    //ф-я скалярного произведения, которая возвращает скалярное произведение двух указанных элементов.
    double (*scalar_product)(const void*, const void*);
} Vector;


Vector* vector_new(size_t capacity, bool (*equals)(const void*, const void*), void (*print)(const void*), void* (*add)(const void*, const void*), double (*scalar_product)(const void*, const void*));


void vector_free(Vector* v);

bool vector_empty(const Vector* v);

size_t vector_size(const Vector* v);

void vector_push_back(Vector* v, const void* value);

void* vector_get(const Vector* v, size_t index);

void vector_print(const Vector* v);

Vector* vector_add(const Vector* v1, const Vector* v2);

double vector_scalar_product(const Vector* v1, const Vector* v2);

#endif
