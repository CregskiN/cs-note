#include <iostream>
#include <memory>

// #include "StrBlob.h"
using namespace std;
int main() {
    shared_ptr<int> p = make_shared<int>(10);
    shared_ptr<int> q(p.get());
    std::cout << *p << std::endl;
    std::cout << *q << std::endl;
    p = nullptr;
    q = nullptr;

    return 0;
}
