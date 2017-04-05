/*!
*    @file
*
*    @brief Реализация shared_ptr
*
*    @author Денис Трощенков
*
*    @data 4.04.2017
*/


#ifndef _MY_SHARED_PTR_HPP__
#define _MY_SHARED_PTR_HPP__

#include <iostream>

namespace mcr {

template <typename T>
class MySharedPtr {
public:
    MySharedPtr() : m_ptr(nullptr),
                    m_count(new size_t(1))
    {}

    MySharedPtr(const MySharedPtr& that) : m_ptr(that.m_ptr),
                                           m_count(that.m_count)
    {++(*m_count);}

    explicit MySharedPtr(T* ptr) : m_ptr(ptr),
                                   m_count(new size_t(1))
    {}

    ~MySharedPtr()
    {
        --(*m_count);
        if (*m_count == 0)
        {
            delete m_ptr;
            delete m_count;
        }
    }

    MySharedPtr& operator = (const MySharedPtr& that)
    {
        m_ptr(that.m_ptr);
        m_count(that.m_count);
        return *this;
    }
    
    T* operator ->()
    {
        return m_ptr;
    }

    T& operator *()
    {
        return *m_ptr;
    }

    void reset(T* ptr)
    {
        this->~MySharedPtr();
        m_count(new size_t(1));
        m_ptr = ptr;
    }

    T* get()
    {
        return m_ptr;
    }

    operator bool() const
    {
        return m_ptr != nullptr;
    }

    void swap(MySharedPtr& that)
    {
        std::swap(m_ptr, that.m_ptr);
        std::swap(m_count, that.m_count);
    }

private:
    T* m_ptr;
    size_t *m_count;
};

}

#endif
