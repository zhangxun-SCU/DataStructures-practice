//
// Created by cw on 2022/10/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_REFGENLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_REFGENLIST_HPP

#include <iostream>
#include "RefGenListNode.hpp"

using namespace std;

/*
 * 广义表：引用树法
 */
template<class ElemType>
class RefGenList {
private:
    // 引用树法广义表头指针
    RefGenListNode<ElemType> *head;

    // 辅助函数
    // 显示以hd为头节点的广义表
    void showHelp(RefGenListNode<ElemType> *hd) const;

    // 就是hd为头节点的广义表深度
    int depthHelp(const RefGenListNode<ElemType> *hd);

    // 释放hd广义表
    void clearHelp(RefGenListNode<ElemType> *hd);

    // copy help
    void copyHelp(const RefGenListNode<ElemType> *sourceHead, RefGenListNode<ElemType> *destHead);

    // 创建以first为头节点的广义表
    static void createHelp(RefGenListNode<ElemType> *&first);

public:
    RefGenList();

    explicit RefGenList(RefGenListNode<ElemType> *hd);

    RefGenList(const RefGenList<ElemType> &source);

    ~RefGenList();

    // 返回广义表的第一个元素
    RefGenListNode<ElemType> *first() const;

    // 返回某节点的后继
    RefGenListNode<ElemType> *next(RefGenListNode<ElemType> *elemPtr) const;

    // 判空
    bool empty() const;

    // 将元素作为表头加入广义表最前面
    void push(const ElemType &element);  // atom节点
    void push(RefGenList<ElemType> &subList);  // list子表节点
    // 返回广义表深度
    int depth();

    // 输入广义表
    void input();

    // 显示广义表
    void output();

    // 重载
    RefGenList<ElemType> &operator=(const RefGenList<ElemType> &source);
};

template<class ElemType>
void RefGenList<ElemType>::showHelp(RefGenListNode<ElemType> *hd) const {
    cout << "(";
    for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != nullptr; tmpPtr = tmpPtr->nextLink) {
        if (tmpPtr->tag == LIST) {
            // 节点为子表，递归调用
            showHelp(tmpPtr->subLink);
        } else {
            // atom节点
            cout << tmpPtr->atom;
            if(tmpPtr->nextLink != nullptr){
                cout << ",";
            }
        }
    }
    cout << ")";
}

template<class ElemType>
int RefGenList<ElemType>::depthHelp(const RefGenListNode<ElemType> *hd) {
    /*
     * 观察广义表深度的定义，容易发现这也是一个递归，Depth(GL) = 1+MAX{Depth(ai)}
     */
    // 递归终点
    if (hd->nextLink == nullptr) {
        // 空表深度为1，而atom元素深度为0，不管即可
        return 1;
    }
    int subMaxDepth = 0;
    for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != nullptr; tmpPtr = tmpPtr->nextLink) {
        if (tmpPtr->tag == LIST) {
            // 元素为子表，开始递归求子表深度
            int curSubDepth = depthHelp(tmpPtr->subLink);
            if (subMaxDepth < curSubDepth) {
                subMaxDepth = curSubDepth;
            }
        }
    }
    // 执行到这里，说明不是空表，那么depth = 1 + max{depth(subList}}
    return 1 + subMaxDepth;
}

template<class ElemType>
void RefGenList<ElemType>::clearHelp(RefGenListNode<ElemType> *hd) {
    /*
     * 在清理广义表时，因为广义表的元素共享机制，可能有其他表引用了此表，故不能直接从物理上释放空间（delete）
     * 而是将引用数减一，若引用数为0，则物理上释放广义表
     */
    hd->ref--;
    if (hd->ref == 0) {
        // 释放空间
        RefGenListNode<ElemType> *prePtr, *tmpPtr;
        for (prePtr = hd, tmpPtr = hd->nextLink; tmpPtr != nullptr;prePtr = tmpPtr, tmpPtr = tmpPtr->nextLink) {
            delete prePtr;
            if (tmpPtr->tag == LIST) {
                // 子表节点，释放子表
                clearHelp(tmpPtr->subLink);
            }
        }
        delete prePtr;
    }
}

template<class ElemType>
void RefGenList<ElemType>::copyHelp(const RefGenListNode<ElemType> *sourceHead, RefGenListNode<ElemType> *destHead) {
    /*
     * 看广义表的结构，很容易联想到递归，的确，广义表与递归的联系是很深的，copy过程就可以使用递归实现
     * 主要在于广义表各元素的类型，只有原子节点需要复制值，而像子表节点直接复制子表这个关系，在复制值即可
     */
    destHead = new RefGenListNode<ElemType>(HEAD);
    RefGenListNode<ElemType> *destPtr = destHead;
    destHead->ref = 1;
    for (RefGenListNode<ElemType> *tmpPtr = sourceHead->nextLink; tmpPtr != nullptr; tmpPtr = tmpPtr->nextLink) {
        // 遍历sourceHead这一层，并复制关系和原子节点
        // 先拷贝元素类型
        destPtr->nextLink = new RefGenListNode<ElemType>(tmpPtr->tag);
        destPtr = destPtr->nextLink;
        if (tmpPtr->tag == LIST) {
            // 此元素为一个子表，递归调用copy，复制下一层
            copyHelp(tmpPtr->subLink, destPtr->subLink);
        } else {
            // 否则为原子元素，复制值
            destPtr->atom = tmpPtr->atom;
        }
    }
}

template<class ElemType>
void RefGenList<ElemType>::createHelp(RefGenListNode<ElemType> *&first) {
    // 读入一个字符
    char ch;
    cin >> ch;
    switch (ch) {
        case ')':
            // 递归终止条件
            return;
        case '(':
            // 表头为子表，生成子表节点
            first = new RefGenListNode<ElemType>(LIST);
            RefGenListNode<ElemType> *subHead;
            subHead = new RefGenListNode<ElemType>(HEAD);
            subHead->ref = 1;
            first->subLink = subHead;
            // 开始递归建立子表
            createHelp(subHead->nextLink);
            while (cin.peek() == ',' || cin.peek() == ' ') {
                cin.get();
            }
            // 递归建立这一层的下一个元素节点
            createHelp(first->nextLink);
            break;
        default:
            // 表头为原子atom节点，先将ch放回输入流
            cin.putback(ch);
            ElemType atomData;
            cin >> atomData;
            first = new RefGenListNode<ElemType>(ATOM);
            first->atom = atomData;
            while (cin.peek() == ',' || cin.peek() == ' ') {
                cin.get();
            }
            // 递归创建下一个节点元素
            createHelp(first->nextLink);
            break;
    }
}

template<class ElemType>
RefGenList<ElemType>::RefGenList() {
    // 建立一个空表
    head = new RefGenListNode<ElemType>(HEAD);
    head->ref = 1;
}

template<class ElemType>
RefGenList<ElemType>::RefGenList(RefGenListNode<ElemType> *hd) {
    copyHelp(hd, head);
}

template<class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType> &source) {
    copyHelp(source.head, head);
}

template<class ElemType>
RefGenList<ElemType>::~RefGenList() {
    clearHelp(head);
}

template<class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::first() const {
    // 返回广义表的第一个元素，即是head->next
    return head->nextLink;
}

template<class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::next(RefGenListNode<ElemType> *elemPtr) const {
    // 返回后继
    return elemPtr->nextLink;
}

template<class ElemType>
bool RefGenList<ElemType>::empty() const {
    return head->nextLink == nullptr;
}

template<class ElemType>
void RefGenList<ElemType>::push(const ElemType &element) {
    auto *newNode = new RefGenListNode<ElemType>(ATOM, head->nextLink);
    newNode->atom = element;
    head->nextLink = newNode;
}

template<class ElemType>
void RefGenList<ElemType>::push(RefGenList<ElemType> &subList) {
    auto *newNode = new RefGenListNode<ElemType>(LIST, head->nextLink);
    newNode->subLink = subList.head;
    head->nextLink = newNode;
}

template<class ElemType>
int RefGenList<ElemType>::depth() {
    return depthHelp(head);
}

template<class ElemType>
void RefGenList<ElemType>::input() {
    clearHelp(head);
    head = new RefGenListNode<ElemType>(HEAD);
    head->ref = 1;
    // 读入第一个'('
    while(cin.get() != '(')
        ;
    createHelp(head->nextLink);
}

template<class ElemType>
void RefGenList<ElemType>::output() {
    showHelp(head);
    cout << endl;
}

template<class ElemType>
RefGenList<ElemType> &RefGenList<ElemType>::operator=(const RefGenList<ElemType> &source) {
    if (&source != this) {
        // 先清理原本的空间
        clearHelp(head);
        // 在copy新的
        copyHelp(source.head, head);
    }
}

#endif //DATASTRUCTURESANDALGORITHMS_REFGENLIST_HPP
