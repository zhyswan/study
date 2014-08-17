//
//  main.cpp
//  functional
//
//  Created by nova on 14-8-17.
//  Copyright (c) 2014年 Avazu. All rights reserved.
//

#include <iostream>
#include <functional>
#include <string>

using namespace std;
int main(int argc, const char * argv[])
{

    function<int()> fn = [](){return 1;};
    
    cout << fn() << endl;
    return 0;
}

