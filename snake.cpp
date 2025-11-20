#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
using namespace std;
int speed=50;
bool gameOver;
int width;
int height;
int x,y,fruitX,fruitY,score=0; 
int tailX[150]={0}, tailY[150]={0};
int nTail=0;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void clear_screen()
{
  printf( 
    "\033[2J"       // clear the screen
    "\033[1;1H" );  // move cursor home
}
void Setup() {
    gameOver=false;
    dir=STOP;
    cout<<"      ****SNAKE****";
    cout<<endl;
    cout<<"dimensions=";
    int dim;
    cin>>dim;
    width=2*dim;
    height=dim;
    cout<<endl;
    cout<<"difficulty=? (0-70hard 70-120medium 120-200 easy)"<<endl;
    cin>>speed;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
    clear_screen();
}
void Draw() {
    clear_screen();
    for (int i=0;i<width;i++) cout<<"#";
    cout<<endl;
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++)
            if(j==0 || j==width-1) cout<<"#";
            else if (i==y && j==x) cout<<"O";
                else if(i==fruitY && j==fruitX) cout<<"@";
                    else{
                        bool print=false;
                        for (int k=0; k<nTail;k++){
                            if (tailX[k]==j && tailY[k]==i){ cout<<"o"; print=true;}
                        }
                        if(!print) cout<<" ";
                    }
        cout<<endl;
    }
    for (int i=0;i<width;i++) cout<<"#";
    cout<<endl;
    cout<<"Score="<<score;
}
void Input() {
    if(_kbhit()){
        switch(_getch()) {
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'x':
                gameOver=true;
                break;
        }
    }
}
void Logic() {
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for (int i=1;i<nTail;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;    
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    
    if (x > width) x = x - width;
    if (x < 0) x = x + width;
    if (y > height) y = y - height;
    if ( y < 0) y = y + height;
    
   /*
   if (x>width+1 || x<=0 || y>height+1 || y<=0){
         gameOver=true;
   } 
    */
   for (int i=0;i<nTail;i++){
    if(tailX[i]==x && tailY[i]==y) gameOver=true;
   }
   if (x==fruitX && y==fruitY){
    score+=10;
    nTail++;
    fruitX=rand()%width;
    fruitY=rand()%height;
   }
}
int main () {
    Setup();
    while(true){
        Draw();
        Input();
        Logic();
        if (dir == LEFT || dir == RIGHT) {
            Sleep(5);
        }   
        Sleep(speed);

        if (dir == UP || dir == DOWN){
            Sleep(60);
        }
        if (gameOver){
            clear_screen(); 
            cout<<"GAME OVER!"; 
            cout<<endl; 
            cout<<"SCORE="; 
            cout<<score;
            cout<<endl;
            cout<<"R to retry X to quit";
            int ok=0;
            while (!ok){
                if(_kbhit()){
                    switch(_getch()) {
                        case 'r':
                            gameOver=false;
                            dir=STOP;
                            x=width/2;
                            y=height/2;
                            fruitX=rand()%width;
                            fruitY=rand()%height;
                            score=0;
                            for (int i=0;i<150;i++){tailX[i]=0; tailY[i]=0;}
                            ok=1;
                            clear_screen();
                            system("snake.exe");
                            return 0;
                            break;
                        case 'x':
                            return 0;
                            break;
                    }
                }
            }
        }
    }
}
