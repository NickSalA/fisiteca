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
        Grabacion.close();
    }
}
void eliminarLibro(Libro libros[], int& n) {
    int numLibro;
    
    //Mostrar lista de libros
    for (int i = 0; i < n; i++) {
        cout << "\nLibro " << i + 1 << ": " << libros[i].nombre << endl;
    }

    cout << "Seleccione el número del libro que desea eliminar: ";
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    if (numLibro >= 1 && numLibro <= n) {
        int indiceLibro = numLibro - 1;
        // Mostrar la información del libro seleccionado
        cout << "\nLibro: " << libros[indiceLibro].nombre << endl;
        cout << "Genero: " << libros[indiceLibro].genero << endl;
        cout << "Autor: " << libros[indiceLibro].autor << endl;
        cout << "Año de publicacion: " << libros[indiceLibro].anoPublicacion << endl;
        
        char confirmacion;
        cout << "¿Está seguro de que desea eliminar este libro? (S/N): ";
        cin >> confirmacion;
        confirmacion = toupper(confirmacion);
        
        // Procesar la respuesta del usuario
        if (confirmacion == 'S') {
            for (int i = indiceLibro; i < n - 1; ++i) {
                libros[i] = libros[i + 1];
            }
            --n;
            cout << "Libro eliminado exitosamente." << endl;

            ofstream Grabacion("libros.txt");
            for (int i = 0; i < n; ++i) {
                Grabacion << libros[i].codigo << endl;
                Grabacion << libros[i].nombre << endl;
                Grabacion << libros[i].genero << endl;
                Grabacion << libros[i].autor << endl;
                Grabacion << libros[i].anoPublicacion << endl;
                Grabacion << libros[i].sinopsis << endl;
            }
            Grabacion.close();
        } else {
            cout << "Operación cancelada. El libro no ha sido eliminado." << endl;
        }
    } else {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}
void editarLibro(){
    
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
                agregarLibro(libros, n);
                break;
            case 2:
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
