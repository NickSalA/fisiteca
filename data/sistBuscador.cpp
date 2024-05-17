#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> 
#include <cstdlib> 
#include <windows.h>

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
};


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

void mainBuscador_ti(){
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    while (true) {
        system("cls");

        cout << "Ingrese el término de búsqueda: ";
        getline(cin, busqueda);


        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        cout << "Coincidencias encontradas:\n";
        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
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
        system("pause");
    }

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



void mainBuscador_gen(){
                
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    while (true) {
        system("cls");
        cout << "Ingrese el género a buscar: ";
        getline(cin,busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

        cout << "Coincidencias encontradas:\n";
        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el género: " << busqueda << endl;
        } else {
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
        system("pause");
    }

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
                    while (true) {
                        system("cls");

                        cout << "Ingrese el año de publicación a buscar: ";
                        getline(cin, busqueda);

                        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

                        cout << "Coincidencias encontradas:\n";
                        if (coincidencias.empty()) {
                            cout << "No se encontraron coincidencias para el año de publicación: " << busqueda << endl;
                        } else {
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

                        system("pause");
                    }

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

                        vector<Libro>libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

                        string busqueda;
                        while (true) {
                            system("cls");

                            cout << "Ingrese el autor de búsqueda: ";
                            getline(cin, busqueda);

                            vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

                            cout << "Coincidencias encontradas:\n";
                            if (coincidencias.empty()) {
                                cout << "No se encontraron coincidencias para el autor de búsqueda: " << busqueda << endl;
                            } else {
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

                            system("pause");
                        }
                    }

int main(){
    setlocale(LC_ALL, "es_ES.UTF-8"); 
    mainBuscar_autor();
    
}