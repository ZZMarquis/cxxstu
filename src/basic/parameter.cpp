#include "common.hpp"

using namespace cxxstu;

void PassRef(const Foo &f)
{
    //һ����Ϊ���ʱ����������ǳ����ã�ʹ�����õ����ô���Ч�ʣ����ֵ������˵����
    //ʹ��const������ʹ������ȷ���߱������ʹ����Ķ�������һ����Σ����ɱ��ı䡣
    PRINT_FUNC_LINE();
}

void PassValue(const Foo f)
{
    //ֵ���ݵù����У�ʵ�����ǵ��ÿ������캯����������һ���������ݵ������У�
    //�뿪����ʱ��������������������ø�������Ȼ��������Ч���ǲ������ô��ݵġ�
    PRINT_FUNC_LINE();
}

void PassValueAndModify(Foo f)
{
    //ֵ�����ں����ڶ��ǶԸ������в�������Ȼ���ں����ڶ�������������κβ�����������Ժ������ԭ�������κ�Ӱ�졣
    PRINT_FUNC_LINE();
    f.PrintName();
    f.Rename(__FUNCTION__);
    std::cout << "Rename in " << __FUNCTION__ << std::endl;
}

void PassRefAndModify(Foo &f)
{
    //���ô������ǰ�ԭ��������ô��ݵ��˺����ڲ����ں����ڲ��Ը����õĲ���ʵ���϶��������ں������ԭ�������ϡ�
    PRINT_FUNC_LINE();
    f.PrintName();
    f.Rename(__FUNCTION__);
    std::cout << "Rename in " << __FUNCTION__ << std::endl;
}

void PassRefAndAssign(Foo &f)
{
    //��ô�ں������½�һ������Ȼ����������ֵ�����ݽ��������ûᷢ��ʲô�أ�
    //��ʵ���Ǻ��������ö�Ӧ��ԭ����ᱻ�滻��������ָ�����µĶ��󣬶�ԭ��������ü����ᱻ��1��
    //�������������Ϊ�Ѿ�û������ָ��ԭ�����ˣ�����ԭ����ᱻ������
    PRINT_FUNC_LINE();
    f.PrintName();
    Foo newF(__FUNCTION__);
    f = newF;
    std::cout << "new Foo and assign it to out parameter in " << __FUNCTION__ << std::endl;
}

void PassValueAndAssign(Foo f)
{
    //��ô�ں������½�һ������Ȼ����������ֵ�����ݽ�����ֵ�ᷢ��ʲô�أ�
    //��Ȼ���ǶԺ������ԭ����û���κ�Ӱ�죬�����;ֲ������¶��󶼻��ڸú�������ʱ��������
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