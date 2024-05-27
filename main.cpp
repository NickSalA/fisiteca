#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "data/userManagement.hpp"
#include "menu/funciones.hpp"
using namespace std;

int main() {
    int opc = 0;
    vector<string> opciones = {"Ingresar como Usuario", "Ingresar como Administrador", "Registrar Usuario", "Salir"};
    coordXY pos = {7, 7};

    configurarConsolaUtf8();
    ocultarCursor();

    while (true) {
        system("cls");
        dibujarTitulo(2, 2, "MENU PRINCIPAL");
        dibujarMenu(pos.x, pos.y, opciones);
        moverCursor({pos.x - 2, pos.y + opc});

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