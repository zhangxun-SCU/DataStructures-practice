//
// Created by cw on 2022/9/20.
//

#ifndef DATASTRUCTURESANDALGORITHMS_SORT_HPP
#define DATASTRUCTURESANDALGORITHMS_SORT_HPP

#include "Utils.hpp"


class Sort {
public:
    // 冒泡排序：
    template<class ElemType>
    static void bubbleSort(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b));

    // 鸡尾酒排序：升级冒泡排序
    template<class ElemType>
    static void cockTailSort(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b));
};

template<class ElemType>
void Sort::bubbleSort(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b)) {
    /**
     * 优化：
     *  1.
     *  因为在排序时，有时已经有序了，但还没有遍历完，这是可以优化的一点
     *  我们使用一个变量(isSorted)来记录数组是否有序，如果已经有序就不在排序
     *  方法：在每一轮内层遍历开始，我们认为已经有序（isSorted=true），如果发生了元素交换在设为false
     *  2.
     *  观察排序过程我们会发现常常数组中后面一大部分已经有序，不必在进行遍历
     *  方法：记录最后一次交换的位置，因为冒泡排序每一轮原理上将一个数放到正确的位置，所以记录下的这个位置
     *  就是无序数组的边界，下一次遍历只到无序数组的边界即可
     */

    // 无序数组的边界，遍历到此即可
    int sortBorder = size - 1;
    // 记录最后一次交换的位置
    int lastExchangeIndex = 0;
    for (int i = 0; i < size - 1; i++) {
        // 记录数组是否有序
        bool isSorted = true;
        for (int j = 0; j < sortBorder; j++) {
            if (compare(array[j], array[j + 1])) {
                Utils::swap(array[j], array[j + 1]);
                // 交换过数据，说明仍是无序
                isSorted = false;
                lastExchangeIndex = j;
            }
        }
        sortBorder = lastExchangeIndex;
        if (isSorted) {
            break;
        }
    }
}

template<class ElemType>
void Sort::cockTailSort(ElemType *array, int size, bool (*compare)(const ElemType &, const ElemType &)) {
    /**
     * 优化：
     *  1.
     *  与冒泡排序相同，这里也可以使用无序边界进行优化，但有些许不同
     *  方法：观察鸡尾酒排序过程我们可以发现正向遍历的最佳起始点是上一次逆序遍历最后一次交换点，最佳终止点是上次正序遍历最后一次交换点
     *  逆序遍历于此相反。所以定义两个边界
     */

    // 记录最后一次交换的位置
    int lastExchangeIndex = 0;
    // 正序遍历无序边界/逆序遍历起始点
    int po_sortBorder = size - 1;
    // 逆序遍历无序边界/正序遍历起始点
    int re_sortBorder = 0;
    for(int i = 0; i < size / 2; i++){
        // 有序标记
        bool isSorted = true;
        // 奇数轮次，从左到右交换
        for(int j = re_sortBorder; j < po_sortBorder; j++){
            if(compare(array[j], array[j+1])){
                Utils::swap(array[j], array[j+1]);
                isSorted = false;
                lastExchangeIndex = j;
            }
        }
        po_sortBorder = lastExchangeIndex;
        if(isSorted){
            break;
        }
        // 偶数次遍历，在遍历前将isSorted重新标记魏true: 因为有可能上面进行交换之后数组就变得有序了，这由下面这一轮遍历来判断
        isSorted = true;
        for(int j = po_sortBorder; j > re_sortBorder; j--){
            if(!compare(array[j], array[j-1])){
                Utils::swap(array[j], array[j-1]);
                isSorted = false;
                lastExchangeIndex = j;
            }
        }
        re_sortBorder = lastExchangeIndex;
        if(isSorted){
            break;
        }
    }
}


#endif //DATASTRUCTURESANDALGORITHMS_SORT_HPP
