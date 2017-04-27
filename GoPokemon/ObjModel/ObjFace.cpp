//
//  ObjFace.cpp
//  GoPokemon
//
//  Created by Jesús Martínez on 27/04/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#include "ObjFace.hpp"

using namespace std;

ObjFace::ObjFace(vector<ObjVertex> vector)
{
    vertices.swap(vector);
}

vector<ObjVertex>& ObjFace::getVertices()
{
    return vertices;
}
