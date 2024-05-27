#include <windows.h>
#include <iostream>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void limpia();
void vacio();

void gotoxy(int x,int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

void CursorOn(bool visible, DWORD size){
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void CursorOff(){
    CursorOn(false, 0);
}
void limpia(){
    system("cls");
}

void vacio(){
    gotoxy(0, 0);
}


int main(){
    CursorOff();
    dibujarCuadro(20, 5, 60, 12);
    gotoxy(30, 5);
    cout << "MENU PRINCIPAL" << endl;
    gotoxy(23, 7);
    cout << "1. Ingresar como Usuario" << endl;
    gotoxy(23, 8);
    cout << "2. Ingresar como Administrador" << endl;
    gotoxy(23, 9);
    cout << "3. Registrar Usuario" << endl;
    gotoxy(23, 10);
    cout << "4. Salir" << endl;
    vacio();
    return 0;
}

void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "Ä";
		gotoxy(i,y2); cout << "Ä";
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout << "³";
		gotoxy(x2,i); cout << "³";
    }
    
    gotoxy(x1,y1); cout << "Ú";
    gotoxy(x1,y2); cout << "À";
    gotoxy(x2,y1); cout << "¿";
    gotoxy(x2,y2); cout << "Ù";
}

namespace cine 
{   
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //Imprime mas rapido
    void print(char ch) {
        WriteConsole(consoleHandle, &ch, 1, NULL, NULL);
    }
    void print(std::string str) {
        WriteConsole(consoleHandle, str.c_str(), str.length(), NULL, NULL);
    }
    void print(const char* str) {
        WriteConsole(consoleHandle, str, strlen(str), NULL, NULL);
    }

    //Logotoipo de fisicode
    std::string logo_fisicode = 
    R"( _____   ___   ____    ___    ____    ___    ____    _____ 
|  ___| |_ _| / ___|  |_ _|  / ___|  / _ \  |  _ \  | ____|
| |_     | |  \___ \   | |  | |     | | | | | | | | |  _|  
|  _|    | |   ___) |  | |  | |___  | |_| | | |_| | | |___ 
|_|     |___| |____/  |___|  \____|  \___/  |____/  |_____|)";

    

    //Estructura que permite trabajaar en conjuntos las coordenada (x,y) para no trabajarlas por separadas
    struct coordXY {
        int x;
        int y;
        bool operator == (const coordXY& vec) { return (x == vec.x && y == vec.y); }
        bool operator != (const coordXY& vec) { return !(*this == vec); }
        coordXY operator + (const coordXY& vec) { return { x + vec.x, y + vec.y }; }
        coordXY operator - (const coordXY& vec) { return { x - vec.x, y - vec.y }; }
    };


    //Obtiene la posicion del cursor donde se encuentra
    cine::coordXY getCursorPosition(){
        cine::coordXY coords;
        CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
        GetConsoleScreenBufferInfo(consoleHandle, &BufferInfo);
        coords = { BufferInfo.dwCursorPosition.X, BufferInfo.dwCursorPosition.Y };
        return coords;
    }

    //Mueve el cursor a un al punto x y
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    //gotoxy con parametro de coordenada
    void gotoxy(cine::coordXY pos){
        COORD cursorPosition = { short(pos.x), short(pos.y) };
        SetConsoleCursorPosition(consoleHandle, cursorPosition);
    }

    //Mueve el cursor solo en el eje X
    void gotoX(short x){
        COORD cursorPosition = { x, short(cine::getCursorPosition().y) };
        SetConsoleCursorPosition(consoleHandle, cursorPosition);
    }

    //Mueve el cursor en el eje Y
    void gotoY(short y){
        COORD cursorPosition = { short(cine::getCursorPosition().x), y};
        SetConsoleCursorPosition(consoleHandle, cursorPosition);
    }

    // Devuelve el tamano de la consola (columns/filas) como vector 2d { x, y }
    cine::coordXY getConsoleSize() {
        cine::coordXY coords;
        CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
        GetConsoleScreenBufferInfo(consoleHandle, &BufferInfo);
        coords = { BufferInfo.dwSize.X, BufferInfo.dwSize.Y };

        return coords;
    }
    
    // Imprime un texto multilinea de forma centrada en la consola
    void printRawCenter(std::string& raw) {
        SetConsoleTextAttribute(consoleHandle, 11); 
        std::vector<std::string> subStringsList;
        std::string buffer = "";

        // Divide la cadena en subcadenas en funcion de los saltos de linea
        for (size_t i = 0; i < raw.length(); i++) {
            if (raw[i] != '\n' && i != raw.length() - 1) {
                buffer += raw[i];
            } else {
                if (buffer.empty() && subStringsList.empty()) {
                    // Si es la primera linea vacia, agrega espacios para centrarla
                    size_t consoleWidth = getConsoleSize().x;
                    size_t padding = (consoleWidth - buffer.length()) / 2;
                    buffer = std::string(padding, ' ') + buffer;
                }
                subStringsList.push_back(buffer);
                buffer = "";
            }
        }

        // Determina la longitud de la linea mas larga
        size_t biggestSlice = 0;
        for (std::string substr : subStringsList) {
            if (substr.length() >= biggestSlice) {
                biggestSlice = substr.length();
            }
        }

        // Calcula el desplazamiento horizontal
        int offset = (getConsoleSize().x)/2 - (biggestSlice / 2);
        // Imprime el texto centrado
        for (size_t i = 0; i < subStringsList.size(); i++) {
            cine::gotoX(offset);
            cine::print(subStringsList[i] + "\n");
        }
        SetConsoleTextAttribute(consoleHandle, 15);
    }
    
    //Obtiene la tecla presionado o en su efecto el caracter;
    int getch(){
        //if (_kbhit()) { // Comprobar si se presiono una tecla
        //primero obtenemos el caracter de control
        int control = _getch(); //  
        int input; 
        if (_kbhit()) input = _getch();

        switch (control) {
        case 224://caso cuando es caracter de control
            if (input == 77) return Right;
            if (input == 75) return Left;
            if (input == 72) return Up;
            if (input == 80) return Down;
            break;
        default:
            return control;//sino hay caracter de control solo retorna asci de la tecla
            break;
        }
        //}
        return 0;
    }
}//namespaces cine


//Retorna la fecha y hora actual
string obteneFechaHora() {
    SYSTEMTIME localTime; GetLocalTime(&localTime);
    stringstream ss; ss << localTime.wYear << "/" << localTime.wMonth << "/" << localTime.wDay;
    return ss.str();
}