//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
#define DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
#include "Exception.h"
Exception queue_is_full("queue is full!");
Exception queue_is_empty("queue is empty!");
template<class T>
class CircularQueue {
private:
    T* queue;
    int front;
    int rear;
    unsigned int capacity;
public:
    explicit CircularQueue(unsigned int capacity);
    ~CircularQueue();
//    入队
    void enQueue(T element);
//    出队
    T deQueue();
//    输出
    void output();
};

template<class T>
CircularQueue<T>::CircularQueue(unsigned int capacity):capacity(capacity), rear(0), front(0), queue(new T[capacity]) {}

template<class T>
CircularQueue<T>::~CircularQueue() {
    delete[] queue;
    queue = nullptr;
}

template<class T>
void CircularQueue<T>::enQueue(T element) {
    try{
        if((rear + 1)%capacity == front){
            throw queue_is_full;
        }
        queue[rear] = element;
        rear = (rear + 1) % capacity;
    } catch(Exception &){
        std::cout<<queue_is_full.what()<<std::endl;
    }
}

template<class T>
T CircularQueue<T>::deQueue() {
    try{
        if(rear == front){
            throw queue_is_empty;
        }
        T deleteElement = queue[front];
        front = (front + 1) % capacity;
        return deleteElement;
    } catch (Exception&) {
        std::cout<<queue_is_empty.what()<<std::endl;
    }
}

template<class T>
void CircularQueue<T>::output() {
    for(int i = front; i!=rear; i = (i+1)%capacity){
        std::cout<<queue[i]<<" ";
    }
    std::cout<<std::endl;
}

#endif //DATASTRUCTURESANDALGORITHMS_CIRCULARQUEUE_HPP
