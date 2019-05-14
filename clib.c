#define DEBUG
#ifdef DEBUG
#include <assert.h>

#endif // DEBUG
#define MCU

//动态长度
#include "clib.h"







//list********************************
#include <stddef.h>
//link list **********************
#include <stdlib.h>
#include<memory.h>

//结构体=====================================
//成员便宜地址
#ifdef DEBUG
//#define OFFSET_DIFF(type, start,end)  ((char *)&((type *)0)->end - (char *)&((type *)0)->start)  
//todo 计算2成员间隔的长度
//
#endif // DEBUG


void struct_main() {
	typedef struct A
	{
		int a;
		char* b[3];
		short* c;
	}A;
	int offset = 0;
	offset = offsetof(A, b);
	offset = offsetof(A, c);
	int hex = StrToHex("a9");
	hex = StrToHex("A1");
	//int diff=OFFSET_DIFF(A, b, c);
}
//iter=========================================


//iter
#ifdef LIST
// list==================================================== =

List * list_new(int len)
{
	//初始化尾部节点为头节点
	List* list = malloc(sizeof(List));

	Node *node = malloc(sizeof(Node));
	Node *head = node;
	node->data = NULL;
	for (int i = 1; i < len; i++)
	{
		Node *new_node = malloc(sizeof(Node));
		new_node->data = NULL;
		head->next = new_node;
		//更新尾节点为新节点
		head = new_node;
		list->tail = new_node;
	}
	//尾节点的指针域为空
	head->next = NULL;


	list->head = node;
	return list;

}

int list_append(List* list, void* data) {
	assert(list != NULL);

	Node * tail = malloc(sizeof(Node));
	tail->data = data;
	tail->next = NULL;

	list->tail->next = tail;
	list->tail = tail;
	return 0;
}
int list_len(List *list)
{
	Node* head = list->head;
	int cnt = 0;
	while (head)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}


int list_delet(List **list)
{
	Node *head = (*list)->head;
	Node *tmp = NULL;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	free((*list));

	*list = NULL;

}
//返回节点 数据的地址
void* list_get(List *list, int index) {
	Node *head = list->head;

	while (index--) {
		head = head->next;
	}

	return (head->data);
}

int list_set(List *list, int index, void* val) {
	Node *head = list->head;

	while (index--) {
		head = head->next;
	}
	head->data = val;
	return 0;
}

//遍历
// void print_list(Node* list)
// {
//  //第一个节点
//  Node *node = list->next;
//  while (node)
//  {
//      *(list->data)=0xf0;
//      node = node->next;
//  }
// }
//link

int list_main()
{
	List *P = list_new(3);
	int num = 0x99;
	list_append(P, 123);
	num = list_len(P);
	/*int * data=  list_index(P, 2);

	*data = num;*/
	int * data = list_get(P, 0);

	u8 str[10] = "hello";
	list_set(P, 0, str);


	list_delet(&P);

	return 0;
}

#endif // LIST
#ifdef QUEUE
#include <stdlib.h>
#include <stdio.h>


/**********************创建队列*************************/
Queue*  queue_new( int size)
{
	//todo 只能在堆上定义，考虑可以让他在栈上
	Queue* queue=(Queue*)malloc(sizeof(Queue));
	queue->iSize = size;
	queue->iLength = 0;
	queue->iTail = 0;
	queue->iHead = 0;
	queue->Datas = (Elem *)malloc(size * sizeof(Elem));
	
	return queue;
}

/**********************删除队列*************************/
u8 queue_delete(Queue *queue)
{
	//todo 该地址 把指针指向NULL
	free(queue->Datas);

	free(queue);

	return 1;
}

/*********************队头队尾操作**********************/

static void queue_tail_add(Queue *queue)
{
	queue->iTail++;
	queue->iTail = queue->iTail % queue->iSize;
}
static void queue_head_add(Queue *queue)
{
	queue->iHead++;
	queue->iHead = queue->iHead % queue->iSize;
}

/***********************队列判空************************/
u8 is_queue_empty(Queue *queue)
{
	if (queue->iLength == 0)
	{
		return 1;
	}
	return 0;
}

/***********************队列判满************************/

u8 is_queue_full(Queue *queue)
{
	if (queue->iLength >= queue->iSize)
	{
		return 1;
	}
	return 0;
}

/*******************返回队列现有长度********************/

int queue_size(Queue *queue)
{
	return queue->iLength;
}

/********************往队尾放入元素*********************/

u8 queue_push(Queue *queue, Elem data)
{
	if (is_queue_full(queue))
	{
		return 0;
	}

	queue->Datas[queue->iTail] = data;
	queue_tail_add(queue);
	queue->iLength++;
	return 1;
}

/************获取队头第一个元素（不删除）***************/

Elem queue_front(Queue *queue)
{
	if (is_queue_empty(queue))
	{
		return 0;
	}

	return queue->Datas[queue->iHead];
}
Elem queue_back(Queue *queue)
{
	if (is_queue_empty(queue))
	{
		return 0;
	}
	return queue->Datas[queue->iTail];
}

/******************删除队列第一个元素*******************/

u8 queue_pop(Queue *queue)
{
	if (is_queue_empty(queue))
	{
		return 0;//queue empty
	}

	queue_head_add(queue);
	queue->iLength--;
	return 1;
}

/*****************打印队列中的全部元素******************/

void queue_printf(Queue *queue)
{
	int i;
	int temp = queue->iHead;
	printf("queue datas:\r\n");
	for (i = 0; i < queue->iLength; i++)
	{
		printf("%d ", queue->Datas[temp++%queue->iSize]);
	}
	printf("\r\n");
}

int queue_main() {
	int i;
	//queue(stack)
	Queue *queue2 = queue_new(20);
	//queue(heap)
	//Queue Init

	Queue *queue = queue_new( 20);

	//queue1
	printf("insert datas:(0-19)\r\n");
	for (i = 0; i < 20; i++)
	{
		queue_push(queue, i);
	}

	queue_printf(queue);

	printf("delete datas(first 10):\r\n");
	for (i = 0; i < 10; i++)
	{
		queue_pop(queue);
	}

	queue_printf(queue);

	printf("first data:%d\r\n", queue_front(queue));

	printf("queuesize = %d\r\n", queue_size(queue));

	//queue2
	printf("\r\n");
	printf("insert datas to queue2:(0-190,10interval)\r\n");
	for (i = 0; i < 20; i++)
	{
		queue_push(queue2, i * 10);
	}

	queue_printf(queue2);

	printf("delete datas(first 10):\r\n");
	for (i = 0; i < 10; i++)
	{
		queue_pop(queue2);
	}

	queue_printf(queue2);

	//delete queue
	printf("\r\n");
	printf("queue1 delete\r\n");
	queue_delete(queue);
	//free(queue);
	queue = 0;

	printf("queue2 delete\r\n");
	queue_delete(queue2);
}
#endif // QUEUE
// queue



//memory
//cursor====================================
void mem_append(u32* cursor_ptr, u8* dst, void* src, u32 len) {
	//注意指针的指向的大小
	memcpy(dst + *cursor_ptr, src, len);
	*cursor_ptr += len;
}

#ifdef MCU
void *mymalloc_size(u32 size) {
	return malloc(size);
}
void myfree_size(void *ptr) {
	free(ptr);
}
void *mycalloc_size(u32 count, u32 t_size) {
	return calloc(count, t_size);
}
#endif // !MCU



//
//}
////


//string match==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//函数名: strchr
//功  能 : 在一个串中查找给定字符的第一个匹配之处de 指针\
//用  法 :  char *strchr(char *str, char c);


void string_match_main()
{
	//char *pattern = 'c';
	//char *text = "bacabaabababaababababcabcaababababcabbababababababababcabab";
	//char* p=strchr(text, 'c');

	return 0;
}
//string match
unsigned char StrToHex(char *NumStr)
{
	unsigned  char Data = 0x00;

	if ('0' <= *NumStr && *NumStr <= '9')
		Data = (*NumStr - '0') << 4;
	else if ('A' <= *NumStr && *NumStr <= 'F')
		Data = (*NumStr - 'A' + 10) << 4;
	else if ('a' <= *NumStr && *NumStr <= 'f')
		Data = (*NumStr - 'a' + 10) << 4;

	if ('0' <= *(NumStr + 1) && *(NumStr + 1) <= '9')
		Data &= (*(NumStr + 1) - '0');
	else if ('A' <= *(NumStr + 1) && *(NumStr + 1) <= 'F')
		Data &= (*(NumStr + 1) - 'A' + 10);
	else if ('a' <= *(NumStr + 1) && *(NumStr + 1) <= 'f')
		Data &= (*(NumStr + 1) - 'a' + 10);

	return Data;
}




//math =====================================================

Bool is_odd(int data) {
	return (data & 0x0f) % 2;
}

//math
#define RUN_MAIN
#ifdef RUN_MAIN
int main() {
	queue_main();
	list_main();
}

#endif // RUN_MAIN
