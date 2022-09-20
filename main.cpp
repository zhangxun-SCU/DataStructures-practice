#include <list>
#include <vector>
#include <iostream>
#include "MyLinkedList.hpp"
#include "MyArrayStack.hpp"
#include "MyArray.hpp"
#include "MyCircularQueue.hpp"
#include "MyBinaryTree.hpp"
#include "MyBinaryHeap.hpp"
#include "MyPriorityQueue.hpp"
#include "MySort.hpp"
#include "Utils.hpp"
using namespace std;

bool cmp(const int &a,const int &b){
    return a>b;
}
int main() {

    int b[]{5, 6, 7, 5, 4, 8, 10, 5, 7, 2, 3, 4};
    bool (*ptr)(const int &, const int&);

    ptr = cmp;
    MySort::bubbleSort(b, 12, ptr);
    for(int i : b){
        cout << i << " ";
    }
    cout<<endl;
    return 0;
}


