#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include<locale>

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
}; //incluir esto con las librerias para que funcione.

void esperaConMensaje(const string& mensaje) {
    cout << mensaje << endl;
    _getwch(); // Espera a que el usuario presione una tecla sin mostrar un mensaje por defecto
}

vector<Libro> cargarLibrosDesdeArchivo_ti(const string& nombreArchivo) {
    vector<Libro> libros;
    ifstream archivo(nombreArchivo.c_str(), ios::in);
    if (archivo.is_open()) {
        Libro libro;
        while (archivo >> libro.codigo) {

            archivo.ignore();
            getline(archivo, libro.nombre);
            getline(archivo, libro.genero);
            getline(archivo, libro.autor);
            archivo >> libro.anoPublicacion;
            archivo.ignore();
            getline(archivo, libro.sinopsis);
            libros.push_back(libro);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return libros;
}


vector<Libro> buscarCoincidencias_ti(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string tituloLower = libro.nombre;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (tituloLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscador_ti() {
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");
        
        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el titulo a buscar: ";
        getline(cin, busqueda);
        
        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        
        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_gen(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string generoLower = libro.genero;
        transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

        if (generoLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscador_gen() {
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el genero a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_autor(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string autorLower = libro.autor;
        transform(autorLower.begin(), autorLower.end(), autorLower.begin(), ::tolower);

        if (autorLower.find(busquedaLower) != string::npos) {
        coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}             
void mainBuscar_autor(){
        
     string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el autor a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_anio(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    for (const Libro& libro : libros) {
        string anoPublicacionStr = to_string(libro.anoPublicacion);

        if (anoPublicacionStr.find(busqueda) != string::npos) {
                            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscar_anio() {
                
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el anio a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


void escogerFiltro(){

    int opcion;
    do{
    
    system("cls");
    cout << "Bienvenido al sistema de búsqueda de libros." << endl;
    cout << "1. Buscar por título" << endl;
    cout << "2. Buscar por género" << endl;
    cout << "3. Buscar por año de publicación" << endl;
    cout << "4. Buscar por autor" << endl;
    cout << "5. Regresar al menú principal" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1:
            mainBuscador_ti();
            break;
        case 2:
            mainBuscador_gen();
            break;
        case 3:
            mainBuscar_anio();
            break;
        case 4:
            mainBuscar_autor();
            break;
        case 5:
            exit(0);//debe ir un break pero eso es con el menú principal
        default:
            cout << "Opción no válida." << endl;
            break;
    }
    }while(opcion != 5);
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    escogerFiltro();
}