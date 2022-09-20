//
// Created by cw on 2022/9/16.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MYBINARYHEAP_HPP
#define DATASTRUCTURESANDALGORITHMS_MYBINARYHEAP_HPP
#include <vector>

/**
 * 二叉堆：
 * - 插入节点：插入在末尾节点再上浮
 * - 删除节点：删除顶点
 * - 构建二叉堆：所有非叶子节点一次下沉
 *
 * 二叉堆特点：
 * - 最大堆的堆顶是最大元素
 * - 最小堆的对顶是最小元素
 */
using namespace std;
template<class ElemType>
class MyBinaryHeap {
private:
    ElemType *array;
    int count;
    int maxSize;
    int childIndex;
    int parentIndex;
    // 保存插入叶子节点的值
    ElemType temp;
    // 上浮调整
    void upAdjust();
    // 下沉调整
    void downAdjust(int index);
public:
    MyBinaryHeap();
    explicit MyBinaryHeap(ElemType *tmp, int size, int maxSize = 1000);
    ~MyBinaryHeap();
    void add(ElemType element);
    ElemType del();
    void output();
};

template<class ElemType>
MyBinaryHeap<ElemType>::MyBinaryHeap():maxSize(1000), count(0), array(new ElemType[maxSize]), childIndex(-1), parentIndex(-1)  {};

template<class ElemType>
MyBinaryHeap<ElemType>::MyBinaryHeap(ElemType *tmp, int size, int maxSize):count(size), maxSize(maxSize), array(new ElemType[maxSize]), childIndex(-1), parentIndex(-1){
    for(int i = 0; i < count; i++){
        array[i] = tmp[i];
    }
    // 从最后一个非叶子节点开始，依次下沉
    for(int i = (count - 2) / 2; i >= 0; i--){
        this->downAdjust(i);
    }
}

template<class ElemType>
MyBinaryHeap<ElemType>::~MyBinaryHeap() {
    delete[] array;
}

template<class ElemType>
void MyBinaryHeap<ElemType>::upAdjust() {
    childIndex = count - 1;
    parentIndex = (childIndex - 1) / 2;
    temp = array[childIndex];
    while(childIndex > 0 && temp < array[parentIndex]){
        array[childIndex] = array[parentIndex];
        childIndex = parentIndex;
        parentIndex = (parentIndex - 1) / 2;
    }
    array[childIndex] = temp;
}

template<class ElemType>
void MyBinaryHeap<ElemType>::downAdjust(int index) {
    int length = count;
    parentIndex = index;
    // temp保存父节点的值，用于最后的赋值
    temp = array[parentIndex];
    childIndex = parentIndex * 2 + 1;
    while(childIndex < length){
        // 如果有右孩子，且右孩子小于左孩子，就定位到右孩子
        if(childIndex + 1 < length && array[childIndex + 1] < array[childIndex]){
            childIndex++;
        }
        // 如果父节点小于两个子节点，直接退出
        if(temp <= array[childIndex]){
            break;
        }
        array[parentIndex] = array[childIndex];
        parentIndex = childIndex;
        childIndex = childIndex * 2 + 1;
    }
    array[parentIndex] = temp;
}

template<class ElemType>
void MyBinaryHeap<ElemType>::add(ElemType element) {
    if(count >= maxSize){
        cout<<"超出最大范围"<<endl;
        return;
    }
    array[count++] = element;
    this->upAdjust();
}

template<class ElemType>
ElemType MyBinaryHeap<ElemType>::del() {
    ElemType tmp = array[0];
    array[0] = array[count-- -1];
    this->downAdjust(0);
    return tmp;
}

template<class ElemType>
void MyBinaryHeap<ElemType>::output() {
    for(int i = 0; i < count; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}
#endif //DATASTRUCTURESANDALGORITHMS_MYBINARYHEAP_HPP
