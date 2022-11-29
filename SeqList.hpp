//
// Created by cw on 2022/9/5.
//

#ifndef DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP

#include "iostream"

using namespace std;

template<class T>
class SeqList {
protected:
//    数组容量
    unsigned int size;
//    数组长度
    unsigned int length;
//    指向数组的指针
    T *arr;
public:
    /*
     * 这里得explit关键字是为了防止发生隐式类型转换，具体原因详细阅读C++primer
     * */
    explicit SeqList(int size = 10);

//     拷贝构造
    SeqList(const SeqList<T> &);

    ~SeqList();

//    插入
    void insert(int index, T element);

//    扩容
    void resize();

//    删除
    T elementDelete(int index);

//    重载下标运算符
    T const &operator[](unsigned int) const;  // 返回常量，但不可被修改
    T &operator[](unsigned int);  // 可以修改
//    输出
    void output();
};


template<class T>
SeqList<T>::SeqList(int size): size(size), length(0), arr(new T[size]) {}

template<class T>
SeqList<T>::SeqList(const SeqList<T> &tmp):size(tmp.size), length(tmp.length), arr(new int[this->size]) {
    for (int i = 0; i < tmp.size; i++) {
        this->arr[i] = tmp.arr[i];
    }
}

template<class T>
SeqList<T>::~SeqList() {
    delete[] arr;
    arr = nullptr;
}

template<class T>
void SeqList<T>::insert(int index, T element) {
    if (index < 0 || index > size) {
        cout << "访问异常" << endl;
        return;
    } else {
        for (int i = this->size - 1; i >= index; i--) {
            arr[i + 1] = arr[i];
        }
        arr[index] = element;
        this->length++;
    }
}

template<class T>
void SeqList<T>::resize() {
    T *arrNew = new T[this->size * 2];
    for (int i = 0; i < this->size; i++) {
        arrNew[i] = arr[i];
    }
    delete[] arr;
    arr = arrNew;
    this->size *= 2;
}

template<class T>
T SeqList<T>::elementDelete(int index) {
    T deElement;
    if (index < 0 || index > this->size) {
        cout << "没有这个元素" << endl;
        return deElement;
    }
    deElement = arr[index];
//          从左到右元素向前移一位
    for (int i = index; i < this->size; i++) {
        arr[i] = arr[i + 1];
    }
    this->length--;
    return deElement;
}

template<class T>
const T &SeqList<T>::operator[](unsigned int index) const {
    if (index < 0 || index > size) {
        cout << "下标越界" << endl;
        return arr[0];
    }
    return arr[index];
}

template<class T>
T &SeqList<T>::operator[](unsigned int index) {
    if (index < 0 || index > size) {
        cout << "下标越界" << endl;
        return arr[0];
    }
    return arr[index];
}

template<class T>
void SeqList<T>::output() {
    for (int i = 0; i < this->length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

#endif //DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP

