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
//尾插法建立链表 !!!尾插法建立链表 一定要有一个额外的指针指向表尾元素,不能用L指向表尾元素,会破坏
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
LinkList List_TailInsert(LinkList &L, int x[], int length)
{
    LNode *s, *r = L;
    for (int i = 0; i < length; i++)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}
LinkList List_TailInsert(LinkList &L, int x)
{
    LNode *s, *r = L;
    while (r->next)
        r = r->next;
    s = (LNode *)malloc(sizeof(LNode));
    s->data = x;
    r->next = s;
    r = s;
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
LNode *Find_SameNode_1(LinkList L1, LinkList L2)
{
    LNode *p = L1->next;
    LNode *q;
    while (p != NULL)
    {
        q = L2->next;
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
int Length(LinkList L)
{
    int i = 0;
    while (L->next)
    {
        i++;
        L = L->next;
    }
    return i;
}
LNode *Find_SameNode_2(LinkList L1, LinkList L2)
{
    int Len1 = Length(L1);
    int Len2 = Length(L2);
    LinkList longList;
    LinkList shortList;
    int dist = Len1 > Len2 ? Len1 - Len2 : Len2 - Len1;
    if (Len1 > Len2)
    {
        longList = L1;
        shortList = L2;
    }
    else
    {
        longList = L2;
        shortList = L1;
    }
    while (dist--)
    {
        longList = longList->next;
    }
    while (longList != NULL)
    {
        if (longList = shortList)
            return longList;
        else
        {
            longList = longList->next;
            shortList = shortList->next;
        }
    }
    return NULL;
}
// 9.带头结点的链表，按递增顺序输出元素，并释放所在节点(不允许使用数组作为辅助空间)
void PrintNodeOrder(LinkList L)
{
    LNode *pre = L->next, *MinPre = L, *p, *Min;
    while (L->next)
    {
        pre = L->next;
        p = pre->next;
        MinPre = L;
        while (p)
        {
            if (MinPre->next->data > p->data)
                MinPre = pre;
            pre = p;
            p = p->next;
        }
        printf("%d", MinPre->next->data);
        Min = MinPre->next;
        MinPre->next = Min->next;
        free(Min);
    }
}
// 10.把A B量表拆开,A保留奇数元素,B保留偶数元素
void Split(LinkList &L)
{
    LinkList LA, LB;
    LA = (LinkList)malloc(sizeof(LNode));
    LB = (LinkList)malloc(sizeof(LNode));
    LA->next = NULL;
    LB->next = NULL;
    int Len = Length(L);
    for (int i = 0; i < Len; i++)
    {
        if (i % 2 == 0)
            LA = List_TailInsert(LA, L->next->data);
        else
            LB = List_TailInsert(LB, L->next->data);
        L = L->next;
    }
}
// 11.

// 12.递增有序线性表,删除重复元素
void Delete_Order_Duplicate(LinkList &L)
{
    LNode *p = L->next, *q, *r;
    q = p->next;
    while (q)
    {
        if (q->data == p->data)
        {
            p->next = q->next;
            r = q;
            q = q->next;
            free(r);
        }
        else
        {
            p = p->next;
            q = q->next;
        }
    }
}
// 13.合并两个有序递增的单链表,并用原来的结点保存
void Merge_Order_InSame(LinkList &La, LinkList &Lb)
{
    LNode *pLa = La->next, *pLb = Lb->next, *p, *q, *r;
    La->next = NULL;
    q = La;
    p = La->next;
    while (pLa != NULL && pLb != NULL)
    {

        if (pLa->data < pLb->data)
        {
            p = pLa;
            r = pLa;
            pLa = pLa->next;
        }
        else
        {

            p = pLb;
            r = pLb;
            pLb = pLb->next;
        }
        q->next = p;
        q = q->next;
    }
    if (pLa)
    {
        q->next = pLa;
    }
    else
    {
        La->next = pLb;
    }
    free(Lb);
}
int main()
{
    // LinkList L = (LinkList)malloc(sizeof(LNode));
    //  List_HeadInsert(L);
    //  Show_reverse(L);
    //  SortAscend(L);
    //  Show_reverse_1(L);
    //  Del_Min(L);
    //  Show_reverse(L);
    //  return 0;
    //  SeqList L;
    //  3.C的初始动态分配语句为
    //  L.data = (ElemType *)malloc(sizeof(ElemType) * InitSize);
    //  4.C++的初始动态分配语句为
    //  L.data = new ElemType[InitSize];

    // SqlList L2 = {{1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6}, 12};
    // Del_Duplicate(L2);
    // PrintNodeOrder(L);
    // Split(L);
    // Delete_Order_Duplicate(L);
    LinkList La = (LinkList)malloc(sizeof(LNode));
    LinkList Lb = (LinkList)malloc(sizeof(LNode));
    int x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int y[] = {1, 2, 2, 5, 5, 6, 6, 8, 8, 8};
    List_TailInsert(La, x, 10);
    List_TailInsert(Lb, y, 10);
    Merge_Order_InSame(La, Lb);
}