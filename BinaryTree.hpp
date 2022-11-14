//
// Created by cw on 2022/9/6.
//

#ifndef DATASTRUCTURESANDALGORITHMS_BINARYTREE_HPP
#define DATASTRUCTURESANDALGORITHMS_BINARYTREE_HPP

#include <iostream>

#include "LinkStack.hpp"
#include "LinkQueue.hpp"
#include "Node.hpp"

using namespace std;


/*
 * 二叉树：链式实现
 */
template<class ElemType>
class BinaryTree {
private:
    unsigned int size;
    BinTreeNode<ElemType> *root;

    //  复制辅助函数
    BinTreeNode<ElemType> *copyTreeHelp(BinTreeNode<ElemType> *r);

    // 销毁辅助函数
    void destroyHelp(BinTreeNode<ElemType> *r);

    // 先序遍历
    void preOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;

    // 中序遍历
    void inOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;

    // 后序遍历
    void postOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;

    // 高度
    int heightHelp(const BinTreeNode<ElemType> *r) const;

    // 返回节点个数
    int nodeCountHelp(const BinTreeNode<ElemType> *r) const;

    // 返回双亲
    BinTreeNode<ElemType> *parentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const;

    // 以树状形式显示二叉树, level为层次
    static void disPlayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);

    // 使用前序序列和中序序列构造二叉树的辅助函数
    static void
    createBinaryTreeHelp(BinTreeNode<ElemType> *r, ElemType *pre, ElemType *in, int preLeft, int preRight, int inLeft,
                         int inRight);
    // 找到某节点最左边的子孙结点并入栈经过的结点，中序遍历的辅助函数
    static void goAlongLeft(BinTreeNode<ElemType> *cur, LinkStack<BinTreeNode<ElemType> *> &nodeStack);
public:
    // 构造、copy构造、析构
    BinaryTree();

    explicit BinaryTree(const ElemType &element);

    BinaryTree(const BinaryTree<ElemType> &source);

    explicit BinaryTree(BinTreeNode<ElemType> *r);

    virtual ~BinaryTree();

    // root
    BinTreeNode<ElemType> *getRoot() const;

    // 判空
    bool empty() const;

    // 求高度
    int height() const;

    // 返回节点值
    bool getElem(BinTreeNode<ElemType> *cur, ElemType &element) const;

    // 设置结点值
    bool setElem(BinTreeNode<ElemType> *cur, ElemType &element);

    // 四个遍历
    void preOrder(void(*visit)(const ElemType &));

    void preOrderNoRecur(void(*visit)(const ElemType &));

    void inOrder(void(*visit)(const ElemType &));

    void inOrderNoRecur(void(*visit)(const ElemType &));

    void postOrder(void(*visit)(const ElemType &));

    void postOrderNoRecur(void(*visit)(const ElemType &));

    void levelOrder(void(*visit)(const ElemType &));

    // 节点个数
    int nodeCount() const;

    // 找孩子和父亲
    BinTreeNode<ElemType> *leftChild(const BinTreeNode<ElemType> *cur) const;

    BinTreeNode<ElemType> *rightChild(const BinTreeNode<ElemType> *cur) const;

    BinTreeNode<ElemType> *parent(const BinTreeNode<ElemType> *cur) const;

    // 插入孩子
    bool insertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &element);

    bool insertRightChild(BinTreeNode<ElemType> *cur, const ElemType &element);

    // 删除
    bool deleteLeftChild(BinTreeNode<ElemType> *cur);

    bool deleteRightChild(BinTreeNode<ElemType> *cur);

    // 重载
    BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &source);

    // static
    static void disPlayBTWithTreeShape(const BinaryTree<ElemType> &bt);

    static BinaryTree<ElemType> &createBinaryTree(ElemType *pre, ElemType *in, int n);
};

template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::copyTreeHelp(BinTreeNode<ElemType> *r) {
    /*
     * 递归实现：先复制左右子树然后以左右子树生成根节点，一个一个复制，从叶子节点开始
     */
    if (r == nullptr) {
        return nullptr;
    }
    BinTreeNode<ElemType> *lChild = copyTreeHelp(r->leftChild);
    BinTreeNode<ElemType> *rChild = copyTreeHelp(r->rightChild);
    BinTreeNode<ElemType> *rt = new BinTreeNode<ElemType>(r->data, lChild, rChild);
    return rt;
}

template<class ElemType>
void BinaryTree<ElemType>::destroyHelp(BinTreeNode<ElemType> *r) {
    /*
     * 递归实现：先delete左右子树，再删除根节点
     */
    if (r != nullptr) {
        destroyHelp(r->leftChild);
        destroyHelp(r->rightChild);
        delete r;
        r = nullptr;
    }
}

template<class ElemType>
void BinaryTree<ElemType>::preOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    /*
     * 根节点、左子树、右子树
     */
    // 递归实现：
    if (r != nullptr) {
        visit(r->data);
        preOrderHelp(r->leftChild, visit);
        preOrderHelp(r->rightChild, visit);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::inOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    /*
     * 左子树、根节点、右子树
     */
    // 递归实现
    if (r != nullptr) {
        inOrderHelp(r->leftChild, visit);
        visit(r->data);
        inOrderHelp(r->rightChild, visit);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::postOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    /*
     * 左子树、右子树、根节点
     */
    // 递归实现
    if (r != nullptr) {
        postOrderHelp(r->leftChild, visit);
        postOrderHelp(r->rightChild, visit);
        visit(r->data);
    }
}

template<class ElemType>
int BinaryTree<ElemType>::heightHelp(const BinTreeNode<ElemType> *r) const {
    /*
     * 递归实现：二叉树高度为左右子树高度的最大值加1
     */
    if (r == nullptr) {
        return 0;
    }
    int lHeight = heightHelp(r->leftChild);
    int rHeight = heightHelp(r->rightChild);
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

template<class ElemType>
int BinaryTree<ElemType>::nodeCountHelp(const BinTreeNode<ElemType> *r) const {
    /*
     * 递归实现，二叉树结点数量就是左子树+右子树结点数量+1
     */
    if (r == nullptr) {
        // 递归结束条件：遇到叶子节点的左右子树（空），返回0
        return 0;
    }
    return nodeCountHelp(r->leftChild) + nodeCountHelp(r->rightChild) + 1;
}

template<class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::parentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const {
    /*
     * 递归实现：
     */
    if(r ->leftChild == cur || r->rightChild == cur){
        return r;
    }
    parentHelp(r->leftChild, cur);
    parentHelp(r->rightChild, cur);
}

template<class ElemType>
void BinaryTree<ElemType>::disPlayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level) {
    if (r != nullptr) {
        // 非空，打印出来(是横着打印的)
        cout.width(3);
        disPlayBTWithTreeShapeHelp(r->rightChild, level + 1);
        cout << endl;
        for (int tmpPos = 0; tmpPos < level - 1; tmpPos++) {
            cout << "   ";
        }
        cout << r->data;
        disPlayBTWithTreeShapeHelp(r->leftChild, level + 1);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::createBinaryTreeHelp(BinTreeNode<ElemType> *r, ElemType *pre, ElemType *in, int preLeft,
                                                int preRight, int inLeft, int inRight) {
    if(inLeft > inRight){
        // 没有结点了，空二叉树(没有子树，中序序列就是判断左右子树)
        r = nullptr;
    } else {
        // 根据前序序列的第一个也就是根节点生成根节点
        r = new BinTreeNode<ElemType>(pre[preLeft]);
        // 查找根结点在中序序列中的位置，由此区别出左右子树
        int mid = inLeft;
        while(in[mid] != pre[preLeft]){
            mid++;
        }
        // 生成左子树
        createBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid-1);
        // 生成右子树
        createBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft+1, preRight, mid+1, inRight);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::goAlongLeft(BinTreeNode<ElemType> *cur, LinkStack<BinTreeNode<ElemType> *> &nodeStack) {
    while(cur){
        nodeStack.push(cur);
        cur = cur->leftChild;
    }
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree() {
    root = nullptr;
    size = 0;
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &element) {
    root = new BinTreeNode<ElemType>(element);
    size = 1;
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &source) {
    root = copyTreeHelp(source.root);
    size = source.size;
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r) {
    root = r;
    size = nodeCountHelp(root);
}

template<class ElemType>
BinaryTree<ElemType>::~BinaryTree() {
    size = 0;
    destroyHelp(root);
}

template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::getRoot() const {
    return root;
}

template<class ElemType>
bool BinaryTree<ElemType>::empty() const {
    // 检查root是否为空即可(或者检查size?)
    return root == nullptr;
}

template<class ElemType>
int BinaryTree<ElemType>::height() const {
    return heightHelp(root);
}

template<class ElemType>
bool BinaryTree<ElemType>::getElem(BinTreeNode<ElemType> *cur, ElemType &element) const {
    if (cur != nullptr) {
        cerr << "warning: 取值失败!" << endl;
        return false;
    }
    element = cur->data;
    return true;
}

template<class ElemType>
bool BinaryTree<ElemType>::setElem(BinTreeNode<ElemType> *cur, ElemType &element) {
    if (cur == nullptr) {
        cerr << "warning: 取值失败!" << endl;
        return false;
    }
    cur->data = element;
    return true;
}

template<class ElemType>
void BinaryTree<ElemType>::preOrder(void (*visit)(const ElemType &)) {
    preOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::preOrderNoRecur(void (*visit)(const ElemType &)) {
    /*
     * 前序遍历：使用循环/迭代遍历
     *     重点在于理解前序遍历的顺序：D->L->R，并且对于右子树也是一个树，同样也是有左右子树
     */
    // 存储前面结点的栈
    LinkStack<BinTreeNode<ElemType> *> nodeStack;
    // 遍历的当前结点
    BinTreeNode<ElemType> *cur = root;
    while(true){
        while(cur){
            visit(cur->data);
            nodeStack.push(cur->rightChild);
            cur = cur->leftChild;
        }
        if(nodeStack.empty()){
            break;
        }
        // cur为null,pop出栈内结点
        nodeStack.pop(cur);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::inOrder(void (*visit)(const ElemType &)) {
    inOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::inOrderNoRecur(void (*visit)(const ElemType &)) {
    /*
     * 中序遍历：循环实现
     */
    LinkStack<BinTreeNode<ElemType> *> nodeStack;
    BinTreeNode<ElemType> *cur = root;
    /*
     * 方法一：
     */
//    while(true){
//        // 沿着此路径向左一直到此子树上最左边的叶子节点，并将沿途结点入栈(将结点按批次入栈)
//        goAlongLeft(cur, nodeStack);
//        if(nodeStack.empty()){
//            // 栈为空说明遍历完了，退出
//            break;
//        }
//        nodeStack.pop(cur);
//        visit(cur->data);
//        // 转到对应的右子树
//        cur = cur->rightChild;
//    }

    /*
     * 方法二：
     * 上面是使用goAlongLeft得到的中序遍历代码，但中序遍历的本质就在于要找到遍历的起始点和其直接后继，
     * 而找到其直接后继主要分为两种情况：一是右子树存在时直接后继一定存在于右子树的最左边的叶子结点，如果不存咋，直接后继就是包含此结点为左子树的最小祖先结点
     * 所以可以优化代码，更简单的实现中序遍历
     */
    while(true){
        if(cur){
            // 如果cur不为null,那么一直向左走，并入栈途经的结点
            nodeStack.push(cur);
            cur = cur->leftChild;
        } else if(!nodeStack.empty()){
            // 如果cur为null且栈不为空说明找到子树的最左子节点了，弹出此节点，遍历此节点
            nodeStack.pop(cur);
            visit(cur->data);
            // 最左的子节点只能是叶子节点或者是中间结点,按照LDR的顺序应该转到右子树（如果有右子树的话）
            cur = cur->rightChild;
        } else {
            // cur为空且栈空说明已经到最后一个结点了，退出遍历
            break;
        }
    }
}

template<class ElemType>
void BinaryTree<ElemType>::postOrder(void (*visit)(const ElemType &)) {
    postOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::postOrderNoRecur(void (*visit)(const ElemType &)) {

}

template<class ElemType>
void BinaryTree<ElemType>::levelOrder(void (*visit)(const ElemType &)) {
    /*
     * 层序遍历：即按照二叉树的层次遍历二叉树，使用循环即可简单实现，但要使用队列
     */
    // 使用队列来存放一层的结点
    LinkQueue<BinaryTree<ElemType> *> nodeQueue;
    BinTreeNode<ElemType> *cur;  // 当前结点，即调用visit的结点
    if (root != nullptr) {
        // 确保为非空树，然后将根节点也就是第一层入队
        nodeQueue.enQueue(root);
    }
    while (!nodeQueue.empty()) {
        // 队列非空，说明还可能有下一层（！！！focus：可能有下一层是因为如果遍历已经到了最后一层，但我们不知
        // 道这时最后一层，还要看一下它的左右孩子是否存在才能确定是否是最后一层）
        nodeQueue.deQueue(cur);
        visit(cur->data);
        if (cur->leftChild != nullptr) {
            // 左子树不为空，说明左子树还有下一层，将leftChild入队
            nodeQueue.enQueue(cur->leftChild);
        }
        if (cur->rightChild != nullptr) {
            // 同上
            nodeQueue.enQueue(cur->rightChild);
        }
    }
}

template<class ElemType>
int BinaryTree<ElemType>::nodeCount() const {
    return nodeCountHelp(root);
}

template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::leftChild(const BinTreeNode<ElemType> *cur) const {
    return cur->leftChild;
}

template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::rightChild(const BinTreeNode<ElemType> *cur) const {
    return cur->rightChild;
}

template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::parent(const BinTreeNode<ElemType> *cur) const {
    return parentHelp(root, cur);
}

template<class ElemType>
bool BinaryTree<ElemType>::insertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &element) {
    if (cur->leftChild != nullptr) {
        cerr << "warning: 插入结点失败，结点已存在!" << endl;
        return false;
    }
    cur->leftChild = new BinTreeNode<ElemType>(element);
    return true;
}

template<class ElemType>
bool BinaryTree<ElemType>::insertRightChild(BinTreeNode<ElemType> *cur, const ElemType &element) {
    if (cur->rightChild != nullptr) {
        cerr << "warning: 插入结点失败，结点已存在!" << endl;
        return false;
    }
    cur->rightChild = new BinTreeNode<ElemType>(element);
    return true;
}

template<class ElemType>
bool BinaryTree<ElemType>::deleteLeftChild(BinTreeNode<ElemType> *cur) {
    if (cur == nullptr) {
        cerr << "warning: 删除失败，结点不存在!" << endl;
        return false;
    }
    delete cur;
    return true;
}

template<class ElemType>
bool BinaryTree<ElemType>::deleteRightChild(BinTreeNode<ElemType> *cur) {
    if (cur == nullptr) {
        cerr << "warning: 删除失败，结点不存在!" << endl;
        return false;
    }
    delete cur;
    return true;
}

template<class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &source) {
    if (&source != this) {
        destroyHelp(root);
        root = copyTreeHelp(source.root);
    }
    return *this;
}

template<class ElemType>
void BinaryTree<ElemType>::disPlayBTWithTreeShape(const BinaryTree<ElemType> &bt) {
    disPlayBTWithTreeShapeHelp(bt.getRoot(), 1);
    cout << endl;
}

template<class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::createBinaryTree(ElemType *pre, ElemType *in, int n) {
    // 构建的二叉树的根
    BinTreeNode<ElemType> *r;
    createBinaryTreeHelp(r, pre, in, 0, n-1, 0, n-1);
    BinaryTree<ElemType> *newTree = new BinaryTree<ElemType>(r);
    return newTree;
}

#endif //DATASTRUCTURESANDALGORITHMS_BINARYTREE_HPP
