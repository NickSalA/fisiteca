#ifndef SISTLIBROADMIN_HPP
#define SISTLIBROADMIN_HPP
#include "../menu/funciones.hpp"

using namespace std;

void agregarLibro(Libro libros[], int &n)
{
    limpiarPantalla();
    ofstream Grabacion("libros.txt", ios::app);
    dibujarTitulo(50, 2, "AGREGAR LIBRO");
    dibujarCuadro(10, 5, 100, 20);
    dibujarTexto(20, 7, "Ingrese los datos del libro:");
    Libro newLibro;
    dibujarTexto(20, 9, "Codigo: ");
    cin >> newLibro.codigo;
    fflush(stdin);
    cin.ignore();
    dibujarTexto(20, 11, "Nombre: ");
    getline(cin, newLibro.nombre);
    dibujarTexto(20, 13, "Genero: ");
    getline(cin, newLibro.genero);
    dibujarTexto(20, 15, "Autor: ");
    getline(cin, newLibro.autor);
    dibujarTexto(20, 17, "Año de publicacion: ");
    cin >> newLibro.anoPublicacion;
    fflush(stdin);
    cin.ignore();

    dibujarTexto(20, 19, "Sinopsis: ");
    getline(cin, newLibro.sinopsis);
    dibujarTexto(20, 21, "Cantidad: ");
    cin >> newLibro.cantidad;
    fflush(stdin);
    cin.ignore();

    libros[n] = newLibro;
    n++;
    if (Grabacion.fail())
    {
        cout << "Error en el archivo..." << endl;
        Sleep(2000);
    }
    else
    {
        Grabacion << newLibro.codigo << endl;
        Grabacion << newLibro.nombre << endl;
        Grabacion << newLibro.genero << endl;
        Grabacion << newLibro.autor << endl;
        Grabacion << newLibro.anoPublicacion << endl;
        Grabacion << newLibro.sinopsis << endl;
        Grabacion << newLibro.cantidad << endl; // Guardamos la cantidad aquí
        Grabacion.close();
    }
    dibujarTexto(20, 23, "Libro agregado exitosamente.");
}

void eliminarLibro(Libro libros[], int &n)
{
    int numLibro;

    for (int i = 0; i < n; i++)
    {
        cout << "\nLibro " << i + 1 << ": " << libros[i].nombre << " - Cantidad: " << libros[i].cantidad << endl;
    }

    cout << "Seleccione el número del libro que desea eliminar: ";
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (numLibro >= 1 && numLibro <= n)
    {
        int indiceLibro = numLibro - 1;
        cout << "\nLibro: " << libros[indiceLibro].nombre << " - Cantidad: " << libros[indiceLibro].cantidad << endl;
        cout << "Genero: " << libros[indiceLibro].genero << endl;
        cout << "Autor: " << libros[indiceLibro].autor << endl;
        cout << "Año de publicacion: " << libros[indiceLibro].anoPublicacion << endl;

        char confirmacion;
        cout << "¿Está seguro de que desea eliminar este libro? (S/N): ";
        cin >> confirmacion;
        confirmacion = toupper(confirmacion);

        if (confirmacion == 'S')
        {
            // Elimina el libro del arreglo
            for (int i = indiceLibro; i < n - 1; ++i)
            {
                libros[i] = libros[i + 1];
            }
            --n;

            // Lee todos los libros del archivo
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
                // Lee el resto de los datos del libro
                getline(Leer >> ws, libroTemp.nombre);
                getline(Leer, libroTemp.genero);
                getline(Leer, libroTemp.autor);
                Leer >> libroTemp.anoPublicacion;
                getline(Leer >> ws, libroTemp.sinopsis);
                Leer >> libroTemp.cantidad;

                librosActualizados.push_back(libroTemp);
            }
            Leer.close();

            // Escribe todos los libros actualizados en el archivo
            ofstream Escribir("libros.txt");
            if (!Escribir.is_open())
            {
                cerr << "Error al abrir el archivo para escribir..." << endl;
                return;
            }
            for (int i = 0; i < n; ++i)
            {
                Escribir << libros[i].codigo << endl
                         << libros[i].nombre << endl
                         << libros[i].genero << endl
                         << libros[i].autor << endl
                         << libros[i].anoPublicacion << endl
                         << libros[i].sinopsis << endl
                         << libros[i].cantidad << endl;
            }
            Escribir.close();

            cout << "Libro eliminado exitosamente." << endl;
        }
        else
        {
            cout << "Operación cancelada. El libro no ha sido eliminado." << endl;
        }
    }
    else
    {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}

void editarLibro(Libro libros[], int n)
{

    system("cls");

    dibujarCuadro(10, 0, 100, 30);
    dibujarTitulo(50, 2, "Editar libro");
    int numLibro;

    for (int i = 0; i < n; i++)
    {
        dibujarTexto(20, 5 + i * 1, "Libro " + to_string(i + 1) + ": " + libros[i].nombre + " - Cantidad: " + to_string(libros[i].cantidad));
    }

    dibujarTeslaASCII(90, 15);

    dibujarTexto(20, 6 + n * 1, "Seleccione el número del libro que desea editar: ");
    cin >> numLibro;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    system("cls");

    if (numLibro >= 1 && numLibro <= n)
    {
        int indiceLibro = numLibro - 1;
        dibujarCuadro(10, 0, 100, 20);
        dibujarTexto(20, 2, "Editar libro: " + libros[indiceLibro].nombre);
        dibujarTexto(20, 4, "1. Nombre: " + libros[indiceLibro].nombre);
        dibujarTexto(20, 6, "2. Genero: " + libros[indiceLibro].genero);
        dibujarTexto(20, 8, "3. Autor: " + libros[indiceLibro].autor);
        dibujarTexto(20, 10, "4. Año de publicación: " + to_string(libros[indiceLibro].anoPublicacion));
        dibujarTexto(20, 12, "5. Sinopsis: " + libros[indiceLibro].sinopsis);
        dibujarTexto(20, 14, "6. Cantidad: " + to_string(libros[indiceLibro].cantidad)); 
        int opcion;
        dibujarTexto(20, 16, "Seleccione el número del campo que desea editar (1-6): ");
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");
        system("cls");

        dibujarCuadro(10, 0, 100, 20);
        dibujarTitulo(50, 2, "Editor de libros");
        dibujarTeslaASCII(90, 15);
        switch (opcion)
        {
        case 1:
            dibujarTexto(20, 10, "Ingrese el nuevo nombre del libro: ");
            getline(cin, libros[indiceLibro].nombre);
            break;
        case 2:
            dibujarTexto(20, 10, "Ingrese el nuevo género del libro: ");
            getline(cin, libros[indiceLibro].genero);
            break;
        case 3:
            dibujarTexto(20, 10, "Ingrese el nuevo autor del libro: ");
            getline(cin, libros[indiceLibro].autor);
            break;
        case 4:
            dibujarTexto(20, 10, "Ingrese el nuevo año de publicación del libro: ");
            cin >> libros[indiceLibro].anoPublicacion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 5:
            dibujarTexto(20, 10, "Ingrese la nueva sinopsis del libro: ");
            getline(cin, libros[indiceLibro].sinopsis);
            break;
        case 6:
            dibujarTexto(20, 10, "Ingrese la nueva cantidad del libro: ");
            cin >> libros[indiceLibro].cantidad;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        default:
            dibujarTexto(20, 10, "Opción no válida.");
            break;
        }

        ofstream Grabacion("libros.txt");
        for (int i = 0; i < n; ++i)
        {
            Grabacion << libros[i].codigo << endl;
            Grabacion << libros[i].nombre << endl;
            Grabacion << libros[i].genero << endl;
            Grabacion << libros[i].autor << endl;
            Grabacion << libros[i].anoPublicacion << endl;
            Grabacion << libros[i].sinopsis << endl;
            Grabacion << libros[i].cantidad << endl; 
        }
        Grabacion.close();

        cout << "Información del libro editada exitosamente." << endl;
    }
    else
    {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}

void aceptarLibroDonado(Libro libros[], int &n)
{
    int nDonativos = 0;
    Libro librosDonativos[100];
    leerLibro(librosDonativos, "libros(donativo).txt", nDonativos);

    if (nDonativos == 0)
    {
        cout << "No hay libros donados para aceptar." << endl;
        Sleep(1000);
        return;
    }

    limpiarPantalla();
    cout << "Seleccione el libro que desea aceptar:" << endl;
    for (int i = 0; i < nDonativos; i++)
    {
        cout << "\nLibro " << i + 1 << endl;
        cout << "Codigo: " << librosDonativos[i].codigo << endl;
        cout << "Nombre: " << librosDonativos[i].nombre << endl;
        cout << "Genero: " << librosDonativos[i].genero << endl;
        cout << "Autor: " << librosDonativos[i].autor << endl;
        cout << "Año de publicacion: " << librosDonativos[i].anoPublicacion << endl;
        cout << "Sinopsis: " << librosDonativos[i].sinopsis << endl;
        cout << "Cantidad: " << librosDonativos[i].cantidad << endl;
    }

    int seleccion;
    cout << "Ingrese el número del libro que desea aceptar: ";
    cin >> seleccion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seleccion >= 1 && seleccion <= nDonativos)
    {
        int indice = seleccion - 1;

        libros[n] = librosDonativos[indice];
        n++;

        ofstream Grabacion("libros.txt", ios::app);
        if (!Grabacion.is_open())
        {
            cerr << "Error al abrir el archivo para escribir..." << endl;
            return;
        }
        Grabacion << librosDonativos[indice].codigo << endl
                  << librosDonativos[indice].nombre << endl
                  << librosDonativos[indice].genero << endl
                  << librosDonativos[indice].autor << endl
                  << librosDonativos[indice].anoPublicacion << endl
                  << librosDonativos[indice].sinopsis << endl
                  << librosDonativos[indice].cantidad << endl;
        Grabacion.close();

        cout << "Libro aceptado exitosamente." << endl;

        for (int i = indice; i < nDonativos - 1; ++i)
        {
            librosDonativos[i] = librosDonativos[i + 1];
        }
        --nDonativos;

        ofstream GrabacionDonativo("libros(donativo).txt");
        if (!GrabacionDonativo.is_open())
        {
            cerr << "No se pudo abrir el archivo libros(donativo).txt para escritura." << endl;
            return;
        }
        for (int i = 0; i < nDonativos; ++i)
        {
            GrabacionDonativo << librosDonativos[i].codigo << endl
                              << librosDonativos[i].nombre << endl
                              << librosDonativos[i].genero << endl
                              << librosDonativos[i].autor << endl
                              << librosDonativos[i].anoPublicacion << endl
                              << librosDonativos[i].sinopsis << endl
                              << librosDonativos[i].cantidad << endl;
        }
        GrabacionDonativo.close();
    }
    else
    {
        cout << "Número de libro no válido. Por favor, seleccione un número de libro válido." << endl;
    }
}

void mostrarMenu(vector<string> &usuarios)
{
    for (size_t i = 0; i < usuarios.size(); ++i)
    {
        cout << i + 1 << ". " << usuarios[i] << "\n";
    }

    int opcion;
    cout << "\nDesee el numero de orden del usuario que desea saber su estado de prestamos de libros: ";
    cin >> opcion;
    cout << endl;

    if (opcion > 0 && opcion <= usuarios.size())
    {
        mostrarPrestamosUsuario(usuarios[opcion - 1]);
    }
    else
    {
        cout << "Opción inválida.\n";
    }

    cout << "0. Regresar\n1. Salir\n\nElija una opción: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 0)
    {
        limpiarPantalla();
        mostrarMenu(usuarios);
    }
    else if (opcion != 1)
    {
        cout << "Opción inválida.\n";
    }
}

void estadoUsuario()
{

    configurarConsolaUtf8();

    vector<string> usuarios;
    ifstream archivo("credUsuario.txt");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo credUsuario.txt\n";
    }

    string linea;
    int contador = 0;
    while (getline(archivo, linea))
    {
        // Solo guarda las líneas impares (nombres de usuario)
        if (contador % 2 == 0)
        {
            usuarios.push_back(linea);
        }
        contador++;
    }

    archivo.close();

    mostrarMenu(usuarios);
}

#endif // SISTLIBROADMIN_HPP