//
//  main.cpp
//  typedef
//
//  Created by nova on 14-8-15.
//  Copyright (c) 2014年 Avazu. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

typedef struct SA{
    SA(int _i, string _s):i(_i),s(_s){}
    int i;
    string s;
} SB;
/** 等价于下面的定义,以上定义可以省略SA(如果不需要SA struct 名称)*/
/*
struct SA{
    int i;
    string s;
};
typedef SA SB;*/


int main(int argc, const char * argv[])
{
    SB sb{1,"aa"};
    
    SB sbs[] = {
        {2,"bb"},
        {3,"cc"}
    };
    
    cout << sb.s  << endl;
    cout << sbs[0].s << endl;
    
    auto sc = sbs[1];
    cout << sc.s << endl;
    
    SB * psb = new SB(4,"dd");
    cout << psb->s << endl;
    delete psb;
    psb = nullptr;
    return 0;
}

