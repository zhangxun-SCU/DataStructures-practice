//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_HPP

#include "MyException.h"
MyException out_of_list_exception = MyException("Linked list out of range!");

template<class T>
struct Node {
    T data;
    Node<T>* next;

    explicit Node(T data, Node*ptr = nullptr):data(data),next(ptr){};
};

template<class T>
class MyLinkedList {
private:
    Node<T> *head;
    Node<T> *last;
    int size;
public:
    MyLinkedList();
    MyLinkedList(unsigned int long, T *arr);
    //    插入节点
    void insert(T, int);

//    删除节点
    Node<T> *remove(int);

//    查找
    Node<T> *get(int);

//    重载下标运算符
    T& operator [] (unsigned int); // 可修改

//    输出链表数据
    void output();

};

template<class T>
MyLinkedList<T>::MyLinkedList(): size(0), head(nullptr), last(nullptr) {}

template<class T>
MyLinkedList<T>::MyLinkedList(unsigned int long, T *arr) {
    this->size = 0;
    for(int i = 0; i < 10; i++){
        this->insert(arr[i], i);
    }
}

template<class T>
void MyLinkedList<T>::insert(T data, int index) {
//    注意insertNode一定要使用new来创建，不然在函数执行完毕后，节点会被销毁
    Node<T> *insertNode = new Node<T>(data);
//    定义超出链表范围得异常
    try {
        if (index < 0 || index > size) {
            throw out_of_list_exception;
        }
        if (size == 0) {
//            空链表初始化
            head = insertNode;
            last = insertNode;
        } else if (index == 0) {
//            插入头部
            insertNode->next = head;
            head = insertNode;
        } else if (size == index) {
//            插入尾部
            last->next = insertNode;
            last = insertNode;
        } else {
//            插入中间: 先找到插入位置前面得节点
            Node<T> *preNode = get(index - 1);
            insertNode->next = preNode->next;
            preNode->next = insertNode;
        }
        size++;
    } catch (MyException& e) {
        std::cout << out_of_list_exception.what() << std::endl;
    }
}

template<class T>
Node<T> *MyLinkedList<T>::remove(int index) {
    Node<T> *removeNode = nullptr;
    try {
        if (index < 0 || index > size) {
            throw out_of_list_exception;
        }
        if (index == 0) {
//            删除头节点
            removeNode = head;
            head = head->next;
        } else if (index == size - 1) {
//            删除尾节点
            Node<T> *prevNode = get(index - 1);
            removeNode = prevNode->next;
            prevNode->next = nullptr;
            last = prevNode;
        } else {
//            删除中间节点
            Node<T> *prevNode = get(index - 1);
            removeNode = prevNode->next;
            Node<T> *nextNode = prevNode->next->next;
            prevNode->next = nextNode;
        }
        size--;
    } catch (MyException& e) {
        std::cout << out_of_list_exception.what() << std::endl;
    }
    return removeNode;
}

template<class T>
Node<T> *MyLinkedList<T>::get(int index) {
    Node<T> *temp = head;
    try {
        if (index < 0 || index > size) {
            throw out_of_list_exception;
        }
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
    } catch (MyException& e) {
        std::cout << out_of_list_exception.what() << std::endl;
    }
    return temp;
}

template<class T>
T &MyLinkedList<T>::operator[](unsigned int index) {
    Node<T>* temp = nullptr;
    try{
        if(index < 0 || index > size){
            throw out_of_list_exception;
        }
        temp = get(index);
    } catch (MyException&){
        std::cout<<out_of_list_exception.what()<<std::endl;
    }

//    if(temp == nullptr){
//        return null_;
//    }
    return temp->data;
}

template<class T>
void MyLinkedList<T>::output() {
    Node<T> *temp = head;
    for (int i = 0; i < size; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

#endif //DATASTRUCTURESANDALGORITHMS_MYLINKEDLIST_HPP

