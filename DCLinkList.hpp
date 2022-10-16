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
    // size cur
    size = 0;
    curPos = 0;
    curPtr = head;
}

template<class ElemType>
DCLinkList<ElemType>::DCLinkList(const DCLinkList<ElemType> &source) {
    size = source.size;
    curPos = 0;
    curPtr = head;
    int count = 0;
    for(NodeDbl<ElemType> *tmpPtr = source.head->next; tmpPtr != head; tmpPtr = tmpPtr->next){
        this->insert(tmpPtr->data, count++);
    }
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
    NodeDbl<ElemType> *tmpPtr;
    // 选择一个最快的方式去寻找目标元素
    int interval = index - curPos;
    if(interval >= 0 && interval >= size - index){
        // 从curPos通过next去找
        tmpPtr = curPtr;
        for(int i = 0; i < interval; i++){
            tmpPtr = tmpPtr->next;
        }
    } else if(interval >= 0 && interval < size - index){
        // 从head通过prev找
        tmpPtr = head->prev;
        for(int i = 0; i < size - 1 - index; i++){
            tmpPtr = tmpPtr->prev;
        }
    } else if(interval < 0 && -interval <= index){
        // 从curPos通过prev找
        tmpPtr = curPtr;
        for(int i = 0; i < -interval; i++){
            tmpPtr = tmpPtr->prev;
        }
    } else{
        // 从head通过next找
        tmpPtr = head->next;
        for(int i = 0; i < index; i++){
            tmpPtr = tmpPtr->next;
        }
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
    if(index < 0 || index > size){
        // 插入位置非法
        return false;
    }
//    auto *insertNode = new NodeDbl<ElemType>(data);
    NodeDbl<ElemType> *prevNode = getElemPtr(index - 1);
    auto insertNode = new NodeDbl<ElemType>(data, prevNode, prevNode->next);
    prevNode->next->prev = insertNode;
    prevNode->next = insertNode;
//    insertNode->next = prevNode->next;
//    insertNode->prev = prevNode;
//    prevNode->next->prev = insertNode;
//    prevNode->next = insertNode;
    size++;
    curPos = index;
    curPtr = insertNode;
    return true;
}

template<class ElemType>
bool DCLinkList<ElemType>::deleteElem(int index) {
    if(index < 0 || index >= size){
        return false;
    }
    NodeDbl<ElemType> *prevPtr = getElemPtr(index - 1);
    NodeDbl<ElemType> *tmpPtr = prevPtr->next;
    prevPtr->next = tmpPtr->next;
    tmpPtr->next->prev = prevPtr;
    curPtr = prevPtr;
    delete tmpPtr;
    size--;
    curPos = index - 1;
    return true;
}

template<class ElemType>
bool DCLinkList<ElemType>::removeElem(int index, ElemType &element) {
    if(index < 0 || index >= size){
        return false;
    }
    NodeDbl<ElemType> *prevPtr = getElemPtr(index - 1);
    NodeDbl<ElemType> *tmpPtr = prevPtr->next;
    prevPtr->next = tmpPtr->next;
    tmpPtr->next->prev = prevPtr;
    curPtr = prevPtr;
    element = tmpPtr->data;
    delete tmpPtr;
    size--;
    curPos = index - 1;
    return true;
}

#endif //DATASTRUCTURESANDALGORITHMS_DCLINKLIST_HPP
