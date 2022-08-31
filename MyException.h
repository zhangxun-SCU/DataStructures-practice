//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
#define DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
#include<iostream>
class MyException {
private:
    const char* message_;
public:
    explicit MyException(const char*);
    const char* what() const throw();
};


#endif //DATASTRUCTURESANDALGORITHMS_MYEXCEPTION_H
