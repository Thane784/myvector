#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    std::vector<int> vec{1,2,3,4,5,784,512,1024,20,30,40,50};
    vec.insert(vec.begin()+1,244);
    for(int i{0};i<vec.size();++i)
        std::cout << vec[i] << " ";
    std::cout << "\n";
    myvector<int> myvec{1,2,3,4,5,784,512,1024,20,30,40,50};
    auto myit = myvec.begin();
    myvec.insert(myit+1,244);
    for(int i{0};i<myvec.size();++i)
        std::cout << myvec[i] << " ";
    std::cout << "\n";
    std::cout << (myvec.cbegin()+1)-myvec.cend() << "\n";
    return(0);
}
