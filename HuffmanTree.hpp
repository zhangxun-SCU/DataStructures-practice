//
// Created by cw on 2022/11/14.
//

#ifndef DATASTRUCTURESANDALGORITHMS_HUFFMANTREE_HPP
#define DATASTRUCTURESANDALGORITHMS_HUFFMANTREE_HPP
#include <iostream>
#include "Node.hpp"
#include "CharString.hpp"
#include "SingleLinkList.hpp"

using namespace std;
template<class CharType, class WeightType>
class HuffmanTree {
private:
    // 存储结点信息
    HuffmanTreeNode<WeightType> *node;
    // 叶子节点字符
    CharType *leafChars;
    // 叶子节点字符编码
    CharString *leafCharCodes;
    // 当前节点
    int curPos;
    // 叶节点个数
    int leafNum;
    // 选择双亲为0，权值最小的两个节点
    void select(int cur, int &r1, int&r2);
public:
    HuffmanTree(CharType ch[], WeightType w[], int n);
    HuffmanTree(const HuffmanTree<CharType, WeightType> &source);
    virtual ~HuffmanTree();
    // 编码
    CharString encode(CharType ch);
    // 解码
    SingleLinkList<CharType> decode(CharString codeStr);
    // 复制构造函数
    HuffmanTree<CharType, WeightType>&operator=(const HuffmanTree<CharType, WeightType> &source);
};


#endif //DATASTRUCTURESANDALGORITHMS_HUFFMANTREE_HPP
