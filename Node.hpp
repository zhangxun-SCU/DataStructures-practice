//
// Created by cw on 2022/9/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_NODE_HPP
#define DATASTRUCTURESANDALGORITHMS_NODE_HPP


template<class ElemType>
struct Node {
    ElemType data;
    Node<ElemType> *next;

    Node() = default;

    explicit Node(ElemType data, Node *ptr = nullptr) : data(data), next(ptr) {};

    Node(Node<ElemType> &source){
        data = source.data;
        next = source.next;
    }
};

template<class ElemType>
struct NodeDbl{
    ElemType data;
    Node<ElemType> *prev;
    Node<ElemType> *next;

    NodeDbl() = default;
    NodeDbl(ElemType data, Node<ElemType> *prevPtr, NodeDbl<ElemType> *nextPtr): data(data), prev(prevPtr), next(nextPtr) {};
    NodeDbl(NodeDbl<ElemType> &source){
        data = source.data;
        prev = source.prev;
        next = source.next;
    }
    // 有参构造
};
#endif //DATASTRUCTURESANDALGORITHMS_NODE_HPP
