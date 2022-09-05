//
// Created by cw on 2022/9/1.
//

#include "MyArrayStack.h"

MyArrayStack::MyArrayStack() {
    this->stack = MyArray();
    this->pos = 0;
}

void MyArrayStack::push(int element) {
    stack.insert(pos, element);
    pos++;
}

int MyArrayStack::pop() {
    int popElement = stack.elementDelete(pos - 1);
    pos--;
    return popElement;
}

int MyArrayStack::peek() {
    return stack[pos-1];
}

int MyArrayStack::size() const{
    return pos;
}

int MyArrayStack::isEmpty() const{
    return pos == 0 ? 1 : 0;
}