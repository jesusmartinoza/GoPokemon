//
//  main.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "ObjModel.hpp"
#include "Pokeball.hpp"
#include "Pokemon.hpp"

/*==============================================================*
                      V A R I A B L E S
 *==============================================================*/
Pokemon pokemon;
Pokeball pokeball;
static int redisplay_interval;

/*==============================================================*
                  G L U T    F U N C T I O N S
 *==============================================================*/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.13, 0.22, 0.29, 1.00);
    glLoadIdentity();
    
    glPushMatrix();
    pokemon.draw();
    pokeball.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            pokemon.moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            pokemon.moveRight();
            break;
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-2, 2, -2, 2, 1, 20);
    gluPerspective(60.0, 1.0, 1.5, 30.0);
    gluLookAt (0.0, 0.0, 11.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*==============================================================*
                        F U N C T I O N S
 *==============================================================*/
void timer(int)
{
    pokeball.update();
    glutPostRedisplay();
    glutTimerFunc(redisplay_interval, timer, 0);
}

void setFPS(int fps)
{
    redisplay_interval = 1000 / fps;
    glutTimerFunc(redisplay_interval, timer, 0);
}

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    
    pokemon = Pokemon("Models/Magnemite.obj");
    
    ObjVertex p1 = ObjVertex(-6, 8, -12);
    ObjVertex r1 = ObjVertex(-11, 3, -4);
    ObjVertex r4 = ObjVertex(-3, 2, 1);
    ObjVertex p4 = ObjVertex(-2, -2, 1);
    pokeball = Pokeball("Models/Pokeball.obj", p1, p4, r1, r4);
    
    pokemon.translate(ObjVertex(0.3, 0, 2));
    pokeball.scale(0.8, 0.8, 0.8);
    setFPS(50);
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 640);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("GoPokemon");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();
    return 0;
}
