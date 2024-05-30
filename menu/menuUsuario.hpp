#ifndef MENUUSUARIO_HPP
#define MENUSUARIO_HPP
#include <iostream>
#include "funciones.hpp"

using namespace std;

void menuUsuario() {
    while (true) {
        <vector> opciones ={'Buscador de libros, Donacion de libros, Prestamo de Libros, Salir'};
        limpiarPantalla();
        dibujarTitulo(2, 2, titulo);
        dibujarCuadro(pos.x-5, 1, 50,25 );
        dibujarMenu(pos.x+3, pos.y, opciones);
        moverCursor({pos.x + 1, pos.y + opc});

        cout << "Menu de Opciones" << endl;
        cout << "1. Buscador de libros" << endl;
        cout << "2. Donacion de libros" << endl;
        cout << "3. Prestamo de libros" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";

        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
        cout << "=>";

        char key = _getch();
        if (key == 72 && opc > 0) { // Flecha arriba
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) { // Flecha abajo
            opc++;
        } else if (key == '\r') {
            switch (opc) {
            case 1:
                cout << "Has seleccionado la Opción 1" << endl;
                break;
            case 2:
                cout << "Has seleccionado la Opción 2" << endl;
                break;
            case 3:
                cout << "Has seleccionado la Opción 3" << endl;
                break;
            case 4:
                cout << "Saliendo..." << endl;
                return;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                break;
            }
        }
    }
}
#endif //MENUUSUARIO_HPP