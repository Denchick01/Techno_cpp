/*!

	\file

	\brief Заголовочный файл с описание класса MyStack

	\author Трощенков Денис

	\data 27.02.2017

	В данном классе реализуется механизм хранения данных типа FILO

*/

#include <iostream>
#include <cassert>

#define DEBUG_SET 1; 
#define MESSAGE(str) \
	std::cerr << "file: " << __FILE__ << "line: " << __LINE__ << str << std::endl;

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
	~MyStack					///< Деструктор
	

	inline void pop();				///< Удаление верхнего элемента
	inline void push( const value_type& );		///< Добавление элемента
	void swap( const MyStack<value_type>& );	///< Копирование содержимого
	size_type size() const;				///< Количество элементов стека
	bool empty() const;				///< Проверка наличия элементов
	inline const_referens top() const; 		///< Доступ к Верхнему элементу для константного объекта
	inline referens top();				///< Доступ к Верхнему элементу для не константного объекта
	const_referens take_any( size_type ) const;	///< Взятие произвольного элемента стека для константного объекта
	referens take_any( size_type );			///< Взятие произвольного элемента стека для не константного объекта

private:
	size_type m_stk_size;				///< Размер стека
	size_type m_stk_top;				///< Индекс на позицию за последним элементом
	value_type* m_stk_ptr;				///< Указатель на стек
	inline bool stk_verifier(int) const;		///< Верификатор
	inline void stk_dump( char*, int );		///< Дампер
	void resize(size_type);                         ///< Изменение размеров стека
		
}


/*! 
	\brief	Конструктор
 
	\param[in] Начальный размер стека

*/
template <typename T>
MyStack<value_type>::MyStack(size_type initial_size) :
	m_stk_size{intial_size}, m_stk_top{0} 	
{
    	m_stk_ptr = new value_type[initial_size]; 

    	#if DEBUG_SET
	stk_verifier(15);
	#endif
}

/*! 
	\brief Копирующей конструктор
	
	\param[in] объект типа  MyStack
	
	В случае вызова конструктора с параметром в виде объекта типа MyStack,
	будет произведено копирование этого объекта
*/
template <typename T>
MyStack<value_type>::MyStack(const MyStack<value_type>& other) :
	m_stk_top{other.size()}
{
	m_stk_ptr = new value_type[sizeof(other)]; 

	#if DEBUG_SET
 	stk_verifier(15);
 	#endif
	
	swap(other);

	#if DEBUG_SET
	stk_verifier(15);
	#endif
}

/*!
	\brief Деструктор

*/
template <typename T>
MyStack<value_type>::~Mystack()
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
inline void MyStack<value_type>::pop()
{
	#if DEBUG_SET
 	stk_verifier(15);
 	#endif

	if (m_stk_size > (m_stk_top * 4))
		resize(m_stk_top * 2);

	m_stk_ptr[--m_stk_top] = 0;

	#if DEBUG_SET
	stk_verifier(15);
	#endif
}
/*!
	\brief Добавление элемента

	\param[in] Новый элемент стека	
*/
template <typename T>
inline void MyStack<value_type>::push(const value_type& value)
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif
	
	if (m_stk_top == m_stk_size)
		resize(m_stk_size * 2);

	m_stk_ptr[m_stk_top++] = value;

	#if DEBUG_SET
	stk_verifier(15);
	#endif				
}
/*! 
	\brief Копирование содержимого 

	\param[in] объект типа  MyStack
*/
template <typename T>
void MyStack<value_type>::swap( const MyStack<value_type>& other) 
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif

	if (m_stk_size < other.size())
		resize(other.size() * 2);
	else if (m_stk_size > (other.size() * 2))
		resize(other.size() * 2);

	m_stk_top = other.size();

	for (size_type i = 0; i < m_stk_top; i++)
		m_stk_ptr[i] = other.take_any(i);

	#if DEBUG_SET
	stk_verifier(15);
	#endif
}
/*!
	\brief	 Количество элементов стека	

	\return Размер стека
*/
template <typename T>
size_type MyStack<value_type>::size() const
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif

	return m_stk_top;
}
/*!
	\brief Проверка наличия элементов

	\return True if size > 0 else false
*/
template <typename T>
bool MyStack<value_type>::empty() const
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif

	return m_stk_top > 0;
}
/*!
	\brief Доступ к Верхнему элементу для константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline const_referens MyStack<value_type>::top() const
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif            

	return &m_stk_ptr[m_stk_top - 1];
}

/*!
	\brief Доступ к Верхнему элементу для не константного объекта

	\return Ссылка на верхний последний элемент
*/
template <typename T>
inline referens MyStack<value_type>::top()
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif            

	return &m_stk_ptr[m_stk_top - 1];
}
/*! 
	\brief Взятие произвольного элемента стека для константного объекта
	
	\return Ссылка на объект
*/
template <typename T>
const_referens MyStack<value_type>::take_any(size_type it) const
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif

	return &m_stk_ptr[it];
}
/*! 
	\brief Взятие произвольного элемента стека для не константного объекта
	
	\return Ссылка на объект
*/
template <typename T>
referens MyStack<value_type>::take_any(size_type it)
{
	#if DEBUG_SET
	stk_verifier(15);
	#endif

	return &m_stk_ptr[it];
}





