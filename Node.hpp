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

    Node(Node<ElemType> &source) {
        data = source.data;
        next = source.next;
    }
};

/*
 * 双链表节点
 */
template<class ElemType>
struct NodeDbl {
    ElemType data;
    NodeDbl<ElemType> *prev;
    NodeDbl<ElemType> *next;

    NodeDbl() = default;

    explicit NodeDbl(ElemType data, NodeDbl<ElemType> *prevPtr = nullptr, NodeDbl<ElemType> *nextPtr = nullptr) : data(
            data), prev(prevPtr), next(nextPtr) {};

    NodeDbl(NodeDbl<ElemType> &source) {
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

    explicit BinTreeNode(ElemType data, BinTreeNode<ElemType> *ptrL = nullptr, BinTreeNode<ElemType> *ptrR = nullptr)
            : data(data), leftChild(ptrL),
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

    explicit TriBinTreeNode(ElemType data, TriBinTreeNode<ElemType> *ptrL = nullptr,
                            TriBinTreeNode<ElemType> *ptrR = nullptr, TriBinTreeNode<ElemType> *par = nullptr) : data(
            data), leftChild(ptrL),
                                                                                                                 rightChild(
                                                                                                                         ptrR),
                                                                                                                 parent(par) {};
};

/*
 * 顺序式哈夫曼树节点类
 */
template<class WeightType>
struct HuffmanTreeNode {
    // 权重数据
    WeightType weightType;
    // 父节点，左右孩子结点
    unsigned int parent, leftChild, rightChild;

    HuffmanTreeNode() = default;
    explicit HuffmanTreeNode(const WeightType &w, int p = 0, int l=0, int r=0): weightType(w), parent(p), leftChild(l), rightChild(r) {};
};

/*
 * 链式哈夫曼树结点类
 */
template<class WeightType>
struct LinkHuffmanTreeNode {
    // 权重
    WeightType weight;
    // 父节点和子节点
    LinkHuffmanTreeNode<WeightType> *parent, *leftChild, *rightChild;

    LinkHuffmanTreeNode() = default;

    explicit LinkHuffmanTreeNode(const WeightType &w, LinkHuffmanTreeNode<WeightType> *l = nullptr,
                                 LinkHuffmanTreeNode<WeightType> *r = nullptr,
                                 LinkHuffmanTreeNode<WeightType> *p = nullptr)
            : weight(w), leftChild(l), rightChild(r), parent(p) {};
};

#endif //DATASTRUCTURESANDALGORITHMS_NODE_HPP
