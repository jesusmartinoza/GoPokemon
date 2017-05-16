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
int counter = 0;
int score = 0;
float timeClock = 0;

/*==============================================================*
                  G L U T    F U N C T I O N S
 *==============================================================*/
void displayText( float x, float y, int r, int g, int b, const string text ) {
    int j = text.length();
    
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text[i] );
    }
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.13, 0.22, 0.29, 1.00);
    glLoadIdentity();
    
    glPushMatrix();
    pokemon.draw();
    pokeball.draw();
    string counterLabel = "Time: " + to_string(counter);
    string scoreLabel = "Score: " + to_string(score);
    displayText(4, 5.5, 80, 100, 200, counterLabel);
    displayText(4, 5, 80, 100, 200, scoreLabel);
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
    gluPerspective(60.0, 1.0, 0.5, 30.0);
    gluLookAt (0.0, 0.0, 11.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt (1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    //gluLookAt (0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*==============================================================*
                        F U N C T I O N S
 *==============================================================*/
void timer(int)
{
    if(pokeball.update()) // true if path is finished
        score += 4;
    pokemon.update();
    
    if(pokemon.checkCollision(pokeball)) {
        //pokemon.captured = true;
        pokeball.calculatePath();
        score -= score >= 5 ? 5 : 0;
    }
    
    if(counter == 150)
        pokemon.afraid = true;
    
    float currentTime = glutGet( GLUT_ELAPSED_TIME );
    if( currentTime - timeClock > 1000 )
    {
        timeClock = currentTime;
        counter++;
    }
    
    glutPostRedisplay();
    glutTimerFunc(redisplay_interval, timer, 0);}

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
    pokeball = Pokeball("Models/Pokeball.obj");
    
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
