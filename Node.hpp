//
// Created by cw on 2022/9/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_NODE_HPP
#define DATASTRUCTURESANDALGORITHMS_NODE_HPP

/*
 * 单链表，单循环链表节点
 */
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

/*
 * 双链表节点
 */
template<class ElemType>
struct NodeDbl{
    ElemType data;
    NodeDbl<ElemType> *prev;
    NodeDbl<ElemType> *next;

    NodeDbl() = default;
    explicit NodeDbl(ElemType data, NodeDbl<ElemType> *prevPtr=nullptr, NodeDbl<ElemType> *nextPtr=nullptr): data(data), prev(prevPtr), next(nextPtr) {};
    NodeDbl(NodeDbl<ElemType> &source){
        data = source.data;
        prev = source.prev;
        next = source.next;
    }
    // 有参构造
};

/*
 * 二叉树节点TreeNode
 */
template<class T>
struct TreeNode {
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    explicit TreeNode(T data, TreeNode *ptrL = nullptr, TreeNode *ptrR = nullptr) : data(data), left(ptrL),
                                                                                    right(ptrR) {};
};
#endif //DATASTRUCTURESANDALGORITHMS_NODE_HPP
