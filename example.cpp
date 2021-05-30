#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    std::vector<int> vec{1,2,3,4,5,784};
    myvector<int> myvec{1,2,3,4,5,784};
    auto myit = myvector<int>::const_myiterator{myvec.cbegin()};
    auto it = std::vector<int>::const_iterator{vec.cbegin()};
    std::cout << *it << std::endl;
    it+=2;
    std::cout << *(it+3) << std::endl;
    return(0);
}
