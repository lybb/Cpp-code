#include <iostream>
using namespace std;

//-1、链表翻转。给出一个链表和一个数k，比如链表1→2→3→4→5→6，k=2，翻转后2→1→4→3→6→5，
//若k=3,翻转后3→2→1→6→5→4，若k=4，翻转后4→3→2→1→5→6.
//用程序实现Node* RotateList(Node* list, size_t k).


//思路分析：将链表按照k的大小分成一个一个的“区间”，对每一个区间进行逆置后，将两部分连接起来
//需要得到每个逆置后的区间的头指针head和尾指针tail，用pos记录上一个区间翻转后的尾指针tail，第1个区
//间翻转后不需要进行连接head，否则形成循环链表；当第二个区间翻转以后再开始将上次的尾指针pos记录的
//位置与这次翻转后的head指针进行连接

Node* ReverseList(Node* pHead)	//链表逆置返回头结点
{
	if(pHead == NULL)
		return NULL;
	Node* newHead = NULL;
	Node* cur = pHead;
	Node* tmp = NULL;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		tmp->next = newHead;
		newHead = tmp;
	}
	return newHead;
}

Node* GetTailNode(Node* pHead)	//取得尾结点
{
	Node* cur = pHead;
	while (cur->next)
	{
		cur = cur->next;
	}
	return cur;
}

Node* RotateList(Node* pHead,int k)
{
	if(pHead==NULL || k<=0)
		return NULL;
	Node* cur = pHead;
	Node* prev = pHead;	//需要翻转的区间的头结点
	Node* next = NULL;
	Node* head = NULL;
	Node* tail = NULL;
	Node* pos = NULL;
	Node* newHead = NULL;	//记录新链表的头结点
	for (int i=0; i<k; i++)
	{
		newHead = cur;
		cur = cur->next;
	}
	cur = pHead;
	int count = k;
	while (cur)
	{
		while (--count)
			cur = cur->next;

		if (cur)
		{
			next = cur->next;
			cur->next = NULL;
			head = ReverseList(prev);	//翻转后的头结点
			tail = GetTailNode(cur);	//翻转后的尾结点

			//当pos为空时不连接头，即第一次翻转
			if(pos)
				pos->next = head;

			pos = tail;
			prev = next;
			cur = next;
			count = k;
		}
	}
	return newHead;
}
