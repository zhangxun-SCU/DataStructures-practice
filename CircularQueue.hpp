//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
#define DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
#include <iostream>

using namespace std;
template<class ElemType>
class CircularQueue {
private:
    ElemType *elems;
    int front;
    int rear;
    unsigned int capacity;
    int count;
public:
    explicit CircularQueue(unsigned int capacity = 100);
    CircularQueue(const CircularQueue<ElemType> &source);
    ~CircularQueue();
    // 长度
    int length() const;
    // 判空
    bool empty() const;
    // 清空
    void clear();
    // 遍历
    void traverse(void(*visit)(const ElemType &)) const;
    // 入队
    bool enQueue(ElemType &element);
    // 出队
     bool deQueue();
     // 出队并返回
     bool deQueue(ElemType &element);
     // 对头
     bool getHead(ElemType &element);
     // 重载
     CircularQueue<ElemType> &operator=(const CircularQueue<ElemType> &source);
};

template<class ElemType>
CircularQueue<ElemType>::CircularQueue(unsigned int capacity):capacity(capacity), count(0), front(0), rear(0), elems(new ElemType[capacity]){}

template<class ElemType>
CircularQueue<ElemType>::CircularQueue(const CircularQueue<ElemType> &source) {
    capacity = source.capacity;
    elems = new ElemType[capacity];
    count = source.count;
    front = source.front, rear = source.rear;
    for(int temp = front; (temp + 1) % capacity != rear; temp = (temp + 1) % capacity){
        elems[temp] = source.elems[temp];
    }
}

template<class ElemType>
CircularQueue<ElemType>::~CircularQueue() {
    delete[] elems;
}

template<class ElemType>
int CircularQueue<ElemType>::length() const {
    return count;
}

template<class ElemType>
bool CircularQueue<ElemType>::empty() const {
    return (front + 1) % capacity == rear;
}

template<class ElemType>
void CircularQueue<ElemType>::clear() {
    rear = (front + 1) % capacity;
}

template<class ElemType>
void CircularQueue<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    for(int temp = front; (temp + 1) % capacity != rear; temp = (temp + 1) % capacity){
        visit(elems[temp]);
    }
}

template<class ElemType>
bool CircularQueue<ElemType>::enQueue(ElemType &element) {

}

template<class ElemType>
bool CircularQueue<ElemType>::deQueue() {

}

template<class ElemType>
bool CircularQueue<ElemType>::deQueue(ElemType &element) {

}

template<class ElemType>
bool CircularQueue<ElemType>::getHead(ElemType &element) {

}

#endif //DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
