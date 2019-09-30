//
//  Judge.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef Judge_hpp
#define Judge_hpp

#include "ROI.hpp"
#include "DetectedObject.hpp"
#include "vector"
using namespace std;

class Judge{
/* input: origin frame with ROI's / output: origin frame with detected boxes */
public:
    Judge();
    void detectPeople(Mat& origin, vector<ROI>* ROIs, vector<DetectedObject>& Objs, int absFrame, const int& ref_midline);
};

#endif /* Judge_hpp */
