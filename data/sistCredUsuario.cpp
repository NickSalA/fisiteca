#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool verificarCredenciales(const string& usuario, const string& contrasena) {
    ifstream archivo("credUsuario.txt");
    
    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << endl;
        return false;
    }
    
    string usuarioGuardado;
    string contrasenaGuardada;
    
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

    cout << "Ingrese su nombre de usuario: ";
    cin >> usuarioIngresado;

    cout << "Ingrese su contrasena: ";
    cin >> contrasenaIngresada;

    if (verificarCredenciales(usuarioIngresado, contrasenaIngresada)) {
        cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << endl;
    } else {
        cout << "\nError: Nombre de usuario o contrasena incorrectos." << endl;
    }

    return 0;
}
