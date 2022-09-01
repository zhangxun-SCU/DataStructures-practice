#include <iostream>
#include "MyArray.h"
#include "MyLinkedList.h"

int main() {
/***********************数组测试*************************/
//    MyArray arr = MyArray(5);
//    arr.insert(0, 10);
//    arr.output();
//    arr.resize();
//    arr.resize();
//    arr.resize();
//    arr.resize();
//    arr.resize();
//    arr.insert(50, 10);
//    arr.insert(1, 1);
//    arr.insert(3, 1);
//    arr.output();

/************************单向链表测试**********************/
    MyLinkedList myLinkedList = MyLinkedList();
    myLinkedList.insert(5, 0);
    myLinkedList.insert(2, 1);
//    myLinkedList.insert(0, 2);
    myLinkedList.output();
    return 0;
}

