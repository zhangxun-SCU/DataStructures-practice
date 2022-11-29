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
struct BufferType {
    char ch;
    unsigned int bits;

    BufferType() = default;

    BufferType(char c, unsigned int b) : ch(c), bits(b) {};
};

class HuffmanCompress {
protected:
    // haffman树
    LinkHuffmanTree<char, unsigned long> *huffmanTree;
    ifstream inFile;
    ofstream outFile;
    BufferType buffer;
    CharString inFName, outFName;
    unsigned long long int fileSize = 0;

    bool openFile();

    void closeFile();

    void write(unsigned short bit);

    void write();

public:
    HuffmanCompress() = default;

    ~HuffmanCompress() = default;

    void compress();

    void deCompress();

    void run();
};

bool HuffmanCompress::openFile() {
    cout << "输入源文件名: ";
    cin >> inFName;
    inFile.open(inFName.toCStr(), ios::in | ios::binary);
    if (inFile.fail()) {
        cerr << "源文件打开失败" << endl;
        return false;
    }
    cout << "输入目标文件名: ";
    cin >> outFName;
    outFile.open(outFName.toCStr(), ios::out | ios::binary);
    if (outFile.fail()) {
        cerr << "目标文件打开失败" << endl;
        return false;
    }
    return true;
}

void HuffmanCompress::closeFile() {
    if (inFile.is_open()) {
        inFile.close();
    }
    if (outFile.is_open()) {
        outFile.close();
    }
}

void HuffmanCompress::write(unsigned short bit) {
    buffer.bits++;
    buffer.ch = (buffer.ch << 1) | bit;
    if (buffer.bits == 8) {
        // 缓存区满32位则输入
        outFile.write((char *)&buffer.ch, 1);
        // 清空缓存区
        buffer.bits = 0;
        buffer.ch = 0;
    }
}

void HuffmanCompress::write() {
    // 用于文件最后缓存区如果没有满就强制写入
    unsigned int len = buffer.bits;
    if (len > 0) {
        // 缓存区不为空，将缓存区充满
        for (unsigned int i = 0; i < 8 - len; i++) {
            write(0);
        }
    }
}

void HuffmanCompress::compress() {
    // 初步统计字符总类和个数
    char r_ch[256];
    unsigned long r_w[256];
    for (int i = 0; i < 256; i++) {
        r_ch[i] = (char) i;
        r_w[i] = 0;
    }
    // 将文件指针定到文件开始
    // 读取文件直到结束并统计字符个数
    inFile.clear();
    inFile.seekg(0, ios::beg);
    char tempChar;
    while (inFile.read(&tempChar, 1)) {
        r_w[(unsigned char)tempChar]++;
        fileSize++;
    }
    // 统计有效字符及其个数
    int numOfCh = 0;
    for (unsigned long i: r_w) {
        if (i != 0) {
            numOfCh++;
        }
    }
    char ch[numOfCh];
    unsigned long w[numOfCh];
    numOfCh = 0;
    for (int i = 0; i < 256; i++) {
        if (r_w[i] != 0) {
            ch[numOfCh] = (char) i;
            w[numOfCh] = r_w[i];
            numOfCh++;
        }
    }
    // 向目标文件先写入源文件信息：0. 文件大小 1.有效字符个数，2.各个有效字符. 3.各个有效字符权重
    outFile.clear();
    outFile.seekp(0, ios::beg);
    outFile.write((char *)&fileSize, sizeof(fileSize));
    outFile.write((char *) &numOfCh, sizeof(numOfCh));
    outFile.write((char *) ch, numOfCh);
    outFile.write((char *) w, 4 * numOfCh);
    // 构造huffman树和缓存区
    huffmanTree = new LinkHuffmanTree<char, unsigned long>(ch, w, numOfCh);
    buffer = *new BufferType(0, 0);
    // 对源文件进行编码并压缩
    inFile.clear();
    inFile.seekg(0, ios::beg);
    while (inFile.read(&tempChar, 1)) {
        CharString code = huffmanTree->encode(tempChar);
        for (int i = 0; i < code.length(); i++) {
            if (code[i] == '0') {
                write(0);
            } else {
                write(1);
            }
        }
    }
    // 检查缓存区是否为空，考虑是否强制写入
    write();
    delete huffmanTree;
}

void HuffmanCompress::deCompress() {
    // 先读取各个字符信息
    inFile.read((char *)&fileSize, sizeof(fileSize));
    int numOfCh = 0;
    inFile.read((char *) &numOfCh, 4);
    char ch[numOfCh];
    inFile.read(ch, numOfCh);
    unsigned long w[numOfCh];
    inFile.read((char *) w, 4 * numOfCh);
    // 构建huffman树
    huffmanTree = new LinkHuffmanTree<char, unsigned long>(ch, w, numOfCh);
    // 读取并解码
    unsigned long long len = 0; // 记录已解码长度
    unsigned char tempChar;
    while (inFile.read((char *)&tempChar, 1)) {
        CharString code("");
        // 读出code
        unsigned char c = tempChar;
        for (int i = 0; i < 8; i++) {
            if (c & 0x80) {
                CharString::concat(code, CharString("1"));
            } else {
                CharString::concat(code, CharString("0"));
            }
            c = c << 1;
        }
        CharString str = huffmanTree->decode(code);
        for (int i = 0; i < str.length(); i++) {
            if(len == fileSize){
                break;
            }
            outFile.write(&str[i], 1);
            len++;
        }
    }
    delete huffmanTree;
}

void HuffmanCompress::run() {
    bool loop_flag = true;
    while (loop_flag) {
        cout << "1.压缩" << endl;
        cout << "2.解压缩" << endl;
        cout << "3.退出" << endl;
        int choice;
        cout << "请选择: ";
        cin >> choice;
        clock_t start_time;
        clock_t end_time;
        switch (choice) {
            case 1:
                // 压缩
                if (!openFile()) break;
                clog << "正在处理，请稍候..." << endl;
                start_time = clock();
                compress();
                end_time=clock();
                clog << "压缩完成" << endl;
                clog << "压缩消耗时间 " <<(double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
                closeFile();
                break;
            case 2:
                // 解压缩
                if (!openFile()) break;
                clog << "正在处理，请稍候..." << endl;
                start_time = clock();
                deCompress();
                end_time = clock();
                clog << "解压完成" << endl;
                clog << "解压消耗时间 " <<(double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
                closeFile();
                break;
            case 3:
                clog << "退出程序" << endl;
                loop_flag = false;
                break;
            default:
                cerr << "输入非法，请重新输入" << endl;
                break;
        }
    }
}

#endif //DATASTRUCTURESANDALGORITHMS_HUFFMANCOMPRESS_HPP
