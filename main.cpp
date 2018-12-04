#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdlib.h>
#include "game.h"
#include "RGBpixmap.cpp"

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern int sDirection ;
bool gameOver = false;
int score = 0;

RGBpixmap pix[6];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D,5);
	glEnable(GL_TEXTURE_2D);
    drawGrid();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
    drawSnake();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,4);
	glEnable(GL_TEXTURE_2D);
    drawFood();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
    if(gameOver)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50] = "Your Score: ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
    }
}

void resize(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,COLUMNS,0,ROWS,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(1,1,1,1);
    initGrid(COLUMNS,ROWS);
    glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);	// create texture int parameter as TextureName


    //pix[0].readBMPFile("teapot.bmp");
    //	pix[0].setTexture(1);

	pix[1].readBMPFile("C:\\Codeblocks\\CG5\\SnakeGame2D\\jack.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("C:\\Codeblocks\\CG5\\SnakeGame2D\\snake.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("C:\\Codeblocks\\CG5\\SnakeGame2D\\apple.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Codeblocks\\CG5\\SnakeGame2D\\meta.bmp");
	pix[4].setTexture(5);

}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

void keyboard(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("MyGame");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
