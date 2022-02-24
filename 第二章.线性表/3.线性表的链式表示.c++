#include <malloc.h>
#include "stdio.h"
#define MaxSize 12
typedef int ElemType;
//
//!!!!!!!!!!!!
//链表的下标和数组下标统一了(因为有头结点)即 ai就是链表第i个元素

// 2.单链表节点类型的描述
typedef struct LNode
{
    ElemType data;      //数据域
    struct LNode *next; //指针域
} LNode, *LinkList;

//头插法建立单链表
LinkList List_HeadInsert(LinkList &L)
{
    LNode *s;
    int x;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
        scanf("%d", &x);
    }
    return L;
}
//尾插法建立链表
LinkList List_TailInsert(LinkList &L)
{
    int x;
    L = (LinkList)malloc(sizeof(LNode));
    LNode *s, *r = L;
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}
//按序号查找结点值
LNode *GetElem(LinkList L, int i)
{
    if (i < 0)
        return NULL;
    LNode *s = L;
    while (i != 0 && s)
    {
        s = s->next;
        i--;
    }
    return s;
}
LNode *GetElem_2(LinkList L, int i)
{
    int j = 1; //计数器
    LNode *p = L->next;
    if (i < 0)
        return NULL;
    if (i == 0)
        return NULL;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}
//按值查找结点
LNode *LocateElem(LinkList L, ElemType e)
{
    LNode *p = L->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;
}
//插入结点操作
void InsertElem(LinkList &L, int i, ElemType e)
{
    LNode *p = GetElem(L, i - 1); //查到插入结点的前驱结点
    LNode *s;                     //构造新结点
    s->data = e;
    s->next = p->next;
    p->next = s;
}
void DeleteElem(LinkList &L, int i)
{
    LNode *p = GetElem(L, i - 1);
    LNode *q = p->next;
    p->next = q->next;
    free(q);
}
typedef struct DNode
{
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;
//双链表查找
//双链表的插入操作
void InsertDElem(DLinkList &L, DNode &s)
{
    int i = 5; //假设要在第5个元素后插入
    DNode *p = L->next;
    while (i != 0 && p)
    {
        p = p->next;
        i--;
    }
    p->next->prior = &s;
    s.next = p->next;
    p->next = &s;
    s.prior = p;
}
void DeleteDElem()
{
    // q=p->next
    // p->next=q->next
    // q->next->prior=p
    // free(q);
}
//静态链表的结构
typedef struct
{
    ElemType data;
    int next;
} SLinkList[MaxSize];
//应用题
void Print_L(LinkList &L)
{
    while (L->next != NULL)
    {
        L = L->next;
        printf("%d", L->data);
    }
}
// 1.设计递归算法,删除不带头结点的单链表L中所有值为x的结点
void Del_X_NoHead(LinkList &L, ElemType x)
{
    LNode *p;
    if (L == NULL)
        return;
    if (L->data == x)
    {
        p = L;
        L = L->next;
        free(p);
        Del_X_NoHead(L, x);
    }
    else
        Del_X_NoHead(L->next, x);
}

// 2.在带头结点的单链表L中,删除所有值为x的结点
void Del_X_1(LinkList &L, ElemType x)
{
    LNode *p = L->next, *q, *pre = L;
    while (p != NULL)
    {
        if (p->data == x)
        {
            pre->next = p->next;
            q = p;
            pre = p;
            p = p->next;
            free(q);
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}
void Del_X_2(LinkList &L, ElemType x)
{
    LNode *p = L->next, *q = L, *r;
    while (p != NULL)
    {
        if (p->data != x)
        {
            q->next = p;
            q = p;
            p = p->next;
        }
        else
        {
            r = p;
            p = p->next;
            free(r);
        }
        q->next = NULL;
    }
}
// 3.L为带头结点的单链表,反向输出每个结点的值
//单链表反向输出,可以考虑递归
void Show_reverse(LinkList &L)
{
    LNode *p = L->next, *q, *pre = NULL;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        q->next = pre;
        pre = q;
    }
    L->next = pre;
    while (L->next != NULL)
    {
        L = L->next;
        printf("%d", L->data);
    }
}
// 4.带头结点的单链表L中删除最小值的高效算法(最小值唯一)
void Del_Min(LinkList &L)
{
    LNode *pre = L, *q = L->next, *preMin;
    ElemType Min = q->data;
    while (q->next != NULL)
    {
        pre = q;
        q = q->next;
        if (Min > q->data)
        {
            preMin = pre;
            Min = q->data;
        }
    }
    LNode *s = preMin->next;
    preMin->next = s->next;
    free(s);
}
// 5-1.逆转链表
//通过调转指针
void Reverse_1(LinkList &L)
{
    LNode *p = L->next, *q, *pre = NULL;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        q->next = pre;
        pre = q;
    }
    L->next = pre;
}
// 5-2通过头插法重拼元素
void Reverse_2(LinkList &L)
{
    LNode *p = L->next, *r;
    L->next = NULL;
    while (p != NULL)
    {
        p->next = L->next;
        L->next = p;
        r = p->next;
        p = r;
    }
}
// 6.使元素有序递增
void SortAscend(LinkList &L)
{
    LNode *p = L->next, *pre, *r = p->next; // r是第一个数字
    p->next = NULL;
    p = r; // p是第一个数字
    while (p)
    {
        pre = L;
        while (pre->next && pre->next->data < p->data)
        {
            pre = pre->next;
        }
        r = p;
        p = p->next;
        r->next = pre->next;
        pre->next = r;
    }
    int a = 0;
}
// 7.删除介于ab之间的值
void Del_a_b(LinkList &L, int a, int b)
{
    LNode *p = L->next;
    LNode *pre = L;
    while (p != NULL)
    {
        if (p->data > a && p->data < b)
        {
            pre->next = p->next;
            free(p);
            p = pre->next;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}
// 8.找出两个表的公共结点
LNode *Find_SameNode(LinkList L1, LinkList L2)
{
    LNode *p = L1->next;
    LNode *q = L2->next;
    while (p != NULL)
    {
        while (q != NULL)
        {
            if (q == p)
                return q;
            q = q->next;
        }
        p = p->next;
    }
    return NULL;
}
int main()
{
    LinkList L = (LinkList)malloc(sizeof(LNode));
    List_HeadInsert(L);
    // Show_reverse(L);
    SortAscend(L);
    // Show_reverse_1(L);
    // Del_Min(L);
    // Show_reverse(L);
    return 0;
    // SeqList L;
    // 3.C的初始动态分配语句为
    // L.data = (ElemType *)malloc(sizeof(ElemType) * InitSize);
    // 4.C++的初始动态分配语句为
    // L.data = new ElemType[InitSize];

    // SqlList L2 = {{1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6}, 12};
    // Del_Duplicate(L2);
}