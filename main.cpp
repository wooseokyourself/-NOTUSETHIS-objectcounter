//
//  main.cpp
//
//  Created by wooseokyourself on 23/07/2019.
//  Copyright © 2019 wooseokyourself. All rights reserved.
//

#include "System.hpp"

int main(void){
    System* system = new System("$VIDEO_PATH");
    system->Run();
    delete system;
    return 0;
}
