#include <windows.h>
#include <iostream>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void limpia();
void vacio();


void dibujarCuadro(int x1,int y1,int x2,int y2){
    for(int i=x1;i<=x2;i++){
        gotoxy(i,y1);cout<<(char)205;
        gotoxy(i,y2);cout<<(char)205;
    }
    for(int i=y1;i<=y2;i++){
        gotoxy(x1,i);cout<<(char)186;
        gotoxy(x2,i);cout<<(char)186;
    }
    gotoxy(x1,y1);cout<<(char)201;
    gotoxy(x2,y1);cout<<(char)187;
    gotoxy(x1,y2);cout<<(char)200;
    gotoxy(x2,y2);cout<<(char)188;
}