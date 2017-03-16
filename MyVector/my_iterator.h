/*!
    \file
   
    \brief Файл с описанием методов MyVector
  
    \author Трощенков Денис
    
    \data 27.02.2017
 
    Реализация методов класса MyVector
*/

template<typename T>
class MyIterator: public std::iterator<std::input_iterator_tag, T>
{
public:
    MyIterator(T* p);
    MyIterator(const MyIterator<T>&);
    const MyIterator<T>& operator = (const MyIterator<T>&);
    bool operator != (const MyIterator<T>& ) const;
    bool operator == (const MyIterator<T>& ) const; 
    typename MyIterator<T>::reference operator*() const;
    MyIterator<T>& operator++();
private:
    T* p;
};


template<typename T>
MyIterator<T>::MyIterator(T *p) : p(p)
{ }

template<typename T>
MyIterator<T>::MyIterator(const MyIterator& it) : p(it.p)
{ }

template<typename T>
const MyIterator<T>& MyIterator<T>::operator = (const MyIterator<T>& it)
{
    p(it.p);   
    return *this;
}

template<typename T>
bool MyIterator<T>::operator != (const MyIterator& it) const
{
    return p != it.p;
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
MyIterator<T> &MyIterator<T>::operator++()
{
    ++p;
    return *this;
}
