//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_ARRAYSTACK_HPP
#define DATASTRUCTURESANDALGORITHMS_ARRAYSTACK_HPP
#include "Array.hpp"

template<class T>
class ArrayStack {
private:
    Array<T> stack;
    unsigned int pos;
public:
    ArrayStack();
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
ArrayStack<T>::ArrayStack(): stack(Array<T>()), pos(0) {}

template<class T>
void ArrayStack<T>::push(T element) {
    stack.insert(pos, element);
    pos++;
}

template<class T>
int ArrayStack<T>::pop() {
    T popElement = stack.elementDelete(pos - 1);
    pos--;
    return popElement;
}

template<class T>
int ArrayStack<T>::peek() {
    return stack[pos-1];
}

template<class T>
int ArrayStack<T>::size() const {
    return pos;
}

template<class T>
int ArrayStack<T>::isEmpty() const {
    return pos == 0 ? 1 : 0;
}

#endif //DATASTRUCTURESANDALGORITHMS_ARRAYSTACK_HPP

