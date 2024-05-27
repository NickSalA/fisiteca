#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "data/rlutil.h"
#include "data/userManagement.hpp"
#include "menu/funciones.hpp"



using namespace std;

int main() {
    int y = 0;
    int opc = 0; 
    rlutil::hidecursor();
    configurarConsolaUtf8();
    do {
        system("cls");
        rlutil::locate(30, 5);
        cout << "MENU PRINCIPAL" << endl;
        rlutil::locate(23, 7);
        cout << "1. Ingresar como Usuario" << endl;
        rlutil::locate(23, 8);
        cout << "2. Ingresar como Administrador" << endl;
        rlutil::locate(23, 9);
        cout << "3. Registrar Usuario" << endl;
        rlutil::locate(23, 10);
        cout << "4. Salir" << endl;
        
        rlutil::locate(20, 7 + y);
        cout << (char)175;
        
        int key = rlutil::getkey();
        
        switch (key) {
            case 14: // up
                rlutil::locate(20, 7 + y);
                cout << " " << endl;
                y--;
                if (y < 0) {
                    y = 0;
                }
                break;
            case 15: // down
                rlutil::locate(20, 7 + y);
                cout << " " << endl;
                y++;
                if (y > 3) {
                    y = 3;
                }
                break;
            case 1: // enter
                opc = y + 1;
                break;
            default:
                break;
        }
    } while (opc == 0);
    
    switch (opc) {
        case 1: 
            menuUsuario();
            break;
        case 2: 
            menuAdmin();
            break;
        case 3: 
            registrarUsuario();
            break;
        case 4: 
            cout<< "Saliendo...";
            return 0;
            break;
    }
}

