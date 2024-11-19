#include <windows.h>
#include "utils.h"

void SetColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� �������
    SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | textColor)); // ������������� �������� �����
}