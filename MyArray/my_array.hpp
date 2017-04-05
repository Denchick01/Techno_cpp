/*!
*    @file
*
*    @brief Файл с описанием методов MyArray
*
*    @author Трощенков Денис
*
*    @data 27.02.2017
*
*    Реализация методов класса MyArray
*/

namespace mcr {

///Возвращает итератор на первый элемент 
template <typename T, size_t N>
typename MyArray<T, N>::iterator MyArray<T, N>::begin()
{   
    return iterator(data());
}

///Возвращает итератор на элемент, следующий за последним
template <typename T, size_t N> 
typename MyArray<T, N>::iterator MyArray<T, N>::end()
{ 
    return iterator(data() + this->size());
}

///Возвращает итератор на первый элемент 
template <typename T, size_t N> 
typename MyArray<T, N>::const_iterator MyArray<T, N>::begin() const
{
    return const_iterator(data());
}

///Возвращает итератор на элемент, следующий за последним
template <typename T, size_t N> 
typename MyArray<T, N>::const_iterator MyArray<T, N>::end() const
{
    return const_iterator(data() + this->size());
}

///Оператор произвольного доступа для не константного объекта
template <typename T, size_t N>
T& MyArray<T, N>::operator [] (size_type it) 
{
    return m_ptr[it];
}

///Оператор произвольного доступа для константного объекта
template <typename T, size_t N>
const T& MyArray<T, N>::operator [] (size_type it) const
{
    return m_ptr[it];
}

///Оператор сравнения
template <typename T, size_t N>
bool  MyArray<T, N>::operator == (const MyArray<T, N>& rhs) const 
{
    if (rhs.size() != this->size()) {
    return false;
    }

    for (size_t it = 0; it < this->size(); it++){
        if (rhs.m_ptr[it] != m_ptr[it])
            return false;
    }
    return true;
}

///Оператор неравенства
template <typename T, size_t N>
bool  MyArray<T, N>::operator != (const MyArray<T, N>& rhs) const
{
    if (rhs.size() == this->size()) {
    return false;
    }

    for (size_t it = 0; it < this->size(); it++){
        if (rhs.m_ptr[it] == m_ptr[it])
            return false;
    }
    return true;
}

///Доступ к элементу с проверкой выхода за границу
template <typename T, size_t N>
const T& MyArray<T, N>::at(size_t it) const throw (MyException)
{ 
    if (it >= this-> size()) {
        throw  MyException(OUT_RANGE, "ERROR: out of range", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[it];
}

///Доступ к элементу с проверкой выхода за границу
template <typename T,size_t N>
T& MyArray<T, N>::at(size_t it)  throw (MyException)
{
    if (it >= this-> size()) {
        throw MyException(OUT_RANGE, "ERROR: out of range", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[it];
}

///Доступ к первому элементу для константного объекта
template <typename T, size_t N>
const T& MyArray<T, N>::front() const throw (MyException)
{
    if (this->size() == 0) {
        throw MyException(OUT_RANGE, "Error: Array is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[0];
}

///Доступ к первому элементу для не константного объекта
template <typename T, size_t N>
T& MyArray<T, N>::front() throw (MyException)
{
    if (this->size() == 0) {
        throw MyException(OUT_RANGE, "Error: Array is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[0];
}

///Количество элементов массива	
template <typename T, size_t N>
size_t MyArray<T, N>::size() const
{
    return N;
}

///Проверка на наличия элементов
template <typename T, size_t N>
bool MyArray<T, N>::empty() const
{
    return this->size() == 0;
}

///Доступ к верхнему элементу для константного объекта
template <typename T, size_t N>
const T&  MyArray<T, N>::back() const throw (MyException)
{
    if (this->size() == 0) {
        throw MyException(OUT_RANGE, "Error: Array is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[this->size() - 1];
}

///Доступ к Верхнему элементу для не константного объекта
template <typename T, size_t N>
T& MyArray<T, N>::back() throw (MyException)
{
    if (this->size() == 0) {
        throw MyException(OUT_RANGE, "Error: Array is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[this->size() - 1];
}

///Максимально допустимое количество элементов
template <typename T, size_t N>
size_t MyArray<T, N>::max_size() const
{
    size_t max_size =  size_t(pow (2, (sizeof(size_t) * 8) - 1)) - 1;
    max_size = (max_size * 2 + 1)/sizeof(value_type);
    return max_size;
}

///Возвращает указатель на базовый массив
template <typename T, size_t N> 
T* MyArray<T, N>::data()
{
    return m_ptr;   
}

///Обменять содержимое двух массивов
template <typename T, size_t N>
void MyArray<T, N>::swap(mcr::MyArray<T, N>& other )
{
    std::swap(m_ptr, other.m_ptr);
}

}
