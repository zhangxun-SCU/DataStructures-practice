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
#include "string.h"
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
#include "LinkHuffmanTree.hpp"

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
    char ch[5] = {'a', 'b', 'c', 'd', 'e'};
    long weight[5] = {10, 2, 3,6, 5};
    LinkHuffmanTree<char, long>  temp = LinkHuffmanTree<char, long>(ch, weight, 5);
    cout << temp.encode('a') << endl;
    cout << temp.encode('b') << endl;
    cout << temp.encode('c') << endl;
    cout << temp.encode('d') << endl;
    cout << temp.encode('e') << endl;
    temp.decode(CharString("01110111110110"));
    return 0;
}


