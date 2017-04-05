/*!
*    @file
*
*    @brief Файл с описанием методов MyStack
*
*    @author Трощенков Денис
*
*    @data 27.02.2017
*
*    Реализация методов класса MyStack
*/

namespace mcr {


///Вывод структуры стека в output
template <typename T> 
inline void MyStack<T>::show_v(std::ostream &output) const
{
    MESSAGE("IN")
    output << "MyStack\n\t{\n";
    output << "\tAmount of elements: " << m_size << "\n";
    output << "\tSize of allocated memory: " << m_capacity << "\n";
    output << "\tMyStack[" << m_size << "]:\n\t\t{\n";

    show_this.show(output, *this);
}


///Оператор присваивания с копированием
template <typename T>
MyStack<T>& MyStack<T>::operator = (const MyStack<T>& other) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (this == &other) { 
        return *this;	
    }

    this->~MyStack();
    if (new (this) MyStack<T>(other) != this) {
        throw MyException(BAD_ALLOC, "error new",std::vector<MyException>(), SIMPLE_LINE);
    }
    ASSERT_OK()
    return *this;    
}	

///Оператор присваивания с перемещение
template <typename T>
MyStack<T>& MyStack<T>::operator = (MyStack<T>&& other) throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
    return *this;    
}

///Оператор сравнения
template <typename T>
bool  MyStack<T>::operator == (const MyStack<T>& rhs) const 
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
bool  MyStack<T>::operator != (const MyStack<T>& rhs) const
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
MyStack<T>::MyStack() :  m_capacity{0},
                         m_size{0},
                         m_ptr{nullptr}
{
    MESSAGE("IN")
}

/// Конструктор с инициализацией
template <typename T>
MyStack<T>::MyStack(size_t initial_size, const T& value) throw (MyException): 
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
MyStack<T>::MyStack(size_t initial_size)	: m_capacity{0},
                                                  m_size{0},
                                                  m_ptr{nullptr}
{
    MESSAGE("IN")  
    value_type zero_obj{value_type()};
    MyStack<value_type> new_obj(initial_size, zero_obj);
    swap(new_obj);
    ASSERT_OK()
}

///Копирующей конструктор	
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& other) throw (MyException): 
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
MyStack<T>::MyStack(MyStack<T>&& other) : m_capacity{0},
                                          m_size{0},
                                          m_ptr{nullptr}
{
    MESSAGE("IN")
    swap(other);
    ASSERT_OK()
}

///Деструктор
template <typename T>
MyStack<T>::~MyStack()
{
    MESSAGE("IN")
    MESSAGE(m_ptr)
    delete [] m_ptr;
    MESSAGE("Destructor is complete!")
}

///Удаление верхнего элемента
template <typename T>
void MyStack<T>::pop() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Stack is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    m_ptr[--m_size] = value_type();   
    ASSERT_OK()
}

///Добавление элемента с копированием
template <typename T>
void MyStack<T>::push(const T& value)
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
void MyStack<T>::push(T&& value)
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
void MyStack<T>::copy(mcr::MyStack<T> other) 
{
    MESSAGE("IN")
    ASSERT_OK()
    swap(other);
    ASSERT_OK()
}

///Количество элементов стеке
template <typename T>
size_t MyStack<T>::size() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_size;
}

///Проверка на наличия элементов
template <typename T>
bool MyStack<T>::empty() const
{
    MESSAGE("IN")
    ASSERT_OK()
    return m_size == 0;
}

///Доступ к верхнему элементу для константного объекта
template <typename T>
const T&  MyStack<T>::top() const throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Stack is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[m_size - 1];
}

///Доступ к Верхнему элементу для не константного объекта
template <typename T>
T& MyStack<T>::top() throw (MyException)
{
    MESSAGE("IN")
    ASSERT_OK()
    if (m_size == 0) {
        throw MyException(OUT_RANGE, "Error: Stack is epmty!!", std::vector<MyException>(), SIMPLE_LINE);
    }
    return m_ptr[m_size - 1];
}

///Верификатор
template <typename T>
bool MyStack<T>::v_ok() const
{
    MESSAGE("IN")
    if (m_size > m_capacity)
        return false;
    return true;
}
 
///Дампер
template <typename T>
inline void MyStack<T>::dump(const char* file_name, int line , const char* func_name, std::ostream& output) const
{

    m_logg.get_log(output);
 
    output << " FILE: " << file_name << "\n";
    output <<  " ERROR: LINE: " << line << "\n";
    output << " FUNCTION: " << func_name << "\n";

    show_v(output);
}


/// Устанавливает минимально возможное количество элементов в стеке
template <typename T>
void MyStack<T>::reserve(size_t new_capacity) throw (MyException)
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
size_t MyStack<T>::max_size() const
{
    MESSAGE("IN")
    ASSERT_OK()
    size_t max_size =  size_t(pow (2, (sizeof(size_t) * 8) - 1)) - 1;
    max_size = (max_size * 2 + 1)/sizeof(value_type);
    ASSERT_OK()
    return max_size;
}


///Обменять содержимое двух стеков
template <typename T>
void MyStack<T>::swap(mcr::MyStack<T>& other )
{
    MESSAGE("IN")
    ASSERT_OK()

    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_ptr, other.m_ptr);

    ASSERT_OK()
}	

}
