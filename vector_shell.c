#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_test.c"

// Интерфейс командной строки
enum Command {
    EXIT,
    INPUT_VECTORS,
    INPUT_COMPLEX_VECTORS,
    VECTOR_SUM,
    SCALAR_PRODUCT,
    TEST
};

// Отображение команды с ее номером
char* command_names[] = {
    "Выход",
    "Ввод векторов",
    "Ввод комплексных векторов",
    "Сумма векторов",
    "Скалярное произведение векторов",
    "Тестирование"
};

// Функции для обработки команд
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

        // Выделяем память для элемента вектора
        double* element = malloc(sizeof(double));
        *element = value;

        vector_push_back(*v1, element);
    }

    printf("Введите элементы второго вектора:\n");
    for (int i = 0; i < size; i++) {
        double value;
        scanf("%lf", &value);

        // Выделяем память для элемента вектора
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

        // Выделяем память для элемента вектора
        Complex* element = malloc(sizeof(Complex));
        element->real = real;
        element->imag = imag;

        vector_push_back(*v1, element);
    }

    printf("Введите элементы второго вектора (вещественная часть, мнимая часть):\n");
    for (int i = 0; i < size; i++) {
        double real, imag;
        scanf("%lf %lf", &real, &imag);

        // Выделяем память для элемента вектора
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
        // Сумма векторов действительных чисел
        Vector* result = vector_new(v1->size, real_equals, print_real, add_real, scalar_product_real);

        for (size_t i = 0; i < v1->size; i++) {
            // Складываем действительные числа
            double* r1 = v1->data[i];
            double* r2 = v2->data[i];
            double* sum = add_real(r1, r2);

            // Добавляем сумму в результирующий вектор
            vector_push_back(result, sum);
        }

        printf("Сумма векторов:\n");
        vector_print(result);

        vector_free(result);
    } else if (v1->equals == complex_equals) {
        // Сумма векторов комплексных чисел
        Vector* result = vector_new(v1->size, complex_equals, print_complex, add_complex, scalar_product_complex);

        for (size_t i = 0; i < v1->size; i++) {
            // Складываем комплексные числа
            Complex* c1 = v1->data[i];
            Complex* c2 = v2->data[i];
            Complex* sum = add_complex(c1, c2);

            // Добавляем сумму в результирующий вектор
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

    if (v1->equals == real_equals) {
        // Скалярное произведение векторов действительных чисел
        double scalar_product = 0;

        for (size_t i = 0; i < v1->size; i++) {
            // Вычисляем скалярное произведение действительных чисел
            double* r1 = v1->data[i];
            double* r2 = v2->data[i];
            scalar_product += (*r1) * (*r2);
        }

        printf("Скалярное произведение векторов: %.2f\n", scalar_product);
    } else if (v1->equals == complex_equals) {
        // Скалярное произведение векторов комплексных чисел
        double scalar_product = 0;

        for (size_t i = 0; i < v1->size; i++) {
            // Вычисляем скалярное произведение комплексных чисел
            Complex* c1 = v1->data[i];
            Complex* c2 = v2->data[i];
            scalar_product += scalar_product_complex(c1, c2);
        }

        printf("Скалярное произведение векторов: %.2f\n", scalar_product);
    } else {
        printf("Ошибка: неизвестный тип данных\n");
    }
}

void test() {
    test_vector_complex();
    test_vector_real();
}

int main() {
    puts("\033[01;32m");
    for (int i = 0; i < 50; i++) {
        printf("#");
    }
    printf("#                                                 #\n");
    printf("#       ______    ______    ______    __          #\n");
    printf("#       ||||||    ||||||    ||||||    ||          #\n");
    printf("#         ||        ||      ||        ||          #\n");
    printf("#         ||        ||      ||||||    |||||\\      #\n");
    printf("#         ||        ||      ||        ||   ||     #\n");
    printf("#       ||||||      ||      ||||||    ||   ||     #\n");
    printf("#                                                 #\n");
   
    
    for (int i = 0; i < 51; i++) {
        printf("#");
    }
    puts("\033[01;37m");
    
    // Векторы для хранения ввода пользователя

    Vector* v1 = NULL;
    Vector* v2 = NULL;

    // Цикл командной строки
    while (true) {
        // Вывод меню
        printf("\nВыберите команду:\n");
        for (int i = 0; i < sizeof(command_names) / sizeof(char*); i++) {
            printf("%d. %s\n", i + 1, command_names[i]);
        }
        printf("0. Выход\n");

        // Ввод команды
        int command;
        scanf("%d", &command);

        // Обработка команды
        switch (command-1) {
            case EXIT:
                return 0;
            case INPUT_VECTORS:
                input_vectors(&v1, &v2);
                break;
            case INPUT_COMPLEX_VECTORS:
                input_complex_vectors(&v1, &v2);
                break;
            case VECTOR_SUM:
                vector_sum(v1, v2);
                break;
            case SCALAR_PRODUCT:
                scalar_product(v1, v2);
                break;
            case TEST:
                test();
                break;
            default:
                printf("Неизвестная команда\n");
                break;
        }
    }

    return 0;
}
