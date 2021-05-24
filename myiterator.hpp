#pragma once
#include "myvector.hpp"

template<class T>
class myvector;

template<class V>
class myiterator: public std::iterator<std::random_access_iterator_tag, V>{//ttc write
    friend class myvector<V>;
private:
    V* m_ptr;
    myiterator(V *ptr) :m_ptr(ptr){};
public:
    myiterator(const myiterator& it) :m_ptr(it.m_ptr){};
    myiterator<V>::reference operator*() const {return(*m_ptr);};
    myiterator<V>::reference operator*(){return(*m_ptr);};
    myiterator<V> operator++(); 
    myiterator<V> operator++(V);
    myiterator<V> operator--();
    myiterator<V> operator--(V);
    bool operator==(myiterator const& other) const;
};

template<typename V>
bool myiterator<V>::operator==(myiterator const& other) const{
    return(m_ptr == other.m_ptr);
}

template<typename V>
myiterator<V> myiterator<V>::operator++(){
    ++m_ptr;
    return(*this);
}

template<typename V>
myiterator<V> myiterator<V>::operator++(V){
    auto old_iterator = *this;
    ++m_ptr;
    return(old_iterator);
}

template<typename V>
myiterator<V> myiterator<V>::operator--(){
    --m_ptr;
    return(*this);
}

template<typename V>
myiterator<V> myiterator<V>::operator--(V){
    auto old_iterator = *this;
    --m_ptr;
    return(old_iterator);
}

