//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_PRIORITYQUEUE_HPP
#define DATASTRUCTURESANDALGORITHMS_PRIORITYQUEUE_HPP
#include "iostream"
#include "BinaryHeap.hpp"
using namespace std;

/**
 * 优先队列：使用最大堆/最小堆实现
 * @tparam ElemType
 */
template<class ElemType>
class PriorityQueue {
private:
    BinaryHeap<ElemType> elems;
    int count;
    int maxSize;
public:
    PriorityQueue();
    PriorityQueue(ElemType* tmp, int size, int maxSize=1000);
    void enQueue(ElemType key);
    ElemType deQueue();
    void output();
};

template<class ElemType>
PriorityQueue<ElemType>::PriorityQueue():count(0), maxSize(1000), elems(BinaryHeap<ElemType>()) {}

template<class ElemType>
PriorityQueue<ElemType>::PriorityQueue(ElemType *tmp, int size, int maxSize): count(size), maxSize(maxSize), elems(BinaryHeap<ElemType>(tmp, size, maxSize)){}

template<class ElemType>
void PriorityQueue<ElemType>::enQueue(ElemType key) {
    elems.add(key);
}

template<class ElemType>
ElemType PriorityQueue<ElemType>::deQueue() {
    return elems.del();
}

template<class ElemType>
void PriorityQueue<ElemType>::output() {
    elems.output();
}

#endif //DATASTRUCTURESANDALGORITHMS_PRIORITYQUEUE_HPP
