//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_UTILS_HPP
#define DATASTRUCTURESANDALGORITHMS_UTILS_HPP

class Utils {
public:
    // 交换两元素
    template<class ElemType>
    static void swap(ElemType & a, ElemType &b);
};

template<class ElemType>
void Utils::swap(ElemType &a, ElemType &b) {
    ElemType tmp = a;
    a = b;
    b = tmp;
}


#endif //DATASTRUCTURESANDALGORITHMS_UTILS_HPP
