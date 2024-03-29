#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

// Тип вектора
typedef struct {
    void **data;     // Массив указателей на элементы вектора
    int size;       // Текущий размер вектора
    int capacity;   // Текущая емкость вектора
} Vector;

// Тип комплексного числа
typedef struct {
    double real;    // Вещественная часть
    double imag;    // Мнимая часть
} Complex;

// Создает новый вектор
Vector *new_vector(int capacity);

// Освобождает память, занимаемую вектором
void free_vector(Vector *v);

// Добавляет элемент в конец вектора
void push_back(Vector *v, void *value);

// Получает элемент вектора по индексу
void *get(Vector *v, int index);

// Вычисляет векторное сложение двух векторов
Vector *vector_add(Vector *v1, Vector *v2);

// Вычисляет скалярное произведение двух векторов
double scalar_product(Vector *v1, Vector *v2);

// Печатает вектор
void print_vector(Vector *v);

#endif  // VECTOR_H
