//
// Created by cw on 2022/10/16.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CHARSTRING_HPP
#define DATASTRUCTURESANDALGORITHMS_CHARSTRING_HPP

#include "iostream"
#include "cassert"
#include "SingleLinkList.hpp"

using namespace std;

class CharString {
private:
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
    CharString(SingleLinkList<char> &source);

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



    /**          串相关操作               **/
    /*C风格字符串函数*/
    static char *strcpy(char *dest, const char *src);

    static char *strncpy(char *dest, const char *src, int n);

    static int strlen(const char *str);

    static char *strcat(char *dest, const char *src);

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

CharString::CharString() : strVal(nullptr), size(0) {}

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
    while (str[len++] != '\0')
        ;
    return len - 1;
}

char *CharString::strcat(char *dest, const char *src) {
    char *ret = dest;
    assert(dest != nullptr && src != nullptr);
    ret = ret + strlen(dest);
    while ((*ret++ = *src++) != '\0');
    return dest;
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
    while (ch = input.peek() != EOF && (ch = input.get()) != '\n') {
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
