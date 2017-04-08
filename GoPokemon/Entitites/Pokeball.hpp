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
public:
    Pokeball();
    Pokeball(std::string fileName, ObjVertex p1, ObjVertex p4, ObjVertex r1, ObjVertex r4);
    vector<ObjVertex> getPathPoints();
    void setR1(ObjVertex r1);
    void setR4(ObjVertex r4);
    void setP1(ObjVertex p1);
    void calculatePath();
};


#endif /* Pokeball_hpp */
