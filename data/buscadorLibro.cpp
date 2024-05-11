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
    ifstream Leer("D:/Repos/fisiteca/data/libros.txt", ios::in);
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

int main(){
    Libro libros[100];
    int n = 0;
    leerLibro(libros,n);
    int opcion;
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
}
