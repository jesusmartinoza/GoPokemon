//
//  ObjObject.cpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#include "ObjObject.hpp"

ObjObject::ObjObject(string name)
{
    this->name = name;
    color.r = 1;
    color.g = 1;
    color.b = 1;
}

vector<ObjFace>& ObjObject::getFaces()
{
    return faces;
}

string ObjObject::getName()
{
    return name;
}

void ObjObject::addFace(ObjFace face)
{
    faces.push_back(face);
}

void ObjObject::setColor(COLOR color)
{
    this->color = color;
}
COLOR & ObjObject::getColor()
{
    return color;
}
