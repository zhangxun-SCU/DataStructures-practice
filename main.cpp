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


using namespace std;

void visit(const int &element){
    cout << element << endl;
}

int main() {
//    (new Calculator())->run();
//    (new FileEditor())->run();
    RefGenList<int> tmp;
    tmp.input();
    tmp.output();
    cout<<tmp.depth()<<endl;
    RefGenList<int> tmp2;
    tmp2.push(tmp);
    tmp2.output();
    return 0;

}


