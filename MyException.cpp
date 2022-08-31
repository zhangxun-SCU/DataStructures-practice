//
// Created by cw on 2022/8/31.
//

#include "MyException.h"

MyException::MyException(const char * str): message_(str) {};

const char *MyException::what () const throw() {
    return this->message_;
}