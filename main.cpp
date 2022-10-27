#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>


#include "SingleLinkList.hpp"
#include "SeqStack.hpp"
#include "SeqList.hpp"
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


using namespace std;

int main() {
//    (new Calculator())->run();
//    (new FileEditor())->run();

    SeqStack<int> stack;
    int tmp = 0;
    stack.push(0);
    stack.push(1);
    stack.push(2);
    stack.top(tmp);
    stack.pop();
    stack.top(tmp);
    stack.clear();
    for(int i = 0; i < 1000; i++){
        stack.push(i);
    }
    cout << stack.length()<<endl;
    stack.push(1001);
}


