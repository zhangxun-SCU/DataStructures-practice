//
// Created by cw on 2022/10/29.
//

#ifndef DATASTRUCTURESANDALGORITHMS_LINKQUEUE_HPP
#define DATASTRUCTURESANDALGORITHMS_LINKQUEUE_HPP
#include <iostream>

#include "Node.hpp"

using namespace std;
template<class ElemType>
class LinkQueue {
private:
    Node<ElemType> *front, *rear;
    int count;
public:
    LinkQueue();
    LinkQueue(const LinkQueue<ElemType> &source);
    virtual ~LinkQueue();
    // 求长度
    int length();
    // 判空
    bool empty();
    // 清空
    void clear();
    // 遍历
    void traverse(void (*visit)(const ElemType &)) const;
    // 出队
    bool deQueue();
    // 出队并返回
    bool deQueue(ElemType &element);
    // 取对头
    bool getHead(ElemType &element) const;
    // 入队
    bool enQueue(const ElemType &element);
    // 重载
    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &source);

};

template<class ElemType>
LinkQueue<ElemType>::LinkQueue() {
    count = 0;
    rear = front = new Node<ElemType>;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &source) {
    count = source.count;
    rear = front = new Node<ElemType>;
    for(Node<ElemType> *temp = source.front->next; temp != source.rear; temp = temp->next){
        enQueue(temp->data);
    }
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
    clear();
    delete front;
}

template<class ElemType>
int LinkQueue<ElemType>::length() {
    return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::empty() {
    return count == 0;
}

template<class ElemType>
void LinkQueue<ElemType>::clear() {
    while(!empty()){
        deQueue();
    }
}

template<class ElemType>
void LinkQueue<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    for(Node<ElemType> *temp = front->next; front != rear; temp = temp->next){
        visit(temp->data);
    }
}

template<class ElemType>
bool LinkQueue<ElemType>::deQueue() {
    if(empty()){
        cerr << "warning: 队列为空" << endl;
        return false;
    }
    // 第一个元素
    Node<ElemType> *temp = front->next;
    front->next = temp->next;
    if(rear == temp){
        // 说明队列只有一个元素，出对后就没有的，故此时要改变rear的指向
        rear = front;
    }
    delete temp;
    count--;
    return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::deQueue(ElemType &element) {
    if(empty()){
        cerr << "warning: 队列为空" << endl;
        return false;
    }
    // 第一个元素
    Node<ElemType> *temp = front->next;
    element = temp->data;
    front->next = temp->next;
    if(rear == temp){
        // 说明队列只有一个元素，出对后就没有的，故此时要改变rear的指向
        rear = front;
    }
    delete temp;
    count--;
    return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::getHead(ElemType &element) const {
    if(empty()){
        cerr << "warning: 队列为空" << endl;
        return false;
    }
    element = front->next->data;
    return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::enQueue(const ElemType &element) {
    Node<ElemType> *enNode = new Node<ElemType>(element);
    if (enNode == nullptr) {
        cerr << "warning: 内存耗尽，入队失败!" << endl;
        return false;
    }
    count++;
    rear->next = enNode;
    rear = enNode;
    return true;
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &source) {
    if(&source != this){
        clear();
        count = source.count;
        for(Node<ElemType> *temp = source.front->next; temp != source.rear; temp = temp->next){
            enQueue(temp->data);
        }
    }
    return *this;
}
#endif //DATASTRUCTURESANDALGORITHMS_LINKQUEUE_HPP
