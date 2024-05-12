#include <iostream>
#include <conio.h>

using namespace std;

void mostrarMenu(int opcionSeleccionada) {
    system("cls"); // Limpiar la pantalla

    // Mostrar el menú con las opciones
    cout << "Menú:" << endl;
    cout << "  [1] Opcion 1" << endl;
    cout << "  [2] Opcion 2" << endl;
    cout << "  [3] Opcion 3" << endl;
    cout << "  [4] Salir" << endl;

    // Resaltar la opción seleccionada
    switch (opcionSeleccionada) {
        case 1:
            cout << "\n-> Opcion 1" << endl;
            break;
        case 2:
            cout << "\n-> Opcion 2" << endl;
            break;
        case 3:
            cout << "\n-> Opcion 3" << endl;
            break;
        case 4:
            cout << "\n-> Salir" << endl;
            break;
        default:
            break;
    }
}

int main() {
    int opcion = 1; // Opción inicial seleccionada
    int tecla;

    do {
        mostrarMenu(opcion);

        // Obtener entrada del teclado
        tecla = _getch();

        // Actualizar la opción seleccionada según la tecla presionada
        switch (tecla) {
            case 72: // Flecha arriba
                opcion = (opcion > 1) ? opcion - 1 : 4; // Ciclar hacia abajo si se alcanza la primera opción
                break;
            case 80: // Flecha abajo
                opcion = (opcion < 4) ? opcion + 1 : 1; // Ciclar hacia arriba si se alcanza la última opción
                break;
            default:
                break;
        }
    } while (tecla != 13); // Continuar hasta que se presione Enter (tecla 13)

    return 0;
}