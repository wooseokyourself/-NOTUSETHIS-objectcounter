//
//  ROI.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef ROI_hpp
#define ROI_hpp

#include <opencv2/opencv.hpp>

class ROI{
private:
    cv::Rect* box;
public:
    ROI(int center_x, int center_y, int width, int height);
    ~ROI();
    inline cv::Rect& rect() {return *box;}
    inline int x()          {return box->x;}
    inline int y()          {return box->y;}
    inline int width()      {return box->width;}
    inline int height()     {return box->height;}
    inline int half_width() {return box->width/2;}
    inline int half_height(){return box->height/2;}
    inline int center_x()   {return box->x - box->width/2;}
    inline int center_y()   {return box->y - box->height/2;}
};

#endif /* ROI_hpp */
