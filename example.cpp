#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    myvector<int> myvec{0,0,0,0};
    myiterator<int> it{myvec.begin()};
    std::cout << *it <<"\n";
    myvector<int> vec{5,6,7,8,9,784};
    std::cout << vec << "\n";
    return(0);
}
