//
//  DetectedObject.cpp
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "DetectedObject.hpp"


DetectedObject::DetectedObject(int center_x, int center_y, int half_width, int half_height, int frame, int position)
: frame(frame), position(position){
    box = new Rect(center_x - half_width, center_y - half_height, half_width*2, half_height*2);
}

DetectedObject::~DetectedObject(){
    delete box;
}
