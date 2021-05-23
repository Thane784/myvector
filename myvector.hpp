#pragma once
#include <iostream>
#include <initializer_list>
#include <cassert>
#include "myiterator.hpp"
#include "write_check.hpp"

template <class T>
class myvector{
private:
    T* m_array;
    int m_size;
public:
    // constructors
    myvector(){};
    myvector(int size):m_size(size){};
    myvector(const std::initializer_list<T> &list);
    myvector(const myvector& myvec);
    myvector(myvector&& myvec);
    virtual ~myvector(){delete[] m_array;};
    // operators 
    T& operator[] (const int index) const;       
    write_check<T> operator[] (const int index);
    myvector<T>& operator =(const myvector<T> & myvec);
    myvector<T>& operator =(myvector<T>&& myvec);
    template<class U>
    friend std::ostream& operator << (std::ostream &out, const myvector<U> &myvec);
    template<class U>
    friend bool operator == ( const myvector<U> &a, const myvector<U>  &b);
    // functions
    myiterator<T> begin() const;
    myiterator<T> end() const;
    void insert(myiterator<T> it,T value);//ttc assert write
    void push_back(T value);
    void pop_back();
    void resize(int size);
    int size() const {return(m_size);};
};

// functions

template<class T>
myiterator<T> myvector<T>::begin() const{
    return(myiterator{m_array});
}

template<class T>
myiterator<T> myvector<T>::end() const{
    return(myiterator{m_array+m_size});
}

template<class T>
void myvector<T>::insert(myiterator<T> it,T value){
}

template<class T>
void myvector<T>::push_back(T value){
    resize(m_size+1);
    m_array[m_size-1] = value;
}

template<class T>
void myvector<T>::pop_back(){
    resize(m_size-1);
}

template<class T>
void myvector<T>::resize(int size){
    T* temp = new T[size];
    for (int i{0};i<size;++i)
        temp[i] = m_array[i];
    delete[] m_array;
    m_array = new T[size];
    m_size = size;
    for (int i{0};i<size;++i)
        m_array[i] = temp[i];
}

// operators

template<class T>
T& myvector<T>::operator[] (const int index) const{
    if(index<0 or index>=m_size)
        return(0);
    return m_array[index];
}

template<class T>
write_check<T> myvector<T>::operator[] (const int index){
    return(write_check<T>(*this, m_array[index], index));
}

template<class T>
myvector<T>& myvector<T>::operator=(const myvector<T>& myvec){
    if(*this == myvec)
        return(*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if(myvec.m_array){
        m_array = new T[m_size];
        for (int i{0};i<myvec.m_size;++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    return(*this);
}

template<class T>
myvector<T>& myvector<T>::operator=(myvector<T>&& myvec){
    if(*this == myvec)
        return(*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if(myvec.m_array){
        m_array = new T[m_size];
        for (int i{0};i<myvec.m_size;++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
    return(*this);
}

template<class U>
bool operator == ( const myvector<U> &a, const myvector<U>  &b){
    if(a.m_array == b.m_array)
        return(false);
    return(true);
}

template<class U>
std::ostream& operator<< (std::ostream &out, const myvector<U> &myvec){
    for(int i{0};i<myvec.m_size;++i)
        out << myvec.m_array[i] << " ";
    return(out);
}

// constructors

template<class T>
myvector<T>::myvector(const std::initializer_list<T> &list):myvector(list.size()){
    m_array = new T[m_size];
    int i{0};
    for (auto &elem : list){
        m_array[i] = elem;
        ++i;
    }
}


template<class T>
myvector<T>::myvector(const myvector<T>& myvec){
    m_size = myvec.m_size;
    if(myvec.m_array){
        m_array = new T[m_size];
        for (int i{0};i<myvec.m_size;++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
}

template<class T>
myvector<T>::myvector(myvector<T>&& myvec){
    m_size = myvec.m_size;
    if(myvec.m_array){
        m_array = new T[m_size];
        for (int i{0};i<myvec.m_size;++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
}




