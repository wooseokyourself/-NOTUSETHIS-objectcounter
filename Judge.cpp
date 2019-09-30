//
//  Judge.cpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "Judge.hpp"

Judge::Judge(){
    
}

void Judge::detectPeople(Mat& origin, vector<ROI> *ROIs, vector<DetectedObject> &Objs, int absFrame, const int& ref_midline){ /* find people in ROIs vector and push into Objs vector */
    
    int abs_x, abs_y;
    Mat ROI;
    vector<Vec3f> circles;
    
    /*
     ROIs 를 순회하는 한 번의 task에 대해..
     ROIs 벡터로부터 가져온 정보 + origin_frame 으로 Mat ROI 제작.
     이후 이 Mat ROI를 input으로 HoughCircle에 집어넣기, 여기에서 원이 0개 혹은 3개 이상이라면 ROI벡터.pop() 및 continue
     원이 1개 혹은 2개라면 그 원의 (center_x, center_y, 반지름, 반지름, absFrame, position)을 input으로 Objs.push_back() 및 ROI벡터.pop() 및 continue
     이 때 Objs의
     
     */
    for(int i=ROIs->size(); i<0; i--){ /* traverse from back to front in order to pop_back */
        /*
         ROIs <-- addr of vector
         *ROIs <-- real verctor
         (*ROIs)[i] <-- indexing of vector
         */
        abs_x = (*ROIs)[i].x();
        abs_y = (*ROIs)[i].y();
        ROI = origin( (*ROIs)[i].rect() ); /* get Mat ROI from origin_frame */
        medianBlur(ROI, ROI, 5);
        cvtColor(ROI, ROI, COLOR_BGR2GRAY);
        
        /*
         Objs' center cordinate on origin_frame is (abs_x + circle_x, abs_y + circle_y)
         
        if(FindCircleAlgorithm(Mat ROI) == true){
            Objs.push_back( DetectedObject(abs_x + circle_x, abs_y + circle_y, circle_radius, circle_radius, absFrame, position) );
        }
         */
        HoughCircles(ROI, circles, HOUGH_GRADIENT, 1, ROI.rows/3, 200, 10, 0, 0);
        /*
         args: (InputArray image, OutputArray circles, int method,
        double     @dp
            Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
        double     @minDist
            Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
        double     @param1 = 100
            First method-specific parameter. In case of HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny edge detector (the lower one is twice smaller).
        double     @param2 = 100
            Second method-specific parameter. In case of HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
        int     @minRadius = 0
        int     @maxRadius = 0
        )
         */
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Vec3i c = circles[i];
            Point center = Point(c[0] + abs_x, c[1] + abs_y);
            int radius = c[2];
            if(center.y > ref_midline)
                Objs.push_back( DetectedObject(center, radius, radius, absFrame, below_area) );
            else
                Objs.push_back( DetectedObject(center, radius, radius, absFrame, upper_area));
        }
        
        ROIs->pop_back();
    }

    delete ROIs;
}
