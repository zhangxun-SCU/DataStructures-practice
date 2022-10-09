//
// Created by cw on 2022/9/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP

#include "Node.hpp"

template<class ElemType>
class CirLinkList {
private:
    Node<ElemType> *head;
    int size;

    // 辅助函数：返回index处节点指针
    Node<ElemType>* getElemptr(int index) const;

public:
//    构造函数
    CirLinkList();
//    拷贝构造
    CirLinkList(const CirLinkList<ElemType> &source);
//    析构
    virtual ~CirLinkList();
//    求长度
    int length();
//    判空
    bool empty();
//    清空
    void clear();
//    遍历执行
    void traverse(void (*visit)(const ElemType &)) const;
//    直接删除
    bool deleteElem(int index);
//    删除并返回
    bool removeElem(int idnex);
//    重载

};

#endif //DATASTRUCTURESANDALGORITHMS_CIRLINKLIST_HPP

template<class ElemType>
CirLinkList<ElemType>::CirLinkList():size(0) {
    head = new Node<ElemType>;
    // 循环链表，尾指针指向头元素
    head->next = head;
}

template<class ElemType>
CirLinkList<ElemType>::CirLinkList(const CirLinkList<ElemType> &source) {
    this->size = source.size;
    /****/



}

template<class ElemType>
CirLinkList<ElemType>::~CirLinkList() {
    /** delete **/
    clear();
    delete head;
}

template<class ElemType>
Node<ElemType> *CirLinkList<ElemType>::getElemptr(int index) const {
    Node<ElemType> *temp = head;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }
}

template<class ElemType>
int CirLinkList<ElemType>::length() {

}
