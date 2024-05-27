#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <limits>
#include "sistLibro(Admin).hpp"

bool usuarioExiste(const std::string& usuario) {
    std::ifstream archivo("credUsuario.txt");
    std::string usuarioGuardado;
    while (archivo >> usuarioGuardado) {
        if (usuarioGuardado == usuario) {
            archivo.close();
            return true;
        }
        archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    archivo.close();
    return false;
}

bool verificarCredencialesUsuario(const std::string& usuario, const std::string& contraseña) {
    std::ifstream archivo("credUsuario.txt");
    if (archivo.fail()) {
        std::cout << "Error: No se pudo abrir el archivo 'credUsuario.txt'." << std::endl;
        return false;
    }

    std::string usuarioGuardado, contraseñaGuardada;
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool verificarCredencialesAdmin(const std::string& usuario, const std::string& contraseña) {
    std::ifstream archivo("credAdmin.txt");
    if (archivo.fail()) {
        std::cout << "Error: No se pudo abrir el archivo 'credAdmin.txt'." << std::endl;
        return false;
    }

    std::string usuarioGuardado, contraseñaGuardada;
    while (archivo >> usuarioGuardado >> contraseñaGuardada) {
        if (usuarioGuardado == usuario && contraseñaGuardada == contraseña) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void registrarUsuario() {
    std::string usuario, contrasena, confirmar_contrasena;
    bool registrado = false;

    while (!registrado) {
        std::cout << "Introduce tu nombre de usuario: ";
        std::getline(std::cin, usuario);

        if (usuario.empty()) {
            std::cout << "\nEl nombre de usuario no puede estar vacío. Inténtalo de nuevo." << std::endl << std::endl;
            continue;
        }

        if (usuarioExiste(usuario)) {
            std::cout << "\nEl usuario ya existe. Introduce un nombre de usuario diferente." << std::endl << std::endl;
            continue;
        }

        std::cout << "Introduce tu contraseña: ";
        std::getline(std::cin, contrasena);

        if (contrasena.empty()) {
            std::cout << "\nLa contraseña no puede estar vacía. Inténtalo de nuevo." << std::endl << std::endl;
            continue;
        }

        std::cout << "Confirma tu contraseña: ";
        std::getline(std::cin, confirmar_contrasena);

        if (contrasena != confirmar_contrasena) {
            std::cout << "\nLas contraseñas no coinciden. Inténtalo de nuevo." << std::endl << std::endl;
            continue;
        }

        std::ofstream archivo("credUsuario.txt", std::ios::app);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir el archivo." << std::endl;
            return;
        }

        archivo << usuario << std::endl << contrasena << std::endl;
        archivo.close();

        registrado = true;
        std::cout << "\nRegistro exitoso. ¡Te has registrado correctamente!" << std::endl;
    }
}

void menuUsuario() {
    while (true) {
        std::cout << "Menu de Opciones" << std::endl;
        std::cout << "1. Buscador de libros" << std::endl;
        std::cout << "2. Donacion de libros" << std::endl;
        std::cout << "3. Prestamo de libros" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input

        switch (opcion) {
            case 1:
                std::cout << "Has seleccionado la Opción 1" << std::endl;
                break;
            case 2:
                std::cout << "Has seleccionado la Opción 2" << std::endl;
                break;
            case 3:
                std::cout << "Has seleccionado la Opción 3" << std::endl;
                break;
            case 4:
                std::cout << "Saliendo..." << std::endl;
                return;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                break;
        }
    }
}

void menuAdmin() {
    Libro libros[100];
    int n = 0;
    leerLibro(libros, n);
    int opcion;
    do {
        std::cout << "\n1. Agregar libro\n2. Eliminar libro\n3. Editar Libro\n4. Salir" << std::endl;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
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
                std::cout << "Adios!" << std::endl;
                return;
            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
    } while (opcion != 4);
}

void ingresarUsuario() {
    std::string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;

    do {
        std::cout << "Ingrese su nombre de usuario: ";
        std::getline(std::cin, usuarioIngresado);

        std::cout << "Ingrese su contraseña: ";
        std::getline(std::cin, contraseñaIngresada);

        if (verificarCredencialesUsuario(usuarioIngresado, contraseñaIngresada)) {
            credencialesCorrectas = true;
            std::cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente." << std::endl;
            menuUsuario();
        } else {
            std::cout << "\nError: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << std::endl;
        }
    } while (!credencialesCorrectas);
}

void ingresarComoAdmin() {
    std::string usuarioIngresado, contraseñaIngresada;
    bool credencialesCorrectas = false;

    do {
        std::cout << "Ingrese su nombre de usuario: ";
        std::getline(std::cin, usuarioIngresado);

        std::cout << "Ingrese su contraseña: ";
        std::getline(std::cin, contraseñaIngresada);

        if (verificarCredencialesAdmin(usuarioIngresado, contraseñaIngresada)) {
            credencialesCorrectas = true;
            std::cout << "\n¡Bienvenido, " << usuarioIngresado << "! Has ingresado correctamente como administrador." << std::endl;
            menuAdmin();
        } else {
            std::cout << "\nError: Nombre de usuario o contraseña incorrectos. Intente de nuevo." << std::endl << std::endl;
        }
    } while (!credencialesCorrectas);
}

#endif // USERMANAGEMENT_HPP
