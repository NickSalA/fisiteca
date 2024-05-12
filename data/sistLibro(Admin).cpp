#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>

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
    ifstream Leer("C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca-1/data/libros.txt", ios::in);
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

    //Prob cuando lo compilen les salga erro/r D:, si encuentran la forma de conectarlo a la nube en lugar del espacio de trabajo local colocanlo uu
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
    cin >> newLibro.anoPublicacion;
    cin.ignore();
    cout << "Sinopsis: ";
    getline(cin, newLibro.sinopsis);
    libros[n] = newLibro;
    n++;
    ofstream Grabacion("C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca-1/data/libros.txt", ios::app);
    if (Grabacion.fail()) {
        cout << "Error en el archivo..." << endl;
        Sleep(2000);
    } else {
        Grabacion << newLibro.codigo << endl;
        Grabacion << newLibro.nombre << endl;
        fflush(stdin);
        Grabacion << newLibro.genero << endl;
        Grabacion << newLibro.autor << endl;
        Grabacion << newLibro.anoPublicacion << endl;
        Grabacion << newLibro.sinopsis << endl;
        Grabacion.close();
    }
}
void eliminarLibro(){
    
}
//int main provisional, lo importante es lo de arriba xd
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Libro libros[100];
    int n = 0;
    leerLibro(libros,n);
    int opcion;
    do {
        cout << "\n1. Agregar libro\n2. Leer libros\n3. Salir" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarLibro(libros, n);
                leerLibro(libros,n);
                break;
            case 2:
                int numlibro;
                
                for (int i = 0; i < n; i++) {
                    cout << "\nLibro " << i + 1<<": " <<libros[i].nombre<< endl;
                }
                cout<<"Seleccione su libro "<<endl;cin>>numlibro;
                numlibro-=1;
                cout<<"\nLibro: "<<libros[numlibro].nombre;
                cout<<"\nGenero: "<<libros[numlibro].genero;
                cout<<"\nAutor: "<<libros[numlibro].autor;
                cout<<"\nAño de publicacion: "<<libros[numlibro].anoPublicacion;
                cout<<"\nSipnosis: "<<libros[numlibro].sinopsis;
                break;
            case 3:
                cout << "Adios!" << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
        system("pause");
        system("cls");

    } while (opcion!= 3);
}