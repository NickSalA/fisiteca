#ifndef SISTLIBROUSUARIO_HPP
#define SISTLIBROUSUARIO_HPP
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

void mainBuscador_ti()
{
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");
        dibujarCuadro(5, 2, 110, 25);
        dibujarTexto(100, 25, "0. Regresar");
        dibujarTeslaASCII(106, 3);
        dibujarTexto(30, 5, "Ingrese el título a buscar: ");
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        if (busqueda == to_string(0))
        {
            dibujarTexto(40, 10, "Regresando....");
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            dibujarTexto(10, 10, "No se encontraron coincidencias para el término de búsqueda: " + busqueda);
        }
        else
        {
            dibujarTexto(10, 10, "Coincidencias encontradas:");
            for (const Libro &libro : coincidencias)
            {
                dibujarTexto(10, 12, "Código: " + to_string(libro.codigo));
                dibujarTexto(10, 13, "Nombre: " + libro.nombre);
                dibujarTexto(10, 14, "Género: " + libro.genero);
                dibujarTexto(10, 15, "Autor: " + libro.autor);
                dibujarTexto(10, 16, "Año de Publicación: " + to_string(libro.anoPublicacion));
                dibujarTexto(10, 17, "Sinopsis: " + libro.sinopsis);
                dibujarTexto(10, 19, "Cantidad: " + to_string(libro.cantidad));
            }
        
        dibujarTexto(10, 25, "Presione una tecla para volver a buscar...");}
        esperaConMensaje("");
    } while (true);
}

bool buscarcoincidencia_cod(const std::string &codigo)
{
    std::ifstream archivo("libros.txt");
    std::string linea;

    // Verificar si se pudo abrir el archivo
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo libros.txt" << std::endl;
        return false; // No se pudo abrir el archivo
    }

    // Recorrer cada línea del archivo
    while (std::getline(archivo, linea))
    {
        // Si la línea contiene el código buscado, retornar true
        if (linea == codigo)
        {
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

        dibujarCuadro(5, 2, 110, 25);
        dibujarTexto(100, 25, "0. Regresar");
        dibujarTeslaASCII(106, 3);
        dibujarTexto(30, 5, "Ingrese el genero a buscar: ");
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

        if (busqueda == to_string(0))
        {

            dibujarTexto(40, 10, "Regresando....");
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            dibujarTexto(10, 10, "No se encontraron coincidencias para el término de búsqueda: " + busqueda);
        }
        else
        {
            dibujarTexto(10, 10, "Coincidencias encontradas:");
            for (const Libro &libro : coincidencias)
            {
                dibujarTexto(10, 12, "Código: " + to_string(libro.codigo));
                dibujarTexto(10, 13, "Nombre: " + libro.nombre);
                dibujarTexto(10, 14, "Género: " + libro.genero);
                dibujarTexto(10, 15, "Autor: " + libro.autor);
                dibujarTexto(10, 16, "Año de Publicación: " + to_string(libro.anoPublicacion));
                dibujarTexto(10, 17, "Sinopsis: " + libro.sinopsis);
                dibujarTexto(10, 19, "Cantidad: " + to_string(libro.cantidad));
            }
        
        dibujarTexto(10, 25, "Presione una tecla para volver a buscar...");}
        esperaConMensaje("");    
    } while (true);
}

void mainBuscar_autor()
{

    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");
        dibujarCuadro(5, 2, 110, 25);
        dibujarTexto(100, 25, "0. Regresar");
        dibujarTeslaASCII(106, 3);
        dibujarTexto(30, 5, "Ingrese el autor a buscar: ");
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

        if (busqueda == to_string(0))
        {

            dibujarTexto(40, 10, "Regresando....");
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            dibujarTexto(10, 10, "No se encontraron coincidencias para el término de búsqueda: " + busqueda);
        }
        else
        {
            dibujarTexto(10, 10, "Coincidencias encontradas:");
            for (const Libro &libro : coincidencias)
            {
                dibujarTexto(10, 12, "Código: " + to_string(libro.codigo));
                dibujarTexto(10, 13, "Nombre: " + libro.nombre);
                dibujarTexto(10, 14, "Género: " + libro.genero);
                dibujarTexto(10, 15, "Autor: " + libro.autor);
                dibujarTexto(10, 16, "Año de Publicación: " + to_string(libro.anoPublicacion));
                dibujarTexto(10, 17, "Sinopsis: " + libro.sinopsis);
                dibujarTexto(10, 19, "Cantidad: " + to_string(libro.cantidad));
            }
        dibujarTexto(10, 25, "Presione una tecla para volver a buscar...");}
        esperaConMensaje("");
    } while (true);
}

void mainBuscar_anio()
{

    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do
    {
        system("cls");
        dibujarCuadro(5, 2, 110, 25);
        dibujarTexto(100, 25, "0. Regresar");
        dibujarTeslaASCII(106, 3);
        dibujarTexto(30, 5, "Ingrese el título a buscar: ");
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

        if (busqueda == to_string(0))
        {

            dibujarTexto(40, 10, "Regresando....");
            Sleep(2000);
            break;
        }

        if (coincidencias.empty())
        {
            dibujarTexto(10, 10, "No se encontraron coincidencias para el término de búsqueda: " + busqueda);
        }
        else
        {
            dibujarTexto(10, 10, "Coincidencias encontradas:");
            for (const Libro &libro : coincidencias)
            {
                dibujarTexto(10, 12, "Código: " + to_string(libro.codigo));
                dibujarTexto(10, 13, "Nombre: " + libro.nombre);
                dibujarTexto(10, 14, "Género: " + libro.genero);
                dibujarTexto(10, 15, "Autor: " + libro.autor);
                dibujarTexto(10, 16, "Año de Publicación: " + to_string(libro.anoPublicacion));
                dibujarTexto(10, 17, "Sinopsis: " + libro.sinopsis);
                dibujarTexto(10, 19, "Cantidad: " + to_string(libro.cantidad));
            }
        dibujarTexto(10, 25, "Presione una tecla para volver a buscar...");}
        esperaConMensaje("");
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
    dibujarCuadro(pos.x - 10, 2, 60, 25);
    dibujarMenu(pos.x + 3, pos.y - 2, opciones);
    bool repite = true;

    while (repite)
    {
        if (lastopcionSeleccionada != opcionSeleccionada)
        {
            if (lastopcionSeleccionada != -1)
            {
                moverCursor({pos.x - 2, pos.y - 2 + lastopcionSeleccionada * 3});
                cout << "  ";
                moverCursor({pos.x + 41, pos.y - 2 + lastopcionSeleccionada * 3});
                cout << "  ";
            }

            moverCursor({pos.x - 2, pos.y - 2 + opcionSeleccionada * 3});
            cout << "=>";
            moverCursor({pos.x + 41, pos.y - 2 + opcionSeleccionada * 3});
            cout << "<=";

            lastopcionSeleccionada = opcionSeleccionada;
        }

        char key = _getch();
        if (key == 72 && opcionSeleccionada > 0)
        {
            opcionSeleccionada--;
        }
        else if (key == 80 && opcionSeleccionada < static_cast<int>(opciones.size() - 1))
        {
            opcionSeleccionada++;
        }
        else if (key == '\r')
        {
            limpiarPantalla();
            switch (opcionSeleccionada)
            {
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
            dibujarCuadro(pos.x - 10, 2, 60, 25);
            dibujarMenu(pos.x + 3, pos.y - 2, opciones);
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

void mostrarLibros(const Libro libros[], int n, int seleccion)
{
    for (int i = 0; i < n; ++i)
    {
        cout << (i == seleccion ? "> " : "  ") << libros[i].nombre << endl;
    }
}

void pedirPrestado(Libro libros[], int seleccion, const string &usuarioIngresado)
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

void prestarLibro(string &usuarioIngresado)
{
    const int MAX_LIBROS = 100;

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
                pedirPrestado(libros, seleccion, usuarioIngresado);
            }
        }
        else if (tecla == 27)
        { // Escape
            break;
        }
    }
}

void donarLibro(string &usuarioIngresado)
{
    string nombreArchivo = "libros.txt";
    string archivoDonativos = "libros(donativo).txt";
    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string nombreLibro;
    cout << "Ingrese el nombre del libro: ";
    getline(cin, nombreLibro);

    // Buscar coincidencias del nombre del libro
    vector<Libro> coincidencias = buscarCoincidencias_ti(libros, nombreLibro);

    if (!coincidencias.empty())
    {
        cout << "El libro ya existe en la biblioteca.\n";
        char respuesta;
        cout << "¿Desea añadir más existencias del libro en donaciones? (S/N): ";
        cin >> respuesta;
        cin.ignore(); // Limpiar el buffer

        if (respuesta == 'S' || respuesta == 's')
        {
            cout << "Ingrese la cantidad de existencias adicionales para la donación: ";
            int cantidadAdicional;
            cin >> cantidadAdicional;
            cin.ignore(); // Limpiar el buffer

            // Tomar el primer libro encontrado para usar sus detalles existentes
            const Libro &libroExistente = coincidencias[0];

            // Guardar el libro en libro(donativo).txt junto con el nombre del usuario
            ofstream archivo(archivoDonativos.c_str(), ios::app);
            if (archivo.is_open())
            {
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
            }
            else
            {
                cerr << "No se pudo abrir el archivo " << archivoDonativos << endl;
                Sleep(2000);
            }
        }
        else
        {
            cout << "No se han añadido existencias adicionales en donaciones." << endl;
            Sleep(2000);
        }
    }
    else
    {
        // Si no hay coincidencias, el libro no existe en la biblioteca
        cout << "El libro no existe en la biblioteca. Por favor, ingrese los datos del libro para donarlo." << endl;

        // Solicitar todos los demás datos del libro para agregarlo
        Libro nuevoLibro;
        nuevoLibro.nombre = nombreLibro;

        bool codigoRepetido = true;
        string codigoLibro;

        while (codigoRepetido)
        {
            cout << "Ingrese el código del libro: ";
            cin >> codigoLibro;
            istringstream(codigoLibro) >> nuevoLibro.codigo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Verificar si el código ya existe en libros.txt
            if (buscarcoincidencia_cod(codigoLibro))
            {
                cout << "El código ingresado ya existe. Por favor, ingrese otro código." << endl;
            }
            else
            {
                codigoRepetido = false; // Salir del bucle, código válido
            }
        }

        cout << "Ingrese el género del libro: ";
        getline(cin, nuevoLibro.genero);

        cout << "Ingrese el autor del libro: ";
        getline(cin, nuevoLibro.autor);

        cout << "Ingrese el año de publicación del libro: ";
        cin >> nuevoLibro.anoPublicacion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ingrese la sinopsis del libro: ";
        getline(cin, nuevoLibro.sinopsis);

        cout << "Ingrese la cantidad de existencias para la donación: ";
        cin >> nuevoLibro.cantidad;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Guardar el nuevo libro en libros(donativo).txt junto con el nombre del usuario
        ofstream archivo(archivoDonativos.c_str(), ios::app);
        if (archivo.is_open())
        {
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
        }
        else
        {
            cerr << "No se pudo abrir el archivo " << archivoDonativos << endl;
            Sleep(2000);
        }
    }
}

#endif // SISTLIBROUSUARIO_HPP