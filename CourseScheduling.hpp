//
// Created by cw on 2022/12/29.
//

#ifndef DATASTRUCTURESANDALGORITHMS_COURSESCHEDULING_HPP
#define DATASTRUCTURESANDALGORITHMS_COURSESCHEDULING_HPP

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

#include "CharString.hpp"
#include "LinkQueue.hpp"
#include "AdjMatrixDirGraph.hpp"

using namespace std;

struct CourseType{

    CharString courseNo;  // 课程编号
    CharString courseName;  // 课程名称
    int period{0};  // 学时
    int term{0};  // 开课学期

    CourseType() = default;
    CourseType(CharString num, CharString name, int p, int t) : courseNo(num), courseName(name), period(p), term(t) {}
};

template<int termsNum>  // termsNum表示要排课的学期数
class CourseScheduling {
private:
    // 课程信息关系图
    AdjMatrixDirGraph<CourseType, int> *pGraph{};
    // 入度数组
    int *inDeg{};
    // 输入输出
    ifstream inFile;
    ofstream outFile;
    // 入度为0的结点的缓冲队列：无指定学期 + 1-termsNum学期
    LinkQueue<int> zeroInDegQ[termsNum + 1];
    // 课程表信息 ： 学期 + 节次 + 星期 + 课程名
    char courseTable[termsNum + 1][11][6][100] {""};
    // 每学期课程总数
    int coursesNumPerTerm[termsNum + 1] = {0};
    // 将字符串分割为数字并填入数组
    void strSplit(CharString str, int* num);
    // 返回某编号在图中的位置
    int locateVex(const CharString& courseNo);
    // 排课
    void range(int num, int term, CharString courseName);
    // 排一天的一节课
    bool rangeOne(int &weekday, int term, CharString courseName);
    // 排一天的2节课
    bool rangeTwo(int &weekday, int term, CharString courseName);
    // 排一天的3节课
    bool rangeThree(int &weekday, int term, CharString courseName);
    // 查找一天1节空课
    int findOne(int weekday, int term);
    // 查找一天连续两节空课
    int findTwo(int weekday, int term);
    // 查找一天连续三节空课
    int findThree(int weekday, int term);
    // 中文表示的十进制数
    CharString decimalToChineseChar(int n);
    // 有排课信息构造课程关系图
    void createGraph(const CharString &inName);

public:
    CourseScheduling() = default;
    virtual ~CourseScheduling();
    // 拓扑排序
    void TopologicalOrder();
    // 输出课表信息
    void write(const CharString& outFileName);

    void run();
};

template<int termsNum>
void CourseScheduling<termsNum>::strSplit(CharString str, int *num) {
    int count = 1;
    for(int i = 0; i < str.length(); i++){
        if(str[i] > '0' && str[i] <= '9'){
            num[count] = str[i] + 1 - '1';
            count++;
        }
    }
}

template<int termsNum>
int CourseScheduling<termsNum>::locateVex(const CharString& courseNo) {
    CourseType temp_course;
    for(int i = 0; i < pGraph->getVexNum(); i++){
        pGraph->getElem(i, temp_course);
        if(temp_course.courseNo == courseNo){
            // 找到此课程
            return i;
        }
    }
    // 没有找到
    cerr << "warning: 未发现课程号为"<<courseNo << "的课程" <<endl;
    return -1;
}

template<int termsNum>
void CourseScheduling<termsNum>::range(int num, int term, CharString courseName) {
    int weekday = 1;
    // 为了不在同一天排相同的课，所以取一个标志
    bool haveClass[6] = {false, false, false, false, false, false};
    bool threeClass, twoClass, oneClass;
    while(num > 0){
        if(haveClass[weekday]){
            weekday = (weekday + 2 > 5) ? ((weekday + 2) % 5) : (weekday + 2);
            continue;
        }
        if(num >=  3){
            // 排三节课
            threeClass = rangeThree(weekday, term, courseName);
            while(!threeClass && weekday < 6){
                // 如果第一次没有成功，就试试后面
                threeClass = rangeThree(weekday, term, courseName);
                weekday++;
            }
            // 如果还是失败，说明没有连续三节课的空余时间
            if(!threeClass){
                weekday = 1;
                // 用2+1代替3
                twoClass = rangeTwo(weekday, term, courseName);
                if(!twoClass){
                    weekday++;
                    continue;
                } else {
                    // 排完2排1
                    haveClass[weekday] = true;
                    oneClass = rangeOne(weekday, term, courseName);
                    if(!oneClass){
                        // 如果没有1，那只能排在之后
                        num -= 2;
                        weekday = (weekday + 2 > 5) ? ((weekday + 2) % 5) : (weekday + 2);
                        continue;
                    }
                }
            } else {
                // 三节课一次排完了
                haveClass[weekday] = true;
                weekday = (weekday + 2 > 5) ? ((weekday + 2) % 5) : (weekday + 2);
                num -= 3;
            }
        } else if(num == 2){
            twoClass = rangeTwo(weekday, term, courseName);
            if(twoClass){
                num -= 2;
            } else{
                weekday++;
            }
        } else if(num == 1){
            oneClass = rangeOne(weekday, term, courseName);
            if(oneClass){
                num -= 1;
            } else{
                weekday++;
            }
        }
    }
}

template<int termsNum>
bool CourseScheduling<termsNum>::rangeOne(int &weekday, int term, CharString courseName) {
    int pos = findOne(weekday, term);
    if(pos == -1){
        return false;
    }
    CharString::strcpy(courseTable[term][pos][weekday], courseName.toCStr());
    return true;
}

template<int termsNum>
bool CourseScheduling<termsNum>::rangeTwo(int &weekday, int term, CharString courseName) {
    int pos = findTwo(weekday, term);
    if(pos == -1){
        return false;
    }
    for(int i = 0; i < 2; i++){
        CharString::strcpy(courseTable[term][pos+i][weekday], courseName.toCStr());
    }
    return true;
}

template<int termsNum>
bool CourseScheduling<termsNum>::rangeThree(int &weekday, int term, CharString courseName) {
    int pos = findThree(weekday, term);
    if(pos == -1){
        return false;
    }
    for(int i = 0; i < 3; i++){
        CharString::strcpy(courseTable[term][pos+i][weekday], courseName.toCStr());
    }
    return true;
}

template<int termsNum>
int CourseScheduling<termsNum>::findOne(int weekday, int term) {
    for(int i = 1; i < 11; i++){
        if(CharString::strcmp(courseTable[term][i][weekday], "") == 0){
            return i;
        }
    }
    // 没有找到
    return -1;
}

template<int termsNum>
int CourseScheduling<termsNum>::findTwo(int weekday, int term) {
    if(CharString::strcmp(courseTable[term][1][weekday], "") == 0 && CharString::strcmp(courseTable[term][2][weekday], "") == 0){
        return 1;
    }
    if(CharString::strcmp(courseTable[term][3][weekday], "") == 0 && CharString::strcmp(courseTable[term][4][weekday], "") == 0){
        return 3;
    }
    if(CharString::strcmp(courseTable[term][6][weekday], "") == 0 && CharString::strcmp(courseTable[term][7][weekday], "") == 0){
        return 6;
    }
    if(CharString::strcmp(courseTable[term][8][weekday], "") == 0 && CharString::strcmp(courseTable[term][9][weekday], "") == 0){
        return 8;
    }
    return -1;
}

template<int termsNum>
int CourseScheduling<termsNum>::findThree(int weekday, int term) {
    if(CharString::strcmp(courseTable[term][3][weekday], "") == 0
       && CharString::strcmp(courseTable[term][4][weekday], "") == 0
       && CharString::strcmp(courseTable[term][5][weekday], "") == 0){
        return 3;
    }
    if(CharString::strcmp(courseTable[term][8][weekday], "") == 0
       && CharString::strcmp(courseTable[term][9][weekday], "") == 0
       && CharString::strcmp(courseTable[term][10][weekday], "") == 0){
        return 8;
    }
    return -1;
}

template<int termsNum>
CharString CourseScheduling<termsNum>::decimalToChineseChar(int n) {
    switch (n) {
        case 1: return CharString("一");
        case 2: return CharString("二");
        case 3: return CharString("三");
        case 4: return CharString("四");
        case 5: return CharString("五");
        case 6: return CharString("六");
        case 7: return CharString("七");
        case 8: return CharString("八");
        case 9: return CharString("九");
        case 10: return CharString("十");
        default: return CharString("none");
    }
}

template<int termsNum>
void CourseScheduling<termsNum>::createGraph(const CharString &inName) {
    inFile.open(inName.toCStr(), ios::in);
    if(inFile.fail()){
        cerr << "课程信息文件读取失败"<<endl;
        exit(-1);
    }
    // 统计课程总数
    int vexNum = 0;  // 课程总数
    int note_lines = 0;
    string str;
    while(getline(inFile, str, '\n')){
        if(str[0] == '/'){
            note_lines++;
        } else if(str[0] > '0' && str[0] <= '9'){
            // 每学期课程栏
            strSplit(CharString(str.c_str()), coursesNumPerTerm);
            note_lines++;
        } else {
            vexNum++;
        }
    }
    // 恢复文件指针位置
    inFile.clear();
    inFile.seekg(0);
    // 跳过注释
    for(int i = 0; i < note_lines; i++){
        getline(inFile, str, '\n');
    }
    // 构建图并完成关系
    pGraph = new AdjMatrixDirGraph<CourseType, int>(vexNum);
    inDeg = new int[vexNum]{0};
    CourseType courseV, courseW;
    CharString courseNo, courseName, perCourseNum;
    int period, term;
    int v = 0;  // 记录录入课程数量是否正确
    int temp_ch;
    // 读取第一门课的信息，第一门课不会又先修课程
    inFile >> courseNo;
    inFile >> courseName;
    inFile >> period;
    inFile >> term;
    pGraph->setElem(v++, CourseType(courseNo, courseName, period, term));
    for(; v < vexNum; ){
        inFile >> courseNo;
        inFile >> courseName;
        inFile >> period;
        inFile >> term;
        pGraph->setElem(v, CourseType(courseNo, courseName, period, term));
        temp_ch = inFile.peek();
        if(inFile.eof()){
            break;
        }
        // 如果temp_ch 不是换行，那说明有先修课程
        while(temp_ch != '\n'){
            inFile >> perCourseNum;
            int w = locateVex(perCourseNum);
            pGraph->insertEdge(w, v);
            inDeg[v]++;  // 此结点入度 +1
            temp_ch = inFile.peek();
        }
        v++;
    }
    inFile.close();
}

template<int termsNum>
void CourseScheduling<termsNum>::TopologicalOrder() {
    CourseType courseV, courseW;
    int size0, sizeTerm, v, w;
    // 统计入度为0的结点，即不需要先导课程
    for(v = 0; v < pGraph->getVexNum(); v++){
        if(inDeg[v] == 0){
            pGraph->getElem(v, courseV);
            // 每个学期入度为0的课都入读
            zeroInDegQ[courseV.term].enQueue(v);
        }
    }

    // 生成课表
    for(int term = 1; term <= termsNum; term++){
        // term: 0-term-1,从0开始
        size0 = zeroInDegQ[0].length();  // 没有要求开设学期的课程
        sizeTerm = zeroInDegQ[term].length();  // term学期的课程
        // ??
        if(size0 + sizeTerm < coursesNumPerTerm[term] || sizeTerm > coursesNumPerTerm[term]){
            cerr << "term: " << term << endl;
            cerr << "size0: " << size0 << endl;
            cerr << "sizeTerm: " << sizeTerm << endl;
            cerr << "coursesNumPerTerm: " << coursesNumPerTerm[term] << endl;
            cerr << "排课时出现冲突!" << endl;
            exit(10);
        }
        // 排第term学期的课程
        for(int i = 0; i < sizeTerm; i++){
            zeroInDegQ[term].deQueue(v);
            pGraph->getElem(v, courseV);
            range(courseV.period, term, courseV.courseName);
            // 排完一节课后，将后序需要此课程的先修课减去，即入读-1
            for(bool flag = pGraph->firstAdjVex(v, w); flag; flag = pGraph->nextAdjVex(v, w, w)){
                // w 为 v的邻接点
                inDeg[w]--;
                // 在w结点入0度-1后查看其入度是否为0
                pGraph->getElem(w, courseW);
                if(inDeg[w] == 0 && (courseW.term == 0 || courseW.term > term)){
                    // 如果此课入度为0且（没有规定学期或者在此学期之后上）则入队
                    zeroInDegQ[courseW.term].enQueue(w);
                } else if(inDeg[w] == 0 && (courseW.term > 0 && courseW.term <= term)){
                    // 出现异常，有的课不应该出现
                    cerr << "排课时出现冲突！" <<endl;
                    exit(11);
                }
            }
        }
        // 排无学期要求的课程
        for(int i = 0; i < coursesNumPerTerm[term] - sizeTerm; i++){
            zeroInDegQ[0].deQueue(v);
            pGraph->getElem(v, courseV);
            range(courseV.period, term, courseV.courseName);
            for(bool flag = pGraph->firstAdjVex(v, w); flag; flag = pGraph->nextAdjVex(v, w, w)){
                inDeg[w]--;
                pGraph->getElem(w, courseW);
                if(inDeg[w] == 0 && (courseW.term == 0 || courseW.term > term)){
                    zeroInDegQ[courseW.term].enQueue(w);
                } else if(inDeg[w] == 0 && (courseW.term > 0 && courseW.term <= term)){
                    cerr << "排课时出现冲突！"<< endl;
                    exit(12);
                }
            }
        }
    }
}

template<int termsNum>
CourseScheduling<termsNum>::~CourseScheduling() {
    delete[] inDeg;
    delete pGraph;
}

template<int termsNum>
void CourseScheduling<termsNum>::write(const CharString& outFileName) {
    outFile.open(outFileName.toCStr(), ios::out);
    if(outFile.fail()){
        cerr << "课程表文件打开失败"<<endl;
        exit(13);
    }
    outFile << setiosflags(ios::left);
    for(int i = 1; i <= termsNum; i++){
        outFile << "第" << decimalToChineseChar(i) << "学期课表" << endl;
        outFile << setw(18) << "节次";
        outFile << setw(18) << "星期一";
        outFile << setw(18) << "星期二";
        outFile << setw(18) << "星期三";
        outFile << setw(18) << "星期四";
        outFile << setw(18) << "星期五";
        outFile << setw(18) << "星期六";
        outFile << setw(18) << "星期天";
        outFile << endl;

        for(int c = 1; c <= 10; c++){
            outFile << setw(18) << string("第")  +  string(decimalToChineseChar(c).toCStr()) + string("节");
            for(int d = 1; d <= 5; d++){
                outFile << setw(18) << courseTable[i][c][d];
            }
            outFile << endl;
            if (c == 2 || c == 7) {
                outFile << "\n" << "课间休息" << "\n\n";
            } else if (c == 5) {
                outFile << "\n" << "午间休息" << "\n\n";
            } else if (c == 10) {
                outFile << "\n" << "晚自习" << "\n\n\n\n";
            }
        }
    }
    outFile.close();
}

template<int termsNum>
void CourseScheduling<termsNum>::run() {
    CharString inName("course_inf.txt"), outName("");
    cout << "请输入课程信息文件名：";
    cin >> inName;
    cout << "输出课表文件名：";
    cin >> outName;

    createGraph(inName);
    TopologicalOrder();
    write(outName);

}

#endif //DATASTRUCTURESANDALGORITHMS_COURSESCHEDULING_HPP
