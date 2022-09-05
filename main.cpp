#include <iostream>
#include "MyArray.h"
#include "MyLinkedList.h"
#include "MyArrayStack.h"
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
//    arr.output();


/************************单向链表测试**********************/
//    MyLinkedList myLinkedList = MyLinkedList();
//    myLinkedList.insert(5, 0);
//    myLinkedList.insert(2, 1);
//    myLinkedList.insert(0, 2);
//    myLinkedList.output();
//    Node*ptr = myLinkedList.remove(1);
//    cout<<"删除的数据是:"<<ptr->data<<endl;
//    myLinkedList.output();
//    Node *ptr1 = myLinkedList.get(1);
//    cout<<"得到的数据是:"<<ptr1->data<<endl;
//    myLinkedList.insert(10, 100);
//    myLinkedList.get(100);
//    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
//    myLinkedList[0] = 10;
//    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
//    cout<<"第一百个数是:"<<myLinkedList[100]<<endl;


/************************数组栈测试*************************/
    MyArrayStack stack = MyArrayStack();
    if(stack.isEmpty()){
        cout<<"现在有一个空栈"<<endl;
    }
    stack.push(10);
    cout<<"现在第一个元素是："<<stack.peek()<<endl;
    stack.push(100);
    cout<<"现在第一个元素是："<<stack.peek()<<endl;
    int tmp = stack.pop();
    cout<<"删除的元素是："<<tmp<<endl;
    cout<<"现在第一个元素是："<<stack.peek()<<endl;
    cout<<"栈大小"<<stack.size()<<endl;
    stack.push(1);
    stack.push(2);
    stack.push(2);
    stack.push(3);
    stack.push(3);
    stack.push(3);
    stack.push(4);
    stack.push(4);
    stack.push(4);
    cout<<"栈大小"<<stack.size()<<endl;
    cout<<"现在栈是否为空呢：";
    if(stack.isEmpty()){
        cout<<"yes"<<endl;
    } else{
        cout<<"No"<<endl;
    }
    return 0;
}

