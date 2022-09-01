#include <iostream>
#include "MyArray.h"
#include "MyLinkedList.h"
using namespace std;
int main() {
/***********************数组测试*************************/
//    MyArray arr = MyArray(5);
//    arr.insert(0, 10);
////    arr.insert(50, 10);
//    arr.insert(1, 1);
//    arr.insert(2, 1);
//    arr.output();
//    cout<<"第一个数为:"<<arr[0]<<endl;
//    arr[0] = 5;
//    cout<<"第一个数为:"<<arr[0]<<endl;


/************************单向链表测试**********************/
    MyLinkedList myLinkedList = MyLinkedList();
    myLinkedList.insert(5, 0);
    myLinkedList.insert(2, 1);
    myLinkedList.insert(0, 2);
    myLinkedList.output();
    Node*ptr = myLinkedList.remove(1);
    cout<<"删除的数据是:"<<ptr->data<<endl;
    myLinkedList.output();
    Node *ptr1 = myLinkedList.get(1);
    cout<<"得到的数据是:"<<ptr1->data<<endl;
    myLinkedList.insert(10, 100);
    myLinkedList.get(100);
    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
    myLinkedList[0] = 10;
    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
    cout<<"第一百个数是:"<<myLinkedList[100]<<endl;
    return 0;
}

