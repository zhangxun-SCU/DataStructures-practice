//
// Created by cw on 2022/12/11.
//

#include "Ackerman.h"
int Ackerman(int m, int n){
    if(m == 0 && n != 0) {
        return n + 1;
    } else if(m != 0 && n == 0){
        return Ackerman(m-1, 1);
    }
    return Ackerman(m-1, Ackerman(m, n-1));
}

int AckermanNoRer(int m, int n){
    int temp_m, temp_n;
    LinkStack<int> stack;
    stack.push(m);
    stack.push(n);
    while(stack.length() != 1){
        stack.pop(temp_n);
        stack.pop(temp_m);
        if(temp_m == 0){
            stack.push(temp_n+1);
        } else if(temp_n == 0){
            stack.push(temp_m - 1);
            stack.push(1);
        } else{
            stack.push(temp_m - 1);
            stack.push(temp_m);
            stack.push(temp_n-1);
        }
    }
    int result;
    stack.pop(result);
    return result;
}