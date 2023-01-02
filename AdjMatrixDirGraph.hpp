//
// Created by cw on 2022/11/28.
//

#ifndef DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP
#define DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP

#include <iostream>

#include "LinkQueue.hpp"

using namespace std;

/*
 * 有向网得邻接矩阵表示（带权重）
 */
template<class ElemType, class WeightType>
class AdjMatrixDirGraph {
protected:
    // 顶点个数
    int vexNum;
    // 边数
    int edgeNum;
    // 顶点元素
    ElemType *elems;
    WeightType **matrix;
    // 指向标志数组的指针
    mutable bool *tag;

    // 辅助函数
    // 自v开始广度优先
    void DFS(int v, void (*visit)(const ElemType &e)) const;

    // 深度优先
    void BFS(int v, void (*visit)(const ElemType &e)) const;

public:
    explicit AdjMatrixDirGraph(ElemType *data, int vertexNum = 10);

    explicit AdjMatrixDirGraph(int vertexNum = 10);

    AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType, WeightType> &source);

    ~AdjMatrixDirGraph();

    // 求顶点值
    bool getElem(int v, ElemType &element) const;

    // 设置顶点值
    bool setElem(int v, const ElemType &element);

    // 返回顶点个数
    int getVexNum() const;

    // 返回边数
    int getEdgeNum() const;

    // 返回v1的第一个邻接点
    bool firstAdjVex(int v1, int &v) const;

    // 返回下一个顶点（相对于v1）
    bool nextAdjVex(int v1, int v2, int &v) const;

    // 插入顶点为v1v2的边
    bool insertEdge(int v1, int v2, int w = 1);

    // 删除边
    bool deleteEdge(int v1, int v2);

    // 返回权重
    bool getWeight(int v1, int v2, WeightType &w) const;

    // 设置权重
    bool setWeight(int v1, int v2, WeightType &w);

    // 返回tag
    bool getTag(int v, bool &val) const;

    // 设置tag
    bool setTag(int v, bool val) const;

    // 遍历
    void DFSTraverse(void (*visit)(const ElemType &e)) const;

    void BFSTraverse(void (*visit)(const ElemType &e)) const;

    // 赋值
    AdjMatrixDirGraph<ElemType, WeightType> &operator=(const AdjMatrixDirGraph<ElemType, WeightType> &source);
};

template<class ElemType, class WeightType>
void AdjMatrixDirGraph<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &)) const {
    visit(elems[v]);
    setTag(v, true);
    int u;
    bool traverse_flag;
    for(bool flag = firstAdjVex(v, u); flag; flag = nextAdjVex(v, u, u)){
        getTag(u, traverse_flag);
        if(!traverse_flag){
            DFS(u, visit);
        }
    }
}

template<class ElemType, class WeightType>
void AdjMatrixDirGraph<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const {
    visit(elems[v]);
    setTag(v, true);
    LinkQueue<ElemType> queue;
    queue.enQueue(v);
    bool traverse_flag;
    while(!queue.empty()){
        int u;
        queue.deQueue(v);
        for(bool get_flag = firstAdjVex(v, u); get_flag ; get_flag = nextAdjVex(v, u, u)){
            getTag(u, traverse_flag);
            if(!traverse_flag){
                visit(elems[u]);
                setTag(u, true);
                queue.enQueue(u);
            }
        }
    }
}

template<class ElemType, class WeightType>
AdjMatrixDirGraph<ElemType, WeightType>::AdjMatrixDirGraph(ElemType *data, int vertexNum) {
    vexNum = vertexNum;
    edgeNum = 0;
    elems = new ElemType[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        elems[i] = data[i];
    }
    matrix = new WeightType *[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        matrix[i] = new WeightType[vertexNum];
        for (int j = 0; j < vertexNum; j++) {
            matrix[i][j] = 0;
        }
    }
    tag = new bool[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        tag[i] = false;
    }
}

template<class ElemType, class WeightType>
AdjMatrixDirGraph<ElemType, WeightType>::AdjMatrixDirGraph(int vertexNum) {
    vexNum = vertexNum;
    edgeNum = 0;
    elems = new ElemType[vertexNum];
//    for (int i = 0; i < vertexNum; i++) {
//        elems[i] = 0;
//    }
    matrix = new WeightType *[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        matrix[i] = new WeightType[vertexNum];
        for (int j = 0; j < vertexNum; j++) {
            matrix[i][j] = 0;
        }
    }
    tag = new bool[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        tag[i] = false;
    }
}

template<class ElemType, class WeightType>
AdjMatrixDirGraph<ElemType, WeightType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType, WeightType> &source) {
    vexNum = source.vexNum;
    edgeNum = source.edgeNum;
    elems = new ElemType[vexNum];
    for (int i = 0; i < vexNum; i++) {
        elems[i] = source.elems[i];
    }
    matrix = new WeightType *[vexNum];
    for (int i = 0; i < vexNum; i++) {
        matrix[i] = new WeightType[vexNum];
        for (int j = 0; j < vexNum; j++) {
            matrix[i][j] = source.matrix[i][j];
        }
    }
    tag = new bool[vexNum];
    for (int i = 0; i < vexNum; i++) {
        tag[i] = source.tag[i];
    }
}

template<class ElemType, class WeightType>
AdjMatrixDirGraph<ElemType, WeightType>::~AdjMatrixDirGraph() {
    delete[] elems;
    delete tag;
    for (int i = 0; i < vexNum; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::getElem(int v, ElemType &element) const {
    if (v < 0 || v >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    element = elems[v];
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::setElem(int v, const ElemType &element) {
    if (v < 0 || v >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    elems[v] = element;
    return true;
}

template<class ElemType, class WeightType>
int AdjMatrixDirGraph<ElemType, WeightType>::getVexNum() const {
    return vexNum;
}

template<class ElemType, class WeightType>
int AdjMatrixDirGraph<ElemType, WeightType>::getEdgeNum() const {
    return edgeNum;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::firstAdjVex(int v1, int &v) const {
    if (v1 < 0 || v1 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    v = -1;
    for (int i = 0; i < vexNum; i++) {
        if (matrix[v1][i] != 0) {
            v = i;
            break;
        }
    }
    if (v == -1) {
        return false;
    }
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::nextAdjVex(int v1, int v2, int &v) const {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    v = -1;
    for (int i = v2 + 1; i < vexNum; i++) {
        if (matrix[v1][i] != 0) {
            v = i;
            break;
        }
    }
    if (v == -1) {
        return false;
    }
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::insertEdge(int v1, int v2, int w) {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    if (matrix[v1][v2] == 0) {
        edgeNum++;
    }
    matrix[v1][v2] = w;
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::deleteEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    if (matrix[v1][v2] != 0) {
        edgeNum--;
    }
    matrix[v1][v2] = 0;
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::getWeight(int v1, int v2, WeightType &w) const {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    w = matrix[v1][v2];
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::setWeight(int v1, int v2, WeightType &w) {
    if (v1 < 0 || v1 >= vexNum || v2 < 0 || v2 >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    matrix[v1][v2] = w;
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::getTag(int v, bool &val) const {
    if (v < 0 || v >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    val = tag[v];
    return true;
}

template<class ElemType, class WeightType>
bool AdjMatrixDirGraph<ElemType, WeightType>::setTag(int v, bool val) const {
    if (v < 0 || v >= vexNum) {
        cerr << "未找到此顶点" << endl;
        return false;
    }
    tag[v] = val;
    return true;
}

template<class ElemType, class WeightType>
void AdjMatrixDirGraph<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &)) const {
    // 深度优先遍历
    // reset the flag
    for(int i = 0; i < vexNum; i++){
        setTag(i, false);
    }
    // 执行遍历
    bool traverse_flag;
    for(int v = 0; v < vexNum; v++){
        getTag(v, traverse_flag);
        if(!traverse_flag) {
            DFS(v, visit);
        }
    }
}

template<class ElemType, class WeightType>
void AdjMatrixDirGraph<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const {
    // reset the flag
    for(int i = 0; i < vexNum; i++){
        setTag(i, false);
    }
    // 广度优先遍历
    bool traverse_flag;
    for(int v = 0; v < vexNum; v++){
        // 外部仍嵌套一层循环，防止图是非连通图
        getTag(v, traverse_flag);
        if(!traverse_flag){
            BFS(v, visit);
        }
    }
}

template<class ElemType, class WeightType>
AdjMatrixDirGraph<ElemType, WeightType> &
AdjMatrixDirGraph<ElemType, WeightType>::operator=(const AdjMatrixDirGraph<ElemType, WeightType> &source) {
    if(&source != this){
        vexNum = source.vexNum;
        edgeNum = source.edgeNum;
        elems = new ElemType[vexNum];
        for (int i = 0; i < vexNum; i++) {
            elems[i] = source.elems[i];
        }
        matrix = new WeightType *[vexNum];
        for (int i = 0; i < vexNum; i++) {
            matrix[i] = new WeightType[vexNum];
            for (int j = 0; j < vexNum; j++) {
                matrix[i][j] = source.matrix[i][j];
            }
        }
        tag = new bool[vexNum];
        for (int i = 0; i < vexNum; i++) {
            tag[i] = source.tag[i];
        }
    }
}

#endif //DATASTRUCTURESANDALGORITHMS_ADJMATRIXDIRGRAPH_HPP
