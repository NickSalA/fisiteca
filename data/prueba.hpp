#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <limits> 
#ifndef FUNCIONESVERIFICAR_H
#define FUNCIONES_VERIFICAR_HPP

using namespace std;

void configurarConsolaUtf8() {
    setlocale(LC_ALL, "es_ES.UTF-8");
}

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

// Verificar credenciales de usuario
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

// Verificar credenciales de administrador
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

// Registrar un nuevo usuario
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

#endif // FUNCIONESVERIFICAR_H