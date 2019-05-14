#pragma once
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef enum Bool {
	True = 1,
	False = 0
}Bool;

typedef struct Block {
	void* data;
	int size;

}Block;

typedef  struct Slice {
	void* array_pointer;
	int	len;//当前长度
	int cap;//容量
}Slice;




//export***************************
//链表
#define LIST
#ifdef LIST

#define ANY_TYPE void*
typedef struct Node
{
	ANY_TYPE data;
	struct Node *next;
} Node;

typedef struct List {
	struct Node *head;
	struct Node *tail;
} List;

List *list_new(int len);

int list_len(List *head);

int list_delet(List **head);

int list_append(List* list, void* data);

void* list_get(List *list, int index);

int list_set(List *list, int index, void* val);
#endif // LIST


//链表

#define QUEUE
#ifdef QUEUE

typedef unsigned char u8;
typedef u8 Elem;

typedef struct circlequeue
{
	int iLength;
	int iSize;
	int iHead;
	int iTail;
	Elem *Datas;
}Queue;

Queue*  queue_new(int size);
u8 queue_delete(Queue *queue);
u8 is_queue_empty(Queue *queue);
u8 is_queue_full(Queue *queue);
int queue_size(Queue *queue);
u8 queue_push(Queue *queue, Elem data);
Elem queue_front(Queue *queue);
Elem queue_back(Queue *queue);
u8 queue_pop(Queue *queue);
void queue_printf(Queue *queue);



#endif // QUEUE



//内存游标==============================
//自动定位到最后一个复制的数据
void mem_append(u32* cursor_ptr, u8* dst, u8* src, u32 len);

//内存游标


//math ==============
Bool is_odd(int data);
//math


void struct_main();
void string_match_main();
int list_main();

u8 StrToHex(char *NumStr);