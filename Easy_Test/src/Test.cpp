#include "../lib/libtest.h"
#include <vector>
#include <iostream>

int main(){
    std::vector<int> a;
    for (int i = 0; i < 10; i++) a.push_back(i);
    std::cout << Sum(a) << '\n';
    std::cout << Sum1(a);
    return 0;
}
