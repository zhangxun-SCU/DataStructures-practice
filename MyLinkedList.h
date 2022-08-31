//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_H
#define DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_H

#include <iostream>
#include "MyException.h"

// 定义链表节点
struct Node {
    int data;
    Node *next{};
    explicit Node(int data): data(data){};
};

class MyLinkedList {
private:
    Node *head;
    Node *last;
    int size;
public:
    MyLinkedList() = default;
    MyLinkedList(int);

//    插入节点
    void insert(int, int);

//    删除节点
    Node* remove(int);

//    查找
    Node* get(int);

//    输出链表数据
    void ouput();
};


#endif //DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_H
