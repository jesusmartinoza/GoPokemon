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

bool ObjFace::isVisible()
{
    return visible;
}

/**
 * Calculate normal using the first 3 points. And determine if the face is visible.
 **/
void ObjFace::calculateNormal()
{
    normal = (vertices.at(1) - vertices.at(0))*(vertices.at(2) - vertices.at(0));
    
    float dotProduct = normal.dot(ObjVertex(0, 0, 11));
    visible = dotProduct >= 0;
}

/**
 * Calculate illumination
 **/
void ObjFace::calculateIllumination()
{
    float k_a = 0.3;
    float k_d = 0.7;
    float I_a = 1.0;
    float I_l = 0.5;
    ObjVertex light = ObjVertex(1, 0, 1);
    normal.normalize();
    
    float prod = normal.dot(light);
    illumination = (I_a * k_a) + (I_l * k_d * prod);
}

/**
 * @return illumination
 **/
float ObjFace::getIllumination() {
    return illumination;
}
