#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include<limits>
#include<vector>
#include<algorithm>
#include<cstdlib>
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
    ifstream Leer("C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca/data/libros.txt", ios::in);
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

    do{
        
	int opc;
	    
        cout << "QUE FILTRO LE GUSTARIA USAR ?" << endl;
        cout << "\t 1. Nombre del libro" << endl;
        cout << "\t 2. Género" << endl;
        cout << "\t 3. Año de publicación" << endl;
        cout << "\t 4. Autor" << endl;
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
                // Función para buscar coincidencias en los títulos de los libros (ignorando mayúsculas/minúsculas)
                vector<Libro> buscarCoincidencias(const vector<Libro>& libros, const string& busqueda){
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
                vector<Libro> cargarLibrosDesdeArchivo(const string& nombreArchivo){
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
                              

                void mainBuscador(){
                     
                        // Ruta completa del archivo de texto
                        string nombreArchivo = "C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca/data/libros.txt";

                        // Cargar los libros desde el archivo de texto
                        vector<Libro> libros = cargarLibrosDesdeArchivo(nombreArchivo);

                        // Bucle de búsqueda
                        string busqueda;
                        while (true) {
                            // Limpiar la pantalla
                            system("cls");

                            // Pedir al usuario que ingrese el término de búsqueda
                         cout << "Ingrese el término de búsqueda: ";
                         getline(cin, busqueda);

                            // Buscar coincidencias
                            vector<Libro> coincidencias = buscarCoincidencias(libros, busqueda);

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
                
                mainBuscador();
                break;

            case 2:
                // Función para buscar coincidencias en los géneros de los libros (ignorando mayúsculas/minúsculas)
                vector<Libro> buscarCoincidencias(const vector<Libro>& libros, const string& busqueda) {
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
                vector<Libro> cargarLibrosDesdeArchivo(const string& nombreArchivo) {               
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

                void mainBuscador(){
                
                    // Ruta completa del archivo de texto
                    string nombreArchivo = "C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca/data/libros.txt";

                    // Cargar los libros desde el archivo de texto
                    vector<Libro> libros = cargarLibrosDesdeArchivo(nombreArchivo);

                    // Bucle de búsqueda
                    string busqueda;
                    while (true) {
                                    // Limpiar la pantalla
                        system("cls");

                        // Pedir al usuario que ingrese el término de búsqueda
                        cout << "Ingrese el género a buscar: ";
                        getline(cin,busqueda);

                        // Buscar coincidencias
                        vector<Libro> coincidencias = buscarCoincidencias(libros, busqueda);

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
                mainBuscador();          
                break;
                
            case 3:
                // Función para buscar coincidencias en los años de publicación de los libros
                vector<Libro> buscarCoincidencias(const vector<Libro>& libros, const string& busqueda) {
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
                vector<Libro> cargarLibrosDesdeArchivo(const string& nombreArchivo){
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

                void mainBuscar() {
                
                    // Ruta completa del archivo de texto
                    string nombreArchivo = "C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca/data/libros.txt";

                    // Cargar los libros desde el archivo de texto
                    vector<Libro> libros = cargarLibrosDesdeArchivo(nombreArchivo);

                    // Bucle de búsqueda
                    string busqueda;
                    while (true) {
                        // Limpiar la pantalla
                        system("cls");

                        // Pedir al usuario que ingrese el año de publicación a buscar
                        cout << "Ingrese el año de publicación a buscar: ";
                        getline(cin, busqueda);

                        // Buscar coincidencias
                        vector<Libro> coincidencias = buscarCoincidencias(libros, busqueda);

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
                mainBuscador();
                break;
                
            case 4:
            	
                    // Función para buscar coincidencias en los autores de los libros (ignorando mayúsculas/minúsculas)
                    vector<Libro> buscarCoincidencias(const vector<Libro>& libros, const string& busqueda) {
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
                    vector<Libro> cargarLibrosDesdeArchivo(const string& nombreArchivo) {
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
        
                    void mainBuscar(){
        
                        // Ruta completa del archivo de texto
                        string nombreArchivo = "C:/Users/Giancarlo/Desktop/Proyecto algoritmica/fisiteca/data/libros.txt";

                        // Cargar los libros desde el archivo de texto
                        vector<Libro>libros = cargarLibrosDesdeArchivo(nombreArchivo);

                        // Bucle de búsqueda
                        string busqueda;
                        while (true) {
                            // Limpiar la pantalla
                            system("cls");

                            // Pedir al usuario que ingrese el término de búsqueda
                            cout << "Ingrese el autor de búsqueda: ";
                            getline(cin, busqueda);

                            // Buscar coincidencias
                            vector<Libro> coincidencias = buscarCoincidencias(libros, busqueda);

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

                   mainBuscador();
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

