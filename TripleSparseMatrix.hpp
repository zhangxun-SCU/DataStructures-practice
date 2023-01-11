//
// Created by cw on 2022/10/24.
//

#ifndef DATASTRUCTURESANDALGORITHMS_TRIPLESPARSEMATRIX_HPP
#define DATASTRUCTURESANDALGORITHMS_TRIPLESPARSEMATRIX_HPP

#include <iostream>

#include "Triple.hpp"

using namespace std;

/**
 * 三元组实现稀疏矩阵
 * @tparam ElemType
 */
template<class ElemType>
class TripleSparseMatrix {
protected:
    Triple<ElemType> *elems;
    int maxSize;
    int rows, cols, num;
public:
    explicit TripleSparseMatrix(int r = 10, int c = 10, int num = 10);

    TripleSparseMatrix(const TripleSparseMatrix<ElemType> &source);

    virtual ~TripleSparseMatrix();

    // 返回行数
    int getRows() const;

    // 返回列数
    int getCols() const;

    // 返回稀疏矩阵非0元个数
    int getNum() const;

    // 设定指定位置的值
    bool setElem(int row, int col, const ElemType &element);

    // 得到指定位置的值
    bool getElem(int row, int col, ElemType &element);

    // 简单转置
    static void simpleTranspose(const TripleSparseMatrix<ElemType> &source, TripleSparseMatrix<ElemType> &dest);

    // 快速转置
    static void fastTranspose(const TripleSparseMatrix<ElemType> &source, TripleSparseMatrix<ElemType> &dest);

    // 重载
    TripleSparseMatrix<ElemType> &operator=(const TripleSparseMatrix<ElemType> &source);

    ElemType &operator()(int i, int j);
};

template<class ElemType>
TripleSparseMatrix<ElemType>::TripleSparseMatrix(int r, int c, int num):rows(r), cols(c), num(num), maxSize(r * c / 2),
                                                                        elems(new Triple<ElemType>[maxSize]) {}

template<class ElemType>
TripleSparseMatrix<ElemType>::TripleSparseMatrix(const TripleSparseMatrix<ElemType> &source) {
    maxSize = source.maxSize;
    rows = source.rows;
    cols = source.cols;
    num = source.num;
    elems = new Triple<ElemType>[maxSize];
    for(int i = 0; i < num; i++){
        elems[i](source.elems[i]);
    }
}

template<class ElemType>
TripleSparseMatrix<ElemType>::~TripleSparseMatrix() {
    delete[] elems;
}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getRows() const {
    return rows;
}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getCols() const {
    return cols;
}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getNum() const {
    return num;
}

template<class ElemType>
bool TripleSparseMatrix<ElemType>::setElem(int row, int col, const ElemType &element) {
    /*
     * 对于set,首先查找是否有这个元素，有则修改值，修改后v为0，就删去这个三元组
     * 不为0不变，如果不存在，且v为0，什么也不用管，若v不为0，则添加此三元组
     */
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cerr << "warning: 索引越界" << endl;
        return false;
    }
    int i, j;
    for (i = num - 1; i >= 0 && (row < elems[i].row || row == elems[i].row && col <= elems[i].col); i--)
        // 查找三元组位置
        ;

    if (elems[i].row == row && elems[i].col == col) {
        // 找到三元组
        if (element == 0) {
            // 修改后的值为0，删除此三元组即可
            for (j = i + 1; j < num; j++) {
                elems[j - 1] = elems[j];
            }
            num--;
        } else {
            // 修改值即可
            elems[i].value = element;
        }
        return true;
    } else if (element != 0) {
        // 没有找到且值不为0
        if (num < maxSize) {
            // 容量还够，将元素向后移，然后插入新的三元组
            i++;  // 应该插入的位置
            for (j = num; j > i; j--) {
                elems[j] = elems[j - 1];
            }
            elems[i].row = row;
            elems[i].col = col;
            elems[i].value = element;
            num++;
            return true;
        } else {
            cerr << "warning: 超过最大容量" << endl;
        }
    }
    return true;
}

template<class ElemType>
bool TripleSparseMatrix<ElemType>::getElem(int row, int col, ElemType &element) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cerr << "warning: 索引越界" << endl;
        return false;
    }
    // 查找元素，找到返回对应值，没有则返回0
    for(int i = 0; i < num; i++){
        if(elems[i].row == row && elems[i].col == col){
            element = elems[i].value;
            return true;
        }
    }
    element = 0;
    return true;
}

template<class ElemType>
void TripleSparseMatrix<ElemType>::simpleTranspose(const TripleSparseMatrix<ElemType> &source,
                                                   TripleSparseMatrix<ElemType> &dest) {
    /*
     * 先进行行列的转换
     */
    dest.rows = source.cols;
    dest.cols = source.rows;
    dest.num = source.num;
    dest.maxSize = source.maxSize;
    delete[] dest.elems;
    dest.elems = new Triple<ElemType>[dest.maxSize];
    if (dest.num) {
        int destPos = 0;  // 纪录插入元素的位置
        for (int col = 0; col < source.cols; col++) {
            // source的列变为dest的行，dest按行存，那么source按列去找
            for (int sourcePos = 0; sourcePos < source.num; sourcePos++) {
                // 再次遍历source，找到col列的元素存在dest的col行
                if (source.elems[sourcePos].col == col) {
                    // 找到source col列的元素，存入dest的col行
                    dest.elems[destPos].row = source.elems[sourcePos].col;
                    dest.elems[destPos].col = source.elems[sourcePos].row;
                    dest.elems[destPos].value = source.elems[sourcePos].value;
                    // 更新dest存放位置
                    destPos++;
                }
            }
        }
    }
}

template<class ElemType>
void TripleSparseMatrix<ElemType>::fastTranspose(const TripleSparseMatrix<ElemType> &source,
                                                 TripleSparseMatrix<ElemType> &dest) {
    /*
     * SimpleTranspose 每一 行/列 都要遍历数组
     * fastTranspose 思想是直接取出每一个元素并找到它应该在的位置
     *     1. 找到source每一列非零元素的个数
     *     2. 找到source每一列第一个非零元素应该在dest的位置
     */
    dest.rows = source.cols;
    dest.cols = source.rows;
    dest.num = source.num;
    dest.maxSize = source.maxSize;
    delete[] dest.elems;
    dest.elems = new Triple<ElemType>[dest.maxSize];
    // source每列非零元素个数
    int perColNums[source.cols];
    // source每一列第一个非零元素应该在dest的位置
    int firstPos[source.cols];
    // 初始化perColNums
    for (int i = 0; i < source.cols; i++) {
        perColNums[i] = 0;
    }
    // source每列非零元素个数
    for (int i = 0; i < source.num; i++) {
        perColNums[source.elems[i].col]++;
    }
    // source每一列第一个非零元素应该在dest的位置
    firstPos[0] = 0;  // 第一列第一个元素放在第一
    for (int i = 1; i < source.cols; i++) {
        firstPos[i] = firstPos[i - 1] + perColNums[i - 1];
    }
    // 遍历一次，进行复制
    for (int sourcePos = 0; sourcePos < source.num; sourcePos++) {
        int destPos = firstPos[source.elems[sourcePos].col];
        dest.elems[destPos].row = source.elems[sourcePos].col;
        dest.elems[destPos].col = source.elems[sourcePos].row;
        dest.elems[destPos].value = source.elems[sourcePos].value;
        // 复制完这一列的一个元素，那么这一列的下一个元素在dest数组中的位置+1即可
        firstPos[source.elems[sourcePos].col]++;
    }
}

template<class ElemType>
TripleSparseMatrix<ElemType> &TripleSparseMatrix<ElemType>::operator=(const TripleSparseMatrix<ElemType> &source) {
    if(this != &source){
        delete[] elems;
        maxSize = source.maxSize;
        rows = source.rows;
        cols = source.cols;
        num = source.num;
        elems = new Triple<ElemType>[maxSize];
        for(int i = 0; i < num; i++){
            elems[i](source.elems[i]);
        }
    }
}

template<class ElemType>
ElemType &TripleSparseMatrix<ElemType>::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        cerr << "warning: 索引越界" << endl;
        exit(7);
    }
    for(int pos = 0; pos < num; pos++){
        if(elems[pos].row == i && elems[pos].col == j){
            return elems[pos].value;
        }
    }
    return 0;
}


#endif //DATASTRUCTURESANDALGORITHMS_TRIPLESPARSEMATRIX_HPP
