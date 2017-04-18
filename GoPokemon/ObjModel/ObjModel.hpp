//
//  ObjModel.hpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#ifndef ObjModel_hpp
#define ObjModel_hpp
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <vector>
#include <string>
#include "ObjVertex.hpp"
#include "ObjObject.hpp"

using namespace std;

class ObjModel {
private:
    vector<ObjVertex> vertices; // Cleared at finished reading file.
    vector<ObjObject> objects;
    void multiplyMatrix(float (&matrix)[4][4]);
public:
    ObjModel();
    ObjModel(string fileName);
    vector<const char*> getSplittedLine(const string &line);
    vector<ObjObject> getObjects();
    void print();
    void translate(ObjVertex destination);
    void rotateY(float degrees);
    void scale(float sx, float sy, float sz);
    void draw();
};

#endif /* ObjModel_hpp */
