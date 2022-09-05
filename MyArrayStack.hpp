//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYARRAYSTACK_HPP
#define DATASTRUCTURESANDALGORITHMS_MYARRAYSTACK_HPP
#include "MyArray.hpp"

template<class T>
class MyArrayStack {
private:
    MyArray<T> stack;
    unsigned int pos;
public:
    MyArrayStack();
//    压栈
    void push(T element);
//    出栈
    int pop();
//    返回栈顶元素
    int peek();
//    栈大小
    int size() const;
//    是否是空栈
    int isEmpty() const;

};


template<class T>
MyArrayStack<T>::MyArrayStack(): stack(MyArray<T>()), pos(0) {}

template<class T>
void MyArrayStack<T>::push(T element) {
    stack.insert(pos, element);
    pos++;
}

template<class T>
int MyArrayStack<T>::pop() {
    T popElement = stack.elementDelete(pos - 1);
    pos--;
    return popElement;
}

template<class T>
int MyArrayStack<T>::peek() {
    return stack[pos-1];
}

template<class T>
int MyArrayStack<T>::size() const {
    return pos;
}

template<class T>
int MyArrayStack<T>::isEmpty() const {
    return pos == 0 ? 1 : 0;
}

#endif //DATASTRUCTURESANDALGORITHMS_MYARRAYSTACK_HPP

