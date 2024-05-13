#include <iostream>
#include <fstream>
#include <string>
#include <locale> // Necesario para admitir caracteres especiales

using namespace std;

int main() {
    // Configurar la localización para admitir caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");

    string usuario, contrasena, confirmar_contrasena;
    
    // Pedir al usuario y contraseña
    cout << "Introduce tu nombre de usuario: ";
    getline(cin, usuario);
    
    cout << "Introduce tu contraseña: ";
    getline(cin, contrasena);
    
    cout << "Confirma tu contraseña: ";
    getline(cin, confirmar_contrasena);
    
    // Verificar si las contraseñas coinciden
    if (contrasena != confirmar_contrasena) {
        cout << "Las contraseñas no coinciden. Inténtalo de nuevo." << endl;
        return 1;
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
            
    return 0;
}
