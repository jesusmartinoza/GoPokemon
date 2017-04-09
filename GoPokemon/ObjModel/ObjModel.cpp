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
        vertices.clear();
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
 * @return objects vector
 **/
vector<ObjObject> ObjModel::getObjects()
{
    return objects;
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
 * Translate vectors to the given vertex.
 * @param destination Final point
 */
void ObjModel::translate(ObjVertex destination)
{
    // Calculate dx, dy, dz using the first point as anchor.
    //                               1st object  .  1st face  .  1st vertex
    float dx = destination.getX() - objects.at(0).getFaces().at(0).at(0).getX();
    float dy = destination.getY() - objects.at(0).getFaces().at(0).at(0).getY();
    float dz = destination.getZ() - objects.at(0).getFaces().at(0).at(0).getZ();
    
    vector<ObjVertex>::iterator it;
    float matrix[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    
    for (auto &object : objects)
    {
        for(auto &face : object.getFaces())
        {
            for(it = face.begin(); it < face.end(); it++)
            {
                float origin[] = {
                    it->getX(),
                    it->getY(),
                    it->getZ()
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
}

/**
* Scale model.
* @param sx Scale in x
* @param sy Scale in y
* @param sz Scale in z
**/
void ObjModel::scale(float sx, float sy, float sz)
{
    vector<ObjVertex>::iterator it;
    float matrix[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    
    for (auto &object : objects)
    {
        for(auto &face : object.getFaces())
        {
            for(it = face.begin(); it < face.end(); it++)
            {
                float origin[] = {
                    it->getX(),
                    it->getY(),
                    it->getZ()
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
}

/**
 * Iterate over vertices and draw them using GL_LINE_STRIP
 **/
void ObjModel::draw()
{
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
}
