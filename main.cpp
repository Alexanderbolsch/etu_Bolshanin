#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "menu.h"
#include "arcana.h"
#include "utils.h"
#include "main.h"

int main() {
    system("color 41"); // ������������� ���� �������
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "rus"); // ������������� ������� ������ ��� ������ ������
    while (1) { // ����������� ����
        system("cls"); // ������� �������
        SetColor(15, 3);
        Menu(); // ������� ����
        int choice = _getch(); // ��������� ������� �������
        switch (choice) { // � ����������� �� ������� ������� ��������� ��������������� ��������
        case 72: // ������� �����
            if (pos > 0) {
                pos--;
            }
            break;
        case 80: // ������� ����
            if (pos < 3) {
                pos++;
            }
            break;
        case 13: // Enter
            handleAction(pos); // �������� ������� ��������� ���������� ������ ����
            break;
        default:
            break;
        }
    }
    return 0;
}