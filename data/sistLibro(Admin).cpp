#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <limits>
#include "../menu/funciones.hpp"

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
    
    mostrarBarraDeCarga(100,100,5000);

    system("cls");

    dibujarCuadro(10, 0, 100, 30);
    dibujarTitulo(50, 2, "Editar libro");
    int numLibro;
    
    for (int i = 0; i < n; i++) {
        dibujarTexto(20, 5 + i * 1, "Libro " + to_string(i + 1) + ": " + libros[i].nombre + " - Cantidad: " + to_string(libros[i].cantidad));
    }
      
        dibujarTeslaASCII(90, 15);

    dibujarTexto(20, 6 + n * 1, "Seleccione el número del libro que desea editar: ");
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    


    system("cls");

    if (numLibro >= 1 && numLibro <= n) {
        int indiceLibro = numLibro - 1;
        dibujarCuadro(10, 0, 100, 20);
        dibujarTexto(20, 2, "Editar libro: " + libros[indiceLibro].nombre);
        dibujarTexto(20, 4, "1. Nombre: " + libros[indiceLibro].nombre);
        dibujarTexto(20, 6, "2. Genero: " + libros[indiceLibro].genero);
        dibujarTexto(20, 8, "3. Autor: " + libros[indiceLibro].autor);
        dibujarTexto(20, 10, "4. Año de publicación: " + to_string(libros[indiceLibro].anoPublicacion));
        dibujarTexto(20, 12, "5. Sinopsis: " + libros[indiceLibro].sinopsis);
        dibujarTexto(20, 14, "6. Cantidad: " + to_string(libros[indiceLibro].cantidad)); // Añadimos la opción de editar la cantidad
        int opcion;
        dibujarTexto(20, 16, "Seleccione el número del campo que desea editar (1-6): ");
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");
        system("cls");

        dibujarCuadro(10, 0, 100, 20);
        dibujarTitulo(50, 2, "Editor de libros");
        dibujarTeslaASCII(90, 15);
        switch (opcion) {
            case 1:
                dibujarTexto(20, 10, "Ingrese el nuevo nombre del libro: ");
                getline(cin, libros[indiceLibro].nombre);
                break;
            case 2:
                dibujarTexto(20, 10, "Ingrese el nuevo género del libro: ");
                getline(cin, libros[indiceLibro].genero);
                break;
            case 3:
                dibujarTexto(20, 10, "Ingrese el nuevo autor del libro: ");
                getline(cin, libros[indiceLibro].autor);
                break;
            case 4:
                dibujarTexto(20, 10, "Ingrese el nuevo año de publicación del libro: ");
                cin >> libros[indiceLibro].anoPublicacion;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                break;
            case 5:
                dibujarTexto(20, 10, "Ingrese la nueva sinopsis del libro: ");
                getline(cin, libros[indiceLibro].sinopsis);
                break;
            case 6:
                dibujarTexto(20, 10, "Ingrese la nueva cantidad del libro: ");
                cin >> libros[indiceLibro].cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                break;
            default:
                dibujarTexto(20, 10, "Opción no válida.");
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

int main (){

    Set_Console_Sizes(150, 100, false);
    setColor(White);
    configurarConsolaUtf8();

    Libro libroa[100];  
    int n=0;
    leerLibro(libroa,n);
    editarLibro(libroa,n);
}