#define MaxSize 50
#include <malloc.h>
#include "stdio.h"
typedef int ElemType;
typedef struct
{
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

bool EmptyQueue(SqQueue &Q)//非循环队列判断空
{
    if (Q.front == Q.rear == 0) //判断顺序队列是否为空,必须有==0,否则进队出队头尾指针会在尾指针处相等
        return true;
    else
        return false;
}
//由于队头队尾的位置会相对移动,所以会存在"假溢出"等现象,常用循环队列来解决
//循环队列
void InitQueue(SqQueue &Q)
{
    Q.rear = Q.front = 0;
}
bool isEmpty(SqQueue &Q)
{
    if (Q.rear == Q.front)
        return true;
    else
        return false;
}
bool EnQueue(SqQueue &Q, ElemType x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}
bool DeQueue(SqQueue &Q, ElemType &x)
{
    if (Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}
//队列的链式存储
typedef struct LinkNode //队列的结点
{
    ElemType data;
    struct LinkNode *next;
} LinkNode;
typedef struct //队列 就是在结点上多了头尾指针 结点是自己链在一起的
{
    LinkNode *front, *rear;
} LinkQueue;
void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (LinkNode *)malloc(sizeof(LinkNode));//为什么写右边,因为建立头结点
    Q.front->next = NULL;
}
bool IsEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}
void EnQueue(LinkQueue &Q, ElemType x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(x));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}
bool DeQueue(LinkQueue &Q, ElemType &x)
{
    if (IsEmpty(Q))
        return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next; // Q.front指向头结点
    if (Q.rear == p)
        Q.rear = Q.front; //若队列中只有一个结点,删除后变空
    free(p);
    return true;
}
int main()
{
    return 0;
}
// 1.编写一个结构,tag=0或1来表示队空和队满
typedef struct
{
    ElemType data;
    LinkNode1 *next;
} LinkNode1;
typedef struct
{
    ElemType data[MaxSize];
    int top = -1;
    int tag = 0;
} Queue1;
