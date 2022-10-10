//
// Created by cw on 2022/9/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
#include <iostream>
#include "Node.hpp"

using namespace std;

template<class ElemType>
class CirLinkList {
private:
    Node<ElemType> *head;
    Node<ElemType> *last;
    int size;

    // 辅助函数：返回index处节点指针
    Node<ElemType>* getElemptr(int index) const;

public:
//    构造函数
    CirLinkList();
//    拷贝构造
    CirLinkList(const CirLinkList<ElemType> &source);
//    析构
    virtual ~CirLinkList();
//    求长度
    int length();
//    判空
    bool empty();
//    清空
    void clear();
//    插入节点
    bool insert(ElemType data, int index);
//    遍历执行
    void traverse(void (*visit)(const ElemType &)) const;
//    获取元素
    bool getElem(int index, ElemType &element);
//    直接删除
    bool deleteElem(int index);
//    删除并返回
    bool removeElem(int index);
//    重载

};

#endif //DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP

template<class ElemType>
CirLinkList<ElemType>::CirLinkList():size(0) {
    head = new Node<ElemType>;
    // 循环链表，尾指针指向头元素
    head->next = head;
    // 链表为空时, last=head
    last = head;
}

template<class ElemType>
CirLinkList<ElemType>::CirLinkList(const CirLinkList<ElemType> &source) {
    size = source.size;
    /****/

}

template<class ElemType>
CirLinkList<ElemType>::~CirLinkList() {
    /** delete **/
    clear();
    delete head;
}

template<class ElemType>
Node<ElemType> *CirLinkList<ElemType>::getElemptr(int index) const {
    Node<ElemType> *temp = head;
    if(index == -1){
        return head;
    } else if(index < -1){
        exit(-1);
    }
    for(int i = 0; i <= index; i++){
        temp = temp->next;
    }
}

template<class ElemType>
int CirLinkList<ElemType>::length() {
    return size;
}

template<class ElemType>
bool CirLinkList<ElemType>::empty() {
    return size == 0;
}

template<class ElemType>
void CirLinkList<ElemType>::clear() {
    while(!empty()){
        deleteElem(0);
    }
}

template<class ElemType>
bool CirLinkList<ElemType>::insert(ElemType data, int index) {
    // 先构建节点
    auto *insertNode = new Node<ElemType>(data);
    if(index < 0 || index > size){
        // 插入位置不合法
        return false;
    } else if (index == size){
        // 插入在尾部
        last->next = insertNode;
        last = insertNode;
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
void CirLinkList<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    for(int i = 0; i < size; i++){
        Node<ElemType> *tmpPtr = getElemptr(i - 1);
        visit(tmpPtr->data);
    }
}

template<class ElemType>
bool CirLinkList<ElemType>::getElem(int index, ElemType &e) {
    return false;
}

template<class ElemType>
bool CirLinkList<ElemType>::deleteElem(int index) {

}

template<class ElemType>
bool CirLinkList<ElemType>::removeElem(int index) {

}

