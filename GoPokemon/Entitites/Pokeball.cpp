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
    this->p1 = ObjVertex(-6, 12, -20);
    this->r1 = ObjVertex(-11, 3, -4);
    this->r4 = ObjVertex(-3, 2, 1);
    this->p4 = ObjVertex(-2, -5, 10);
    this->n = 80;
}

/**
 * Initialize obj model and create curve points.
 * @param fileName Name of the obj file.
 **/
Pokeball::Pokeball(string fileName)
    :ObjModel(fileName)
{
    this->p1 = ObjVertex(0, 12, -20);
    this->r1 = ObjVertex(-11, 3, -4);
    this->r4 = ObjVertex(-3, 2, 1);
    this->p4 = ObjVertex(-2, -5, 10);
    this->n = 80;
    
    calculatePath();
    scale(0.6, 0.6, 0.6);
}

/**
 * Create points using Bezier curve.
 **/
void Pokeball::calculatePath()
{
     // Reset path
    pathPointIndex = 0;
    pathPoints.clear();
    
    // Random path
    int factor = rand()%4;
    int factor2 = rand()%10;
    int factor3 = rand()%3;
    int factor4 = rand()%5;
    if((direction = rand() % 2))  // To right
    {
        this->p4 = ObjVertex(factor, -5, 9);
        this->r1 = ObjVertex(factor + factor2, 3, -4);
        this->r4 = ObjVertex(factor - factor4, 2, 3 + factor3);
    } else {
        factor *= -1;
        this->p4 = ObjVertex(factor, -5, 9);
        this->r1 = ObjVertex(factor - factor2, 3, -4);
        this->r4 = ObjVertex(factor + factor4, 2, 3 - factor3);
    }
    
    // Calculate path.
    this->n -= n > 50 ? 1 : 0;
    
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

/**
 * Translate pokeball to next path point. Generate new random path when finish. 
 **/
bool Pokeball::update()
{
    // Rotate every 10 points
    if(pathPointIndex < 50 && pathPointIndex % 4) {
        rotateY((80 - pathPointIndex)/3);
        rotateY(rand()%7);
    }
    
    ObjVertex dest = pathPoints.at(pathPointIndex);
    translate(dest);
    
    if(++pathPointIndex >= pathPoints.size()) {
        calculatePath();
        return true;
    }
    
    return false;
}
