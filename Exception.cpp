//
// Created by cw on 2022/8/31.
//

#include "Exception.h"

Exception::Exception(const char * str): message_(str) {};

const char *Exception::what () const throw() {
    return this->message_;
}