//
//  System.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <iostream>
#include "FrameHandler.hpp"
#include "WhiteDetector.hpp"
#include "Judge.hpp"
#include "Tracker.hpp"

class System{
public:
    System(string videopath);
    void Run();
protected:
    void preprocess();
    void postprocess();
    
private:
    FrameHandler Frame;
    WhiteDetector WhiteDetecting;
    Judge Judging;
    Tracker Tracking;
    
private:
    vector<DetectedObject> Objs;
    int detectInterval_time;
    int count;
    int inside;
    int64 time_start;
    int64 time_end;
    int ref_midline;
};

#endif /* System_hpp */
