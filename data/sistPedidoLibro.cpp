#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;
struct Libro {
    int codigo;
    string nombre;
    string genero;
	string autor;
	int añoPublicacion;
	string sinopsis;
};

void leerLibro(Libro libros[], int& n){
    ifstream Leer("libros.txt", ios::in);
    if(Leer.fail()){
		cout<<"Error en el archivo..."<<endl;
		exit(1);

	for (int i = 0; i < n; i++) {
        Leer >> libros[i].codigo;
        Leer >> libros[i].nombre;
        Leer >> libros[i].genero;
		Leer >> libros[i].autor;
        Leer >> libros[i].añoPublicacion;
        Leer >> libros[i].sinopsis;	
	}
	Leer.close();
	}
}

void agregarLibro(Libro libros[], int& n) {
    ofstream Grabacion("libros.txt", ios::app);
    cout << "Sistema de pedido de libros" << endl;
    cout << "Ingresar los datos del libro" << endl;
	//Lo de abajo es la base de datos, los cout se pueden cambiar de acuerdo al diseño final
    Libro newLibro;
    cout << "Codigo: ";
    cin >> newLibro.codigo;
    fflush(stdin);
    cout << "Nombre: ";
    getline(cin, newLibro.nombre);
    cout << "Genero: ";
    getline(cin, newLibro.genero);
    cout << "Autor: ";
    getline(cin, newLibro.autor);
    cout << "Año de publicacion: ";
    cin >> newLibro.añoPublicacion;
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
        Grabacion << newLibro.añoPublicacion << endl;
        Grabacion << newLibro.sinopsis << endl;
        Grabacion.close();
    }
}

//int main provisional, lo importante es lo de arriba xd
int main() {
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    int opcion;
    do {
        cout << "\n1. Agregar libro\n2. Leer libros\n3. Salir" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarLibro(libros, n);
                break;
            case 2:
                for (int i = 0; i < n; i++) {
                    cout << "\nLibro " << i + 1 << endl;
                    cout << "Codigo: " << libros[i].codigo << endl;
                    cout << "Nombre: " << libros[i].nombre << endl;
                    cout << "Genero: " << libros[i].genero << endl;
                    cout << "Autor: " << libros[i].autor << endl;
                    cout << "Año de publicacion: " << libros[i].añoPublicacion << endl;
                    cout << "Sinopsis: " << libros[i].sinopsis << endl;
                }
                break;
            case 3:
                cout << "Adios!" << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    } while (opcion!= 3);
    return 0;
}
//ayuda Edu D: