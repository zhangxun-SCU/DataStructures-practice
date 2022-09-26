//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_UTILS_HPP
#define DATASTRUCTURESANDALGORITHMS_UTILS_HPP

class Utils {
public:
    // 交换两元素
    template<class ElemType>
    static void swap(ElemType &a, ElemType &b);

    // 排序的顺序
    static bool s2l(const int &a, const int &b);

    static bool l2s(const int &a, const int &b);

    static bool s2l(const double &a, const double &b);

    static bool l2s(const double &a, const double &b);


};

template<class ElemType>
void Utils::swap(ElemType &a, ElemType &b) {
    ElemType tmp = a;
    a = b;
    b = tmp;
}

bool Utils::s2l(const int &a, const int &b) { return a > b; }

bool Utils::l2s(const int &a, const int &b) { return b > a; }

bool Utils::s2l(const double &a, const double &b) { return a > b; }

bool Utils::l2s(const double &a, const double &b) { return b > a; }


#endif //DATASTRUCTURESANDALGORITHMS_UTILS_HPP
