#include <list>
#include <vector>
#include <iostream>
#include <string>
#include "SingleLinkList.hpp"
#include "ArrayStack.hpp"
#include "Array.hpp"
#include "CircularQueue.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "PriorityQueue.hpp"
#include "Sort.hpp"
#include "Utils.hpp"
#include "CircleLinkList.hpp"
#include "DCLinkList.hpp"
#include "CharString.hpp"


#include "Calculator.hpp"
#include <iostream>
using namespace std;

int main() {
//    (new Calculator())->Run();

    CharString temp1("12345");
    CharString::write(temp1);
    CharString temp2("6789");
    char *tmp1 = new char;
    const char *tmp2 = "efg";
    CharString temp3("45");
    temp3 = temp1;
    cout << temp1.length() << " "<< temp2.length() << " "<< temp3.length()<<endl;
    CharString temp4 = CharString("4468");
//    temp4 = "4448";
    CharString::write(temp4);
    cout<<temp4[1];
    return 0;
}


