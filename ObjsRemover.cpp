//
//  ObjsRemover.cpp
//  src
//
//  Created by ChoiWooSeok on 30/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "ObjsRemover.hpp"

ObjsRemover::ObjsRemover(){
    
}

void ObjsRemover::remove(vector<DetectedObject>& Objs){
    for(int i=0; i<Objs.size(); i++){
        if(onEndpoint(Objs[i])){
            swap(Objs[i], Objs.back());
            Objs.pop_back();
            i++;
            continue;
        }
        for(int j=i; j<Objs.size(); j++){
            if(areOverlapping(Objs[i], Objs[j])){
                swap(Objs[j], Objs.back());
                Objs.pop_back();
                i++;
                j++;
                continue;
            }
        }
    }
}

bool ObjsRemover::onEndpoint(DetectedObject &obj){
    if(){
        return true;
    }
    else
        return false;
}

bool ObjsRemover::areOverlapping(DetectedObject &obj_a, DetectedObject &obj_b){
    if(){
        return true;
    }
    else
        return false;
}
