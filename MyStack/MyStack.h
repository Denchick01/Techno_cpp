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

#include "MyStack.hpp"
