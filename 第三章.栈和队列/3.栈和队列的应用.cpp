#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
#define MaxSize 50
typedef struct
{
    ElemType data[MaxSize];
    int top;
} SqStack;
void InitStack(SqStack &S)
{
    S.top = -1;
}
bool StackEmpty(SqStack &S)
{
    if (S.top == -1)
        return true;
    else
        return false;
}
bool Push(SqStack &S, ElemType x)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}
bool Pop(SqStack &S, ElemType &x)
{
    if (StackEmpty(S))
        return false;
    x = S.data[S.top--];
    return true;
}
bool GetTop(SqStack S, ElemType &x)
{
    if (StackEmpty(S))
        return false;
    x = S.data[S.top];
    return true;
}

//栈的链式存储
typedef struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
} * LinkStack;

bool BracektCheck(char *str)
{
    SqStack S;
    ElemType e;
    InitStack(S);
    int i = 0;
    while (str[i] != '\0')
    {
        switch (str[i])
        {
        case '(':
            Push(S, '(');
            break;
        case '[':
            Push(S, '(');
            break;
        case '{':
            Push(S, '(');
            break;
        case ')':
            Pop(S, e);
            if (e != '(')
                return false;
            break;
        case ']':
            Pop(S, e);
            if (e != '[')
                return false;
            break;
        case '}':
            Pop(S, e);
            if (e != '{')
                return false;
            break;
        default:
            break;
        }
        i++;
    }
    if (!StackEmpty(S)) //如果栈中还有括号 说明有括号没匹配上
    {
        return false;
    }
    else
    {
        return true;
    }
}
void SetSeats(char *Seats, int n)
{
    SqStack S;
    char *ResultSeats;
    InitStack(S);
    for (int i = 0; i < n; i++)
    {
        Push(S, Seats[i]);
        if (Seats[i] == 'S')
        {
            ElemType Result;
            Pop(S, Result);
            ResultSeats += Result;
        }
        while (!StackEmpty(S))
        {
           ElemType Result;
            Pop(S, Result);
            ResultSeats += Result;
        }
    }
}
int main()
{
}