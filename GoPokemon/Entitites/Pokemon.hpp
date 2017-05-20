//
//  Pokemon.hpp
//  GoPokemon
//
//  Created by Jesús Martínez on 08/04/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#ifndef Pokemon_hpp
#define Pokemon_hpp

#include <stdio.h>

#include "ObjModel.hpp"

class Pokemon: public ObjModel {
private:
    bool rotateDirection;
public:
    Pokemon();
    Pokemon(std::string fileName);
    bool afraid;
    bool captured;
    void moveLeft();
    void moveRight();
    void update();
    void reorderObjects();
};
#endif /* Pokemon_hpp */
