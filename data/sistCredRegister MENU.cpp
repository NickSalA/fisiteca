#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <codecvt>

using namespace std;

void gotoxy(int x, int y) {
    COORD dwPos = { .X = x, .Y = y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
}

void obtenerDimensionConsola(int& ancho, int& alto) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void dibujarInterfaz(int x, int y, int ancho, int alto) {
    system("color F0");
    for (int i = 0; i <= ancho; i++) {
        gotoxy(x + i, y); wcout << L"-";
        gotoxy(x + i, y + alto); wcout << L"-";
    }
    for (int i = 0; i <= alto; i++) {
        gotoxy(x, y + i); wcout << L"|";
        gotoxy(x + ancho, y + i); wcout << L"|";
    }
    gotoxy(x, y); wcout << L"┌";
    gotoxy(x + ancho, y); wcout << L"┐";
    gotoxy(x, y + alto); wcout << L"└";
    gotoxy(x + ancho, y + alto); wcout << L"┘";
    gotoxy(x + 12, y + 4); wcout << L"CREAR USUARIO:";
    gotoxy(x + 36, y + 4); wcout << L"____________________";
    gotoxy(x + 12, y + 7); wcout << L"CREAR CONTRASEÑA:";
    gotoxy(x + 36, y + 7); wcout << L"____________________";
    gotoxy(x + 12, y + 10); wcout << L"CONFIRMAR CONTRASEÑA:";
    gotoxy(x + 36, y + 10); wcout << L"____________________";
}

bool usuarioExiste(const wstring& usuario) {
    wifstream archivo("credUsuario.txt");
    archivo.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
    wstring linea;
    while (getline(archivo, linea)) {
        if (linea == usuario) {
            return true;
        }
    }
    return false;
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int anchoConsola, altoConsola;
    obtenerDimensionConsola(anchoConsola, altoConsola);
    int anchoInterfaz = 70;
    int altoInterfaz = 15;
    int x = (anchoConsola - anchoInterfaz) / 2;
    int y = (altoConsola - altoInterfaz) / 2;

    wstring usuario, contrasena, confirmar_contrasena;
    bool registrado = false;
    while (!registrado) {
        dibujarInterfaz(x, y, anchoInterfaz, altoInterfaz);
        gotoxy(x + 36, y + 4); wcout << L"                    ";
        gotoxy(x + 36, y + 4); getline(wcin, usuario);
        if (usuario.empty()) {
            gotoxy(x + 2, y + 14); wcout << L"El nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        if (usuarioExiste(usuario)) {
            gotoxy(x + 2, y + 14); wcout << L"El usuario ya existe. Introduce un nombre de usuario diferente." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 7); wcout << L"                    ";
        gotoxy(x + 36, y + 7); getline(wcin, contrasena);
        if (contrasena.empty()) {
            gotoxy(x + 2, y + 14); wcout << L"La contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 10); wcout << L"                    ";
        gotoxy(x + 36, y + 10); getline(wcin, confirmar_contrasena);
        if (contrasena != confirmar_contrasena) {
            gotoxy(x + 2, y + 14); wcout << L"Las contraseñas no coinciden. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        wofstream archivo("credUsuario.txt", ios::app);
        archivo.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
        if (!archivo.is_open()) {
            gotoxy(x + 2, y + 14); wcout << L"Error al abrir el archivo." << endl;
            return 1;
        }
        archivo << usuario << endl << contrasena << endl;
        registrado = true;
        gotoxy(x + 2, y + 14); wcout << L"Registro exitoso. ¡Te has registrado correctamente!" << endl;
    }
    return 0;
}