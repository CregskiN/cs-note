#include <iostream>
#include <cstdio>

using namespace std;
int idx;
int Array[8] = {0};
class Parent {
   public:
    Parent() { Array[idx++] = 9; }
    virtual ~Parent() { Array[idx++] = 8; }
    virtual void fun() { Array[idx++] = 10; }
    void fun1() { Array[idx++] = 6; }
    void fun2(int x) { Array[idx++] = x; }
};

class Child : public Parent {
   public:
    Child() { Array[idx++] = 3; }
    virtual ~Child() { Array[idx++] = 5; }
    virtual void fun() { Array[idx++] = 4; }
    void fun1() { Array[idx++] = 2; }
    void fun2(int x, int y) { Array[idx++] = x + y; }
};

int main(int argc, char *argv[]) {
    Parent *pP;
    idx = 0;
    pP = new Child;
    pP->fun();
    pP->fun1();
    pP->fun2(4);
    delete pP;
    for (int i = 0; i < 8; i++) {
        printf("Array[%d] = %d\n", i, Array[i]);
    }
    return 0;
}