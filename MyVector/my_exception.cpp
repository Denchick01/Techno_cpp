/*!
*   @file
*
*   @brief MyException source
*
*   @author Трощенков Денис
*
*   @data 27.02.2017
*
*/

#include "my_exception.hpp"

namespace mcr {

///Конструктор
MyException::MyException(int err_code, std::string msg, const std::vector<MyException>& exc_stack,
                         std::string file, std::string func, int line) : m_err_code(err_code), m_msg(msg), 
                                                                         m_file(file), m_func(func), 
                                                                         m_line(line), m_exc_stack(exc_stack) 
{
    m_exc_stack.push_back(*this);
}

///Извлечь стек
std::vector<MyException> MyException::get_stack() {
    return m_exc_stack;
}


///Вывод сообщения об этой ошибке
std::string MyException::what_that()
{
    std::string msg;
    std::stringstream ss;

    ss << m_msg << "\n"; 
    ss << "error_code: " << m_err_code << "\n";
    ss << "file: " << m_file << "\n";
    ss << "line: " << m_line << "\n";
    ss << "function: " << m_func << "\n";
    msg = ss.str();

    return msg;
}

///Вывод сообщения о всех ошибках
std::string MyException::what()
{
    std::string msg;
    std::stringstream ss;
    for (size_t it = 0; it < m_exc_stack.size(); ++it) {
        ss << "exception: " << it << "\n";
        ss << m_exc_stack[it].what_that() << "\n";
    }
    msg += ss.str();
}

///Оператор сравнения
bool MyException::operator == (const MyException& exc) const
{
    return m_err_code == exc.m_err_code;
}

///Оператор неравенства
bool MyException::operator != (const MyException& exc) const
{
    return m_err_code != exc.m_err_code;
}

}
