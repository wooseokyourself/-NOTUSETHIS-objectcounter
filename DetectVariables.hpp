//
//  DetectVariables.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef DetectVariables_hpp
#define DetectVariables_hpp

#include <iostream>
#include "WhiteDetector.hpp"

class DetectVariables{
    friend class WhiteDetector;
    
private:
    int top_line;
    int mid_line;
    int btm_line;
    int detect_time;

    int min_width;
    int min_height;
    int roi_width;
    int roi_height;
    int detectInterval_cols; // 줄 위아래 간격
    int detectInterval_rows; // 줄당 point 간격
    
public:
    DetectVariables(Mat& frame){
        top_line = frame.rows/10;
        mid_line = frame.rows/2;
        btm_line = frame.rows*9/10;
        
        cout << "Detect variables set" << endl;
        cout << "min_width : "; cin >> min_width;
        cout << "min_height : "; cin >> min_height;
        cout << "roi_width : "; cin >> roi_width;
        cout << "roi_height : "; cin >> roi_height;
        cout << "detect_time : "; cin >> detect_time;
        cout << "detectInterval_cols : "; cin >> detectInterval_cols;
        cout << "detectInterval_rows : "; cin >> detectInterval_rows;
        
    }
};

#endif /* DetectVariables_hpp */
