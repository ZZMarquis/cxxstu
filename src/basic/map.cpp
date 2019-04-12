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
    这种方式与TestDeleteInLoop里的方式的区别在于：
    m.erase(it++)和m.erase(it); iter++; 这个执行序列是不相同的。（需理解后置++会返回一个临时变量来缓存原值）。
    前者在erase执行前进行了加操作，在it被删除(失效)前进行了加操作，根据当前迭代器找到了下一个迭代器，是安全的；
    后者是在erase执行后才进行加操作，而此时迭代器已经被删除销毁，
    对一个已被销毁的迭代器进行寻址找下一个位置，会导致crash。
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
    这种方式与TestDeleteInLoop里的方式其实道理是一样的，只是显式地声明了一个临时变量来缓存当前迭代器，
    但是需切记：一定要在erase操作之前执行++操作，也就是在erase之前先找到下一个迭代器，
    如果在erase之后再去++则与TestDeleteInLoopIncorrectly其实是一个道理了
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