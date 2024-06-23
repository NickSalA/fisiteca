void donacionLibro(vector<Libro> &libros, vector<Libro> &librosDonados, const string &filename)
{
    Libro libro;
    char respuesta;
    cout << "¿Desea donar un libro existente o uno nuevo? (E/N): ";
    cin >> respuesta;
    if (respuesta == 'E' || respuesta == 'e')
    {
        cout << "Ingresa el código del libro que quieres donar: ";
        cin >> libro.codigo;
        int i = buscarLibro(libros, libro.codigo);
        if (i != -1)
        {
            cout << "Ingresa la cantidad que deseas añadir: ";
            int cantidad;
            cin >> cantidad;
            libros[i].cantidad += cantidad;
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
    if (respuesta == 'N' || respuesta == 'n')
    {
        cout << "Ingresa el código del libro que quieres donar: ";
        cin >> libro.codigo;
        for (size_t i = 0; i < librosDonados.size(); i++)
        {
            if (librosDonados[i].codigo == libro.codigo)
            {
                cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 'S' || respuesta == 's')
                {
                    cout << "Ingresa la cantidad que deseas añadir: ";
                    int cantidad;
                    cin >> cantidad;
                    librosDonados[i].cantidad += cantidad;
                    actualizarArchivoLibros(librosDonados, "libros(donativo).txt");
                    cout << "Cantidad actualizada exitosamente.\n";
                    return;
                }
                else
                {
                    cout << "No se agregó ningún libro.\n";
                    return;
                }
            }
        }
        cout << "Ingresa el nombre del libro: ";
        cin.ignore();
        getline(cin, libro.nombre);

        for (size_t i = 0; i < librosDonados.size(); i++)
        {
            if (librosDonados[i].nombre == libro.nombre)
            {
                cout << "Este libro ya existe. ¿Deseas añadir más cantidad al libro existente? (S/N): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 'S' || respuesta == 's')
                {
                    cout << "Ingresa la cantidad que deseas añadir: ";
                    int cantidad;
                    cin >> cantidad;
                    librosDonados[i].cantidad += cantidad;
                    actualizarArchivoLibros(librosDonados, "libros(donativo).txt");
                    cout << "Cantidad actualizada exitosamente.\n";
                    return;
                }
                else
                {
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
        librosDonados.push_back(libro);                                 // Agrega el libro donado al vector de libros donados
        actualizarArchivoLibros(librosDonados, "libros(donativo).txt"); // Actualiza el archivo "libros(donativo).txt" con los libros donados
        cout << "Libro donado exitosamente.\n";
    }
    else
    {
        cerr << "Respuesta no válida.\n";
        return;
    }
}

void donarLibro()
{
    limpiarPantalla();
    vector<Libro> libros;
    vector<Libro> librosDonados; // Vector para almacenar los libros donados
    unordered_set<int> codigos;
    unordered_set<string> nombres;
    CargarLibros(libros, "libros.txt", codigos, nombres);
    donacionLibro(libros, librosDonados, "libros.txt");
}