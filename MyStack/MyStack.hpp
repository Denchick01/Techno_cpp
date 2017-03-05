/*!

	\file

	\brief Файл с описанием методов MyStack

	\author Трощенков Денис

	\data 27.02.2017

	В данном классе реализуется механизм хранения данных типа FILO

*/

/*! 
	\brief	Конструктор
 
	\param[in] Начальный размер стека

*/
template <typename T>
MyStack<T>::MyStack(size_t initial_size) :
	m_stk_size{initial_size}, m_stk_top{0} 	
{
	ASSERT_OK("MyStack()")
	try {  
		m_stk_ptr = new value_type[initial_size];
   	}  
   	catch(std::bad_alloc& e) {  
		MESSAGE(e.what(), std::cerr)
   	}    
	ASSERT_OK("MyStack()")
}

/*! 
	\brief Копирующей конструктор
	
	\param[in] объект типа  MyStack
	
	В случае вызова конструктора с параметром в виде объекта типа MyStack,
	будет произведено копирование этого объекта
*/
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& other) :
	m_stk_top{other.m_stk_top}, m_stk_size{other.m_stk_size}
{
	ASSERT_OK("MyStack()")
	try {
		m_stk_ptr = new value_type[sizeof(other.m_stk_size)]; 
	}
	catch (std::bad_alloc& e) {
		MESSAGE(e.what(), std::cerr)
	}
	swap(other);
	ASSERT_OK("MyStack()")

}

/*!
	\brief Деструктор

*/
template <typename T>
MyStack<T>::~MyStack()
{
	delete [] m_stk_ptr;
	MESSAGE("Destructor is complete!", std::cout)
}

/*!
	\brief Удаление верхнего элемента
*/
template <typename T>
inline void MyStack<T>::pop()
{

	ASSERT_OK("pop()")
	try {
		if (m_stk_top == 0)
			throw "Error: Stack is epmty!!!";
	}
	catch (const char* str) {
		MESSAGE(str, std::cerr)
		assert(!"Error: Stack is epmty!!!");
	}
	m_stk_ptr[--m_stk_top] = 0;
	ASSERT_OK("pop()")
}
/*!
	\brief Добавление элемента

	\param[in] Новый элемент стека	
*/
template <typename T>
inline void MyStack<T>::push(const T& value)
{
	ASSERT_OK("push()")
	if (m_stk_top == m_stk_size)
		resize(m_stk_size * 2);

	m_stk_ptr[m_stk_top++] = value;
	ASSERT_OK("push()")
}
/*! 
	\brief Копирование содержимого 

	\param[in] объект типа  MyStack
*/
template <typename T>
void MyStack<T>::swap( const MyStack<T>& other) 
{
	ASSERT_OK("push()")
	if (m_stk_size < other.m_stk_top)
		resize(other.m_stk_top * 2);
	else if (m_stk_size > (other.m_stk_top * 2))
		resize(other.m_stk_top * 2);

	m_stk_top = other.m_stk_top;

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = other.m_stk_ptr[i];
	ASSERT_OK("push()")
}
/*!
	\brief	 Количество элементов стека	

	\return Размер стека
*/
template <typename T>
size_t MyStack<T>::size() const
{
	ASSERT_OK("size()")
	return m_stk_top;
}
/*!
	\brief Проверка наличия элементов

	\return True if size > 0 else false
*/
template <typename T>
bool MyStack<T>::empty() const
{
	ASSERT_OK("emty()")
	return m_stk_top == 0;
}
/*!
	\brief Доступ к Верхнему элементу для константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline const T&  MyStack<T>::top() const
{
	ASSERT_OK("top()")
	return m_stk_ptr[m_stk_top - 1];
}

/*!
	\brief Доступ к Верхнему элементу для не константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline T& MyStack<T>::top()
{
	ASSERT_OK("top()")
	return m_stk_ptr[m_stk_top - 1];
}
/*!
	\brief Вывод структуры стека на экран
*/
template <typename T>
void MyStack<T>::show_stk() const 
{
	std::cout << "MyStack\n\t{\n";
	std::cout << "\tКоличество элементов: " << m_stk_top << "\n";
	std::cout << "\tОбъем памяти выделенной под стек: " << m_stk_size << "\n";
	std::cout << "\tMyStack[" << m_stk_top << "]:\n\t\t{\n";

	for (size_type i = 0; i < m_stk_top; i++) 
		std::cout << "\t\t[" << i << "] = " << m_stk_ptr[i] << "\n";

	std::cout << "\t\t}\n\t}" << std::endl;
}
/*!
	\brief Верификатор
*/
template <typename T>
bool MyStack<T>::v_ok() const
{
	if (m_stk_top > m_stk_size)
		return false;
	if (m_stk_top < 0) 
		return false;
	return true;
} 
/*!
	\brief Дампер
	
	\param[in] func_name Имя функции, которая вызвала верификатор

	\param[in] file_name Имя файла

	\param[in] line номер строки, которая вызвала верификатор
*/
template <typename T>
inline void MyStack<T>::stk_dump(const char* file_name, int line ,const char* func_name) const
{

	std::cerr << " FILE: " << __FILE__ ;
	std::cerr <<  " ERROR: LINE: " << line;
	std::cerr << " FUNCTION: " << func_name << "\n";

	show_stk();
}

/*!
	\brief Изменение размеров стека

	\param[in] Новый размер стека
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
 	}
	ASSERT_OK("resize()")	

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = old_stk_ptr[i];
	
	delete [] old_stk_ptr;	
	ASSERT_OK("resize()") 
}

