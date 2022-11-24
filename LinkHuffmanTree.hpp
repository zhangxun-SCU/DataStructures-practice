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
    LinkHuffmanTreeNode<WeightType> **leafNodes;
    CharString *leafCodes;
    map<CharType, CharString> char2code;
    map<CharString, CharType> code2char;
    map<LinkHuffmanTreeNode<WeightType> *, CharType> node2char;
public:
    LinkHuffmanTree(CharType *ch, WeightType *w, int n);
    LinkHuffmanTree(CharType *ch, map<CharType, WeightType> c2w);
    LinkHuffmanTree(const LinkHuffmanTree<CharType, WeightType> &source);
    virtual ~LinkHuffmanTree();
    // 编码
    CharString encode(CharType ch);
    // 解码
    SingleLinkList<CharType> decode(const CharString& codeStr);
    // 重载
    LinkHuffmanTree<CharType, WeightType> &operator = (const LinkHuffmanTree<CharType, WeightType> &source);

};

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::LinkHuffmanTree(CharType *ch, WeightType *w, int n) {
    // 分配空间
    leafNodes = new CharString[n];
    // 先创建叶子节点，并记录相应的字符
    // 创建一个单链表用于构造huffman树
    SingleLinkList<LinkHuffmanTreeNode<WeightType> *> nodeList;
    for(int temp = 0; temp < n; temp++){
        leafNodes[temp] = new LinkHuffmanTreeNode<WeightType>(w[temp]);
        nodeList.insert(temp, nodeList);
        node2char[leafNodes[temp]] = ch[temp];
    }

    // 建立Huffman树：进行n-1次操作
    LinkHuffmanTreeNode<WeightType> *r1, *r2, *tempNode;
    nodeList.getElem(0, r1);
    nodeList.getElem(1, r2);
    if(r1->weight > r2->weight){
        // 调整大小：r1为最小，r2为次小
        tempNode = r1;
        r1 = r2;
        r2 = tempNode;
    }
    for(int i = 0; i < n-1; i++){
        // 选取连个最小权重的节点
        for(int index = 0; index < nodeList.length(); index++){
            nodeList.getElem(index, tempNode);
            if(tempNode->weight < r1->weight && r1->parent != nullptr){
                // 如果此节点无父节点且更小
                r1 = tempNode;
            } else if(tempNode->weight < r2->weight && r2->parent != nullptr){
                // 无父节点的情况
                r2 = tempNode;
            }
        }
        // 创建新的节点
        LinkHuffmanTreeNode<WeightType> newNode = new LinkHuffmanTreeNode<WeightType>(r1->weight + r2->weight, r1, r2);
        r1->parent = newNode;
        r2->parent = newNode;
    }
    nodeList.getElem(nodeList.length()-1, root);

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
        char2code[node2char[leafNodes[i]]] = charCode;
    }
}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::LinkHuffmanTree(const LinkHuffmanTree<CharType, WeightType> &source) {

}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType>::~LinkHuffmanTree() {

}

template<class CharType, class WeightType>
CharString LinkHuffmanTree<CharType, WeightType>::encode(CharType ch) {
    return char2code[ch];
}

template<class CharType, class WeightType>
SingleLinkList<CharType> LinkHuffmanTree<CharType, WeightType>::decode(const CharString& codeStr) {
    // 编码前的字符序列
    SingleLinkList<CharType> charList;
    LinkHuffmanTreeNode<WeightType> *curPos = root;
    for(int pos = 0; pos < codeStr.length(); pos++){
        // 每次从根节点向下查找：0为左，1为右
        if(codeStr[pos] == '0'){
            curPos = curPos->leftChild;
        } else {
            curPos = curPos->rightChild;
        }
        // 如果当前为叶子结点，则成功解码一个字符
        if(curPos->leftChild == nullptr && curPos->rightChild){
            charList.insert(charList.length(), code2char[curPos]);
            // 解码一个字符后回到根结点
            curPos = root;
        }
    }
    return charList;
}

template<class CharType, class WeightType>
LinkHuffmanTree<CharType, WeightType> &
LinkHuffmanTree<CharType, WeightType>::operator=(const LinkHuffmanTree<CharType, WeightType> &source) {

}
#endif //DATASTRUCTURESANDALGORITHMS_LINKHUFFMANTREE_HPP
