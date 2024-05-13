#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> // Para std::numeric_limits
#include <cstdlib> // Para system
#include <windows.h>

using namespace std;

// Estructura para representar un libro
struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
};

// Función para buscar coincidencias en los títulos de los libros (ignorando mayúsculas/minúsculas)
vector<Libro> buscarCoincidencias_ti(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    // Convertir la búsqueda a minúsculas (o mayúsculas) para ignorar diferencias de caso
    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        // Convertir el título del libro a minúsculas (o mayúsculas)
        string tituloLower = libro.nombre;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        // Buscar coincidencias
        if (tituloLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}

// Función para cargar los libros desde un archivo de texto
vector<Libro> cargarLibrosDesdeArchivo_ti(const string& nombreArchivo) {
    vector<Libro> libros;
    ifstream archivo(nombreArchivo.c_str(), ios::in); // Se necesita convertir la cadena de nombreArchivo a un const char* usando c_str()
    if (archivo.is_open()) {
        Libro libro;
        while (archivo >> libro.codigo) {
            // Ignorar el carácter de nueva línea después del código
            archivo.ignore();
            // Leer los demás atributos del libro
            getline(archivo, libro.nombre);
            getline(archivo, libro.genero);
            getline(archivo, libro.autor);
            archivo >> libro.anoPublicacion;
            // Ignorar el carácter de nueva línea después del año de publicación
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
    // Ruta completa del archivo de texto
    string nombreArchivo = "D:/Repos/fisiteca-1/data/output/libros.txt";

    // Cargar los libros desde el archivo de texto
    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    // Bucle de búsqueda
    string busqueda;
    while (true) {
        // Limpiar la pantalla
        system("cls");

        // Pedir al usuario que ingrese el término de búsqueda
        cout << "Ingrese el término de búsqueda: ";
        getline(cin, busqueda);

        // Buscar coincidencias
        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        // Mostrar coincidencias
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

        // Pausar para permitir al usuario ver los resultados
        system("pause");
    }

}




vector<Libro> buscarCoincidencias_gen(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    // Convertir la búsqueda a minúsculas (o mayúsculas) para ignorar diferencias de caso
    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        // Convertir el género del libro a minúsculas (o mayúsculas)
        string generoLower = libro.genero;
        transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

        // Buscar coincidencias
        if (generoLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

     return coincidencias;
}

    // Función para cargar los libros desde un archivo de texto
vector<Libro> cargarLibrosDesdeArchivo_gen(const string& nombreArchivo) {               
        vector<Libro> libros;
        ifstream archivo(nombreArchivo.c_str(), ios::in); // Se necesita convertir la cadena de nombreArchivo a un const char* usando c_str()
        if (archivo.is_open()) {
            Libro libro;
            while (archivo >> libro.codigo) {
                // Ignorar el carácter de nueva línea después del código
                archivo.ignore();
                // Leer los demás atributos del libro
                getline(archivo, libro.nombre);
                getline(archivo, libro.genero);
                getline(archivo, libro.autor);
                archivo >> libro.anoPublicacion;
                // Ignorar el carácter de nueva línea después del año de publicación
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

void mainBuscador_gen(){
                
    // Ruta completa del archivo de texto
    string nombreArchivo = "D:/Repos/fisiteca-1/data/output/libros.txt";

    // Cargar los libros desde el archivo de texto
    vector<Libro> libros = cargarLibrosDesdeArchivo_gen(nombreArchivo);

    // Bucle de búsqueda
    string busqueda;
    while (true) {
                    // Limpiar la pantalla
        system("cls");

        // Pedir al usuario que ingrese el término de búsqueda
        cout << "Ingrese el género a buscar: ";
        getline(cin,busqueda);

        // Buscar coincidencias
        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

                    // Mostrar coincidencias
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

        // Pausar para permitir al usuario ver los resultados 
        system("pause");
    }

}





// Función para buscar coincidencias en los años de publicación de los libros
vector<Libro> buscarCoincidencias_anio(const vector<Libro>& libros, const string& busqueda) {
                    vector<Libro> coincidencias;

                    for (const Libro& libro : libros) {
                        // Convertir el año de publicación del libro a string
                        string anoPublicacionStr = to_string(libro.anoPublicacion);

                        // Buscar coincidencias
                        if (anoPublicacionStr.find(busqueda) != string::npos) {
                                            coincidencias.push_back(libro);
                        }
                    }

                    return coincidencias;
                }

// Función para cargar los libros desde un archivo de texto
vector<Libro> cargarLibrosDesdeArchivo_anio(const string& nombreArchivo){
                    vector<Libro> libros;
                    ifstream archivo(nombreArchivo.c_str(), ios::in); // Se necesita convertir la cadena de nombreArchivo a un const char* usando c_str()
                    if (archivo.is_open()) {
                        Libro libro;
                        while (archivo >> libro.codigo) {
                            // Ignorar el carácter de nueva línea después del código
                            archivo.ignore();
                            // Leer los demás atributos del libro
                            getline(archivo, libro.nombre);
                            getline(archivo, libro.genero);
                            getline(archivo, libro.autor);
                            archivo >> libro.anoPublicacion;
                            // Ignorar el carácter de nueva línea después del año de publicación
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

void mainBuscar_anio() {
                
                    // Ruta completa del archivo de texto
                    string nombreArchivo = "D:/Repos/fisiteca-1/data/output/libros.txt";

                    // Cargar los libros desde el archivo de texto
                    vector<Libro> libros = cargarLibrosDesdeArchivo_anio(nombreArchivo);

                    // Bucle de búsqueda
                    string busqueda;
                    while (true) {
                        // Limpiar la pantalla
                        system("cls");

                        // Pedir al usuario que ingrese el año de publicación a buscar
                        cout << "Ingrese el año de publicación a buscar: ";
                        getline(cin, busqueda);

                        // Buscar coincidencias
                        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

                        // Mostrar coincidencias
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

                        // Pausar para permitir al usuario ver los resultados 
                        system("pause");
                    }

                }



// Función para buscar coincidencias en los autores de los libros (ignorando mayúsculas/minúsculas)
vector<Libro> buscarCoincidencias_autor(const vector<Libro>& libros, const string& busqueda) {
                    vector<Libro> coincidencias;

                        // Convertir la búsqueda a minúsculas (o mayúsculas) para ignorar diferencias de caso
                        string busquedaLower = busqueda;
                        transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

                        for (const Libro& libro : libros) {
                            // Convertir el autor del libro a minúsculas (o mayúsculas)
                            string autorLower = libro.autor;
                            transform(autorLower.begin(), autorLower.end(), autorLower.begin(), ::tolower);

                            // Buscar coincidencias
                            if (autorLower.find(busquedaLower) != string::npos) {
                            coincidencias.push_back(libro);
                            }
                        }

                        return coincidencias;
                    }       

// Función para cargar los libros desde un archivo de texto
vector<Libro> cargarLibrosDesdeArchivo_autor(const string& nombreArchivo) {
                        vector<Libro> libros;
                        ifstream archivo(nombreArchivo.c_str(), ios::in); // Se necesita convertir la cadena de nombreArchivo a un const char* usando c_str()
                        if (archivo.is_open()) {
                            Libro libro;
                         while (archivo >> libro.codigo) {
                                // Ignorar el carácter de nueva línea después del código
                                archivo.ignore();
                                // Leer los demás atributos del libro
                                getline(archivo, libro.nombre);
                                getline(archivo, libro.genero);
                                getline(archivo, libro.autor);
                                archivo >> libro.anoPublicacion;
                                // Ignorar el carácter de nueva línea después del año de publicación
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
        
void mainBuscar_autor(){
        
                        // Ruta completa del archivo de texto
                        string nombreArchivo = "D:/Repos/fisiteca-1/data/output/libros.txt";

                        // Cargar los libros desde el archivo de texto
                        vector<Libro>libros = cargarLibrosDesdeArchivo_autor(nombreArchivo);

                        // Bucle de búsqueda
                        string busqueda;
                        while (true) {
                            // Limpiar la pantalla
                            system("cls");

                            // Pedir al usuario que ingrese el término de búsqueda
                            cout << "Ingrese el autor de búsqueda: ";
                            getline(cin, busqueda);

                            // Buscar coincidencias
                            vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

                            // Mostrar coincidencias
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

                            // Pausar para permitir al usuario ver los resultados
                            system("pause");
                        }
                    }

int main(){
    SetConsoleOutputCP(CP_UTF8);
    mainBuscar_autor();
    //colocar un switch futuro al menu uwu
}