#include <iostream>
#include <conio.h>
#include <windows.h>
#include "headers.h"

#define color SetConsoleTextAttribute

using namespace std;

int main(){

    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE);
    cursorVisible(false);

    int opc = 2;
    int opcPos = 2;
    int xPos = 14;
    int yPos = 10;

    int colorUse = 79;
    int colorSet[3]={7, colorUse, 7};

    do{

    color(hConsole, colorSet[0]);
    gotoxy(xPos, yPos);     cout<<"                 ";
    gotoxy(xPos, yPos + 1); cout<<"     Opcion      ";
    gotoxy(xPos, yPos + 2); cout<<"                 ";

    color(hConsole, colorSet[1]);
    gotoxy(xPos, yPos + 4); cout<<"                 ";
    gotoxy(xPos, yPos + 5); cout<<"     Opcion      ";
    gotoxy(xPos, yPos + 6); cout<<"                 ";


    color(hConsole, colorSet[2]);
    gotoxy(xPos, yPos + 8);     cout<<"                 ";
    gotoxy(xPos, yPos + 9); cout<<"     Opcion      ";
    gotoxy(xPos, yPos + 10); cout<<"                 ";

    int key = _getch(); 

    if (key == 72 && opcPos>1) opcPos--;
    else if(key == 80 && opcPos<3) opcPos++;

    for (int i = 0; i<3; i++)
        colorSet[i] = 7;

    if (opcPos == 1)
        colorSet[0] = colorUse;

    else if (opcPos == 2)
        colorSet[1] = colorUse;

    else if (opcPos == 3)
        colorSet[2] = colorUse;

    }
    while( opc != 3);

    return 0;
}