#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string usuario, contrasena;
    
    // Pedir al usuario y contraseña
    cout << "Introduce tu nombre de usuario: ";
    cin >> usuario;
    cout << "Introduce tu contraseña: ";
    cin >> contrasena;
    
    // Abrir el archivo para escritura (se creará si no existe)
    ofstream archivo("credUsuario.txt", ios::app);
    
    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo.";
        return 1;
    }
    
    // Guardar el usuario y contraseña en el archivo
    archivo <<endl<< usuario << endl << contrasena;
    
    // Cerrar el archivo
    archivo.close();
        
    return 0;
}
