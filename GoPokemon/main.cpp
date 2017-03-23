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

ObjModel model;

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -2, 2, 1, 80);
    gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    // clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    for (auto &object : model.getObjects())
    {
        for(auto &faceVector : object.getFaces())
        {
            glColor3ub(rand()%255, rand()%155, rand()%255 );
            glBegin(GL_LINE_STRIP);
            for(auto vectorIndex : faceVector)
            {
                ObjVertex vertex = model.getVertices().at(vectorIndex);
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            glEnd();
        }
    }
    glFlush();
}

int main(int argc, char * argv[]) {
    model = ObjModel("Models/Magnemite.obj");
    
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
