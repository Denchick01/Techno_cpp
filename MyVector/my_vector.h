/*!
*   @file
*
*   @brief Заголовочный файл с описание класса MyVector
*
*   @author Трощенков Денис
*
*   @data 27.02.2017
*
*   Реализация динамического массива
*/

#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__

#include <malloc.h>
#include <type_traits>
#include <initializer_list>
#include <new>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cmath>
#include "my_iterator.h"
#include "my_macro.h"
#include "logger.hpp"
#include <sstream>
#include <fstream>
#include "my_exception.hpp"

/*!
*   @brief Класс MyVector
*/
namespace mcr {
template <typename T>	
class MyVector
{
public:
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference; 	
    typedef const T* const_pointer;
    typedef T* pointer;

    typedef const MyIterator<const value_type> const_iterator;
    typedef MyIterator<value_type> iterator;
    
    /*!
    *   @brief Возвращает итератор на первый элемент 
    */
    iterator begin();
    /*!
    *   @brief 	Возвращает итератор на элемент, следующий за последним 
    */
    iterator end();
    /*!
    *   @brief Возвращает итератор на первый элемент 
    */ 
    const_iterator begin() const;
    /*!
    *   @brief 	Возвращает итератор на элемент, следующий за последним 
    */
    const_iterator end() const;
    /*! 
    *   @brief  Конструктор по умолчанию. Создает пустой контейнер.        
    *
    *   @param[in] Начальный размер вектора
    */
    MyVector();
    /*! 
    *   @brief  Конструктор с одним параметром                             
    *
    *   @param[in] Начальный размер вектора
    */
    explicit MyVector(size_type);
    /*! 
    *   @brief  Конструктор с инициализацией                               
    *
    *   @param[in] Начальный размер вектора
    */
    MyVector(size_type, const value_type&) throw (MyException);                       
    /*! 
    *   @brief Копирующей конструктор                                      
    *    
    *   @param[in] объект типа  MyVector
    *    
    */				
    MyVector( const MyVector<value_type>& ) throw (MyException);
    /*! 
    *   @brief Конструктор с перемещением                                   
    *    
    *   @param[in] объект типа  MyVector
    *    
    */	
    MyVector( MyVector<value_type>&& );	
    /*!
    *   @brief Деструктор                                                   
    */                         						
    ~MyVector();					                								
    /*!
    *   @brief Оператор присваивания с копированием 
    */
    MyVector<value_type>& operator = (const MyVector<value_type>& ) throw (MyException);
    /*!
    *   @brief Оператор присваивания с перемещением 
    */
    MyVector<value_type>& operator = (MyVector<value_type>&& ) throw (MyException);
    /*!
    *   @brief Предоставление доступа к указанному элементу для не константного 
    *           объекта
    */ 	                                                                         
    reference operator [] (size_type);
    /*!
    *   @brief Предоставление доступа к указанному элементу для константного 
    *           объекта
    */ 	                                                                         
    const_reference operator [] (size_type) const;
    /*!
    *   @brief Оператор сравнения  
    */		                           			       	
    bool operator == (const MyVector<value_type>&) const;  
    /*!
    *   @brief Оператор неравенства 
    */		                           			       	
    bool operator != (const MyVector<value_type>&) const;   
    /*! 
    *   @brief Взятие произвольного элемента вектора для константного объекта                 
    *   @param[in] Индекс элемента
    *    
    *   @return Ссылка на объект
    */
    const_reference at(size_type) const throw (MyException);
    /*! 
    *   @brief Взятие произвольного элемента вектора для не константного объекта               
    *   @param[in] Индекс элемента      
    *    
    *   @return Ссылка на объект
    */		                         		
    reference at(size_type) throw (MyException);
    /*!
    *   @brief Удаление верхнего элемента                                                    
    */				 		
    void pop_back() throw (MyException);	
    /*!
    *   @brief Добавление элемента с копированием
    *   @param[in] Новый элемент вектора        
    */			                  							
    void push_back( const value_type& );
    /*!
    *   @brief Добавление элемента с перемещением
    *   @param[in] Новый элемент вектора        
    */	
    void push_back( T&& value );
    /*! 
    *   @brief Копирование содержимого 
    *   @param[in] объект типа  MyVector
    */	                         							
    void copy(MyVector<value_type> );
    /*!
    *   @brief   Количество элементов вектора   
    *   @return Размер вектора
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
    *   @brief Доступ к первому элементу для константного объекта
    *   @return Ссылка на первый элемент
    */
    const_reference front() const throw (MyException);
    /*!
    *   @brief Доступ к первому элементу для не константного объекта
    *   @return Ссылка на первый элемент
    */                                  
    reference front() throw (MyException); 
    /*!
    *   @brief Доступ к Верхнему элементу для константного объекта
    *   @return Ссылка на верхний последний элемент
    */                                            
    const_reference back() const throw (MyException);
    /*!
    *   @brief Доступ к Верхнему элементу для не константного объекта
    *   @return Ссылка на верхний последний элемент
    */ 		                  			
    reference back() throw (MyException);
    /*!
    *   @brief Возвращает указатель на базовый массив, выступающей 
    *     в качестве элемента хранения для не константного объекта
    */
    pointer data();
    /*!
    *   @brief Возвращает указатель на базовый массив, выступающей 
    *     в качестве элемента хранения для константного объекта
    */
    const_pointer data() const;				                  
    /*!
    *   @brief Устанавливает минимально возможное количество элементов в векторе
    *   @param[in] Новый размер вектора
    */			
    void reserve(size_type) throw (MyException);  
    /*!
    *    @brief Возвращает количество элементов, которое может содержать вектор до того, 
    *           как ему потребуется выделить больше места.
    */
    size_type capacity() const;
    /*!
    *    @brief Уменьшает количество используемой памяти за счет освобождения неиспользованной
    */
    void shrink_to_fit() throw (MyException);
    /*!
    *    @brief Изменяет размер вектора на заданную величину
    */
    void resize( size_type count ) throw (MyException);
    /*!
    *    @brief Изменение размера вектора на заданную величину,
    *           с инициализацией 
    */
    void resize( size_type count, const value_type& value) throw (MyException);
    /*!
    *    @brief Вставляет элементы в указанную позицию в контейнере с перемещением
    */
    iterator insert(const_iterator, T&&) throw (MyException);
    /*!
    *    @brief Вставляет элементы в указанную позицию в контейнере с копированием
    */
    iterator insert(iterator, const value_type&) throw (MyException);
    /*!
    *    @brief Вставляет элементы в указанную позицию в контейнере.
    */
    iterator insert(iterator, size_type, const value_type&) throw (MyException);
    /*!
    *    @brief Вставляет элементы в указанную позицию в контейнере.
    */
    template< class InputIt, typename G = typename
                             std::enable_if<std::is_convertible<typename
		             std::iterator_traits<InputIt>::iterator_category,
			     std::input_iterator_tag>::value>::type>
    iterator insert(iterator, InputIt, InputIt) throw (MyException);
    /*!
    *    @brief Вставляет элементы в указанную позицию в контейнере.
    */
    iterator insert(iterator, std::initializer_list<T>);
    /*!
    *    @brief Удаляет элемент в позиции pos
    */
    iterator erase(iterator) throw (MyException);
    /*!
    *    @brief Удаляет элемент в диапазоне [first; last)
    */
    iterator erase(iterator, iterator) throw (MyException);
    /*!
    *   @brief Удаляет все элементы вектора
    */
    void clear();
    /*!
    *   @brief Обменять содержимое двух векторов
    */
    void swap(MyVector<value_type>& );                                            	
    /*!
    *   @brief Вывод структуру вектора на экран
    */	
    inline void show_v(std::ostream &output) const;
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
        void show (std::ostream &output, const MyVector<T>& that) const {
            for (size_type i = 0; i < that.m_size; ++i) 
            output << "\t\t[" << i << "] = " << that.m_ptr[i] << "\n";

            output << "\t\t}\n\t}\n";
          }
    };
   
    template <class V>
    struct check_streamable <V, false>
    {
        void show (std::ostream &output, const MyVector<T>& that) const {
            output << "I can not display the vector structure for this type\n";
        }
    };

    friend check_streamable<T>;   

    check_streamable<T> show_this;

};
}
#include "my_vector.hpp"

#endif
