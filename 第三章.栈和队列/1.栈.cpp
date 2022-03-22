typedef char ElemType;
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

int main()
{
    return 0;
}
// 4.单链表判断是否中心堆成
typedef struct LNode
{
    char data;
    LNode *next;
} LNode, *LinkList;
bool IsSymmetry(LinkList L, int n)
{
    SqStack s;
    InitStack(s);
    LNode *p = L->next;
    for (int i = 0; i < n / 2; i++)
    {
        Pop(s, p->data);
        p = p->next;
    }
    if (n % 2 == 1)
        p = p->next;
    while (p)
    {
        ElemType t;
        Pop(s, t);
        if (p->data != t)
            return false;
    }
    return true;
}
// 5.共享栈设计进栈退栈方法
typedef int ElemType;
typedef struct
{
    ElemType stack[MaxSize];
    int top[2];
} stk;
bool Push_5(stk &s, ElemType x, int i) // i说明进哪个栈
{
    if (s.top[1] - s.top[0] == 1)
    {
        return false; //栈满
    }
    if (i == 0)
    {
        s.stack[++s.top[0]] = x;
        return true;
    }
    else if (i == 1)
    {
        s.stack[--s.top[1]] = x;
        return true;
    }
    else
    {
        return false; //栈错
    }
}
ElemType Pop_5(stk &s, ElemType &x, int i)
{
    if (s.top[1] - s.top[0] == 1)
    {
        return false; //栈满
    }
    if (i != 0 && i != 1)
    {
        return false;
    }
    else if (i = 0)
    {
        if (s.top[0] == -1)
        {
            return false;
        }
        x = s.stack[s.top[0]--];
    }
    else
    {
        if (s.top[1] == MaxSize)
        {
            return false;
        }
        x = s.stack[s.top[1]--];
    }
    return true;
}
