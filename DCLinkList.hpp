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
    int corPos;
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
//    插入
    bool insert(int index, ElemType &element);
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
}

#endif //DATASTRUCTURESANDALGORITHMS_DCLINKLIST_HPP
