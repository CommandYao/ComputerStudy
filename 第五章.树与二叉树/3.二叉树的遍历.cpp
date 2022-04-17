#include <stdio.h>
#include <malloc.h>
typedef struct BiTNode
{
    char data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef BiTree BElemType;
#pragma region
#define MaxSize 50
typedef struct
{
    BElemType data[MaxSize];
    int front, rear;
} SqQueue;

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
bool EnQueue(SqQueue &Q, BElemType x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}
bool DeQueue(SqQueue &Q, BElemType &x)
{
}

typedef int ElemType;

typedef struct
{
    BElemType data[MaxSize];
    int top;
} SqStack;
bool IsEmpty(SqStack s)
{
    if (s.top == -1)
    {
        return true;
    }
    return false;
}
bool Push(SqStack &S, BElemType x)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}
bool Pop(SqStack &S, BElemType &x)
{
    if (IsEmpty(S))
        return false;
    x = S.data[S.top--];
    return true;
}
void InitStack(SqStack &S)
{
    S.top = -1;
}

#pragma endregion
void Visit(BiTree T)
{
}
// 1.先序遍历
void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        Visit(T);            //访问根结点
        PreOrder(T->lchild); //递归遍历左子树
        PreOrder(T->rchild); //递归遍历右子树
    }
}
// 2.中序遍历
void InOrder(BiTree T)
{
    if (T != NULL)
    {
        InOrder(T->lchild);
        Visit(T);
        InOrder(T->rchild);
    }
}
// 3.后序遍历
void PostOrder(BiTree T)
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        Visit(T);
    }
}
// 1-2.先序遍历的非递归实现
void PreOrder2(BiTree T)
{
    SqStack S;
    S.top = -1;
    InitStack(S);
    BiTree p = T;
    while (p || !IsEmpty(S))
    {
        if (p) //树不空
        {
            Visit(p);
            Push(S, p);
            p = p->lchild;
        }
        else
        {              //树空
            Pop(S, p); //
            p - p->rchild;
        }
    }
}
// 2-2.中序遍历的非递归实现
void InOrder2(BiTree T)
{
    SqStack S;
    InitStack(S);
    BiTree p = T;
    while (p || !IsEmpty(S))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild;
        }
        else
        {
            Pop(S, p);
            Visit(p);
            p = p->rchild;
        }
    }
}
//层次遍历
void LevelOrder(BiTree T)
{
    SqQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T); //根结点入队
    while (!isEmpty(Q))
    {
        DeQueue(Q, p);
        Visit(p);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }
}
typedef struct ThreadNode //线索二叉树的存储结构
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;
void InThread(ThreadTree &p, ThreadTree &pre)
{
    if (p != NULL)
    {
        InThread(p->lchild, pre); //递归,线索化左子树
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) // pre!=NULL就是说pre不是头结点
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}
void CreateInThread(ThreadTree T)
{
    ThreadTree pre = NULL;
    if (T != NULL)
    {
        InThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}
ThreadNode *FirstNode(ThreadNode *p)
{
    while (p->ltag == 0) //中序遍历 左根右 如果有左孩子就继续找左孩子,如果没有,那下一个访问的就是他
    {
        p = p->lchild;
    }
    return p;
}
//求中序线索二叉树中结点p在中序序列下的后继
ThreadNode *NextNode(ThreadNode *p)
{
    if (p->rtag == 1)
        return p->rchild; //如果rtag是1则lchild指向后继
    else
    {
        return FirstNode(p);
    }
}
int main()
{

    BiTree A = (BiTree)malloc(sizeof(BiTree));
    A->data = 'A';
    BiTNode *B = (BiTNode *)malloc(sizeof(BiTNode));
    B->data = 'B';
    BiTNode *C = (BiTNode *)malloc(sizeof(BiTNode));
    C->data = 'C';
    BiTNode *D = (BiTNode *)malloc(sizeof(BiTNode));
    D->data = 'D';
    BiTNode *E = (BiTNode *)malloc(sizeof(BiTNode));
    E->data = 'E';
    A->lchild = B;
    A->rchild = C;
    B->rchild = D;
    C->lchild = E;
    void *pre = A;

    ThreadTree A = (ThreadTree)malloc(sizeof(ThreadNode));
    A->data = 'A';
    ThreadTree B = (ThreadTree)malloc(sizeof(ThreadNode));
    B->data = 'B';
    ThreadTree C = (ThreadTree)malloc(sizeof(ThreadNode));
    C->data = 'C';
    ThreadTree D = (ThreadTree)malloc(sizeof(ThreadNode));
    D->data = 'D';
    ThreadTree E = (ThreadTree)malloc(sizeof(ThreadNode));
    E->data = 'E';
    A->lchild = B;
    A->rchild = C;
    B->rchild = D;
    C->lchild = E;
    // ThreadTree *pre->next = A
    return 0;
}

