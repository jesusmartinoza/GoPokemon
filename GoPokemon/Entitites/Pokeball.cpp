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
    this->p1 = ObjVertex(-6, 8, -12);
    this->r1 = ObjVertex(-11, 3, -4);
    this->r4 = ObjVertex(-3, 2, 1);
    this->p4 = ObjVertex(-2, -2, 1);
    pathPointIndex = 0;
}

/**
 * Initialize obj model and create curve points.
 * @param fileName Name of the obj file.
 * @param p1 Start point
 * @param p4 End point
 * @param r1 Control point attached to p1
 * @param r4 Contron point attached to p4
 **/
Pokeball::Pokeball(string fileName, ObjVertex p1, ObjVertex p4, ObjVertex r1, ObjVertex r4)
    :ObjModel(fileName)
{
    this->p1 = p1;
    this->r1 = r1;
    this->r4 = r4;
    this->p4 = p4;
    this->n = 50;
    
    calculatePath();
}

/**
 * Create points using Bezier curve.
 **/
void Pokeball::calculatePath()
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
 * Set control point R1
 */
void Pokeball::setR1(ObjVertex r1)
{
    this->r1 = r1;
}

/**
 * Set control point R4
 */
void Pokeball::setR4(ObjVertex r4)
{
    this->r4 = r4;
}

/**
 * Set bezier curve point P1
 */
void Pokeball::setP1(ObjVertex p1)
{
    this->p1 = p1;
}

/**
 * Return path points.
 **/
vector<ObjVertex> Pokeball::getPathPoints()
{
    return pathPoints;
}

/**
 * Translate pokeball to next path point. Generate new random path when finish. 
 **/
void Pokeball::update()
{
    
    if(++pathPointIndex >= pathPoints.size())
    {
        pathPointIndex =  0;
        r1 = ObjVertex(rand()%10 - rand()%20, rand()%3 - rand()%6, rand()%4 - rand()%8);
        r4 = ObjVertex(rand()%4 - 8, rand()%3 - 4, rand()%2 - 4);
        calculatePath();
    }
    
    ObjVertex dest = pathPoints.at(pathPointIndex);
    translate(dest);
}
