//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYSORT_HPP
#define DATASTRUCTURESANDALGORITHMS_MYSORT_HPP
#include "Utils.hpp"


class MySort {
public:
    // 冒泡排序：
    template<class ElemType>
    static void bubbleSort(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b));
};

template<class ElemType>
void MySort::bubbleSort(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b)) {
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(compare(array[j], array[j + 1])){
                Utils::swap(array[j], array[j + 1]);
            }
        }
    }
}


#endif //DATASTRUCTURESANDALGORITHMS_MYSORT_HPP
