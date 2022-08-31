//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYARRAY_H
#define DATASTRUCTURESANDALGORITHMS_MYARRAY_H
#include<iostream>
#include "MyException.h"

class MyArray {
private:
//    数组容量
    unsigned int size;
//    数组长度
    unsigned int length;
//    指向数组的指针
    int* arr;
public:
    /*
     * 这里得explit关键字是为了防止发生隐式类型转换，具体原因详细阅读C++primer
     * */
    explicit MyArray(int size = 10);
    MyArray(const MyArray&);
    ~MyArray();
//    插入
    void insert(int index, int element);
//    扩容
    void resize();
//    删除
    int elementDelete(int);
//    输出
    void output();
};


#endif //DATASTRUCTURESANDALGORITHMS_MYARRAY_H
