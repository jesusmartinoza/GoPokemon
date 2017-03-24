//
//  ObjVertex.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#include "ObjVertex.hpp"

ObjVertex::ObjVertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float ObjVertex::getX()
{
    return x;
}

float ObjVertex::getY()
{
    return y;
}

float ObjVertex::getZ()
{
    return z;
}

void ObjVertex::setX(float x)
{
    this->x = x;
}

void ObjVertex::setY(float y)
{
    this->y = y;
}

void ObjVertex::setZ(float z)
{
    this->z = z;
}

void ObjVertex::print()
{
    std::cout << x << " " << y << " " << z << std::endl;
}
