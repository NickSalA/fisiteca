#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <limits>
#include "sistLibro(Admin).hpp"
#include "sistLibro(Usuario).hpp"

using namespace std;

bool usuarioExiste(const string& usuario) {
    ifstream archivo("credUsuario.txt");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea == usuario) {
            return true;
        }
    }
    return false;
}

bool verificarCredencialesUsuario(const string& usuario, const string& contraseña) {
    ifstream archivo("credUsuario.txt");
    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << endl;
        return false;
    }

    string usuarioGuardado, contraseñaGuardada;
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool verificarCredencialesAdmin(const string& usuario, const string& contraseña) {
    ifstream archivo("credAdmin.txt");
    
    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo 'credAdmin.txt'." << endl;
        return false;
    }
    
    string usuarioGuardado;
    string contraseñaGuardada;
    
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }
    
    archivo.close();
    return false;
}

void registrarUsuario() {
    limpiarPantalla();
    int anchoConsola, altoConsola;
    obtenerDimensionConsola(anchoConsola, altoConsola);
    int anchoInterfaz = 70;
    int altoInterfaz = 15;
    int x = (anchoConsola - anchoInterfaz) / 2;
    int y = (altoConsola - altoInterfaz) / 2;

    string usuario, contrasena, confirmar_contrasena;
    bool registrado = false;
    while (!registrado) {
        dibujarInterfazRegistrar(x, y, anchoInterfaz, altoInterfaz);
        gotoxy(x + 36, y + 4); cout << "                    ";
        gotoxy(x + 36, y + 4); getline(cin, usuario);
        if (usuario.empty()) {
            gotoxy(x + 2, y + 14); cout << "El nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        if (usuarioExiste(usuario)) {
            gotoxy(x + 2, y + 14); cout << "El usuario ya existe. Introduce un nombre de usuario diferente." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 7); cout << "                    ";
        gotoxy(x + 36, y + 7); getline(cin, contrasena);
        if (contrasena.empty()) {
            gotoxy(x + 2, y + 14); cout << "La contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 10); cout << "                    ";
        gotoxy(x + 36, y + 10); getline(cin, confirmar_contrasena);
        if (contrasena != confirmar_contrasena) {
            gotoxy(x + 2, y + 14); cout << "Las contraseñas no coinciden. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        ofstream archivo("credUsuario.txt", ios::app);

        if (!archivo.is_open()) {
            gotoxy(x + 2, y + 14); cout << "Error al abrir el archivo." << endl;
        }
        archivo << usuario << endl << contrasena << endl;
        registrado = true;
        gotoxy(x + 2, y + 14); cout << "Registro exitoso. ¡Te has registrado correctamente!" << endl;
    }
}

void menuUsuario(string& usuarioIngresado) {
    CenterConsoleWindow();
    setColor(White);
    int opc = 0;
    int lastOpc = -1;
    vector<string> opciones = {"Buscador de libros", "Donación de libros", "Prestamo de libros", "Menu principal"};
    coordXY pos = {40, 15};
    string titulo = R"(

                                         ░█░░█░████░█░░█░████░████░█░████░
                                         ░█░░█░█░░░░█░░█░█░░█░█░░█░█░█░░█░
                                         ░█░░█░████░█░░█░████░████░█░█░░█░
                                         ░█░░█░░░░█░█░░█░█░░█░███░░█░█░░█░
                                         ░████░████░████░█░░█░█░██░█░████░

                                    __________________________________________
)";
    configurarConsolaUtf8();
    ocultarCursor();
    
    limpiarPantalla();
    dibujarTitulo(2, 3, titulo);
    dibujarCuadro(pos.x-8, 2, 50, 25);
    dibujarMenu(pos.x+6, pos.y-1, opciones);

    bool iterador = true;
    while (iterador) {
        if (lastOpc != opc) {
            if (lastOpc != -1) {
                moverCursor({pos.x + 1, pos.y-1 + lastOpc * 3});
                cout << "  ";
                moverCursor({pos.x + 31, pos.y-1 + lastOpc * 3});
                cout << "  ";
            }

            moverCursor({pos.x + 1, pos.y-1 + opc * 3});
            cout << "=>";
            moverCursor({pos.x + 31, pos.y-1 + opc * 3});
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
                    BuscarLibro();
                    break;
                case 1: 
                    donarLibro();
                    break;
                case 2: 
                    prestarLibro(usuarioIngresado);
                    break;
                case 3: 
                    iterador = false;
                    break;
            }
            limpiarPantalla();
            dibujarTitulo(2, 3, titulo);
            dibujarCuadro(pos.x-8, 2, 50, 25);
            dibujarMenu(pos.x+6, pos.y-1, opciones);
            lastOpc = -1;
        }
    }
}

void menuAdmin() {
    CenterConsoleWindow();
    setColor(White);
    int opc = 0;
    int lastOpc = -1;
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    vector<string> opciones = {"Agregar libro", "Editar libro", "Eliminar libro", "Menu principal"};
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
    
    limpiarPantalla();
    dibujarTitulo(2, 3, titulo);
    dibujarCuadro(pos.x-8, 2, 50, 25);
    dibujarMenu(pos.x+9, pos.y-1, opciones);

    bool iterador = true;
    while (iterador) {
        if (lastOpc != opc) {
            if (lastOpc != -1) {
                moverCursor({pos.x + 4, pos.y-1 + lastOpc * 3});
                cout << "  ";
                moverCursor({pos.x + 29, pos.y-1 + lastOpc * 3});
                cout << "  ";
            }

            moverCursor({pos.x + 4, pos.y-1 + opc * 3});
            cout << "=>";
            moverCursor({pos.x + 29, pos.y-1 + opc * 3});
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
                    agregarLibro(libros, n);
                    break;
                case 1: 
                    editarLibro(libros, n);
                    break;
                case 2: 
                    eliminarLibro(libros, n);
                    break;
                case 3: 
                    iterador = false;
                    break;
            }
            limpiarPantalla();
            dibujarTitulo(2, 3, titulo);
            dibujarCuadro(pos.x-8, 2, 50, 25);
            dibujarMenu(pos.x+9, pos.y-1, opciones);
            lastOpc = -1;
        }
    }
}

void ingresarUsuario() {
    limpiarPantalla();
    int anchoConsola, altoConsola;
    obtenerDimensionConsola(anchoConsola, altoConsola);
    int anchoInterfaz = 70;
    int altoInterfaz = 15;
    int x = (anchoConsola - anchoInterfaz) / 2;
    int y = (altoConsola - altoInterfaz) / 2;

    string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;
    do {
        dibujarInterfazUser(x, y, anchoInterfaz, altoInterfaz);
        gotoxy(x + 36, y + 4); cout << "                    ";
        gotoxy(x + 36, y + 4); getline(cin, usuarioIngresado);
        if (usuarioIngresado.empty()) {
            gotoxy(x + 2, y + 14); cout << "El nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 7); cout << "                    ";
        gotoxy(x + 36, y + 7); getline(cin, contraseñaIngresada);
        if (contraseñaIngresada.empty()) {
            gotoxy(x + 2, y + 14); cout << "La contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        if (!verificarCredencialesUsuario(usuarioIngresado, contraseñaIngresada)) {
            gotoxy(x + 2, y + 14); cout << "Error: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl << endl;
            continue;
        }
        credencialesCorrectas = true;
        gotoxy(x + 7, y + 10); cout << "¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << endl << endl;

    } while (!credencialesCorrectas);
    menuUsuario(usuarioIngresado);
}

void ingresarComoAdmin() {
    limpiarPantalla();
    int anchoConsola, altoConsola;
    obtenerDimensionConsola(anchoConsola, altoConsola);
    int anchoInterfaz = 70;
    int altoInterfaz = 15;
    int x = (anchoConsola - anchoInterfaz) / 2;
    int y = (altoConsola - altoInterfaz) / 2;

    string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;
    do {
        dibujarInterfazUser(x, y, anchoInterfaz, altoInterfaz);
        gotoxy(x + 36, y + 4); cout << "                    ";
        gotoxy(x + 36, y + 4); getline(cin, usuarioIngresado);
        if (usuarioIngresado.empty()) {
            gotoxy(x + 2, y + 14); cout << "El nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        gotoxy(x + 36, y + 7); cout << "                    ";
        gotoxy(x + 36, y + 7); getline(cin, contraseñaIngresada);
        if (contraseñaIngresada.empty()) {
            gotoxy(x + 2, y + 14); cout << "La contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        if (!verificarCredencialesAdmin(usuarioIngresado, contraseñaIngresada)) {
            gotoxy(x + 2, y + 14); cout << "Error: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl << endl;
            continue;
        }
        credencialesCorrectas = true;
        gotoxy(x + 2, y + 10); cout << "¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente como administrador." << endl << endl;

    } while (!credencialesCorrectas);
    menuAdmin();
}

#endif // USERMANAGEMENT_HPP