#include <iostream>
#include <vector>
#include "myvector.hpp"

int main(){
    myvector<int> myvec{1,2,3,4,5,784};
    myvec.pop_back();
    myvec.push_back(123);
    myvec.insert(myvec.cbegin()+2,2147483647);
    auto myit = myvec.begin();
    auto myit2 = myit;
    ++myit;
    if(myit>myit2)
        myit += 2;
    myit[3] = 24;
    std::cout << *myvec.insert(myit-2,512) << "\n";
    std::cout << myvec << "\n";
    std::cout << *myvec.insert(myvec.begin()+4,{11,13,17,19,23}) << "\n";
    std::cout << myvec << "\n";
    //
    std::vector vec{1,2,3,4,5,6};
    vec.insert(vec.end(),{1,2,3,4,56,8});
    return(0);
}
