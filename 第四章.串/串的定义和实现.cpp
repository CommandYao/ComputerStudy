#include <stdio.h>
#define MAXLEN 255 //定长顺序存储
typedef struct
{
    char ch[MAXLEN];
    int length;
} SString;
typedef struct //堆分配存储
{
    char *ch; //按串长度分配存储区,ch指向串的基地址
    int length;
} HString;
void SubString(SString &sub, SString S, int pos, int len)
{
}
int StrLength(SString S) {}
int StrCompare(SString S, SString T) {}
int Index(SString S, SString T)
{
    int i = 1, n = StrLength(S), m = StrLength(T); //默认n>m
    while (i <= n - m + 1)
    {
        SString sub;
        SubString(sub, S, i, m);
        if (StrCompare(S, sub) != 0)
            i++;
        else
            return i;
    }
    return 0;
}
//简单的模式匹配
int Index(SString S, SString T)
{
    int i = 1, j = 1;
    while (i < S.length && j < T.length)
    {
        if (S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;//i-j+1回到开始比较的字符再+1到下一个字符
            j = 1;
        }
    }
    if (j > T.length)
        return i - T.length;
    else
        return 0;
}
int main()
{
    return 0;
}