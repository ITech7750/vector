#include "vector.h"
#include "vector_impl.c"
#include <stdio.h>
#include <stdlib.h>



int main() {
    // Создаем два вектора
    Vector *v1 = new_vector(4);
    push_back(v1, &(Complex){1.0, 2.0});
    push_back(v1, &(Complex){3.0, 4.0});

    Vector *v2 = new_vector(4);
    push_back(v2, &(Complex){5.0, 6.0});
    push_back(v2, &(Complex){7.0, 8.0});

    // Печатаем векторы
    printf("Первый вектор:\n");
    print_vector(v1);
    printf("Второй вектор:\n");
    print_vector(v2);

    // Вычисляем векторное сложение
    Vector *v3 = vector_add(v1, v2);
    printf("Векторное сложение:\n");
    print_vector(v3);

    // Вычисляем скалярное произведение
    double product = scalar_product(v1, v2);
    printf("Скалярное произведение: %.2f\n", product);

    // Освобождаем память
    free_vector(v1);
    free_vector(v2);
    free_vector(v3);

    return 0;
}


/*
Введите данные для первого вектора:
1 2
3 4
5 6
7 8

Введите данные для второго вектора:
9 10
11 12
13 14
15 16

Первый вектор:
[(1, 2), (3, 4), (5, 6), (7, 8)]
Второй вектор:
[(9, 10), (11, 12), (13, 14), (15, 16)]
Векторное сложение:
[(10, 12), (14, 16), (18, 20), (22, 24)]
Скалярное произведение: 200.00



Введите данные для первого вектора:
1
2
3
4

Введите данные для второго вектора:
5
6
7
8

Первый вектор:
[1.00, 2.00, 3.00, 4.00]
Второй вектор:
[5.00, 6.00, 7.00, 8.00]
Векторное сложение:
[6.00, 8.00, 10.00, 12.00]
Скалярное произведение: 70.00

*/
