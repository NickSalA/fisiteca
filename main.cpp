#include <iostream>
#include <fstream>
#include <windows.h>
#include "menu/funcionesVerificar.h"
using namespace std;

// Prototipos de funciones
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void createLoginWindow(HINSTANCE hInstance);
void createRegistroWindow(HINSTANCE hInstance);
void createAdminWindow(HINSTANCE hInstance);
void menuUsuario();
void menuAdmin();

// Función principal
int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    createLoginWindow(hInstance);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
    cout<<"hola";
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND: {
            if ((HWND)lParam == hBotonIngresarUsuario) {
                char usuario[50], contraseña[50];
                GetWindowText(hUsuario, usuario, 50);
                GetWindowText(hContraseña, contraseña, 50);
                if (verificarCredencialesUsuario(usuario, contraseña)) {
                    MessageBox(hwnd, "Inicio de sesion exitoso", "Mensaje", MB_OK);
                    DestroyWindow(hwnd);
                    //Añadir aca las funciones (del CMD :D)
                    menuUsuario();
                } else {
                    MessageBox(hwnd, "Ingrese un usuario y/o contrasena validos", "Error", MB_OK | MB_ICONERROR);
                }
            } else if ((HWND)lParam == hBotonRegistrarse) {
                createRegistroWindow(GetModuleHandle(NULL));
            } else if ((HWND)lParam == hBotonAdmin) {
                createAdminWindow(GetModuleHandle(NULL));
            } else if ((HWND)lParam == hBotonIngresarAdmin) {
                char usuario[50], contraseña[50];
                GetWindowText(hUsuario, usuario, 50);
                GetWindowText(hContraseña, contraseña, 50);
                if (verificarCredencialesAdmin(usuario, contraseña)) {
                    MessageBox(hwnd, "Inicio de sesion exitoso como administrador", "Mensaje", MB_OK);
                    DestroyWindow(hwnd);
                    //Añadir aca las funciones (del CMD :D)
                    menuAdmin();
                } 
                else {
                    MessageBox(hwnd, "Ingrese un usuario y/o contrasena validos", "Error", MB_OK | MB_ICONERROR);
                }
            } else if ((HWND)lParam == hBotonRegistrar) {
                char nombre[50], contraseña[50], confirmar[50];
                GetWindowText(hNombre, nombre, 50);
                GetWindowText(hContraseñaReg, contraseña, 50);
                GetWindowText(hConfirmarContraseña, confirmar, 50);
                if (strcmp(contraseña, confirmar) == 0) {
                    registrarUsuario(nombre, contraseña);
                    MessageBox(hwnd, "Registro exitoso", "Mensaje", MB_OK);
                } else {
                    MessageBox(hwnd, "Las contrasenas no coinciden", "Error", MB_OK | MB_ICONERROR);
                }
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Función para crear la ventana de inicio de sesión
void createLoginWindow(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = "LoginWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    hwndLogin = CreateWindowEx(
        0,
        "LoginWindow",
        "Inicio de Sesion",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 550, 270,
        NULL, NULL, hInstance, NULL
    );

    // Crear controles
    CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 20, 20, 505, 110, hwndLogin, NULL, NULL, NULL);
    CreateWindow("STATIC", "Usuario:", WS_VISIBLE | WS_CHILD, 80, 50, 100, 20, hwndLogin, NULL, NULL, NULL);
    hUsuario = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 50, 300, 20, hwndLogin, NULL, NULL, NULL);
    CreateWindow("STATIC", "Contrasena:", WS_VISIBLE | WS_CHILD, 80, 90, 100, 20, hwndLogin, NULL, NULL, NULL);
    hContraseña = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 180, 90, 300, 20, hwndLogin, NULL, NULL, NULL);
    hBotonIngresarUsuario = CreateWindow("BUTTON", "Ingresar", WS_VISIBLE | WS_CHILD, 340, 150, 200, 25, hwndLogin, (HMENU)1, NULL, NULL);
    hBotonRegistrarse = CreateWindow("BUTTON", "Registrarse", WS_VISIBLE | WS_CHILD, 70, 210, 200, 25, hwndLogin, (HMENU)2, NULL, NULL);
    hBotonAdmin = CreateWindow("BUTTON", "Ingresar como administrador", WS_VISIBLE | WS_CHILD, 320, 210, 200, 25, hwndLogin, (HMENU)3, NULL, NULL);

    ShowWindow(hwndLogin, SW_SHOW);
    UpdateWindow(hwndLogin);
}

// Función para crear la ventana de registro
void createRegistroWindow(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = "RegistroWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    hwndRegistro = CreateWindowEx(
        0,
        "RegistroWindow",
        "Registro",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 220,
        NULL, NULL, hInstance, NULL
    );

    // Crear controles
    CreateWindow("STATIC", "Nombre de usuario:", WS_VISIBLE | WS_CHILD, 50, 30, 150, 20, hwndRegistro, NULL, NULL, NULL);
    hNombre = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 30, 150, 20, hwndRegistro, NULL, NULL, NULL);
    CreateWindow("STATIC", "Contrasena:", WS_VISIBLE | WS_CHILD, 50, 60, 150, 20, hwndRegistro, NULL, NULL, NULL);
    hContraseñaReg = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 200, 60, 150, 20, hwndRegistro, NULL, NULL, NULL);
    CreateWindow("STATIC", "Confirmar contrasena:", WS_VISIBLE | WS_CHILD, 50, 90, 150, 20, hwndRegistro, NULL, NULL, NULL);
    hConfirmarContraseña = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 200, 90, 150, 20, hwndRegistro, NULL, NULL, NULL);
    hBotonRegistrar = CreateWindow("BUTTON", "Registrarse", WS_VISIBLE | WS_CHILD, 150, 130, 200, 25, hwndRegistro, (HMENU)4, NULL, NULL);

    ShowWindow(hwndRegistro, SW_SHOW);
    UpdateWindow(hwndRegistro);
}

// Función para crear la ventana de administrador
void createAdminWindow(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = "AdminWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    hwndAdmin = CreateWindowEx(
        0,
        "AdminWindow",
        "Ingresar como Administrador",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
        NULL, NULL, hInstance, NULL
    );

    // Crear controles
    CreateWindow("STATIC", "Usuario:", WS_VISIBLE | WS_CHILD, 50, 33, 100, 20, hwndAdmin, NULL, NULL, NULL);
    hUsuario = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 30, 200, 20, hwndAdmin, NULL, NULL, NULL);
    CreateWindow("STATIC", "Contrasena:", WS_VISIBLE | WS_CHILD, 50, 63, 100, 20, hwndAdmin, NULL, NULL, NULL);
    hContraseña = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 60, 200, 20, hwndAdmin, NULL, NULL, NULL);
    hBotonIngresarAdmin = CreateWindow("BUTTON", "Ingresar", WS_VISIBLE | WS_CHILD, 150, 90, 200, 25, hwndAdmin, (HMENU)5, NULL, NULL);

    ShowWindow(hwndAdmin, SW_SHOW);
    UpdateWindow(hwndAdmin);
}

// Función para verificar las credenciales de usuario
void menuUsuario() {
    while (true) {
        system("cls"); // Limpiar la consola
        cout << "Menu de Opciones" << endl;
        cout << "1. Opción 1" << endl;
        cout << "2. Opción 2" << endl;
        cout << "3. Opción 3" << endl;
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
    while (true) {
        system("cls"); // Limpiar la consola
        cout << "Menu de Opciones" << endl;
        cout << "1. Opción 1" << endl;
        cout << "2. Opción 2" << endl;
        cout << "3. Opción 3" << endl;
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