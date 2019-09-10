//
//  DetectedObject.hpp
//  NoDeepLearning
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef DetectedObject_hpp
#define DetectedObject_hpp

#include <opencv2/opencv.hpp>

using namespace cv;

#define upper_area 0
#define below_area 1

class DetectedObject{
private:
    friend class FrameHandler;
    
public:
    Rect box;
    int x;
    int y;
    int width;
    int height;
    int center_x;
    int center_y;
    
    int frame;
    int position;
    
public:
    DetectedObject(int x, int y, int width, int height, int frame, int position);
    // width <- horizon , height <- 2*thold_object_column
    void reset();
};

#endif /* DetectedObject_hpp */
