//
//  WhiteDetector.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef WhiteDetector_hpp
#define WhiteDetector_hpp

#include "default.hpp"
#include "DetectVariables.hpp"
#include "ROI.hpp"

class WhiteDetector{
/* input: origin frame, foreground frame / output: origin frame with ROI's(vector) */
private:
    DetectVariables dtcVar;
    
                    // ------------upper_1--------------
                    // ------------upper_2--------------
                    // ------------upper_3--------------
    uchar* top_1;   // -                               -
    uchar* top_2;   // -                               -
    uchar* top_3;   // ------------midline--------------
    uchar* blw_3;   // -                               -
    uchar* blw_2;   // -                               -
    uchar* blw_1;   // ------------below_3--------------
                    // ------------below_2--------------
                    // ------------below_1--------------
    
    
public:
    WhiteDetector(Mat& frame);
    void getPixels(Mat& foreground);
    vector<ROI>* makeROI(Mat& foreground);
    inline int& midline() {return dtcVar.mid_line;}
    
protected:
    int recursive_ruler(uchar* ptr, int real_x, Mat& foreground);
};

#endif /* WhiteDetector_hpp */
