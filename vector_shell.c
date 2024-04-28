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





void print_annotation() {
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
}

void start() {
    print_annotation();
    // Векторы для хранения ввода пользователя
    Vector* v1 = NULL;
    Vector* v2 = NULL;

    // Цикл командной строки
    while (1) {
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
                return;
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
}

