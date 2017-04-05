/*!
*    @file 
*
*    @brief Реализация auto_ptr
*
*    @author Денис Трощенков
*
*    @data 4.04.2017
*
*/


#ifndef __MY_AUTO_PTR_HPP__
#define __MY_AUTO_PTR_HPP__


namespace mcr {

template <typename T>	
class MyAutoPtr {
public:
    MyAutoPtr () : m_ptr(nullptr) {}
    explicit MyAutoPtr (T* ptr) : m_ptr(ptr) {}
    MyAutoPtr (MyAutoPtr& that) : m_ptr(that.m_ptr) 
    {that.release();}

    ~MyAutoPtr() {delete m_ptr;}
    
    MyAutoPtr (const MyAutoPtr& ptr) = delete;
    MyAutoPtr& operator = (const MyAutoPtr& ptr) = delete;

    MyAutoPtr& operator = (MyAutoPtr& ptr)
    {
         m_ptr(ptr.m_ptr);
         ptr.release();
    }

    void reset(T* ptr)
    {
        this->~MyAutoPtr();
        m_ptr = ptr;
    }

    void release() 
    {
        this->~MyAutoPtr();
        m_ptr = nullptr;
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
