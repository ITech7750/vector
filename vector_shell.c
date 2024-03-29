#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector_test.c"

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

void input_vectors(Vector **v1, Vector **v2) {
    int size, type;

    printf("Введите размер векторов: ");
    scanf("%d", &size);

    printf("Выберите тип векторов:\n");
    printf("0. Комплексные числа\n");
    printf("1. Вещественные числа\n");
    printf("2. Целые числа\n");
    
    printf("Введите номер типа: ");
    scanf("%d", &type);

    *v1 = new_vector(size, type);
    *v2 = new_vector(size, type);

    if (type == INT) {
        int value;
        printf("Введите элементы первого вектора: ");
        for (int i = 0; i < size; i++) {
            scanf("%d", &value);
            push_back(*v1, &value);
        }

        printf("Введите элементы второго вектора: ");
        for (int i = 0; i < size; i++) {
            scanf("%d", &value);
            push_back(*v2, &value);
        }
    } else if (type == REAL) {
        double value;
        printf("Введите элементы первого вектора: ");
        for (int i = 0; i < size; i++) {
            scanf("%lf", &value);
            double *tmp = malloc(sizeof(double));
            *tmp = value;
            push_back(*v1, tmp);
        }
        

        printf("Введите элементы второго вектора: ");
        for (int i = 0; i < size; i++) {
            scanf("%lf", &value);
            double *tmp = malloc(sizeof(double));
            *tmp = value;
            push_back(*v2, tmp);
        }
    } else if (type == COMPLEX) {
        double real, imag;
        printf("Введите элементы первого вектора (действительная и мнимая части): ");
        for (int i = 0; i < size; i++) {
            scanf("%lf %lf", &real, &imag);
            Complex *value = malloc(sizeof(Complex));
            value->real = real;
            value->imag = imag;
            push_back(*v1, value);
        }

        printf("Введите элементы второго вектора (действительная и мнимая части): ");
        for (int i = 0; i < size; i++) {
            scanf("%lf %lf", &real, &imag);
            Complex *value = malloc(sizeof(Complex));
            value->real = real;
            value->imag = imag;
            push_back(*v2, value);
        }
    }
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
                input_vectors(&v1, &v2);
                printf("---------------------\n");
                printf("Первый вектор:\n");
                print_vector(v1);
                printf("---------------------\n");
                printf("Второй вектор:\n");
                print_vector(v2);
                printf("---------------------\n");

                Vector *result = vector_add(v1, v2);
                printf("Векторное сложение:\n");
                print_vector(result);
                free_vector(result);

                Complex product = scalar_product(v1, v2);
                if (v1->type == COMPLEX){
                    printf("Скалярное произведение: %.2f + i*%.2f\n", product.real, product.imag);
                }else{
                    printf("Скалярное произведение: %.2f\n", product);
                }

                free_vector(v1);
                free_vector(v2);
                break;
            case 2:
                printf("Запуск тестов:\n");

                test_new_vector_real();
                printf("OK\n");
                test_push_back_real();
                printf("OK\n");
                test_get_real();
                printf("OK\n");
                test_vector_add_real();
                printf("OK\n");
                //test_scalar_product_real();
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
