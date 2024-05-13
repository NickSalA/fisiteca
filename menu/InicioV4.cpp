#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// Declaración de variables globales
HWND hwnd, hwndLogin, hwndRegistro, hwndAdmin;
HWND hUsuario, hContraseña, hBotonIngresar, hBotonRegistrarse, hBotonAdmin, hNombre, hContraseñaReg, hConfirmarContraseña, hBotonRegistrar;

// Prototipos de funciones
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void createLoginWindow(HINSTANCE hInstance);
void createRegistroWindow(HINSTANCE hInstance);
void createAdminWindow(HINSTANCE hInstance);
bool verificarCredencialesUsuario(const string& usuario, const string& contraseña);
bool verificarCredencialesAdmin(const string& usuario, const string& contraseña);
void registrarUsuario(const string& usuario, const string& contraseña);

// Función principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Crear ventana de inicio de sesión
    createLoginWindow(hInstance);

    // Ciclo principal del programa
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND: {
            if ((HWND)lParam == hBotonIngresar) {
                char usuario[50], contraseña[50];
                GetWindowText(hUsuario, usuario, 50);
                GetWindowText(hContraseña, contraseña, 50);
                if (verificarCredencialesUsuario(usuario, contraseña)) {
                    MessageBox(hwnd, "Inicio de sesion exitoso", "Mensaje", MB_OK);
                } else if (verificarCredencialesAdmin(usuario, contraseña)) {
                    MessageBox(hwnd, "Inicio de sesion exitoso como administrador", "Mensaje", MB_OK);
                } else {
                    MessageBox(hwnd, "Ingrese un usuario y/o contrasena validos", "Error", MB_OK | MB_ICONERROR);
                }
            } else if ((HWND)lParam == hBotonRegistrarse) {
                createRegistroWindow(GetModuleHandle(NULL));
            } else if ((HWND)lParam == hBotonAdmin) {
                createAdminWindow(GetModuleHandle(NULL));
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
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 300,
        NULL, NULL, hInstance, NULL
    );

    // Crear controles
    CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 40, 35, 500, 90, hwndLogin, NULL, NULL, NULL);
    CreateWindow("STATIC", "Usuario:", WS_VISIBLE | WS_CHILD, 80, 50, 100, 20, hwndLogin, NULL, NULL, NULL);
    hUsuario = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 50, 300, 20, hwndLogin, NULL, NULL, NULL);
    CreateWindow("STATIC", "Contrasena:", WS_VISIBLE | WS_CHILD, 80, 90, 100, 20, hwndLogin, NULL, NULL, NULL);
    hContraseña = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 180, 90, 300, 20, hwndLogin, NULL, NULL, NULL);
    hBotonIngresar = CreateWindow("BUTTON", "Ingresar", WS_VISIBLE | WS_CHILD, 340, 150, 200, 25, hwndLogin, (HMENU)1, NULL, NULL);
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
    hBotonIngresar = CreateWindow("BUTTON", "Ingresar", WS_VISIBLE | WS_CHILD, 150, 90, 200, 25, hwndAdmin, (HMENU)1, NULL, NULL);

    ShowWindow(hwndAdmin, SW_SHOW);
    UpdateWindow(hwndAdmin);
}

// Función para verificar las credenciales de usuario
bool verificarCredencialesUsuario(const string& usuario, const string& contraseña) {
    ifstream file("credUsuario.txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credUsuario.txt" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == usuario) {
            if (getline(file, line) && line == contraseña) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

// Función para verificar las credenciales de administrador
bool verificarCredencialesAdmin(const string& usuario, const string& contraseña) {
    ifstream file("credAdmin.txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credAdmin.txt" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == usuario) {
            if (getline(file, line) && line == contraseña) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

// Función para registrar un nuevo usuario
void registrarUsuario(const string& usuario, const string& contraseña) {
    ofstream file("credUsuario.txt", ios_base::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo credUsuario.txt" << endl;
        return;
    }
    file << usuario << endl << contraseña << endl;
    file.close();
}