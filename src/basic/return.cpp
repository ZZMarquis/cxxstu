#include "common.hpp"

using namespace cxxstu;

class FooHolder
{
public:
    FooHolder()
    {
        std::cout << "This is FooHolder Constructor" << std::endl;
    }

    ~FooHolder()
    {
        std::cout << "This is FooHolder Destructor" << std::endl;
    }

    Foo GetFoo()
    {
        //返回值，其实是通过拷贝构造函数拷贝了一个对象的副本返回出去，看运行效果便知这里调用了Foo的拷贝构造函数
        //显然外部对返回出去的副本作任何改变，都不会影响到原对象本身。
        return foo;
    }

    Foo& GetFooRef()
    {
        //返回引用，则是直接把原对象的引用返回出去了，外部对该引用的改变都会体现到原对象身上。
        //但是如果外部定义了变量来接收返回的引用的赋值又另当别论，此时其实会调用对象的赋值构造函数，
        //也创造了一个原对象的副本，此时对这个副本的任何改变，也不会影响到原对象本身。
        return foo;
    }

private:
    Foo foo;
};

Foo ReturnLocalVarValue()
{
    //返回局部变量的值
    Foo f;
    f.Rename(__FUNCTION__);
    return f;
}

Foo& ReturnLocalVarRef()
{
    /*
    返回局部变量的引用
    这种写法是万万要不得的，因为其实在返回引用之后局部变量立刻就析构了，
    外部执行赋值构造的时候实际上这个引用对应的对象已经不存在了，此时引发Crash。

    返回局部变量引用和返回局部变量的差异在于：

    返回局部变量值的执行顺序是这样的：
        1、执行拷贝构造函数复制一个副本；
        2、析构局部变量；
        3、返回副本给外部，副本是一个存在的完整的对象

    返回局部变量引用的执行顺序是这样的：
        1、析构局部变量；
        2、返回局部变量的引用（引用其实就是一个地址，局部变量虽然被析构了，但是那个地址还是在那里）
        3、外部拿到了一个地址，但是这个地址指向的对象已经不存在的

    其实这种写法，编译器在编译时都会给出编译警告，如果不处理掉这种警告那就是给自己挖坑了
    */
    Foo f;
    f.Rename(__FUNCTION__);
    return f;
}

void GetLocalVarByRefParameter(Foo &outF)
{
    //其实个人感觉返回局部变量更好的做法应该是通过出参引用带出去，这比返回值的好处是有的情况下可以少一次副本的构造和析构，
    //比如在这个例子代码中就少了一次副本的构造和析构调用，效率更高。
    Foo f;
    f.Rename(__FUNCTION__);
    outF = f;
}

int main(int argc, char **argv)
{
    FooHolder fh;

    std::cout << "=====================================" << std::endl;

    fh.GetFoo().PrintName();
    fh.GetFoo().Rename("Return Value of Foo");
    fh.GetFoo().PrintName();
    std::cout << "=====================================" << std::endl;

    fh.GetFooRef().PrintName();
    fh.GetFooRef().Rename("Return Ref of Foo");
    fh.GetFooRef().PrintName();
    fh.GetFooRef().Reset();
    std::cout << "=====================================" << std::endl;

    Foo f = fh.GetFooRef();
    f.PrintName();
    f.Rename("Return Ref of Foo, And assign to Local Var");
    f.PrintName();
    fh.GetFooRef().PrintName();
    std::cout << "=====================================" << std::endl;

    f = ReturnLocalVarValue();
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    //f = ReturnLocalVarRef(); //这里会崩溃
    //f.PrintName();
    //std::cout << "=====================================" << std::endl;

    GetLocalVarByRefParameter(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    getchar();
    return 0;
}