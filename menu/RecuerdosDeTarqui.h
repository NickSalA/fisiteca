#include <iostream>
#include <fstream>
#include <windows.h>
#ifndef FUNCIONESVERIFICAR_H
#define FUNCIONES_VERIFICAR_HPP
using namespace std;

HWND hwnd, hwndLogin, hwndRegistro, hwndAdmin;
HWND hUsuario, hContraseña, hBotonIngresarUsuario, hBotonRegistrarse, hBotonAdmin, hNombre, hContraseñaReg, hConfirmarContraseña, hBotonRegistrar, hBotonIngresarAdmin;

//funciones
bool verificarCredencialesAdmin(const string& usuario, const string& contraseña);
bool verificarCredencialesUsuario(const string& usuario, const string& contraseña);
bool registrarUsuario(const string& usuario, const string& contraseña);
bool usuarioExiste(const string& usuario);

// Prototipos de funciones
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void createLoginWindow(HINSTANCE hInstance);
void createRegistroWindow(HINSTANCE hInstance);
void createAdminWindow(HINSTANCE hInstance);
void menuUsuario();
void menuAdmin();

//métodos
bool verificarCredencialesUsuario(const string& usuario, const string& contraseña) {
    ifstream file("credUsuario.txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credUsuario.txt" << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line == usuario) {
            if (getline(file, line) && line == contraseña) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

bool verificarCredencialesAdmin(const string& usuario, const string& contraseña) {
    ifstream file("credAdmin.txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credAdmin.txt" << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line == usuario) {
            if (getline(file, line) && line == contraseña) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

bool usuarioExiste(const string& usuario) {
    ifstream archivo("credUsuario.txt");
    string linea;
    while (getline(archivo, linea)) {
        if (linea == usuario) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool registrarUsuario(const string& usuario, const string& contraseña) {
     if (usuarioExiste(usuario)) {
        return false;
    }

    ofstream file("credUsuario.txt", ios_base::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credUsuario.txt" << endl;
        return false;
    }

    file << usuario << endl << contraseña << endl;
    file.close();
    return true;
}

#endif // FUNCIONESVERIFICAR_H