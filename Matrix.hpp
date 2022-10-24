//
// Created by cw on 2022/10/24.
//

#ifndef DATASTRUCTURESANDALGORITHMS_MATRIX_HPP
#define DATASTRUCTURESANDALGORITHMS_MATRIX_HPP

template<class ElemType>
class Matrix {
private:

public:
    int getRows() const;
    int getCols() const;
    ElemType &operator()(int i, int j);
};


#endif //DATASTRUCTURESANDALGORITHMS_MATRIX_HPP
