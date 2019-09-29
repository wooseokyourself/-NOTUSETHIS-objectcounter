//
//  ImageVariables.hpp
//  src
//
//  Created by ChoiWooSeok on 29/09/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#ifndef ImageVariables_hpp
#define ImageVariables_hpp

#include <iostream>
#include "FrameHandler.hpp"

class ImageVariables{
    friend class FrameHandler
    
private:
    int MOG2_varThreshold;
    int MOG2_history;
    int bin;
public:
    ImageVariables(){
        cout << "Image variables set" << endl;
        cout << "MOG2_varThreshold : " ; cin >> MOG2_varThreshold;
        cout << "MOG2_history : " ; cin >> MOG2_history;
        cout << "bin : " ; cin >> bin;
    }
};

#endif /* ImageVariables_hpp */
