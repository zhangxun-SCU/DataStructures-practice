//
// Created by cw on 2022/10/17.
//

#ifndef DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP
#define DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP

#include <iostream>
#include <fstream>
#include <cctype>
#include "DCLinkList.hpp"
#include "CharString.hpp"

class FileEditor {
private:
    // 文本缓存
    DCLinkList<CharString> textBuffer;
    // 当前行号
    int curLineNum{};
    // 输入、输出文件
    ifstream inFile;
    ofstream outFile;
    unsigned char userCommand{};
    // 判断是否修改
    bool anyChange;
    // 初始化参数
    void init(char *inFName, char *outFName);

    // 复制函数 yes/no
    bool userSaysYes() const;

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
    FileEditor() = default;

    ~FileEditor() = default;

    // 读取命令
    bool getCommand();

    // 运行命令
    void runCommand();

    // 主程序
    void run();
};

void FileEditor::init(char *inFName, char *outFName) {
    anyChange = false;
    curLineNum = 0;
    this->inFile.open(inFName, ios::in);
    readFile();
    this->outFile.open(outFName, ios::out);
    if(inFile.fail() || outFile.fail()){
        cerr<<"文件打开失败"<<endl;
        exit(-1);
    }
}

bool FileEditor::userSaysYes() const {
    CharString answer("");
    if(anyChange){
        cout<<"缓存区修改未保存，确认退出？(yes/no)";
    } else if(!textBuffer.empty()){
        cout<<"缓存区内容未保存，确认退出？(yes/no)";
    } else {
        cout << "确认退出？(yes/no)";
    }
    cin >> answer;
    if(answer == CharString("yes")){
        return true;
    } else{
        return false;
    }
}

bool FileEditor::nextLine() {
    //
    if (curLineNum >= textBuffer.length()) {
        cout << "当前行号" << curLineNum << " 总共" << textBuffer.length() << "行，无法到下一行" << endl;
        return false;
    } else {
        curLineNum++;
        return true;
    }
}

bool FileEditor::previousLine() {
    if (curLineNum != 1) {
        curLineNum--;
        return true;
    }
    cerr << "已在第一行，无法倒退" << endl;
    return false;
}

bool FileEditor::gotoLine() {
    int lineNumber;
    cout << " 输入指定行号？";
    cin >> lineNumber;
    if (lineNumber < 1 || lineNumber > textBuffer.length()) {
        cerr << "不存在此行，跳转失败" << endl;
        return false;
    }
    curLineNum = lineNumber;
    return true;
}

bool FileEditor:: insertLine() {
    int lineNumber;
    cout << " 输入指定行号？";
    cin >> lineNumber;
    while (cin.get() != '\n');
    cout << " 输入新行文本：";
    CharString toInsert = CharString::read(cin);
    if (textBuffer.insert(lineNumber - 1, toInsert)) {
        // 插入成功
        curLineNum = lineNumber;
        anyChange = true;
        return true;
    }
    return false;
}

bool FileEditor::changeLine() {
    int lineNumber;
    cout << " 输入指定行号？";
    cin >> lineNumber;
    while (cin.get() != '\n');
    cout << " 输入新行文本：";
    CharString toChange = CharString::read(cin);
    if (textBuffer.setElem(lineNumber - 1, toChange)) {
        curLineNum = lineNumber;
        anyChange = true;
        return true;
    }
    return false;
}

void FileEditor::readFile() {
    CharString line;
    line = CharString::read(inFile);
    textBuffer.insert(textBuffer.length(), line);
    while (!inFile.eof()) {
        inFile >> line;
        textBuffer.insert(textBuffer.length(), line);
    }
    curLineNum = textBuffer.length();
}

void FileEditor::writeFile() {
    CharString line;
    int count = 0;
    while(!textBuffer.empty()){
        textBuffer.removeElem(0, line);
        outFile << line << endl;
    }
    curLineNum = 0;
    anyChange = false;
}

void FileEditor::findCharString() {
    CharString toFind;
    CharString line;
    cout << "输入你要找的内容";
    cin >> toFind;
    for (int i = 0; i < textBuffer.length(); i++) {
        textBuffer.getElem(i, line);
        if (line == toFind) {

        }
    }

}

void FileEditor::view() {
    if (textBuffer.empty()) {
        cerr << "当前缓存区为空" << endl;
    } else {
        CharString line;
        cout << "当前缓存区如下: " << endl;
        for (int i = 0; i < textBuffer.length(); i++) {
            textBuffer.getElem(i, line);
            cout << i + 1 << ": " << line << endl;
        }
    }
}

bool FileEditor::getCommand() {
    // 读取命令：q表示退出
    CharString curLine;  // 当前行
    if (curLineNum != 0) {
        // 存在当前行
        textBuffer.getElem(curLineNum - 1, curLine);
        cout << curLineNum << ": " << curLine << endl << "?";
    } else {
        cout << "文件缓存空" << endl << "?";
    }
    // 取指令 && 转为小写
    cin >> userCommand;
    userCommand = tolower(userCommand);
    while (cin.get() != '\n');
    if (userCommand == 'q' && userSaysYes()) {
        cout << "退出系统" << endl;
        return false;
    }else {
        return true;
    }
}

void FileEditor::runCommand() {
    switch (userCommand) {
        case 'q':
            // 误触q指令，跳过本次run
            break;
        case 'b':
            // begin：转到第一行
            if (textBuffer.empty()) {
                // 文本缓存空
                cerr << "warning: 文本缓存空!" << endl;
            } else {
                // 文本缓存非空
                curLineNum = 1;
            }
            break;
        case 'c':
            // change：替换当前行
            if (textBuffer.empty()) {
                // 文本缓存为空
                cerr << "warning: 文本缓存空!" << endl;
            } else if (!changeLine()) {
                cout << "warning: 操作失败!" << endl;
            }
            break;
        case 'd':
            // delete：删除当前行
            if (textBuffer.empty()) {
                // 文本缓存为空
                cerr << "warning: 文本缓存空!" << endl;
            } else if (curLineNum == textBuffer.length() && textBuffer.deleteElem(curLineNum - 1)) {
                curLineNum--;
            } else {
                cerr << "warning: 操作失败!" << endl;
            }
            break;
        case 'e':
            // end：转到最后一行
            if (textBuffer.empty()) {
                // 文本缓存为空
                cerr << "warning: 文本缓存空!" << endl;
            } else {
                curLineNum = textBuffer.length();
            }
            break;
        case 'f':
            // find：当当前行开始查找指定文本
            if (textBuffer.empty()) {
                // 文本缓存为空
                cerr << "warning: 文本缓存空!" << endl;
            } else {
                findCharString();
            }
            break;
        case 'g':
            // goto：转到指定行
            if (!gotoLine()) {
                cerr << "error: 操作失败!"<<endl;
            }
            break;
        case '?':
            // 获得帮助
        case 'h':
            // help：获得帮助
            cout << "有效命令: b(egin) c(hange)" << endl
                 << "d(el) e(nd) f(ind) g(oto) h(elp)" << endl
                 << "i(nsert) n(ext) p(revious) q(uit)" << endl
                 << "r(ead) v(iew) w(rite)" << endl;
            break;
        case 'i':
            // insert：插入指定行
            if (!insertLine()) {
                cerr << "error: 操作失败!" << endl;
            }
            break;
        case 'n':
            // next：转到下一行
            if (!nextLine()) {
                cerr << "error: 操作失败" << endl;
            }
            break;
        case 'p':
            // previous：转到前一行
            if (!previousLine()) {
                cerr << "error: 操作失败" << endl;
            }
            break;
        case 'r':
            // read：读入文本
            readFile();
            break;
        case 'v':
            // view：显示文本
            view();
            break;
        case 'w':
            // write：写文本缓存到输出文件中
            if (textBuffer.empty()) {
                cerr << "warning: 文本缓存空" << endl;
            } else {
                writeFile();
            }
            break;
        default:
            cout << "输入h或？获得帮助或输入有效指令。" << endl;
    }
}

void FileEditor::run() {
    char inFName[256], outFName[256];
    cout << "输入文件名(default:file_in.txt)";
    CharString::strcpy(inFName, CharString::read(cin).toCStr());
    // 判空
    if (CharString::strlen(inFName) == 0) {
        CharString::strcpy(inFName, "file_in.txt");
    }
    cout << "输出文件名(default:file_out.txt)";
    CharString::strcpy(outFName, CharString::read(cin).toCStr());
    if(CharString::strlen(outFName) == 0){
        CharString::strcpy(outFName, "file_out.txt");
    }
    // 初始化参数：相当于构造函数
    init(inFName, outFName);
    while (getCommand()) {
        runCommand();
    }
    inFile.close();
    outFile.close();
}


#endif //DATASTRUCTURESANDALGORITHMS_FILEEDITOR_HPP
