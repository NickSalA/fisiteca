#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

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

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

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
            return 1;
        }
        
        archivo << usuario << endl << contrasena << endl;
        
        archivo.close();
        
        registrado = true;
        cout << "\nRegistro exitoso. ¡Te has registrado correctamente!" << endl;
    }
            
    return 0;
}
//prueba