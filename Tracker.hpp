//
//  Tracker.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef Tracker_hpp
#define Tracker_hpp

#include <vector>
#include <opencv2/opencv.hpp>
#include "DetectedObject.hpp"

using namespace std;
using namespace cv;

class Tracker{
/* input: origin frame with detected boxes / output: renew the boxes in the frame */
public:
    Tracker();
    void tracking_and_counting(Mat& origin, Mat& foreground, vector<DetectedObject>& Objs, const int& midline, const int& inside, int& count);
    
private:
    
};

#endif /* Tracker_hpp */
