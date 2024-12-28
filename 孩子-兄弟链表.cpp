#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct BiTnode {
	char data;
	BiTnode* lchild;
	BiTnode* rchild;
}BiTree;


BiTree* Creatnode(char data) {
	BiTree* newnode = (BiTree*)malloc(sizeof(BiTree));
	newnode->data = data;
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	return newnode;
}



void visit(char data) {
	printf("%c\n", data);
}

void preorder(BiTree* t, void(*visit)(char)) { // 先序递归遍历二叉树
	if (t) {
		visit(t->data);
		preorder(t->lchild, visit);
		preorder(t->rchild, visit);
	}
}

BiTree* CreatTree(char datas[], int degrees[], int n) {
	if (!n)return NULL;
	BiTree* root = Creatnode(datas[0]);
	BiTree** queue = (BiTree**)malloc(n * sizeof(BiTree*));//因为要层次遍历每个元素，所以要队列存
	int front = 0, rear = 0;//维护两个指针来标记加入队列位置和建树位置
	queue[rear] = root;
	rear++;
	int index = 1;
	for (int i = 0; i < n && index < n; i++) {
		BiTree* parent = queue[front];
		front++;
		int degree = degrees[i];
		BiTree* frontchild = NULL;
		for (int j = 0; j < degree && index < n; j++) {
			BiTree* newnode = Creatnode(datas[index]);
			index++;
			if (!j) {
				parent->lchild = newnode;//左孩子，第一个出度必须是左孩子，因为该节点的兄弟应该在它孩子的右边
			}
			else {
				frontchild->rchild = newnode;//右兄弟
			}
			frontchild = newnode;
			queue[rear] = newnode;
			rear++;
		}
	}
	free(queue);
	return root;
}


int main() {
	char datas[100];
	int degrees[100];
	int n;
	int i = 0, j = 0;
	printf("输入节点个数\n");
	scanf("%d", &n);
	getchar();
	printf("输入各个节点的值\n");
	for (int i = 0; i < n; i++) {
		scanf("%c", &datas[i]);
	}
	getchar();
	printf("输入各个节点的度(依次输入)\n");
	for (int j = 0; j < n; j++) {
		scanf("%d", &degrees[j]);
	}

	BiTree* t = CreatTree(datas, degrees, n);
	preorder(t, visit);
}