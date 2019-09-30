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
#include "vector"
using namespace std;

class ObjsRemover{
public:
    ObjsRemover();
    void remove(vector<DetectedObject>& Objs);
    
protected:
    bool onEndpoint(DetectedObject& obj);
    bool areOverlapping(DetectedObject& obj_a, DetectedObject& obj_b);
};

#endif /* ObjsRemover_hpp */
