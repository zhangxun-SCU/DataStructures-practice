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
protected:
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
    bool insert(int index, ElemType data);

    // 直接删除
    bool deleteElem(int index);

    // 删除节点
    bool removeElem(int index, ElemType &e);

    // 查找
    bool getElem(int index, ElemType &e);

    // 修改/set
    bool setElem(int index, ElemType &e);

    // 遍历
    void traverse(void (*visit)(const ElemType &)) const;

    // 重载赋值
    SingleLinkList<ElemType> &operator=(const SingleLinkList<ElemType> &source);

    // 重载下标运算符
    ElemType &operator[](unsigned int index);

    // 输出链表数据，用于测试
    void output();

    // 链表基本使用/算法
    /*翻转链表*/
    static SingleLinkList<ElemType> &reverse(SingleLinkList<ElemType> &source);
    /*顺序合并链表*/
    static void merge(SingleLinkList<ElemType> &la, SingleLinkList<ElemType> &lb, SingleLinkList<ElemType> &lc);
};

template<class ElemType>
SingleLinkList<ElemType>::SingleLinkList(): size(0), head(nullptr) {
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
    } else if (index < -1 || index >= size) {
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
bool SingleLinkList<ElemType>::insert(int index, ElemType data) {
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
bool SingleLinkList<ElemType>::getElem(int index, ElemType &e) {
    if (index < 0 || index >= size) {
        return false;
    }
    Node<ElemType> *ptr = getElemPtr(index);
    e = ptr->data;
    return true;
}

template<class ElemType>
bool SingleLinkList<ElemType>::setElem(int index, ElemType &e) {
    if (index < 0 || index >= size) {
        return false;
    }
    Node<ElemType> *ptr = getElemPtr(index);
    ptr->data = e;
    return true;
}

template<class ElemType>
void SingleLinkList<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    Node<ElemType> *tempPtr;
    for (int i = 0; i < size; i++) {
        tempPtr = getElemPtr(i);
        visit(tempPtr->data);
    }
}

template<class ElemType>
SingleLinkList<ElemType> &SingleLinkList<ElemType>::operator=(const SingleLinkList<ElemType> &source) {
    if (&source != this) {
        head = source.head;
        size = source.size;
        Node<ElemType> *ptr = source.head->next;
        for (int i = 0; i < size; i++, ptr = ptr->next) {
            this->insert(ptr->data, size);
        }
    }
    return *this;
}

template<class ElemType>
ElemType &SingleLinkList<ElemType>::operator[](unsigned int index) {
    if (index > size) {
        cerr << "out of range!" << endl;
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

template<class ElemType>
SingleLinkList<ElemType> &SingleLinkList<ElemType>::reverse(SingleLinkList<ElemType> &source) {
    // 反转链表
    Node<ElemType> *head = source.getElemPtr(0);
    Node<ElemType> *tmp, *newHead = nullptr;
    while (head) {
        tmp = head->next;
        head->next = newHead;
        newHead = head;
        head = tmp;
    }
    source.head->next = newHead;
    return source;
}

template <class ElemType >
void SingleLinkList<ElemType> :: merge(SingleLinkList<ElemType> &la, SingleLinkList<ElemType> &lb, SingleLinkList< ElemType > &lc){
    int aLen = la.length();
    int bLen = lb.length();
    ElemType a, b;
    for(int aPos = 0, bPos = 0; aPos < aLen || bPos < bLen;){
        if(aPos < aLen && bPos < bLen){
            la.getElem(aPos, a);
            lb.getElem(bPos, b);
            if(a < b){
                lc.insert(0, a);
                aPos++;
            } else {
                lc.insert(0, b);
                bPos++;
            }
        } else if(aPos < aLen && bPos == bLen){
            la.getElem(aPos, a);
            lc.insert(0, a);
            aPos++;
        } else if(aPos == aLen && bPos < bLen){
            lb.getElem(bPos, b);
            lc.insert(0, b);
            bPos++;
        }
    }
}

#endif //DATASTRUCTURESANDALGORITHMS_SINGLELINKLIST_HPP

