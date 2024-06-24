#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>   // Para _getch()
#include <windows.h> // Para limpiar pantalla y mover el cursor
#include <sstream>
#include "menu/funciones.hpp"
#include "data/userManagement.hpp"

using namespace std;

const int MAX_LIBROS = 100;

void mostrarLibros(const Libro libros[], int n, int seleccion)
{
    for (int i = 0; i < n; ++i)
    {
        cout << (i == seleccion ? "> " : "  ") << libros[i].nombre << endl;
    }
}

void pedirPrestado(Libro libros[], int n, int seleccion, const string &usuarioIngresado)
{
    if (libros[seleccion].cantidad > 0)
    {
        libros[seleccion].cantidad--;

        // Leer todos los libros del archivo libros.txt en un vector de estructuras
        vector<Libro> librosActualizados;
        ifstream Leer("libros.txt");
        if (Leer.fail())
        {
            cerr << "Error al abrir el archivo para leer..." << endl;
            return;
        }
        Libro libroTemp;
        while (Leer >> libroTemp.codigo)
        {
            // Leer el resto de los datos del libro
            getline(Leer >> ws, libroTemp.nombre);
            getline(Leer, libroTemp.genero);
            getline(Leer, libroTemp.autor);
            Leer >> libroTemp.anoPublicacion;
            getline(Leer >> ws, libroTemp.sinopsis);
            Leer >> libroTemp.cantidad;

            // Si el código del libro coincide con el seleccionado, actualizar la cantidad
            if (libroTemp.codigo == libros[seleccion].codigo)
            {
                libroTemp.cantidad = libros[seleccion].cantidad;
            }

            librosActualizados.push_back(libroTemp);
        }
        Leer.close();

        // Escribir todos los libros actualizados en el archivo
        ofstream Escribir("libros.txt");
        if (!Escribir.is_open())
        {
            cerr << "Error al abrir el archivo para escribir..." << endl;
            return;
        }
        for (const auto &libro : librosActualizados)
        {
            Escribir << libro.codigo << endl
                     << libro.nombre << endl
                     << libro.genero << endl
                     << libro.autor << endl
                     << libro.anoPublicacion << endl
                     << libro.sinopsis << endl
                     << libro.cantidad << endl;
        }
        Escribir.close();

        // Registrar el préstamo en el archivo de pedidos
        ofstream EscribirPedido("libros(pedidos).txt", ios::app);
        if (!EscribirPedido.is_open())
        {
            cerr << "Error al abrir el archivo de pedidos..." << endl;
            return;
        }
        EscribirPedido << usuarioIngresado << endl
                       << libros[seleccion].codigo << endl
                       << libros[seleccion].nombre << endl;
        EscribirPedido.close();

        cout << "¡Has pedido prestado el libro: " << libros[seleccion].nombre << "!" << endl;
    }
    else
    {
        cout << "Lo siento, no hay copias disponibles de este libro." << endl;
    }
    system("pause");
}

int main()
{
    configurarConsolaUtf8();
    Libro libros[MAX_LIBROS];
    int n = 0;
    string archivoLibros = "libros.txt";
    leerLibro(libros, archivoLibros, n);

    int seleccion = 0;
    char tecla;

    while (true)
    {
        limpiarPantalla();
        mostrarLibros(libros, n, seleccion);

        tecla = _getch();
        if (tecla == 72 && seleccion > 0)
        { // Flecha arriba
            seleccion--;
        }
        else if (tecla == 80 && seleccion < n - 1)
        { // Flecha abajo
            seleccion++;
        }
        else if (tecla == 13)
        { // Enter
            limpiarPantalla();
            cout << "Detalles del libro seleccionado:" << endl;
            cout << "Código: " << libros[seleccion].codigo << endl
                 << "Nombre: " << libros[seleccion].nombre << endl
                 << "Género: " << libros[seleccion].genero << endl
                 << "Autor: " << libros[seleccion].autor << endl
                 << "Año de publicación: " << libros[seleccion].anoPublicacion << endl
                 << "Sinopsis: " << libros[seleccion].sinopsis << endl
                 << "Cantidad disponible: " << libros[seleccion].cantidad << endl;

            cout << "¿Estás seguro de que deseas pedir prestado este libro? (S/N): ";
            char confirmar;
            cin >> confirmar;
            if (confirmar == 'S' || confirmar == 's')
            {
                pedirPrestado(libros, n, seleccion, usuarioIngresado);
            }
        }
        else if (tecla == 27)
        { // Escape
            break;
        }
    }

    return 0;
}
