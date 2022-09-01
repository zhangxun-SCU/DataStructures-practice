//
// Created by cw on 2022/8/31.
//

#include "MyLinkedList.h"

MyException out_of_list_exception = MyException("Linked list out of range!");

MyLinkedList::MyLinkedList():size(0), head(nullptr), last(nullptr) {}

void MyLinkedList::insert(int data, int index) {
    Node tmp = Node(data);
    Node *insertNode = &tmp;
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
            Node *preNode = get(index - 1);
            insertNode->next = preNode->next;
            preNode->next = insertNode;
        }
        size++;
    } catch (MyException& e) {
        std::cout << out_of_list_exception.what() << std::endl;
    }
}

Node *MyLinkedList::remove(int index) {
    Node *removeNode = nullptr;
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
            Node *prevNode = get(index - 1);
            removeNode = prevNode->next;
            prevNode->next = nullptr;
            last = prevNode;
        } else {
//            删除中间节点
            Node *prevNode = get(index - 1);
            removeNode = prevNode->next;
            Node *nextNode = prevNode->next->next;
            prevNode->next = nextNode;
        }
        size--;
    } catch (MyException& e) {
        std::cout << out_of_list_exception.what() << std::endl;
    }
    return removeNode;
}

Node *MyLinkedList::get(int index) {
    Node *temp = head;
    try {
        if (index < 0 || index > 0) {
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

void MyLinkedList::output() {
    std::cout<<head->data<<std::endl;
    std::cout<<head->next->data<<std::endl;
    Node *temp = head;
    for (int i = 0; i < size; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}