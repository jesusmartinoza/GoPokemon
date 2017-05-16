//
//  ObjVertex.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#include "ObjVertex.hpp"
#include <math.h>

ObjVertex::ObjVertex()
{
    
}

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

/**
 * @return Dot product
 **/
float ObjVertex::dot(ObjVertex v)
{
    return (x * v.x) + (y * v.y) + (z * v.z);
}

/**
 * @return Cross product
 **/
ObjVertex ObjVertex::operator*(const ObjVertex& v)
{
    return ObjVertex(y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x);
}

/**
 * @return Substract of vectors
 **/
ObjVertex ObjVertex::operator-(const ObjVertex& v)
{
    return ObjVertex(x - v.x, y - v.y, z - v.z);
}

/**
 * Normal to unit vector
 **/
void ObjVertex::normalize()
{
    float magnitude;
    magnitude = sqrt(x * x +
                     y * y +
                     z * z);
    
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}
