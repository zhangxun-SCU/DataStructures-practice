//
// Created by cw on 2022/8/31.
//

#ifndef DATASTRUCTURESANDALGORITHMS_EXCEPTION_H
#define DATASTRUCTURESANDALGORITHMS_EXCEPTION_H
#include<iostream>
class Exception {
private:
    const char* message_;
public:
    explicit Exception(const char*);
    const char* what() const throw();
};


#endif //DATASTRUCTURESANDALGORITHMS_EXCEPTION_H
