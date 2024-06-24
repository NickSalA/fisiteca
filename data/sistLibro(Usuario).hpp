#ifndef SISTLIBROUSUARIO_HPP
#define SISTLIBROUSUARIO_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include <locale>
#include "../menu/funciones.hpp"

using namespace std;

vector<Libro> cargarLibrosDesdeArchivo_ti(const string &nombreArchivo)
{
    vector<Libro> libros;
    ifstream archivo(nombreArchivo.c_str(), ios::in);
    if (archivo.is_open())
    {
        Libro libro;
        while (archivo >> libro.codigo)
        {

            archivo.ignore();
            getline(archivo, libro.nombre);
            getline(archivo, libro.genero);
            getline(archivo, libro.autor);
            archivo >> libro.anoPublicacion;
            archivo.ignore();
            getline(archivo, libro.sinopsis);
            archivo >> libro.cantidad;
            archivo.ignore();
            libros.push_back(libro);
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return libros;
}

vector<Libro> buscarCoincidencias_ti(const vector<Libro> &libros, const string &busqueda)
{
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro &libro : libros)
    {
        string tituloLower = libro.nombre;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (tituloLower.find(busquedaLower) != string::npos)
        {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}

void mainBuscador_ti()
{
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");

        cout << "0.Regresar\n";
        cout << "\t\tIngrese el titulo a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        if (busqueda == to_string(0))
        {

            cout << "Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        }
        else
        {
            cout << "Coincidencias encontradas:\n";
            for (const Libro &libro : coincidencias)
            {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << "Cantidad: " << libro.cantidad << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while (true);
}

vector<Libro> buscarCoincidencias_gen(const vector<Libro> &libros, const string &busqueda)
{
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro &libro : libros)
    {
        string generoLower = libro.genero;
        transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

        if (generoLower.find(busquedaLower) != string::npos)
        {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}

bool buscarcoincidencia_cod(const std::string& codigo) {
    std::ifstream archivo("libros.txt");
    std::string linea;

    // Verificar si se pudo abrir el archivo
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo libros.txt" << std::endl;
        return false; // No se pudo abrir el archivo
    }

    // Recorrer cada línea del archivo
    while (std::getline(archivo, linea)) {
        // Si la línea contiene el código buscado, retornar true
        if (linea == codigo) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false; // No se encontró el código en el archivo
}

void mainBuscador_gen()
{
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");

        cout << "0.Regresar\n";
        cout << "\t\tIngrese el genero a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

        if (busqueda == to_string(0))
        {

            cout << "Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        }
        else
        {
            cout << "Coincidencias encontradas:\n";
            for (const Libro &libro : coincidencias)
            {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << "Cantidad: " << libro.cantidad << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while (true);
}

vector<Libro> buscarCoincidencias_autor(const vector<Libro> &libros, const string &busqueda)
{
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro &libro : libros)
    {
        string autorLower = libro.autor;
        transform(autorLower.begin(), autorLower.end(), autorLower.begin(), ::tolower);

        if (autorLower.find(busquedaLower) != string::npos)
        {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}

void mainBuscar_autor()
{

    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");

        cout << "0.Regresar\n";
        cout << "\t\tIngrese el autor a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

        if (busqueda == to_string(0))
        {

            cout << "Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        }
        else
        {
            cout << "Coincidencias encontradas:\n";
            for (const Libro &libro : coincidencias)
            {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << "Cantidad: " << libro.cantidad << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while (true);
}

vector<Libro> buscarCoincidencias_anio(const vector<Libro> &libros, const string &busqueda)
{
    vector<Libro> coincidencias;

    for (const Libro &libro : libros)
    {
        string anoPublicacionStr = to_string(libro.anoPublicacion);

        if (anoPublicacionStr.find(busqueda) != string::npos)
        {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}

void mainBuscar_anio()
{

    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");

        cout << "0.Regresar\n";
        cout << "\t\tIngrese el año a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

        if (busqueda == to_string(0))
        {

            cout << "Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        }
        else
        {
            cout << "Coincidencias encontradas:\n";
            for (const Libro &libro : coincidencias)
            {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout << "Cantidad: " << libro.cantidad << endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while (true);
}

void BuscarLibro()
{
    configurarConsolaUtf8();
    int opcionSeleccionada = 1; // Indica la opción seleccionada
    int lastopcionSeleccionada = -1; 
    vector<string> opciones = {" Buscar por título", " Buscar por género", " Buscar por año de publicación", " Buscar por autor", " Regresar al menu de usuario"};
    coordXY pos = {40, 15};
    string titulo = R"(

                                        ░░████░█░░█░███░███░░█░░█░███░████░████░
                                        ░░█░░█░█░░█░█░░░█░█░░█░░█░█░░░█░░█░█░░█░
                                        ░░███░░█░░█░███░█░█░░█░░█░███░█░░█░████░
                                        ░░█░░█░█░░█░░░█░█░█░░█░░█░█░░░█░░█░█░░█░
                                        ░░████░████░███░████░████░███░████░█░░█░


)";
    ocultarCursor();
    limpiarPantalla();
    dibujarTitulo(2, 3, titulo);
    dibujarCuadro(pos.x-10, 2, 60, 25);
    dibujarMenu(pos.x+3, pos.y-2, opciones);
    bool repite = true; 

    while (repite){
        if (lastopcionSeleccionada != opcionSeleccionada) {
            if (lastopcionSeleccionada != -1) {
                moverCursor({pos.x-2, pos.y-2 + lastopcionSeleccionada * 3});
                cout << "  ";
                moverCursor({pos.x + 41, pos.y-2 + lastopcionSeleccionada * 3});
                cout << "  ";
            }

            moverCursor({pos.x-2, pos.y-2 + opcionSeleccionada * 3});
            cout << "=>";
            moverCursor({pos.x + 41, pos.y-2 + opcionSeleccionada * 3});
            cout << "<=";
            
            lastopcionSeleccionada = opcionSeleccionada;
        }

        char key = _getch();
        if (key == 72 && opcionSeleccionada > 0) {
            opcionSeleccionada--;
        } else if (key == 80 && opcionSeleccionada < static_cast<int>(opciones.size() - 1)) {
            opcionSeleccionada++;
        } else if (key == '\r') {
            limpiarPantalla();
            switch (opcionSeleccionada) {
                case 0: 
                    mainBuscador_ti();
                    break;
                case 1: 
                    mainBuscador_gen();
                    break;
                case 2: 
                    mainBuscar_autor();
                    break;
                case 3: 
                    mainBuscar_anio();
                    break;
                case 4: 
                    repite = false;
                    break;
            }
            limpiarPantalla();
            dibujarTitulo(2, 3, titulo);
            dibujarCuadro(pos.x-8, 2, 50, 25);
            dibujarMenu(pos.x+9, pos.y-1, opciones);
            lastopcionSeleccionada = -1;
        }
    }
}

void cargarLibros(vector<Libro> &libros, const string &filename)
{
    ifstream archivo(filename);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    while (!archivo.eof())
    {
        Libro libro;
        string linea;

        getline(archivo, linea);
        if (linea.empty())
            break;
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

int buscarLibro(const vector<Libro> &libros, int codigo)
{
    for (size_t i = 0; i < libros.size(); i++)
    {
        if (libros[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}

void actualizarArchivoLibros(const vector<Libro> &libros, const string &filename)
{
    ofstream archivo(filename);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    for (const auto &libro : libros)
    {
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

bool usuarioYaTieneLibroPrestado(const string &usuario, int codigo)
{
    ifstream archivo("libros(pedidos).txt");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo libros(pedidos).txt\n";
        return false;
    }

    string linea;
    while (getline(archivo, linea))
    {
        if (linea.find("Usuario: " + usuario) != string::npos)
        {
            getline(archivo, linea); // Leer la línea del código
            if (linea.find("Código: " + to_string(codigo)) != string::npos)
            {
                archivo.close();
                return true;
            }
        }
        // Saltar las siguientes líneas del libro prestado
        for (int i = 0; i < 6; ++i)
        {
            getline(archivo, linea);
        }
    }

    archivo.close();
    return false;
}

int contarLibrosPrestados(const string &usuario)
{
    ifstream archivo("libros(pedidos).txt");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo libros(pedidos).txt\n";
        return 0;
    }

    int count = 0;
    string linea;
    while (getline(archivo, linea))
    {
        if (linea.find("Usuario: " + usuario) != string::npos)
        {
            count++;
        }
        // Saltar las siguientes líneas del libro prestado
        for (int i = 0; i < 6; ++i)
        {
            getline(archivo, linea);
        }
    }

    archivo.close();
    return count;
}

void prestamoLibro(vector<Libro> libros, const string &filename, string &usuarioIngresado)
{
    if (contarLibrosPrestados(usuarioIngresado) >= 3)
    {
        cout << "Ya has pedido prestado el máximo de 3 libros.\n";
        return;
    }

    int codigo;
    cout << "Ingresa el código del libro que quieres pedir prestado: ";
    cin >> codigo;

    if (usuarioYaTieneLibroPrestado(usuarioIngresado, codigo))
    {
        cout << "Ya has pedido prestado este libro.\n";
        return;
    }

    int i = buscarLibro(libros, codigo);
    if (i == -1)
    {
        cout << "\nLo siento, ese libro no está disponible.\n";
    }
    else
    {
        if (libros[i].cantidad == 0)
        {
            cout << "\nLo siento, ese libro está agotado.\n";
        }
        else
        {
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
            if (respuesta == 's' || respuesta == 'S')
            {
                libros[i].cantidad--;

                ofstream Escribir("libros(pedidos).txt", ios::app);
                Escribir << usuarioIngresado << "\n"
                         << libros[i].codigo << "\n"
                         << libros[i].nombre << "\n";
                Escribir.close();

                actualizarArchivoLibros(libros, filename);

                cout << "\nHas pedido prestado el libro " << libros[i].nombre << ".\n";
            }
            else
            {
                cout << "\nHas decidido no pedir prestado el libro.\n";
            }
        }
    }
}

void prestarLibro(string &usuarioIngresado)
{
    limpiarPantalla();
    vector<Libro> libros;
    cargarLibros(libros, "libros.txt");

    if (libros.empty())
    {
        cout << "No hay libros disponibles para prestar.\n";
    }

    prestamoLibro(libros, "libros.txt", usuarioIngresado);
}

void CargarLibros(vector<Libro> &libros, const string &filename, unordered_set<int> &codigos, unordered_set<string> &nombres)
{
    ifstream archivo(filename);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo " << filename << "\n";
        return;
    }

    string linea;
    int contador = 0;
    Libro libro;

    while (getline(archivo, linea))
    {
        if ((contador % 7 == 0 || contador % 7 == 4 || contador % 7 == 6) && !esNumero(linea))
        {
            cerr << "Error: se esperaba un número en la línea " << contador + 1 << ", pero se encontró '" << linea << "'.\n";
            return;
        }
        if (contador % 7 == 1)
        {
            libro.nombre = linea;
            if (nombres.find(libro.nombre) != nombres.end())
            {
                cerr << "El nombre '" << libro.nombre << "' está duplicado en el archivo.\n";
                cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 'S' || respuesta == 's')
                {
                    cout << "Ingresa la cantidad que deseas añadir: ";
                    int cantidad;
                    cin >> cantidad;
                    libro.cantidad = cantidad;
                    libros.push_back(libro); // Se agrega fuera del bucle
                    actualizarArchivoLibros(libros, filename);
                    cout << "Cantidad actualizada exitosamente.\n";
                    return;
                }
                else
                {
                    cout << "No se agregó ningún libro.\n";
                    return;
                }
            }
            nombres.insert(libro.nombre);
        }
        else if (contador % 7 == 0)
        {
            libro.codigo = stoi(linea);
            if (codigos.find(libro.codigo) != codigos.end())
            {
                cerr << "El código " << libro.codigo << " está duplicado en el archivo.\n";
                contador = 0;
                continue;
            }
            codigos.insert(libro.codigo);
        }
        else if (contador % 7 == 2)
        {
            libro.genero = linea;
        }
        else if (contador % 7 == 3)
        {
            libro.autor = linea;
        }
        else if (contador % 7 == 4)
        {
            libro.anoPublicacion = stoi(linea);
        }
        else if (contador % 7 == 5)
        {
            libro.sinopsis = linea;
        }
        else if (contador % 7 == 6)
        {
            libro.cantidad = stoi(linea);
            libros.push_back(libro); // Se agrega el libro después de que todos sus campos hayan sido leídos y asignados
        }
        contador++;
    }

    archivo.close();
}

void donarLibro(string &usuarioIngresado) {
    string nombreArchivo = "libros.txt";
    string archivoDonativos = "libros(donativo).txt";
    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string nombreLibro;
    cout << "Ingrese el nombre del libro: ";
    getline(cin, nombreLibro);

    // Buscar coincidencias del nombre del libro
    vector<Libro> coincidencias = buscarCoincidencias_ti(libros, nombreLibro);

    if (!coincidencias.empty()) {
        cout << "El libro ya existe en la biblioteca.\n";
        char respuesta;
        cout << "¿Desea añadir más existencias del libro en donaciones? (S/N): ";
        cin >> respuesta;
        cin.ignore(); // Limpiar el buffer

        if (respuesta == 'S' || respuesta == 's') {
            cout << "Ingrese la cantidad de existencias adicionales para la donación: ";
            int cantidadAdicional;
            cin >> cantidadAdicional;
            cin.ignore(); // Limpiar el buffer

            // Tomar el primer libro encontrado para usar sus detalles existentes
            const Libro &libroExistente = coincidencias[0];

            // Guardar el libro en libro(donativo).txt junto con el nombre del usuario
            ofstream archivo(archivoDonativos.c_str(), ios::app);
            if (archivo.is_open()) {
                archivo << usuarioIngresado << endl;
                archivo << libroExistente.codigo << endl;
                archivo << libroExistente.nombre << endl;
                archivo << libroExistente.genero << endl;
                archivo << libroExistente.autor << endl;
                archivo << libroExistente.anoPublicacion << endl;
                archivo << libroExistente.sinopsis << endl;
                archivo << cantidadAdicional << endl;
                archivo.close();
                cout << "El libro ha sido donado y registrado en el archivo de donativos." << endl;
                Sleep(2000);
            } else {
                cerr << "No se pudo abrir el archivo " << archivoDonativos << endl;
                Sleep(2000);
            }
        } else {
            cout << "No se han añadido existencias adicionales en donaciones." << endl;
            Sleep(2000);
        }
    } else {
        // Si no hay coincidencias, el libro no existe en la biblioteca
        cout << "El libro no existe en la biblioteca. Por favor, ingrese los datos del libro para donarlo." << endl;

        // Solicitar todos los demás datos del libro para agregarlo
        Libro nuevoLibro;
        nuevoLibro.nombre = nombreLibro;
        
        bool codigoRepetido = true;
        string codigoLibro;

        while (codigoRepetido) {
            cout << "Ingrese el código del libro: ";
            cin >> codigoLibro;
            cin.ignore(); // Limpiar el buffer

            // Verificar si el código ya existe en libros.txt
             if (buscarcoincidencia_cod(codigoLibro)) {
                 cout << "El código ingresado ya existe. Por favor, ingrese otro código." << endl;
            } else {
                codigoRepetido = false; // Salir del bucle, código válido
            }
        }
        
        cout << "Ingrese el género del libro: ";
        getline(cin, nuevoLibro.genero);
        
        cout << "Ingrese el autor del libro: ";
        getline(cin, nuevoLibro.autor);
        
        cout << "Ingrese el año de publicación del libro: ";
        cin >> nuevoLibro.anoPublicacion;
        cin.ignore(); // Limpiar el buffer
        
        cout << "Ingrese la sinopsis del libro: ";
        getline(cin, nuevoLibro.sinopsis);
        
        cout << "Ingrese la cantidad de existencias para la donación: ";
        cin >> nuevoLibro.cantidad;
        cin.ignore(); // Limpiar el buffer

        // Guardar el nuevo libro en libros(donativo).txt junto con el nombre del usuario
        ofstream archivo(archivoDonativos.c_str(), ios::app);
        if (archivo.is_open()) {
            archivo << usuarioIngresado << endl;
            archivo << nuevoLibro.codigo << endl;
            archivo << nuevoLibro.nombre << endl;
            archivo << nuevoLibro.genero << endl;
            archivo << nuevoLibro.autor << endl;
            archivo << nuevoLibro.anoPublicacion << endl;
            archivo << nuevoLibro.sinopsis << endl;
            archivo << nuevoLibro.cantidad << endl;
            archivo.close();
            cout << "El libro ha sido donado y registrado en el archivo de donativos." << endl;
            Sleep(2000);
        } else {
            cerr << "No se pudo abrir el archivo " << archivoDonativos << endl;
            Sleep(2000);
        }
    }
}

#endif // SISTLIBROUSUARIO_HPP