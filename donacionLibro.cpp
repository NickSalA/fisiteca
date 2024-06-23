#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <string>
#include <limits>
#include <fstream>

#include "menu/funciones.hpp"

using namespace std;

void donarLibro()
{
    Libro libroos[100];
    int n = 0;
    char opcion;
    leerLibro(libroos, "libros.txt", n); // Leer los libros existentes
    cout << "¿Desea donar un libro existente o nuevo?(E/N): ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    if (toupper(opcion) == 'E')
    {
        int codigo, cantidad;
        cout << "Ingrese el codigo del libro que desea donar: ";
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout<< "Ingrese la cantidad de libros a donar: "; cin >> cantidad;
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (libroos[i].codigo == codigo)
            {
                libroos[i].cantidad+=cantidad;
                found = true;
                cout << "Donacion exitosa\n";
                break;
            }
        }
        if (found)
        {
            ofstream Grabacion("libros.txt");
            if (Grabacion.fail())
            {
                cout << "Error en el archivo..." << endl;
                Sleep(2000);
            }
            else
            {
                for (int i = 0; i < n; ++i)
                {
                    Grabacion << libroos[i].codigo << endl;
                    Grabacion << libroos[i].nombre << endl;
                    Grabacion << libroos[i].genero << endl;
                    Grabacion << libroos[i].autor << endl;
                    Grabacion << libroos[i].anoPublicacion << endl;
                    Grabacion << libroos[i].sinopsis << endl;
                    Grabacion << libroos[i].cantidad << endl; // Guardamos la cantidad aquí
                }
                Grabacion.close();
            }
        }
        else
        {
            cout << "Libro no encontrado\n";
        }
    }
    else if (toupper(opcion) == 'N')
    {
        ofstream archivo("libros(donativo).txt", ios::app);
        if (archivo.fail())
        {
            cout << "Error en el archivo..." << endl;
            Sleep(2000);
        }
        else
        {
            Libro newLibro;
            cout << "Ingrese los datos del libro a donar:" << endl;
            cout << "Codigo: ";
            cin >> newLibro.codigo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
            cout << "Titulo: ";
            getline(cin, newLibro.nombre);
            cout << "Genero: ";
            getline(cin, newLibro.genero);
            cout << "Año de publicacion: ";
            cin >> newLibro.anoPublicacion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
            cout << "Autor: ";
            getline(cin, newLibro.autor);
            cout << "Sinopsis: ";
            getline(cin, newLibro.sinopsis);
            cout << "Cantidad: ";
            cin >> newLibro.cantidad;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

            archivo << newLibro.codigo << endl;
            archivo << newLibro.nombre << endl;
            archivo << newLibro.genero << endl;
            archivo << newLibro.autor << endl;
            archivo << newLibro.anoPublicacion << endl;
            archivo << newLibro.sinopsis << endl;
            archivo << newLibro.cantidad << endl;

            archivo.close();
            cout << "Donacion exitosa\n";
        }
    }
    else
    {
        cout << "Opcion no valida\n";
    }
}
int main()
{
    donarrLibro();
    return 0;
}