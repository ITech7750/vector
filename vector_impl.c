#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Vector* vector_new(size_t capacity, bool (*equals)(const void*, const void*), void (*print)(const void*), void* (*add)(const void*, const void*), void* (*scalar_product)(const void*, const void*)) {
    Vector* v = malloc(sizeof(Vector));
    if (v == NULL) {
        return NULL;
    }
    v->size = 0;
    v->capacity = capacity;
    v->data = malloc(sizeof(void*) * capacity);  
    if (v->data == NULL) {
        free(v);
        return NULL;
    }
    v->equals = equals;
    v->print = print;
    v->add = add;
    v->scalar_product = scalar_product;
    return v;
}

void vector_free(Vector* v) {
    free(v->data);
    free(v);
}

bool vector_empty(const Vector* v) {
    return v->size == 0;
}

size_t vector_size(const Vector* v) {
    return v->size;
}

void vector_push_back(Vector* v, const void* value) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(void*) * v->capacity);
    }
    v->data[v->size++] = value;  
}

void* vector_get(const Vector* v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(1);
    }
    return v->data[index];  
}

void vector_print(const Vector* v) {
    printf("[");
    for (size_t i = 0; i < v->size; i++) {
        v->print(v->data[i]);  
        if (i < v->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

Vector* vector_add(const Vector* v1, const Vector* v2) {
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors mcomplex_equalsust have the same size\n");
        exit(1);
    }
    Vector* result = vector_new(v1->size, v1->equals, v1->print, v1->add, v1->scalar_product);
    for (size_t i = 0; i < v1->size; i++) {
        vector_push_back(result, v1->add(v1->data[i], v2->data[i]));
    }
    return result;
}

void* vector_scalar_product(const Vector* v1, const Vector* v2) {
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors must have the same size\n");
        exit(1);
    }
    void* result = NULL;
    for (size_t i = 0; i < v1->size; i++) {
        void* partial = v1->scalar_product(v1->data[i], v2->data[i]);
        if (result == NULL) {
            result = partial;
        } else {
            void* new_result = v1->add(result, partial);
            free(result); 
            result = new_result;
        }
    }
    return result;
}



