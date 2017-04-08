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

void drawModel(ObjModel *model);
void init (void);
void reshape(int w, int h);

ObjModel pokemon;
Pokeball pokeball;

int i = 0;
void render() {
    if(++i >= pokeball.getPathPoints().size()) {
        i =  0;
        pokeball.setR1(ObjVertex(rand()%10 - rand()%20, rand()%3 - rand()%6, rand()%4 - rand()%8));
        pokeball.setR4(ObjVertex(rand()%4 - 8, rand()%3 - 4, rand()%2 - 4));
        pokeball.calculatePath();
    }
    
    ObjVertex dest = pokeball.getPathPoints().at(i);
    pokeball.translate(dest);
    glutPostRedisplay();
}
/*
 static int redisplay_interval;
void timer(int) {
    render();
    glutPostRedisplay();
    glutTimerFunc(redisplay_interval, timer, 0);
}

void setFPS(int fps)
{
    redisplay_interval = 1000 / fps;
    glutTimerFunc(redisplay_interval, timer, 0);
}*/

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    
    pokemon = ObjModel("Models/Magnemite.obj");
    
    ObjVertex p1 = ObjVertex(-6, 8, -12);
    ObjVertex r1 = ObjVertex(-11, 3, -4);
    ObjVertex r4 = ObjVertex(-3, 2, 1);
    ObjVertex p4 = ObjVertex(-2, -2, 1);
    pokeball = Pokeball("Models/Pokeball.obj", p1, p4, r1, r4);
    
    pokemon.translate(ObjVertex(0.3, 0, 2));
    pokeball.scale(0.8, 0.8, 0.8);
    //setFPS(15);
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
ObjVertex vertex;
void drawModel(ObjModel *model)
{
    for (auto &object : model->getObjects())
    {
        for(auto &faceVector : object.getFaces())
        {
            glBegin(GL_LINE_STRIP);
            //glColor3ub(rand()%r, rand()%g, rand()%b);
            for(auto vectorIndex : faceVector)
            {
                vertex = model->getVertices().at(vectorIndex);
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            glEnd();
        }
    }
}

void SpecialInput(int key, int x, int y)
{
    ObjVertex dest = pokemon.getVertices().at(0);
    switch(key)
    {
        case GLUT_KEY_LEFT:
            dest.setX(dest.getX()-0.5);
            break;
        case GLUT_KEY_RIGHT:
            dest.setX(dest.getX()+0.5);
            break;
    }
    pokemon.translate(dest);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.13, 0.22, 0.29, 1.00);
    //glLoadIdentity();
    glPushMatrix();
    drawModel(&pokemon);
    drawModel(&pokeball);
    
    glPopMatrix();
    glutSwapBuffers();
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
    glutIdleFunc(render);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();
    return 0;
}
