#include <list>
#include <vector>
#include <iostream>

#include "LinkedList.hpp"
#include "ArrayStack.hpp"
#include "Array.hpp"
#include "CircularQueue.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "Sort.hpp"
#include "Utils.hpp"

using namespace std;

bool cmp(const int &a, const int &b) {
    return a > b;
}

int main() {
    int b[]{5, 6, 7, 5, 4, 8, 10, 5, 7, 2, 3, 4};
    bool (*ptr)(const int &, const int &);
    int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 0};
    ptr = cmp;
    Sort::cockTailSort(arr, 10, ptr);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}


