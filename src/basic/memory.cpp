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
    ������ôд
    */
    //std::shared_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    �Ƽ�д��
    �������ʾ�����ڴ�����function�������������е����͵���һ��Ĭ�ϵ��ڴ�����function����ʵ���վ͸���1�ַ�ʽһ����
    */
    std::shared_ptr<Foo[]> foos(new Foo[3]);

    /*
    3
    �Զ����ڴ�����function
    ��ôдҲ�ǿ��Եģ������е�������ͷŸ��Ӷ��󣨱�������ֳ���ָ��̬�����ڴ��ָ�룩ʱ�����Զ����ڴ�����function
    */
    //auto deleteFunc = [](Foo *foos) {
    //    delete[] foos;
    //};
    //std::shared_ptr<Foo[]> foos(new Foo[3], deleteFunc);

    /*
    4
    ��ôд�ǲ��еģ����������ʵ�ǵ���delete pȥ�ͷţ������ǵ���delete[] p
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
    ������Ҫ����Ŀ�꣬��ʱ��ʹ��shared_ptr������unique_ptr���ʺ��������ܹ���̬���飬
    Ʃ�������̬�����Ǿֲ���������Ӧ����ʹ��unique_ptr��
    */

    /*
    1
    ��ôд��Ȼ���ԣ����ǻ��ǽ��鰴TestArrayBySharedPtr�е��Ƽ���ʽ
    */
    std::shared_ptr<Foo> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    ��ôд�ǲ��еģ����������ʵ�ǵ���delete pȥ�ͷţ������ǵ���delete[] p
    */
    //std::shared_ptr<Foo> foos(new Foo[3], std::default_delete<Foo>()); 

    /*
    3
    ��ôдҲ�ǲ��еģ������
    �������ʾ�����ڴ�����function�������������е����͵���һ��Ĭ�ϵ��ڴ�����function����ʵ���վ͸���2�ַ�ʽһ����
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
    ������ôд
    */
    //std::unique_ptr<Foo[]> foos(new Foo[3], std::default_delete<Foo[]>());

    /*
    2
    �Ƽ�д��
    �������ʾ�����ڴ�����function�������������е����͵���һ��Ĭ�ϵ��ڴ�����function����ʵ���վ͸���1�ַ�ʽһ����
    */
    std::unique_ptr<Foo[]> foos(new Foo[3]);

    /*
    3
    ʵ��֧����ô�Զ����ڴ�����function
    */
    //auto deleteFunc = [](Foo *foos) {
    //    delete[] foos;
    //};
    //std::unique_ptr<Foo[]> foos(new Foo[3], deleteFunc);

    /*
    4
    ��ôд�ǲ��еģ�ֱ�Ӿͱ��벻��
    ����ʹ��shared_ptr��ʱ���ǿ��Ա���ͨ���ģ����ǻᵼ���ͷŲ���ȷ������
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