/*!
	\file

	\brief Файл с описанием методов MyVector

	\author Трощенков Денис

	\data 27.02.2017

	Реализация методов класса MyVector
*/

	 
///Оператор присваивания 
template <typename T>
MyVector<T>& MyVector<T>::operator = (const MyVector& other)
{
	ASSERT_OK("operator =")
 	copy(other);
 	ASSERT_OK("operator =")
	return *this;	
}	

///Оператор произвольного доступа
template <typename T>
T& MyVector<T>::operator [] (size_type it) 
{
	ASSERT_OK("operator []")
	return m_stk_ptr[it];
}
///Оператор сравнения
template <typename T>
bool operator == (const MyVector<T>& lhs, const MyVector<T>& rhs) 
{
	ASSERT_OK("operator ==")		             
	if (lhs.m_stk_top != rhs.m_stk_top)
		return false;

	for (size_t it = 0; it < lhs.m_stk_top; it++){
		if (lhs.at(it) != rhs.at(it))
			return false;
	}
	ASSERT_OK("operator ==")	
	return true;
}

///Конструктор по умолчанию
template <typename T>
explicit mcr::MyVector<T>MyVector() : m_ptr{nullptr},
                                      m_size{0},
                                      m_capacity{0}
{
    MESSAGE("In MyVector()", std::cout)
}

/// Конструктор с инициализацией
template <typename T>
explicit mcr::MyVector<T>MyVector(size_t initial_size, const T& value) : m_capacity{initial_size}
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
explicit mcr::MyVector<T>::MyVector(size_t initial_size)	
{
    MESSAGE("In MyVector(size_t)", std::cout)
    value_type zero_obj{value_type()};
    MyVector<value_type> new_obj(initial_size, zero_obj);
    swap(new_obj);
    ASSERT_OK()
}

///Копирующей конструктор	
template <typename T>
mcr::MyVector<T>::MyVector(const MyVector<T>& other) : m_capacity{other.m_size}
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
mcr::MyVector<T>::MyVector(MyVector<T>&& other) : m_ptr{nullptr},
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
    if (m_ptr != nullptr) {
        delete [] m_stk_ptr;
        MESSAGE("Destructor is complete!", std::cout)
    }
}

///Доступ к элементу с проверкой выхода за границу
template <typename T>
const T& mcr::MyVector<T>::at(size_t it) const
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
T& mcr::MyVector<T>::at(size_t it)
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
const T& mcr::MyVector<T>::front() const
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
T& mcr::MyVector<T>::front()
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
void mcr::MyVector<T>::pop_back()
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
void mcr::MyVector<T>::copy( MyVector<T> other) 
{
    MESSAGE("copy( MyVector<T>)", std::cout)
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
}

///Количество элементов вектора	
template <typename T>
size_t MyVector<T>::size() const
{
    MESSAGE("size()", std::cout)
    ASSERT_OK()
    return m_size;
}

///Проверка на наличия элементов
template <typename T>
bool MyVector<T>::empty() const
{
    MESSAGE("empty()", std::cout)
    ASSERT_OK()
    return m_size == 0;
}

///Доступ к верхнему элементу для константного объекта
template <typename T>
const T&  MyVector<T>::back() const
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
T& MyVector<T>::back()
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
void MyVector<T>::show_v() const 
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
bool MyStack<T>::v_ok() const
{
    MESSAGE("v_ok()", std::cout)
    if (m_size > m_capacity)
        return false;
    return true;
} 
///Дампер
template <typename T>
inline void MyStack<T>::stk_dump(const char* file_name, int line ,const char* func_name) const
{

	std::cerr << " FILE: " << file_name << "\n";
	std::cerr <<  " ERROR: LINE: " << line << "\n";
	std::cerr << " FUNCTION: " << func_name << "\n";

	show_v();
}

/*!
	\brief Изменение размеров вектора
	\param[in] Новый размер вектора
*/
template <typename T>			
void MyStack<T>::resize(size_t new_size)
{
	value_type* old_stk_ptr = m_stk_ptr;
	m_stk_size = new_size;

	ASSERT_OK("resize()")
	try {
		m_stk_ptr = new value_type[new_size];
	}
	catch(std::bad_alloc& e) {
		MESSAGE(e.what(), std::cerr)
		assert(!"ERROR: bad alloc");
 	}
	ASSERT_OK("resize()")	

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = old_stk_ptr[i];
	
	delete [] old_stk_ptr;	
	ASSERT_OK("resize()") 
}
