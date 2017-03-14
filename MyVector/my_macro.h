/*!
    \file

    \brief Вспомогательные отладочные макросы

    \author Трощенков Денис
   
    \data 27.02.2017
   
*/

#ifndef __MY_MACRO_H__
#define __MY_MACRO_H__

#include <iostream>
#include <cassert>
  
#if DEBUG_SET
    #define MESSAGE(massage, stream)                                                             \
        stream << "FILE: " << __FILE__ << " LINE: " << __LINE__ << "  "<< massage << std::endl;
    #define ASSERT_OK()                                                                          \
        if (!v_ok()) {                                                                           \
        stk_dump(__FILE__, __LINE__, __FUNCTION__);                                              \
        assert(!"Object is OK");                                                                 \
        }
#else
    #define ASSERT_OK() 
    #define MESSAGE(massage, stream)
#endif

#endif
