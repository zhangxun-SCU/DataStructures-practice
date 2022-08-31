//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYARRAY_H
#define DATASTRUCTURESANDALGORITHMS_MYARRAY_H


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
    ~MyArray();
    void insert(int index, int element);
    void output();
};


#endif //DATASTRUCTURESANDALGORITHMS_MYARRAY_H
