#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include "arcana.h"
#include "main.h"

int day, month, year; // Переменные для хранения даты рождения
bool realdate = false;

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