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
    template<class ElemType>
    static bool s2l(const ElemType &a, const ElemType &b);
    template<class ElemType>
    static bool l2s(const ElemType &a, const ElemType &b);

    // 阶乘
    template<class ElemType>
    static ElemType factorial(ElemType n);

};

template<class ElemType>
void Utils::swap(ElemType &a, ElemType &b) {
    ElemType tmp = a;
    a = b;
    b = tmp;
}

template<class ElemType>
bool Utils::s2l(const ElemType &a, const ElemType &b) { return a > b; }
template<class ElemType>
bool Utils::l2s(const ElemType &a, const ElemType &b) { return b > a; }

template<class ElemType>
ElemType Utils::factorial(ElemType n) {
    ElemType result = 1;
    for(int i = 0; i < n; i++){
        result *= (i+1);
    }
    return result;
}
#endif //DATASTRUCTURESANDALGORITHMS_UTILS_HPP
