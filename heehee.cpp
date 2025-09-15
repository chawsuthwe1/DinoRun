#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#define dinoPos 2
#define hurdlePos 74

using namespace std;
HANDLE console = GetStdHandle (STD_OUTPUT_HANDLE);
COORD CursorPosition;
string name="", score1="0";
int dinoY;
int speed = 40;
int gameover = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor (bool visible, DWORD size){
    if (size == 0) {
    size = 20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo (console, & lpCursor);
}

void init() {
    system("cls");
    gameover = 0;
    gotoxy(3, 2); cout<<"SCORE: ";
    for (int i = 0 ; i < 69 ; i++){
        gotoxy (1+i, 1); cout<<"ß";
        gotoxy (1+i, 1); cout<<"ß";
    }
}

void moveDino (int jump = 0) {
    static int foot = 0;
    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;
        gotoxy (dinoPos, 15 - dinoY); cout<<"                 ";
        gotoxy (dinoPos, 16 - dinoY); cout<<"         ÜÛßÛÛÛÛÜ";
        gotoxy (dinoPos, 17 - dinoY); cout<<"         ÛÛÛÛÛÛÛÛ";
        gotoxy (dinoPos, 18 - dinoY); cout<<"         ÛÛÛÛÛßßß";
        gotoxy (dinoPos, 19 - dinoY); cout<<" Û      ÜÛÛÛÛßßß ";
        gotoxy (dinoPos, 20 - dinoY); cout<<" ÛÛÜ  ÜÛÛÛÛÛÛÜÜÜ ";
        gotoxy (dinoPos, 21 - dinoY); cout<<" ßÛÛÛÛÛÛÛÛÛÛÛ  ß ";
        gotoxy (dinoPos, 22 - dinoY); cout<<"   ßÛÛÛÛÛÛÛß     ";
        gotoxy (dinoPos, 23 - dinoY);
    if (jump == 1 || jump == 2) {
        cout<<"    ÛÛß ßÛ       ";
        gotoxy(2, 24 - dinoY);
        cout<<"    ÛÜ   ÛÜ      ";
    }
    else if (foot == 0) {
        cout<<"    ßÛÛß  ßßß    ";
        gotoxy(2, 24 - dinoY);
        cout<<"      ÛÜ         ";
        foot = !foot;
    }
    else if (foot == 1) {
        cout<<"    ßÛÜ ßÛ       ";
        gotoxy(2, 24 - dinoY);
        cout<<"         ÛÜ      ";
        foot = !foot;
    }

    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout<<"ßßßßßßßßßßßßßßßßß";
    } else {
        cout<<"                 ";
    }
    Sleep(speed);
}
void drawHurdle() {
    static int plantX = 0;
    static int score = 0;
    if (plantX == 56 && dinoY < 4) {
    speed = 40;
    gotoxy(36, 8); cout<<"Game Over"; getch(); gameover= 1;
    if(gameover == 1)
    {
        ofstream myfile("C:/Dinoscore/score.txt",ios::app);
        myfile<<score<<" ";
        myfile.close();
    }
    score =-1;
}
    gotoxy (hurdlePos - plantX, 20); cout<<"| | ";
    gotoxy (hurdlePos - plantX, 21); cout<<"| | ";
    gotoxy (hurdlePos - plantX, 22); cout<<"|_| ";
    gotoxy (hurdlePos - plantX, 23); cout<<" |  ";
    gotoxy (hurdlePos - plantX, 24); cout<<" |  ";
    plantX++;
    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2); cout<<"      ";
        gotoxy(11, 2); cout<<score;
        if (score > 5)
            speed = 25;
        if (score > 15)
            speed = 2;
        if (score > 20)
            speed = 10;
        if (score > 30)
            speed = 5;
        if (score > 40)
            speed = 0;
        if (score > 50)
            speed = -10;
        }
    }

void play(){
    system("cls");
    char ch;
    int i;
    init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1){
                return;
            }
            moveDino();
            drawHurdle();
        }
        ch = getch();
        if(ch == 'p' || ch == 'P')
        {
            char a;
            do{

            gotoxy(30,10); cout<<"-----------------";
            gotoxy(30,11); cout<<"|     Pause     |";
            gotoxy(30,12); cout<<"-----------------";
            gotoxy(27,14); cout<<"Press small 'p' for continue";
            a = getch();
            }
            while(a != 'p');system("cls");
            init();
        }
        else if (ch == 32) {
            i = 0;
            while( i < 12 ) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while (i > 0) {
                moveDino (2);
                drawHurdle();
                i--;
            }
        }
            else if (ch == 'p' || ch== 'P')
                getch();
            else if (ch == 27)
                break;
    }
}

void instructions() {
    system("cls");
    gotoxy(10,5) ;cout<<"        Instructions";
    gotoxy(10,6) ;cout<<"---------------------------------";
    gotoxy(10,7) ;cout<<"1. Press 'Spacebar' to jump ";
    gotoxy(10,8) ;cout<<"2. Press 'p' to pause game ";
    gotoxy(10,9) ;cout<<"3. Press 'Esc' to exit from game";
    gotoxy(10,10);cout<<"   Press any key to go back to menu";
    getch();
}

void show(){
    system("cls");
    string score;
    int i =1;
    gotoxy(10,3); cout << name<<"\t\t\t\t\t\t\t\t"<< "Score"<<endl;
    ifstream open("C:/Dinoscore/score.txt");
    while ( open >> score){
    gotoxy(10,3+i);cout << "Game"<<i<<"\t\t\t\t\t\t\t\t"<<score<<endl;
    i++;
    }
    system ("pause");
}
int main() {
        remove("C:/Dinoscore/score.txt");
        setcursor(0, 0);
        system("color 70");
        gotoxy (10,3); cout<<"Enter your name : ";
        getline(cin, name);
    do{
        system("cls");
        gotoxy(10,3) ; cout<<"Welcome to Dino, "<<name;
        gotoxy(10,5) ; cout<<"--------------------------";
        gotoxy(10,6) ; cout<<"|       Dino Run         |";
        gotoxy(10,7) ; cout<<"--------------------------";
        gotoxy(10,9) ; cout<<"1. Instructions";
        gotoxy(10,10); cout<<"2. Start Game (*Spacebar* to Jump)";
        gotoxy(10,11); cout<<"3. Scores";
        gotoxy(10,12); cout<<"4. Quit";
        gotoxy(10,14); cout<<"Select option: "; char op = getche();
        if( op=='1') instructions();
        else if( op=='2') play();
        else if( op=='3') show();
        else if( op=='4') exit(0);
    } while(1);
    return 0;
}

