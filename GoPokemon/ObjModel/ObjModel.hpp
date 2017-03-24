//
//  ObjModel.hpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//

#ifndef ObjModel_hpp
#define ObjModel_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "ObjVertex.hpp"
#include "ObjObject.hpp"

using namespace std;

class ObjModel {
private:
    vector<ObjVertex> vertices;
    vector<ObjObject> objects;
public:
    ObjModel();
    ObjModel(string fileName);
    vector<const char*> getSplittedLine(const string &line);
    vector<ObjVertex> getVertices();
    vector<ObjObject> getObjects();
    void print();
};

#endif /* ObjModel_hpp */
