/*!
*   @file
*
*   @brief Заголовочный файл с описание класса MyException
*
*   @author Трощенков Денис
*
*   @data 27.02.2017
*
*/

#ifndef __MY_EXCEPTION_HPP__
#define __MY_EXCEPTION_HPP__


#include <sstream>
#include <string>
#include <exception>
#include <vector>

#define BAD_ALLOC 1
#define OUT_RANGE 2

#define SIMPLE_LINE __FILE__, __FUNCTION__, __LINE__

namespace mcr {

class MyException:  public std::exception {
public:
    /*!
    *   @brief Конструктор
    */
    MyException(int err_code, std::string msg, const std::vector<MyException>& parent, 
                std::string file, std::string func, int line);
    /*!
    *   @brief Деструктор
    */
    ~MyException() {};
    /*!
    *   @brief Вывод сообщения о всех ошибках 
    */
    std::string what();
    /*!
    *   @brief Вывод сообщения об этой ошибке 
    */
    std::string what_that();
    /*!
    *   @brief Оператор сравнения  
    */                                                                  
    bool operator == (const MyException&) const;  
    /*!
    *   @brief Оператор неравенства 
    */                                                                  
    bool operator != (const MyException&) const;     
    /*!
    *   @brief Извлечь стек
    */  
    std::vector<MyException> get_stack();
private:
    /// Код Ошибки
    int m_err_code;
    /// Пользовательское сообщение
    std::string m_msg;
    /// Имя файла
    std::string m_file;
    /// Имя Функции
    std::string m_func;
    /// Номер линии
    int m_line;
    /// Стек исключений 
    std::vector<MyException> m_exc_stack;
};
}

#endif
