#include <iostream>
#include <fstream>
#include <string>
#include <locale> 

using namespace std;

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    string usuario, contrasena, confirmar_contrasena;
    
    cout << "Introduce tu nombre de usuario: ";
    getline(cin, usuario);
    
    cout << "Introduce tu contraseña: ";
    getline(cin, contrasena);
    
    cout << "Confirma tu contraseña: ";
    getline(cin, confirmar_contrasena);
    
    if (contrasena != confirmar_contrasena) {
        cout << "Las contraseñas no coinciden. Inténtalo de nuevo." << endl;
        return 1;
    }
    
    ofstream archivo("credUsuario.txt", ios::app);
    
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    
    archivo << usuario << endl << contrasena << endl;
    
    archivo.close();
            
    return 0;
}
