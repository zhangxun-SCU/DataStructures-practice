//
// Created by cw on 2022/8/31.
//

#include "MyLinkedList.h"

void MyLinkedList::insert(int data, int index) {
    Node insertNode = Node(data);
//    定义超出链表范围得异常
    MyException exception = MyException("Linked list out of range!");
    try {
        if (index < 0 || index > size) {
            throw exception;
        }
        if (size == 0) {
//            空链表初始化
            head = &insertNode;
            last = &insertNode;
        } else if (index == 0) {
//            插入头部
            insertNode.next = head;
            head = &insertNode;
        } else if (size == index) {
//            插入尾部
            last->next = &insertNode;
            last = &insertNode;
        } else {
//            插入中间: 先找到插入位置前面得节点
            Node* preNode = get(index - 1);
            insertNode.next = preNode->next;
            preNode->next = &insertNode;
        }
        size++;
    } catch (std::exception) {
        std::cout << exception.what() << std::endl;
    }
}