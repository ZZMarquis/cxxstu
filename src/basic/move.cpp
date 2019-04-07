#include <map>
#include <stdio.h>

//��Ҫ�ο���https://www.lanindex.com/stdmove%E5%AE%9E%E9%99%85%E5%BA%94%E7%94%A8%E5%88%86%E6%9E%90/

/*
����ֵ����ֵ��һ�����������ǣ��Ⱥ���ߵľ�����ֵ���Ⱥ��ұߵľ�����ֵ��
��ֵ����ֵ������Ա��ʽ���Եģ���ֵ��ָ���ʽ��������Ȼ���ڵĳ־ö�����ֵ��ָ���ʽ����ʱ�Ͳ��ٴ��ڵ���ʱ����
һ��������ֵ����ֵ�ı�ݷ����ǣ����ܲ��ܶԱ��ʽȡ��ַ������ܣ���Ϊ��ֵ������Ϊ��ֵ��

Ҫ����ƶ�����ĺô�������Ҫ��������ǳ������
�����A�������һƬ�µĿռ䣬��ȫ����B�����ݵ��¿ռ��У�
ǳ������A����Bָ�룬���Լ���ָ��ָ��B�����ݵ�ַ��A��B����һ���ڴ��ַ��
���Զ��������A���޸���Bû�й�ϵ������ǳ������A���޸�Ҳ����B����Ҳ�ᱻ�ı䡣

std::move()ʹ�õ����弴��Э��ʹ���߽���ǳ������
ǰ�������ǿ���������Ҫ֧���ƶ���ֵ��move-assignment�����ƶ����죨move-constructor����
�������Զ��������Ҫ�û��Զ����ƶ����캯�����ƶ���ֵ������
*/

void TestDeepCopy()
{
    /*
    ������Կ���mapA��mapBÿһ��Ԫ�صĵ�ַ����һ����˵�����ڿ�����ʱ��mapBΪÿһ��Ԫ�ض����¿������ڴ�ռ�
    Ȼ���mapA�ж�Ӧ�����ݿ������¿��ٵ��ڴ�ռ���
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
    ������ʹ��std::move֮��B��A������ǳ����������ֻ��ֵ��key=1,2,3��ָ�롣
    ��ô����������һ���µ����⣺��move(mapA)֮�����ǲ���ϣ���ٽ�һ����A��key=1,2,3�Ķ�����������
    ��������𡰲���Ԥ�ڡ��Ľ���������ͷ���ͬһ����ַ��
    ����������ҪԼ������move��Ķ���Ӧ�����ϡ����á���std::map�Ѿ��Զ����������������move֮��A�����keyȫ��������ˣ���
    */
    std::map<int, int> mapA;
    mapA[1] = 1;
    mapA[2] = 2;
    mapA[3] = 3;
    printf("addr A: %x|%x|%x\n", &mapA[1], &mapA[2], &mapA[3]);

    std::map<int, int> mapB = std::move(mapA);
    printf("addr B: %x|%x|%x\n", &mapB[1], &mapB[2], &mapB[3]);

    //������Կ���A size==0�ˣ�˵��mapA�Ѿ�������ˡ�
    printf("A size:%d\n", mapA.size());

    //������Կ���mapA[4]��mapB[4]��ַ�Ѿ���һ���ˣ�˵�������ƶ���ֵ���֮������֮���Ѿ���������ϵ
    mapB[4] = 4;
    printf("new value: %d|%d\n", mapA[4], mapB[4]);
    printf("addr new: %d|%d\n", &mapA[4], &mapB[4]);
}

void TestRefAssign()
{
    /*
    ������ܻ������ʣ�ΪʲôҪ����ô�鷳����ֱ����C++��ͳ����ֵ���ò��Ϳ�������
    �������������Կ�����ͳ����ֵ���õ���A��B����Ӱ�죬���ﾳ��˵��̫���ڰ�A������B��Ȼ����A�ĳ�����
    ����˵�ƶ����岹�������հף�����ľ�������ǳ������ģ�������ƶ���Ϊ�������Ч�ʣ������������ȷ��
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