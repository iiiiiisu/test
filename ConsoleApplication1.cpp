// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
	int flag;
};

int PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
int InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType e);
BinTree Delete(BinTree BST, ElementType e);
Position Find(BinTree BST, ElementType e);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
int* createList(int *list, int length);
int* randomSort(int *list, int length);
int printBinaryTree(int length);
int clearFile();
int main()
{
	int i;
	int* list = NULL;
	//int list[20] = {11, 9, 17, 18, 7, 2, 15, 6, 14, 0, 10, 4, 12, 13, 8, 5, 3, 19, 16, 1 };
	int length = 45;
	BinTree bt = NULL;
	list = createList(list, length);
	list = randomSort(list, length);
	for (i = 0; i < length; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
	printf("start insert!\n");
	for (i = 0; i < length; i++) {
		bt = Insert(bt, list[i]);
	}
	printf("end insert!\n");
	clearFile();
	PreorderTraversal(bt);
	system("pause");
	InorderTraversal(bt);
	system("pause");
	printBinaryTree(length);
	system("pause");
	return 0;
}

int* createList(int *list, int length)
{
	int i = 0;
	if (list) {
		free(list);
	}
	list = (int*)malloc(sizeof(int)*length);
	for (; i < length; i++) {
		list[i] = i;
	}
	return list;
}

int* randomSort(int *list, int length)
{
	int i = 0;
	int a = 0, b = 0;
	int temp = 0;
	srand((unsigned)time(NULL));
	for (; i < length; i++) {
		a = rand();
		a = a % (length*length);
		b = a % length;
		a = (int)a / length;
		temp = list[a];
		list[a] = list[b];
		list[b] = temp;
	}
	return list;
}

BinTree Insert(BinTree BST, ElementType e)
{
	BinTree p = BST;
	BinTree pre_p = p;
	BinTree temp_p = NULL;
	// 如果树为空
	if (!p) {
		p = (BinTree)malloc(sizeof(struct TNode));
		p->Data = e;
		p->Left = NULL;
		p->Right = NULL;
		p->flag = 0;
		return p;
	}
	// 树不为空时
	while (p) {
		if (!p) {
			break;
		}
		pre_p = p;
		if (e == p->Data) {
			printf("该值已存在！\n");
			return BST;
		}
		else if (e > p->Data) {
			p->flag += 1;
			if (p->flag == 2) {
				p->Left = Insert(p->Left, p->Data);
				temp_p = FindMin(p->Right);
				if (e == temp_p->Data) {
					printf("已存在该值！");
					return BST;
				}
				else if (e < temp_p->Data) {
					p->Data = e;
					p->flag = 0;
					return BST;
				}
				else if (e > temp_p->Data) {
					p->Data = temp_p->Data;
					p->Right = Delete(p->Right,temp_p->Data);
					p->flag = 0;
				}
			}
			p = p->Right;
		}
		else if (e < p->Data) {
			p->flag -= 1;
			if (p->flag == -2) {
				p->Right = Insert(p->Right, p->Data);
				temp_p = FindMax(p->Left);
				if (e == temp_p->Data) {
					printf("已存在该值！");
					return BST;
				}
				else if (e > temp_p->Data) {
					p->Data = e;
					p->flag = 0;
					return BST;
				}
				else if (e < temp_p->Data) {
					p->Data = temp_p->Data;
					p->Left = Delete(p->Left,temp_p->Data);
					p->flag = 0;
				}
			}
			p = p->Left;
		}
	}
	if (e < pre_p->Data) {
		p = pre_p;
		p->Left = (BinTree)malloc(sizeof(struct TNode));
		p = p->Left;
	}
	if (e > pre_p->Data) {
		p = pre_p;
		p->Right = (BinTree)malloc(sizeof(struct TNode));
		p = p->Right;
	}
	p->Data = e;
	p->Left = NULL;
	p->Right = NULL;
	p->flag = 0;
	return BST;
}

BinTree Delete(BinTree BST, ElementType e)
{
	BinTree p = BST;
	BinTree pre_p = p;
	BinTree temp_p = NULL;

	if (!p) {
		printf("没有这个元素\n");
		return BST;
	}
	while (p) {
		if (e > p->Data) {
			p->flag -= 1;
			if (p->flag == -2) {
				p->Right = Insert(p->Right, p->Data);
				temp_p = FindMax(p->Left);
				p->Data = temp_p->Data;
				Delete(p->Left, temp_p->Data);
				p->flag = 0;
			}
			pre_p = p;
			p = p->Right;
		}
		else if (e < p->Data) {
			p->flag += 1;
			if (p->flag == 2) {
				p->Left = Insert(p->Left, p->Data);
				temp_p = FindMin(p->Right);
				p->Data = temp_p->Data;
				Delete(p->Right, temp_p->Data);
				p->flag = 0;
			}
			pre_p = p;
			p = p->Left;
		}
		else if (e == p->Data) {
			break;
		}
	}
	if (!p) {
		printf("没有这个元素\n");
		return BST;
	}
	if (!p->Left && !p->Right) {
		if (pre_p == p) {
			free(p);
			return NULL;
		}
		else if (pre_p->Left == p) {
			pre_p->Left = NULL;
		}
		else if (pre_p->Right == p) {
			pre_p->Right = NULL;
		}
		free(p);
	}
	else if (!p->Left) {
		p->Data = p->Right->Data;
		free(p->Right);
		p->Right = NULL;
		p->flag = 0;
	}

	else if (!p->Right) {
		p->Data = p->Left->Data;
		free(p->Left);
		p->Left = NULL;
		p->flag = 0;
	}
	else if (p->flag >= 0) {
		temp_p = FindMin(p->Right);
		p->Data = temp_p->Data;
		p->Right = Delete(p->Right, temp_p->Data);
		p->flag = 0;
	}
	else {
		temp_p = FindMax(p->Left);
		p->Data = temp_p->Data;
		p->Left = Delete(p->Left, temp_p->Data);
		p->flag = 0;
	}
	return BST;
}

Position Find(BinTree BST, ElementType e)
{
	return NULL;
}

Position FindMin(BinTree BST)
{
	BinTree p = BST;
	if (!p) {
		return NULL;
	}
	while (p->Left) {
		p = p->Left;
	}
	return p;
}

Position FindMax(BinTree BST) {
	BinTree p = BST;
	if (!p) {
		return NULL;
	}
	while (p->Right) {
		p = p->Right;
	}
	return p;
}

int PreorderTraversal(BinTree BT)
{	
	FILE *fp;
	if(BT){
		fopen_s(&fp, "PreorderData.txt", "a");
		if (fp == NULL) {
			printf("The file can not be opened.\n");
			return 1;
		}
		fprintf(fp, "%d ", BT->Data);
		fclose(fp);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
	return 0;
}

int InorderTraversal(BinTree BT)
{
	FILE *fp;
	if (BT) {
		InorderTraversal(BT->Left);
		fopen_s(&fp, "InorderData.txt", "a");
		if (fp == NULL) {
			printf("The file can not be opened.\n");
			return 1;
		}
		fprintf(fp, "%d ", BT->Data);
		fclose(fp);
		InorderTraversal(BT->Right);
	}
	return 0;
}

int printBinaryTree(int length)
{
	FILE *fp = NULL;
	int ch, i = 0, j = 0, k=0, temp=0, count=0;				//临时变量
	int pos1 = 0, pos2 = 0, pos3 = 0;				
	//存放位置，1为输出行已存在字符数，2为输出行距离前一个字符距离，3为当前输出字符在list中的序号

	int num = 2, sum = 0;					//num计算层数，sum计算最后一层路径
	int depth = 0, depth_t = 0;				//depth记录总层数-1，depth_t记录当前遍历层数
	int *list = (int*)malloc(sizeof(int)*length);
	int *list1 = NULL;
	while (num - 1 <= length) {
		depth += 1;
		num = num * 2;
	}
	list1 = (int*)malloc(sizeof(int)*(depth + 2));
	fopen_s(&fp, "PreorderData.txt", "r");
	if (fp == NULL) {
		printf("The file can not be opened.\n");
		return 1;
	}
	list[0] = 0;
	do {
		ch = fgetc(fp);
		if (ch == ' ') {
			i++;
			list[i] = 0;
		}
		else {
			list[i] = list[i] * 10 + ch -48;
		}
	} while (ch != EOF);
	for (i = 0; i < length; i++) {
		if (i == 0) {
			pos3 = i;
		}
		else if (depth_t == 0) {
			list1[0] = 0;
			depth_t = 1;
		}
		else {
			for (j = depth_t; j > 0; j--) {
				if(list1[j-1] == 0){
					list1[j - 1] = 1;
					break;
				}
				else {
					list1[j - 1] = 0;
				}
			}
			if (j == 0 && list1[0] == 0) {
				list1[depth_t] = 0;
				depth_t += 1;
				printf("\n");
				pos1 = 0;
			}
		}
		if (depth_t < depth) {
			for (j = 0; j < depth_t; j++) {
				if (j == 0) {
					pos3 = 0;
					num = 0;
				}
				if (list1[j] == 0) {
					pos3 += 1;;
					num += 1;
				}
				else if (list1[j] == 1) {
					pos3 = list[pos3] + num +1;
				}
			}
		}
		else {
			for (j = 0; j < depth_t; j++) {
				if (j == 0) {
					pos3 = 0;
					num = 0;
					sum = 0;
				}
				temp = pow(2, depth - j - 1) - 1;
				if (i > pow(2, depth) -1) {
					count = i + 1- pow(2,depth);
				}
				if (list[pos3] <= sum + temp + count) {
					if (list1[j] == 0) {
						for (k = j+1; k < depth_t; k++) {
							list1[k] = 0;
						}
					}
					list1[j] = 1;
					sum += temp + 1;
				}
				if (list1[j] == 0) {
					pos3 += 1;;
					num += 1;
				}
				else if (list1[j] == 1) {
					pos3 = list[pos3] + num + 1;
				}
				if (j+2 == depth) {
					if (list[pos3] + num + 1 - pos3 == 1) {

					}
				}
			}
		}
		pos2 = list[pos3] - pos1;
		for (j = 0; j < pos2; j++)
			printf("  ");
		printf("%2d", list[pos3]);
		pos1 = pos1 + pos2 + 1;
		if (i == 0) {
			pos1 = 0;
			printf("\n");
		}
;	}
	printf("\n");
	fclose(fp);
	return 0;
}

int clearFile()
{
	FILE *fp1 = NULL, *fp2 = NULL;
	fopen_s(&fp1, "PreorderData.txt", "w");
	fopen_s(&fp2, "InorderData.txt", "w");
	fprintf(fp1, "");
	fprintf(fp2, "");
	fclose(fp1);
	fclose(fp2);
	return 0;
}
