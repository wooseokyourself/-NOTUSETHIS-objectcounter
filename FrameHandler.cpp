//
//  FrameHandler.cpp
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "FrameHandler.hpp"

FrameHandler::FrameHandler(string videopath)
: imgVar(), absframe(0){
    int capture_type;
    cout << "Capture type(1: video input / 0: Cam) : "; cin >> capture_type;
    if(capture_type == 1)
        capture.open(videopath);
    else if(capture_type == 0)
        capture.open(-1);
    else{
        cout << "Wrong input." << endl;
        exit(1);
    }
    
    pMOG = createBackgroundSubtractorMOG2(imgVar.MOG2_history, imgVar.MOG2_varThreshold, true);
    
    namedWindow("Origin");
    namedWindow("ForeGround");
    
    capture >> origin_frame;
    pMOG->apply(origin_frame, foreground_frame);
}

void FrameHandler::ready(){ /* get frame from videoCapture, set foreground */
    capture >> origin_frame;
    if(origin_frame.empty()){
        cout << "Unable to read next frame." << endl;
        cout << "Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    
    pMOG->apply(origin_frame, foreground_frame);
    blur(foreground_frame, foreground_frame, Size(15, 15), Point(-1, -1));
    threshold(foreground_frame, foreground_frame, imgVar.bin, 255, cv::THRESH_BINARY);
}

int FrameHandler::setInfo(){ /* returns absFrame */
    absframe++;
    
    stringstream ss;
    rectangle(origin_frame, Point(10, 2), Point(100,20), Scalar(255,255,255), -1);
    ss << capture.get(CAP_PROP_POS_FRAMES);
    string frameNumberString = ss.str();
    putText(origin_frame, frameNumberString.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
    
    // rectangle(origin_frame, Point(10, 20), Point(200, 40), Scalar(255, 255, 255), -1);
    // string dude = "COUNTER : " + to_string(counter);
    // putText(origin_frame, dude, Point(15, 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
    
    if(absframe == 2000)
        absframe = 0;
    
    return absframe;
}

void FrameHandler::show(){
    imshow("Origin", origin_frame);
    imshow("ForeGround", foreground_frame);
}
