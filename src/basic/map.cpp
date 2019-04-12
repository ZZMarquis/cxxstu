#include <stdio.h>
#include <map>
#include "common.hpp"

void CreateIntMap(std::map<int, int> &map)
{
    for (int i = 0; i < 20; i++) {
        map.insert(std::make_pair(i, i));
    }
}

void PrintIntMap(const std::map<int, int> &map)
{
    PRINT_ENTER_FUNC();
    for (const auto &t : map) {
        printf("Key:%d, Value:%d\n", t.first, t.second);
    }
}

void TestDeleteInLoop()
{
    PRINT_ENTER_FUNC();

    std::map<int, int> map;
    CreateIntMap(map);

    std::map<int, int>::iterator itr;
    for (itr = map.begin(); itr != map.end();) {
        if ((*itr).first % 3 == 0) {
            map.erase(itr++);
        } else {
            itr++;
        }
    }

    PrintIntMap(map);
}

void TestDeleteInLoopIncorrectly()
{
    PRINT_ENTER_FUNC();

    std::map<int, int> map;
    CreateIntMap(map);

    /*
    ���ַ�ʽ��TestDeleteInLoop��ķ�ʽ���������ڣ�
    m.erase(it++)��m.erase(it); iter++; ���ִ�������ǲ���ͬ�ġ�����������++�᷵��һ����ʱ����������ԭֵ����
    ǰ����eraseִ��ǰ�����˼Ӳ�������it��ɾ��(ʧЧ)ǰ�����˼Ӳ��������ݵ�ǰ�������ҵ�����һ�����������ǰ�ȫ�ģ�
    ��������eraseִ�к�Ž��мӲ���������ʱ�������Ѿ���ɾ�����٣�
    ��һ���ѱ����ٵĵ���������Ѱַ����һ��λ�ã��ᵼ��crash��
    */
    std::map<int, int>::iterator itr;
    for (itr = map.begin(); itr != map.end(); itr++) {
        if ((*itr).first % 3 == 0) {
            map.erase(itr);
        }
    }

    PrintIntMap(map);
}

void TestDeleteInLoop2()
{
    PRINT_ENTER_FUNC();

    std::map<int, int> map;
    CreateIntMap(map);

    /*
    ���ַ�ʽ��TestDeleteInLoop��ķ�ʽ��ʵ������һ���ģ�ֻ����ʽ��������һ����ʱ���������浱ǰ��������
    �������мǣ�һ��Ҫ��erase����֮ǰִ��++������Ҳ������erase֮ǰ���ҵ���һ����������
    �����erase֮����ȥ++����TestDeleteInLoopIncorrectly��ʵ��һ��������
    */
    std::map<int, int>::iterator itr;
    std::map<int, int>::iterator tmp;
    for (itr = map.begin(); itr != map.end();) {
        tmp = itr;
        itr++;
        if ((*tmp).first % 3 == 0) {
            map.erase(tmp);
        }
    }

    PrintIntMap(map);
}

int main(int argc, char **argv)
{
    TestDeleteInLoop();
    std::cout << "=====================================" << std::endl;

    //TestDeleteInLoopIncorrectly(); 
    //std::cout << "=====================================" << std::endl;

    TestDeleteInLoop2();
    std::cout << "=====================================" << std::endl;

    getchar();
    return 0;
}