#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <limits>
#include "sistLibro(Admin).hpp"

using namespace std;

bool usuarioExiste(const string& usuario) {
    ifstream archivo("credUsuario.txt");
    string usuarioGuardado;
    while (archivo >> usuarioGuardado) {
        if (usuarioGuardado == usuario) {
            archivo.close();
            return true;
        }
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    archivo.close();
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

void registrarUsuario() {
    string usuario, contrasena, confirmar_contrasena;
    bool registrado = false;

    while (!registrado) {
        cout << "Introduce tu nombre de usuario: ";
        getline(cin, usuario);

        if (usuario.empty()) {
            cout << "\nEl nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }

        if (usuarioExiste(usuario)) {
            cout << "\nEl usuario ya existe. Introduce un nombre de usuario diferente." << endl << endl;
            continue;
        }

        cout << "Introduce tu contraseña: ";
        getline(cin, contrasena);

        if (contrasena.empty()) {
            cout << "\nLa contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }

        cout << "Confirma tu contraseña: ";
        getline(cin, confirmar_contrasena);

        if (contrasena != confirmar_contrasena) {
            cout << "\nLas contraseñas no coinciden. Inténtalo de nuevo." << endl << endl;
            continue;
        }

        ofstream archivo("credUsuario.txt", ios::app);
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo." << endl;
            return;
        }

        archivo << usuario << endl << contrasena << endl;
        archivo.close();

        registrado = true;
        cout << "\nRegistro exitoso. ¡Te has registrado correctamente!" << endl;
    }
}

void menuUsuario() {
    while (true) {
        cout << "Menu de Opciones" << endl;
        cout << "1. Buscador de libros" << endl;
        cout << "2. Donacion de libros" << endl;
        cout << "3. Prestamo de libros" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";

        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input

        switch (opcion) {
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

void menuAdmin() {
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    int opcion;
    do {
        cout << "\n1. Agregar libro\n2. Eliminar libro\n3. Editar Libro\n4. Salir" << endl;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
        switch (opcion) {
            case 1:
                agregarLibro(libros, n);
                break;
            case 2:
                eliminarLibro(libros, n);
                break;
            case 3:
                editarLibro(libros, n);
                break;
            case 4:
                cout << "Adios!" << endl;
                return;
            default:
                cout << "Opcion invalida" << endl;
                break;
        }
    } while (opcion != 4);
}

void ingresarUsuario() {
    string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;

    do {
        cout << "Ingrese su nombre de usuario: ";
        getline(cin, usuarioIngresado);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseñaIngresada);

        if (verificarCredencialesUsuario(usuarioIngresado, contraseñaIngresada)) {
            credencialesCorrectas = true;
            cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << endl;
            menuUsuario();
        } else {
            cout << "\nError: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl;
        }
    } while (!credencialesCorrectas);
}

void ingresarComoAdmin() {
    string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;

    do {
        cout << "Ingrese su nombre de usuario: ";
        getline(cin, usuarioIngresado);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseñaIngresada);

        if (verificarCredencialesAdmin(usuarioIngresado, contraseñaIngresada)) {
            credencialesCorrectas = true;
            cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente como administrador." << endl;
            menuAdmin();
        } else {
            cout << "\nError: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl << endl;
        }
    } while (!credencialesCorrectas);
}

#endif // USERMANAGEMENT_HPP