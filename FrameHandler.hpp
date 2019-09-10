//
//  FrameHandler.hpp
//  NoDeepLearning
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef FrameHandler_hpp
#define FrameHandler_hpp

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "DetectedObject.hpp"

#define thold_detect_cols 50
#define thold_detect_time 5

using namespace cv;
using namespace std;

class FrameHandler{
private:
    int history;
    int varThreshold;
    
    int counter;
    int inside; // UP(0) or DOWN(1)
    
    VideoCapture capture;
    Mat frame;
    Mat fgMaskMOG2;
    Ptr<BackgroundSubtractor> pMOG;
    
    int ratio;
    int thold_object_width;
    int thold_object_height;
    int thold_binarization;
    int unit_brightness;
    
    int upperline;
    int midline;
    int belowline;
    
    uchar* upper_1;
    uchar* upper_2;
    uchar* upper_3;
    
    uchar* below_3;
    uchar* below_2;
    uchar* below_1;
    
    int x;
    
    int totalframe;
    
    vector<DetectedObject> Objects;
    
    int64 time_start;
    int64 time_end;
    
private: // Used only for methods
    int k;
    int boxwidth_temp;
    int recursive_temp1;
    int recursive_temp2;
    int recursive_temp3;
    
public:
    FrameHandler(string videopath);
    ~FrameHandler();
    bool Play();
    
protected:
    void set_Mask();
    void check_endpoint();
    void detection();
    void tracking_and_counting();
    void paint_line();
    
protected:
    int recursive_ruler_x(uchar* ptr, int start, const int& interval);
    void MakeBox(int x, int y, int horizon);
};

#endif /* FrameHandler_hpp */
