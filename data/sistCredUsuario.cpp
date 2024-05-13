#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool verificarCredenciales(const string& usuario, const string& contrasena) {
    // Abrir el archivo para lectura
    ifstream archivo("credUsuario.txt");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << endl;
        return false;
    }
    
    string usuarioGuardado;
    string contrasenaGuardada;
    
    // Leer el archivo línea por línea y buscar las credenciales
    while (archivo >> usuarioGuardado >> contrasenaGuardada) {
        if (usuarioGuardado == usuario && contrasenaGuardada == contrasena) {
            archivo.close();
            return true;
        }
    }
    
    archivo.close();
    return false;
}

int main() {
    string usuarioIngresado;
    string contrasenaIngresada;

    // Solicitar al usuario que ingrese su nombre de usuario
    cout << "Ingrese su nombre de usuario: ";
    cin >> usuarioIngresado;

    // Solicitar al usuario que ingrese su contraseña
    cout << "Ingrese su contrasena: ";
    cin >> contrasenaIngresada;

    // Verificar las credenciales con el archivo de notas
    if (verificarCredenciales(usuarioIngresado, contrasenaIngresada)) {
        cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << endl;
    } else {
        cout << "\nError: Nombre de usuario o contrasena incorrectos." << endl;
    }

    return 0;
}
