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
        //����ֵ����ʵ��ͨ���������캯��������һ������ĸ������س�ȥ��������Ч����֪���������Foo�Ŀ������캯��
        //��Ȼ�ⲿ�Է��س�ȥ�ĸ������κθı䣬������Ӱ�쵽ԭ������
        return foo;
    }

    Foo& GetFooRef()
    {
        //�������ã�����ֱ�Ӱ�ԭ��������÷��س�ȥ�ˣ��ⲿ�Ը����õĸı䶼�����ֵ�ԭ�������ϡ�
        //��������ⲿ�����˱��������շ��ص����õĸ�ֵ�������ۣ���ʱ��ʵ����ö���ĸ�ֵ���캯����
        //Ҳ������һ��ԭ����ĸ�������ʱ������������κθı䣬Ҳ����Ӱ�쵽ԭ������
        return foo;
    }

private:
    Foo foo;
};

Foo ReturnLocalVarValue()
{
    //���ؾֲ�������ֵ
    Foo f;
    f.Rename(__FUNCTION__);
    return f;
}

Foo& ReturnLocalVarRef()
{
    /*
    ���ؾֲ�����������
    ����д��������Ҫ���õģ���Ϊ��ʵ�ڷ�������֮��ֲ��������̾������ˣ�
    �ⲿִ�и�ֵ�����ʱ��ʵ����������ö�Ӧ�Ķ����Ѿ��������ˣ���ʱ����Crash��

    ���ؾֲ��������úͷ��ؾֲ������Ĳ������ڣ�

    ���ؾֲ�����ֵ��ִ��˳���������ģ�
        1��ִ�п������캯������һ��������
        2�������ֲ�������
        3�����ظ������ⲿ��������һ�����ڵ������Ķ���

    ���ؾֲ��������õ�ִ��˳���������ģ�
        1�������ֲ�������
        2�����ؾֲ����������ã�������ʵ����һ����ַ���ֲ�������Ȼ�������ˣ������Ǹ���ַ���������
        3���ⲿ�õ���һ����ַ�����������ַָ��Ķ����Ѿ������ڵ�

    ��ʵ����д�����������ڱ���ʱ����������뾯�棬�������������־����Ǿ��Ǹ��Լ��ڿ���
    */
    Foo f;
    f.Rename(__FUNCTION__);
    return f;
}

void GetLocalVarByRefParameter(Foo &outF)
{
    //��ʵ���˸о����ؾֲ��������õ�����Ӧ����ͨ���������ô���ȥ����ȷ���ֵ�ĺô����е�����¿�����һ�θ����Ĺ����������
    //������������Ӵ����о�����һ�θ����Ĺ�����������ã�Ч�ʸ��ߡ�
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

    //f = ReturnLocalVarRef(); //��������
    //f.PrintName();
    //std::cout << "=====================================" << std::endl;

    GetLocalVarByRefParameter(f);
    f.PrintName();
    std::cout << "=====================================" << std::endl;

    getchar();
    return 0;
}