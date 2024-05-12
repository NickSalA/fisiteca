#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include<limits>
using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
};

void leerLibro(Libro libros[], int& n) {
    ifstream Leer("C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca-1/data/libros.txt", ios::in);
    if (Leer.fail()) {
        cout << "Error en el archivo..." << endl;
        exit(1);
    }
    int i = 0;
    while (!Leer.eof()) {
        //lectura de datos
        string xcodigo, xano;
        getline(Leer, xcodigo);
        getline(Leer, libros[i].nombre);
        getline(Leer, libros[i].genero);
        getline(Leer, libros[i].autor);
        getline(Leer, xano);
        getline(Leer, libros[i].sinopsis);
        //almacenar datos
        istringstream(xcodigo) >> libros[i].codigo;
        istringstream(xano) >> libros[i].anoPublicacion;
        n++;
        i++;
    }
    Leer.close();
}

void buscar(int n,Libro libros[]){
	
	int opc;
	    do {
        cout << "QUE FILTRO LE GUSTARIA USAR ?" << endl;
        cout << "\t 1. Nombre del libro" << endl;
        cout << "\t 2. Género" << endl;
        cout << "\t 3. Autor" << endl;
        cout << "\t 4. Año de lanzamiento" << endl;
        cout << "\t 5. Retroceder" << endl;
        cin >> opc;
        system("cls");

        // Limpiar el búfer de entrada(no c q es,pero m dio muchos errores)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        string dato;
        int anio;
        string coincidencia[100];
        string nombre;

        switch (opc) {
            case 1:
                cout << "INGRESE EL TITULO DEL LIBRO: ";
                getline(cin, dato);

                for (int i = 0; i < n; i++) {
                    if (dato == libros[i].nombre) {
                        coincidencia[i] = dato;
                    }
                }

                for (int k = 0; k < n - 1; k++) {
                    if (coincidencia[k] == dato) {
                        cout << "\nLibro " << k + 1 << ": " << libros[k].nombre << endl << endl;
                    }
                }
                break;

            case 2:
				cout << "INGRESE EL GENERO DEL LIBRO: ";
                getline(cin, dato);

                for (int i = 0; i < n; i++) {
                    if (dato == libros[i].genero) {
                        coincidencia[i] = dato;
                    }
                }

                for (int k = 0; k < n - 1; k++) {
                    if (coincidencia[k] == dato) {
                        cout << "\nLibro " << k + 1 << ": " << libros[k].nombre << endl << endl;
                    }
                }
                break;
                
            case 3:
            	cout << "INGRESE EL AUTOR DEL LIBRO: ";
                getline(cin, dato);

                for (int i = 0; i < n; i++) {
                    if (dato == libros[i].autor) {
                        coincidencia[i] = dato;
                    }
                }

                for (int k = 0; k < n - 1; k++) {
                    if (coincidencia[k] == dato) {
                        cout << "\nLibro " << k + 1 << ": " << libros[k].nombre << endl << endl;
                    }
                }
                break;
                
            case 4:
            	cout << "INGRESE EL AÑO DE LANZAMIENTO DEL LIBRO: ";
                cin>>anio;

                for (int i = 0; i < n; i++) {
                    if (anio == libros[i].anoPublicacion) {
                        coincidencia[i] = dato;
                    }
                }

                for (int k = 0; k < n - 1; k++) {
                    if (coincidencia[k] == dato) {
                        cout << "\nLibro " << k + 1 << ": " << libros[k].nombre << endl << endl;
                    }
                }
                break;
            	
            case 5:
                cout << "saliendo uu...." << endl;
                break;

            default:
                cout << "Opción no válida. Ingrese un número del 1 al 5." << endl;
                break;
        }
    } while (opc != 5);   
}

int main() {
    SetConsoleOutputCP(CP_UTF8); //CONDIGURA EL CODIGO A ESPAÑOL

    int n = 0;
    Libro libros[100];
    leerLibro(libros, n);
    int numlibro;
    int opc;
    
    buscar(n,libros);
}
