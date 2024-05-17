#include <iostream>
#include <fstream>
#include <windows.h>
#ifndef FUNCIONESVERIFICAR_H
#define FUNCIONES_VERIFICAR_HPP
using namespace std;

//funciones
bool verificarCredencialesAdmin(const string& usuario, const string& contraseña);
bool verificarCredencialesUsuario(const string& usuario, const string& contraseña);
void registrarUsuario(const string& usuario, const string& contraseña);
bool usuarioExiste(const string& usuario);

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

void registrarUsuario(const string& usuario, const string& contraseña) {
    ofstream file("credUsuario.txt", ios_base::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credUsuario.txt" << endl;
        return;
    }
    if (usuarioExiste(usuario)) {
            MessageBox(hwnd, "El usuario ya existe. Introduce un nombre de usuario diferente", "Error", MB_OK | MB_ICONERROR);            return;
        }
    file << usuario << endl << contraseña << endl;
    file.close();
}

#endif // FUNCIONESVERIFICAR_H