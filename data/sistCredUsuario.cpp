#include <iostream>
#include <fstream>
#include <string>
#include <locale> 

using namespace std;

void configurarConsolaUtf8() {
    setlocale(LC_ALL, "es_ES.UTF-8"); 
}

bool verificarCredenciales(const string& usuario, const string& contraseña) {
    ifstream archivo("credUsuario.txt");
    
    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << endl;
        return false;
    }
    
    string usuarioGuardado;
    string contraseñaGuardada;
    
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }
    
    archivo.close();
    return false;
}

int main() {
    configurarConsolaUtf8(); 
    
    string usuarioIngresado;
    string contraseñaIngresada;
    bool credencialesCorrectas = false;

    do {
        cout << "Ingrese su nombre de usuario: ";
        getline(cin, usuarioIngresado);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseñaIngresada);

        if (verificarCredenciales(usuarioIngresado, contraseñaIngresada)) {
            credencialesCorrectas = true;
        } else {
            cout << "\nError: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << endl << endl;
        }
    } while (!credencialesCorrectas);

    cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << endl;

    return 0;
}
