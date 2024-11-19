#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "arcana.h"
#include "utils.h"
#include "main.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctime>


int pos = 0;

void Menu() {
    char menu[4][50] = { "1. Ввести Дату Рождения", "2. Вывести Аркан", "3. Вывести лог", "4. Выход" };
    char marker[5] = "<-";
    for (int i = 0; i < 4; ++i) {
        printf("%s", menu[i]);
        if (i == pos) {
            printf(" %s", marker);
        }
        printf("\n");
    }
}

void handleAction(int choice) {
    system("cls"); // Очищаем консоль
    char input[20];
    time_t start, end;
    double duration; // Переменная для хранения времени выполнения функции
    system("color 41"); // Устанавливаем цвет консоли
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 6);

    switch (choice) {
    case 0: { // Ввод даты рождения
        int isValidDate = 0;
        while (!isValidDate) {
            printf("Введите дату рождения (пример: день.месяц.год): ");
            scanf("%s", input);

            if (sscanf(input, "%d.%d.%d", &day, &month, &year) != 3) {
                printf("Некорректный формат даты. Попробуйте еще раз.\n"); // Выводим сообщение об ошибке
                _getch();
            }
            else if (month < 1 || month > 12) { // Проверяем, корректен ли введенный месяц
                printf("Некорректный ввод. Месяц не должен быть больше 12. Попробуйте еще раз.\n");
                _getch();
            }
            else if (day < 1 || day > 31) { // Проверяем, корректен ли введенный день
                printf("Некорректный ввод. Дней не должно быть больше 31. Попробуйте еще раз.\n");
                _getch(); // Ожидаем нажатия клавиши
            }
            else {
                FILE* logFile;
                if (fopen_s(&logFile, "log.txt", "a") != 0) { // Открываем файл log.txt для добавления в него информации
                    printf("Не удалось открыть файл log.txt\n"); // Выводим сообщение об ошибке
                    _getch(); // Ожидаем нажатия клавиши
                }
                else {
                    fprintf(logFile, "%d.%d.%d\n", day, month, year); // Записываем введенную дату в файл
                    fclose(logFile); // Закрываем файл

                    realdate = true; // Устанавливаем флаг, что дата была введена
                    isValidDate = 1; // Устанавливаем флаг, что дата введена корректно
                    printf("Дата успешно введена!\n");
                    _getch(); // Ожидаем нажатия клавиши
                }
            }
        }
        break;
    }
    case 1: {
        if (realdate) { // Если дата была введена
            start = clock(); // Замеряем время начала выполнения
            int arcana = arcan(day, month, year); // Вычисляем номер аркана
            printf("Ваш аркан: %d\n", arcana); // Выводим номер аркана
            printArcanaDescription(arcana); // Выводим описание аркана
            end = clock(); // Замеряем время окончания выполнения
            duration = ((double)(end - start)) / CLOCKS_PER_SEC; // Вычисляем время выполнения
            printf("Время выполнения: %f секунд\n", duration); // Выводим время выполнения
            _getch(); // Ожидаем нажатия клавиши
        }
        else { // Если дата не была введена
            printf("Введите дату рождения сначала!\n");
            _getch();
        }
        break;
    }
    case 2: { // Вывод лога
        FILE* logFile;
        if (fopen_s(&logFile, "log.txt", "r") != 0) { // Открываем файл log.txt для чтения
            printf("Не удалось открыть файл log.txt\n");
            _getch();
            break;
        }

        char line[256]; // Массив для хранения строки из файла
        while (fgets(line, sizeof(line), logFile)) { // Читаем файл построчно
            printf("%s", line); // Выводим строку
        }

        fclose(logFile);
        _getch();
        break;
    }
    case 3: {
        exit(0); // Завершаем программу
    }
    default: {
        printf("Некорректный ввод.\n"); // Выводим сообщение об ошибке
        _getch();
        break;
    }
    }
}