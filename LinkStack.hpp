//
// Created by cw on 2022/10/27.
//

#ifndef DATASTRUCTURESANDALGORITHMS_LINKSTACK_HPP
#define DATASTRUCTURESANDALGORITHMS_LINKSTACK_HPP
#include <iostream>

#include "Node.hpp"

using namespace std;

template<class ElemType>
class LinkStack {
private:
    // 栈顶指针
    Node<ElemType> *topPtr;
    int count;
public:
    LinkStack();
    LinkStack(const LinkStack<ElemType> &source);
    virtual ~LinkStack();
    // 求长度
    int length() const;
    // 判空
    bool empty() const;
    // 清空栈
    void clear();
    // 遍历
    void traverse(void(*visit)(const ElemType &)) const;
    // 入栈
    bool push(const ElemType &element);
    // 栈顶
    bool top(ElemType &element) const;
    // 出栈
    bool pop();
    // 出栈并返回
    bool pop(ElemType &element);
    // 重载
    LinkStack<ElemType> &operator=(const LinkStack<ElemType> &source);

};

template<class ElemType>
LinkStack<ElemType>::LinkStack() {
    topPtr = nullptr;
    count = 0;
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &source) {

}

template<class ElemType>
LinkStack<ElemType>::~LinkStack() {
    clear();
}

template<class ElemType>
int LinkStack<ElemType>::length() const {
    return count;
}

template<class ElemType>
bool LinkStack<ElemType>::empty() const {
    return count == 0;
}

template<class ElemType>
void LinkStack<ElemType>::clear() {
    while (!this->empty()) {
        this->pop();
    }
}

template<class ElemType>
void LinkStack<ElemType>::traverse(void (*visit)(const ElemType &)) const {

}

template<class ElemType>
bool LinkStack<ElemType>::push(const ElemType &element) {
    Node<ElemType> *newTop = new Node<ElemType>(element, top);
    if(newTop == nullptr){
        cerr << "warning: 内存耗尽，入栈失败!"<<endl;
        return false;
    }
    topPtr = newTop;
    count++;
    return true;
}

template<class ElemType>
bool LinkStack<ElemType>::top(ElemType &element) const {
    if(count == 0){
        cerr << "warning: 栈为空!"<<endl;
        return false;
    }
    element = topPtr->data;
    return true;
}

template<class ElemType>
bool LinkStack<ElemType>::pop() {
    if(count == 0){
        cerr << "warning: 栈已空!"<<endl;
        return false;
    }
    // 旧栈顶
    Node<ElemType> *oldTop = topPtr;
    topPtr = oldTop->next;
    delete oldTop;
    count--;
    return true;
}

template<class ElemType>
bool LinkStack<ElemType>::pop(ElemType &element) {
    if(count == 0){
        cerr << "warning: 栈已空!"<<endl;
        return false;
    }
    // 旧栈顶
    Node<ElemType> *oldTop = topPtr;
    element = oldTop->data;
    topPtr = oldTop->next;
    delete oldTop;
    count--;
    return true;
}
#endif //DATASTRUCTURESANDALGORITHMS_LINKSTACK_HPP
