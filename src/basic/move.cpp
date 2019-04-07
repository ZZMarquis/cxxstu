#include <map>
#include <stdio.h>

//主要参考：https://www.lanindex.com/stdmove%E5%AE%9E%E9%99%85%E5%BA%94%E7%94%A8%E5%88%86%E6%9E%90/

/*
对左值和右值的一个最常见的误解是：等号左边的就是左值，等号右边的就是右值。
左值和右值都是针对表达式而言的，左值是指表达式结束后依然存在的持久对象，右值是指表达式结束时就不再存在的临时对象。
一个区分左值与右值的便捷方法是：看能不能对表达式取地址，如果能，则为左值，否则为右值。

要理解移动语义的好处，首先要理解深拷贝与浅拷贝：
深拷贝：A先申请出一片新的空间，完全复制B的内容到新空间中；
浅拷贝：A复制B指针，将自己的指针指向B的内容地址，A、B公用一块内存地址；
所以对于深拷贝，A的修改与B没有关系；对于浅拷贝，A的修改也会在B对象也会被改变。

std::move()使用的意义即是协助使用者进行浅拷贝，
前提条件是拷贝对象需要支持移动赋值（move-assignment）、移动构造（move-constructor），
即对于自定义对象需要用户自定义移动构造函数和移动赋值函数。
*/

void TestDeepCopy()
{
    /*
    这里可以看到mapA和mapB每一个元素的地址都不一样，说明是在拷贝的时候mapB为每一个元素都重新开辟了内存空间
    然后把mapA中对应的内容拷贝到新开辟的内存空间中
    */
    std::map<int, int> mapA;
    mapA[1] = 1;
    mapA[2] = 2;
    mapA[3] = 3;
    printf("addr A: %x|%x|%x\n", &mapA[1], &mapA[2], &mapA[3]);

    std::map<int, int> mapB = mapA;
    printf("addr B: %x|%x|%x\n", &mapB[1], &mapB[2], &mapB[3]);

    mapB[4] = 4;
    printf("new value: %d|%d\n", mapA[4], mapB[4]);
    printf("addr new: %d|%d\n", &mapA[4], &mapB[4]);
}

void TestMove()
{
    /*
    看到在使用std::move之后，B对A进行了浅拷贝，仅仅只赋值了key=1,2,3的指针。
    那么这里引发了一个新的问题：在move(mapA)之后，我们并不希望再进一步对A中key=1,2,3的对象做操作，
    否则会引起“不可预期”的结果，比如释放了同一个地址。
    所以我们需要约束对于move后的对象，应当马上“弃用”（std::map已经自动做了这个操作，在move之后A里面的key全部被清空了）。
    */
    std::map<int, int> mapA;
    mapA[1] = 1;
    mapA[2] = 2;
    mapA[3] = 3;
    printf("addr A: %x|%x|%x\n", &mapA[1], &mapA[2], &mapA[3]);

    std::map<int, int> mapB = std::move(mapA);
    printf("addr B: %x|%x|%x\n", &mapB[1], &mapB[2], &mapB[3]);

    //这里可以看到A size==0了，说明mapA已经被清空了。
    printf("A size:%d\n", mapA.size());

    //这里可以看到mapA[4]和mapB[4]地址已经不一样了，说明了自移动赋值完成之后，它们之间已经不再有联系
    mapB[4] = 4;
    printf("new value: %d|%d\n", mapA[4], mapB[4]);
    printf("addr new: %d|%d\n", &mapA[4], &mapB[4]);
}

void TestRefAssign()
{
    /*
    这里可能会有人问，为什么要搞这么麻烦，我直接用C++传统的左值引用不就可以了吗？
    从这个例子里可以看到传统的左值引用导致A，B互相影响，就语境来说不太利于把A拷贝到B，然后丢弃A的场景。
    所以说移动语义补充了这块空白，其核心就是利用浅拷贝来模拟对象的移动行为，提高了效率，让语义更加明确。
    */
    std::map<int, int> mapA;
    mapA[1] = 1;
    mapA[2] = 2;
    mapA[3] = 3;
    printf("addr A: %x|%x|%x\n", &mapA[1], &mapA[2], &mapA[3]);

    std::map<int, int> &mapB = mapA;
    printf("addr B: %x|%x|%x\n", &mapB[1], &mapB[2], &mapB[3]);

    mapB[4] = 4;
    printf("new value: %d|%d\n", mapA[4], mapB[4]);
    printf("addr new: %d|%d\n", &mapA[4], &mapB[4]);
}

int main(int argc, char **argv)
{
    TestDeepCopy();
    printf("=====================================\n");

    TestMove();
    printf("=====================================\n");

    TestRefAssign();
    printf("=====================================\n");

    getchar();
    return 0;
}