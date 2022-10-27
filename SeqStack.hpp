//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_SEQSTACK_HPP
#define DATASTRUCTURESANDALGORITHMS_SEQSTACK_HPP
#define DEFAULT_SIZE 1000
#include <iostream>

using namespace std;

template<class ElemType>
class SeqStack {
private:
    ElemType *elems;
    int maxSize;
    int count;
public:
    // 构造+复制构造+析构
    explicit SeqStack(int size=DEFAULT_SIZE);
    SeqStack(const SeqStack<ElemType> &source);
    virtual ~SeqStack();
    // 返回栈长
    int length() const;
    // 判空
    int empty() const;
    // 清空
    void clear();
    // 遍历traverse
    void traverse(void(*visit)(const ElemType &));
    // 压栈
    bool push(const ElemType &element);
    // 返回栈顶元素
    bool top(ElemType &element);
    // pop出栈顶元素
    bool pop();
    // pop出栈顶元素并返回
    bool pop(ElemType &element);
    // 重载
    SeqStack<ElemType> &operator=(const SeqStack<ElemType> &source);

};

template<class ElemType>
SeqStack<ElemType>::SeqStack(int size) {
    maxSize = size;
    elems = new ElemType[maxSize];
    count = 0;
}

template<class ElemType>
SeqStack<ElemType>::SeqStack(const SeqStack<ElemType> &source) {
    maxSize = source.maxSize;
    elems = new ElemType[maxSize];
    count = source.count;
    for(int i = 0; i < source.length(); i++){
        elems[i] = source.elems[i];
    }
}

template<class ElemType>
SeqStack<ElemType>::~SeqStack() {
    delete[] elems;
}

template<class ElemType>
int SeqStack<ElemType>::length() const {
    return count;
}

template<class ElemType>
int SeqStack<ElemType>::empty() const {
    return count == 0;
}

template<class ElemType>
void SeqStack<ElemType>::clear() {
    while(!this->empty()){
        this->pop();
    }
}

template<class ElemType>
void SeqStack<ElemType>::traverse(void (*visit)(const ElemType &)) {
    for(int i = 0; i < this->length(); i++){
        visit(elems[i]);
    }
}

template<class ElemType>
bool SeqStack<ElemType>::push(const ElemType &element) {
    if(count >= maxSize){
        cerr << "warning: 栈已满!"<<endl;
        return false;
    }
    elems[count++] = element;
    return true;
}

template<class ElemType>
bool SeqStack<ElemType>::top(ElemType &element) {
    if(count == 0){
        cerr<<"warning: 栈为空!"<<endl;
        return false;
    }
    element = elems[count - 1];
    return true;
}

template<class ElemType>
bool SeqStack<ElemType>::pop() {
    if(count <= 0){
        cerr << "warning: 栈已空!"<<endl;
        return false;
    }
    count--;
    return true;
}

template<class ElemType>
bool SeqStack<ElemType>::pop(ElemType &element) {
    if(count <= 0){
        cerr << "warning: 栈已空!"<<endl;
        return false;
    }
    element = elems[count--];
    return true;
}

template<class ElemType>
SeqStack<ElemType> &SeqStack<ElemType>::operator=(const SeqStack<ElemType> &source) {
    if(&source != this){
        maxSize = source.maxSize;
        // 先释放原本的空间，再分配新的空间
        delete elems;
        elems = new ElemType[maxSize];
        count = source.count;
        for(int i = 0; i < this->length(); i++){
            elems[i] = source.elems[i];
        }
    }
    return *this;
}
#endif //DATASTRUCTURESANDALGORITHMS_SEQSTACK_HPP

