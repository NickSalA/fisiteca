#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
    int cantidad;
};

void cargarLibros(vector<Libro>& libros, const string& filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    while (!archivo.eof()) {
        Libro libro;
        string linea;

        getline(archivo, linea);
        if (linea.empty()) break;
        libro.codigo = stoi(linea);

        getline(archivo, libro.nombre);
        getline(archivo, libro.genero);
        getline(archivo, libro.autor);

        getline(archivo, linea);
        libro.anoPublicacion = stoi(linea);

        getline(archivo, libro.sinopsis);

        getline(archivo, linea);
        libro.cantidad = stoi(linea);

        libros.push_back(libro);
    }

    archivo.close();
}

int buscarLibro(const vector<Libro>& libros, int codigo) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void actualizarArchivoLibros(const vector<Libro>& libros, const string& filename) {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    for (const auto& libro : libros) {
        archivo << libro.codigo << "\n"
                << libro.nombre << "\n"
                << libro.genero << "\n"
                << libro.autor << "\n"
                << libro.anoPublicacion << "\n"
                << libro.sinopsis << "\n"
                << libro.cantidad << "\n";
    }

    archivo.close();
}

bool usuarioYaTieneLibroPrestado(const string& usuario, int codigo) {
    ifstream archivo("libros(pedidos).txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo libros(pedidos).txt\n";
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Usuario: " + usuario) != string::npos) {
            getline(archivo, linea); // Leer la línea del código
            if (linea.find("Código: " + to_string(codigo)) != string::npos) {
                archivo.close();
                return true;
            }
        }
        // Saltar las siguientes líneas del libro prestado
        for (int i = 0; i < 6; ++i) {
            getline(archivo, linea);
        }
    }

    archivo.close();
    return false;
}

int contarLibrosPrestados(const string& usuario) {
    ifstream archivo("libros(pedidos).txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo libros(pedidos).txt\n";
        return 0;
    }

    int count = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Usuario: " + usuario) != string::npos) {
            count++;
        }
        // Saltar las siguientes líneas del libro prestado
        for (int i = 0; i < 6; ++i) {
            getline(archivo, linea);
        }
    }

    archivo.close();
    return count;
}

void prestarLibro(vector<Libro>& libros, const string& filename, const string& usuario) {
    if (contarLibrosPrestados(usuario) >= 3) {
        cout << "Ya has pedido prestado el máximo de 3 libros.\n";
        return;
    }

    int codigo;
    cout << "Ingresa el código del libro que quieres pedir prestado: ";
    cin >> codigo;

    if (usuarioYaTieneLibroPrestado(usuario, codigo)) {
        cout << "Ya has pedido prestado este libro.\n";
        return;
    }

    int i = buscarLibro(libros, codigo);
    if (i == -1) {
        cout << "\nLo siento, ese libro no está disponible.\n";
    } else {
        if (libros[i].cantidad == 0) {
            cout << "\nLo siento, ese libro está agotado.\n";
        } else {
            cout << "\nInformación del libro:\n"
                 << "Código: " << libros[i].codigo << "\n"
                 << "Nombre: " << libros[i].nombre << "\n"
                 << "Género: " << libros[i].genero << "\n"
                 << "Autor: " << libros[i].autor << "\n"
                 << "Año de Publicación: " << libros[i].anoPublicacion << "\n"
                 << "Sinopsis: " << libros[i].sinopsis << "\n";

            char respuesta;
            cout << "\n¿Estás seguro de que quieres pedir prestado este libro? (S/N): ";
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                libros[i].cantidad--;

                ofstream Escribir("libros(pedidos).txt", ios::app);
                Escribir << "Usuario: " << usuario << "\n"
                         << "Código: " << libros[i].codigo << "\n"
                         << "Nombre: " << libros[i].nombre << "\n"
                         << "Género: " << libros[i].genero << "\n"
                         << "Autor: " << libros[i].autor << "\n"
                         << "Año de Publicación: " << libros[i].anoPublicacion << "\n"
                         << "Sinopsis: " << libros[i].sinopsis << "\n";
                Escribir.close();

                actualizarArchivoLibros(libros, filename);

                cout << "\nHas pedido prestado el libro " << libros[i].nombre << ".\n";
            } else {
                cout << "\nHas decidido no pedir prestado el libro.\n";
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    vector<Libro> libros;
    cargarLibros(libros, "libros.txt");

    if (libros.empty()) {
        cout << "No hay libros disponibles para prestar.\n";
        return 1;
    }

    string usuario;
    ifstream credUsuario("credUsuario.txt");
    if (credUsuario.is_open()) {
        getline(credUsuario, usuario);
        credUsuario.close();
    } else {
        cout << "No se pudo abrir el archivo credUsuario.txt\n";
        return 1;
    }

    prestarLibro(libros, "libros.txt", usuario);

    return 0;
}
