//
//                       .::::.
//                     .::::::::.
//                    :::::::::::
//                 ..:::::::::::'
//              '::::::::::::'
//                .::::::::::
//           '::::::::::::::..
//                ..::::::::::::.
//              ``::::::::::::::::
//               ::::``:::::::::'        .:::.
//              ::::'   ':::::'       .::::::::.
//            .::::'      ::::     .:::::::'::::.
//           .:::'       :::::  .:::::::::' ':::::.
//          .::'        :::::.:::::::::'      ':::::.
//         .::'         ::::::::::::::'         ``::::.
//     ...:::           ::::::::::::'              ``::.
//    ````':.          ':::::::::'                  ::::..
//                       '.:::::'                    ':'````..
//

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
#include "Matrix.hpp"
#include "BinaryTree.hpp"

using namespace std;

void visit(const int &element){
    cout << element << endl;
}

int main() {
//    (new Calculator())->run();
//    (new FileEditor())->run();
//    RefGenList<char> temp;
//    temp.input();
//    temp.output();
//    temp.input();
//    temp.output();
    BinaryTree<int> temp(1);
    temp.insertLeftChild(temp.getRoot(), 1);
    temp.insertRightChild(temp.getRoot(), 2);
    temp.insertRightChild(temp.leftChild(temp.getRoot()), 3);
    temp.insertLeftChild(temp.rightChild(temp.getRoot()), 4);
    temp.disPlayBTWithTreeShape(temp);
    cout <<temp.empty() << endl;
    cout << temp.nodeCount() << endl;
    cout << temp.height() << endl;

    cout << endl;
    temp.preOrderNoRecur(visit);
    cout << endl;

    temp.inOrderNoRecur(visit);
    cout << endl;

    temp.postOrder(visit);
    return 0;
}


