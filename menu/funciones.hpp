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
//Creditos: FisiCode
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

void dibujarTitulo(int x, int y, const string& titulo) {
    // Mueve el cursor a la posición (x, y) en la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);

    // Imprime el título
    cout << titulo << endl;
}

void dibujarMenu(int x, int y, const vector<string>& opciones) {
    for (int i = 0; i < static_cast<int>(opciones.size()); i++) {
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

enum ConsoleColor {
    Black = 0,
    Blue = BACKGROUND_BLUE,
    Green = BACKGROUND_GREEN,
    Red = BACKGROUND_RED,
    Intensity = BACKGROUND_INTENSITY
    };

void setColor(ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void CenterConsoleWindow() {
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectClient.right - rectClient.left) / 2, 
    posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectClient.bottom - rectClient.top) / 2,

    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}
#endif // USERMANAGEMENT_HPP