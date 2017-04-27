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
