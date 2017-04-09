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
    
}

void Pokemon::moveLeft()
{
    ObjVertex dest = getObjects().at(0).getFaces().at(0).at(0);
    dest.setX(dest.getX() - 0.3);
    translate(dest);
}

void Pokemon::moveRight()
{
    ObjVertex dest = getObjects().at(0).getFaces().at(0).at(0);
    dest.setX(dest.getX() + 0.3);
    translate(dest);
}
