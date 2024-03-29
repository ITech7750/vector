#include "vector.h"
#include <stdio.h>

// Создаем новый вектор
Vector *new_vector(int capacity, int type) {
    // Выделяем память для структуры вектора
    Vector *v = malloc(sizeof(Vector));
    
    // Выделяем память для массива указателей на элементы вектора
    v->data = malloc(sizeof(void *) * capacity);
    
    // Инициализируем текущий размер и емкость вектора
    v->size = 0;
    v->capacity = capacity;
    v->type = type;
    // Возвращаем указатель на созданный вектор
    return v;
}

// Освобождаем память, занимаемую вектором
void free_vector(Vector *v) {

    // Освобождаем память для массива указателей на элементы вектора
    free(v->data);
    
    // Освобождаем память для структуры вектора
    free(v);
}

// Добавляем элемент в конец вектора
void push_back(Vector *v, void *value) {
    // Проверяем, нужно ли увеличить емкость вектора
    if (v->size == v->capacity) {
        // Удваиваем емкость вектора
        v->capacity *= 2;
        
        // Перевыделяем память для массива указателей на элементы вектора
        v->data = realloc(v->data, sizeof(void *) * v->capacity);
    }
    
    // Добавляем элемент в конец вектора
    v->data[v->size++] = value;
}

// Получаем элемент вектора по индексу
void *get(Vector *v, int index) {
    // Проверяем, находится ли индекс в пределах вектора
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(1);
    }
    
    // Возвращаем указатель на элемент вектора по индексу
    return v->data[index];
}


// Вычисляем векторное сложение двух векторов
Vector *vector_add(Vector *v1, Vector *v2) {
    // Проверяем, имеют ли векторы одинаковый размер
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors must have the same size\n");
        exit(1);
    }
    
    // Создаем новый вектор для результата
    Vector *result = new_vector(v1->size,v1->type);
    
    // Цикл для сложения элементов векторов
    for (int i = 0; i < v1->size; i++) {
        // Проверяем, являются ли элементы не пустыми
        if (v1->data[i] != NULL && v2->data[i] != NULL) {

            if (v1->type == COMPLEX){
                // Получаем указатели на комплексные числа
                Complex *c1 = v1->data[i];
                Complex *c2 = v2->data[i];
                
                // Создаем новое комплексное число для результата
                Complex *c3 = malloc(sizeof(Complex));
                
                // Складываем вещественные и мнимые части комплексных чисел
                c3->real = c1->real + c2->real;
                c3->imag = c1->imag + c2->imag;
                
                // Добавляем результирующее комплексное число в вектор результата
                push_back(result, c3);

            } else {
               
                // Вычисляем сумму обычных чисел
                double *value1 = v1->data[i];
                double *value2 = v2->data[i];
                double *result_value = malloc(sizeof(double));
                *result_value = *value1 + *value2;
                
                // Добавляем сумму в вектор результата
                push_back(result, result_value);
            }
        
        } else {
            // Добавляем `NULL` в вектор результата
            push_back(result, NULL);
        }
    }
    
    // Возвращаем вектор результата
    return result;
}


// Вычисляем скалярное произведение двух векторов
Complex scalar_product(Vector *v1, Vector *v2) {
    // Проверяем, имеют ли векторы одинаковый размер
    if (v1->size != v2->size) {
        fprintf(stderr, "Error: Vectors must have the same size\n");
        exit(1);
    }
    


    Complex result = {0.0, 0.0};


    for (int i = 0; i < v1->size; i++) {
        // Проверяем, являются ли элементы не пустыми
        if (v1->data[i] != NULL && v2->data[i] != NULL) {
                if (v1->type == COMPLEX){
                    // Вычисляет произведение комплексных чисел
                    Complex *value1 = v1->data[i];
                    Complex *value2 = v2->data[i];
                    //result.real += value1->real * value2->real + value1->imag * value2->imag;
                    //result.imag += value1->real * value2->imag - value1->imag * value2->real;
                    result.real += value1->real * value2->real;
                    result.imag += + value1->imag * value2->imag;
        
                } else {
                    // Вычисляет произведение обычных чисел
                    double *value1 = v1->data[i];
                    double *value2 = v2->data[i];
                    result.real += *value1 * *value2;
            }
        }
    }
    
    // Возвращаем скалярное произведение
    return result;
}

// Выводим вектор
void print_vector(Vector *v) {
    printf("[");
    
    // Выводит элементы вектора
    for (int i = 0; i < v->size; i++) {
        // Проверяем, являемся ли элемент не пустым
        if (v->data[i] != NULL) {
            if (v->type == COMPLEX){
            // Выводит значение элемента
            void *value = v->data[i];
            printf("%.2f + i*%.2f", ((Complex *)value)->real, ((Complex *)value)->imag);}
            else {
                // Выводит обычное число
                double *value = v->data[i];
                printf("%.2f", *value);
                }
        } else {
            // Выводит `NULL`
            printf("NULL");
        }
        
        // Выводит запятую, если это не последний элемент
        if (i < v->size - 1) {
            printf(", ");
        }
    }
    
    printf("]\n");
}
