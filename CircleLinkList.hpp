//
// Created by cw on 2022/9/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
#include <iostream>
#include "Node.hpp"

using namespace std;

template<class ElemType>
class CircleLinkList {
private:
    Node<ElemType> *head;
    Node<ElemType> *last;
    int size;

    // 辅助函数：返回index处节点指针
    Node<ElemType>* getElemptr(int index) const;

public:
//    构造函数
    CircleLinkList();
//    拷贝构造
    CircleLinkList(const CircleLinkList<ElemType> &source);
//    析构
    virtual ~CircleLinkList();
//    求长度
    int length();
//    判空
    bool empty();
//    清空
    void clear();
//    插入节点
    bool insert(int index, ElemType data);
//    遍历执行
    void traverse(void (*visit)(const ElemType &)) const;
//    获取元素
    bool getElem(int index, ElemType &element);
//    修改元素
    bool setElem(int index, ElemType data);
//    直接删除
    bool deleteElem(int index);
//    删除并返回
    bool removeElem(int index, ElemType &element);
//    重载

};

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList():size(0) {
    head = new Node<ElemType>;
    // 循环链表，尾指针指向头元素
    head->next = head;
    // 链表为空时, last=head
    last = head;
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList(const CircleLinkList<ElemType> &source) {
    size = source.size;
    Node<ElemType> *tmpPtr = source.head;
    for(int i = 0; i < size; i++){
        tmpPtr = tmpPtr->next;
        this->insert(tmpPtr->data, i);
    }
}

template<class ElemType>
CircleLinkList<ElemType>::~CircleLinkList() {
    /** delete **/
    clear();
    delete head;
}

template<class ElemType>
Node<ElemType> *CircleLinkList<ElemType>::getElemptr(int index) const {
    if(index == -1){
        return head;
    } else if(index < -1 || index >= size){
        exit(-1);
    }
    Node<ElemType> *tmpPtr = head->next;
    for(int i = 0; i < index; i++){
        tmpPtr = tmpPtr->next;
    }
    return tmpPtr;
}

template<class ElemType>
int CircleLinkList<ElemType>::length() {
    /* length 应该计算还是size? */
//    int count = 0;
//    Node<ElemType> *tmpPtr = head->next;
//    for(; tmpPtr != head; tmpPtr = tmpPtr->next){
//        count++;
//    }
//    return count;
    return size;
}

template<class ElemType>
bool CircleLinkList<ElemType>::empty() {
    return size == 0;
}

template<class ElemType>
void CircleLinkList<ElemType>::clear() {
    while(!empty()){
        deleteElem(0);
    }
}

template<class ElemType>
bool CircleLinkList<ElemType>::insert(int index, ElemType data) {
    // 先构建节点
    auto *insertNode = new Node<ElemType>(data);
    if(index < 0 || index > size){
        // 插入位置不合法
        return false;
    } else if (index == size){
        // 插入在尾部
        last->next = insertNode;
        last = insertNode;
        // last执行head，徐娜混
        last->next = head;
    } else {
        // 插入在中间，先get前一个节点
        Node<ElemType> *prevNode = getElemptr(index - 1);
        insertNode->next = prevNode->next;
        prevNode->next = insertNode;
    }
    size++;
    return true;
}

template<class ElemType>
void CircleLinkList<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    for(Node<Exception> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next){
        visit(tmpPtr->data);
    }
}

template<class ElemType>
bool CircleLinkList<ElemType>::getElem(int index, ElemType &element) {
    if(index < 0 || index >= size){
        return false;
    }
    Node<ElemType> *tmpPtr = getElemptr(index);
    element = tmpPtr->data;
    return true;
}

template<class ElemType>
bool CircleLinkList<ElemType>::setElem(int index, ElemType data) {
    if(index < 0 || index >= size){
        return false;
    }
    Node<ElemType> *tmpPtr = getElemptr(index);
    tmpPtr->data = data;
    return true;
}

template<class ElemType>
bool CircleLinkList<ElemType>::deleteElem(int index) {
    if(index < 0 || index >= size){
        return false;
    } else if(index == size - 1){
        // 删除尾节点
        Node<ElemType> *tmpPtr = last;
        Node<ElemType> *prevPtr = getElemptr(index - 1);
        last = prevPtr;
        last->next = head;
        delete tmpPtr;
    } else{
        Node<ElemType> *prevPtr = getElemptr(index - 1);
        Node<ElemType> *tmpPtr = prevPtr->next;
        prevPtr->next = tmpPtr->next;
        delete tmpPtr;
    }
    size--;
    return true;
}

template<class ElemType>
bool CircleLinkList<ElemType>::removeElem(int index, ElemType &element) {
    if(index < 0 || index >= size){
        return false;
    } else if(index == size - 1){
        // 删除尾节点
        Node<ElemType> *tmpPtr = last;
        Node<ElemType> *prevPtr = getElemptr(index - 1);
        element = tmpPtr->data;
        last = prevPtr;
        last->next = head;
        delete tmpPtr;
    } else{
        Node<ElemType> *prevPtr = getElemptr(index - 1);
        Node<ElemType> *tmpPtr = prevPtr->next;
        element = tmpPtr->data;
        prevPtr->next = tmpPtr->next;
        delete tmpPtr;
    }
    size--;
    return true;
}

#endif //DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
