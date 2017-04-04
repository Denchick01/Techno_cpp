/*
*    @file
*    @brief Logger
*    @author Денис Трощенков 
*    @version 1.0
*    @data 23.03.2017
*
*/

#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_
  
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
 
namespace mcr {

class Logger {
public:
    typedef std::chrono::system_clock::time_point Lg_time;
    /*!
    *    @brief Конструктор 
    */
    Logger();
    /*!
    *    @brief Деструктор
    */
    ~Logger() {}
    /*! 
    *    @brief Конструктор копирования, запрещен 
    */
    Logger(const Logger&) = delete;
    /*!
    *    @brief Оператор присваивания, запрещен 
    */
    Logger& operator = (const Logger&) = delete;
    /*!
    *    @brief Установить метку времени
    */
    void set_time_point();
    /*!
    *    @brief вывести время на экран
    *    @return время
    */
    double show_time();
private:
    /*!
    *    @brief Добавить сроку лога
    */
    void push_log_string() {
        m_log_stack.push_back(m_log_str);
        m_log_str.clear();
    }
public:
    template<typename T, typename... Args>
    void push_log_string(const T& value, const Args&... args) 
    {
        std::stringstream ss;
        ss << " " << value;
        m_log_str += ss.str();
        push_log_string(args...);
    }
    /*!
    *    @brief Вывести лог в output
    */
    void get_log(std::ostream &output);
    /*!
    *    @brief Очистка лога
    */
    void clear_log();    
private:
    bool m_time_point_f;
    Lg_time m_log_time_point;
    std::string m_log_str;   
    std::vector<std::string> m_log_stack;
};
}

#endif



