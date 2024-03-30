#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector_test.c"

// это пока не работает усе, завтра допилм ))
void print_menu() {
    printf("\n---------------------------------------------------------\n");
    printf("Добро пожаловать в калькулятор векторов!\n");
    printf("---------------------------------------------------------\n");
    printf("Выберите действие:\n");
    printf("1. Ввести векторы вручную\n");
    printf("2. Запустить тестирование\n");
    printf("3. Выход\n");
    printf("---------------------------------------------------------\n");
    printf("Введите номер действия: ");
}

int get_input() {
    int choice;
    scanf("%d", &choice);
    return choice;
}

void clear_buffer() {
    while (getchar() != '\n');
}


// Функции для создания векторов
Vector* create_complex_vector() {
    Vector* v = vector_new(10, complex_equals, print_complex, add_complex, scalar_product_complex);
    return v;
}

Vector* create_real_vector() {
    Vector* v = vector_new(10, real_equals, print_real, add_real, scalar_product_real);
    return v;
}

// Функция для ввода комплексного вектора
Vector* input_complex_vector() {
    Vector* v;
    v = create_complex_vector();
    int size;
    printf("Введите размер вектора: ");
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
            Complex c;
            printf("Введите комплексное число %d: ", i + 1);
            scanf("%lf %lf", &c.real, &c.imag);
            vector_push_back(v, &c);

    }

    return v;
}


// Функция для ввода вектора вручную
Vector* input_real_vector() {
    Vector* v;
    v = create_real_vector();

    int size;
    printf("Введите размер вектора: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        double r;
        printf("Введите действительное число %d: ", i + 1);
        scanf("%lf", &r);
        vector_push_back(v, &r);
    
    }

    return v;
}


int main() {
    int choice;
    Vector *v1, *v2;

    do {
        print_menu();
        choice = get_input();
        clear_buffer();

        switch (choice) {
            case 1:
                int type;
                printf("Введите тип элементов вектора (1 - комплексные, 2 - действительные): ");
                scanf("%d", &type);

                if (type == 1) {
                    printf("Введите вектор №1:\n");
                    Vector *v1 = input_complex_vector();
                    printf("Введите вектор №2:\n");
                    Vector *v2 = input_complex_vector();

                    Vector *result = vector_add(v1, v2);
                    printf("Векторное сложение:\n");
                    print_complex(result);
                    //free_vector(result);

                } else if (type == 2) {
                    printf("Введите вектор №1:\n");
                    Vector *v1 = input_real_vector();
                    printf("Введите вектор №2:\n");
                    Vector *v2 = input_real_vector();

                    Vector *result = vector_add(v1, v2);
                    printf("Векторное сложение:\n");
                    print_real(result);
                    //free_vector(result);

                } else {
                    printf("Неверный тип элементов вектора!\n");
                    return NULL;
                }


                double scalar = vector_scalar_product(v1, v2);
                printf("Скалярное произведение : %.2f\n", scalar);

                //free_vector(v1);
                //free_vector(v2);
                break;
            case 2:
                printf("Запуск тестов:\n");
                test_vector_complex();
                printf("OK\n");
                test_vector_real();
                printf("OK\n");
                
                break;
            case 3:
                printf("До свидания!\n");
                break;

            default:
                printf("Неверный выбор. Пожалуйста, введите число от 1 до 3.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
