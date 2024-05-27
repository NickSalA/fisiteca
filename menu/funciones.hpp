#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <limits>
#include <locale>

using namespace std;

struct coordXY {
        int x;
        int y;
        bool operator == (const coordXY& vec) { return (x == vec.x && y == vec.y); }
        bool operator != (const coordXY& vec) { return !(*this == vec); }
        coordXY operator + (const coordXY& vec) { return { x + vec.x, y + vec.y }; }
        coordXY operator - (const coordXY& vec) { return { x - vec.x, y - vec.y }; }
    };
void gotoxy (int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void configurarConsolaUtf8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void limpiarPantalla() {
    system("cls");
}

void pausa() {
    system("pause");
}

void dibujarCuadro(int x, int y, int ancho, int alto) {
    for (int i = 0; i < ancho; i++) {
        gotoxy(x + i, y);
        cout << char(205);
        gotoxy(x + i, y + alto);
        cout << char(205);
    }
    for (int i = 0; i < alto; i++) {
        gotoxy(x, y + i);
        cout << char(186);
        gotoxy(x + ancho, y + i);
        cout << char(186);
    }
    gotoxy(x, y);
    cout << char(201);
    gotoxy(x + ancho, y);
    cout << char(187);
    gotoxy(x, y + alto);
    cout << char(200);
    gotoxy(x + ancho, y + alto);
    cout << char(188);
}

void dibujarTitulo(int x, int y, string titulo) {
    int padding = 2; // Espacio adicional a cada lado del título
    gotoxy(x, y);
    cout << char(201);
    for (int i = 0; i < static_cast<int>(titulo.size()) + 2 * padding; i++) {
        cout << char(205);
    }
    cout << char(187);
    gotoxy(x, y + 1);
    cout << char(186);
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << titulo;
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << char(186);
    gotoxy(x, y + 2);
    cout << char(200);
    for (int i = 0; i < static_cast<int>(titulo.size()) + 2 * padding; i++) {
        cout << char(205);
    }
    cout << char(188);
}

void dibujarMenu(int x, int y, vector<string> opciones) {
    for (int i = 0; i < opciones.size(); i++) {
        gotoxy(x, y + i);
        cout << i + 1 << ". " << opciones[i];
    }
}

void cursorVisible(bool visible) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void ocultarCursor() {
    cursorVisible(false);
}

void moverCursor(coordXY pos) {
    gotoxy(pos.x, pos.y);
}

void moverCursorUP(int n) {
    COORD coord;
    coord.X = 0;
    coord.Y = -n;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void moverCursorDOWN(int n) {
    COORD coord;
    coord.X = 0;
    coord.Y = n;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}  

#endif // USERMANAGEMENT_HPP