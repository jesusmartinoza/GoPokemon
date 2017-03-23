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

void ObjObject::addFaceVector(vector<int> faceVector)
{
    this->faces.push_back(faceVector);
}

vector<vector<int> >& ObjObject::getFaces()
{
    return faces;
}

string ObjObject::getName()
{
    return name;
}
