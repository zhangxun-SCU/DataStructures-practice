//
// Created by cw on 2022/10/17.
//

#ifndef DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP
#define DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP
#include <iostream>
#include <fstream>

#include "DCLinkList.hpp"
#include "CharString.hpp"

class FileEditor {
private:
    // 文本缓存
    DCLinkList<CharString> textBuffer;
    // 当前行号
    int curLineNum;
    // 输入、输出文件
    ifstream inFile;
    ofstream outFile;
    char userCommand;
    // 复制函数 yes/no
    bool userSaysYes();
    // n -> 转到下一行
    bool nextLine();
    // p -> 转到前一行
    bool previousLine();
    // g -> 转到指定行
    bool gotoLine();
    // i -> 插入一行
    bool insertLine();
    // c -> 替换当前行的指定文本串
    bool changeLine();
    // r -> 读入文本文件
    void readFile();
    // w -> 写文本文件
    void writeFile();
    // f -> 查找串
    void findCharString();
    // v -> 查看显示缓存区
    void view();

public:
    // 构造函数
    FileEditor(char *inFName, char *outFName);
    ~FileEditor() = default;
    // 读取命令
    bool getCommand();
    // 运行命令
    void runCommand();
    // 主程序
    static void run();
};

FileEditor::FileEditor(char *inFName, char *outFName) {

}

bool FileEditor::getCommand() {
    // 读取命令：q表示退出
    CharString curLine;  // 当前行
    if(curLineNum != 0){
        // 存在当前行
        textBuffer.getElem(curLineNum, curLine);
        cout << curLineNum << ": "<<curLine.toCStr()<<endl<<"?";
    } else{
        cout<<"文件缓存空"<<endl<<"?";
    }
    // 取指令 && 转为小写
    cin>>userCommand;
    userCommand = tolower(userCommand);
    while(cin.get() != '\n');
    if(userCommand == 'q'){
        return false;
    } else {
        return true;
    }
}

void FileEditor::runCommand() {
    switch (userCommand) {
        case 'b':
            // begin：转到第一行
            break;
        case 'c':
            // change：替换当前行
            break;
        case 'd':
            // delete：删除当前行
            break;
        case 'e':
            // end：转到最后一行
            break;
        case 'f':
            // find：当当前行开始查找指定文本
            break;
        case 'g':
            // goto：转到指定行
            break;
        case '?':
            // 获得帮助
        case 'h':
            // help：获得帮助
            break;
        case 'i':
            // insert：插入指定行
            break;
        case 'n':
            // next：转到下一行
            break;
        case 'p':
            // prior：转到前一行
            break;
        case 'r':
            // read：读入文本
            break;
        case 'v':
            // view：显示文本
            break;
        case 'w':
            // write：写文本缓存到输出文件中
            break;
        default:
            cout<<"输入h或？获得帮助或输入有效指令。"<<endl;
    }
}

void FileEditor::run() {
    char inFName[256], outFName[256];
    cout<<"输入文件名(default:file_in.txt)";
    CharString::strcpy(inFName, CharString::read(cin).toCStr());
    // 判空
    if(CharString::strlen(inFName) == 0){
        CharString::strcpy(inFName, "file_in.txt");
    }
    cout<<"输出文件名(default:file_out.txt)";
    CharString::strcpy(outFName, CharString::read(cin).toCStr());
    // 定义文本对象
    FileEditor text(inFName, outFName);
    while(text.getCommand()){
        text.runCommand();
    }
    cout<<"退出系统"<<endl;
}


#endif //DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP
