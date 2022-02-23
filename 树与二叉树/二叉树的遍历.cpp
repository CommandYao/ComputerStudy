#include <stdio.h>
typedef int ElemType;
typedef struct BiTNode
{
    ElemType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
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
//1.先序遍历
void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        //visit(T);//访问根结点
        PreOrder(T->lchild); //递归遍历左子树
        PreOrder(T->rchild); //递归遍历右子树
    }
}
//2.中序遍历
void InOrder(BiTree T)
{
    if (T != NULL)
        PostOrder(T->lchild);
    //visit(T);
    PostOrder(T->rchild);
}
//3.后序遍历
void PostOrder(BiTree T)
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        //visit(T);
    }
}
//1-1.先序遍历的非递归实现
void PreOrder2(BiTree T)
{
    SqStack S;
    InitStack(S);
    BiTree p = T;
    while (p || !IsEmpty(S))
    {

    }
}
int main()
{
    return 0;
}