#pragma once
#include <iterator>
#include "myvector.hpp"

template<class T>
class myvector;

template<class V>
class myiterator: std::iterator<std::random_access_iterator_tag, V>{//ttc write
    friend class myvector<V>;
private:
    V* m_ptr;
    myiterator(V *ptr) :m_ptr(ptr){};
public:
    myiterator():m_ptr(nullptr){};
    myiterator(const myiterator& it) :m_ptr(it.m_ptr){};
    myiterator(myiterator&& it);
    myiterator<V>& operator =(const myiterator<V> & it);
    myiterator<V>& operator =(myiterator<V>&& it);
    myiterator::reference operator*() const {return(*m_ptr);};
    myiterator::reference operator*(){return(*m_ptr);};
    myiterator<V> operator++(); 
    myiterator<V> operator++(V);
    myiterator<V> operator--();
    myiterator<V> operator--(V);
    bool operator==(myiterator const& other) const {return(m_ptr == other.m_ptr);};
    bool operator!=(myiterator const& other) const {return(m_ptr != other.m_ptr);};
    myiterator::reference operator[](ptrdiff_t n) const;
};

/*
template<class V>
myiterator<V>::reference myiterator<V>::operator[](myiterator::difference_type n) const{
}
*/

template<class V>
myiterator<V>::reference myiterator<V>::operator[](ptrdiff_t n) const{
    auto temp = *this;
    //temp += n; //ttc write
    return(temp);
}

template<typename V>
myiterator<V>& myiterator<V>::operator =(myiterator<V> && it){
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return(*this);
}

template<typename V>
myiterator<V>& myiterator<V>::operator =(const myiterator<V> & it){
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

