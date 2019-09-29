//
//  FrameHandler.hpp
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef FrameHandler_hpp
#define FrameHandler_hpp

#include "default.hpp"
#include "ImageVariables.hpp"

class FrameHandler{
private:
    ImageVariables imgVar;
    VideoCapture capture;
    Mat origin_frame;
    Mat foreground_frame;
    Ptr<BackgroundSubtractor> pMOG;
    
    int absframe;
    
public:
    FrameHandler(string videopath);
    inline Mat& origin()        {return origin_frame;}
    inline Mat& foreground()    {return foreground_frame;}
    void ready();
    int setInfo();
    void show();
};

#endif /* FrameHandler_hpp */
