#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    std::vector<int> vec{1,2,3,4,5,784,512,1024,20,30,40,50};
     myvector<std::string> myvec2{"Hello world!","12345678909876654","100x100"};
    myvector<int> myvec{1,2,3,4,5,784,512,1024,20,30,40,50};
    auto myit = myvector<int>::const_myiterator{myvec.cbegin()};
    auto myit2 = myvector<int>::const_myiterator{myvec.cbegin()+2};
    auto it = std::vector<int>::const_iterator{vec.cbegin()};
    myit+=2;
    myit2++;
    std::cout << myit2-myit << std::endl;
    return(0);
}
