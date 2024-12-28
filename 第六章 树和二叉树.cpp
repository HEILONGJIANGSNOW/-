#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct BiTNode {
    int value;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

typedef struct Stack {
    BiTree* base;
    BiTree* top;
} Stack;

typedef struct Queue {
    BiTree* elem;
    int front, rear;
} queue;

Stack S;
queue Q;

void InitStack(Stack* S)
{
    S->base = (BiTree*)malloc(sizeof(BiTNode));
    S->top = S->base;
}

void Push(Stack* S, BiTree p)
{
    *S->top++ = p;
}

void Pop(Stack* S, BiTree* p)
{
    if (S->top == S->base) return;
    *p = *(--S->top);
}

int StackEmpty(Stack S)
{
    if (S.top == S.base) return 1;
    else return 0;
}

int GetTop(Stack S, BiTree* p)
{
    if (S.top == S.base) return 0;
    *p = *(S.top - 1);
    return 1;
}

void InitQueue(queue* Q)
{
    Q->elem = (BiTree*)malloc(sizeof(BiTNode));
    Q->front = Q->rear = 0;
}

int QueueEmpty(queue Q)
{
    return Q.front == Q.rear;
}

int EnQueue(queue* Q, BiTree p)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) return -1;
    Q->elem[Q->rear] = p;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 0;
}

int DeQueue(queue* Q, BiTree* p)
{
    if (Q->front == Q->rear) return -1;
    *p = Q->elem[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return 0;
}

BiTree CreateBiTree(BiTree T) {
    /*分配存储空间*/
    T = (BiTNode*)malloc(sizeof(BiTNode));

    int val;
    scanf("%d", &val);
    //如果输入为空，则二叉树是空树
    if (val == -1) {
        T = NULL;
    }
    else {
        if (!T) {
            printf("分配存储空间失败！");
            exit(0);
        }
        T->value = val;//先输入根结点
        T->lchild = CreateBiTree(T->lchild);//递归生成左子树
        T->rchild = CreateBiTree(T->rchild);//递归生成右子树
    }
    return T;
}

void visit(int data) // 访问二叉树节点值
{
    printf("节点的值为：%d ", data);
}

void PreOrder(BiTree T) // 先序遍历
{
    if (T == NULL) return;
    else
    {
        visit(T->value);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) // 中序遍历
{
    if (T == NULL) return;
    else
    {
        InOrder(T->lchild);
        visit(T->value);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) // 后序遍历
{
    if (T == NULL) return;
    else
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T->value);
    }
}

void InOrderTraverse(BiTree T) // 中序遍历的非递归算法
{
    InitStack(&S);        
    while (T || !StackEmpty(S)) { // 栈不为空，或者当前节点不为空
        while (T) {//一路向左
            Push(&S, T);          
            T = T->lchild;      
        }

        if (!StackEmpty(S)) {
            Pop(&S, &T);//一定得是先弹出在访问
            visit(T->value);     
            T = T->rchild; //右树入栈
        }
    }
}

void TransLevel(BiTree T) // 层次遍历的非递归算法
{
    InitQueue(&Q);
    EnQueue(&Q, T);
    while (!QueueEmpty(Q))
    {
        BiTree t;
        DeQueue(&Q, &t);//顺序不能整混，先弹出在访问
        visit(t->value);
        if (t->lchild) EnQueue(&Q, t->lchild);
        if (t->rchild) EnQueue(&Q, t->rchild);
    }
}

int TreeDepth(BiTree T) // 求二叉树的深度(后序遍历)
{
    if (T == NULL) return 0;
    int leftdepth = TreeDepth(T->lchild);
    int rightdepth = TreeDepth(T->rchild);
    return (leftdepth > rightdepth ? leftdepth : rightdepth) + 1;
}

int main()
{
    BiTree T = NULL;
    printf("请输入二叉树，-1表示空：\n");
    T = CreateBiTree(T); // 创建二叉树
    printf("先序遍历：");
    PreOrder(T);
    printf("\n中序遍历：");
    InOrder(T);
    printf("\n后序遍历：");
    PostOrder(T);
    printf("\n中序遍历非递归：");
    InOrderTraverse(T);
    printf("\n层次遍历：");
    TransLevel(T);
    printf("\n二叉树深度：%d", TreeDepth(T));
    return 0;
}