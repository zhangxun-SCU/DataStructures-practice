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
protected:
    // 存储结点信息
    HuffmanTreeNode<WeightType> *nodes;
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

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType *ch, WeightType *w, int n) {
    // 由字符权值字符个数构造huffman树
    leafNum = n;
    int m = 2 * n - 1;

    nodes = new HuffmanTreeNode<WeightType> [m];
    leafChars = new CharType[n];
    leafCharCodes = new CharString[n];

    int tempPos;

    for(tempPos = 0; tempPos < n; tempPos++){
        nodes[tempPos].weight = w[tempPos];
        leafChars = ch[tempPos];
    }

    // 建立Huffman树
    for(tempPos = n; tempPos < m; tempPos++){
        int r1, r2;
        select(tempPos, r1, r2);

        // 合并以r1,r2为根的树
        nodes[r1].parent = nodes[r2].parent = tempPos;
        nodes[tempPos].leftChild = r1;
        nodes[tempPos].rightChild = r2;
        nodes[tempPos].weight = nodes[r1].weight + nodes[r2].weight;
    }

    // 求n个叶子节点的编码
    for(tempPos = 0; tempPos < n; tempPos++){
        // 暂存编码
        SingleLinkList<CharType> charCode;
        for(int child = tempPos, parent = nodes[child].parent; parent != 0; child = parent, parent = nodes[child].parent){
            if(nodes[parent].leftChild == child){
                charCode.insert(0, '0');
            } else {
                charCode.insert(0, '1');
            }
        }
        leafCharCodes[tempPos] = charCode;
    }

    // m-1为根
    curPos = m-1;
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
    delete[] leafChars;
    delete[] nodes;
    delete[] leafCharCodes;
}

template<class CharType, class WeightType>
CharString HuffmanTree<CharType, WeightType>::encode(CharType ch) {
    int temp;
    for(temp = 0; temp < leafNum; temp++){
        // 查找字符位置
        if(leafChars[temp] == ch){
            break;
        }
    }
    if(temp < leafNum){
        // 找到了
        return leafCharCodes[temp];
    } else {
        cerr << "出现非法字符，无法编码" <<endl;
        exit(-1);
    }
}

template<class CharType, class WeightType>
SingleLinkList<CharType> HuffmanTree<CharType, WeightType>::decode(CharString codeStr) {
    SingleLinkList<CharType> charList;
    for(int temp = 0; temp < codeStr.length(); temp++){
        if(codeStr[temp] == '0'){
            curPos = nodes[curPos].leftChild;
        } else {
            curPos = nodes[curPos].rightChild;
        }
        if(nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0){
            charList.insert(charList.length(), leafChars[curPos]);
            // 回到根节点
            curPos = 2 * leafNum - 1;
        }
    }
    return charList;
}

#endif //DATASTRUCTURESANDALGORITHMS_HUFFMANTREE_HPP
