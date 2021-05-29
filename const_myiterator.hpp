#pragma once
#include <iterator>
#include "myvector.hpp"

template<class T>
class myvector;

template<class V>
class const_myiterator: std::iterator<std::random_access_iterator_tag, V>{//ttc write
    friend class myvector<V>;
private:
    const V* m_ptr;
    const_myiterator(V *ptr) :m_ptr(ptr){};
public:
    const_myiterator():m_ptr(nullptr){};
    const_myiterator(const const_myiterator& it) :m_ptr(it.m_ptr){};
    const_myiterator(const_myiterator&& it);
    const_myiterator::reference operator =(const const_myiterator<V> & it) noexcept;
    const_myiterator::reference operator =(const_myiterator<V>&& it) noexcept;
    const_myiterator::reference operator*() const noexcept;
    const_myiterator::pointer operator->() const noexcept;
    const_myiterator& operator++() noexcept;
    const_myiterator operator++(int) noexcept;
    const_myiterator& operator--() noexcept;
    const_myiterator operator--(int) noexcept;
    const_myiterator& operator+=(const typename const_myiterator::difference_type _Off) noexcept;
    const_myiterator operator+(const const_myiterator::difference_type _Off) const noexcept;
    const_myiterator& operator-=(const typename const_myiterator::difference_type _Off) noexcept;
    const_myiterator operator-(const const_myiterator::difference_type _Off) const noexcept;
    const_myiterator::difference_type operator-(const const_myiterator& _Right) const noexcept;
    const_myiterator::reference operator[](const const_myiterator::difference_type _Off) const noexcept;
    bool operator==(const const_myiterator& _Right) const noexcept;
    const_myiterator::strong_ordering operator<=>(const const_myiterator& _Right) const noexcept;    
};

template<typename V>
const_myiterator<V>::reference const_myiterator<V>::operator =(const_myiterator<V> && it) noexcept{
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return(*this);
}

template<typename V>
const_myiterator<V>::reference const_myiterator<V>::operator =(const const_myiterator<V> & it) noexcept{
    if (&it == this)
		return *this;
    m_ptr = it.m_ptr;
    return(*this);
}

template<typename V>
const_myiterator<V>::const_myiterator(const_myiterator&& it){
    m_ptr = it.m_ptr; 
    it.m_ptr = nullptr;
}