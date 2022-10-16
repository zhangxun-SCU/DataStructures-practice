#include <list>
#include <vector>
#include <iostream>

#include "SingleLinkList.hpp"
#include "ArrayStack.hpp"
#include "Array.hpp"
#include "CircularQueue.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "Sort.hpp"
#include "Utils.hpp"
#include "Calculator.hpp"
#include "CircleLinkList.hpp"
#include "DCLinkList.hpp"

using namespace std;

int main() {

//    (new Calculator())->Run();
//    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    Sort::bubbleSort(a, 10, Utils::tmp);
//    for(int i:a){
//        cout<<i<<" ";
//    }
//    cout<<endl;
//    DCLinkList<int> dc;
    int a;
    DCLinkList<int> ac;
    ac.insert(0, 1);
    ac.insert(1, 2);
    ac.insert(2, 3);
    ac.insert(3, 4);
    for(int i = 0; i < 4; i++){
        if(ac.getElem(i, a)){
            cout << a << " ";
        }
    }
    cout << endl;
    if(ac.removeElem(2, a)){
        cout << a << endl;
    }
    ac.deleteElem(1);
    for(int i = 0; i < 2; i++){
        if(ac.getElem(i, a)){
            cout << a << " ";
        }
    }
    return 0;
}


