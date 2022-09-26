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
};


#endif //DATASTRUCTURESANDALGORITHMS_NODE_HPP
