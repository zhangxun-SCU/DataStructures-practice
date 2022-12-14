//
// Created by cw on 2022/10/16.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CHARSTRING_HPP
#define DATASTRUCTURESANDALGORITHMS_CHARSTRING_HPP

#include <iostream>
#include <cassert>
#include "SingleLinkList.hpp"

using namespace std;

class CharString {
protected:
    // 串值
    char *strVal;
    // 串长
    int size;
public:
    CharString();

    // C风格转换的构造函数
   explicit CharString(const char *source);

    // 复制构造
    CharString(const CharString &source);

    // 从线性表转换的构造函数
    explicit CharString(SingleLinkList<char> &source);

    // 析构
    virtual ~CharString();

    // 求串长度
    int length() const;

    // 判空
    bool empty() const;

    // 转换为C风格字符串
    const char *toCStr() const;

    // 重载
    CharString &operator=(const CharString &source);

    CharString &operator=(const char *source);

    const char &operator[](int i) const;

    /**         其他重载            **/
    friend ostream &operator<<(ostream &output, const CharString &out);

    friend istream &operator>>(istream &input, CharString &in);

    bool operator==(const CharString &another);

    bool operator!=(const CharString &another);

    /**          串相关操作               **/
    /*C风格字符串函数*/
    static char *strcpy(char *dest, const char *src);

    static char *strncpy(char *dest, const char *src, int n);

    static int strlen(const char *str);

    static char *strcat(char *dest, const char *src);

    static int strcmp(const char *str1, const char *str2);

    /*串基本操作*/
    static void copy(CharString &target, const CharString &source);

    // 复制n个字符
    static void copy(CharString &target, const CharString &source, int n);

    static void concat(CharString &target, const CharString &source);

    static CharString subString(const CharString &s, int pos, int len);

    static int index(const CharString &target, const CharString &pattern, int pos = 0);

    // 从输入流读入串
    static CharString read(istream &input);

    // 读入串，并用terminalChar返回串结束字符
    static CharString read(istream &input, char &terminalChar);

    // 输出串
    static void write(CharString &s);
};

CharString::CharString() : strVal(new char [0]), size(0) {}

CharString::CharString(const char *source) {
    size = strlen(source);
    strVal = new char[size + 1];
    strVal = strcpy(strVal, source);
}

CharString::CharString(const CharString &source) {
    size = source.size;
    strVal = new char[size + 1];
    strVal = strcpy(strVal, source.strVal);
}

CharString::CharString(SingleLinkList<char> &source) {
    size = source.length();
    strVal = new char[size + 1];
    for (int i = 0; i < size; i++) {
        source.getElem(i, strVal[i]);
    }
    strVal[size] = '\0';
}

CharString::~CharString() {
    delete[] strVal;
}

int CharString::length() const {
    return size;
}

bool CharString::empty() const {
    return size == 0;
}

const char *CharString::toCStr() const {
    return (const char *) strVal;
}

CharString &CharString::operator=(const CharString &source) {
    if (&source != this) {
        delete[] strVal;
        size = source.size;
        strVal = new char[size + 1];
        strcpy(strVal, source.strVal);
    }
    return *this;
}

CharString &CharString::operator=(const char *source) {
    delete[] strVal;
    size = strlen(source);
    strVal = new char[size + 1];
    strcpy(strVal, source);
    return *this;
}

const char &CharString::operator[](int i) const {
    return strVal[i];
}

ostream &operator<<(ostream &output, const CharString &out) {
    output << out.strVal;
    return output;
}

istream &operator>>(istream &input, CharString &in) {
    delete[] in.strVal;
    char temp[1000];
    input >> temp;
    in.size = CharString::strlen(temp);
    in.strVal = new char[in.size + 1];
    CharString::strcpy(in.strVal, temp);
    return input;
}

bool CharString::operator==(const CharString &another) {
    if(!strcmp(this->strVal, another.strVal)){
        return true;
    }
    return false;
}

bool CharString::operator!=(const CharString &another) {
    if(strcmp(this->strVal, another.strVal) != 0){
        return true;
    }
    return false;
}

char *CharString::strcpy(char *dest, const char *src) {
    char *ret = dest;
    assert(src != nullptr && dest != nullptr);
    while ((*ret++ = *src++) != '\0');
    return dest;
}

char *CharString::strncpy(char *dest, const char *src, int n) {
    assert(dest != nullptr && src != nullptr);
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    dest[n] = '\0';
    return dest;
}

int CharString::strlen(const char *str) {
    assert(str != nullptr);
    int len = 0;
    while (str[len++] != '\0');
    return len - 1;
}

char *CharString::strcat(char *dest, const char *src) {
    char *ret = dest;
    assert(dest != nullptr && src != nullptr);
    ret = ret + strlen(dest);
    while ((*ret++ = *src++) != '\0');
    return dest;
}

int CharString::strcmp(const char *str1, const char *str2) {
    assert(nullptr != str1);
    assert(nullptr != str2);
    while(*str1 == *str2){
        if(*str1 == '\0'){
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void CharString::copy(CharString &target, const CharString &source) {
    target.size = source.size;
    target.strVal = new char[target.size + 1];
    strcpy(target.strVal, source.strVal);
}

void CharString::copy(CharString &target, const CharString &source, int n) {
    target.size = n;
    target.strVal = new char[target.size + 1];
    strncpy(target.strVal, source.strVal, n);
}

void CharString::concat(CharString &target, const CharString &source) {
    char *new_strVal = new char[target.size + source.size + 1];
    strcpy(new_strVal, target.strVal);
    strcat(new_strVal, source.strVal);
    target = CharString(new_strVal);
    delete[] new_strVal;
}

CharString CharString::subString(const CharString &s, int pos, int len) {
    char *new_strVal = new char[len + 1];
    strncpy(new_strVal, s.strVal + pos, len);
    CharString ret = CharString(new_strVal);
    return ret;
}

int CharString::index(const CharString &target, const CharString &pattern, int pos) {
    int startPos = pos, curTargetStrPos = pos, curPatternStrPos = 0;
    while (curTargetStrPos <= target.size - pattern.size && curPatternStrPos < pattern.size) {
        if (target[curTargetStrPos] == pattern[curPatternStrPos]) {
            // 如果相等，则继续比较后面的字符
            curTargetStrPos++;
            curPatternStrPos++;
        } else {
            // 不相等，指针回退到开始的下一个
            curTargetStrPos = ++startPos;
            curPatternStrPos = 0;
        }
    }
    if (curPatternStrPos >= pattern.size) {
        // 说明比较到了最后一个字符，说明匹配成功，startPos就是
        return startPos;
    }
    // 否则匹配失败
    return -1;
}

CharString CharString::read(std::istream &input) {
    SingleLinkList<char> temp;
    int size = 0;
    char ch;
    while ((input.peek() != EOF) && ((ch = input.get()) != '\n')) {
        // peek是从输入流中度一个字符，但是指针不往后移动，即是观测一个字符
        // 将字符插入链表
        temp.insert(size++, ch);
    }
    CharString answer(temp);
    return answer;
}

CharString CharString::read(std::istream &input, char &terminalChar) {
    SingleLinkList<char> temp;
    int size = 0;
    char ch;
    while (ch = input.peek() != EOF && (ch = input.get()) != '\n') {
        // peek是从输入流中度一个字符，但是指针不往后移动，即是观测一个字符
        // 将字符插入链表
        temp.insert(size++, ch);
    }
    terminalChar = ch;
    CharString answer(temp);
    return answer;
}

void CharString::write(CharString &s) {
    cout << s.toCStr() << endl;
}


#endif //DATASTRUCTURESANDALGORITHMS_CHARSTRING_HPP
