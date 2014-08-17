//
//  main.cpp
//  functional
//
//  Created by nova on 14-8-17.
//  Copyright (c) 2014年 Avazu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

using namespace std;

//工具函数
string itos(int i){
    ostringstream ss;
    ss << i;
    return ss.str();
}


//用于演示函数指针调用
string usefuncp(int i,bool b){
    return itos(i) + "->函数指针";
};

//函数定义
string func(int i,bool b){
    return itos(i) + "->function";
}

//函数对象定义
struct Func{
    Func(string _s):s(_s){
        
    }
    string operator()(int i,bool b){
        return itos(i) + "->函数对象:" + s;
    }
private:
    string s;
};

/*
 function<string(int,bool)> 可调用对象，返回string，参数int，bool
 可调用类型有以下情况
 1，函数
 2，函数指针
 3，函数对象（实现了()操作符的类对象）
 4，lambda表达式（一种函数对象，编译器会翻译生成未命名类的未命名对象），可定义在函数内部，可以使用[]捕获函数内部的局部变量
 5，bind()返回的可调用对象
 */


/**
 functional bind(functional,args);
 bind() 接受一个可调用对象，以及这个可调用对象需要的参数，返回一个可调用对象
 返回的可调用对象的参数，为bind参数中的 placeholder::_n的参数，

 因此bind可以生成一个可调用对象，可调用对象执行时，调用bind的参一，并将除参一之外的参数传递给参一
 其中placeholder是占位符，通过bind生成的可调用对象的参数按顺序传递
 可调用对象的参数由bind参数中的placeholders决定
 
 bindf1是一个可调用对象，接收2个参数,实参按顺序传递给bind函数参数的 placeholders::_n
 如调用
 bindf1(1,false);
 相当于 
 bindfunc(1,"abc",false);
 
 */
string bindfunc(int i,const string &s,bool b){
    return itos(i) + "->bind函数适配器:" + s;
}
auto bindf1 = bind(bindfunc,placeholders::_1,"bindf1",placeholders::_2);

int main(int argc, const char * argv[])
{
    
    //函数指针
    string (*funcp)(int i ,bool b);
    
    funcp = usefuncp;//  等价于 funcp = & usefuncp;
    
    
    int locali = 10;
    
    //f的类型为可调用对象，返回string，参数为int,bool
    typedef function<string(int,bool)> f;
    //vector<function<string(int,bool)>> vfs = {
    vector<f> vfs = {
        func,
        funcp,
        Func("Class Func"),
        /**
         lambda表达式,可以忽略参数列表和返回类型，但是捕获列表［］函数体不能省略,
         ，且返回类型必须后置,忽略()和参数列表等价于空的参数列表
         */
        [locali](int i,bool b) {return itos(i) + "->lambda表达式:" + itos(locali);},
        bind(bindfunc,placeholders::_1,"匿名",placeholders::_2),
        bindf1
        
    };

    static int loci = 10;
    for(auto &f :vfs){
        cout << f(++loci,false) << endl;
    }
    
    cout << endl;
    
    for(int i=0;i<vfs.size();i++){
        cout << vfs[i](i+1,false) << endl;
    }
    
    cout << endl;
    return 0;
}


