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
vector<Libro> buscarCoincidencias(const vector<Libro>& libros, const string& busqueda) {
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

int main() {
    SetConsoleOutputCP(CP_UTF8);
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
        for (const Libro& libro : coincidencias) {
            cout << "Código: " << libro.codigo << endl;
            cout << "Nombre: " << libro.nombre << endl;
            cout << "Género: " << libro.genero << endl;
            cout << "Autor: " << libro.autor << endl;
            cout << "Año de Publicación: " << libro.anoPublicacion << endl;
            cout << "Sinopsis: " << libro.sinopsis << endl;
            cout << endl;
        }

        // Pausar para permitir al usuario ver los resultados
        system("pause");
    }

    return 0;
}
