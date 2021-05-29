#pragma once
#include <iterator>
#include "myvector.hpp"
#include "const_myiterator.hpp"

template<class T>
class myvector;

template<class V>
class myiterator: const_myiterator<V>{//ttc write
    friend class myvector<V>;
private:
    V* m_ptr;
    myiterator(V *ptr) :m_ptr(ptr){};
public:
    myiterator():m_ptr(nullptr){};
    myiterator(const myiterator& it) :m_ptr(it.m_ptr){};
    myiterator(myiterator&& it);
    myiterator::reference operator =(const myiterator<V> & it);
    myiterator::reference operator =(myiterator<V>&& it);
};

template<typename V>
myiterator<V>::reference myiterator<V>::operator =(myiterator<V> && it){
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return(*this);
}

template<typename V>
myiterator<V>::reference myiterator<V>::operator =(const myiterator<V> & it){
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    return(*this);
}

template<typename V>
myiterator<V>::myiterator(myiterator&& it){
    m_ptr = it.m_ptr; 
    it.m_ptr = nullptr;
}