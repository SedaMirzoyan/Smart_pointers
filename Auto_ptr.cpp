
#include <iostream>

class A
{
    int m_val;

public:
    A(int a)
    {
        m_val = a;
        std::cout << __func__ << std::endl;
    }

    ~A() = default;

    void print()
    {
        std::cout << "m_val = " << m_val << std::endl;
    }
};


template <typename T>
class Auto_ptr
{
    T* m_ptr;

public:
    Auto_ptr(T* ptr)
    {
        m_ptr = ptr;
        std::cout << __func__ << std::endl;
        if (m_ptr != nullptr)
        {
            std::cout << "m_ptr = " << m_ptr << std::endl;    
        }
        else
        {
            std::cout << "nullptr" << std::endl;    
        }
    }

    ~Auto_ptr()
    {
        std::cout << __func__ << std::endl;
        delete m_ptr;
        m_ptr = nullptr;
    }

    Auto_ptr(Auto_ptr& ob)          
    {
        //m_ptr = ob.m_ptr;
        std::cout << "Copy " << __func__ << std::endl;
        m_ptr = ob.release();
    }


    Auto_ptr& operator=(Auto_ptr& ob)
    {
        if (this != &ob)
        {
            delete m_ptr;
            m_ptr = ob.m_ptr;
        }
        return *this;
    }

    T* release()
    {
        T* tmp = m_ptr;
        m_ptr = nullptr;

        return tmp;
    }

    T* operator->()
    {
        return m_ptr;
    }

    T& operator*()
    {
        return *m_ptr;
    }
};


int main()
{
    int* arr = new int[10];
    A* ptr = new A(5);
    ptr->print();

    Auto_ptr<int> sp(new int(12));

    Auto_ptr<A> sp1 = (new A(7));
    //sp1->print();
    (*sp1).print();

    Auto_ptr<int> sp2 = sp;

    return 0;
}
