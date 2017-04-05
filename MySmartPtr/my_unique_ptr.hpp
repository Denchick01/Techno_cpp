/*!
*    @file 
*
*    @brief Реализация unique_ptr
*
*    @author Денис Трощенков
*
*    @data 4.04.2017
*
*/


#ifndef __MY_UNIQUE_PTR_HPP__
#define __MY_UNIQUE_PTR_HPP__


namespace mcr {

template <typename T>	
class MyUniquePtr {
public:
    MyUniquePtr () : m_ptr(nullptr) {}
    explicit MyUniquePtr (T* ptr) : m_ptr(ptr) {}
    MyUniquePtr (MyUniquePtr& that) : m_ptr(that.m_ptr) 
    {that.release();}

    ~MyUniquePtr() {delete m_ptr;}
    
    MyUniquePtr (const MyUniquePtr& ptr) = delete;
    MyUniquePtr& operator = (const MyUniquePtr& ptr) = delete;

    void release() 
    {
        this->~MyUniquePtr();
        m_ptr = nullptr;
    }

    void reset(T* ptr)
    {
        delete m_ptr;
        m_ptr = ptr;
    }

    void swap(MyUniquePtr& ptr)
    {
        std::swap(m_ptr, ptr.m_ptr);
    }

    operator bool() const
    {
        return m_ptr != nullptr;
    }

    T* operator ->()
    {
        return m_ptr;
    }

    T& operator *()
    {
        return *m_ptr;
    }

    T* get()
    {
        return m_ptr;
    }
private:
    T* m_ptr;
};
}

#endif
