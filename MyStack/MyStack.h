/*!

	\file

	\brief Заголовочный файл с описание класса MyStack

	\author Трощенков Денис

	\data 27.02.2017

	В данном классе реализуется механизм хранения данных типа FILO

*/

#include <iostream>
#include <cassert>

#define NULL_PTR 1
#define OVER_SIZE 2
#define NEGATIVE_SIZE 4
#define MESSAGE(str) \
	std::cerr << "file: " << __FILE__ << " line: " << __LINE__ << "  "<<str << std::endl;

///Класс MyStack
template <typename T>	
class MyStack
{
public:
	typedef size_t size_type;
	typedef T value_type;
	typedef T& referens;
	typedef const T& const_referens; 	

	MyStack(size_type = 15); 			///< Дефолтный конструктор класса MyStack
	MyStack( const MyStack<value_type>& );		///< Копирующей конструктор
	~MyStack();					///< Деструктор
	

	inline void pop();				///< Удаление верхнего элемента
	inline void push( const value_type& );		///< Добавление элемента
	void swap( const MyStack<value_type>& );	///< Копирование содержимого
	size_type size() const;				///< Количество элементов стека
	bool empty() const;				///< Проверка наличия элементов
	inline const_referens top() const; 		///< Доступ к Верхнему элементу для константного объекта
	inline referens top();				///< Доступ к Верхнему элементу для не константного объекта
	const_referens take_any( size_type ) const;	///< Взятие произвольного элемента стека для константного объекта
	referens take_any( size_type );			///< Взятие произвольного элемента стека для не константного объекта
	void show_stk() const;				///< Вывод структуры стека на экран

private:
	size_type m_stk_size;				///< Размер стека
	size_type m_stk_top;				///< Индекс на позицию за последним элементом
	value_type* m_stk_ptr;				///< Указатель на стек
	inline void stk_verifier(int, const char*, int) const;	///< Верификатор
	inline void stk_dump(const char*, int, int) const; ///< Дампер
	void resize(size_type);                         ///< Изменение размеров стека
		
};


/*! 
	\brief	Конструктор
 
	\param[in] Начальный размер стека

*/
template <typename T>
MyStack<T>::MyStack(size_t initial_size) :
	m_stk_size{initial_size}, m_stk_top{0} 	
{
    	m_stk_ptr = new value_type[initial_size]; 

    	#if DEBUG_SET
	stk_verifier(NULL_PTR, "C_MyStack", __LINE__);
	#endif
}

/*! 
	\brief Копирующей конструктор
	
	\param[in] объект типа  MyStack
	
	В случае вызова конструктора с параметром в виде объекта типа MyStack,
	будет произведено копирование этого объекта
*/
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& other) :
	m_stk_top{other.size()}
{
	m_stk_ptr = new value_type[sizeof(other)]; 

	#if DEBUG_SET
 	stk_verifier(NULL_PTR, "CC_MyStack", __LINE__);
 	#endif
	
	swap(other);

	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "D_MyStack", __LINE__);
	#endif
}

/*!
	\brief Деструктор

*/
template <typename T>
MyStack<T>::~MyStack()
{
	delete [] m_stk_ptr;

	#if DEBUG_SET
	MESSAGE("Destructor is complete!")
	#endif
}

/*!
	\brief Удаление верхнего элемента
*/
template <typename T>
inline void MyStack<T>::pop()
{
	#if DEBUG_SET
 	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "pop", __LINE__);
 	#endif

	if (m_stk_top == 0)
		assert(!"stack is empty!!!");

	if (m_stk_size > (m_stk_top * 4))
		resize(m_stk_top * 2);
	
	m_stk_ptr[--m_stk_top] = 0;

	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "pop", __LINE__);
	#endif
}
/*!
	\brief Добавление элемента

	\param[in] Новый элемент стека	
*/
template <typename T>
inline void MyStack<T>::push(const T& value)
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "push", __LINE__);
	#endif
	
	if (m_stk_top == m_stk_size)
		resize(m_stk_size * 2);

	m_stk_ptr[m_stk_top++] = value;

	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "push", __LINE__);
	#endif				
}
/*! 
	\brief Копирование содержимого 

	\param[in] объект типа  MyStack
*/
template <typename T>
void MyStack<T>::swap( const MyStack<T>& other) 
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "swap", __LINE__);
	#endif

	if (m_stk_size < other.size())
		resize(other.size() * 2);
	else if (m_stk_size > (other.size() * 2))
		resize(other.size() * 2);

	m_stk_top = other.size();

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = other.take_any(i);

	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "swap", __LINE__);
	#endif
}
/*!
	\brief	 Количество элементов стека	

	\return Размер стека
*/
template <typename T>
size_t MyStack<T>::size() const
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "size", __LINE__);
	#endif

	return m_stk_top;
}
/*!
	\brief Проверка наличия элементов

	\return True if size > 0 else false
*/
template <typename T>
bool MyStack<T>::empty() const
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "empty", __LINE__);
	#endif

	return !(m_stk_top > 0);
}
/*!
	\brief Доступ к Верхнему элементу для константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline const T&  MyStack<T>::top() const
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "top", __LINE__);
	#endif            

	return m_stk_ptr[m_stk_top - 1];
}

/*!
	\brief Доступ к Верхнему элементу для не константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline T& MyStack<T>::top()
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "top", __LINE__);
	#endif            

	return m_stk_ptr[m_stk_top - 1];
}
/*! 
	\brief Взятие произвольного элемента стека для константного объекта

	\param[in] Индекс элемента
	
	\return Ссылка на объект
*/
template <typename T>
const T& MyStack<T>::take_any(size_t it) const
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "take_any", __LINE__);
	#endif

	return m_stk_ptr[it];
}
/*! 
	\brief Взятие произвольного элемента стека для не константного объекта

	\param[in] Индекс элемента	
	
	\return Ссылка на объект
*/
template <typename T>
T& MyStack<T>::take_any(size_t it)
{
	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "take_any", __LINE__);
	#endif

	return m_stk_ptr[it];
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

	\param[in] flags В качестве входного параметра выступает целочисленное значение,
		которое в битовом представление является набором флагов, сигнализирующих 
		о необходимости верификации определенных состояний стека, в частности
		бит 0 = 1 - проверка указателя стека на NULL
		бит 1 = 1 - проверка на выход стека за выделенную область памяти
		бит 2 = 1 - проверка на отрицательный индекс

	\param[in] func_name Имя функции, которая вызвала верификатор 

	\param[in] line номер строки, которая вызвала верификатор

*/
template <typename T>
inline void MyStack<T>::stk_verifier(int flags, const char* func_name, int line) const
{
	if (flags & NULL_PTR) {	
		if (m_stk_ptr == NULL) {
			stk_dump(func_name, NULL_PTR, line);	
			assert(!"null pointer");
		}
	}		
	if (flags & OVER_SIZE) {
		if (m_stk_top > m_stk_size) {
			stk_dump(func_name, OVER_SIZE, line);
			assert(!"over size");
		}
	}
	if (flags & NEGATIVE_SIZE) {
		if (m_stk_top < 0) {
			stk_dump(func_name, OVER_SIZE, line);
			assert(!"negative size");
		}
	}
} 
/*!
	\brief Дампер
	
	\param[in] func_name Имя функции, которая вызвала верификатор

	\param[in] err_f Номер ошибки

	\param[in] line номер строки, которая вызвала верификатор
*/
template <typename T>
inline void MyStack<T>::stk_dump(const char* func_name, int err_f , int line) const
{

	std::cerr << " FILE: " << __FILE__ ;
	std::cerr <<  " ERROR: LINE: " << line;
	std::cerr << " FUNCTION: " << func_name << "\n";

	switch (err_f) {
		case NULL_PTR:
		std::cerr << " m_stk_ptr == NULL\n";
		break;
		case OVER_SIZE:
		std::cerr << " m_stk_top > m_stk_size\n";
		break;
		case NEGATIVE_SIZE:
		std::cerr << " m_stk_top < 0\n";
		break;
	}

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

	m_stk_ptr = new value_type[new_size];
	
	#if DEBUG_SET
	stk_verifier(NULL_PTR, "resize", __LINE__);
	#endif

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = old_stk_ptr[i];
	
	delete [] old_stk_ptr;	

	#if DEBUG_SET
	stk_verifier(NULL_PTR | OVER_SIZE | NEGATIVE_SIZE, "resize", __LINE__);
	#endif
}

