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

    // 双边快速排序使用递归
    template<class ElemType>
    static void
    quickSort_double_recursion(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b));

    // 单边循环快速排序递归
    template<class ElemType>
    static void
    quickSort_single_recursion(ElemType *array, int size, bool (*compare)(const ElemType &a, const ElemType &b));
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
    for (int i = 0; i < size / 2; i++) {
        // 有序标记
        bool isSorted = true;
        // 奇数轮次，从左到右交换
        for (int j = re_sortBorder; j < po_sortBorder; j++) {
            if (compare(array[j], array[j + 1])) {
                Utils::swap(array[j], array[j + 1]);
                isSorted = false;
                lastExchangeIndex = j;
            }
        }
        po_sortBorder = lastExchangeIndex;
        if (isSorted) {
            break;
        }
        // 偶数次遍历，在遍历前将isSorted重新标记魏true: 因为有可能上面进行交换之后数组就变得有序了，这由下面这一轮遍历来判断
        isSorted = true;
        for (int j = po_sortBorder; j > re_sortBorder; j--) {
            if (!compare(array[j], array[j - 1])) {
                Utils::swap(array[j], array[j - 1]);
                isSorted = false;
                lastExchangeIndex = j;
            }
        }
        re_sortBorder = lastExchangeIndex;
        if (isSorted) {
            break;
        }
    }
}

template<class ElemType>
void Sort::quickSort_double_recursion(ElemType *array, int size, bool (*compare)(const ElemType &, const ElemType &)) {
    // 递归实现双边快速排序
    // 递归终止条件
    if (size <= 1) {
        return;
    }
    int left = 0, right = size - 1;
    // 选取基准元素，这里直接取第一个数，此处是可以优化的点
    ElemType pivot = array[0];
    while (left < right) {
        while (left < right && compare(array[right], pivot)) {
            right--;
        }
        while (left < right && compare(pivot, array[left])) {
            left++;
        }
        if (left < right) {
            // 找到左边大于pivot和右边小于pivot的元素后交换位置（以从大到小为例）
            Utils::swap(array[left], array[right]);
        }
    }
    // 退出循环是left = right，即左右指针重合，这个位置就是基准元素pivot应该在的位置，左边的元素小于pivot，右边的元素大于pivot
    array[left] = pivot;
    // 递归
    // 左边一部分，左边元素个数为left
    quickSort_double_recursion(array, left, compare);
    // 右边一部分，右边元素其起始点为arr+left+1，即从left后一个元素开始，长度为size - left(基准元素左边的元素) - 1(基准元素)
    quickSort_double_recursion(array + left + 1, size - left - 1, compare);
}

template<class ElemType>
void Sort::quickSort_single_recursion(ElemType *array, int size, bool (*compare)(const ElemType &, const ElemType &)) {
    // 递归实现单边循环快速排序
    // 递归终止条件
    if (size <= 1) {
        return;
    }
    // 选取基准元素，这里直接取第一个数，此处是可以优化的点
    ElemType pivot = array[0];
    // 基准数的起始位置为0,根据上面的优化而改变
    int pivotIndex = 0;
    // 使用mark来标记基准元素pivot应该在的位置，初始为0，表示mark左边不该有数字
    int mark = 0;
    for (int i = 0; i < size; i++) {
        if (compare(pivot, array[i])) {
            // 如果compare为true，说明基准元素左边的元素要多一个，pivotIndex+1，并且将arr[i]与
            mark++;
            Utils::swap(array[mark], array[i]);
        }
    }
    // 一次循环结束就找到了基准元素pivot改在的位置，左边的元素小于它，右边的元素大于它，所以交换mark处与pivotIndex处的值
    Utils::swap(array[mark], array[pivotIndex]);
    // 递归
    // 左边部分，与双边循环类似，此时mark就是pivot的位置，左边的元素个数就是mark
    quickSort_single_recursion(array, mark, compare);
    // 右边部分
    quickSort_single_recursion(array + mark + 1, size - mark - 1, compare);
}


#endif //DATASTRUCTURESANDALGORITHMS_SORT_HPP
