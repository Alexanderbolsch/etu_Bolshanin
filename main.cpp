#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "menu.h"
#include "arcana.h"
#include "utils.h"
#include "main.h"

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