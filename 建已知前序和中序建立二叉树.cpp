#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct BiTNode {
    int data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
} *BiTree;

void visit(int data) {
    printf("%d\n", data);
}

void preorder(BiTree t, void(*visit)(int)) { // 先序递归遍历二叉树
    if (t) {
        visit(t->data);
        preorder(t->lchild, visit);
        preorder(t->rchild, visit);
    }
}

BiTree build(ElemType pre[], ElemType in[], int length) {
    if (length <= 0) return NULL;

    BiTree root = (BiTree)malloc(sizeof(struct BiTNode));
    root->data = pre[0];
    root->lchild = NULL;
    root->rchild = NULL;

    int index = 0;
    while (index < length && in[index] != root->data) {//直到找到根节点
        index++;
    }

    root->lchild = build(pre + 1, in, index);//分别对左右建树
    root->rchild = build(pre + index + 1, in + index + 1, length - 1 - index);

    return root;
}

int main() {
    int pre[5] = { 1, 2, 4, 5, 3 };
    int in[5] = { 4, 2, 5, 1, 3 };

    BiTree t = build(pre, in, 5);
    preorder(t, visit);

    return 0;
}
