#include <list>
#include <vector>
#include <iostream>
#include "MyLinkedList.hpp"
#include "MyArrayStack.hpp"
#include "MyArray.hpp"
#include "MyCircularQueue.hpp"
#include "MyBinaryTree.hpp"
#include "MyBinaryHeap.hpp"
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
//    MyArrayStack<int> stack;
//    if(stack.isEmpty()){
//        cout<<"现在有一个空栈"<<endl;
//    }
//    stack.push(10);
//    cout<<"现在第一个元素是："<<stack.peek()<<endl;
//    stack.push(100);
//    cout<<"现在第一个元素是："<<stack.peek()<<endl;
//    int tmp = stack.pop();
//    cout<<"删除的元素是："<<tmp<<endl;
//    cout<<"现在第一个元素是："<<stack.peek()<<endl;
//    cout<<"栈大小"<<stack.size()<<endl;
//    stack.push(1);
//    stack.push(2);
//    stack.push(2);
//    stack.push(3);
//    stack.push(3);
//    stack.push(3);
//    stack.push(4);
//    stack.push(4);
//    stack.push(4);
//    cout<<"栈大小"<<stack.size()<<endl;
//    cout<<"现在栈是否为空呢：";
//    if(stack.isEmpty()){
//        cout<<"yes"<<endl;
//    } else{
//        cout<<"No"<<endl;
//    }


/*****************模板数组**************************/
//    MyArray<int> array(5);
//    array.insert(0, 1);
//    array.insert(1, 2);
//    array.insert(2, 3);
//    array.output();
//    int temp = array.elementDelete(2);
//    cout<<temp<<endl;
//    array.output();
//    array.insert(10, 1);
//    array.resize();
//    array.resize();
//    array.insert(10, 1);
//    array.output();


/****************模板链表***********************************/
//    MyLinkedList<int> myLinkedList;
//    myLinkedList.insert(5, 0);
//    myLinkedList.insert(2, 1);
//    myLinkedList.insert(0, 2);
//    myLinkedList.output();
//    Node<int> *ptr = myLinkedList.remove(1);
//    cout<<"删除的数据是:"<<ptr->data<<endl;
//    myLinkedList.output();
//    Node<int> *ptr1 = myLinkedList.get(1);
//    cout<<"得到的数据是:"<<ptr1->data<<endl;
//    myLinkedList.insert(10, 100);
//    myLinkedList.get(100);
//    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
//    myLinkedList[0] = 10;
//    cout<<"第一个数是:"<< myLinkedList[0]<<endl;
//    cout<<"第一百个数是:"<<myLinkedList[100]<<endl;
//    myLinkedList.output();
//    float  arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    MyLinkedList<float> myLinkedList2(10, arr);
//    myLinkedList2.output();


/********************循环队列******************************/
//    需要注意的是循环对列的实际长度比capacity小1
//    MyCircularQueue<int> queue(5);
//    queue.enQueue(5);
//    queue.enQueue(4);
//    queue.enQueue(3);
//    queue.enQueue(2);
//    queue.enQueue(1);
//    queue.output();
//    int tmp1 = queue.deQueue();
//    int tmp2 = queue.deQueue();
//    cout<<"tmp1:"<<tmp1<<"  tmp2:"<<tmp2<<endl;
//    queue.output();

/********************二叉树*************************************/



/********************二叉堆：最小堆*************************************/
    vector<int> a{1, 3, 2, 6, 5, 7, 8, 9, 10};
    MyBinaryHeap<int> myBinaryHeap(a);
    myBinaryHeap.output();
    myBinaryHeap.add(0);
    myBinaryHeap.output();
    for(auto i :a){
        cout<<i<<" ";
    }
    cout<<endl;
    vector<int> b{5, 6, 7, 5, 4, 8, 10, 5, 7, 2, 3, 4};
    MyBinaryHeap<int> myBinaryHeap1(b);
    myBinaryHeap1.output();

    return 0;
}
