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
private:
    Triple<ElemType> *elems;
    int maxSize;
    int rows, cols, num;
public:
    TripleSparseMatrix(int r=10, int c=10, int num=10);
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
TripleSparseMatrix<ElemType>::TripleSparseMatrix(int r, int c, int num) {

}

template<class ElemType>
TripleSparseMatrix<ElemType>::TripleSparseMatrix(const TripleSparseMatrix<ElemType> &source) {

}

template<class ElemType>
TripleSparseMatrix<ElemType>::~TripleSparseMatrix() {

}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getRows() const {

}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getCols() const {

}

template<class ElemType>
int TripleSparseMatrix<ElemType>::getNum() const {

}

template<class ElemType>
bool TripleSparseMatrix<ElemType>::setElem(int row, int col, const ElemType &element) {
    /*
     * 对于set,首先查找是否有这个元素，有则修改值，修改后v为0，就删去这个三元组
     * 不为0不变，如果不存在，且v为0，什么也不用管，若v不为0，则添加此三元组
     */
    if(row < 0 || row >= rows || col < 0 || col >= cols){
        cerr << "warning: 索引越界" << endl;
        return false;
    }
    int i, j;
    for(i = num - 1; i >= 0 && (row < elems[i].row || row == elems[i].row && col <= elems[i].col); i--)
        // 查找三元组位置
        ;

    if(elems[i].row == row && elems[i].col == col){
        // 找到三元组
        if(element == 0){
            // 修改后的值为0，删除此三元组即可
            for(j = i + 1; j < num; j++){
                elems[j - 1] = elems[j];
            }
            num--;
        } else {
            // 修改值即可
            elems[i].value = element;
        }
        return true;
    } else if(element != 0){
        // 没有找到且值不为0
        if(num < maxSize){
            // 容量还够，将元素向后移，然后插入新的三元组
            i++;  // 应该插入的位置
            for(j = num; j > i; j--){
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

}

template<class ElemType>
void TripleSparseMatrix<ElemType>::simpleTranspose(const TripleSparseMatrix<ElemType> &source,
                                                   TripleSparseMatrix<ElemType> &dest) {

}

template<class ElemType>
void TripleSparseMatrix<ElemType>::fastTranspose(const TripleSparseMatrix<ElemType> &source,
                                                 TripleSparseMatrix<ElemType> &dest) {

}

template<class ElemType>
TripleSparseMatrix<ElemType> &TripleSparseMatrix<ElemType>::operator=(const TripleSparseMatrix<ElemType> &source) {

}

template<class ElemType>
ElemType &TripleSparseMatrix<ElemType>::operator()(int i, int j) {

}


#endif //DATASTRUCTURESANDALGORITHMS_TRIPLESPARSEMATRIX_HPP
