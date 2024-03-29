#include "vector.h"
#include <stdio.h>

// Создает новый вектор
Vector *new_vector(int capacity) {
    // Выделяет память для структуры вектора
    Vector *v = malloc(sizeof(Vector));
    
    // Выделяет память для массива указателей на элементы вектора
    v->data = malloc(sizeof(void *) * capacity);
    
    // Инициализирует текущий размер и емкость вектора
    v->size = 0;
    v->capacity = capacity;
    
    // Возвращает указатель на созданный вектор
    return v;
}

// Освобождает память, занимаемую вектором
void free_vector(Vector *v) {
    // Освобождает память для каждого элемента вектора
    for (int i = 0; i < v->size; i++) {
        if (v->data[i] != NULL) {
            free(v->data[i]);
        }
    }
    
    // Освобождает память для массива указателей на элементы вектора
    free(v->data);
    
    // Освобождает память для структуры вектора
    free(v);
}

// Добавляет элемент в конец вектора
void push_back(Vector *v, void *value) {
    // Проверяет, нужно ли увеличить емкость вектора
    if (v->size == v->capacity) {
        // Удваивает емкость вектора
        v->capacity *= 2;
        
        // Перевыделяет память для массива указателей на элементы вектора
        v->data = realloc(v->data, sizeof(void *) * v->capacity);
    }
    
    // Добавляет элемент в конец вектора
    v->data[v->size++] = value;
}

// Получает элемент вектора по индексу
void *get(Vector *v, int index) {
    // Проверяет, находится ли индекс в пределах вектора
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(1);
    }
    
    // Возвращает указатель на элемент вектора по индексу
    return v->data[index];
}
// Вычисляет векторное сложение двух векторов
Vector *vector_add(Vector *v1, Vector *v2) {
    // Проверяет, имеют ли векторы одинаковый размер
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors must have the same size\n");
        exit(1);
    }
    
    // Создает новый вектор для результата
    Vector *result = new_vector(v1->size);
    
    // Цикл для сложения элементов векторов
    for (int i = 0; i < v1->size; i++) {
        // Проверяет, являются ли элементы не пустыми
        if (v1->data[i] != NULL && v2->data[i] != NULL) {
            // Получает указатели на комплексные числа
            Complex *c1 = v1->data[i];
            Complex *c2 = v2->data[i];
            
            // Создает новое комплексное число для результата
            Complex *c3 = malloc(sizeof(Complex));
            
            // Складывает вещественные и мнимые части комплексных чисел
            c3->real = c1->real + c2->real;
            c3->imag = c1->imag + c2->imag;
            
            // Добавляет результирующее комплексное число в вектор результата
            push_back(result, c3);
        } else {
            // Добавляет `NULL` в вектор результата
            push_back(result, NULL);
        }
    }
    
    // Возвращает вектор результата
    return result;
}


// Вычисляет скалярное произведение двух векторов
double scalar_product(Vector *v1, Vector *v2) {
    // Проверяет, имеют ли векторы одинаковый размер
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors must have the same size\n");
        exit(1);
    }
    
    // Вычисляет скалярное произведение для каждого элемента вектора
    double result = 0.0;
    for (int i = 0; i < v1->size; i++) {
        // Проверяет, являются ли элементы не пустыми
        if (v1->data[i] != NULL && v2->data[i] != NULL) {
            // Вычисляет произведение элементов
            void *value1 = v1->data[i];
            void *value2 = v2->data[i];
            result += *(double *)value1 * *(double *)value2;
        }
    }
    
    // Возвращает скалярное произведение
    return result;
}

// Печатает вектор
void print_vector(Vector *v) {
    // Выводит открывающую квадратную скобку
    printf("[");
    
    // Выводит элементы вектора
    for (int i = 0; i < v->size; i++) {
        // Проверяет, является ли элемент не пустым
        if (v->data[i] != NULL) {
            // Выводит значение элемента
            void *value = v->data[i];
            printf("(%.2f, %.2f)", ((Complex *)value)->real, ((Complex *)value)->imag);
        } else {
            // Выводит `NULL`
            printf("NULL");
        }
        
        // Выводит запятую, если это не последний элемент
        if (i < v->size - 1) {
            printf(", ");
        }
    }
    
    // Выводит закрывающую квадратную скобку
    printf("]\n");
}
