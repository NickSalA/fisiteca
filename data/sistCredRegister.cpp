#include <iostream>
#include <fstream>
#include <string>
#include <locale> // Necesario para admitir caracteres especiales

using namespace std;

// Función para verificar si el usuario ya existe
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
    // Configurar la localización para admitir caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");

    string usuario, contrasena, confirmar_contrasena;
    
    bool registrado = false;
    while (!registrado) {
        // Pedir al usuario y contraseña
        cout << "Introduce tu nombre de usuario: ";
        getline(cin, usuario);
        
        // Verificar si el usuario está vacío
        if (usuario.empty()) {
            cout << "\nEl nombre de usuario no puede estar vacío. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        
        // Verificar si el usuario ya existe
        if (usuarioExiste(usuario)) {
            cout << "\nEl usuario ya existe. Introduce un nombre de usuario diferente." << endl << endl;
            continue;
        }
        
        cout << "Introduce tu contraseña: ";
        getline(cin, contrasena);
        
        // Verificar si la contraseña está vacía
        if (contrasena.empty()) {
            cout << "\nLa contraseña no puede estar vacía. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        
        cout << "Confirma tu contraseña: ";
        getline(cin, confirmar_contrasena);
        
        // Verificar si las contraseñas coinciden
        if (contrasena != confirmar_contrasena) {
            cout << "\nLas contraseñas no coinciden. Inténtalo de nuevo." << endl << endl;
            continue;
        }
        
        // Abrir el archivo para escritura (se creará si no existe)
        ofstream archivo("credUsuario.txt", ios::app);
        
        // Verificar si el archivo se abrió correctamente
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo." << endl;
            return 1;
        }
        
        // Guardar el usuario y contraseña en el archivo
        archivo << usuario << endl << contrasena << endl;
        
        // Cerrar el archivo
        archivo.close();
        
        registrado = true;
        cout << "Registro exitoso. ¡Te has registrado correctamente!" << endl;
    }
            
    return 0;
}
