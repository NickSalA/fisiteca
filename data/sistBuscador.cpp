#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include<locale>
#include"../menu/funciones.hpp"
#define ARRIBA VK_UP
#define ABAJO VK_DOWN
#define ENTER 13

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string genero;
    string autor;
    int anoPublicacion;
    string sinopsis;
    int cantidad;
}; //incluir esto con las librerias para que funcione.

char getch2() {
    char c = 0;
    DWORD contador;
    HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInputRecord; // Estructura para el registro de entrada

    // Lee un evento de entrada del teclado
    ReadConsoleInputA(ih, &irInputRecord, 1, &contador);

    // Verifica si el evento es una tecla presionada
    if (irInputRecord.EventType == KEY_EVENT && irInputRecord.Event.KeyEvent.bKeyDown) {
        // Extrae el código virtual de la tecla
        c = irInputRecord.Event.KeyEvent.wVirtualKeyCode;

        // Convierte el código virtual a una de las teclas definidas (ARRIBA o ABAJO)
        switch (c) {
            case VK_UP:
                c = ARRIBA;
                break;
            case VK_DOWN:
                c = ABAJO;
                break;
        }
    }

    return c;
}

void esperaConMensaje(const string& mensaje) {
    cout << mensaje << endl;
    _getwch(); // Espera a que el usuario presione una tecla mostrnaof rl mrnssaje que esta como parametrok
}

vector<Libro> cargarLibrosDesdeArchivo_ti(const string& nombreArchivo) {
    vector<Libro> libros;
    ifstream archivo(nombreArchivo.c_str(), ios::in);
    if (archivo.is_open()) {
        Libro libro;
        while (archivo >> libro.codigo) {

            archivo.ignore();
            getline(archivo, libro.nombre);
            getline(archivo, libro.genero);
            getline(archivo, libro.autor);
            archivo >> libro.anoPublicacion;
            archivo.ignore();
            getline(archivo, libro.sinopsis);
            archivo>>libro.cantidad;
            archivo.ignore();
            libros.push_back(libro);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return libros;
}


vector<Libro> buscarCoincidencias_ti(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string tituloLower = libro.nombre;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (tituloLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscador_ti() {
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");
        
        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el titulo a buscar: ";
        getline(cin, busqueda);
        
        vector<Libro> coincidencias = buscarCoincidencias_ti(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout<<"Cantidad: "<<libro.cantidad<<endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_gen(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string generoLower = libro.genero;
        transform(generoLower.begin(), generoLower.end(), generoLower.begin(), ::tolower);

        if (generoLower.find(busquedaLower) != string::npos) {
            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscador_gen() {
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el genero a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_gen(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout<<"Cantidad: "<<libro.cantidad<<endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_autor(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    for (const Libro& libro : libros) {
        string autorLower = libro.autor;
        transform(autorLower.begin(), autorLower.end(), autorLower.begin(), ::tolower);

        if (autorLower.find(busquedaLower) != string::npos) {
        coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}             
void mainBuscar_autor(){
        
     string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el autor a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_autor(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout<<"Cantidad: "<<libro.cantidad<<endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}


vector<Libro> buscarCoincidencias_anio(const vector<Libro>& libros, const string& busqueda) {
    vector<Libro> coincidencias;

    for (const Libro& libro : libros) {
        string anoPublicacionStr = to_string(libro.anoPublicacion);

        if (anoPublicacionStr.find(busqueda) != string::npos) {
                            coincidencias.push_back(libro);
        }
    }

    return coincidencias;
}
void mainBuscar_anio() {
                
    string nombreArchivo = "libros.txt";

    vector<Libro> libros = cargarLibrosDesdeArchivo_ti(nombreArchivo);

    string busqueda;
    do {
        system("cls");

        cout<<"0.Regresar\n";
        cout << "\t\tIngrese el anio a buscar: ";
        getline(cin, busqueda);

        vector<Libro> coincidencias = buscarCoincidencias_anio(libros, busqueda);

        if(busqueda == to_string(0)){

            cout<<"Regresando....";
            Sleep(2000);
            break;
        }

        if (coincidencias.empty()) {
            cout << "No se encontraron coincidencias para el término de búsqueda: " << busqueda << endl;
        } else {
            cout << "Coincidencias encontradas:\n";
            for (const Libro& libro : coincidencias) {
                cout << "Código: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Género: " << libro.genero << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de Publicación: " << libro.anoPublicacion << endl;
                cout << "Sinopsis: " << libro.sinopsis << endl;
                cout<<"Cantidad: "<<libro.cantidad<<endl;
                cout << endl;
            }
        }
        esperaConMensaje("Presione una tecla para volver a buscar...");
    } while(true);
}

int menu(int n) {
      setColor(White);    
      int opcionSeleccionada = 1;  // Indica la opción seleccionada
      int tecla;
      string titulo = R"(    
                                          ████░█░░░█░████░█████░░░█░░░░█░█████░████░░░███░
                                          █░░█░█░░░█░█░░░░█░░░█░░░█░░░░█░█░░░░░█░░░█░█░░░█
                                          ███░░█░░░█░░██░░█░░░█░░░█░░░░█░█████░█░░░█░█░░░█
                                          █░░█░█░░░█░░░░█░█░░░█░░░█░░░░█░█░░░░░█░░░█░█████
                                          ███░░░███░░████░██████░░░████░░█████░████░░█░░░█
                                          ░░░░░░░░░░░░░░░░░░░░███░░░░░░░░░░░░░░░░░░░░░░░░░
)";
      vector<string>opciones = {" Buscar por título", " Buscar por género", " Buscar por año de publicación", " Buscar por autor", " Regresar al menú principal"};   
      bool repite = true; // controla el bucle para regresar a la rutina que lo llamó, al presionar ENTER
  
      do {
         system("cls");
         CenterConsoleWindow();
         dibujarTitulo(2, 3, titulo);
         dibujarCuadro(35, 2, 60, 25);
         dibujarCuadro(32, 0, 66, 29);
         dibujarMenu(48,13,opciones);
         gotoxy(42, 10 + opcionSeleccionada*3); cout << "=>" <<"\t\t\t\t\t\t"<<"<="<<endl;
 
   
         // Solo permite que se ingrese ARRIBA, ABAJO o ENTER
         do {
               tecla = getch2();
         } while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
   
         switch (tecla) {
               case ARRIBA:   // En caso de que se presione ARRIBA
                  opcionSeleccionada--;
                  if (opcionSeleccionada < 1) {
                     opcionSeleccionada = n;
                  }
                  break;
   
               case ABAJO:
                  opcionSeleccionada++;
                  if (opcionSeleccionada > n) {
                     opcionSeleccionada = 1;
                  }
                  break;
   
               case ENTER:
                  repite = false;
                  break;
         }

   
        } while (repite);
   
      return opcionSeleccionada;
   }

void menuPrincipal(){
	
    bool repite = true;
   int opcion;   

   int n = 5;  // Numero de opciones
   
    do {
      opcion = menu(n);
 
      switch (opcion) {
         case 1:
            mainBuscador_ti();
            break;
 
 
         case 2:
            mainBuscador_gen();
            break;
 
         case 3:
            mainBuscar_anio();
            break;
 
         case 4:
            mainBuscar_autor();
            break;
 
         case 5:
           break;
           
        default:
            cout << "Opción no válida." << endl;
            break;
      }
 
   } while(repite);	
}
