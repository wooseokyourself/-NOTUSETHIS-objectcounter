//
//  DetectedObject.cpp
//  NoDeepLearning
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "DetectedObject.hpp"

DetectedObject::DetectedObject(int x, int y, int width, int height, int frame, int position)
: box(x, y, width, height), frame(frame), position(position){
    x = box.x;
    y = box.y;
    width = box.width;
    height = box.height;
    center_x = x + width/2;
    center_y = y + height/2;
}

void DetectedObject::reset(){
    x = box.x;
    y = box.y;
    width = box.width;
    height = box.height;
    center_x = x + width/2;
    center_y = y + height/2;
}
