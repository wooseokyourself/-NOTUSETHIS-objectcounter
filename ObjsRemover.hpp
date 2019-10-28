//
//  ObjsRemover.hpp
//  src
//
//  Created by ChoiWooSeok on 30/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef ObjsRemover_hpp
#define ObjsRemover_hpp

#include "DetectedObject.hpp"
#include "DetectVariables.hpp"
#include <vector> 
using namespace std;

class ObjsRemover{
public:
    ObjsRemover();
    void remove(vector<DetectedObject>& Objs, const DetectVariables& vars);
    
protected:
    bool onEndpoint(const DetectedObject& obj, const DetectVariables& vars);
    bool areOverlapping(const DetectedObject& obj_a, const DetectedObject& obj_b);
};

#endif /* ObjsRemover_hpp */
