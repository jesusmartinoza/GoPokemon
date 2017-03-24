//
//  Pokeball.hpp
//  GoPokemon
//
//  Created by Jesús Martínez on 23/03/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#ifndef Pokeball_hpp
#define Pokeball_hpp

#include <stdio.h>
#include "ObjModel.hpp"

class Pokeball: public ObjModel {
private:
    vector<ObjVertex> pathPoints;
    void calculatePath(ObjVertex p1, ObjVertex p4, ObjVertex r1, ObjVertex r4, int n);
public:
    Pokeball();
    Pokeball(std::string fileName);
    vector<ObjVertex> getPathPoints();
};


#endif /* Pokeball_hpp */
