//
//  ObjFace.hpp
//  GoPokemon
//
//  Created by Jesús Martínez on 27/04/17.
//  Copyright © 2017 Jesús Alberto Martínez Mendoza. All rights reserved.
//

#ifndef ObjFace_hpp
#define ObjFace_hpp

#include <stdio.h>
#include <vector>
#include "ObjVertex.hpp"

using namespace std;

class ObjFace {
private:
    vector<ObjVertex> vertices;
    ObjVertex normal;
    ObjVertex PRP;
    bool visible;
    float illumination;
public:
    ObjFace(vector<ObjVertex> vertices);
    vector<ObjVertex>& getVertices();
    ObjVertex getNormal();
    void calculateNormal();
    float getIllumination();
    void calculateIllumination();
    bool isVisible();
};
#endif /* ObjFace_hpp */
