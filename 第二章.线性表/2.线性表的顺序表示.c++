#include <malloc.h>
#include "stdio.h"
#include <iostream>
using namespace std;

// 1.线性表(静态分配)
#define MaxSize 100 //顺序表的最大长度
typedef int ElemType;
typedef struct
{
    ElemType data[MaxSize];
    int length; //顺序表的当前长度
} SqlList;
// 2.线性表(动态分配)
#define InitSize 100
typedef struct
{
    ElemType *data;
    int MaxSize2, length;
} SeqList;

bool ListInsert(SqlList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i, j--;)
    {
        L.data[j] = L.data[j - 1]; // L.data[j]是a(j+1)
                                   // L.data[从0开始]
    }
    L.data[i - 1] = e; //插到第i个位置 就是插入数组第[i-1]个位置
    L.length++;
    return true;
}
bool ListDelete(SqlList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return false;
    e = L.data[i - 1];
    for (int j = i; j < L.length - 1; j++)
    {
        L.data[j] = L.data[j + 1];
    }
    L.length--;
    return true;
}
int LocateElem(SqlList L, ElemType e)
{
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
            return i + 1;
    }
    return 0;
}
//综合应用题
// 1.删除表中唯一的最小元素，并返回元素的值,空出的位置用最后一个元素填补
bool Del_Min(SqlList &L, ElemType &value)
{
    if (L.length == 0)
        return false;
    int MinIndex = 0;
    for (int i = 1; i < L.length; i++)
    {
        if (L.data[i] < L.data[MinIndex])
            MinIndex = i;
    }
    L.data[MinIndex] = L.data[L.length - 1];
    value = L.data[MinIndex];
    return true;
}
// 2.将顺序表L的所有元素逆置，且算法空间复杂度为1
void Reverse(SqlList &L)
{
    for (int i = 0; i < L.length / 2; i++)
    {
        int temp = L.data[i];
        L.data[i] = L.data[L.length - i - 1];
        L.data[L.length - i - 1] = temp;
    }
}
// 3.长度为n的顺序表L,删除线性表中所有值为x的数据元素,要求时间复杂度O(n),空间复杂度O(1)
void Del_ValueX(SqlList &L, ElemType x)
{
    int j = 0;
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] != x)
        {
            L.data[j++] = L.data[i];
        }
    }
    L.length = j;
}
void Del_ValueX_2(SqlList &L, ElemType x)
{
    int i = 0, k = 0;
    while (i < L.length)
    {
        if (L.data[i] == x)
        {
            k++;
        }
        else
        {
            L.data[i - k] = L.data[i];
        }
        i++;
    }
    L.length = L.length - k;
}
// 4.有序表中删除值s与t之间的值(包含s和t,s<t),若st不合理或顺序表为空,显示错误
bool Del_Bet_st_1(SqlList &L, ElemType s, ElemType t) //逐个排查删除，可以用在有序表可以用在无序表
{
    if (s >= t)
        return false;
    if (L.length == 0)
        return false;
    int j = 0;
    for (int i = 1; i < L.length; i++)
    {
        if (L.data[i] < s || L.data[i] > t)
        {
            L.data[j++] = L.data[i];
        }
    }
    L.length = j;
    return true;
}
bool Del_Bet_st_2(SqlList &L, ElemType s, ElemType t) //找到最小最大值，统一删除，仅可用在有序表
{
    int i, j;
    for (i = 0; L.data[i] < s && i < L.length; i++)
        ;
    for (j = i; L.data[j] <= t && j < L.length; j++)
        ;
    for (; j < L.length; j++)
    {
        L.data[i++] = L.data[j];
    }
    L.length = L.length - (j - i + 1);
    return true;
}
// 5.可以同上Del_Bet_St_1
// 6.从有序表中删除重复值
void Del_Duplicate(SqlList &L)
{
    int j = 0;
    for (int i = 1; i < L.length; i++)
    {
        if (L.data[i] != L.data[j])
        {
            L.data[++j] = L.data[i];
        }
    }
    L.length = j + 1;
}
void Del_Duplicate_2(SqlList &L) //能成功但是不好的方法
{
    int k = 0;
    for (int i = 0; i < L.length; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (L.data[i] == L.data[j])
            {
                break;
            }
        }
        L.data[k++] = L.data[i];
    }
    L.length = k;
}
// 7.将两个有序表顺序表合并为一个新的有序顺序表,并由函数返回结果顺序表
void Merge(SqlList &La, SqlList &Lb, SqlList &result)
{
    int k = 0, i, j;
    for (i = 0, j = 0; i < La.length && j < Lb.length;)
    {
        if (La.data[i] < Lb.data[j])
            result.data[k++] = La.data[i++];
        else
            result.data[k++] = Lb.data[j++];
    }
    while (i < La.length)
        result.data[k++] = La.data[i++];
    while (j < Lb.length)
        result.data[k++] = Lb.data[j++];
    result.length = La.length + Lb.length;
}
// 8.将数组A[m+n]转换为A[n+m] 即(a1,a2...am,b1,b2...bn)转换为(b1,b2...bn,a1,a2...an)
void ReverseBO(SqlList &L, ElemType Begin, ElemType Over)
{
    for (int k = Begin - 1; k < (Over - Begin + 1) / 2; k++)
    {
        ElemType temp = L.data[k];
        L.data[k] = L.data[Over - 1 - k];
        L.data[Over - 1 - k] = temp;
    }
}
void ReverseMn(SqlList &L)

{
    int m = 5;
    int n = 10;
    ReverseBO(L, 1, m);
    ReverseBO(L, m + 1, n);
    ReverseBO(L, 1, m + n);
}
// 9.有序递增表,查找x,若找到和后继元素交换,找不到则插入,保持递增
void Insert_X_youxu(SqlList &L, ElemType x) //普通查找
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.data[i] == x)
        {
            L.data[i] = L.data[i + 1];
            L.data[i + 1] = x;
            L.length--;
        }
        else if (L.data[i] > x)
        {
            for (int j = L.length; j > i; j--)
            {
                L.data[j] = L.data[j - 1];
            }
            L.data[i]=x;
            L.length++;
            break;
        }
    }
    int j=0;
}
void Insert_X_youxu_2(SqlList &L, ElemType x){}//折半查找
// 10.
int main()
{
    SqlList Shunxubiao = {{
                              1,
                              3,
                              8,
                              5,
                              2,
                              1,
                              5,
                              2,
                              3,
                              1,
                          },
                          10};
    SqlList Youxubiao = {{
                             1,
                             1,
                             2,
                             2,
                             2,
                             3,
                             4,
                             5,
                             5,
                             5,
                             6,
                             6,
                             7,
                             8,
                             9,
                             10,
                         },
                         16};
    SqlList Youxubiao_2 = {{3, 3, 4, 5, 6, 6, 6, 8, 8, 9, 10, 11, 12, 13}, 14};
    // Del_ValueX(Shunxubiao,1);
    // Del_ValueX_2(Shunxubiao,1);
    // Del_Bet_st_1(Youxubiao, 3, 6);
    // Del_Bet_st_2(Youxubiao, 3, 6);
    SqlList Result = {{}, 0};
    // Merge(Youxubiao, Youxubiao_2, Result);
    // ReverseBO(Youxubiao, 1, Youxubiao.length);
    Insert_X_youxu(Youxubiao_2, 7);
}