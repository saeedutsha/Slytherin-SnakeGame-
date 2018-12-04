#include <GL/gl.h>
#include <GL/glut.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "game.h"


int gridX,gridY;
//int posX=20,posY=20;
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
int sLength=5;
int sDirection = RIGHT;
extern bool gameOver;
bool food=true;
int foodX,foodY;
extern int score;

using namespace std;

void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;
}

void unit(int x, int y)
{

    if(x==0 || y==0 || x==gridX-1 || y==gridY-1){
        glLineWidth(7.0);
        glColor3f(1,0,0);
    }
    else{
        glLineWidth(3.0);
        glColor3f(0,0,0);
    }

    glBegin(GL_LINE_LOOP);

        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);

    glEnd();
}

void drawGrid()
{
    for(int x=0;x<gridX;x++){
        for(int y=0;y<gridY;y++){
            unit(x,y);
        }
    }
}

void drawFood()
{
    if(food){
        random(foodX,foodY);
    }
    food=false;
    glColor3f(1,0,1);
    glRectf(foodX,foodY,foodX+1,foodY+1);
}

void random(int &x,int &y)
{
    int _maxX=gridX-2, _minX=1;
    int _maxY=gridY-2, _minY=1;
    srand(time(NULL));
    x = _minX + rand() % (_maxX-_minX);
    y = _minY + rand() % (_maxY-_minY);
}


void drawSnake()
{
    for(int i = sLength-1; i>0; i--)
    {
        if(posX[i]==posX[0] && posY[i]==posY[0])gameOver=true;

        posX[i]=posX[i-1];
        posY[i]=posY[i-1];

        //cout<<"s"<<posX[i]<<" "<<posY[i];
        //cout<<"h"<<posX[0]<<" "<<posY[0];


    }



    //glColor3f(0,1,0);
    if(sDirection==UP)posY[0]++;
    else if(sDirection==DOWN)posY[0]--;
    else if(sDirection==RIGHT)posX[0]++;
    else if(sDirection==LEFT)posX[0]--;

    for(int i = 0; i < sLength-1; i++)
    {
        if(i==0)glColor3f(0,1,0);
        else glColor3f(1,1,0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }

    if(posX[0]==0 || posY[0]==0 || posX[0]==gridX-1 || posY[0]==gridY-1)gameOver=true;

    /*for(int i = 0; i < sLength-1; i++)
    {
        if(posX[0]==posX[i] || posY[0]==posY[i])
            gameOver=true;
    }*/

    if(posX[0]==foodX && posY[0]==foodY)
    {
        sLength++;
        score++;
        if(sLength>MAX)sLength=MAX;
        food=true;
    }
}



