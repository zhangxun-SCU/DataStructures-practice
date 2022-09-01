//
// Created by cw on 2022/8/31.
//

#include "MyArray.h"

MyException out_of_array_exception = MyException("Array out of range, please resize");
MyException del_exception = MyException("Array out of range, can't delete!");


// 数组构造函数
MyArray::MyArray(int size) : size(size), length(0), arr(new int[size]) {}

// 数组拷贝构造
MyArray::MyArray(const MyArray &tmp) : size(tmp.size), length(tmp.length), arr(new int[this->size]) {
    for (int i = 0; i < tmp.size; i++) {
        this->arr[i] = tmp.arr[i];
    }
}

// 数组析构函数
MyArray::~MyArray() {
    delete[] arr;
    arr = nullptr;
}

// 数组插入元素
void MyArray::insert(int index, int element) {
//    定义数组超出范围得异常
    try {
        if (index < 0 || index > size) {
            throw out_of_array_exception;
        } else {
            for (int i = this->size - 1; i >= index; i--) {
                arr[i + 1] = arr[i];
            }
            arr[index] = element;
            this->length++;
        }
    } catch (MyException &e) {
        std::cout << out_of_array_exception.what() << std::endl;
    }
}

// 数组扩容
void MyArray::resize() {
    int *arrNew = new int[this->size * 2];
    for (int i = 0; i < this->size; i++) {
        arrNew[i] = arr[i];
    }
    delete[] arr;
    arr = arrNew;
    this->size *= 2;
}

// 删除数组
int MyArray::elementDelete(int index) {
    int deElement = -1;
    try {
        if (index < 0 || index > this->size) {
            throw del_exception;
        } else {
            deElement = arr[index];
//            从左到右元素向前移一位
            for (int i = index; i < this->size; i++) {
                arr[i] = arr[i + 1];
            }
            this->length--;
        }
    } catch (MyException& e) {
        std::cout << del_exception.what() << std::endl;
    }
    return deElement;
}

const int &MyArray::operator[](unsigned int index) const {
    try{
        if(index < 0 || index > size){
            throw out_of_array_exception;
        }
    } catch (MyException&){
        std::cout<<out_of_array_exception.what()<<std::endl;
    }
    return arr[index];
}

int &MyArray::operator[](unsigned int index) {
    try{
        if(index < 0 || index > size){
            throw out_of_array_exception;
        }
    } catch (MyException&){
        std::cout<<out_of_array_exception.what()<<std::endl;
    }
    return arr[index];
}

// 输出数组
void MyArray::output() {
    for (int i = 0; i < this->length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}