//
//  FrameHandler.cpp
//  NoDeepLearning
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "FrameHandler.hpp"

FrameHandler::FrameHandler(string videopath) : history(500), varThreshold(200), thold_object_width(300), thold_object_height(50), thold_binarization(200), unit_brightness(75), x(0), totalframe(0), k(0), time_start(0), time_end(0), boxwidth_temp(0), recursive_temp1(0), recursive_temp2(0), recursive_temp3(0), counter(0)
{
    cout << "Which side is inside? Up(0), Down(1)" << endl;
    cin >> inside;
    if(inside == upper_area)
        cout << "UP" << endl;
    else if(inside == below_area)
        cout << "DOWN" << endl;
    else{
        cout << "Wrong input. Program exit." << endl;
        exit(1);
    }
    
    cout << "set history (default : 500) : ";
    cin >> history;
    cout << "set varThreshold (default : 200) : ";
    cin >> varThreshold;
    cout << endl;
    cout << "Program will reboot when 'binarization' is 0" << endl;
    
    capture.open(videopath);
    
    pMOG = createBackgroundSubtractorMOG2(history, varThreshold, true);
    // pMOG = createBackgroundSubtractorMOG2(500, 16, false);
    // pMOG = createBackgroundSubtractorKNN();
    
    namedWindow("Frame");
    namedWindow("FG Mask MOG 2");
    
    createTrackbar("Object_Width", "Frame", &thold_object_width, 300); // For controlling the minimum of detection_width.
    
    createTrackbar("Object_Height", "Frame", &thold_object_height, 80); // For controlling the minimum of detection_comlumn.
    
    createTrackbar("Binarization", "Frame", &thold_binarization, 255);
    
    createTrackbar("Brightness", "Frame", &unit_brightness, 150);
    
    //createTrackbar("Play_Position", "Frame", <#int *value#>, <#int count#>);
    
    capture >> frame;
    ratio = frame.cols/thold_detect_cols;
    upperline = frame.rows/10;
    midline = frame.rows/2;
    belowline = frame.rows*9/10;
    
    pMOG->apply(frame, fgMaskMOG2);
    
    cout << frame.cols << " " << frame.rows << endl;
    cout << fgMaskMOG2.cols << " " << fgMaskMOG2.rows << endl;
    
    namedWindow("Scene", WINDOW_AUTOSIZE);
    
    upper_1, upper_2, upper_3, below_3, below_2, below_1 = nullptr;
    
    cout << "Video : " << frame.cols << " X " << frame.rows << endl;
}

FrameHandler::~FrameHandler(){
    if(frame.isContinuous() && fgMaskMOG2.isContinuous()){
        frame.release();
        fgMaskMOG2.release();
        destroyAllWindows();
    }
    Objects.clear();
}

bool FrameHandler::Play(){
    while(waitKey(1) < 0){
        if(!capture.read(frame)){
            cout << "Unable to read next frame." << endl;
            cout << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
        
        frame = frame + Scalar(unit_brightness-75, unit_brightness-75, unit_brightness-75);
        // apply brightness
        
        pMOG->apply(frame, fgMaskMOG2);
        //cvtColor(frame, frame, COLOR_RGB2HSV);
        set_Mask();
        
        stringstream ss;
        rectangle(frame, Point(10, 2), Point(100,20), Scalar(255,255,255), -1);
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
        
        rectangle(frame, Point(10, 20), Point(200, 40), Scalar(255, 255, 255), -1);
        string dude = "COUNTER : " + to_string(counter);
        putText(frame, dude, Point(15, 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
        
        rectangle(frame, Point(10, 40), Point( 10 + thold_object_width, 40 + thold_object_height*2 ), Scalar(255,255,255), 0);
        
        check_endpoint();
        
        if(totalframe % thold_detect_time == 0)
            detection();
        
        tracking_and_counting();
        
        paint_line();
        
        imshow("Frame", frame);
        imshow("FG Mask MOG 2", fgMaskMOG2);
        
        totalframe++;
        if(totalframe == 2000)
            totalframe = 0;
        
        if(totalframe % 50 == 0){
            cout << "EXISTING OBJECT NUMBER  : " << Objects.size() << endl;
            // cout << "NUMBER OF PEOPLE INSIDE : " << counter << endl; // DEBUG ;
        }
        if(thold_binarization == 0){
            return false;
        }
    } // total while
    return true;
}



// UTILITIES


void FrameHandler::set_Mask(){
    blur(fgMaskMOG2, fgMaskMOG2, cv::Size(15, 15), cv::Point(-1, -1));
    // Blur the foreground mask to reduce the effect of noise and false positives
    
    // dilate(fgMaskMOG2, fgMaskMOG2, Mat(), Point(-1, -1), 2, 1, 1);
    
    threshold(fgMaskMOG2, fgMaskMOG2, thold_binarization, 255, cv::THRESH_BINARY);
    // Remove the shadow parts and the noise
    
    upper_1 = fgMaskMOG2.ptr<uchar>(upperline - thold_object_height);
    upper_2 = fgMaskMOG2.ptr<uchar>(upperline);
    upper_3 = fgMaskMOG2.ptr<uchar>(upperline + thold_object_height);
    
    below_3 = fgMaskMOG2.ptr<uchar>(belowline - thold_object_height);
    below_2 = fgMaskMOG2.ptr<uchar>(belowline);
    below_1 = fgMaskMOG2.ptr<uchar>(belowline + thold_object_height);
}

void FrameHandler::check_endpoint(){
    k = 0;
    while(true){ // Check detected boxes are in end point
        if(k >= Objects.size())
            break;
        if(totalframe - Objects[k].frame > thold_detect_time*5){
            // This "if" checks the difference between "object's frame" from "total frame".
            // this difference helps to prevent not removing the box which just created.
            if(Objects[k].center_y <= upperline /*Down-to-Top*/ || Objects[k].center_y >= belowline  /*Top-to-Down*/
               || Objects[k].y == 0 || Objects[k].y + Objects[k].height == frame.rows){
                if(Objects.size() != 0)
                    swap(Objects[k], Objects.back());
                // cout << "Before pop_back, Objects.size() : " << Objects.size() << endl; // Debug ;
                Objects.pop_back();
                // cout << " / After pop_back, Objects.size() : " << Objects.size() << endl; // Debug ;
                continue;
            }
        }
        for(int i=0; i<Objects.size(); i++){
            if(k == i)
                continue;
            if(abs(Objects[k].center_x - Objects[i].center_x) < 3 && abs(Objects[k].center_y - Objects[i].center_y) < 3){
                swap(Objects[k], Objects.back());
                Objects.pop_back();
                cout << "it works!" << endl;
            }
        }
        k++;
    }
}

void FrameHandler::detection(){
    x = 0;
    while(x < thold_detect_cols){
        // This "while" checks "x" from '0' to 'thold_detect_cols'
        // whether (x , upperline +- thold_object_column) pixel is white.
        
        
        ////////////////////////////////////////////////////////
        //      CHECK OVERLAPPING OBJECTS
        ////////////////////////////////////////////////////////
        for(int i=0; i<Objects.size(); i++){
            // This "for" checks if detected object(boxes) is on the "x"
            // If it does, then "x" jumps the box.
            if( (Objects[i].y <= upperline + thold_object_height) || (Objects[i].y + Objects[i].height >= belowline - thold_object_height) ){
                // If some objects(boxes) are on the DETECT line..
                if((Objects[i].x <= x * ratio) && (x * ratio <= Objects[i].x + Objects[i].width)){
                    /*
                     if the "x" is in below situation, move "x" to the next pixel from boxes[i].x + boxes[i].width
                     
                     ooooooooooooooooooooooooooooooooo
                     o                               o
(DETECTLINE)---------o'x'(<-before pos)--------------o'x'(<-after pos)----------(DETECTLINE)
                     o                               o
                     o                               o
                     ..                             ..
                     "boxes[i].x"           "boxes[i].x + boxes[i].width"
                     
                     */
                    // cout << "JUMP; x before : " << x; // Debug ;
                    x += int(Objects[i].width/ratio);
                    // cout << "  /  after : " << x << endl; // Debug ;
                }
            }
        }
        
        ////////////////////////////////////////////////////////
        //      DETECT; UPPER LINE
        ////////////////////////////////////////////////////////
        circle(frame, Point(x * ratio, upperline + thold_object_height), 3, Scalar(0, 0, 255)); // Debug ; to see detected points.
        if(upper_3[x * ratio] == 255){
            if(upper_2[x * ratio] == 255){
                circle(fgMaskMOG2, Point(x * ratio, upperline), 3, Scalar(0, 0, 255)); // Debug ;
                if(upper_1[x * ratio] == 255){
                    // time_start = getTickCount();
                    boxwidth_temp = 0;
                    circle(fgMaskMOG2, Point(x * ratio, upperline + thold_object_height), 3, Scalar(0, 0, 255)); // Debug ;
                    recursive_temp1 = recursive_ruler_x(upper_1, x * ratio, thold_detect_cols);
                    recursive_temp2 = recursive_ruler_x(upper_2, x * ratio, thold_detect_cols);
                    recursive_temp3 = recursive_ruler_x(upper_3, x * ratio, thold_detect_cols);
                    boxwidth_temp = max( max(recursive_temp1, recursive_temp2), recursive_temp3 );
                    if(thold_object_width <= boxwidth_temp){
                        // This "if" checks whether detected object is big enough ; standard is "thold_object_width"
                        MakeBox(x * ratio, upperline - thold_object_height, boxwidth_temp);
                        // cout << "Make box; range(" << thold_object_width <<") <= horizon(" << box_horizon << ")" << endl; // Debug ;
                    }
                    x += int(boxwidth_temp/ratio); // After checking the object, we don't need to check the overlapping pixels, so jump.
                    // time_end = getTickCount();
                    // cout << "detection() time \t\t: " << (time_end - time_start) / getTickFrequency() << endl;
                    continue;
                }
            }
        }
        
        
        ////////////////////////////////////////////////////////
        //      DETECT; BELOW LINE
        ////////////////////////////////////////////////////////
        circle(frame, Point(x * ratio, belowline - thold_object_height), 3, Scalar(0, 0, 255)); // Debug ; to see detected points.
        if(below_3[x * ratio] == 255){
            if(below_2[x * ratio] == 255){
                circle(fgMaskMOG2, Point(x * ratio, belowline), 3, Scalar(0, 0, 255)); // Debug ;
                if(below_1[x * ratio] == 255){
                    // time_start = getTickCount();
                    boxwidth_temp = 0;
                    circle(fgMaskMOG2, Point(x * ratio, belowline + thold_object_height), 3, Scalar(0, 0, 255)); // Debug ;
                    recursive_temp1 = recursive_ruler_x(below_1, x * ratio, thold_detect_cols);
                    recursive_temp2 = recursive_ruler_x(below_2, x * ratio, thold_detect_cols);
                    recursive_temp3 = recursive_ruler_x(below_3, x * ratio, thold_detect_cols);
                    boxwidth_temp = max( max(recursive_temp1, recursive_temp2), recursive_temp3 );
                    if(thold_object_width <= boxwidth_temp){
                        // This "if" checks whether detected object is big enough ; standard is "thold_object_width"
                        MakeBox(x * ratio, belowline - thold_object_height, boxwidth_temp);
                        // cout << "Make box; range(" << thold_object_width <<") <= horizon(" << box_horizon << ")" << endl; // Debug ;
                    }
                    x += int(boxwidth_temp/ratio); // After checking the object, we don't need to check the overlapping pixels, so jump.
                    // time_end = getTickCount();
                    // cout << "detection() time \t\t: " << (time_end - time_start) / getTickFrequency() << endl;
                    continue;
                }
            }
        }
        x++;
    } // "while" for DETECT
}

void FrameHandler::tracking_and_counting(){
    string cor_a, cor_b;
    for(int i=0; i<Objects.size(); i++){
        // time_start = getTickCount();
        
        ////////////////////// CAM SHIFT ///////////////////////
        RotatedRect tracker = CamShift(fgMaskMOG2, Objects[i].box, TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));
        // boxes[i] is delivered as it's reference; CamShift renews the boxes[i]'s position.
        ellipse( frame, tracker, Scalar(0,0,255), 3, LINE_AA ); // Tracking; renew Objects[i].box
        ////////////////////////////////////////////////////////
    
        
        ////////////////////// MEAN SHIFT //////////////////////
        // meanShift(fgMaskMOG2, Objects[i].box, TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));
        // rectangle(frame, Objects[i].box, Scalar(0, 255, 0));
        ////////////////////////////////////////////////////////
        
        Objects[i].reset();
        
        cor_a = to_string(Objects[i].y);
        cor_b = to_string(Objects[i].y + Objects[i].height);
        
        rectangle(frame, Point(Objects[i].x, Objects[i].y), Point(Objects[i].x + 50, Objects[i].y + 18), Scalar(255,255,255), -1);
        rectangle(frame, Point(Objects[i].x + Objects[i].width, Objects[i].y + Objects[i].height), Point(Objects[i].x + Objects[i].width + 50, Objects[i].y + Objects[i].height + 18), Scalar(255,255,255), -1);
        putText(frame, cor_a, Point(Objects[i].x, Objects[i].y), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
        putText(frame, cor_b, Point(Objects[i].x + Objects[i].width, Objects[i].y + Objects[i].height), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
        
        if( (Objects[i].position == upper_area) && (Objects[i].center_y > midline) ){
            Objects[i].position = below_area;
            cout << "\t\t\t >> DETECT OBJECT, Up to Down." << endl;
            if(inside == upper_area)
                counter--;
            else
                counter++;
        }
        if( (Objects[i].position == below_area) && (Objects[i].center_y < midline) ){
            Objects[i].position = upper_area;
            cout << "\t\t\t >> DETECT OBJECT, Down to Up." << endl;
            if(inside == upper_area)
                counter++;
            else
                counter--;
        }
        // time_end = getTickCount();
        // cout << "tracking_and_counting() time : " << (time_end - time_start) / getTickFrequency() << endl;
    }
}

void FrameHandler::paint_line(){
    // VISUAL DETECT LINE ; UPPER
    line(frame, Point(0, upperline - thold_object_height), Point(frame.cols, upperline - thold_object_height), Scalar(255, 0, 0));
    line(frame, Point(0, upperline),                       Point(frame.cols, upperline),                       Scalar(255, 0, 0)); // UPPER LINE
    line(frame, Point(0, upperline + thold_object_height), Point(frame.cols, upperline + thold_object_height), Scalar(255, 0, 0));
    
    // VISUAL DETECT LINE ; MIDDLE
    line(frame, Point(0, midline),                         Point(frame.cols, midline),                         Scalar(0, 0, 255));
    
    // VISUAL DETECT LINE ; BELOW
    line(frame, Point(0, belowline + thold_object_height), Point(frame.cols, belowline + thold_object_height), Scalar(255, 0, 0));
    line(frame, Point(0, belowline),                       Point(frame.cols, belowline),                       Scalar(255, 0, 0)); // BELOW LINE
    line(frame, Point(0, belowline - thold_object_height), Point(frame.cols, belowline - thold_object_height), Scalar(255, 0, 0));
}

int FrameHandler::recursive_ruler_x(uchar* ptr, int start, const int& interval){
    if(ptr[start] < 255){
        return interval;
    }
    else{
        return recursive_ruler_x(ptr, start + interval, interval) + interval;
    }
}

void FrameHandler::MakeBox(int x, int y, int horizon){
    if( (Objects.size() > 0) && (totalframe - Objects.back().frame <= 10*thold_detect_time) ){
        // This "if" checks whether this box is detected previous box's object(by frame).
        // If does, delete the previous box.
        if( (x < (Objects.back().center_x)) && ((Objects.back().center_x) < (x + horizon)) ){
            Objects.pop_back();
        }
    }
    
    if(y < frame.rows/2)
        Objects.push_back( DetectedObject(x, y, horizon, 2*thold_object_height, totalframe, upper_area) );
    else
        Objects.push_back( DetectedObject(x, y, horizon, 2*thold_object_height, totalframe, below_area) );
    
    rectangle(frame, Objects.back().box, Scalar(0, 255, 0));
    
}
