#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "data/userManagement.hpp"

using namespace std;

int main() {
    int opc;
    configurarConsolaUtf8();
        system("cls");
        cout << "MENU PRINCIPAL" << endl;
        cout << "1. Ingresar como Usuario" << endl;
        cout << "2. Ingresar como Administrador" << endl;
        cout << "3. Registrar Usuario" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opc;
        
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
            break;
        default:    
            cout << "Opcion invalida" << endl;
            break; 
}
}

