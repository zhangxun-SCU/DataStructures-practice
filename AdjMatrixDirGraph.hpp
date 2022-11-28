//
// Created by cw on 2022/11/28.
//

#ifndef DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP
#define DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP
#include <iostream>

using namespace std;
/*
 * 有向图得邻接矩阵表示
 */
template<class ElemType>
class AdjMatrixDirGraph {
protected:
    // 顶点个数
    int vexNum;
    // 边数
    int edgeNum;
    // 顶点元素
    ElemType **matrix;
    // 指向标志数组的指针
    mutable bool *tag;
public:

};


#endif //DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP
