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

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    
    pokemon = ObjModel("Models/Magnemite.obj");
    pokeball = Pokeball("Models/Pokeball.obj");
    
    pokemon.translate(ObjVertex(0.3, 0, 4));
    pokeball.scale(0.8, 0.8, 0.8);
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
}

void drawModel(ObjModel *model, int r, int g, int b)
{
    for (auto &object : model->getObjects())
    {
        for(auto &faceVector : object.getFaces())
        {
            glColor3ub(rand()%r, rand()%g, rand()%b);
            glBegin(GL_LINE_STRIP);
            for(auto vectorIndex : faceVector)
            {
                ObjVertex vertex = model->getVertices().at(vectorIndex);
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            glEnd();
        }
    }
}

int i = 0;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.13, 0.22, 0.29, 1.00);
    glLoadIdentity();
    
    glColor3ub(rand()%180, rand()%220, rand()%100 );
    drawModel(&pokemon, 180, 220, 100);
    drawModel(&pokeball, 200, 10, 10);
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 0, 0.5);
    for(auto point : pokeball.getPathPoints())
    {
        //glVertex3f(point.getX(), point.getY(), point.getZ());
    }
    glEnd();
    
    if(++i >= pokeball.getPathPoints().size())
        i =  0;
    
    ObjVertex dest = pokeball.getPathPoints().at(i);
    pokeball.translate(dest);
    
    glFlush();
    glutPostRedisplay();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 640);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("GoPokemon");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
