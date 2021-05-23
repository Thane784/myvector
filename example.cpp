#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    myvector<int> myvec{1,2,3,4,784};
    std::cout << myvec[4] << "\n";
    std::vector<int> v{1,2,3,4,784}; 
    myvec.resize(-1);
    return(0);
}