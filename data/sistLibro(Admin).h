#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <limits>

using namespace std;
string xcodigo,xano;
struct Libro {
    int codigo;
    string nombre;
    string genero;
	string autor;
	int anoPublicacion;
	string sinopsis;
};

void leerLibro(Libro libros[], int& n){
    ifstream Leer("libros.txt", ios::in);
    if(Leer.fail()){
		cout<<"Error en el archivo..."<<endl;
		exit(1);
    }
    int i=0;
    while(!Leer.eof()){
        //lectura de datos
        getline(Leer,xcodigo);
        getline(Leer,libros[i].nombre);
        getline(Leer,libros[i].genero);
        getline(Leer,libros[i].autor);
        getline(Leer,xano);
        getline(Leer,libros[i].sinopsis);
        //almacenar datos
        istringstream(xcodigo) >> libros[i].codigo;
        istringstream(xano)>>libros[i].anoPublicacion;
        n++;
        i++;
    }
	Leer.close();
	
}

void agregarLibro(Libro libros[], int& n) {
    ofstream Grabacion("libros.txt", ios::app);
    cout << "Sistema de pedido de libros" << endl;
    cout << "Ingresar los datos del libro" << endl;
    Libro newLibro;
    cout << "Codigo: ";
    cin >> newLibro.codigo;
    fflush(stdin);
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, newLibro.nombre);
    cout << "Genero: ";
    getline(cin, newLibro.genero);
    cout << "Autor: ";
    getline(cin, newLibro.autor);
    cout << "Año de publicacion: ";
    cin >> newLibro.anoPublicacion;
    fflush(stdin);
    cin.ignore();

    cout << "Sinopsis: ";
    getline(cin, newLibro.sinopsis);
    libros[n] = newLibro;
    n++;
    if (Grabacion.fail()) {
        cout << "Error en el archivo..." << endl;
        Sleep(2000);
    } else {
        Grabacion << newLibro.codigo << endl;
        Grabacion << newLibro.nombre << endl;
        Grabacion << newLibro.genero << endl;
        Grabacion << newLibro.autor << endl;
        Grabacion << newLibro.anoPublicacion << endl;
        Grabacion << newLibro.sinopsis << endl;
        // Agregar un salto de línea al final del registro del libro
        Grabacion << endl;
        Grabacion.close();
    }
}
void eliminarLibro(Libro libros[], int& n) {
    int codigo;
    cout << "Ingrese el código del libro que desea eliminar: ";
    cin >> codigo;

    bool encontrado = false;
    for (int i = 0; i < n; ++i) {
        if (libros[i].codigo == codigo) {
            encontrado = true;
            // Desplazar los elementos hacia abajo para sobrescribir el libro a eliminar
            for (int j = i; j < n - 1; ++j) {
                libros[j] = libros[j + 1];
            }
            // Reducir el contador de libros
            --n;
            break;
        }
    }

    if (encontrado) {
        ofstream Grabacion("libros.txt");
        for (int i = 0; i < n; ++i) {
            Grabacion << libros[i].codigo << endl;
            Grabacion << libros[i].nombre << endl;
            Grabacion << libros[i].genero << endl;
            Grabacion << libros[i].autor << endl;
            Grabacion << libros[i].anoPublicacion << endl;
            Grabacion << libros[i].sinopsis << endl;
            // Agregar un salto de línea al final del registro del libro
            Grabacion << endl;
        }
        Grabacion.close();
        cout << "Libro eliminado exitosamente." << endl;
    } else {
        cout << "No se encontró ningún libro con el código " << codigo << "." << endl;
    }
}
//int main provisional, lo importante es lo de arriba xd
int main() {
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    int opcion;
    do {
        cout << "\n1. Agregar libro\n2. Eliminar libros\n3. Salir" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                leerLibro(libros, n);
                agregarLibro(libros, n);
                break;
            case 2:
                leerLibro(libros, n);
                eliminarLibro(libros, n);
                break;
            case 3:
                cout << "Adios!" << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
        // Limpiar el búfer de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
        system("cls");
    } while (opcion != 3);
    return 0;
}
