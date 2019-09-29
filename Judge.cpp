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

void Judge::detectPeople(vector<ROI> *ROIs, vector<DetectedObject> &Objs){ /* find people in ROIs vector and push into Objs vector */
    
    /* do some tasks to make sure a person is in ROI or not */
    
    for(int i=0; i<ROIs->size(); i++)
        ROIs->pop_back();
    delete ROIs;
}
