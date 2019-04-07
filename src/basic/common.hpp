#ifndef _CXX_STU_BASIC_COMMON_HPP_
#define _CXX_STU_BASIC_COMMON_HPP_

#include <iostream>


#define PRINT_FUNC_LINE() std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl

namespace cxxstu {
    class Foo
    {
    public:
        Foo();
        Foo(const std::string name);
        Foo(const Foo &f);
        Foo& operator=(const Foo &f);
        ~Foo();

        Foo(Foo&& f);
        Foo& operator=(Foo&& f);

        void Rename(const std::string &name);
        void PrintName();
        void Reset();

    private:
        std::string name;
    };

    Foo::Foo()
    {
        Reset();
        std::cout << "This is Foo Constructor, name:" << name.c_str() << std::endl;
    }

    Foo::Foo(const std::string name)
    {
        this->name = name;
        std::cout << "This is Foo Constructor, name:" << name.c_str() << std::endl;
    }

    Foo::Foo(const Foo & f)
    {
        this->name = f.name;
        std::cout << "This is Foo Copy Constructor, name:" << name.c_str() << std::endl;
    }

    Foo & Foo::operator=(const Foo & f)
    {
        this->name = f.name;
        std::cout << "This is Foo Assign Constructor, name:" << name.c_str() << std::endl;
        return *this;
    }

    Foo::~Foo()
    {
        std::cout << "This is Foo Destructor, name:" << name.c_str() << std::endl;
    }

    Foo::Foo(Foo && f)
    {
        this->name = f.name;
        f.name.clear();
        std::cout << "This is Foo Move Constructor, name:" << name.c_str() << std::endl;
    }

    Foo & Foo::operator=(Foo && f)
    {
        if (this != &f)
        {
            this->name = f.name;
            f.name.clear();
        }
        std::cout << "This is Foo Move Assign Constructor, name:" << name.c_str() << std::endl;
        return *this;
    }

    inline void Foo::Rename(const std::string &name)
    {
        this->name = name;
    }

    inline void Foo::PrintName()
    {
        std::cout << "name:" << name.c_str() << std::endl;
    }

    inline void Foo::Reset()
    {
        this->name = std::string("HelloWorld");
    }
}

#endif // !_CXX_STU_BASIC_COMMON_HPP_
