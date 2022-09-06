//
// Created by cw on 2022/9/6.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP
#define DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP

#include "MyLinkedList.hpp"

/*
 * 这里我先使用自己写的MyLinkedList，
 * 也可以直接使用C++模板库里自带的list或forward_list
 * 原理一样，方便我完善理解
 */
template<class T>
struct TreeNode {
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    explicit TreeNode(T data, TreeNode *ptrL = nullptr, TreeNode *ptrR = nullptr) : data(data), left(ptrL),
                                                                                    right(ptrR) {};
};

template<class T>
class MyBinaryTree {
private:
    unsigned int size;
    MyLinkedList<T> linkedList;
    TreeNode<T> *root;
public:
//    构造
    MyBinaryTree(int size, T*arr);
//  利用MyLinkedList创建二叉树
    TreeNode<T> *createBinaryTree(MyLinkedList<T> &inputList);
//    前序遍历
    void preOrderTraversal(TreeNode<T> *node);
//    中序遍历
    void inOrderTraversal(TreeNode<T> *node);
//    后序遍历
    void postOrderTraversal(TreeNode<T> *node);


};


#endif //DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP
