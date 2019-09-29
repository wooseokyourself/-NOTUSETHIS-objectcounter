//
//  ROI.cpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "ROI.hpp"

ROI::ROI(int center_x, int center_y, int width, int height){
    box = new cv::Rect(center_x - width/2, center_y - height/2, width, height);
}

ROI::~ROI(){
    delete box;
}
