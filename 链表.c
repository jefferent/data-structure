/*
	目的：研究链表，可排序（难点），可清空链表
	时间：2015年7月16日
	By 李瑞明
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0

typedef char BOOL;				//C语言不直接支持BOOL类型，故将char转定义为BOOL

typedef struct Node				//链表节点
{
	int data;					//数据域
	struct Node * Next;			//指针域
}NODE, *PNODE;

PNODE initList(void);			//定义一个新的空链表
void appendList(PNODE);			//追加链表节点
void sortList(PNODE);			//对链表排序（按从小到大顺序）
void clear(PNODE);				//清空链表的数据
BOOL isEmpty(PNODE);			//检查链表是否为空
void traverseList(PNODE);		//遍历链表

int main(void)
{
	PNODE Head;

	//将想要使用的功能（即函数）写进main函数即可，以下为示例
	Head = initList();
	appendList(Head);
	traverseList(Head);
	sortList(Head);
	traverseList(Head);
	clear(Head);
	traverseList(Head);

	return 0;
}

PNODE initList(void)
{
	PNODE Head;

	if (NULL == (Head = (PNODE)malloc(sizeof(NODE))))
	{
		printf("内存不足，创建链表失败！\n");
		exit(-1);
	}
	Head->Next = NULL;

	return Head;
}

void appendList(PNODE Head)
{
	PNODE Tail, New;
	int i;
	int len;

	Tail = Head;
	
	printf("输入节点的数量：\n");
	scanf("%d", &len);
	for (i = 0; i < len; i++)
	{
		if (NULL == (New = (PNODE)malloc(sizeof(NODE))))
		{
			printf("内存不足，创建链表失败！\n");
			exit(-1);
		}
		scanf("%d", &New->data);
		Tail->Next = New;
		Tail = New;
		New->Next = NULL;
	}
	
	return;
}

void sortList(PNODE Head)
{
	PNODE p;			//当前节点
	PNODE Prep;			//当前节点的前一个节点
	PNODE Temp;			//交换用的临时变量
	PNODE Tail;			//尾节点
	
	Tail = NULL;
	while (Head->Next != Tail)
	{
		Prep = Head;
		p = Head->Next;
		while (p->Next != Tail)
		{
			if (p->data > p->Next->data)
			{
				Temp = p->Next;
				Prep->Next = p->Next;
				p->Next = p -> Next->Next;
				Prep->Next->Next = p;
				p = Temp;
			}
			Prep = Prep->Next;
			p = p->Next;
		}
		Tail = p;
	}
	printf("已对链表进行排序！\n");
	
	return;
}

void clear(PNODE Head)
{
	PNODE p, q;

	p = Head->Next;
	q = NULL;
	while (NULL != p)
	{
		q = p->Next;
		free(p);
		p = q;
	}
	Head->Next = NULL;
	printf("清空完毕！\n");

	return;
}

BOOL isEmpty(PNODE Head)
{
	if (NULL == Head->Next)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void traverseList(PNODE Head)
{
	PNODE p;

	if (isEmpty(Head))
	{
		printf("链表为空，遍历失败！\n");
	}
	else
	{
		printf("各节点的数据分别为：\n");
		p = Head->Next;
		while (NULL != p)
		{
			printf("%d ", p->data);
			p = p->Next;
		}
		printf("\n");
	}

	return;
}
