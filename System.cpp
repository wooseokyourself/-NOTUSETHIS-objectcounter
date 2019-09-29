//
//  System.cpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "System.hpp"

System::System(string videopath)
: Frame(videopath), WhiteDetecting(Frame.origin()), Judging(), Tracking(){
    detectInterval_time = 7;
    count = 0;
    cout << "Which side is inside? Up(0), Down(1) : ";
    cin >> inside;
    ref_midline = 0;
}

void System::Run(){
    while(1){
        time_start = getTickCount();
        
        if(waitKey(20) == 'p'){
            while(waitKey(1) != 'p');
        }
        if(waitKey(1) == 'q'){
            break;
        }
        
        preprocess();
        postprocess();
        
        time_end = getTickCount();
    }
}

void System::preprocess(){
    Frame.ready();
    ref_midline = WhiteDetecting.midline();
    WhiteDetecting.getPixels(Frame.foreground());
}

void System::postprocess(){
    if(Frame.setInfo() % detectInterval_time == 0){ /* Frame.showInfo() returns absFrame */
        Judging.detectPeople(WhiteDetecting.makeROI(Frame.foreground()), Objs);
        /* makeROI() returns vector<ROI>*(<-pointer) */
    }
    Tracking.tracking_and_counting(Frame.origin(), Frame.foreground(), Objs, ref_midline, inside, count); /* renew objects' boxes and count */
    Frame.show(); /* reset absFrame */
}
