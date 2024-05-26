#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <limits>

using namespace std;
string xcodigo,xano,xcantidad;
struct Libro {
    int codigo;
    string nombre;
    string genero;
	string autor;
	int anoPublicacion;
	string sinopsis;
    int cantidad; // Añadimos la cantidad aquí
};

void leerLibro(Libro libros[], int& n){
    ifstream Leer("libros.txt", ios::in);
    if(Leer.fail()){
		cout<<"Error en el archivo..."<<endl;
		exit(1);
    }
    int i=0;
    while(!Leer.eof()){
        getline(Leer,xcodigo);
        getline(Leer,libros[i].nombre);
        getline(Leer,libros[i].genero);
        getline(Leer,libros[i].autor);
        getline(Leer,xano);
        getline(Leer,libros[i].sinopsis);
        getline(Leer,xcantidad); // Leemos la cantidad aquí
        istringstream(xcodigo) >> libros[i].codigo;
        istringstream(xano)>>libros[i].anoPublicacion;
        istringstream(xcantidad)>>libros[i].cantidad; // Convertimos la cantidad a int
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
    cout << "Cantidad: "; // Pedimos la cantidad aquí
    cin >> newLibro.cantidad;
    fflush(stdin);
    cin.ignore();

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
        Grabacion << newLibro.cantidad << endl; // Guardamos la cantidad aquí
        Grabacion.close();
    }
}
void eliminarLibro(Libro libros[], int& n) {
    int numLibro;
    
    for (int i = 0; i < n; i++) {
        cout << "\nLibro " << i + 1 << ": " << libros[i].nombre << " - Cantidad: " << libros[i].cantidad << endl;
    }

    cout << "Seleccione el número del libro que desea eliminar: ";
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    if (numLibro >= 1 && numLibro <= n) {
        int indiceLibro = numLibro - 1;
        cout << "\nLibro: " << libros[indiceLibro].nombre << " - Cantidad: " << libros[indiceLibro].cantidad << endl;
        cout << "Genero: " << libros[indiceLibro].genero << endl;
        cout << "Autor: " << libros[indiceLibro].autor << endl;
        cout << "Año de publicacion: " << libros[indiceLibro].anoPublicacion << endl;
        
        char confirmacion;
        cout << "¿Está seguro de que desea eliminar este libro? (S/N): ";
        cin >> confirmacion;
        confirmacion = toupper(confirmacion);
        
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
                Grabacion << libros[i].cantidad << endl; // Guardamos la cantidad aquí
            }
            Grabacion.close();
        } else {
            cout << "Operación cancelada. El libro no ha sido eliminado." << endl;
        }
    } else {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}

void editarLibro(Libro libros[], int n) {
    int numLibro;
    
    for (int i = 0; i < n; i++) {
        cout << "\nLibro " << i + 1 << ": " << libros[i].nombre << " - Cantidad: " << libros[i].cantidad << endl;
    }
    
    cout << "Seleccione el número del libro que desea editar: ";
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    if (numLibro >= 1 && numLibro <= n) {
        int indiceLibro = numLibro - 1;
        
        cout << "\nEditar libro: " << libros[indiceLibro].nombre << endl;
        cout << "1. Nombre: " << libros[indiceLibro].nombre << endl;
        cout << "2. Genero: " << libros[indiceLibro].genero << endl;
        cout << "3. Autor: " << libros[indiceLibro].autor << endl;
        cout << "4. Año de publicación: " << libros[indiceLibro].anoPublicacion << endl;
        cout << "5. Sinopsis: " << libros[indiceLibro].sinopsis << endl;
        cout << "6. Cantidad: " << libros[indiceLibro].cantidad << endl; // Añadimos la opción de editar la cantidad
        
        int opcion;
        cout << "\nSeleccione el número del campo que desea editar (1-6): ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1:
                cout << "Ingrese el nuevo nombre del libro: ";
                getline(cin, libros[indiceLibro].nombre);
                break;
            case 2:
                cout << "Ingrese el nuevo género del libro: ";
                getline(cin, libros[indiceLibro].genero);
                break;
            case 3:
                cout << "Ingrese el nuevo autor del libro: ";
                getline(cin, libros[indiceLibro].autor);
                break;
            case 4:
                cout << "Ingrese el nuevo año de publicación del libro: ";
                cin >> libros[indiceLibro].anoPublicacion;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                break;
            case 5:
                cout << "Ingrese la nueva sinopsis del libro: ";
                getline(cin, libros[indiceLibro].sinopsis);
                break;
            case 6:
                cout << "Ingrese la nueva cantidad del libro: ";
                cin >> libros[indiceLibro].cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
        
        ofstream Grabacion("libros.txt");
        for (int i = 0; i < n; ++i) {
            Grabacion << libros[i].codigo << endl;
            Grabacion << libros[i].nombre << endl;
            Grabacion << libros[i].genero << endl;
            Grabacion << libros[i].autor << endl;
            Grabacion << libros[i].anoPublicacion << endl;
            Grabacion << libros[i].sinopsis << endl;
            Grabacion << libros[i].cantidad << endl; // Guardamos la cantidad aquí
        }
        Grabacion.close();
        
        cout << "Información del libro editada exitosamente." << endl;
    } else {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}