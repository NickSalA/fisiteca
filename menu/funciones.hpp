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

enum ConsoleColor {
    Black = 0,
    Blue = BACKGROUND_BLUE,
    Green = BACKGROUND_GREEN,
    Red = BACKGROUND_RED,
    Intensity = BACKGROUND_INTENSITY,
    White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
    };

void setColor(ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void dibujarCuadro(int x, int y, int ancho, int alto) {

    for (int i = 0; i < ancho; i++) {
        gotoxy(x + i, y);
        cout << "-";
        gotoxy(x + i, y + alto);
        cout << "-";
    }
    for (int i = 0; i < alto; i++) {
        gotoxy(x, y + i);
        cout << "|";
        gotoxy(x + ancho, y + i);
        cout << "|";
    }
    gotoxy(x, y);
    cout << "┌";
    gotoxy(x + ancho, y);
    cout << "┐"; 
    gotoxy(x, y + alto);
    cout << "└";
    gotoxy(x + ancho, y + alto);
    cout << "┘";
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
    std::string::size_type maxWidth = 0;
    for (const string& opcion : opciones) {
        if (opcion.length() > maxWidth) {
            maxWidth = opcion.length();
        }
    }

    int menuWidth = maxWidth + 6; // Ancho del menú
    int rectHeight = 2; // Altura del rectángulo individual
    int separacionVertical = 1; // Separación vertical entre rectángulos

    // Imprimir opciones dentro de rectángulos individuales
    for (size_t i = 0; i < opciones.size(); ++i) {
        // Aumentar la posición y para crear separación vertical
        int posY = y + i * (rectHeight + separacionVertical);

        // Dibujar rectángulo alrededor de la opción
        dibujarCuadro(x - 2, posY - 1, menuWidth, rectHeight);

        // Imprimir opción dentro del rectángulo correspondiente
        gotoxy(x, posY);
        cout << i + 1 << ". " << opciones[i];
    }
}

void imprimirOpcion(const string& opcion, bool resaltado) {
    // Cambiar el color del texto y el fondo según si está resaltado o no
    if (resaltado) {
        setColor(Intensity); // O cualquier otro color de texto y fondo que desees para resaltado
    } else {
        setColor(Green); // O cualquier otro color de texto y fondo que desees para no resaltado
    }

    // Imprimir el rectángulo con la opción dentro
    cout << "   " << opcion << "   ";

    // Restaurar el color original
    setColor(Red); // O cualquier otro color predeterminado que desees
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