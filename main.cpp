#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#define up 72
#define down 80
#define right 77
#define left 75
#define ENTER 13
using namespace std;

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

void marco(int x, int y){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	y+=2;
	x+=2;
	for(int f=3; f<=x; f++){
		gotoxy(f, 3); printf("%c",205);
		gotoxy(f, y);printf("%c",205);
	}
	for(int c=3; c<=y; c++){
		gotoxy(3, c); printf("%c",186);
		gotoxy(x, c);printf("%c",186);
	}
	
	gotoxy(3,3);printf("%c",201);
	gotoxy(3,y);printf("%c",200);
	
	gotoxy(x,3);printf("%c",187);
	gotoxy(x,y);printf("%c",188);
}

class PJ{
	int x, y;
	int corazones;
	int vidas;
public:
	PJ(int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas){}
	int X(){return x;}
	int Y(){return y;}
	int VIDA(){return vidas;}
	void COR(){corazones--;}
	void pintar(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		gotoxy(x, y);   printf(" %c ",219);
		gotoxy(x, y+1); printf("%c%c%c",219,219,219);
		gotoxy(x, y+2); printf(" %c",219);
		gotoxy(x, y+3); printf("%c %c",219,219);
	}
	void borrar(){
		gotoxy(x, y); printf("   ");
		gotoxy(x, y+1); printf("   ");
		gotoxy(x, y+2); printf("   ");
		gotoxy(x, y+3); printf("   "); 
	}
	void mover(){
		if(kbhit()){
			char tecla = getch();
			borrar();
			if(tecla==up and y>4) y--;
			if(tecla==down and y<28) y++;
			if(tecla==left and x>4) x--;
			if(tecla==right and x<25) x++;
			pintar();
			pintar_corazones();
		}
	}
	void pintar_corazones(){
		gotoxy(10,2); printf("vidas %d", vidas);
		gotoxy(20,2); printf("Salud");
		gotoxy(26,2); printf("    ");
		for(int i=0; i<corazones; i++){
			gotoxy(26+i,2); printf("%c",3);
		}
	}
	void morir(){
		if(corazones==0){
			borrar();
			gotoxy(x,y);   printf(" * ");
			gotoxy(x,y+1); printf("***");
			gotoxy(x,y+2); printf(" * ");
			Sleep(200);
			
			borrar();
			gotoxy(x,y);   printf("* *");
			gotoxy(x,y+1); printf(" * ");
			gotoxy(x,y+2); printf("* *");
			Sleep(200);
			borrar();
			vidas--;
			corazones=3;
			pintar_corazones();
			pintar();
		}
	}
};

class FLECHA {
	int x, y;
public:
	FLECHA(int _x, int _y): x(_x), y(_y){}
	void pintar(int& op);
	void borrar();
	void mover(int& op);
};
void FLECHA::pintar(int& op) {
	gotoxy(x, y); printf(">");
	op=x+y;
}
void FLECHA::borrar() {
	gotoxy(x, y); printf(" ");
}
void FLECHA::mover(int& op) {
	if (_kbhit()) {
		char tecla = _getch();
		borrar();
		if (tecla == down and y < 14) y += 4;
		if (tecla == up and y > 10) y -= 4;
		pintar(op);
	}
}

class enemys{
	int x, y;
public:
	enemys(int _x, int _y): x(_x), y(_y){}
	void borrar(){
		gotoxy(x, y); printf("   ");
		gotoxy(x, y+1); printf("   ");
		gotoxy(x, y+2); printf("   ");
		gotoxy(x, y+3); printf("   ");
	}
	void pintar(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		gotoxy(x, y);   printf("%c %c",219,219);
		gotoxy(x, y+1); printf(" %c ",219);
		gotoxy(x, y+2); printf("%c%c%c",219,219,219);
		gotoxy(x, y+3); printf(" %c ",219);
	}
	void mover(){
		borrar();
		y++;
		pintar();
		if(y>27){borrar();
			x=rand()%22+4;
			y=4;
		}
	}
	void choque(struct PJ &N){
		char sonido[] = "media\\choque.wav";
		if(x+2>=N.X() and x<=N.X()+2 and y>=N.Y()-3 and y-3<=N.Y()+3){
			PlaySound((LPCSTR)sonido, NULL, SND_FILENAME | SND_ASYNC);
			borrar();
			N.COR();
			N.borrar();
			N.pintar();
			N.pintar_corazones();
			Sleep(700);
			x=rand()%22+4;
			y=4;
		}
	}
};
void puntaje();

void inicio(){
	OcultarCursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	int op;
	for(int f=3; f<=40; f++){
		gotoxy(f, 3); printf("%c",205);
		gotoxy(f, 30);printf("%c",205);
	}
	for(int c=3; c<=30; c++){
		gotoxy(3, c); printf("%c",186);
		gotoxy(40, c);printf("%c",186);
	}
	
	gotoxy(3,3);printf("%c",201);
	gotoxy(3,30);printf("%c",200);
	
	gotoxy(40,3);printf("%c",187);
	gotoxy(40,30);printf("%c",188);
	
	gotoxy(16,10);cout << "Iniciar";
	gotoxy(16,14);cout << "Salir";
	bool game_over=false;
	FLECHA f1(14,10);
	f1.pintar(op);
	while(!game_over){
		f1.mover(op);
		if(getch()==ENTER) game_over=true;
	}
	switch(op){
		case 24: break;
		case 28: system("cls"); exit(1);  break;
	}
	system("cls");
}
int main(){
	SetConsoleTitle(TEXT("Autos 10000"));
	system("mode con: cols=44 lines=35");
	ini:
	inicio();
	SetConsoleTitle(TEXT("Coches"));
	OcultarCursor();
	marco(26,30);
	PJ p1(15, 26, 3, 3);
	p1.pintar();
	p1.pintar_corazones();
	enemys e1(10,4);
	bool game_over = false;
	int cont=0;
	int puntaje=0;
	
	ifstream file("puntaje.xml");
	while(!game_over){
		gotoxy(2,1);
    	string line;
    	getline(file, line);
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        printf("puntaje max: %s", line.c_str());
        stringstream geek(line); 
		file.close();
		
		int pmax; 
    	geek >> pmax;
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		if(cont%4==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			gotoxy(5,2); puntaje+=1;cout << puntaje;
		}
		e1.mover(); e1.choque(p1);
		p1.morir();
		p1.mover();
		if(cont < 100){
			Sleep(100);
		}if(cont>=100 and cont <200){
			Sleep(80);
		}if(cont>=200 and cont <400){
			Sleep(60);
		}if(cont>=400 and cont <700){
			Sleep(40);
		}if(cont>=700){
			Sleep(25);
		}
		cont++;
		if(puntaje>pmax){
			pmax=puntaje;
			ofstream maxp;
			maxp.open("puntaje.xml");
			maxp << pmax;
			maxp.close();
		}
		if(p1.VIDA()<0){
			Sleep(400);
			system("cls");
			goto ini;
		}
		
	}
	getch();
	return 0;
}
