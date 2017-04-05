/*!
*   @file
*
*   @brief Заголовочный файл с описание класса MyArray
*
*   @author Трощенков Денис
*
*   @data 27.02.2017
*
*   Реализация статического массива. Массив реализован как 
*   агрегатный тип, поэтому конструкторов, операторов присваивания 
*   и прочего нет.
*/


#ifndef __MY_ARRAY_H__
#define __MY_ARRAY_H__


#include <stdexcept>
#include <cmath>
#include "my_iterator.h"
#include "my_exception.hpp"


/*!
*   @brief Класс MyArray
*/
namespace mcr {

template <typename T, size_t N>	
struct MyArray
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
    bool operator == (const MyArray<value_type, N>&) const;  
    /*!
    *   @brief Оператор неравенства 
    */		                           			       	
    bool operator != (const MyArray<value_type, N>&) const;   
    /*! 
    *   @brief Взятие произвольного элемента массива для константного объекта                 
    *   @param[in] Индекс элемента
    *    
    *   @return Ссылка на объект
    */
    const_reference at(size_type) const throw (MyException);
    /*! 
    *   @brief Взятие произвольного элемента массива для не константного объекта               
    *   @param[in] Индекс элемента      
    *    
    *   @return Ссылка на объект
    */		                         		
    reference at(size_type) throw (MyException);
    /*!
    *   @brief   Количество элементов массива   
    *   @return Размер массива
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
    *   @brief Обменять содержимое двух массивов
    */
    void swap(MyArray<value_type, N>& );

    ///Базовый массив
    T m_ptr[N];
};
}
#include "my_array.hpp"

#endif
       

