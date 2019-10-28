//
//  DetectedObject.hpp
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
    Rect* box;
    
    int frame;
    int position;
    
    int prev_position_x;
    int prev_position_y;
    
public:
    DetectedObject(int center_x, int center_y, int half_width, int half_height, int frame, int position);
    DetectedObject(Point center, int half_width, int half_height, int frame, int position);
    ~DetectedObject();
    inline int center_x()   {return box->x + box->width/2;}
    inline int center_y()   {return box->y + box->height/2;}
    inline Rect& rect()     {return *box;}
    inline int& pos()       {return position;}
};

#endif /* DetectedObject_hpp */
