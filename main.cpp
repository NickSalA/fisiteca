#include "data/userManagement.hpp"
#include "menu/funciones.hpp"

using namespace std;

int main() {
    CenterConsoleWindow();
    setColor(White);
    int opc = 0;
    int lastOpc = -1;
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
    
    limpiarPantalla();
    mostrarIniciando(52,12);
    limpiarPantalla();
    ejecutarGradiente();
    limpiarPantalla();
    dibujarTitulo(2, 3, titulo);
    dibujarCuadro(pos.x-8, 2, 50, 25);
    dibujarMenu(pos.x+3, pos.y, opciones);

    while (true) {
        if (lastOpc != opc) {
            if (lastOpc != -1) {
                moverCursor({pos.x-2, pos.y + lastOpc * 3});
                cout << "  ";
                moverCursor({pos.x + 36, pos.y + lastOpc * 3});
                cout << "  ";
            }

            moverCursor({pos.x-2, pos.y + opc * 3});
            cout << "=>";
            moverCursor({pos.x + 36, pos.y + opc * 3});
            cout << "<=";
            
            lastOpc = opc;
        }

        char key = _getch();
        if (key == 72 && opc > 0) {
            opc--;
        } else if (key == 80 && opc < static_cast<int>(opciones.size() - 1)) {
            opc++;
        } else if (key == '\r') {
            limpiarPantalla();
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
            limpiarPantalla();
            dibujarTitulo(2, 3, titulo);
            dibujarCuadro(pos.x-8, 2, 50, 25);
            dibujarMenu(pos.x+3, pos.y, opciones);
            lastOpc = -1;
        }
    }
}
