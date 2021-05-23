#pragma once
#include "myvector.hpp"
#include <unistd.h>

template<class T>
class myvector;

template<class U>
class write_check{ 
private:
    myvector<U>&  m_myvec;
    U& m_object;
    int m_index;
public:
    write_check(myvector<U>& myvec, U& object, int index):
        m_myvec(myvec), m_object(object), m_index(index) {};
    write_check& operator=(U const& object);
    operator U const&(){return(m_object);}   
};

template<class U>
write_check<U>& write_check<U>::operator=(U const& object){
    if(m_index<0 or m_index>=m_myvec.size()){
        std::cout << "The index of array must be correct!" << std::endl;
        throw "The index of array must be correct!";
    }
    m_object = object;
    return(*this);
}