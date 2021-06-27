#pragma once
#include <iostream>
#include <initializer_list>
#include <compare>
#include <utility>

template <class T>
class myvector{
private:
    T *m_array;
    int m_size;
public:
    class const_myiterator : std::iterator<std::random_access_iterator_tag, T>{
        friend class myvector<T>;
    private:
        T *m_ptr;
        const_myiterator(T *ptr) : m_ptr(ptr){};
    public:
        const_myiterator() : m_ptr(nullptr){};
        const_myiterator(const const_myiterator &it) : m_ptr(it.m_ptr){};
        const_myiterator(const_myiterator &&it);
        const T& operator=(const const_myiterator &it) noexcept;
        const T& operator=(const_myiterator &&it) noexcept;
        const T& operator*() const noexcept { return (*m_ptr); };
        T* operator->() const noexcept { return (m_ptr); };
        const_myiterator &operator++() noexcept;
        const_myiterator operator++(int) noexcept;
        const_myiterator &operator--() noexcept;
        const_myiterator operator--(int) noexcept;
        const_myiterator &operator+=(std::ptrdiff_t step) noexcept;
        const_myiterator operator+(std::ptrdiff_t step) const noexcept;
        const_myiterator &operator-=(std::ptrdiff_t step) noexcept;
        const_myiterator operator-(std::ptrdiff_t step) const noexcept;
        const T& operator[](std::ptrdiff_t step) const noexcept;
        std::ptrdiff_t operator-(const const_myiterator & right) const noexcept{return(m_ptr-right.m_ptr);};
        bool operator!=(const const_myiterator &right) const noexcept{return(!(m_ptr==right.m_ptr));};
        std::strong_ordering operator<=>(const const_myiterator &right) const noexcept{return(m_ptr<=>right.m_ptr);};
    };
    class myiterator : public const_myiterator{
        friend class myvector<T>;
    private:
        myiterator(T *ptr) : const_myiterator(ptr){};
    public:
        myiterator() : const_myiterator(nullptr){};
        myiterator(const myiterator &it) : const_myiterator(it.m_ptr){};
        myiterator(myiterator &&it);
        myiterator(const const_myiterator &it) : const_myiterator(it.m_ptr){};
        myiterator(const_myiterator &&it);
        T& operator=(const myiterator &it);
        T& operator=(myiterator &&it);
        T& operator*() const noexcept{return(*(this->m_ptr));};
        T* operator->() const noexcept{return(this->m_ptr);};
        myiterator &operator++() noexcept;
        myiterator operator++(int) noexcept;
        myiterator &operator--() noexcept;
        myiterator operator--(int) noexcept;
        myiterator &operator+=(std::ptrdiff_t step) noexcept;
        myiterator operator+(std::ptrdiff_t step) const noexcept;
        myiterator &operator-=(std::ptrdiff_t step) noexcept;
        myiterator operator-(std::ptrdiff_t step) const noexcept;
        T& operator[](std::ptrdiff_t step) const noexcept;
    };
    // constructors
    myvector(): m_size(0),m_array(nullptr){};
    myvector(int size) : m_array(nullptr),m_size(size){};
    myvector(const std::initializer_list<T> &list);
    myvector(const myvector &myvec);
    myvector(myvector &&myvec);
    virtual ~myvector();
    // operators
    T &operator[](const int index) const { return (m_array[index]); };
    T &operator[](const int index) { return (m_array[index]); };
    myvector<T> &operator=(const myvector<T> &myvec);
    myvector<T> &operator=(myvector<T> &&myvec);
    template <class U>
    friend std::ostream &operator<<(std::ostream &out, const myvector<U> &myvec);
    template <class U>
    friend bool operator==(const myvector<U> &a, const myvector<U> &b);
    // functions
    const_myiterator cbegin() const;
    const_myiterator cend() const;
    myiterator begin() const;
    myiterator end() const;
    myiterator insert(const_myiterator it, T& value){return(emplace(it,value));};
    myiterator insert(const_myiterator it, T&& value){return(emplace(it,std::move(value)));};
    myiterator insert(const_myiterator it, const std::initializer_list<T> &list){return(emplace(it,list));};
    myiterator emplace(const_myiterator it, T&& value);
    myiterator emplace(const_myiterator it, const std::initializer_list<T> &list);
    void push_back(T value);
    void pop_back();
    void resize(int size);
    int size() const { return (m_size); };
};

// functions
template <class T>
myvector<T>::myiterator myvector<T>::emplace(myvector<T>::const_myiterator it, const std::initializer_list<T> &list){
    m_size+=list.size();
    T *temp = new T[m_size];
    int inserted_count{0};
    std::ptrdiff_t position{it-cbegin()};
    for (int i{0}; i < m_size; ++i){
        if(it-cbegin()==i){
            for (auto &elem : list){
                temp[i] = elem;
                ++i;
            }
            inserted_count += list.size();
            --i;
        }
        else
            temp[i] = m_array[i-inserted_count];
    }
    delete[] m_array;
    m_array = new T[m_size];
    for (int i{0}; i < m_size; ++i)
        m_array[i] = temp[i];
    return(myiterator{begin()+position});
}

template <class T>
myvector<T>::myiterator myvector<T>::emplace(myvector<T>::const_myiterator it, T&& value){
    ++m_size;
    T *temp = new T[m_size];
    int is_inserted{0};
    std::ptrdiff_t position{it-cbegin()};
    for (int i{0}; i < m_size; ++i){
        if(it-cbegin()==i){
            temp[i] = value;
            ++is_inserted;
        }
        else
            temp[i] = m_array[i-is_inserted];
    }
    delete[] m_array;
    m_array = new T[m_size];
    for (int i{0}; i < m_size; ++i)
        m_array[i] = temp[i];
    return(myiterator{begin()+position});
}

template <class T>
myvector<T>::const_myiterator myvector<T>::cbegin() const{
    return (myvector<T>::const_myiterator{m_array});
}

template <class T>
myvector<T>::const_myiterator myvector<T>::cend() const{
    return (myvector<T>::const_myiterator{m_array + m_size});
}

template <class T>
myvector<T>::myiterator myvector<T>::begin() const{
    return (myiterator{m_array});
}

template <class T>
myvector<T>::myiterator myvector<T>::end() const{
    return (myiterator{m_array + m_size});
}



template <class T>
void myvector<T>::push_back(T value){
    resize(m_size + 1);
    m_array[m_size - 1] = value;
}

template <class T>
void myvector<T>::pop_back(){
    resize(m_size - 1);
}

template <class T>
void myvector<T>::resize(int size){
    T *temp = new T[size];
    for (int i{0}; i < size; ++i)
        temp[i] = m_array[i];
    delete[] m_array;
    m_array = new T[size];
    m_size = size;
    for (int i{0}; i < size; ++i)
        m_array[i] = temp[i];
}

// operators

template <class T>
myvector<T> &myvector<T>::operator=(const myvector<T> &myvec){
    if (*this == myvec)
        return (*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    return (*this);
}

template <class T>
myvector<T> &myvector<T>::operator=(myvector<T> &&myvec){
    if (*this == myvec)
        return (*this);
    delete[] m_array;
    m_size = myvec.m_size;
    if (myvec.m_array)
    {
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i)
        {
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
    return (*this);
}

template <class U>
bool operator==(const myvector<U> &a, const myvector<U> &b){
    if (a.m_array == b.m_array)
        return (false);
    return (true);
}

template <class U>
std::ostream &operator<<(std::ostream &out, const myvector<U> &myvec){
    for (int i{0}; i < myvec.m_size; ++i)
        out << myvec.m_array[i] << " ";
    return (out);
}

// constructors

template <class T>
myvector<T>::myvector(const std::initializer_list<T> &list) : myvector(list.size()){
    m_array = new T[m_size];
    int i{0};
    for (auto &elem : list){
        m_array[i] = elem;
        ++i;
    }
}

template <class T>
myvector<T>::myvector(const myvector<T> &myvec){
    m_size = myvec.m_size;
    if (myvec.m_array){
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
}

template <class T>
myvector<T>::myvector(myvector<T> &&myvec){
    m_size = myvec.m_size;
    if (myvec.m_array){
        m_array = new T[m_size];
        for (int i{0}; i < myvec.m_size; ++i){
            m_array[i] = myvec.m_array[i];
        }
    }
    else
        m_array = nullptr;
    myvec.m_array = nullptr;
}

template <class T>
myvector<T>::~myvector(){
    delete[] m_array;
}

/*
----------------------------------------------------------------------------------
*/
template <class T>
const T& myvector<T>::const_myiterator::operator[](std::ptrdiff_t step) const noexcept{
    return(*(*this + step));
}

template <class T>
myvector<T>::const_myiterator &myvector<T>::const_myiterator::operator+=(std::ptrdiff_t step) noexcept
{
    m_ptr += step;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator+(std::ptrdiff_t step) const noexcept{
    auto temp{*this};
    temp+=step;
    return(temp);
}

template <class T>
myvector<T>::const_myiterator& myvector<T>::const_myiterator::operator-=(std::ptrdiff_t step) noexcept{
    m_ptr += step;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator-(std::ptrdiff_t step) const noexcept{
    auto temp{*this};
    temp-=step;
    return(temp);
}



template <class T>
myvector<T>::const_myiterator &myvector<T>::const_myiterator::operator++() noexcept{
    ++m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator++(int) noexcept{
    auto old{*this};
    ++m_ptr;
    return (old);
}

template <class T>
myvector<T>::const_myiterator &myvector<T>::const_myiterator::operator--() noexcept{
    --m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator myvector<T>::const_myiterator::operator--(int) noexcept{
    auto old{*this};
    --m_ptr;
    return (old);
}

template <class T>
const T& myvector<T>::const_myiterator::operator=(myvector<T>::const_myiterator &&it) noexcept{
    if (&it == this)
        return *this;
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return (*this);
}

template <class T>
const T& myvector<T>::const_myiterator::operator=(const myvector<T>::const_myiterator &it) noexcept{
    if (&it == this)
        return *this;
    m_ptr = it.m_ptr;
    return (*this);
}

template <class T>
myvector<T>::const_myiterator::const_myiterator(myvector<T>::const_myiterator &&it){
    m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
}

/*
----------------------------------------------------------------------------------
*/

template <class T>
T& myvector<T>::myiterator::operator=(myvector<T>::myiterator &&it){
    if (&it == this)
        return *this;
    this->m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
    return (*this);
}

template <class T>
T& myvector<T>::myiterator::operator=(const myvector<T>::myiterator &it){
    if (&it == this)
        return *this;
    this->m_ptr = it.m_ptr;
    return (*this);
}

template <class T>
myvector<T>::myiterator::myiterator(myvector<T>::myiterator &&it){
    this->m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
}

template <class T>
myvector<T>::myiterator::myiterator(myvector<T>::const_myiterator &&it){
    this->m_ptr = it.m_ptr;
    it.m_ptr = nullptr;
}

template <class T>
T& myvector<T>::myiterator::operator[](std::ptrdiff_t step) const noexcept{
    return(*(*this + step));
}

template <class T>
myvector<T>::myiterator &myvector<T>::myiterator::operator+=(std::ptrdiff_t step) noexcept
{
    this->m_ptr += step;
    return (*this);
}

template <class T>
myvector<T>::myiterator myvector<T>::myiterator::operator+(std::ptrdiff_t step) const noexcept{
    auto temp{*this};
    temp+=step;
    return(temp);
}

template <class T>
myvector<T>::myiterator& myvector<T>::myiterator::operator-=(std::ptrdiff_t step) noexcept{
    this->m_ptr += step;
    return (*this);
}

template <class T>
myvector<T>::myiterator myvector<T>::myiterator::operator-(std::ptrdiff_t step) const noexcept{
    auto temp{*this};
    temp-=step;
    return(temp);
}



template <class T>
myvector<T>::myiterator &myvector<T>::myiterator::operator++() noexcept{
    ++(this->m_ptr);
    return (*this);
}

template <class T>
myvector<T>::myiterator myvector<T>::myiterator::operator++(int) noexcept{
    auto old{*this};
    ++(this->m_ptr);
    return (old);
}

template <class T>
myvector<T>::myiterator &myvector<T>::myiterator::operator--() noexcept{
    --(this->m_ptr);
    return (*this);
}

template <class T>
myvector<T>::myiterator myvector<T>::myiterator::operator--(int) noexcept{
    auto old{*this};
    --(this->m_ptr);
    return (old);
}
