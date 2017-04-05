/*!
*   @file
*
*   @brief Вспомогательные отладочные макросы
*
*   @author Трощенков Денис
*   
*   @data 27.02.2017
*   
*/


#ifndef __MY_MACRO_H__
#define __MY_MACRO_H__

#include <iostream>
#include <cassert>

//#define DEBUG_SET 0
  
#if DEBUG_SET
    #define MESSAGE(massage)     \
        m_logg.push_log_string("FILE: ", __FILE__ , " LINE: ", __LINE__, "  ", "FUNCTION:", " ",  __FUNCTION__, " " , massage);
    #define ASSERT_OK()                                                                          \
        for (bool t_ok = !v_ok(); t_ok; t_ok = false) {                                                                           \
        dump(__FILE__, __LINE__, __FUNCTION__, std::cerr);                                                  \
        assert("Object is OK");                                                                 \
        }
#else
    #define ASSERT_OK() 
    #define MESSAGE(massag)
#endif

#endif
