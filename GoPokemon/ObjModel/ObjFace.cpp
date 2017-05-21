//
//  ObjFace.cpp
//  GoPokemon
//
//  Created by Jesús Martínez on 27/04/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#include "ObjFace.hpp"

using namespace std;

/**
 * Copy constructor
 * The swap method is to copy the @param vector
 **/
ObjFace::ObjFace(vector<ObjVertex> vector)
{
    PRP = ObjVertex(0, 1, 11);
    PRP.normalize();
    vertices.swap(vector);
}

/**
 * @return face vertices
 **/
vector<ObjVertex>& ObjFace::getVertices()
{
    return vertices;
}

/**
 * Setted in calculateNormal
 **/
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
    
    float dotProduct = normal.dot(PRP);
    visible = dotProduct >= 0;
    
    normal.normalize();
}

/**
 * Calculate illumination
 **/
void ObjFace::calculateIllumination()
{
    float k_a = 0.3; // Ambient reflection
    float k_d = 0.7; // Diffuse reflection
    float k_s = 1.0; // Specular reflection
    float I_a = 0.4; // Intensity of ambient light
    float I_l = 0.7;
    ObjVertex light = ObjVertex(0, -1, -1);
    ObjVertex R = ObjVertex(0, 1, -1);
    float specular = R.dot(PRP);
    
    illumination = (I_a * k_a) + (I_l * k_d * normal.dot(light)) + (I_l * k_s * specular * specular);
}

/**
 * @return illumination
 **/
float ObjFace::getIllumination() {
    return illumination;
}
