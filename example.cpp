#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    std::vector<int> vec{1,2,3,4,5,784};
    const std::vector<int>::iterator it{vec.begin()};
    std::vector<int>::const_iterator it2;
    it2++;
    it2 = std::vector<int>::const_iterator{vec.end()-1};
    std::cout << *it2 << std::endl;
    return(0);
}
