#include <iostream>

typedef char *pstring; 
// 顶层const // 1. cstr为常量指针 2. cstr指向对象为 char 
const pstring cstr = 0; 
// 底层const // 1. ps 为指针 2. ps 指向对象为 常量char 
const pstring *ps = 0; 
// 顶层&底层const // 1. ps2 为常量指针 2. ps指向对象为 常量char 
const pstring *const ps2 = 0; 
// 底层const // 指针cstr2（指向常量char） 
const char *cstr2 = 0; 

int main() {
    /* 
        2.5 处理类型
        + 2.5.1 类型别名
            + typedef、using
    
     */



    return 0;
}
