/*!
*   @file
*
*   @brief Заголовочный файл с описание класса MyStack
*
*   @author Трощенков Денис
*
*   @data 27.02.2017
*
*   Реализация стека
*/


#ifndef __MY_STACK_H__
#define __MY_STACK_H__

#include <new>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cmath>
#include "my_iterator.h"
#include "my_macro.h"
#include "logger.hpp"
#include <sstream>
#include "my_exception.hpp"

/*!
*   @brief Класс MyStack
*/
namespace mcr {
template <typename T>	
class MyStack
{
public:
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference; 	
    typedef const T* const_pointer;
    typedef T* pointer;

    /*! 
    *   @brief  Конструктор по умолчанию. Создает пустой контейнер.        
    *
    *   @param[in] Начальный размер стека
    */
    MyStack();
    /*! 
    *   @brief  Конструктор с одним параметром                             
    *
    *   @param[in] Начальный размер стека
    */
    explicit MyStack(size_type);
    /*! 
    *   @brief  Конструктор с инициализацией                               
    *
    *   @param[in] Начальный размер стека
    */
    MyStack(size_type, const value_type&) throw (MyException);                       
    /*! 
    *   @brief Копирующей конструктор                                      
    *    
    *   @param[in] объект типа  MyStack
    *    
    */				
    MyStack( const MyStack<value_type>& ) throw (MyException);
    /*! 
    *   @brief Конструктор с перемещением                                   
    *    
    *   @param[in] объект типа  MyStack
    *    
    */	
    MyStack( MyStack<value_type>&& );	
    /*!
    *   @brief Деструктор                                                   
    */                         						
    ~MyStack();					                								
    /*!
    *   @brief Оператор присваивания с копированием 
    */
    MyStack<value_type>& operator = (const MyStack<value_type>& ) throw (MyException);
    /*!
    *   @brief Оператор присваивания с перемещением 
    */
    MyStack<value_type>& operator = (MyStack<value_type>&& ) throw (MyException);
    /*!
    *   @brief Оператор сравнения  
    */		                           			       	
    bool operator == (const MyStack<value_type>&) const;  
    /*!
    *   @brief Оператор неравенства 
    */		                           			       	
    bool operator != (const MyStack<value_type>&) const;  
    /*!
    *   @brief Удаление верхнего элемента                                                    
    */				 		
    void pop() throw (MyException);	
    /*!
    *   @brief Добавление элемента с копированием
    *   @param[in] Новый элемент стека        
    */			                  							
    void push( const value_type& );
    /*!
    *   @brief Добавление элемента с перемещением
    *   @param[in] Новый элемент стека  
    */	
    void push( T&& value );
    /*! 
    *   @brief Копирование содержимого 
    *   @param[in] объект типа  MyStack
    */	                         							
    void copy(MyStack<value_type> );
    /*!
    *   @brief   Количество элементов стека   
    *   @return Размер стека
    */	                         							
    size_type size() const;
    /*!
    *   @brief Проверка наличия элементов
    *   @return True if size > 0 else false
    */				                  						
    bool empty() const;				                          							
    /*!
    *   @brief Максимально допустимое количество элементов
    *   @return Максимальное количество элементов
    */	
    size_type max_size() const;
    /*!
    *   @brief Доступ к Верхнему элементу для константного объекта
    *   @return Ссылка на верхний элемент
    */                                            
    const_reference top() const throw (MyException);
    /*!
    *   @brief Доступ к Верхнему элементу для не константного объекта
    *   @return Ссылка на верхний элемент
    */ 		                  			
    reference top() throw (MyException);
    /*!
    *   @brief Обменять содержимое двух стеков
    */
    void swap(MyStack<value_type>& ); 
    /*!
    *   @brief Устанавливает минимально возможное количество элементов в стеке
    *   @param[in] Новый размер стека
    */			
    void reserve(size_type) throw (MyException);  
    /*!
    *   @brief Проверка типа на возможность вывода данных в поток или файл
    */ 
    template<typename L, typename K>
    class is_streamable
    {
        template<typename SS, typename TT>
        static auto test(int)
        -> decltype( std::declval<SS&>() << std::declval<TT>(), std::true_type() );

        template<typename, typename>
        static auto test(...) -> std::false_type;

    public:
        static const bool value = decltype(test<L,K>(0))::value;
    };
    /*!
    *   @brief Дампер
    *    
    *   @param[in] func_name Имя функции, которая вызвала верификатор
    *   @param[in] file_name Имя файла
    *   @param[in] line номер строки, которая вызвала верификатор
    */				                         							
    inline void dump(const char*, int, const char*, std::ostream&) const;
    /*!
    *   @brief Вывод структуру стека на экран
    */	
    inline void show_v(std::ostream &output) const;
    private:
    /// Количество элементов которые могут одновременно хранится в выделенной области памяти
    size_type m_capacity;
    /// Количество элементов                                                 								
    size_type m_size;
    /// Указатель на область памяти, хранящей элементы вектора				                         					
    value_type* m_ptr;
    /// Логирование 
    mutable Logger m_logg;
    /*!
    *   @brief Верификатор 			
    */	                          							
    bool v_ok() const;
    /*!
    *   @brief Проверка типа на возможность вывода данных в поток или файл
    *
    *     Как реализовать подобную проверку без класса я не разобрался, думал изначально
    *     делать частичную специализацию для метода, но как оказалось си этого не разрешает, 
    *     поэтому пришлось упаковать методы в классы для которых  частичная специализация
    *     разрешена
    */
    template <class V, bool str = is_streamable<std::stringstream, V>::value >
    struct check_streamable
    {
        void show (std::ostream &output, const MyStack<T>& that) const {
            for (size_type i = 0; i < that.m_size; ++i) 
            output << "\t\t[" << i << "] = " << that.m_ptr[i] << "\n";

            output << "\t\t}\n\t}\n";
          }
    };
   
    template <class V>
    struct check_streamable <V, false>
    {
        void show (std::ostream &output, const MyStack<T>& that) const {
            output << "I can not display the vector structure for this type\n";
        }
    };

    friend check_streamable<T>;   

    check_streamable<T> show_this;

};
}
#include "my_stack.hpp"

#endif
