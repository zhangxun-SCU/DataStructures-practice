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
 * 双叉二叉树节点TreeNode
 */
template<class ElemType>
struct BinTreeNode {
    ElemType data;
    BinTreeNode<ElemType> *leftChild;
    BinTreeNode<ElemType> *rightChild;
    explicit BinTreeNode(ElemType data, BinTreeNode<ElemType> *ptrL=nullptr, BinTreeNode<ElemType> *ptrR=nullptr) : data(data), leftChild(ptrL),
                                                                                    rightChild(ptrR) {};
};

/*
 * 三叉二叉树节点类
 */
template<class ElemType>
struct TriBinTreeNode {
    ElemType data;
    TriBinTreeNode<ElemType> *leftChild;
    TriBinTreeNode<ElemType> *rightChild;
    TriBinTreeNode<ElemType> *parent;
    explicit TriBinTreeNode(ElemType data, TriBinTreeNode<ElemType> *ptrL=nullptr, TriBinTreeNode<ElemType> *ptrR=nullptr, TriBinTreeNode<ElemType> *par= nullptr) : data(data), leftChild(ptrL),
                                                                                                                                             rightChild(ptrR), parent(par) {};
};
#endif //DATASTRUCTURESANDALGORITHMS_NODE_HPP
