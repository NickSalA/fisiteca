#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menu/funciones.hpp"
#include "data/sistLibro(Admin).hpp"
using namespace std;

int main() {
    CenterConsoleWindow();
    setColor(White);
    int opc = 0;
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    vector<string> opciones = {"Agregar libro", "Editar libro", "Eliminar libro", "Retroceder"};
    coordXY pos = {40, 15};
    string titulo = R"(

                                            ░█████░█████░█████░█░███░█░
                                            ░█░░░█░█░░░█░█░█░█░█░█░█░█░
                                            ░█████░█░░░█░█░░░█░█░█░█░█░
                                            ░█░░░█░█░░░█░█░░░█░█░█░█░█░
                                            ░█░░░█░█████░█░░░█░█░█░███░

                                    __________________________________________
)";
    configurarConsolaUtf8();
    ocultarCursor();
    

    while (true) {
        limpiarPantalla();
        dibujarTitulo(2, 3, titulo);
        dibujarCuadro(pos.x-8, 2, 50, 25);
        dibujarMenu(pos.x+9, pos.y-1, opciones);
        moverCursor({pos.x + 4, pos.y-1 + opc * 3});

        cout << "=>";

        moverCursor({pos.x + 29, pos.y-1 + opc * 3});

        cout << "<=";

        char key = _getch();
        if (key == 72 && opc > 0) { // Flecha arriba
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) { // Flecha abajo
            opc++;
        } else if (key == '\r') { // Enter
            switch (opc) {
                case 0: 
                    agregarLibro(libros, n);
                    break;
                case 1: 
                    editarLibro(libros, n);
                    break;
                case 2: 
                   eliminarLibro(libros, n);
                    break;
                case 3: 
                    cout<<"Saliendo...";
                    return 0;
            }
        }
    }
}