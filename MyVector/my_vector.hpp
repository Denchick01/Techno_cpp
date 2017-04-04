/*!
*    @file
*
*    @brief Файл с описанием методов MyVector
*
*    @author Трощенков Денис
*
*    @data 27.02.2017
*
*    Реализация методов класса MyVector
*/

namespace mcr {

///Вывод структуры вектора на экран
template <typename T> 
inline void MyVector<T>::show_v(std::ostream &output) const
{
    MESSAGE("IN")
    output << "MyVector\n\t{\n";
    output << "\tAmount of elements: " << m_size << "\n";
    output << "\tSize of allocated memory: " << m_capacity << "\n";
    output << "\tMyVector[" << m_size << "]:\n\t\t{\n";

    show_this.show(output, *this);
}

///Возвращает итератор на первый элемент 
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin()
{   
    MESSAGE("IN")
    return iterator(data());
}

///Возвращает итератор на элемент, следующий за последним
template <typename T> 
typename MyVector<T>::iterator MyVector<T>::end()
{ 
    MESSAGE("IN")
    return iterator(data() + m_size);
}

///Возвращает итератор на первый элемент 
template <typename T> 
typename MyVector<T>::const_iterator MyVector<T>::begin() const
{
    MESSAGE("IN")
    return const_iterator(data());
}

///Возвращает итератор на элемент, следующий за последним
template <typename T> 
typename MyVector<T>::const_iterator MyVector<T>::end() const
{
    MESSAGE("IN")
    return const_iterator(data() + m_size);
}

///Вставляет элементы в указанную позицию в контейнере с перемещением
template <typename T> 
typename MyVector<T>::iterator 
MyVector<T>::insert(typename MyVector<T>::const_iterator pos, T&& value) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    return insert(pos, 1, value);
}

///Вставляет элементы в указанную позицию в контейнере с копированием
template <typename T> 
typename MyVector<T>::iterator 
MyVector<T>::insert(typename MyVector<T>::iterator pos, const T& value) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    return insert(pos, 1, value);
}

///Вставляет элементы в указанную позицию в контейнере
template <typename T> 
typename MyVector<T>::iterator
MyVector<T>::insert(typename MyVector<T>::iterator pos, size_t count, const T& value) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (pos > end() || pos < begin()) {
        throw MyException(BAD_ALLOC, "invalid iterator",std::vector<MyException>(), SIMPLE_LINE);
    }
    const  size_t first_pos = pos - begin();
        resize(count + m_size);

    for (iterator it{end() - 1}; it >= (begin() + first_pos); --it) 
        *(it + count) = *it;
   
    for (size_t t_count = 0; t_count < count; ++t_count)
        *((begin() + first_pos) + t_count) = value;
    ASSERT_OK()

    return (begin() + first_pos);
}

///Вставляет элементы в указанную позицию в контейнере.
template <typename T> 
template< class InputIt, typename G >
typename MyVector<T>::iterator
MyVector<T>::insert(typename MyVector<T>::iterator pos, InputIt first, InputIt last) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (pos > end() || pos < begin()) {
        throw MyException(BAD_ALLOC, "invalid iterator",std::vector<MyException>(), SIMPLE_LINE);
    }
    size_t count = 0;
    for (InputIt it(first); it < last; ++it) 
        ++count;

    const  size_t first_pos = pos - begin();
    resize(count + m_size);

    for (iterator it{end() - 1}; it >= (begin() + first_pos); --it) 
        *(it + count) = *it;
   
    for (size_t t_count = 0; t_count < count; ++t_count)
        *((begin() + first_pos) + t_count) = *(first++);

    ASSERT_OK()
    return (begin() + first_pos);
}

///Удаляет элемент в позиции pos
template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(typename MyVector<T>::iterator pos) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    try {
        erase(pos, pos + 1);
    }
    catch (std::bad_alloc& e) {
         throw e;
    }
    ASSERT_OK()
    return pos;   
}

///Удаляет элемент в диапазоне [first; last)
template <typename T>
typename MyVector<T>::iterator 
MyVector<T>::erase(typename MyVector<T>::iterator first, typename MyVector<T>::iterator last) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (last > end() || first < begin() || last <= first) {
        throw MyException(BAD_ALLOC, "invalid iterator",std::vector<MyException>(), SIMPLE_LINE);
    }
    for (iterator it(first), ot(last); ot != end(); ++it, ++ot) 
        *it = *ot;
    resize(m_size - (last - first));
    ASSERT_OK()
    return first;
}

///Вставляет элементы в указанную позицию в контейнере.
template <typename T>
typename MyVector<T>::iterator
MyVector<T>::insert(typename MyVector<T>::iterator pos, std::initializer_list<T> ilist)
{
    MESSAGE("IN")
    ASSERT_OK()
    return insert(pos, ilist.begin(), ilist.end());
}
	 
///Оператор присваивания с копированием
template <typename T>
MyVector<T>& MyVector<T>::operator = (const MyVector<T>& other) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (this == &other) { 
        return *this;	
    }

    this->~MyVector();
    if (new (this) MyVector<T>(other) != this) {
        throw MyException(BAD_ALLOC, "error new",std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return *this;    
}	

///Оператор присваивания с перемещение
template <typename T>
MyVector<T>& MyVector<T>::operator = (MyVector<T>&& other) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
    return *this;    
}	

///Оператор произвольного доступа для не константного объекта
template <typename T>
T& MyVector<T>::operator [] (size_type it) 
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_ptr[it];
}

///Оператор произвольного доступа для константного объекта
template <typename T>
const T& MyVector<T>::operator [] (size_type it) const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_ptr[it];
}

///Оператор сравнения
template <typename T>
bool  MyVector<T>::operator == (const MyVector<T>& rhs) const 
{
    MESSAGE("IN")
    ASSERT_OK()		             
    if (rhs.m_size != m_size) {
    return false;
    }

    for (size_t it = 0; it < m_size; it++){
        if (rhs.m_ptr[it] != m_ptr[it])
            return false;
    }
    ASSERT_OK()	
    return true;
}

///Оператор неравенства
template <typename T>
bool  MyVector<T>::operator != (const MyVector<T>& rhs) const
{
    MESSAGE("IN")
    ASSERT_OK()		             
    if (rhs.m_size == m_size) {
    return false;
    }

    for (size_t it = 0; it < m_size; it++){
        if (rhs.m_ptr[it] == m_ptr[it])
            return false;
    }
    ASSERT_OK()	
    return true;
}

///Конструктор по умолчанию
template <typename T>
MyVector<T>::MyVector() : m_ptr{nullptr},
                                      m_size{0},
                                      m_capacity{0}
{
    MESSAGE("IN")
}

/// Конструктор с инициализацией
template <typename T>
MyVector<T>::MyVector(size_t initial_size, const T& value) throw (MyException): 
                                                                      m_capacity{initial_size}
{
    MESSAGE("IN")
    try {
        m_ptr = new value_type[m_capacity];
    }
    catch(std::bad_alloc& e) {
        MESSAGE(e.what())
        throw MyException(BAD_ALLOC, "new error", std::vector<MyException>(), SIMPLE_LINE);
    }
    for (m_size = 0; m_size < initial_size; ++m_size) {
        m_ptr[m_size] = value;
    }
    ASSERT_OK()
}

///Конструктор с единственным параметром
template <typename T>
MyVector<T>::MyVector(size_t initial_size)	: m_ptr{nullptr},
                                                  m_size{0},
                                                  m_capacity{0}
{
    MESSAGE("IN")  
    value_type zero_obj{value_type()};
    MyVector<value_type> new_obj(initial_size, zero_obj);
    swap(new_obj);
    ASSERT_OK()
}

///Копирующей конструктор	
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) throw (MyException): 
                                                    m_capacity{other.m_size}
{
    MESSAGE("IN")
    try {
        m_ptr = new value_type[m_capacity];
    }
    catch(std::bad_alloc& e) {
        MESSAGE(e.what())
        throw MyException(BAD_ALLOC, "new error", std::vector<MyException>(), SIMPLE_LINE);
    }
    for (m_size = 0; m_size < other.m_size; ++m_size) {
        m_ptr[m_size] = other.m_ptr[m_size];
    }
    ASSERT_OK()
}

///Конструктор с перемещением
template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) : m_ptr{nullptr},
                                                  m_size{0},
                                                  m_capacity{0}
{
    MESSAGE("IN")
    swap(other);
    ASSERT_OK()
}

///Деструктор
template <typename T>
MyVector<T>::~MyVector()
{
    MESSAGE("IN")
    MESSAGE(m_ptr)
    delete [] m_ptr;
    MESSAGE("Destructor is complete!")
}

///Доступ к элементу с проверкой выхода за границу
template <typename T>
const T& MyVector<T>::at(size_t it) const throw (MyException)
{ 
    MESSAGE("IN")
    ASSERT_OK()
    if (it >= m_size) {
        throw  MyException(OUT_RANGE, "ERROR: out of range", std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return m_ptr[it];
}

///Доступ к элементу с проверкой выхода за границу
template <typename T>
T& MyVector<T>::at(size_t it)  throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (it >= m_size) {
        throw MyException(OUT_RANGE, "ERROR: out of range", std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return m_ptr[it];
}

///Доступ к первому элементу для константного объекта
template <typename T>
const T& MyVector<T>::front() const throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Vector is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return m_ptr[0];
}

///Доступ к первому элементу для не константного объекта
template <typename T>
T& MyVector<T>::front() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Vector is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return m_ptr[0];
}

///Удаление верхнего элемента
template <typename T>
void MyVector<T>::pop_back() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Vector is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    m_ptr[--m_size] = value_type();   
    ASSERT_OK()
}

///Добавление элемента с копированием
template <typename T>
void MyVector<T>::push_back(const T& value)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == m_capacity)
        reserve((m_size + 1) * 2);

    m_ptr[m_size++] = value;
    ASSERT_OK()
}

///Добавит элемент с перемещением 
template <typename T>
void MyVector<T>::push_back(T&& value)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == m_capacity)
        reserve((m_size + 1) * 2);
    MESSAGE(m_ptr)
    m_ptr[m_size++] = value;
    ASSERT_OK()
}


///Копирование содержимого 
template <typename T>
void MyVector<T>::copy(mcr::MyVector<T> other) 
{
    MESSAGE("IN")
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
}

///Количество элементов вектора	
template <typename T>
size_t MyVector<T>::size() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_size;
}

///Проверка на наличия элементов
template <typename T>
bool MyVector<T>::empty() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_size == 0;
}

///Доступ к верхнему элементу для константного объекта
template <typename T>
const T&  MyVector<T>::back() const throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Vector is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[m_size - 1];
}

///Доступ к Верхнему элементу для не константного объекта
template <typename T>
T& MyVector<T>::back() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Vector is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[m_size - 1];
}

///Верификатор
template <typename T>
bool MyVector<T>::v_ok() const
{
    MESSAGE("IN")
    if (m_size > m_capacity)
        return false;
    return true;
}
 
///Дампер
template <typename T>
inline void MyVector<T>::dump(const char* file_name, int line , const char* func_name, std::ostream& output) const
{

    m_logg.get_log(output);
 
    output << " FILE: " << file_name << "\n";
    output <<  " ERROR: LINE: " << line << "\n";
    output << " FUNCTION: " << func_name << "\n";

    show_v(output);
}

/// Устанавливает минимально возможное количество элементов в векторе
template <typename T>
void MyVector<T>::reserve(size_t new_capacity) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (new_capacity > m_capacity) {
        if (new_capacity > max_size()) {
            throw MyException(OUT_RANGE, "ERROR: Length error", std::vector<MyException>(), SIMPLE_LINE);
        }
        value_type* old_ptr = m_ptr;
        m_capacity = new_capacity;
        try {
            m_ptr = new value_type[m_capacity];
        }
        catch(std::bad_alloc& e) {
            throw MyException(BAD_ALLOC, "new error", std::vector<MyException>(), SIMPLE_LINE);
        }
        if (old_ptr != nullptr) {
            for (size_type i = 0; i < m_size; i++) {
                m_ptr[i] = old_ptr[i];
            }
            delete [] old_ptr;	
       }
    }
    ASSERT_OK()
} 

///Максимально допустимое количество элементов
template <typename T>
size_t MyVector<T>::max_size() const
{
    MESSAGE("IN")
    ASSERT_OK()
    size_t max_size =  size_t(pow (2, (sizeof(size_t) * 8) - 1)) - 1;
    max_size = (max_size * 2 + 1)/sizeof(value_type);
    ASSERT_OK()
    return max_size;
}


///Изменение размера вектора на заданную величину,
template <typename T>  
void MyVector<T>::resize(size_t new_size, const T& value)  throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (new_size > m_size) {
        if (new_size > m_capacity) {
            reserve(new_size);   
        }    
        for (size_t it = m_size; it < new_size; ++it) {
            m_ptr[it] = value;
        }
    }
    m_size = new_size;
}

///Изменение размеров вектора
template <typename T>			
void MyVector<T>::resize(size_t new_size) throw (MyException)
{
     MESSAGE("IN")
     ASSERT_OK()
     value_type temp_value{value_type()};
     resize(new_size, temp_value);
     ASSERT_OK()
}

///Возвращает указатель на базовый массив
template <typename T> 
T* MyVector<T>::data()
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_ptr;   
}

///Возвращает указатель на базовый массив
template <typename T> 
const T* mcr::MyVector<T>::data() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_ptr;   
}

///Возвращает количество элементов, которое может содержать вектор
template <typename T>
size_t MyVector<T>::capacity() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_capacity;   
}

///Обменять содержимое двух векторов
template <typename T>
void MyVector<T>::swap(mcr::MyVector<T>& other )
{
    MESSAGE("IN")
    ASSERT_OK()

    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_ptr, other.m_ptr);

    ASSERT_OK()
}

///Удаляет все элементы вектора
template <typename T>
void MyVector<T>::clear()
{
    MESSAGE("IN")
    ASSERT_OK()
    m_size = 0;
    ASSERT_OK()
}

///Уменьшает количество используемой памяти
template <typename T>
void MyVector<T>::shrink_to_fit() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()

    m_ptr = (MyVector<T>*) realloc (m_ptr, m_size * sizeof(MyVector<T>));
    if (m_ptr == nullptr) {
        throw MyException(BAD_ALLOC, "realloc error",std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()   
}
} //namespace end
