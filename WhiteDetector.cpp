//
//  WhiteDetector.cpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "WhiteDetector.hpp"

WhiteDetector::WhiteDetector(Mat& frame)
: dtcVar(frame){
    top_1 = nullptr;
    top_2 = nullptr;
    top_3 = nullptr;
    btm_1 = nullptr;
    btm_2 = nullptr;
    btm_3 = nullptr;
}

void WhiteDetector::getPixels(Mat &foreground){ /* get ptrs to access each pixels of a frame */
    top_1 = foreground.ptr<uchar>(dtcVar.top_line - dtcVar.detectInterval_rows);
    top_2 = foreground.ptr<uchar>(dtcVar.top_line);
    top_3 = foreground.ptr<uchar>(dtcVar.top_line + dtcVar.detectInterval_rows);
    
    btm_3 = foreground.ptr<uchar>(dtcVar.btm_line - dtcVar.detectInterval_rows);
    btm_2 = foreground.ptr<uchar>(dtcVar.btm_line);
    btm_1 = foreground.ptr<uchar>(dtcVar.btm_line + dtcVar.detectInterval_rows);
}

vector<ROI>* WhiteDetector::makeROI(Mat &foreground){
    int x;
    int ratio = foreground.cols / dtcVar.detectInterval_cols;
    /* (x * ratio) = (real cordinate x in image) */
    
    int length_1, length_2, length_3;
    
    vector<ROI>* ROIs = new vector<ROI>;
    
    /*
     The two "while"s checks "x(from '0' to 'thold_detect_cols')"
     whether (x , upperline +- thold_object_column) pixel is white.
     The first checks only on upperline, and the second checks only in belowline.
     The "for"s in each "while" checks if detected object(boxes) is on the "x".
     If it does, then "x" jumps the box.
     (In this "for", if the "x" is in below situation, move "x" to the next pixel from boxes[i].x + boxes[i].width)
     
                          ooooooooooooooooooooooooooooooooo
                          o                               o
     (DETECTLINE)---------o'x'(<-before pos)--------------o'x'(<-after pos)----------(DETECTLINE)
                          o                               o
                          o                               o
                          ..                             ..
                    "boxes[i].x"           "boxes[i].x + boxes[i].width"
    */
    
    /* Find ROI on top line */
    x = 0;
    while(true){ /* counting variable is 'x' */
        if(x > dtcVar.detectInterval_cols)
            break;
        else{
            if(top_1[x * ratio] == 255){
                if(top_2[x * ratio] == 255){
                    if(top_3[x * ratio] == 255){
                        length_1 = recursive_ruler(top_1, x * ratio, foreground);
                        length_2 = recursive_ruler(top_2, x * ratio, foreground);
                        length_3 = recursive_ruler(top_3, x * ratio, foreground);
                        if(length_2 >= length_1 && length_2 >= length_3){ /* make ROI only when length_2 has the highest length */
                            if(length_2 >= dtcVar.min_width){
                                ROIs->push_back(ROI(x*ratio + length_2/2, dtcVar.top_line, dtcVar.roi_width, dtcVar.roi_height));
                                /* MakeBox(x * ratio, ) */
                            }
                            x += int(length_2/ratio);
                        }
                        else
                            x += int(length_2/ratio);
                    }
                }
            }
            x++;
        }
    }
    
    /* Find ROI on bottom line */
    x = 0;
    while(true){ /* counting variable is 'x' */
        if(x > dtcVar.detectInterval_cols)
            break;
        else{
            if(btm_1[x * ratio] == 255){
                if(btm_2[x * ratio] == 255){
                    if(btm_3[x * ratio] == 255){
                        length_1 = recursive_ruler(btm_1, x * ratio, foreground);
                        length_2 = recursive_ruler(btm_2, x * ratio, foreground);
                        length_3 = recursive_ruler(btm_3, x * ratio, foreground);
                        if(length_2 >= length_1 && length_2 >= length_3){ /* make ROI only when length_2 has the highest length */
                            if(length_2 >= dtcVar.min_width){
                                ROIs->push_back(ROI(x*ratio + length_2/2, dtcVar.btm_line, dtcVar.roi_width, dtcVar.roi_height));
                                /* MakeBox(x * ratio, ) */
                            }
                            x += int(length_2/ratio);
                        }
                        else
                            x += int(length_2/ratio);
                    }
                }
            }
            x++;
        }
    }
    
    return ROIs;
}

int WhiteDetector::recursive_ruler(uchar *ptr, int start, Mat &foreground){
    if(ptr[start] < 255) /* end condition */
        return dtcVar.detectInterval_cols;
    else
        return recursive_ruler(ptr, start + dtcVar.detectInterval_cols, foreground) + dtcVar.detectInterval_cols;
}
