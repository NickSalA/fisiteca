#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <limits>
#include <locale>
#include <chrono>
#include <thread>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#define ARRIBA VK_UP
#define ABAJO VK_DOWN
#define ENTER 13

using namespace std;
// Creditos: FisiCode
struct Libro
{
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
    int cantidad;
};

string xcodigo, xano, xcantidad;

void leerLibro(Libro libros[], string libro, int &n)
{
    ifstream Leer(libro, ios::in);
    if (Leer.fail())
    {
        cout << "Error en el archivo..." << endl;
        exit(1);
    }
    if (Leer.peek() == ifstream::traits_type::eof())
    {
        Leer.close();
        return;
    }
    int i = 0;
    while (!Leer.eof())
    {
        getline(Leer, xcodigo);
        getline(Leer, libros[i].nombre);
        getline(Leer, libros[i].genero);
        getline(Leer, libros[i].autor);
        getline(Leer, xano);
        getline(Leer, libros[i].sinopsis);
        getline(Leer, xcantidad); 
        istringstream(xcodigo) >> libros[i].codigo;
        istringstream(xano) >> libros[i].anoPublicacion;
        istringstream(xcantidad) >> libros[i].cantidad;
        n++;
        i++;
    }
    Leer.close();
}
struct coordXY
{
    int x;
    int y;
    bool operator==(const coordXY &vec) { return (x == vec.x && y == vec.y); }
    bool operator!=(const coordXY &vec) { return !(*this == vec); }
    coordXY operator+(const coordXY &vec) { return {x + vec.x, y + vec.y}; }
    coordXY operator-(const coordXY &vec) { return {x - vec.x, y - vec.y}; }
};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void esperaConMensaje(const string &mensaje)
{
    cout << mensaje << endl;
    _getwch();
}

char getch2()
{
    char c = 0;
    DWORD contador;
    HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInputRecord; // Estructura para el registro de entrada

    // Lee un evento de entrada del teclado
    ReadConsoleInputA(ih, &irInputRecord, 1, &contador);

    // Verifica si el evento es una tecla presionada
    if (irInputRecord.EventType == KEY_EVENT && irInputRecord.Event.KeyEvent.bKeyDown)
    {
        // Extrae el código virtual de la tecla
        c = irInputRecord.Event.KeyEvent.wVirtualKeyCode;

        // Convierte el código virtual a una de las teclas definidas (ARRIBA o ABAJO)
        switch (c)
        {
        case VK_UP:
            c = ARRIBA;
            break;
        case VK_DOWN:
            c = ABAJO;
            break;
        }
    }

    return c;
}

void configurarConsolaUtf8()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void limpiarPantalla()
{
    system("cls");
}

void pausa()
{
    system("pause");
}

enum ConsoleColor
{
    Black = 0,
    Blue = BACKGROUND_BLUE,
    Green = BACKGROUND_GREEN,
    Red = BACKGROUND_RED,
    Intensity = BACKGROUND_INTENSITY,
    White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
};

void setColor(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void dibujarCuadro(int x, int y, int ancho, int alto)
{

    for (int i = 0; i < ancho; i++)
    {
        gotoxy(x + i, y);
        cout << "-";
        gotoxy(x + i, y + alto);
        cout << "-";
    }
    for (int i = 0; i < alto; i++)
    {
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

void dibujarTitulo(int x, int y, const string &titulo)
{
    // Mueve el cursor a la posición (x, y) en la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);

    // Imprime el título
    cout << titulo << endl;
}

void dibujarMenu(int x, int y, const vector<string> &opciones)
{
    std::string::size_type maxWidth = 0;
    for (const string &opcion : opciones)
    {
        if (opcion.length() > maxWidth)
        {
            maxWidth = opcion.length();
        }
    }

    int menuWidth = maxWidth + 6; // Ancho del menú
    int rectHeight = 2;           // Altura del rectángulo individual
    int separacionVertical = 1;   // Separación vertical entre rectángulos

    // Imprimir opciones dentro de rectángulos individuales
    for (size_t i = 0; i < opciones.size(); ++i)
    {
        // Aumentar la posición y para crear separación vertical
        int posY = y + i * (rectHeight + separacionVertical);

        // Dibujar rectángulo alrededor de la opción
        dibujarCuadro(x - 2, posY - 1, menuWidth, rectHeight);

        // Imprimir opción dentro del rectángulo correspondiente
        gotoxy(x, posY);
        cout << i + 1 << ". " << opciones[i];
    }
}

void imprimirOpcion(const string &opcion, bool resaltado)
{
    // Cambiar el color del texto y el fondo según si está resaltado o no
    if (resaltado)
    {
        setColor(Intensity); // O cualquier otro color de texto y fondo que desees para resaltado
    }
    else
    {
        setColor(Green); // O cualquier otro color de texto y fondo que desees para no resaltado
    }

    // Imprimir el rectángulo con la opción dentro
    cout << "   " << opcion << "   ";

    // Restaurar el color original
    setColor(Red); // O cualquier otro color predeterminado que desees
}

void cursorVisible(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void ocultarCursor()
{
    cursorVisible(false);
}

void moverCursor(coordXY pos)
{
    gotoxy(pos.x, pos.y);
}

void CenterConsoleWindow()
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectClient.right - rectClient.left) / 2,
    posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectClient.bottom - rectClient.top) / 2,

    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void dibujarTexto(int x, int y, const string &texto)
{
    gotoxy(x, y);
    cout << texto;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Set_Console_Sizes(const int consola_ancho, const int consola_alto, bool cursor)
{
    std::stringstream ss;
    ss << "MODE CON: COLS=" << consola_ancho << "LINES=" << consola_alto;
    system(ss.str().c_str());
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    CenterConsoleWindow();
    ShowConsoleCursor(cursor);
}

void dibujarTeslaASCII(int x, int y)
{
    gotoxy(x, y);
    cout << "  /\\_/\\  ";
    gotoxy(x, y + 1);
    cout << " ( o.o ) ";
    gotoxy(x, y + 2);
    cout << "  > ^ <  ";
}

void dibujarTituloASCII(int x, int y, const string &titulo)
{
    // Mueve el cursor a la posición (x, y) en la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);

    // Imprime el título
    cout << titulo << endl;
}

void mostrarBarraDeCarga(int x, int y, int duracion, int tamano = 50)
{
    gotoxy(x, y);
    std::cout << "[";
    for (int i = 0; i < tamano; ++i)
    {
        std::cout << " ";
    }
    std::cout << "]\r";
    gotoxy(x + 1, y); // Mueve el cursor dentro de la barra

    for (int i = 0; i < tamano; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(duracion / tamano));
        std::cout << "=";
        std::cout.flush();
    }

    gotoxy(x + tamano + 1, y); // Mueve el cursor al final de la barra
    std::cout << "]" << std::endl;
}

void obtenerDimensionConsola(int &ancho, int &alto)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void dibujarInterfazRegistrar(int x, int y, int ancho, int alto)
{
    for (int i = 0; i <= ancho; i++)
    {
        gotoxy(x + i, y);
        cout << "-";
        gotoxy(x + i, y + alto);
        cout << "-";
    }
    for (int i = 0; i <= alto; i++)
    {
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
    gotoxy(x + 12, y + 4);
    cout << "CREAR USUARIO:";
    gotoxy(x + 36, y + 4);
    cout << "____________________";
    gotoxy(x + 12, y + 7);
    cout << "CREAR CONTRASEÑA:";
    gotoxy(x + 36, y + 7);
    cout << "____________________";
    gotoxy(x + 12, y + 10);
    cout << "CONFIRMAR CONTRASEÑA:";
    gotoxy(x + 36, y + 10);
    cout << "____________________";
}

void dibujarInterfazUser(int x, int y, int ancho, int alto)
{
    for (int i = 0; i <= ancho; i++)
    {
        gotoxy(x + i, y);
        cout << "-";
        gotoxy(x + i, y + alto);
        cout << "-";
    }
    for (int i = 0; i <= alto; i++)
    {
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
    gotoxy(x + 12, y + 4);
    cout << "USUARIO:";
    gotoxy(x + 36, y + 4);
    cout << "____________________";
    gotoxy(x + 12, y + 7);
    cout << "CONTRASEÑA:";
    gotoxy(x + 36, y + 7);
    cout << "____________________";
}

bool esNumero(const string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}
string obteneFechaHora()
{
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);
    stringstream ss;
    ss << localTime.wDay << "/" << localTime.wMonth << "/" << localTime.wYear;
    return ss.str();
}
string obtenerFechaPlazo()
{
    stringstream sS;
    int daysInMonth;
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);

    // Determinar la cantidad de días en el mes actual
    if (localTime.wMonth == 1 || localTime.wMonth == 3 || localTime.wMonth == 5 || localTime.wMonth == 7 || localTime.wMonth == 8 || localTime.wMonth == 10 || localTime.wMonth == 12)
    {
        daysInMonth = 31;
    }
    else if (localTime.wMonth == 4 || localTime.wMonth == 6 || localTime.wMonth == 9 || localTime.wMonth == 11)
    {
        daysInMonth = 30;
    }
    else if (localTime.wMonth == 2)
    {
        if ((localTime.wYear % 4 == 0 && localTime.wYear % 100 != 0) || localTime.wYear % 400 == 0)
        {
            daysInMonth = 29; // Año bisiesto
        }
        else
        {
            daysInMonth = 28;
        }
    }

    int diaPlazo = localTime.wDay + 7;

    // Ajustar el mes y el año si la suma de días excede el número de días en el mes actual
    while (diaPlazo > daysInMonth)
    {
        diaPlazo -= daysInMonth;
        localTime.wMonth++;
    }

    sS << diaPlazo << "/" << localTime.wMonth << "/" << localTime.wYear;
    return sS.str();
}
#endif // FUNCIONES_HPP