

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


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
#include "Matrix.hpp"
#include "BinaryTree.hpp"
#include "LinkHuffmanTree.hpp"
#include "HuffmanCompress.hpp"
#include "CourseScheduling.hpp"

// homework test
#include "My_Class/Ackerman.h"


using namespace std;

void visit(const int &element){
    cout << element << endl;
}

int main() {
//    (new Calculator())->run();
//    (new FileEditor())->run();
//    (new HuffmanCompress())->run();
    (new CourseScheduling<8>)->run();

    return 0;
}
