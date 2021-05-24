#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    std::vector<int> vector{0,0,0,0};
    auto itend{vector.begin()-10000};
    auto it{vector.begin()};
    myvector<int> vec{5,6,7,8,9,784};
    for (;it>itend;--it){
        if(*it!=0){
            std::cout << *it << std::endl;
            *it = 197;
        }
    }
    std::cout << vec << "\n";
    return(0);
}
