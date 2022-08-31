//
// Created by cw on 2022/8/31.
//

#include "MyArray.h"
#include<iostream>

// 数组构造函数
MyArray::MyArray(int size) {
    this->length = 0;
    this->size = size;
    this->arr = new int[size];
}

// 数组析构函数
MyArray::~MyArray() {
    delete[] arr;
    arr = nullptr;
}

// 数组插入元素
void MyArray::insert(int index, int element) {
////    if(index < 0 || index > size){
////        const char* str = "Array out of range, please resize";
////        throw str;
////    } else {
//////        从后向前循环，将前一位移到后一位
////        for(int i = size - 1; i >= index; i--){
////            arr[i+1] = arr[i];
////        }
////        arr[index] = element;
////        this->length++;
////    }
//    try {
//        if (index < 0 || index > size) {
//            throw std::bad_alloc();
//        } else {
////        从后向前循环，将前一位移到后一位
//            for (int i = size - 1; i >= index; i--) {
//                arr[i + 1] = arr[i];
//            }
//            arr[index] = element;
//            this->length++;
//        }
//    } catch (std::exception &e) {
//        std::cout<<"Array out of range, please resize"<<std::endl;
//    }
}

// 输出数组
void MyArray::output() {
    for (int i = 0; i < this->length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}