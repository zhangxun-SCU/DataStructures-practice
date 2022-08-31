#include <iostream>
#include "MyArray.h"

int main() {
    MyArray arr = MyArray(5);
    arr.insert(0, 10);
    arr.output();
    arr.resize();
    arr.resize();
    arr.resize();
    arr.resize();
    arr.resize();
    arr.insert(50, 10);
    arr.insert(1, 1);
    arr.insert(3, 1);
    arr.output();
    return 0;
}

