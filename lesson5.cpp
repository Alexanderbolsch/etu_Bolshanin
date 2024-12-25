#define CATCH_CONFIG_MAIN
#include"Catch2/catch_all.hpp"
#include "menu.h"
#include "arcana.h"
#include "utils.h"
#include "main.h"
#include <filesystem>



// ����� ��� ��������� ����������������� ����� � ������������ ������ ����������
TEST_CASE("�������� ������������ ��������� ���������� �������� �����", "[input]") {
    REQUIRE(arcan(1, 1, 2000) == 4);
    REQUIRE(arcan(31, 12, 1999) == 7);
}

TEST_CASE("�������� ��������� ��� ������������ ���������", "[input]") {
    int day, month, year;
    char input[] = "32.13.2000";
    REQUIRE(sscanf(input, "%d.%d.%d", &day, &month, &year) != 3);
    char input2[] = "abc.def.ghij";
    REQUIRE(sscanf(input2, "%d.%d.%d", &day, &month, &year) != 3);
}

TEST_CASE("�������� ��������� �������� ���������", "[boundary]") {
    REQUIRE(arcan(1, 1, 1900) == 4);
    REQUIRE(arcan(31, 12, 2100) == 7);
}

TEST_CASE("�������� ������������ �������� � ����������� �� ������� ������", "[calculation]") {
    REQUIRE(arcan(15, 8, 1995) == 20);
    REQUIRE(arcan(22, 2, 2022) == 11);
}

// ����� ��� ������ � �������
TEST_CASE("��������, ��� ������ ��������� ������������ � ����", "[file]") {
    FILE* logFile = fopen("log_test.txt", "w");
    REQUIRE(logFile != nullptr);
    fprintf(logFile, "01.01.2000\n");
    fclose(logFile);

    logFile = fopen("log_test.txt", "r");
    REQUIRE(logFile != nullptr);
    char line[20];
    fgets(line, sizeof(line), logFile);
    fclose(logFile);

    REQUIRE(strcmp(line, "01.01.2000\n") == 0);
    remove("log_test.txt"); // ������� �������� ���� ����� ��������
}

TEST_CASE("���������, ��� ���� ��������� ��� ����������� ��� �������������", "[file]") {
    FILE* logFile = fopen("log_test.txt", "w");
    REQUIRE(logFile != nullptr);
    fprintf(logFile, "01.01.2000\n");
    fclose(logFile);

    logFile = fopen("log_test.txt", "w"); // ��������� ���� ����� ��� ������
    REQUIRE(logFile != nullptr);
    fprintf(logFile, "02.02.2000\n");
    fclose(logFile);

    logFile = fopen("log_test.txt", "r");
    REQUIRE(logFile != nullptr);
    char line[20];
    fgets(line, sizeof(line), logFile);
    fclose(logFile);

    REQUIRE(strcmp(line, "02.02.2000\n") == 0);
    remove("log_test.txt"); // ������� �������� ���� ����� ��������
}

// ����� ��� ���������� ���������
TEST_CASE("�������� ������������ ������ ���������� ���������", "[interface]") {
    // �������� ��������� ������� ������ (��������, ������� �����/����, Enter, ESC)
    pos = 0;
    int key = 80; // ������� ����
    if (key == 80 && pos < 3) {
        pos++;
    }
    REQUIRE(pos == 1);

    key = 72; // ������� �����
    if (key == 72 && pos > 0) {
        pos--;
    }
    REQUIRE(pos == 0);

    key = 13; // Enter
    REQUIRE(key == 13);

    key = 27; // ESC
    REQUIRE(key == 27);
}