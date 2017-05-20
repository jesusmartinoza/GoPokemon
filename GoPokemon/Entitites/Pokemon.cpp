//
//  Pokemon.cpp
//  GoPokemon
//
//  Created by Jesús Martínez on 08/04/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#include "Pokemon.hpp"

/**
 * Default constructor
 **/
Pokemon::Pokemon()
{
}

/**
 * Init obj model
 **/
Pokemon::Pokemon(string fileName):ObjModel(fileName)
{
    captured = false;
    afraid = false;
    
    rotateY(180);
    translate(ObjVertex(0.3, -1.8, 4.7));
    reorderObjects();
}

void Pokemon::moveLeft()
{
    ObjVertex dest = anchorPoint;
    if(dest.getX() > -2) {
        //rotateY(1.4);
        dest.setX(dest.getX() - 0.3);
        translate(dest);
    }
}

void Pokemon::moveRight()
{
    ObjVertex dest = anchorPoint;
    if(dest.getX() < 2) {
        //rotateY(-1.4);
        dest.setX(dest.getX() + 0.3);
        translate(dest);
    }
}

/**
 * Capture the pokemon
 **/
void Pokemon::update()
{
    if(captured)
    {
        scale(0.97, 0.97, 0.97);
    }
   
    if(afraid && rand()%2)
    {
        if(rotateDirection) {
            rotateZ(-0.8);
        } else {
            rotateZ(0.8);
        }
        rotateDirection = !rotateDirection;
    }
}

/**
 * Reorder obj to draw correctly.
 * Squirtle's shield between body and tail.
 **/
void Pokemon::reorderObjects()
{
    reorderObject(0, 1);
    
}
