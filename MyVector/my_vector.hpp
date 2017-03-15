/*!
	\file

	\brief Файл с описанием методов MyVector

	\author Трощенков Денис

	\data 27.02.2017

	Реализация методов класса MyVector
*/

	 
///Оператор присваивания с копированием
template <typename T>
mcr::MyVector<T>& mcr::MyVector<T>::operator = (const mcr::MyVector<T>& other) throw (std::bad_alloc)
{
    MESSAGE("In operator = (const MyVector& other)", std::cout)
    ASSERT_OK()
    if (this == &other) { 
        return *this;	
    }

    this->~MyVector();
    if (new (this) MyVector<T>(other) != this) {
        assert(!"Problem with opertator =");
        throw std::bad_alloc();
    }
    ASSERT_OK()
    return *this;    
}	

///Оператор присваивания с перемещение
template <typename T>
mcr::MyVector<T>& mcr::MyVector<T>::operator = (mcr::MyVector<T>&& other) throw (std::bad_alloc)
{
    MESSAGE("In operator = (MyVector&& other)", std::cout)
    ASSERT_OK()
    if (this == &other) { 
        return *this;	
    }
    swap(other);
    ASSERT_OK()
    return *this;    
}	

///Оператор произвольного доступа для не константного объекта
template <typename T>
T& mcr::MyVector<T>::operator [] (size_type it) 
{
    MESSAGE("In operator []", std::cout)
    ASSERT_OK()
    return m_ptr[it];
}

///Оператор произвольного доступа для константного объекта
template <typename T>
const T& mcr::MyVector<T>::operator [] (size_type it) const
{
    MESSAGE("In operator [] const", std::cout)
    ASSERT_OK()
    return m_ptr[it];
}

///Оператор сравнения
template <typename T>
bool  mcr::MyVector<T>::operator == (const mcr::MyVector<T>& rhs) 
{
    MESSAGE("In operator == ", std::cout)
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

///Конструктор по умолчанию
template <typename T>
mcr::MyVector<T>::MyVector() : m_ptr{nullptr},
                                      m_size{0},
                                      m_capacity{0}
{
    MESSAGE("In MyVector()", std::cout)
}

/// Конструктор с инициализацией
template <typename T>
mcr::MyVector<T>::MyVector(size_t initial_size, const T& value) throw (std::bad_alloc): 
                                                                      m_capacity{initial_size}
{
    MESSAGE("In MyVector(size_t, const T&)", std::cout)
    try {
        m_ptr = new value_type[m_capacity];
    }
    catch(std::bad_alloc& e) {
        MESSAGE(e.what(), std::cerr)
        assert(!"ERROR: bad alloc");
        throw e;
    }
    for (m_size = 0; m_size < initial_size; ++m_size) {
        m_ptr[m_size] = value;
    }
    ASSERT_OK()
}

///Конструктор с единственным параметром
template <typename T>
mcr::MyVector<T>::MyVector(size_t initial_size)	
{
    MESSAGE("In MyVector(size_t)", std::cout)
    value_type zero_obj{value_type()};
    MyVector<value_type> new_obj(initial_size, zero_obj);
    swap(new_obj);
    ASSERT_OK()
}

///Копирующей конструктор	
template <typename T>
mcr::MyVector<T>::MyVector(const mcr::MyVector<T>& other) throw (std::bad_alloc): 
                                                    m_capacity{other.m_size}
{
    MESSAGE("In MyVector(const MyVector<T>& )", std::cout)
    try {
        m_ptr = new value_type[m_capacity];
    }
    catch(std::bad_alloc& e) {
        MESSAGE(e.what(), std::cerr)
        assert(!"ERROR: bad alloc");
        throw e;
    }
    for (m_size = 0; m_size < other.m_size; ++m_size) {
        m_ptr[m_size] = other.m_ptr[m_size];
    }
    ASSERT_OK()
}

///Конструктор с перемещением
template <typename T>
mcr::MyVector<T>::MyVector(mcr::MyVector<T>&& other) : m_ptr{nullptr},
                                                  m_size{0},
                                                  m_capacity{0}
{
    MESSAGE("In MyVector(MyVector<T>&& )", std::cout)
    swap(other);
    ASSERT_OK()
}

///Деструктор
template <typename T>
mcr::MyVector<T>::~MyVector()
{
    MESSAGE("In ~MyVector()", std::cout)
    MESSAGE(m_ptr, std::cout)
    if (m_ptr != nullptr) {
        delete [] m_ptr;
        MESSAGE("Destructor is complete!", std::cout)
    }
}

///Доступ к элементу с проверкой выхода за границу
template <typename T>
const T& mcr::MyVector<T>::at(size_t it) const throw (std::out_of_range)
{ 
    MESSAGE("In at(size) const", std::cout)
    ASSERT_OK()
    if (it >= m_size) {
        assert(!"ERROR: out of range");
        throw std::out_of_range("ERROR: out of range");
    }
    ASSERT_OK()
    return m_ptr[it];
}

///Доступ к элементу с проверкой выхода за границу
template <typename T>
T& mcr::MyVector<T>::at(size_t it)  throw (std::out_of_range)
{
    MESSAGE("In at(size)", std::cout)
    ASSERT_OK()
    if (it >= m_size) {
        assert(!"ERROR: out of range");
        throw std::out_of_range("ERROR: out of range");
    }
    ASSERT_OK()
    return m_ptr[it];
}

///Доступ к первому элементу для константного объекта
template <typename T>
const T& mcr::MyVector<T>::front() const throw (std::range_error)
{
    MESSAGE("In front() const", std::cout)
    ASSERT_OK()
    if (m_size == 0) {
        assert(!"Error: Vector is epmty!!!");
        throw std::range_error( "Error: Vector is epmty!!" );
    }
    ASSERT_OK()
    return m_ptr[0];
}

///Доступ к первому элементу для не константного объекта
template <typename T>
T& mcr::MyVector<T>::front() throw (std::range_error)
{
    MESSAGE("In front()", std::cout)
    ASSERT_OK()
    if (m_size == 0) {
        assert(!"Error: Vector is epmty!!!");
        throw std::range_error( "Error: Vector is epmty!!" );
    }
    ASSERT_OK()
    return m_ptr[0];
}

///Удаление верхнего элемента
template <typename T>
void mcr::MyVector<T>::pop_back() throw (std::range_error)
{
    MESSAGE("In pop_back()", std::cout)
    ASSERT_OK()
    if (m_size == 0) {
        assert(!"Error: Vector is epmty!!!");
        throw std::range_error( "Error: Vector is epmty!!" );
    }
    m_ptr[--m_size] = value_type();   
    ASSERT_OK()
}

///Добавление элемента с копированием
template <typename T>
void mcr::MyVector<T>::push_back(const T& value)
{
    MESSAGE("In push_back(const T&)", std::cout)
    ASSERT_OK()
    if (m_size == m_capacity)
        reserve(m_size * 2);

    m_ptr[m_size++] = value;
    ASSERT_OK()
}

///Добавит элемент с перемещением 
template <typename T>
void mcr::MyVector<T>::push_back(T&& value)
{
    MESSAGE("In push_back(T&&)", std::cout)
    ASSERT_OK()
    if (m_size == m_capacity)
        reserve(m_size * 2);

    m_ptr[m_size++] = value;
    ASSERT_OK()
}


///Копирование содержимого 
template <typename T>
void mcr::MyVector<T>::copy(mcr::MyVector<T> other) 
{
    MESSAGE("copy( MyVector<T>)", std::cout)
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
}

///Количество элементов вектора	
template <typename T>
size_t mcr::MyVector<T>::size() const
{
    MESSAGE("size()", std::cout)
    ASSERT_OK()
    return m_size;
}

///Проверка на наличия элементов
template <typename T>
bool mcr::MyVector<T>::empty() const
{
    MESSAGE("empty()", std::cout)
    ASSERT_OK()
    return m_size == 0;
}

///Доступ к верхнему элементу для константного объекта
template <typename T>
const T&  mcr::MyVector<T>::back() const throw (std::range_error)
{
    MESSAGE("back() const", std::cout)
    ASSERT_OK()
    if (m_size == 0) {
        assert(!"Error: Vector is epmty!!!");
        throw std::range_error( "Error: Vector is epmty!!" );
    }
    return m_ptr[m_size - 1];
}

///Доступ к Верхнему элементу для не константного объекта
template <typename T>
T& mcr::MyVector<T>::back() throw (std::range_error)
{
    MESSAGE("back()", std::cout)
    ASSERT_OK()
    if (m_size == 0) {
        assert(!"Error: Vector is epmty!!!");
        throw std::range_error( "Error: Vector is epmty!!" );
    }
    return m_ptr[m_size - 1];
}

///Вывод структуры вектора на экран
template <typename T>
void mcr::MyVector<T>::show_v() const 
{
    MESSAGE("show_v()", std::cout)
    std::cout << "MyVector\n\t{\n";
    std::cout << "\tКоличество элементов: " << m_size << "\n";
    std::cout << "\tОбъем памяти выделенной под вектор: " << m_capacity << "\n";
    std::cout << "\tMyVector[" << m_size << "]:\n\t\t{\n";

    for (size_type i = 0; i < m_size; ++i) 
        std::cout << "\t\t[" << i << "] = " << m_ptr[i] << "\n";

        std::cout << "\t\t}\n\t}" << std::endl;
}

///Верификатор
template <typename T>
bool mcr::MyVector<T>::v_ok() const
{
    MESSAGE("v_ok()", std::cout)
    if (m_size > m_capacity)
        return false;
    return true;
} 
///Дампер
template <typename T>
inline void mcr::MyVector<T>::dump(const char* file_name, int line ,const char* func_name) const
{

    std::cerr << " FILE: " << file_name << "\n";
    std::cerr <<  " ERROR: LINE: " << line << "\n";
    std::cerr << " FUNCTION: " << func_name << "\n";

    show_v();
}

/// Устанавливает минимально возможное количество элементов в векторе
template <typename T>
void mcr::MyVector<T>::reserve(size_t new_capacity) throw (std::length_error, std::bad_alloc)
{
    MESSAGE("reserve(size_t)", std::cout)
    ASSERT_OK()
    if (new_capacity > m_capacity) {
        if (new_capacity > max_size()) {
            assert(!"ERROR: Length error");
            throw std::length_error("ERROR: Length error");
        }
        value_type* old_ptr = m_ptr;
        m_capacity = new_capacity;
        try {
            m_ptr = new value_type[m_capacity];
        }
        catch(std::bad_alloc& e) {
            assert(!"ERROR: bad alloc");
            throw e;
        }        
        for (size_type i = 0; i < m_size; i++) {
            m_ptr[i] = old_ptr[i];
        }
        delete [] old_ptr;	
    }
    ASSERT_OK()
} 

///Максимально допустимое количество элементов
template <typename T>
size_t mcr::MyVector<T>::max_size() const
{
    MESSAGE("max_size(size_t)", std::cout)
    ASSERT_OK()
    size_t max_size =  size_t(pow (2, (sizeof(size_t) * 8) - 1)) - 1;
    max_size = (max_size * 2 + 1)/sizeof(value_type);
    ASSERT_OK()
    return max_size;
}


///Изменение размера вектора на заданную величину,
template <typename T>  
void mcr::MyVector<T>::resize(size_t new_size, const T& value)
{
    MESSAGE("resize(size_t, const T&)", std::cout)
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
void mcr::MyVector<T>::resize(size_t new_size)
{
     MESSAGE("resize(size_t)", std::cout)
     ASSERT_OK()
     value_type temp_value{value_type()};
     resize(new_size, temp_value);
     ASSERT_OK()
}

///Возвращает указатель на базовый массив
template <typename T> 
T* mcr::MyVector<T>::data()
{
    MESSAGE("data()", std::cout)
    ASSERT_OK()
    return m_ptr;   
}

///Возвращает указатель на базовый массив
template <typename T> 
const T* mcr::MyVector<T>::data() const
{
    MESSAGE("data() const", std::cout)
    ASSERT_OK()
    return m_ptr;   
}

///Возвращает количество элементов, которое может содержать вектор
template <typename T>
size_t mcr::MyVector<T>::capacity() const
{
    MESSAGE("data()", std::cout)
    ASSERT_OK()
    return m_capacity;   
}

///Обменять содержимое двух векторов
template <typename T>
void mcr::MyVector<T>::swap(mcr::MyVector<T>& other )
{
    MESSAGE("swap()", std::cout)
    ASSERT_OK()
    size_t temp_size = m_size;
    size_t temp_capacity = m_capacity;
    value_type* temp_ptr = m_ptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_ptr = other.m_ptr;
    other.m_size = temp_size;
    other.m_capacity = temp_capacity;
    other.m_ptr = temp_ptr;
}

///Удаляет все элементы вектора
template <typename T>
void mcr::MyVector<T>::clear()
{
    MESSAGE("clear()", std::cout)
    ASSERT_OK()
    m_size = 0;
}

///Уменьшает количество используемой памяти
template <typename T>
void mcr::MyVector<T>::shrink_to_fit() throw (std::bad_alloc)
{
    MESSAGE("shrink_to_fit()", std::cout)
    ASSERT_OK()
    value_type* old_ptr = m_ptr;
    if (new (this) MyVector<T>(*this) != this) {
        assert(!"Problem with shrink_to_fit()");
        throw std::bad_alloc();
    }
    delete [] old_ptr;
    ASSERT_OK()   
}





