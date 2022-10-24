//
// Created by cw on 2022/10/24.
//

#ifndef DATASTRUCTURESANDALGORITHMS_TRIPLE_HPP
#define DATASTRUCTURESANDALGORITHMS_TRIPLE_HPP

/**
 * 三元组
 * @tparam ElemType
 */
template<class ElemType>
class Triple {
private:
    int row, col;
    ElemType value;
public:
    Triple() = default;

    Triple(int row, int col, ElemType value) : row(row), col(col), value(value) {};

    ~Triple() = default;
};

#endif //DATASTRUCTURESANDALGORITHMS_TRIPLE_HPP
