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
    setColor(Intensity);
    int opc = 0;
    vector<string> opciones = {"Ingresar como Usuario", "Ingresar como Administrador", "Registrar Usuario", "Salir"};
    coordXY pos = {13, 13};
    string titulo = R"(
                ████░█░███░█░█████░████░████░█████
                █░░░░█░█░░░█░░░█░░░█░░░░█░░░░█░░░█
                █░░░░█░█░░░█░░░█░░░█░░░░█░░░░█░░░█
                ███░░█░███░█░░░█░░░████░█░░░░█████
                █░░░░█░░░█░█░░░█░░░█░░░░█░░░░█░░░█
                █░░░░█░░░█░█░░░█░░░█░░░░█░░░░█░░░█
                █░░░░█░███░█░░░█░░░████░████░█░░░█
)";
    configurarConsolaUtf8();
    ocultarCursor();

    while (true) {
        limpiarPantalla();
        dibujarTitulo(2, 2, titulo);
        dibujarCuadro(pos.x-5, 1, 50,25 );
        dibujarMenu(pos.x+3, pos.y, opciones);
        moverCursor({pos.x + 1, pos.y + opc});


        cout << "=>";

        char key = _getch();
        if (key == 72 && opc > 0) { // Flecha arriba
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) { // Flecha abajo
            opc++;
        } else if (key == '\r') { // Enter
            switch (opc) {
                case 0: 
                    menuUsuario();
                    break;
                case 1: 
                    menuAdmin();
                    break;
                case 2: 
                    registrarUsuario();
                    break;
                case 3: 
                    cout << "Saliendo...";
                    return 0;
            }
        }
    }
}