//
//  ObjModel.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//  Main class that represent the entire OBJ model.
//  It contains a list of vertices and objects.
//

#include "ObjModel.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265

using namespace std;

/**
 * Default constructor
 **/
ObjModel::ObjModel()
{
    
}

/**
 * Constructor. Read obj file as text file and create OBJModel.
 * @param fileName Name of the obj file with extension.
 **/
ObjModel::ObjModel(string fileName)
{
    cout << "File name: " << fileName << "\n" << endl;
    
    string line;
    ifstream file (fileName);
    
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            //cout << line;
            switch (line[0]) {
                // Create OBJ object and add it to vector.
                case 'o': {
                    const char* name = getSplittedLine(line).at(0);
                    ObjObject object = ObjObject(string(name));
                    this->objects.push_back(object);
                    break;
                }
                // Create vertex and add it to vector.
                case 'v': {
                    vector<const char*> coords = getSplittedLine(line);
                    ObjVertex vertex = ObjVertex(::atof(coords.at(0)), ::atof(coords.at(1)), ::atof(coords.at(2)));
                    vertices.push_back(vertex);
                    break;
                }
                // Add vertices indexes to the last OBJ object created.
                case 'f': {
                    vector<ObjVertex> faceVector;
                    vector<const char*> facesIndexes = getSplittedLine(line);
                    
                    for(auto &faceIndex : facesIndexes)
                    {
                        int i = (atoi(faceIndex)) - 1;
                        ObjVertex vertex = ObjVertex(vertices.at(i));
                        faceVector.push_back(vertex);
                    }
                    objects.back().getFaces().push_back(faceVector);
                    break;
                }

            }
            //cout << endl;
        }
        file.close();
        calculateBoxSize();
    }
    
    else cout << "Unable to open file";
}

/**
 * Receive a string and split it in words separated by space.
 * @param line Line to be splitted.
 * @return vector with words.
 **/
vector<const char*> ObjModel::getSplittedLine(const string &line)
{
    vector<const char*> splitted;
    char * lineWord = nullptr;
    
    lineWord = strtok (const_cast<char *>(line.c_str()), " ");
    while (lineWord != NULL)
    {
        lineWord = strtok (NULL, " ");
        splitted.push_back(lineWord);
    }
    splitted.pop_back();
    return splitted;
}

/**
 * Calculate boundary size. Tracking of the max/min
 * for each X, Y and Z axes.
 **/
void ObjModel::calculateBoxSize()
{
    float minX = vertices.at(0).getX();
    float minY = vertices.at(0).getY();
    float minZ = vertices.at(0).getZ();
    
    float maxX = vertices.at(0).getX();
    float maxY = vertices.at(0).getY();
    float maxZ = vertices.at(0).getZ();
    
    for (auto &vertice : vertices)
    {
        if(minX > vertice.getX()) minX = vertice.getX();
        if(minY > vertice.getY()) minY = vertice.getY();
        if(minZ > vertice.getZ()) minZ = vertice.getZ();
        
        if(maxX < vertice.getX()) maxX = vertice.getX();
        if(maxY < vertice.getY()) maxY = vertice.getY();
        if(maxZ < vertice.getZ()) maxZ = vertice.getZ();
    }
    
    sizeX = (maxX - minX);
    sizeY = (maxY - minY);
    sizeZ = (maxZ - minZ);
    
    anchorPoint.setX(sizeX / 2 + minX);
    anchorPoint.setY(sizeY / 2 + minY);
    anchorPoint.setZ(sizeZ / 2 + minZ);
    
    // Reduce size of the box
    sizeX /= 6;
    sizeY /= 4;
    sizeZ /= 3;
}

/**
 * Read all OBJ Model info and print.
 **/
void ObjModel::print()
{
    cout << "\n**** OBJ MODEL *******" << endl;
    /*
        Lost in vertices refactor hehe
     */
}

/**
 * Multiply every point by the matrix to obtain the new point
 * @param matrix Could be rotation, scale, translation, etc.
 **/
void ObjModel::multiplyMatrix(float (&matrix)[4][4])
{
    vector<ObjVertex>::iterator it;
    for (auto &object : objects)
    {
        for(auto &face : object.getFaces())
        {
            for(it = face.begin(); it < face.end(); it++)
            {
                float origin[] = {
                    it->getX(),
                    it->getY(),
                    it->getZ(),
                    1
                };
                float dest[] = {0, 0, 0, 0};
                
                // Multiply translate matrix by origin vector.
                for(int i = 0; i < 4; i++)
                    for(int j = 0; j < 4; j++)
                        dest[i] += matrix[i][j] * origin[j];
                
                it->setX(dest[0]);
                it->setY(dest[1]);
                it->setZ(dest[2]);
            }
        }
    }
    // Update anchorPoint
    float anchor[] = {
        anchorPoint.getX(),
        anchorPoint.getY(),
        anchorPoint.getZ(),
        1
    };
    float dest[] = {0, 0, 0, 0};
    
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            dest[i] += matrix[i][j] * anchor[j];
    
    anchorPoint.setX(dest[0]);
    anchorPoint.setY(dest[1]);
    anchorPoint.setZ(dest[2]);
}

/**
 * Translate vectors to the given vertex.
 * @param destination Final point
 */
void ObjModel::translate(ObjVertex destination)
{
    // Calculate dx, dy, dz using the first point as anchor.
    //                               1st object  .  1st face  .  1st vertex
    float dx = destination.getX() - anchorPoint.getX();
    float dy = destination.getY() - anchorPoint.getY();
    float dz = destination.getZ() - anchorPoint.getZ();
    
    float matrix[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    multiplyMatrix(matrix);
}

/**
 * Rotate model in Y axis. User the first point as reference.
 * @param degrees to rotate
 */
void ObjModel::rotateY(float degrees)
{
    float cosR = cos(degrees * PI / 180);
    float sinR = sin(degrees * PI / 180);
    
    float matrix[4][4] = {
        {cosR, 0, sinR, 0},
        {0, 1, 0, 0},
        {sinR*-1, 0, cosR, 0},
        {0, 0, 0, 1}
    };
    
    // Do rotation
    multiplyMatrix(matrix);
}

/**
 * Rotate model in Y axis. User the first point as reference.
 * @param degrees to rotate
 */
void ObjModel::rotateZ(float degrees)
{
    //translate(ObjVertex(0, 0, 0));
    
    float cosR = cos(degrees * PI / 180);
    float sinR = sin(degrees * PI / 180);
    
    float matrix[4][4] = {
        {cosR, sinR*-1, 0, 0},
        {sinR, cosR, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    // Do rotation
    multiplyMatrix(matrix);
    
    // Translate to anchor point
    //translate(anchorPoint);
}

/**
* Scale model.
* @param sx Scale in x
* @param sy Scale in y
* @param sz Scale in z
**/
void ObjModel::scale(float sx, float sy, float sz)
{
    float matrix[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    
    multiplyMatrix(matrix);
}

/**
 * Iterate over vertices and draw them using GL_LINE_STRIP
 **/
void ObjModel::draw()
{
    glColor3f(255, 255, 255);
    for (auto &object : objects)
    {
        for(auto &face : object.getFaces())
        {
            glBegin(GL_LINE_STRIP);
            for(auto &vertex : face)
            {
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
            glEnd();
        }
    }
    
    // Anchor point
    glColor3b(200, 100, 40);
    glBegin(GL_LINE_STRIP);
    glVertex3f(anchorPoint.getX() - 0.2, anchorPoint.getY() - 0.2, anchorPoint.getZ());
    glVertex3f(anchorPoint.getX(), anchorPoint.getY(), anchorPoint.getZ());
    glVertex3f(anchorPoint.getX() + 0.2, anchorPoint.getY() + 0.2, anchorPoint.getZ());
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(anchorPoint.getX() - 0.2, anchorPoint.getY() + 0.2, anchorPoint.getZ());
    glVertex3f(anchorPoint.getX(), anchorPoint.getY(), anchorPoint.getZ());
    glVertex3f(anchorPoint.getX() + 0.2, anchorPoint.getY() - 0.2, anchorPoint.getZ());
    glEnd();

}

/**
 * Detect collision using Axis Aligned Bounding Box
 **/
bool ObjModel::checkCollision(ObjModel obj)
{
    //check the X axis
    if(abs(anchorPoint.getX() - obj.anchorPoint.getX()) < sizeX + obj.getSizeX())
    {
        //check the Y axis
        if(abs(anchorPoint.getY() - obj.anchorPoint.getY()) < sizeY + obj.getSizeY())
        {
            //check the Z axis
            if(abs(anchorPoint.getZ() - obj.anchorPoint.getZ()) < sizeZ + obj.getSizeZ())
            {
                return true;
            }
        }
    }
    
    return false;
}

/**
 * @return size in X axis
 */
float ObjModel::getSizeX()
{
    return sizeX;
}

/**
 * @return size in Y axis
 */
float ObjModel::getSizeY()
{
    return sizeY;
}

/**
 * @return size in Z axis
 */
float ObjModel::getSizeZ()
{
    return sizeX;
}

/**
 * @return objects vector
 **/
vector<ObjObject> ObjModel::getObjects()
{
    return objects;
}
