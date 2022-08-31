//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
#define DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
#include<string>

class MyException {
private:
    std::string message_;
public:
    explicit MyException(const char*);
};


#endif //DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
