#define UNICODE
#include <windows.h>
#include <string>
#include <fstream>

// Declaración de identificadores de control
#define IDC_USERNAME_EDIT 1001
#define IDC_PASSWORD_EDIT 1002
#define IDC_LOGIN_BUTTON 1003
#define IDC_REGISTER_BUTTON 1004
#define IDC_ADMIN_BUTTON 1005
#define IDC_ADMIN_REGISTER_BUTTON 1006
#define IDC_USERNAME_EDIT_ADMIN 1007
#define IDC_PASSWORD_EDIT_ADMIN 1008
#define IDC_CONFIRM_PASSWORD_EDIT_ADMIN 1009
#define IDC_STUDENT_CODE_EDIT_ADMIN 1010
#define IDC_LOGIN_BUTTON_ADMIN 1011
#define IDC_INVALID_LOGIN_DIALOG 1012
#define IDC_LIBROS_PRESTADOS_BUTTON 1013
#define IDC_LIBROS_DISPONIBLES_BUTTON 1014
#define IDC_PROXIMOS_LIBROS_BUTTON 1015
#define IDC_DONAR_LIBRO_BUTTON 1016

// Función de ventana principal
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Función para abrir la ventana de registro de administrador
void OpenAdminRegistrationWindow(HINSTANCE hInstance);

// Función para abrir la ventana de inicio de sesión de administrador
void OpenAdminLoginWindow(HINSTANCE hInstance);

// Función de ventana para la ventana de registro de administrador
LRESULT CALLBACK AdminRegistrationWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Función de ventana para la ventana de inicio de sesión de administrador
LRESULT CALLBACK AdminLoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Función para mostrar el cuadro de diálogo de inicio de sesión inválido
void ShowInvalidLoginDialog(HWND hwnd);

// Función para abrir la ventana del menú de usuario
// void OpenUserMenuWindow(HINSTANCE hInstance); // Eliminado

HWND g_hMainWindow;

// Función para verificar el usuario y la contraseña
bool VerifyCredentials(const std::wstring& username, const std::wstring& password) {
    // Código de verificación de credenciales...
}

// Función para escribir los datos de usuario en el archivo "credUsuario.txt"
void WriteUserCredentialsToFile(const std::wstring& username, const std::wstring& password) {
    // Código para escribir en el archivo "credUsuario.txt"...
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Registrar la clase de la ventana principal
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass";
    RegisterClassEx(&wc);

    // Crear la ventana principal
    HWND hwnd = CreateWindowEx(
        0,
        L"WindowClass",
        L"Inicio de Sesión",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 250,
        NULL,
        NULL,
        hInstance,
        NULL);

    // Guardar el handle de la ventana principal
    g_hMainWindow = hwnd;

    // Mostrar la ventana principal
    ShowWindow(hwnd, nCmdShow);

    // Bucle de mensajes
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Procedimiento de ventana para la ventana principal
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Crear controles
        CreateWindowW(L"Static", L"Usuario:", WS_VISIBLE | WS_CHILD, 20, 20, 120, 25, hwnd, NULL, NULL, NULL);
        HWND hwndUsernameEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 20, 300, 25, hwnd, (HMENU)IDC_USERNAME_EDIT, NULL, NULL);

        CreateWindowW(L"Static", L"Contraseña:", WS_VISIBLE | WS_CHILD, 20, 60, 120, 25, hwnd, NULL, NULL, NULL);
        HWND hwndPasswordEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 60, 300, 25, hwnd, (HMENU)IDC_PASSWORD_EDIT, NULL, NULL);

        CreateWindowW(L"Button", L"Ingresar", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 70, 100, 150, 30, hwnd, (HMENU)IDC_LOGIN_BUTTON, NULL, NULL);
        CreateWindowW(L"Button", L"Registrarse", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 250, 100, 150, 30, hwnd, (HMENU)IDC_REGISTER_BUTTON, NULL, NULL);
        CreateWindowW(L"Button", L"Ingresar como administrador", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 70, 150, 330, 30, hwnd, (HMENU)IDC_ADMIN_BUTTON, NULL, NULL);
    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_LOGIN_BUTTON:
            // Obtener el texto de los campos de usuario y contraseña
            TCHAR username[256], password[256];
            GetDlgItemText(hwnd, IDC_USERNAME_EDIT, username, 256);
            GetDlgItemText(hwnd, IDC_PASSWORD_EDIT, password, 256);

            // Verificar si los campos están vacíos
            if (lstrlen(username) == 0 || lstrlen(password) == 0) {
                MessageBox(hwnd, L"Ingrese un usuario y/o contraseña válidos", L"Inicio de Sesión", MB_OK | MB_ICONERROR);
            }
            else {
                // Verificar el usuario y la contraseña
                if (VerifyCredentials(username, password)) {
                    // Abrir la ventana del menú de usuario
                    // OpenUserMenuWindow(GetModuleHandle(NULL)); // Eliminado
                }
                else {
                    MessageBox(hwnd, L"Usuario y/o contraseña incorrectos", L"Inicio de Sesión", MB_OK | MB_ICONERROR);
                }
            }
            break;
            
        case IDC_REGISTER_BUTTON:
            // Abrir la ventana de registro de usuario
            OpenAdminRegistrationWindow(GetModuleHandle(NULL));
            break;
        case IDC_ADMIN_BUTTON:
            // Abrir la ventana de inicio de sesión de administrador
            OpenAdminLoginWindow(GetModuleHandle(NULL));
            break;
        // Código para procesar otros mensajes de control
        }
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Función para abrir la ventana de registro de administrador
void OpenAdminRegistrationWindow(HINSTANCE hInstance)
{
    // Registrar la clase de la ventana de registro de administrador
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = AdminRegistrationWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"AdminRegistrationWindowClass";
    RegisterClassEx(&wc);

    // Crear la ventana de registro de administrador
    HWND hwnd = CreateWindowEx(
        0,
        L"AdminRegistrationWindowClass",
        L"Registro de Usuario",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL,
        NULL,
        hInstance,
        NULL);

    // Mostrar la ventana de registro de administrador
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void OpenAdminLoginWindow(HINSTANCE hInstance)
{
    // Registrar la clase de la ventana de inicio de sesión de administrador
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = AdminLoginWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"AdminLoginWindowClass";
    RegisterClassEx(&wc);

    // Crear la ventana de inicio de sesión de administrador
    HWND hwnd = CreateWindowEx(
        0,
        L"AdminLoginWindowClass",
        L"Inicio de Sesión de Administrador",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 250,
        NULL,
        NULL,
        hInstance,
        NULL);

    // Mostrar la ventana de inicio de sesión de administrador
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

// Procedimiento de ventana para la ventana de registro de administrador
LRESULT CALLBACK AdminRegistrationWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Crear controles para la ventana de registro de administrador
        CreateWindowW(L"Static", L"Nombre de usuario:", WS_VISIBLE | WS_CHILD, 20, 20, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 20, 200, 25, hwnd, (HMENU)IDC_USERNAME_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Static", L"Contraseña:", WS_VISIBLE | WS_CHILD, 20, 60, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 180, 60, 200, 25, hwnd, (HMENU)IDC_PASSWORD_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Static", L"Confirmar contraseña:", WS_VISIBLE | WS_CHILD, 20, 100, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 180, 100, 200, 25, hwnd, (HMENU)IDC_CONFIRM_PASSWORD_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Static", L"Código de estudiante:", WS_VISIBLE | WS_CHILD, 20, 140, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 140, 200, 25, hwnd, (HMENU)IDC_STUDENT_CODE_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Button", L"Registrar", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 200, 100, 30, hwnd, (HMENU)IDC_ADMIN_REGISTER_BUTTON, NULL, NULL);
    }
    break;
    case WM_COMMAND:
    {
        // Procesar mensajes de control para la ventana de registro de administrador
        switch (LOWORD(wParam))
        {
        case IDC_ADMIN_REGISTER_BUTTON:
            // Obtener el texto de los campos de registro
            TCHAR username[256], password[256], confirmPassword[256], studentCode[256];
            GetDlgItemText(hwnd, IDC_USERNAME_EDIT_ADMIN, username, 256);
            GetDlgItemText(hwnd, IDC_PASSWORD_EDIT_ADMIN, password, 256);
            GetDlgItemText(hwnd, IDC_CONFIRM_PASSWORD_EDIT_ADMIN, confirmPassword, 256);
            GetDlgItemText(hwnd, IDC_STUDENT_CODE_EDIT_ADMIN, studentCode, 256);

            // Verificar si los campos están vacíos
            if (lstrlen(username) == 0 || lstrlen(password) == 0 || lstrlen(confirmPassword) == 0 || lstrlen(studentCode) == 0) {
                MessageBox(hwnd, L"Todos los campos son obligatorios", L"Registro de Usuario", MB_OK | MB_ICONERROR);
            }
            else if (lstrcmp(password, confirmPassword) != 0) {
                MessageBox(hwnd, L"Las contraseñas no coinciden", L"Registro de Usuario", MB_OK | MB_ICONERROR);
            }
            else {
                // Escribir los datos del usuario en el archivo
                WriteUserCredentialsToFile(username, password);
                MessageBox(hwnd, L"Usuario registrado exitosamente", L"Registro de Usuario", MB_OK | MB_ICONINFORMATION);
            }
            break;
        // Código para procesar eventos de los controles
        }
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Procedimiento de ventana para la ventana de inicio de sesión de administrador
LRESULT CALLBACK AdminLoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Crear controles para la ventana de inicio de sesión de administrador
        CreateWindowW(L"Static", L"Nombre de usuario:", WS_VISIBLE | WS_CHILD, 20, 20, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 20, 200, 25, hwnd, (HMENU)IDC_USERNAME_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Static", L"Contraseña:", WS_VISIBLE | WS_CHILD, 20, 60, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 180, 60, 200, 25, hwnd, (HMENU)IDC_PASSWORD_EDIT_ADMIN, NULL, NULL);

        CreateWindowW(L"Button", L"Ingresar", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 100, 100, 30, hwnd, (HMENU)IDC_LOGIN_BUTTON_ADMIN, NULL, NULL);
    }
    break;
    case WM_COMMAND:
    {
        // Procesar mensajes de control para la ventana de inicio de sesión de administrador
        switch (LOWORD(wParam))
        {
        // Código para procesar eventos de los controles
        }
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Función para mostrar el cuadro de diálogo de inicio de sesión inválido
void ShowInvalidLoginDialog(HWND hwnd)
{
    MessageBox(hwnd, L"Ingrese un usuario y/o contraseña válidos", L"Inicio de Sesión", MB_OK | MB_ICONERROR);
}