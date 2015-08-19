/*
	目的：模拟数组，可自由增减元素，可排序，可倒置
	时间：2015年7月16日
	By 李瑞明
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef char BOOL;	//C语言不直接支持BOOL类型，故将char转定义为BOOL

struct Arr			//数组（此处默认数组元素类型为int，可随意修改类型）
{
	int * pBase;	//存储数组第一个元素的地址
	int len;		//数组所能容纳最大元素的个数
	int cnt;		//当前数组有效元素的个数
};

void init_arr(struct Arr * pArr, int length);				//初始化数组
BOOL append_arr(struct Arr * pArr, int val);				//追加数组元素
BOOL insert_arr(struct Arr * pArr, int pos, int val);		//在指定位置插入数组元素，其中pos为自然顺序的序号
BOOL delete_arr(struct Arr * pArr, int pos, int * pVal);	//在指定位置删除数组元素
BOOL is_empty(struct Arr * pArr);							//检查数组是否为空
BOOL is_full(struct Arr * pArr);							//检查数组是否达到最大容纳量
void sort_arr(struct Arr * pArr);							//为数组排序
void inverse_arr(struct Arr * pArr);						//倒置数组
void traverse_arr(struct Arr * pArr);						//遍历数组元素

int main(void)
{
	int len;
	int val;
	struct Arr arr;
	
	len = 40;												//默认值为40，可随意修改大小
	init_arr(&arr, len);
	//将想要使用的功能（即函数）写进main函数即可，以下为示例
	if (!append_arr(&arr, 3))
	{
		printf("数组达到最大容量，无法添加元素！\n");
	}
	if (!append_arr(&arr, 7))
	{
		printf("数组达到最大容量，无法添加元素！\n");
	}
	if (!append_arr(&arr, 5))
	{
		printf("数组达到最大容量，无法添加元素！\n");
	}
	if (!insert_arr(&arr, 2, 1))
	{
		printf("数组达到最大容量，无法添加元素！\n");
	}
	if (delete_arr(&arr, 3, &val))
	{
		printf("删除成功，被删除的元素的值为%d\n", val);
	}
	else
	{
		printf("数组为空，无法删除！\n");
	}
	traverse_arr(&arr);
	inverse_arr(&arr);
	traverse_arr(&arr);
	sort_arr(&arr);
	traverse_arr(&arr);

	return 0;
}

/*
	静态数组：系统自动分配内存，不可更改容量，数组容量不能是变量，函数执行完毕后自动释放数组空间
	动态数组：程序员手动分配内存(使用malloc函数)，可以更改容量，数组容量可以为变量或常量，需要手动释放数组空间
*/
void init_arr(struct Arr * pArr, int length)
{
	pArr->pBase = (int *)malloc(sizeof(int) * length);
	if (NULL == pArr->pBase)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	else
	{
		pArr->len = length;
		pArr->cnt = 0;
	}

	return;
}

BOOL append_arr(struct Arr * pArr, int val)
{
	if (is_full(pArr))
	{
		return FALSE;
	}
	else
	{
		pArr->pBase[pArr->cnt] = val;
		pArr->cnt++;
		return TRUE;
	}
}

BOOL insert_arr(struct Arr * pArr, int pos, int val)
{
	int i;

	if (is_full(pArr))
	{
		return FALSE;
	}
	if (pos < 1 || pos > pArr->cnt+1)
	{
		return FALSE;
	}

	for (i = pArr->cnt-1; i >= pos-1; i--)
	{
		pArr->pBase[i+1] = pArr->pBase[i];
	}
	pArr->pBase[pos-1] = val;
	pArr->cnt++;
	return TRUE;
}

BOOL delete_arr(struct Arr * pArr, int pos, int * pVal)
{
	int i;

	if (is_empty(pArr))
	{
		return FALSE;
	}
	if (pos < 1 || pos > pArr->cnt)
	{
		return FALSE;
	}

	*pVal = pArr->pBase[pos-1];
	for (i = pos; i < pArr->cnt; i++)
	{
		pArr->pBase[i-1] = pArr->pBase[i];
	}
	pArr->cnt--;
	return TRUE;
}

BOOL is_empty(struct Arr * pArr)
{
	if (0 == pArr->cnt)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL is_full(struct Arr * pArr)
{
	if (pArr->len == pArr->cnt)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void sort_arr(struct Arr * pArr)
{
	int i, j;
	int temp;
	
	if (is_empty(pArr))
	{
		printf("数组为空！排序失败！\n");
	}
	else
	{
		for (i = 0; i < pArr->cnt; i++)
		{
			for (j = i+1; j < pArr->cnt; j++)
			{
				if (pArr->pBase[i] > pArr->pBase[j])
				{
					temp = pArr->pBase[i];
					pArr->pBase[i] = pArr->pBase[j];
					pArr->pBase[j] = temp;
				}
			}
		}
		printf("数组已按从小到大顺序排列！\n");
	}

	return;
}

void inverse_arr(struct Arr * pArr)
{
	int i, j;
	int temp;

	if (is_empty(pArr))
	{
		printf("数组为空！倒置失败！\n");
	}
	else
	{
		i = 0;
		j = pArr->cnt-1;
		while (i < j)
		{
			temp = pArr->pBase[i];
			pArr->pBase[i] = pArr->pBase[j];
			pArr->pBase[j] = temp;
			i++;
			j--;
		}
		printf("数组倒置成功！\n");
	}

	return;
}

void traverse_arr(struct Arr * pArr)
{
	int i;
	
	if (is_empty(pArr))
	{
		printf("数组为空，遍历失败！\n");
	}
	else
	{
		printf("数组各元素的值分别为：\n");
		for (i = 0; i < pArr->cnt; i++)
		{
			printf("%d ", pArr->pBase[i]);
		}
		printf("\n");
	}

	return;
}
