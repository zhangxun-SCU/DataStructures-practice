#include <iostream>
#include "MyArray.h"

int main() {
    MyArray arr = MyArray(5);
    arr.insert(0, 10);
    arr.output();
    arr.insert(50, 10);
    return 0;
}

