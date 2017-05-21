//
//  ObjObject.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#include "ObjObject.hpp"

/**
 * Constructor default.
 * Set name and color
 **/
ObjObject::ObjObject(string name)
{
    this->name = name;
    color.r = 1;
    color.g = 1;
    color.b = 1;
}

/**
 * @return faces of the object
 **/
vector<ObjFace>& ObjObject::getFaces()
{
    return faces;
}

/**
 * @return object's name
 **/
string ObjObject::getName()
{
    return name;
}

/**
 * Add face to vector
 * @param face new face.
 **/
void ObjObject::addFace(ObjFace face)
{
    faces.push_back(face);
}

/**
 * Set object's color
 **/
void ObjObject::setColor(COLOR color)
{
    this->color = color;
}

/**
 * @return object's color
 **/
COLOR & ObjObject::getColor()
{
    return color;
}
