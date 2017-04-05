/*!

	\file

	\brief Заголовочный файл с описание класса MyStack

	\author Трощенков Денис

	\data 27.02.2017

	В данном классе реализуется механизм хранения данных типа FILO

*/
#include <new>
#include <iostream>
#include <cassert>

#if DEBUG_SET
	#define MESSAGE(str, stream) \
		stream << "file: " << __FILE__ << " line: " << __LINE__ << "  "<< str << std::endl;
	#define ASSERT_OK(func_name) 				\
		if (!v_ok()) {					\
			stk_dump(__FILE__, __LINE__, func_name);\
			assert(!"Object is OK"); 		\
		}
#else
	#define ASSERT_OK(func_name) 
	#define MESSAGE(str, stream)
#endif


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

 	MyStack& operator = (const MyStack& ); 		///< Оператор присваивания
	
	inline void pop();				///< Удаление верхнего элемента
	inline void push( const value_type& );		///< Добавление элемента
	void copy( const MyStack<value_type>& );	///< Копирование содержимого
	size_type size() const;				///< Количество элементов стека
	bool empty() const;				///< Проверка наличия элементов
	inline const_referens top() const; 		///< Доступ к Верхнему элементу для константного объекта
	inline referens top();				///< Доступ к Верхнему элементу для не константного объекта
	void resize(size_type);                         ///< Изменение размеров стека
	void show_stk() const;				///< Вывод структуры стека на экран
private:
	size_type m_stk_size;                           ///< Размер стека
	size_type m_stk_top;				///< Индекс на позицию за последним элементом
	value_type* m_stk_ptr;				///< Указатель на стек
	bool v_ok() const;				///< Верификатор
	inline void stk_dump(const char*, int, const char*) const; ///< Дампер
		
};

#include "MyStack.hpp"
