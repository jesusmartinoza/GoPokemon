//
//  ObjVertex.hpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//  Coordinates of the vertex.
//

#ifndef ObjVertex_hpp
#define ObjVertex_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class ObjVertex {
private:
    float x;
    float y;
    float z;
public:
    ObjVertex();
    ObjVertex(float x, float y, float z);
    void print();
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    float dot(ObjVertex v);
    void normalize();
    ObjVertex operator*(const ObjVertex& v);
    ObjVertex operator-(const ObjVertex& v);

};

#endif /* ObjVertex_hpp */
