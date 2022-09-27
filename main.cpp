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
    int arr[10] = {1000, 20, 90, 6, 100, 4, 5, 2, 5, 1201};
    Sort::quickSort_single_recursion(arr, 10, Utils::s2l);
    for(auto i:arr){
        cout<< i << " ";
    }
    cout<<endl;
    return 0;
}


