#include "common.hpp"

using namespace cxxstu;

void PassRef(const Foo &f)
{
    //一般作为入参时，变量最好是常引用，使用引用的最大好处是效率（相对值传递来说），
    //使用const修饰是使语义明确告诉编译器和代码阅读者这是一个入参，不可被改变。
    PRINT_FUNC_LINE();
}

void PassValue(const Foo f)
{
    //值传递得过程中，实际上是调用拷贝构造函数，复制了一个副本传递到函数中，
    //离开函数时还会调用析构函数析构该副本，显然，这样做效率是不如引用传递的。
    PRINT_FUNC_LINE();
}

void PassValueAndModify(Foo f)
{
    //值传递在函数内都是对副本进行操作，显然，在函数内对这个副本进行任何操作，都不会对函数外的原对象有任何影响。
    PRINT_FUNC_LINE();
    f.PrintName();
    f.Rename(__FUNCTION__);
    std::cout << "Rename in " << __FUNCTION__ << std::endl;
}

void PassRefAndModify(Foo &f)
{
    //引用传递则是把原对象的引用传递到了函数内部，在函数内部对该引用的操作实际上都会体现在函数外的原对象身上。
    PRINT_FUNC_LINE();
    f.PrintName();
    f.Rename(__FUNCTION__);
    std::cout << "Rename in " << __FUNCTION__ << std::endl;
}

void PassRefAndAssign(Foo &f)
{
    //那么在函数里新建一个对象，然后把这个对象赋值给传递进来的引用会发生什么呢？
    //其实就是函数外引用对应的原对象会被替换掉，引用指向了新的对象，而原对象的引用计数会被减1，
    //在这个例子里因为已经没有引用指向原对象了，所以原对象会被析构。
    PRINT_FUNC_LINE();
    f.PrintName();
    Foo newF(__FUNCTION__);
    f = newF;
    std::cout << "new Foo and assign it to out parameter in " << __FUNCTION__ << std::endl;
}

void PassValueAndAssign(Foo f)
{
    //那么在函数里新建一个对象，然后把这个对象赋值给传递进来的值会发生什么呢？
    //当然还是对函数外的原对象没有任何影响，副本和局部变量新对象都会在该函数结束时被析构。
    PRINT_FUNC_LINE();
    f.PrintName();
    Foo newF(__FUNCTION__);
    f = newF;
    std::cout << "new Foo and assign it to out parameter in " << __FUNCTION__ << std::endl;
}

int main(int argc, char **argv)
{
    Foo f;

    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassRef(f);
    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassValue(f);
    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassValueAndModify(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassRefAndModify(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassRefAndAssign(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    f.Reset();
    PassValueAndAssign(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    getchar();
    return 0;
}