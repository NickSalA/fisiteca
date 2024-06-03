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
    vector<string> opciones = {"Ingresar como Usuario", "Ingresar como Administrador", "Registrar Usuario", "Salir"};
    coordXY pos = {40, 15};
    string titulo = R"(
                                                Gestor de bibliotecas 

                                          ████░█░███░█░█████░████░████░█████
                                          █░░░░█░█░░░█░░░█░░░█░░░░█░░░░█░░░█
                                          ███░░█░███░█░░░█░░░████░█░░░░█████
                                          █░░░░█░░░█░█░░░█░░░█░░░░█░░░░█░░░█
                                          █░░░░█░███░█░░░█░░░████░████░█░░░█   
)";
    configurarConsolaUtf8();
    ocultarCursor();
    while (true) {
        limpiarPantalla();
        dibujarTitulo(2, 3, titulo);
        dibujarCuadro(pos.x-8, 2, 50, 25);
        dibujarMenu(pos.x+3, pos.y, opciones);
        moverCursor({pos.x-2, pos.y + opc * 3});

        cout << "=>";

        moverCursor({pos.x + 36, pos.y + opc * 3});

        cout << "<=";

        char key = _getch();
        if (key == 72 && opc > 0) { // Flecha arriba
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) { // Flecha abajo
            opc++;
        } else if (key == '\r') { // Enter
            switch (opc) {
                case 0: 
                    ingresarUsuario();
                    break;
                case 1: 
                    ingresarComoAdmin();
                    break;
                case 2: 
                    registrarUsuario();
                    break;
                case 3: 
                    cout << "Saliendo... uwu";
                    return 0;
            }
        }
    }
}