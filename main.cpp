#include <list>
#include <vector>
#include <iostream>

#include "SingleLinkedList.hpp"
#include "ArrayStack.hpp"
#include "Array.hpp"
#include "CircularQueue.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "Sort.hpp"
#include "Utils.hpp"

using namespace std;

int main() {
    SingleLinkedList<int> list;
    list.insert(1, 0);
    list.insert(2, 1);
    list.insert(3,1);
    list.output();

    list.deleteElem(0);
    list.output();

    int a;
    list.removeElem(0, a);

    list.output();
    cout<<a<<endl;
    cout<<list.empty()<<endl;
    list.insert(5, 0);
    list.clear();
    cout<<list.empty()<<endl;

    return 0;
}


