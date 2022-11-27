//
// Created by cw on 2022/11/14.
//

#ifndef DATASTRUCTURESANDALGORITHMS_LINKHUFFMANTREE_HPP
#define DATASTRUCTURESANDALGORITHMS_LINKHUFFMANTREE_HPP
#include <iostream>
#include <map>
#include "Node.hpp"
#include "SingleLinkList.hpp"
#include "CharString.hpp"
#include "DCLinkList.hpp"

template<class CharType, class WeightType>
class LinkHuffmanTree {
private:
    LinkHuffmanTreeNode<WeightType> *root;
    LinkHuffmanTreeNode<WeightType> *curPos;
    LinkHuffmanTreeNode<WeightType> **leafNodes;
    SingleLinkList<LinkHuffmanTreeNode<WeightType> *> nodeList;
    map<CharType, CharString> char2code;
    map<LinkHuffmanTreeNode<WeightType> *, CharType> node2char;
public:
    LinkHuffmanTree(CharType ch[], WeightType w[], int n);
    LinkHuffmanTree(const LinkHuffmanTree<CharType, WeightType> &source);
    virtual ~LinkHuffmanTree();
    // 编码
    CharString encode(CharType ch);
    // 解码
    CharString decode(const CharString& codeStr);
    // 重载
    LinkHuffmanTree<CharType, WeightType> &operator = (const LinkHuffmanTree<CharType, WeightType> &source);

};

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::LinkHuffmanTree(CharType ch[], WeightType w[], int n) {
    // 分配空间
    leafNodes = new LinkHuffmanTreeNode<WeightType>*[n];
    // 先创建叶子节点，并记录相应的字符
    // 创建一个单链表用于构造huffman树
    for(int temp = 0; temp < n; temp++){
        leafNodes[temp] = new LinkHuffmanTreeNode<WeightType>(w[temp]);
        nodeList.insert(temp, leafNodes[temp]);
        node2char[leafNodes[temp]] = ch[temp];
    }

    // 建立Huffman树：进行n-1次操作
    LinkHuffmanTreeNode<WeightType> maxWeight(0x3f3f3f3f);
    LinkHuffmanTreeNode<WeightType> *r1, *r2, *tempNode;
    for(int i = 0; i < n-1; i++){
        // 先初始化r1,r2为无穷大，再选取连个最小权重的节点
        r1 = &maxWeight;
        r2 = &maxWeight;
        for(int index = 0; index < nodeList.length(); index++){
            nodeList.getElem(index, tempNode);
            if(tempNode->weight < r1->weight && tempNode->parent == nullptr){
                // 如果此节点无父节点且更小
                r1 = tempNode;
            } else if(tempNode->weight < r2->weight && tempNode->parent == nullptr){
                // 无父节点的情况
                r2 = tempNode;
            }
        }
        // 创建新的节点,然后将新结点加入nodelist
        LinkHuffmanTreeNode<WeightType> *newNode = new LinkHuffmanTreeNode<WeightType>(r1->weight + r2->weight, r1, r2);
        r1->parent = newNode;
        r2->parent = newNode;
        nodeList.insert(nodeList.length(), newNode);

    }
    nodeList.getElem(nodeList.length()-1, root);
    // 初始化当前位置
    curPos = root;
    // 构建编码
    for(int i = 0; i < n; i++){
        // 有n个叶子结点，循环n次，为每一个叶子结点编码
        SingleLinkList<char> charCode;
        for(LinkHuffmanTreeNode<WeightType> *child = leafNodes[i], *parent = child->parent; parent != nullptr; child = parent, parent = child->parent){
            // 逆向求编码，自叶子结点向上查找
            if(parent->leftChild == child){
                // 左孩子，编码为0
                charCode.insert(0, '0');
            } else {
                // 右分支，编码为1
                charCode.insert(0, '1');
            }
        }
        // 记录编码
        CharString code(charCode);
        char2code[node2char[leafNodes[i]]] = (CharString)charCode;
    }
}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::LinkHuffmanTree(const LinkHuffmanTree<CharType, WeightType> &source) {

}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::~LinkHuffmanTree() {
    nodeList.clear();
    delete[] leafNodes;
}

template<class CharType, class WeightType>
CharString LinkHuffmanTree<CharType, WeightType>::encode(CharType ch) {
    return char2code[ch];
}

template<class CharType, class WeightType>
CharString LinkHuffmanTree<CharType, WeightType>::decode(const CharString& codeStr) {
    // 编码前的字符序列
    SingleLinkList<CharType> charList;
    for(int pos = 0; pos < codeStr.length(); pos++){
        // 每次从根节点向下查找：0为左，1为右
        if(codeStr[pos] == '0'){
            curPos = curPos->leftChild;
        } else {
            curPos = curPos->rightChild;
        }
        // 如果当前为叶子结点，则成功解码一个字符
        if(curPos->leftChild == nullptr && curPos->rightChild == nullptr){
            charList.insert(charList.length(), node2char[curPos]);
            // 解码一个字符后回到根结点
            curPos = root;
        }
    }
    return CharString(charList);
}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType> &
LinkHuffmanTree<CharType, WeightType>::operator=(const LinkHuffmanTree<CharType, WeightType> &source) {

}
#endif //DATASTRUCTURESANDALGORITHMS_LINKHUFFMANTREE_HPP
