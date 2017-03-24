//
//  Pokeball.cpp
//  GoPokemon
//
//  Created by Jesús Martínez on 23/03/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#include "Pokeball.hpp"

using namespace std;

/**
 * Default constructor.
 **/
Pokeball::Pokeball()
{
    
}

/**
 * Initialize obj model and create curve points.
 **/
Pokeball::Pokeball(string fileName):ObjModel(fileName)
{
    ObjVertex p1 = ObjVertex(-4, 0, 0);
    ObjVertex r1 = ObjVertex(-4, -2, 0);
    ObjVertex r4 = ObjVertex(4, 2, 0);
    ObjVertex p4 = ObjVertex(4, 0, 0);
    
    calculatePath(p1, p4, r1, r4, 40);
}

/**
 * Create points using Bezier curve.
 * @param p1 Start point
 * @param p4 End point
 * @param r1 Control point attached to p1
 * @param r4 Contron point attached to p4
 **/
void Pokeball::calculatePath(ObjVertex p1, ObjVertex p4, ObjVertex r1, ObjVertex r4, int n)
{
    float d = 1.0f/n;
    
    for(float t = 0; t <= 1; t+=d)
    {
        float ct = (1-t);
        float ct2 = ct * ct;
        float ct3 = ct2 * ct;
        float t2 = t*t;
        float t3 = t2*t;
        
        float c2 = 3*t*ct2;
        float c3 = 3*t2*ct;
        
        float x = ct3*p1.getX() + c2*r1.getX() + c3*r4.getX() + t3*p4.getX();
        float y = ct3*p1.getY() + c2*r1.getY() + c3*r4.getY() + t3*p4.getY();
        float z = ct3*p1.getZ() + c2*r1.getZ() + c3*r4.getZ() + t3*p4.getZ();
        
        pathPoints.push_back(ObjVertex(x, y, z));
    }
}

/**
 * Return path points.
 **/
vector<ObjVertex> Pokeball::getPathPoints()
{
    return pathPoints;
}
