#include <memory>
#include "common.hpp"

using namespace cxxstu;

#define PRINT_ENTER_FUNC() std::cout<< ">>>>>" << __FUNCTION__ << "<<<<<" << std::endl

void PassArrayAsCStyle(Foo *foos, int count)
{
    for (int i = 0; i < count; ++i) {
        foos[i].PrintName();
        foos[i].Rename(__FUNCTION__);
    }
}

void TestArrayBySharedPtr()
{
    PRINT_ENTER_FUNC();

    /*
    1
    可以这么写
    */
    //std::shared_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    推荐写法
    如果不显示传入内存清理function，则会根据声明中的类型调用一个默认的内存清理function，其实最终就跟第1种方式一样了
    */
    std::shared_ptr<Foo[]> foos(new Foo[3]);

    /*
    3
    自定义内存清理function
    这么写也是可以的，甚至有的情况下释放复杂对象（比如对象又持有指向动态分配内存的指针）时必须自定义内存清理function
    */
    //auto deleteFunc = [](Foo *foos) {
    //    delete[] foos;
    //};
    //std::shared_ptr<Foo[]> foos(new Foo[3], deleteFunc);

    /*
    4
    这么写是不行的，会崩溃，其实是调用delete p去释放，而不是调用delete[] p
    */
    //std::shared_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo>());

    foos[0].Rename(__FUNCTION__ "0");
    foos[1].Rename(__FUNCTION__ "1");
    foos[2].Rename(__FUNCTION__ "2");

    PassArrayAsCStyle(foos.get(), 3);

    foos[0].PrintName();
    foos[1].PrintName();
    foos[2].PrintName();
}

void TestArrayBySharedPtrNotRecommended()
{
    PRINT_ENTER_FUNC();

    /*
    除非需要共享目标，此时需使用shared_ptr。否则unique_ptr更适合用来智能管理动态数组，
    譬如如果动态数组是局部变量，则应尽量使用unique_ptr。
    */

    /*
    1
    这么写虽然可以，但是还是建议按TestArrayBySharedPtr中的推荐方式
    */
    std::shared_ptr<Foo> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    这么写是不行的，会崩溃，其实是调用delete p去释放，而不是调用delete[] p
    */
    //std::shared_ptr<Foo> foos(new Foo[3], std::default_delete<Foo>()); 

    /*
    3
    这么写也是不行的，会崩溃
    如果不显示传入内存清理function，则会根据声明中的类型调用一个默认的内存清理function，其实最终就跟第2种方式一样了
    */
    //std::shared_ptr<Foo> foos(new Foo[3]);

    foos.get()[0].Rename(__FUNCTION__ "0");
    foos.get()[1].Rename(__FUNCTION__ "1");
    foos.get()[2].Rename(__FUNCTION__ "2");

    PassArrayAsCStyle(foos.get(), 3);

    foos.get()[0].PrintName();
    foos.get()[0].PrintName();
    foos.get()[0].PrintName();
}

void TestArrayByUniquePtr()
{
    PRINT_ENTER_FUNC();

    /*
    1
    可以这么写
    */
    //std::unique_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    推荐写法
    如果不显示传入内存清理function，则会根据声明中的类型调用一个默认的内存清理function，其实最终就跟第1种方式一样了
    */
    std::unique_ptr<Foo[]> foos(new Foo[3]);

    /*
    3
    实则不支持这么自定义内存清理function
    */
    //auto deleteFunc = [](Foo *foos) {
    //    delete[] foos;
    //};
    //std::unique_ptr<Foo[]> foos(new Foo[3], deleteFunc);

    /*
    4
    这么写是不行的，直接就编译不过
    这在使用shared_ptr的时候是可以编译通过的，但是会导致释放不正确而崩溃
    */
    //std::unique_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo>());

    foos[0].Rename(__FUNCTION__ "0");
    foos[1].Rename(__FUNCTION__ "1");
    foos[2].Rename(__FUNCTION__ "2");

    PassArrayAsCStyle(foos.get(), 3);

    foos[0].PrintName();
    foos[1].PrintName();
    foos[2].PrintName();
}


int main(int argc, char **argv)
{
    TestArrayBySharedPtr();
    std::cout << "=====================================" << std::endl;

    TestArrayBySharedPtrNotRecommended();
    std::cout << "=====================================" << std::endl;

    TestArrayByUniquePtr();
    std::cout << "=====================================" << std::endl;

    getchar();
    return 0;
}