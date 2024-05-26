// main.cpp
#include <iostream>
#include "data/userManagement.hpp"

using namespace std;

int main() {
    configurarConsolaUtf8();

    int opcion;
    do {
        cout << "\nMenu Principal:" << endl;
        cout << "1. Ingresar como Usuario" << endl;
        cout << "2. Ingresar como Administrador" << endl;
        cout << "3. Registrar Usuario" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline after the option

        switch (opcion) {
            case 1:
                ingresarUsuario();
                break;
            case 2:
                ingresarComoAdmin();
                break;
            case 3:
                registrarUsuario();
                break;
            case 4:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}