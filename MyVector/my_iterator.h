/*!
    \file
   
    \brief Файл с реализацией итератора
  
    \author Трощенков Денис
    
    \data 27.02.2017
 
    Реализация MyIterator
*/

template<typename T>
class MyIterator: public std::iterator<std::input_iterator_tag, T>
{
public:
    MyIterator(T*  p);
    MyIterator(const MyIterator<T>&); 

    const MyIterator<T>& operator = (const MyIterator<T>&);
    bool operator != (const MyIterator<T>& ) const;
    bool operator == (const MyIterator<T>& ) const; 
    bool operator < (const MyIterator<T>& ) const; 
    bool operator > (const MyIterator<T>& ) const; 
    bool operator <= (const MyIterator<T>& ) const; 
    bool operator >= (const MyIterator<T>& ) const; 


    typename MyIterator<T>::reference operator*() const;

    inline MyIterator<T>& operator++();
    inline MyIterator<T>& operator--();
    inline MyIterator<T>& operator += (typename MyIterator<T>::difference_type);
    inline MyIterator<T>& operator -= (typename MyIterator<T>::difference_type);
    inline MyIterator<T>& operator + (typename MyIterator<T>::difference_type);
    inline MyIterator<T>& operator - (typename MyIterator<T>::difference_type);
    inline size_t operator - (const MyIterator<T>&);
    inline T* operator->() const;
private:
    T* p;
};

template<typename T>
T* MyIterator<T>::operator -> () const
{
    return p;
}


template<typename T>
MyIterator<T>::MyIterator(T* p) : p(p)
{ }

template<typename T>
MyIterator<T>::MyIterator(const MyIterator& it) : p(it.p)
{ }


template<typename T>
bool MyIterator<T>::operator < (const MyIterator& it) const
{
    return p < it.p;
}

template<typename T>
bool MyIterator<T>::operator > (const MyIterator& it) const
{
    return p > it.p;
}
template<typename T>
bool MyIterator<T>::operator <= (const MyIterator& it) const
{
    return !(p > it.p);
}

template<typename T>
bool MyIterator<T>::operator >= (const MyIterator& it) const
{
    return !(p < it.p);
}


template<typename T>
inline MyIterator<T>& MyIterator<T>::operator += (typename MyIterator<T>::difference_type n)
{
    if(n>=0)
        while(n--) ++(*this);
    else
        while(n++) --(*this);
    return *this;
}

template<typename T>
inline MyIterator<T>& MyIterator<T>::operator -= (typename MyIterator<T>::difference_type n)
{
    return (*this) += -n;
}

template<typename T>
inline MyIterator<T>& MyIterator<T>::operator + (typename MyIterator<T>::difference_type n)
{
    MyIterator<T> temp{*this};
    return temp += n;
}

template<typename T>
inline MyIterator<T>& MyIterator<T>::operator - (typename MyIterator<T>::difference_type n)
{
    MyIterator<T> temp{*this};
    return temp -= n;
}



template<typename T>
const MyIterator<T>& MyIterator<T>::operator = (const MyIterator<T>& it)
{
    p(it.p);   
    return *this;
}

template<typename T>
bool MyIterator<T>::operator != (const MyIterator& it) const
{
    return !(p == it.p);
}

template<typename T>
bool MyIterator<T>::operator == (const MyIterator& it) const
{
    return p == it.p;
}

template<typename T>
typename MyIterator<T>::reference MyIterator<T>::operator*() const
{
    return *p;
}

template<typename T>
inline MyIterator<T> &MyIterator<T>::operator++()
{
    ++p;
    return *this;
}

template<typename T>
inline MyIterator<T> &MyIterator<T>::operator--()
{
    --p;
    return *this;
}

template<typename T>
inline size_t  MyIterator<T>::operator - (const MyIterator<T>& it)
{
    return p - it.p;
}


