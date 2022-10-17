//
// Created by cw on 2022/10/10.
//

#ifndef DATASTRUCTURESANDALGORITHMS_CALCULATOR_HPP
#define DATASTRUCTURESANDALGORITHMS_CALCULATOR_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "iostream"
#include "stack"
#include "Utils.hpp"

using namespace std;

#define N_OPTR 9 //运算符总数
typedef enum {
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;

class Calculator {
private:
    stack<double> opnd;
    stack<char> optr;
    const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
            /*              |-------------------- 当 前 运 算 符 --------------------| */
            /*                +          -          *          /          ^          !         (          )          =    */
            /* + */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
            /* - */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
            /* * */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
            /* / */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
            /* ^ */    '>', '>', '>', '>', '>', '<', '<', '>', '>',
            /* ! */    '>', '>', '>', '>', '>', '>', 'e', '>', '>',
            /* ( */    '<', '<', '<', '<', '<', '<', '<', '=', 'e',
            /* ) */    'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
            /* = */    '<', '<', '<', '<', '<', '<', '<', 'e', '='
    };

    // 辅助函数
    // 判断字符ch是否为操作符
    static bool isOperator(char ch);

    // 操作符转为对映的枚举变量，本质转为在操作符表中的下标
    static Operator optr2rank(char op);

    // 判断theta1与theta2的优先级
    char precede(char theta1, char theta2);

    // 从操作数栈里退出两个元素
    static void get2oprands(stack<double> &opnd, double &left, double &right);

    // 从操作数栈里退出两个元素
    static void get1oprand(stack<double> &opnd, double &left);

    // 执行二元运算
    static double calcu(double left, char op, double right);

    // 执行一元运算
    static double calcu(char op, double left);

public:
    Calculator() = default;

    virtual ~Calculator() = default;

    void Run();
};


bool Calculator::isOperator(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
        case '!':
        case '=':
            return true;
        default:
            return false;
    }
}

Operator Calculator::optr2rank(char op) {
    switch (op) {
        case '+' :
            return ADD; //加
        case '-' :
            return SUB; //减
        case '*' :
            return MUL; //乘
        case '/' :
            return DIV; //除
        case '^' :
            return POW; //乘方
        case '!' :
            return FAC; //阶乘
        case '(' :
            return L_P; //左括号
        case ')' :
            return R_P; //右括号
        case '=':
            return EOE; //起始符与终止符
        default  :
            exit(-1); //未知运算符
    }
}

char Calculator::precede(char theta1, char theta2) {
    return pri[optr2rank(theta1)][optr2rank(theta2)];
}

void Calculator::get2oprands(stack<double> &opnd, double &left, double &right) {
    right = opnd.top();
    opnd.pop();
    left = opnd.top();
    opnd.pop();
}

void Calculator::get1oprand(stack<double> &opnd, double &left) {
    left = opnd.top();
    opnd.pop();
}

double Calculator::calcu(double left, char op, double right) {
    switch (op) {
        case '+' :
            return left + right;
        case '-' :
            return left - right;
        case '*' :
            return left * right;
        case '/' :
            if (0 == right) {
                exit(-1);
            }
            return left * 1.0 / right; //注意：如此判浮点数为零可能不安全
        case '^' :
            return pow(left, right);
        default  :
            exit(-1);
    }
}

double Calculator::calcu(char op, double left) {
    switch (op) {
        case '!':
            return Utils::factorial(left);
        default:
            exit(-1);
    }
}

void Calculator::Run() {
    optr.push('=');
    // 临时字符
    char ch;
    // 栈顶字符
    char optrTop;
    // 操作数
    double operand;
    // 操作符
    char theta;

    cin >> ch;
    while ((optrTop = optr.top(), optrTop != '=') || ch != '=') {
        if (!isOperator(ch)) {
            // 不是操作符, 即是一个操作数，将ch放回输入流，读入double数据
            cin.putback(ch);
            cin >> operand;
            opnd.push(operand);
            // 读取下一个字符
            cin >> ch;
        } else {
            // ch是操作符
            switch (precede(optrTop, ch)) {
                case '<':
                    optr.push(ch);
                    cin >> ch;
                    break;
                case '=':
                    optrTop = optr.top();
                    optr.pop();
                    cin >> ch;
                    break;
                case '>':
                    theta = optr.top();
                    optr.pop();
                    // 判断单目还是双目
                    if (theta == '!') {
                        double left;
                        get1oprand(opnd, left);
                        opnd.push(calcu(theta, left));
                    } else {
                        double left, right;
                        get2oprands(opnd, left, right);
                        opnd.push(calcu(left, theta, right));
                    }
                    break;
                case 'e':
                    cout << "操作符出错！" << endl;
                    exit(1);
            }
        }
    }
    if(opnd.empty()){
        cout<< 0<<endl;
    } else{
        operand = opnd.top();
        opnd.pop();
        cout << operand << endl;
    }
}

#endif //DATASTRUCTURESANDALGORITHMS_CALCULATOR_HPP
