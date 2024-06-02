#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "data/userManagement.hpp"
#include "menu/funciones.hpp"
using namespace std;

int main() {
    CenterConsoleWindow();
    setColor(White);
    int opc = 0;
    vector<string> opciones = {"Buscador de libros", "Donación de libros", "Prestamo de libros", "Salir"};
    coordXY pos = {40, 15};
    string titulo = R"(

                                         ░█░░█░████░█░░█░████░████░█░████░
                                         ░█░░█░█░░░░█░░█░█░░█░█░░█░█░█░░█░
                                         ░█░░█░████░█░░█░████░████░█░█░░█░
                                         ░█░░█░░░░█░█░░█░█░░█░███░░█░█░░█░
                                         ░████░████░████░█░░█░█░██░█░████░

                                    __________________________________________
)";
    configurarConsolaUtf8();
    ocultarCursor();
    

    while (true) {
        limpiarPantalla();
        dibujarTitulo(2, 3, titulo);
        dibujarCuadro(pos.x-8, 2, 50, 25);
        dibujarMenu(pos.x+6, pos.y-1, opciones);
        moverCursor({pos.x + 1, pos.y-1 + opc * 3});

        cout << "=>";

        moverCursor({pos.x + 31, pos.y-1 + opc * 3});

        cout << "<=";

        char key = _getch();
        if (key == 72 && opc > 0) { // Flecha arriba
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) { // Flecha abajo
            opc++;
        } else if (key == '\r') { // Enter
            switch (opc) {
                case 0: 
                   
                    break;
                case 1: 
                    
                    break;
                case 2: 
                   
                    break;
                case 3: 
                    
                    return 0;
            }
        }
    }
}