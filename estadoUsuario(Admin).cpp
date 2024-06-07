#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "menu/funciones.hpp"

using namespace std;

void mostrarPrestamosUsuario(const string& usuario) {
    ifstream archivo("libros(pedidos).txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo libros(pedidos).txt\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea == usuario) {
            getline(archivo, linea);
            cout << "Código de libro: " << linea << "\n"; // Código del libro
            getline(archivo, linea);
            cout << "Título: " << linea << "\n\n"; // Título del libro
        }
    }

    archivo.close();
}

void mostrarMenu(vector<string>& usuarios) {
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i] << "\n";
    }

    int opcion;
    cout << "\nDesee el numero de orden del usuario que desea saber su estado de prestamos de libros: ";
    cin >> opcion;
    cout << endl;

    if (opcion > 0 && opcion <= usuarios.size()) {
        mostrarPrestamosUsuario(usuarios[opcion - 1]);
    } else {
        cout << "Opción inválida.\n";
    }

    cout << "0. Regresar\n1. Salir\n\nElija una opción: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 0) {
        limpiarPantalla();
        mostrarMenu(usuarios);
    } else if (opcion != 1) {
        cout << "Opción inválida.\n";
    }
}

int main() {

    configurarConsolaUtf8();

    vector<string> usuarios;
    ifstream archivo("credUsuario.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo credUsuario.txt\n";
        return 1;
    }

    string linea;
    int contador = 0;
    while (getline(archivo, linea)) {
        // Solo guarda las líneas impares (nombres de usuario)
        if (contador % 2 == 0) {
            usuarios.push_back(linea);
        }
        contador++;
    }

    archivo.close();

    mostrarMenu(usuarios);

    return 0;
}