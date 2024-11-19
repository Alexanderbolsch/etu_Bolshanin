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
    char menu[4][50] = { "1. ������ ���� ��������", "2. ������� �����", "3. ������� ���", "4. �����" };
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
    system("cls"); // ������� �������
    char input[20];
    time_t start, end;
    double duration; // ���������� ��� �������� ������� ���������� �������
    system("color 41"); // ������������� ���� �������
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 6);

    switch (choice) {
    case 0: { // ���� ���� ��������
        int isValidDate = 0;
        while (!isValidDate) {
            printf("������� ���� �������� (������: ����.�����.���): ");
            scanf("%s", input);

            if (sscanf(input, "%d.%d.%d", &day, &month, &year) != 3) {
                printf("������������ ������ ����. ���������� ��� ���.\n"); // ������� ��������� �� ������
                _getch();
            }
            else if (month < 1 || month > 12) { // ���������, ��������� �� ��������� �����
                printf("������������ ����. ����� �� ������ ���� ������ 12. ���������� ��� ���.\n");
                _getch();
            }
            else if (day < 1 || day > 31) { // ���������, ��������� �� ��������� ����
                printf("������������ ����. ���� �� ������ ���� ������ 31. ���������� ��� ���.\n");
                _getch(); // ������� ������� �������
            }
            else {
                FILE* logFile;
                if (fopen_s(&logFile, "log.txt", "a") != 0) { // ��������� ���� log.txt ��� ���������� � ���� ����������
                    printf("�� ������� ������� ���� log.txt\n"); // ������� ��������� �� ������
                    _getch(); // ������� ������� �������
                }
                else {
                    fprintf(logFile, "%d.%d.%d\n", day, month, year); // ���������� ��������� ���� � ����
                    fclose(logFile); // ��������� ����

                    realdate = true; // ������������� ����, ��� ���� ���� �������
                    isValidDate = 1; // ������������� ����, ��� ���� ������� ���������
                    printf("���� ������� �������!\n");
                    _getch(); // ������� ������� �������
                }
            }
        }
        break;
    }
    case 1: {
        if (realdate) { // ���� ���� ���� �������
            start = clock(); // �������� ����� ������ ����������
            int arcana = arcan(day, month, year); // ��������� ����� ������
            printf("��� �����: %d\n", arcana); // ������� ����� ������
            printArcanaDescription(arcana); // ������� �������� ������
            end = clock(); // �������� ����� ��������� ����������
            duration = ((double)(end - start)) / CLOCKS_PER_SEC; // ��������� ����� ����������
            printf("����� ����������: %f ������\n", duration); // ������� ����� ����������
            _getch(); // ������� ������� �������
        }
        else { // ���� ���� �� ���� �������
            printf("������� ���� �������� �������!\n");
            _getch();
        }
        break;
    }
    case 2: { // ����� ����
        FILE* logFile;
        if (fopen_s(&logFile, "log.txt", "r") != 0) { // ��������� ���� log.txt ��� ������
            printf("�� ������� ������� ���� log.txt\n");
            _getch();
            break;
        }

        char line[256]; // ������ ��� �������� ������ �� �����
        while (fgets(line, sizeof(line), logFile)) { // ������ ���� ���������
            printf("%s", line); // ������� ������
        }

        fclose(logFile);
        _getch();
        break;
    }
    case 3: {
        exit(0); // ��������� ���������
    }
    default: {
        printf("������������ ����.\n"); // ������� ��������� �� ������
        _getch();
        break;
    }
    }
}