#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Window.h"
#include "Window_mgr.h"

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> list1, list2, list3;
    std::copy(vec.begin(), vec.end(), std::inserter(list1, list1.begin()));
    std::copy(vec.begin(), vec.end(), std::back_inserter(list2));
    std::copy(vec.begin(), vec.end(), std::front_inserter(list3));

    for (auto i : list1) {
        std::cout << i;
        std::cout << " ";
    }
    std::cout << std::endl;

    for (auto i : list2) {
        std::cout << i;
        std::cout << " ";
    }
    std::cout << std::endl;

    for (auto i : list3) {
        std::cout << i;
        std::cout << " ";
    }
    std::cout << std::endl;

    return 0;
}