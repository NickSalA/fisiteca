#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <codecvt>

using namespace std;

void configurarConsolaUtf8() {
    setlocale(LC_ALL, "es_ES.UTF-8"); 
}

bool verificarCredenciales(const wstring& usuario, const wstring& contraseña) {
    wifstream archivo("credAdmin.txt");
    
    if (archivo.fail()) {
        wcout << L"Error: No se pudo abrir el archivo 'credAdmin.txt'." << endl;
        return false;
    }
    
    wstring usuarioGuardado;
    wstring contraseñaGuardada;
    
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }
    
    archivo.close();
    return false;
}

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
    gotoxy(x + 12, y + 4); wcout << L"USUARIO:";
    gotoxy(x + 36, y + 4); wcout << L"____________________";
    gotoxy(x + 12, y + 7); wcout << L"CONTRASEÑA:";
    gotoxy(x + 36, y + 7); wcout << L"____________________";
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

    wstring usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;
    do {
        dibujarInterfaz(x, y, anchoInterfaz, altoInterfaz);
        gotoxy(x + 36, y + 4); wcout << L"                    ";
        gotoxy(x + 36, y + 4); getline(wcin, usuarioIngresado);
        if (usuarioIngresado.empty()) {
            gotoxy(x + 2, y + 14); wcout << L"El nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 7); wcout << L"                    ";
        gotoxy(x + 36, y + 7); getline(wcin, contraseñaIngresada);
        if (contraseñaIngresada.empty()) {
            gotoxy(x + 2, y + 14); wcout << L"La contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        if (!verificarCredenciales(usuarioIngresado, contraseñaIngresada)) {
            gotoxy(x + 2, y + 14); wcout << L"Error: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl << endl;
            continue;
        }
        credencialesCorrectas = true;
        gotoxy(x + 2, y + 10); wcout << L"¡Bienvenido, " << usuarioIngresado << L"! Has ingresado correctamente como administrador." << endl << endl;

    } while (!credencialesCorrectas);

    return 0;
}
