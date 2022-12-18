

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

// homework test
#include "My_Class/Ackerman.h"


using namespace std;






void small2Large(int &x, int &y, int &z){
    int temp = 0;
    if(x > y){
        temp = x;
        x = y;
        y = temp;
    }
    if(x > z){
        temp = x;
        x = z;
        z = temp;
    }
    if(y > z){
        temp = y;
        y = z;
        z = temp;
    }
}

//    (new Calculator())->run();
//    (new FileEditor())->run();
//    (new HuffmanCompress())->run();
//    cout << Ackerman(1, 3) << endl;

void visit(const int &element){
    cout << element << endl;
}

int main() {
    for(int i = 0; i < 10; i++){
        if(i == 5){
            cout << 2 << endl;
            continue;
        }
        cout << i <<endl;
    }

    return 0;
}
