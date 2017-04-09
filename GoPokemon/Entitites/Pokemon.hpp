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
public:
    Pokemon();
    Pokemon(std::string fileName);
    void moveLeft();
    void moveRight();
};
#endif /* Pokemon_hpp */
