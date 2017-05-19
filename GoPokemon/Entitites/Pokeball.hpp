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
    ObjVertex p1, p4, r1, r4;
    int n;
    int pathPointIndex;
    int direction;
public:
    Pokeball();
    Pokeball(std::string fileName);
    vector<ObjVertex> getPathPoints();
    void calculatePath();
    bool update();
    void reorderObjects();
};

#endif /* Pokeball_hpp */
