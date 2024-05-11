#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "Ä";
		gotoxy(i,y2); cout << "Ä";
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout << "³";
		gotoxy(x2,i); cout << "³";
    }
    
    gotoxy(x1,y1); cout << "Ú";
    gotoxy(x1,y2); cout << "À";
    gotoxy(x2,y1); cout << "¿";
    gotoxy(x2,y2); cout << "Ù";
}
void CursorOn(bool visible, DWORD size){
	if(size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}