//
// Created by cw on 2022/11/26.
//

#ifndef DATASTRUCTURESANDALGORITHMS_HUFFMANCOMPRESS_HPP
#define DATASTRUCTURESANDALGORITHMS_HUFFMANCOMPRESS_HPP
#include <iostream>
#include <fstream>

#include "LinkHuffmanTree.hpp"

using namespace std;

// 字符缓存器
struct BufferType{
    char ch;
    unsigned int bits;
};

class HuffmanCompress {
protected:
    // haffman树
    LinkHuffmanTree<char, unsigned long> *huffmanTree;
    ifstream inFile;
    ofstream outFile;
    BufferType buffer;
    char *inFName, *outFName;
public:
    HuffmanCompress();
    ~HuffmanCompress();
    void compress();
    void deCompress();
    void run();
};



void HuffmanCompress::run() {
    bool loop_flag = true;
    while(loop_flag){
        cout << "1.压缩" << endl;
        cout << "2.解压缩" << endl;
        cout << "3.退出" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "输入源文件名:";
                cin >> inFName;
                inFile.open(inFName, ios::in|ios::binary);
                if(inFile.fail()){
                    cerr << "源文件打开失败" <<endl;
                    break;
                }
                cout << "输入目标文件名";
                cin >> inFName;
                outFile.open(outFName, ios::out|ios::binary);
                if(outFile.fail()){
                    cerr << "目标文件打开失败" <<endl;
                    break;
                }
                break;
            case 2:
                break;
            case 3:
                cout << "退出程序" << endl;
                loop_flag = false;
            default:
                cout << "输入非法，请重新输入" << endl;
        }
    }
}
#endif //DATASTRUCTURESANDALGORITHMS_HUFFMANCOMPRESS_HPP
