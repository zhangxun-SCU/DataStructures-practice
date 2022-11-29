//
// Created by cw on 2022/10/24.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MATRIX_HPP
#define DATASTRUCTURESANDALGORITHMS_MATRIX_HPP
#include <iostream>

using namespace std;

/*
 * 二维矩阵
 */
template<class ElemType>
class Matrix {
protected:
    ElemType *elems;
    int rows, cols;
public:
    Matrix(int rows, int cols);
    Matrix(const Matrix<ElemType> &source);
    ~Matrix();
    // 返回矩阵行数
    int getRows() const;
    // 返回矩阵列数
    int getCols() const;
    // 重载
    // 重载函数运算符
    ElemType &operator()(int i, int j);
    // 重载复制
    Matrix<ElemType> &operator=(const Matrix<ElemType> &source);
};

template<class ElemType>
Matrix<ElemType>::Matrix(int rows, int cols):rows(rows), cols(cols) {
    if(rows < 1 || cols < 1){
        cerr<<"error: 矩阵行或列无效"<<endl;
        exit(-1);
    }
    elems = new ElemType[rows * cols];
}

template<class ElemType>
Matrix<ElemType>::Matrix(const Matrix<ElemType> &source) {
    rows = source.rows;
    cols = source.cols;
    elems = new ElemType[rows * cols];
    for(int i = 0; i < rows * cols; i++){
        elems[i] = source.elems[i];
    }
}

template<class ElemType>
Matrix<ElemType>::~Matrix() {
    delete[] elems;
}

template<class ElemType>
int Matrix<ElemType>::getRows() const {
    return rows;
}

template<class ElemType>
int Matrix<ElemType>::getCols() const {
    return cols;
}

template<class ElemType>
ElemType &Matrix<ElemType>::operator()(int i, int j) {
    if(i < 0 || i >= rows || j < 0 || j >= cols){
        cerr<<"error: 下标越界"<<endl;
        exit(-1);
    }
    return elems[i * cols + j];
}

template<class ElemType>
Matrix<ElemType> &Matrix<ElemType>::operator=(const Matrix<ElemType> &source) {
    if(&source != this){
        rows = source.rows;
        cols = source.cols;
        elems = new ElemType[rows * cols];
        for(int i = 0; i < rows * cols; i++){
            elems[i] = source.elems[i];
        }
    }
    return *this;
}
#endif //DATASTRUCTURESANDALGORITHMS_MATRIX_HPP
