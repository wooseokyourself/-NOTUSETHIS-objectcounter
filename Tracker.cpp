//
//  Tracker.cpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "Tracker.hpp"

Tracker::Tracker(){
    
}

void Tracker::tracking_and_counting(Mat& origin, Mat &foreground, vector<DetectedObject> &Objs, const int& midline, const int& inside, int& count){ /* tracking, counting, and draw rectangles of tracked Objs */
    if(Objs.size() != 0){
        for(int i=0; i<Objs.size(); i++){
            meanShift(foreground, Objs[i].rect(), TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
            /* notice that the tracking algorithm works in foreground frame */
            rectangle(origin, Objs[i].rect(), Scalar(0, 255, 0), 3);
            
            if(Objs[i].pos() == upper_area && Objs[i].center_y() > midline){
                Objs[i].pos() = below_area;
                cout << "\t >> IN" << endl;
                if(inside == upper_area)
                    count --;
                else
                    count ++;
            }
            if(Objs[i].pos() == below_area && Objs[i].center_y() < midline){
                Objs[i].pos() = upper_area;
                cout << "\t >> OUT" << endl;
                if(inside == upper_area)
                    count ++;
                else
                    count --;
            }
        }
    }
}
