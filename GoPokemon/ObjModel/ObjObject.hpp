//
//  ObjObject.hpp
//  ObjReader
//
//  Created by Jesús Martínez on 16/02/17.
//  name is label of the object.
//  faces is a vector with the indexes of the vertices.
//

#ifndef ObjObject_hpp
#define ObjObject_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "ObjFace.hpp"

using namespace std;

class ObjObject {
private:
    string name;
    
    vector<ObjFace> faces;
public:
    ObjObject(string name);
    string getName();
    void addFaceVector(vector<int> faceVector);
    vector<ObjFace>& getFaces();
    void addFace(ObjFace face);
};

#endif /*ObjObject_hpp */
