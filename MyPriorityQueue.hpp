//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYPRIORITYQUEUE_HPP
#define DATASTRUCTURESANDALGORITHMS_MYPRIORITYQUEUE_HPP
#include "iostream"
#include "MyBinaryHeap.hpp"
using namespace std;

/**
 * 优先队列：使用最大堆/最小堆实现
 * @tparam ElemType
 */
template<class ElemType>
class MyPriorityQueue {
private:
    MyBinaryHeap<ElemType> elems;
    int count;
    int maxSize;
public:
    MyPriorityQueue();
    MyPriorityQueue(ElemType* tmp, int size, int maxSize=1000);
    void enQueue(ElemType key);
    ElemType deQueue();
    void output();
};

template<class ElemType>
MyPriorityQueue<ElemType>::MyPriorityQueue():count(0), maxSize(1000), elems(MyBinaryHeap<ElemType>()) {}

template<class ElemType>
MyPriorityQueue<ElemType>::MyPriorityQueue(ElemType *tmp, int size, int maxSize): count(size), maxSize(maxSize), elems(MyBinaryHeap<ElemType>(tmp, size, maxSize)){}

template<class ElemType>
void MyPriorityQueue<ElemType>::enQueue(ElemType key) {
    elems.add(key);
}

template<class ElemType>
ElemType MyPriorityQueue<ElemType>::deQueue() {
    return elems.del();
}

template<class ElemType>
void MyPriorityQueue<ElemType>::output() {
    elems.output();
}

#endif //DATASTRUCTURESANDALGORITHMS_MYPRIORITYQUEUE_HPP
