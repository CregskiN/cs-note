#include <array>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Window_mgr.h"

int main() {
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3, 4};
    // v1.insert(v1.end(), v2.end() - 2, v2.end());
    // v1.insert(v1.end(), {3, 4, 5, 6, 7});

    auto i1 = v2.begin(),
         i2 = v2.end();

    v2.erase(i1, i2 - 1);
    i1 = v2.begin();
    i2 = v2.end();
    
    while (i1 != i2) {
        std::cout << *i1 << std::endl;
        ++i1;
    }

    return 0;
}