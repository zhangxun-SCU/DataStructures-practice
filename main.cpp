#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "SeqList.hpp"
#include "SingleLinkList.hpp"
#include "SeqStack.hpp"
#include "LinkStack.hpp"
#include "CircularQueue.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "Sort.hpp"
#include "Utils.hpp"
#include "CircleLinkList.hpp"
#include "DCLinkList.hpp"
#include "CharString.hpp"
#include "FileEditor.hpp"
#include "Calculator.hpp"
#include "RefGenList.hpp"
#include "Matrix.hpp"
#include "LinkQueue.hpp"

using namespace std;

void visit(const int &element){
    cout << element << endl;
}

int main() {
//    (new Calculator())->run();
//    (new FileEditor())->run();
    CircularQueue<int> circularQueue;
    for(int i = 0; i < 100; i++){
        circularQueue.enQueue(i);
    }
    cout << circularQueue.empty() << circularQueue.length()<<endl;
    circularQueue.traverse(visit);

    for(int i = 0; i < 100; i++){
        circularQueue.deQueue();
    }
    cout << circularQueue.empty() << circularQueue.length()<<endl;
    circularQueue.enQueue(5);
    cout << circularQueue.empty() << circularQueue.length()<<endl;
    circularQueue.clear();
    cout << circularQueue.empty() << circularQueue.length()<<endl;
    circularQueue.enQueue(5);
    cout << circularQueue.empty() << circularQueue.length()<<endl;
    circularQueue.enQueue(5);
    circularQueue.enQueue(5);
    circularQueue.enQueue(5);
    circularQueue.enQueue(5);
    circularQueue.traverse(visit);
    cout << circularQueue.empty() << circularQueue.length()<<endl;

//    LinkQueue<int> linkQueue;
//    linkQueue.enQueue(1);

    return 0;
}


