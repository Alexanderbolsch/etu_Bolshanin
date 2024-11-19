#define _CRT_SECURE_NO_WARNINGS  
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <time.h> 
#include <string.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <windows.h>

int pos = 0;
int day, month, year; // Переменные для хранения даты рождения
bool realdate = false;
// Функция для установки цвета текста и фона консоли
void SetColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
    SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | textColor)); // Устанавливаем атрибуты цвета
}

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

// Функция для вычисления номера аркана
int arcan(int day, int month, int year) {
    int sum = 0; // Сумма цифр даты рождения
    sum += (day / 10) + (day % 10); // Суммируем цифры дня
    sum += (month / 10) + (month % 10); // Суммируем цифры месяца
    sum += (year / 1000) + ((year / 100) % 10) + ((year / 10) % 10) + (year % 10); // Суммируем цифры года

    while (sum > 22) { // Если сумма больше 22, вычитаем 22
        sum -= 22;
    }

    return sum; // Возвращаем номер аркана
}


void printArcanaDescription(int arcana) {
    FILE* infoFile = fopen("info.txt", "r");
    setlocale(LC_ALL, "Rus");
    if (infoFile == NULL) { // Если файл не открылся
        fprintf(stderr, "Не удалось открыть файл info.txt\n");
        return;
    }

    char line[256]; // Массив для хранения строки из файла
    int currentLine = 1; // Текущий номер строки
    while (fgets(line, sizeof(line), infoFile)) { // Читаем файл построчно
        if (currentLine == arcana) {
            setlocale(LC_ALL, "Rus");
            printf("Описание аркана: %s\n", line); // Выводим описание аркана
            break;
        }
        currentLine++; // Увеличиваем счетчик строк
    }

    fclose(infoFile); // Закрываем файл
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
        printf("Введите дату рождения (пример: день.месяц.год): ");
        scanf("%s", input);

        if (sscanf(input, "%d.%d.%d", &day, &month, &year) != 3) {
            printf("Некорректный формат даты.\n"); // Выводим сообщение об ошибке
            _getch();
            break; // Прерываем обработку
        }
        if (month < 1 || month > 12) { // Проверяем, корректен ли введенный месяц
            printf("Некорректный ввод. Месяц не должен быть больше 12.\n");
            _getch();
            break;
        }
        if (day < 1 || day > 31) { // Проверяем, корректен ли введенный день
            printf("Некорректный ввод. Дней не должно быть больше 31.\n");
            _getch(); // Ожидаем нажатия клавиши
            break;
        }

        FILE* logFile = fopen("log.txt", "a"); // Открываем файл log.txt для добавления в него информации
        if (!logFile) { // Если файл не открылся
            printf("Не удалось открыть файл log.txt\n"); // Выводим сообщение об ошибке
            _getch(); // Ожидаем нажатия клавиши
            break; // Прерываем обработку
        }
        fprintf(logFile, "%d.%d.%d\n", day, month, year); // Записываем введенную дату в файл
        fclose(logFile); // Закрываем файл

        realdate = true; // Устанавливаем флаг, что дата была введена
        _getch(); // Ожидаем нажатия клавиши
        break; // Прерываем обработку
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
        FILE* logFile = fopen("log.txt", "r"); // Открываем файл log.txt для чтения
        if (!logFile) { // Если файл не открылся
            printf("Не удалось открыть файл log.txt\n");
            _getch();
            break; \
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

int main() {
    system("color 41"); // Устанавливаем цвет консоли
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "rus"); // Устанавливаем русскую локаль для вывода текста
    while (1) { // Бесконечный цикл
        system("cls"); // Очищаем консоль
        SetColor(15, 3);
        Menu(); // Выводим меню
        int choice = _getch(); // Считываем нажатую клавишу
        switch (choice) { // В зависимости от нажатой клавиши выполняем соответствующее действие
        case 72: // Стрелка вверх
            if (pos > 0) {
                pos--;
            }
            break;
        case 80: // Стрелка вниз
            if (pos < 3) {
                pos++;
            }
            break;
        case 13: // Enter
            handleAction(pos); // Вызываем функцию обработки выбранного пункта меню
            break;
        default:
            break;
        }
    }
    return 0;
}