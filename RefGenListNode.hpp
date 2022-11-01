//
// Created by cw on 2022/10/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_REFGENLISTNODE_HPP
#define DATASTRUCTURESANDALGORITHMS_REFGENLISTNODE_HPP
enum RefGenListNodeType{
    HEAD,  // 头节点
    ATOM,  // 原子结构
    LIST,  // 表节点
};

/*
 * 广义表节点
 */
template<class ElemType>
struct RefGenListNode {
    RefGenListNodeType tag;
    // 指向同一层中的下一个节点
    RefGenListNode<ElemType> *nextLink;
    union {
        int ref{};  // 表头节点
        ElemType atom;  // 原子节点
        RefGenListNode<ElemType> *subLink;  // 表节点，指向子表
    };

    explicit RefGenListNode(RefGenListNodeType tag=HEAD, RefGenListNode<ElemType> *next= nullptr):tag(tag), nextLink(next) {};
};


#endif //DATASTRUCTURESANDALGORITHMS_REFGENLISTNODE_HPP
