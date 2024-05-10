#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;
int main(){
cout<<"hola";
}

void leerLibro(){
    ifstream Leer("libros.txt", ios::in);
    if(Leer.fail()){
					cout<<"Error en el archivo..."<<endl;
					Sleep(2000);
					exit(1);
}}
void añadirLibro(){
    cout<<"Sistema de pedido de libros"<<endl;
                do{
                	cout<<"Ingresar los datos del libro"<<endl;
				}while((n<1)||(n>10));
                
					for(int i=0; i<n;i++){
						cout<<" "<<i+1<<endl;
						cout<<"Codigo: ";cin>>customer[i].Codigo;
						fflush(stdin);	
						cout<<"Nombre: ";
						getline(cin,customer[i].nombre);
						do{
							cout<<"Precio(20-100): ";cin>>customer[i].precio;
						}while((customer[i].precio<20)||(customer[i].precio>100 ));
						do{
							cout<<"Tipo:\n1.A \n2.B \n";cin>>customer[i].tipo;
						}while((customer[i].tipo<1)||(customer[i].tipo>2 ));
						
					}
					system("pause");
					for(int i=0;i<n;i++){
						cout<<"Producto "<<i+1<<endl;
						cout<<"\nCodigo: "<<customer[i].Codigo;
						cout<<"\nNombre: "<<customer[i].nombre;
						cout<<"\nPrecio base: "<<customer[i].precio;

						cout<<"Campo porcentaje de aumento: "<<customer[i].porcentajeaum*100<<"%"<<endl;
						cout<<"Importe aumento: "<<customer[i].importeau<<endl;
						cout<<"Precio maximo: "<<customer[i].preciomax<<endl;
						cout<<"Campo porcentaje de descuento: "<<customer[i].porcentajedesc*100<<"%"<<endl;
						cout<<"Importe descuento: "<<customer[i].importedesc<<endl;
						cout<<endl;
						ofstream Grabacion("cliente.txt", ios::app);
						if(Grabacion.fail()){
							cout<<"Error en el archivo..."<<endl;
							Sleep(2000);
							exit(1);
						}
						cout<<"Grabando registros....."<<endl;
						Sleep(2000);
						for(int i=0; i<n;i++){
							Grabacion<<	customer[i].Codigo<<endl;
							Grabacion<<	customer[i].nombre<<endl;
							Grabacion<<	customer[i].precio<<endl;
							if(customer[i].tipo==1){
								Grabacion<<"A"<<endl;
							}
							else{
								Grabacion<<"B"<<endl;
							}
							Grabacion<<	customer[i].porcentajeaum<<endl;
							Grabacion<<	customer[i].importeau<<endl;
							Grabacion<<	customer[i].preciomax<<endl;
							Grabacion<<	customer[i].porcentajedesc<<endl;
							Grabacion<<	customer[i].importedesc<<endl;
							
						}
						Grabacion.close();	
					}	
				break;
}

aeaeaeasdajsbdasjkbiuasdasda;
