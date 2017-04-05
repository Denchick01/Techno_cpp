/*!
*    @file
*    @brief source to Logger
*    @author Трощенков Денис
*    @data 23.03.2017
*/


#include "logger.hpp"


namespace mcr {

///Конструктор
Logger::Logger()
{
    set_time_point();   
}

///Установить временную метку
void Logger::set_time_point()
{
    m_log_time_point = std::chrono::system_clock::now();
    m_time_point_f = true;
}

///Показать время
double Logger::show_time()
{
    assert(m_time_point_f);
    std::chrono::system_clock::time_point current_time  =  std::chrono::system_clock::now();
    size_t time = std::chrono::duration_cast<std::chrono::seconds>(current_time - m_log_time_point).count();
    return time/60.0;
}

///Очистка лога
void Logger::clear_log()
{
    m_log_stack.clear();
}

///Вывести лог в output
void Logger::get_log(std::ostream &output)
{
    for (size_t it = 0; it < m_log_stack.size(); it++) {
        output << m_log_stack[it] << "\n";
    }
    output << "Statistics:\n";
    output << "Lead time: " << show_time() << " min\n";
    output << "Number of iterations: " << m_log_stack.size() << "\n";
}
}
