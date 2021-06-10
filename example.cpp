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
    myvec.insert(myit-2,512);
    std::cout << myvec << "\n";
    return(0);
}
