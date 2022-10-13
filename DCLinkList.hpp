//
// Created by cw on 2022/10/11.
//

#ifndef DATASTRUCTURESANDALGORITHMS_DCLINKLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_DCLINKLIST_HPP
#include <iostream>
#include "Node.hpp"

template<class ElemType>
class DCLinkList {
private:
//    头指针与尾指针：引入头节点
    NodeDbl<ElemType> *head;
    NodeDbl<ElemType> *last;
//    链表大小
    int size;
//    当前位置与指针：百年与查找
    int curPos;
    NodeDbl<ElemType> *curPtr;

//    辅助函数
    NodeDbl<ElemType> *getElemPtr(int index) const;

public:
//    构造、拷贝构造、析构
    DCLinkList();
    DCLinkList(const DCLinkList<ElemType> &source);
    virtual ~DCLinkList();
//    返回链表长度
    int length() const;
//    判空
    bool empty() const;
//    清空
    void clear();
//    遍历
    void traverse(void(*visit)(ElemType &)) const;
//    get
    bool getElem(int index, ElemType &element);
//    set
    bool setElem(int index, ElemType data);
//    插入
    bool insert(int index, ElemType data);
//    直接删除
    bool deleteElem(int index);
//    删除并返回
    bool removeElem(int index, ElemType &element);
//    重载


};

template<class ElemType>
DCLinkList<ElemType>::DCLinkList() {
    head = new NodeDbl<ElemType>;
    // 双向循环
    head->prev = head;
    head->next = head;
    // 初始last等于head
    last = head;
    // size cur
    size = 0;
    curPos = 0;
    curPtr = head;
}

template<class ElemType>
DCLinkList<ElemType>::DCLinkList(const DCLinkList<ElemType> &source) {

}

template<class ElemType>
DCLinkList<ElemType>::~DCLinkList() {
    clear();
    delete head;
}

template<class ElemType>
NodeDbl<ElemType> *DCLinkList<ElemType>::getElemPtr(int index) const {
    if(index == -1){
        return head;
    } else if(index < -1 || index >= size){
        exit(-1);
    }
    NodeDbl<ElemType> *tmpPtr = head->next;
    for(int i = 0; i < index; i++){
        tmpPtr = tmpPtr->next;
    }
    return tmpPtr;
}

template<class ElemType>
int DCLinkList<ElemType>::length() const {
    return size;
}

template<class ElemType>
bool DCLinkList<ElemType>::empty() const {
    return size == 0;
}

template<class ElemType>
void DCLinkList<ElemType>::clear() {
    while(!empty()){
        deleteElem(0);
    }
}

template<class ElemType>
void DCLinkList<ElemType>::traverse(void (*visit)(ElemType &)) const {
    for(NodeDbl<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next){
        visit(tmpPtr->data);
    }
}

template<class ElemType>
bool DCLinkList<ElemType>::getElem(int index, ElemType &element) {
    if(index < 0 || index >= size){
        return false;
    }
    NodeDbl<ElemType> *tmpPtr = getElemPtr(index);
    element = tmpPtr->data;
    // 设置curPos和curPtr
    curPos = index;
    curPtr = tmpPtr;
    return true;
}

template<class ElemType>
bool DCLinkList<ElemType>::setElem(int index, ElemType data) {
    if(index < 0 || index >= size){
        return false;
    }
    NodeDbl<ElemType> *tmpPtr = getElemPtr(index);
    tmpPtr->data = data;
    // 设置curPos curPtr
    curPos = index;
    curPtr = tmpPtr;
    return true;
}

template<class ElemType>
bool DCLinkList<ElemType>::insert(int index, ElemType data) {
    NodeDbl<ElemType> *tmpPtr = new NodeDbl<ElemType>(data);
    if(index < 0 || index > size){
        // 插入位置非法
        return false;
    } else if(index == size){
        // 插入链表尾部

    }
}

#endif //DATASTRUCTURESANDALGORITHMS_DCLINKLIST_HPP
