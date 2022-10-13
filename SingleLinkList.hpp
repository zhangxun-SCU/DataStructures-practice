//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_SINGLELINKLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_SINGLELINKLIST_HPP
#include <iostream>
#include "Node.hpp"
using namespace std;

template<class ElemType>
class SingleLinkList {
private:
    Node<ElemType> *head;

    int size;

    Node<ElemType> *getElemPtr(int index) const;  // 返回第pos个结点的指针
public:
    // 无参构造
    SingleLinkList();
    // 给定数组构造
    SingleLinkList(unsigned int size, ElemType *arr);
    // 析构函数
    ~SingleLinkList();
    // 拷贝构造
    SingleLinkList(SingleLinkList<ElemType> &source);
    // 返回链表长度
    int length() const;
    // 判空
    bool empty() const;
    // 清空
    void clear();
    // 插入节点
    bool insert(ElemType data, int index);
    // 直接删除
    bool deleteElem(int index);
    // 删除节点
    bool removeElem(int index, ElemType &e);
    // 查找
    bool get(int index, ElemType &e);
    // 重载下标运算符
    ElemType &operator[](unsigned int index);
    // 输出链表数据，用于测试
    void output();
};

template<class ElemType>
SingleLinkList<ElemType>::SingleLinkList(): size(0), head(nullptr){
    head = new Node<ElemType>(0);
}

template<class ElemType>
SingleLinkList<ElemType>::SingleLinkList(unsigned int size, ElemType *arr):size(size) {
    head = new Node<ElemType>(0);
    for (int i = 0; i < size; i++) {
        this->insert(arr[i], i);
    }
}

template<class ElemType>
SingleLinkList<ElemType>::~SingleLinkList() {
    clear();
    delete head;
}

template<class ElemType>
SingleLinkList<ElemType>::SingleLinkList(SingleLinkList<ElemType> &source) {
    head = source.head;
    size = source.size;
    Node<ElemType> *ptr = source.head->next;
    for (int i = 0; i < size; i++, ptr = ptr->next) {
        this->insert(ptr->data, size);
    }
}

template<class ElemType>
Node<ElemType> *SingleLinkList<ElemType>::getElemPtr(int index) const {
    if (index == -1) {
        return head;
    } else if(index < -1 || index >= size){
        exit(-1);
    }
    Node<ElemType> *tmpPtr = head->next;
    for (int i = 0; i < index; i++) {
        tmpPtr = tmpPtr->next;
    }
    return tmpPtr;
}

template<class ElemType>
int SingleLinkList<ElemType>::length() const {
    return size;
}

template<class ElemType>
bool SingleLinkList<ElemType>::empty() const {
    return size == 0;
}

template<class ElemType>
void SingleLinkList<ElemType>::clear() {
    while (!empty()) {
        deleteElem(0);
    }
}

template<class ElemType>
bool SingleLinkList<ElemType>::insert(ElemType data, int index) {
//    注意insertNode一定要使用new来创建，不然在函数执行完毕后，节点会被销毁
    auto *insertNode = new Node<ElemType>(data);
//    定义超出链表范围得异常
    if (index < 0 || index > size) {
        return false;
    }
/**
 *  这里以及后面很多地方就体现了引入假设的头结点的简便
 *  不用区分插入位置，不管那个位置都可以直接插入
 */
//    找到前面的节点
    Node<ElemType> *prev = getElemPtr(index - 1);
    insertNode->next = prev->next;
    prev->next = insertNode;
    size++;
    return true;
}

template<class ElemType>
bool SingleLinkList<ElemType>::deleteElem(int index) {
    if (index < 0 || index >= size) {
        return false;
    }
//    找到前面的节点
    Node<ElemType> *prev = getElemPtr(index - 1);
    Node<ElemType> *next = prev->next;
    prev->next = next->next;
    size--;
//    最后记得释放内存
    delete next;
    return true;
}

template<class ElemType>
bool SingleLinkList<ElemType>::removeElem(int index, ElemType &e) {
    Node<ElemType> *removeNode = nullptr;

    if (index < 0 || index >= size) {
        return false;
    }
    Node<ElemType> *prev = getElemPtr(index - 1);
    Node<ElemType> *next = prev->next;
    e = next->data;
    prev->next = next->next;
    size--;
    delete next;
    return true;

}

template<class ElemType>
bool SingleLinkList<ElemType>::get(int index, ElemType &e) {
    if (index < 0 || index >= size) {
        return false;
    }
    Node<ElemType> *ptr = getElemPtr(index);
    e = ptr->data;
    return true;
}

template<class ElemType>
ElemType &SingleLinkList<ElemType>::operator[](unsigned int index) {
    if(index > size){
        cout<<"out of range!"<<endl;
        exit(1);
    }
    return getElemPtr(index)->data;
}

template<class ElemType>
void SingleLinkList<ElemType>::output() {
    Node<ElemType> *temp = head->next;
    for (int i = 0; i < size; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

#endif //DATASTRUCTURESANDALGORITHMS_SINGLELINKLIST_HPP

