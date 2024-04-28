#include <iosteam>
#include <stdlib.h>
#include <fstream>

int main(){

}

void Escribir(){
    ifstream Leer("libros.txt", ios::in);
    if(Leer.fail()){
					cout<<"Error en el archivo..."<<endl;
					Sleep(2000);
					exit(1);
}
