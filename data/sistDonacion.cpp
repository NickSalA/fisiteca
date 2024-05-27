#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <locale> // Agregar para setlocale
#include <algorithm> // Agregar para all_of

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

bool esNumero(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

void actualizarArchivoLibros(const vector<Libro>& libros, const string& filename) {
    ofstream archivo(filename, std::ios::app); // Abre el archivo en modo de agregar
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

void cargarLibros(vector<Libro>& libros, const string& filename, unordered_set<int>& codigos, unordered_set<string>& nombres) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    string linea;
    int contador = 0;
    Libro libro;

    while (getline(archivo, linea)) {
        if ((contador % 7 == 0 || contador % 7 == 4 || contador % 7 == 6) && !esNumero(linea)) {
            cerr << "Error: se esperaba un número en la línea " << contador + 1 << ", pero se encontró '" << linea << "'.\n";
            return;
        }
        if (contador % 7 == 1) {
            libro.nombre = linea;
            if (nombres.find(libro.nombre) != nombres.end()) {
                cerr << "El nombre '" << libro.nombre << "' está duplicado en el archivo.\n";
                cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 'S' || respuesta == 's') {
                    cout << "Ingresa la cantidad que deseas añadir: ";
                    int cantidad;
                    cin >> cantidad;
                    libro.cantidad = cantidad;
                    libros.push_back(libro); // Se agrega fuera del bucle
                    actualizarArchivoLibros(libros, filename);
                    cout << "Cantidad actualizada exitosamente.\n";
                    return;
                } else {
                    cout << "No se agregó ningún libro.\n";
                    return;
                }
            }
            nombres.insert(libro.nombre);
        } else if (contador % 7 == 0) {
            libro.codigo = stoi(linea);
            if (codigos.find(libro.codigo) != codigos.end()) {
                cerr << "El código " << libro.codigo << " está duplicado en el archivo.\n";
                contador = 0;
                continue;
            }
            codigos.insert(libro.codigo);
        } else if (contador % 7 == 2) {
            libro.genero = linea;
        } else if (contador % 7 == 3) {
            libro.autor = linea;
        } else if (contador % 7 == 4) {
            libro.anoPublicacion = stoi(linea);
        } else if (contador % 7 == 5) {
            libro.sinopsis = linea;
        } else if (contador % 7 == 6) {
            libro.cantidad = stoi(linea);
            libros.push_back(libro); // Se agrega el libro después de que todos sus campos hayan sido leídos y asignados
        }
        contador++;
    }

    archivo.close();
}

int buscarLibroPorCodigo(const vector<Libro>& libros, int codigo) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void donarLibro(vector<Libro>& libros, vector<Libro>& librosDonados, const string& filename) {
    Libro libro;
    cout << "Ingresa el código del libro que quieres donar: ";
    cin >> libro.codigo;

    int i = buscarLibroPorCodigo(libros, libro.codigo);
    if (i != -1) {
        cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta == 'S' || respuesta == 's') {
            cout << "Ingresa la cantidad que deseas añadir: ";
            int cantidad;
            cin >> cantidad;
            libros[i].cantidad += cantidad;
            actualizarArchivoLibros(libros, filename);
            cout << "Cantidad actualizada exitosamente.\n";
            return;
        } else {
            cout << "No se agregó ningún libro.\n";
            return;
        }
    }

    cout << "Ingresa el nombre del libro: ";
    cin.ignore();
    getline(cin, libro.nombre);

    for (size_t i = 0; i < librosDonados.size(); i++) {
        if (librosDonados[i].nombre == libro.nombre) {
            cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta == 'S' || respuesta == 's') {
                cout << "Ingresa la cantidad que deseas añadir: ";
                int cantidad;
                cin >> cantidad;
                librosDonados[i].cantidad += cantidad; // Actualiza la cantidad del libro existente
                actualizarArchivoLibros(librosDonados, "libros(donativo).txt"); // Actualiza el archivo "libros(donativo).txt" con los libros donados
                cout << "Cantidad actualizada exitosamente.\n";
                return;
            } else {
                cout << "No se agregó ningún libro.\n";
                return;
            }
        }
    }

    cout << "Ingresa el género del libro: ";
    getline(cin, libro.genero);

    cout << "Ingresa el autor del libro: ";
    getline(cin, libro.autor);

    cout << "Ingresa el año de publicación del libro: ";
    cin >> libro.anoPublicacion;
    cout << "Ingresa la sinopsis del libro: ";
    cin.ignore();
    getline(cin, libro.sinopsis);

    cout << "Ingresa la cantidad del libro: ";
    cin >> libro.cantidad;

    libros.push_back(libro);
    librosDonados.push_back(libro); // Agrega el libro donado al vector de libros donados
    actualizarArchivoLibros(librosDonados, "libros(donativo).txt"); // Actualiza el archivo "libros(donativo).txt" con los libros donados
    cout << "Libro donado exitosamente.\n";
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8"); // Se configura la localización
    vector<Libro> libros;
    vector<Libro> librosDonados; // Vector para almacenar los libros donados
    unordered_set<int> codigos;
    unordered_set<string> nombres;
    cargarLibros(libros, "libros.txt", codigos, nombres);

    donarLibro(libros, librosDonados, "libros.txt");

    return 0;
}
