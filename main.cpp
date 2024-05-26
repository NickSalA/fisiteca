void InicioSesion(){
    string usuario, contrasena;
    cout << "Ingrese su usuario: ";
    cin >> usuario;
    cout << "Ingrese su contraseña: ";
    cin >> contrasena;
    if (usuario == "admin" && contrasena == "admin") {
        cout << "Bienvenido administrador" << endl;
        menuAdmin();
    } else {
        cout << "Bienvenido usuario" << endl;
        menuUsuario();
    }
}

void menuUsuario() {
    while (true) {
        system("cls"); 
        cout << "Menu de Opciones" << endl;
        cout << "1. Buscador de libros" << endl;
        cout << "2. Donacion de libros" << endl;
        cout << "3. Prestamo de libros" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Has seleccionado la Opción 1" << endl;
                system("pause");
                break;
            case 2:
                cout << "Has seleccionado la Opción 2" << endl;
                system("pause");
                break;
            case 3:
                cout << "Has seleccionado la Opción 3" << endl;
                system("pause");
                break;
            case 4:
                cout << "Saliendo..." << endl;
                return;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                system("pause");
                break;
        }
    }
}

void menuAdmin() {
    SetConsoleOutputCP(CP_UTF8);
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    int opcion;
    do {
        cout << "\n1. Agregar libro\n2. Eliminar libro\n3. Editar Libro\n4. Salir" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarLibro(libros, n);
                break;
            case 2:
                eliminarLibro(libros, n);
                break;
            case 3:
                editarLibro(libros, n);
                break;
            case 4:
                cout << "Adios!" << endl;
                return;
            default:
                cout << "Opcion invalida" << endl;
                system("pause");
                break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
        system("cls");
    } while (opcion != 4);
}
