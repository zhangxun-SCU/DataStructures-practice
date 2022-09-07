//
// Created by cw on 2022/9/6.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP
#define DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP

#include <list>
#include <iostream>
/*
 * 使用C++模板库的list实现
 * 避免使用自己的list后因为改了一点bug所有代码都需要改的屎山代码出现
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
    std::list<T> List;
    TreeNode<T> *root;
public:
//    构造
    MyBinaryTree(int size, std::list<T>);
//  利用MyLinkedList创建二叉树
    TreeNode<T> *createBinaryTree(std::list<T>);
//    前序遍历
    void preOrderTraversal(TreeNode<T> *node);
//    中序遍历
    void inOrderTraversal(TreeNode<T> *node);
//    后序遍历
    void postOrderTraversal(TreeNode<T> *node);


};

template<class T>
MyBinaryTree<T>::MyBinaryTree(int size, std::list<T> list): size(size), List(list) {}

template<class T>
TreeNode<T> *MyBinaryTree<T>::createBinaryTree(std::list<T> list) {
    TreeNode<T>* node;
    if(list.empty()){
        return nullptr;
    }
    T data = list.pop_front();
    if(data!=0){
        node = new TreeNode<T>(data);
        node->left = createBinaryTree(list);
        node->right = createBinaryTree(list);
    }
}

//template<class T>
//void MyBinaryTree<T>::preOrderTraversal(TreeNode<T> *node) {
//    if(node->data == 0){
//        return;
//    }
//    std::cout<<node->data<<" "<<
//}
#endif //DATASTRUCTURESANDALGORITHMS_MYBINARYTREE_HPP
