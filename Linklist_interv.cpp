#include "LinkList.h"


//---------链表相关面试题（Ⅰ）---------
void EraseNotTail(pLinkNode pos)//删除无头单链表的非尾结点
{
	LinkNode* _next = pos->next;
	pos->data = _next->data;
	pos->next = _next->next;
	delete _next;
	_next = NULL;
}

void ReverList(pLinkList pList)//逆序链表
{
	if (pList->pHead == NULL)
		return ;

	LinkNode* cur = pList->pHead;
	LinkNode* tmp = NULL;
	LinkNode* newHead = NULL;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		tmp->next = newHead;
		newHead = tmp;
	}
	pList->pHead = newHead;
}

void InsertFrontNode(pLinkNode pos,DataType x)//在当前结点前插入一个数据（无头结点单链表）
{
	//先插入到pos的下一个，然后交换两个结点的值
	LinkNode* newNode = BuyNode(x);
	newNode->next = pos->next;
	pos->next = newNode;

	DataType tmp = pos->data;
	pos->data = newNode->data;
	newNode->data = tmp;
}

LinkNode* FindMiddleNode(pLinkList pList)//查找一个链表的中间节点
{
	LinkNode* cur = pList->pHead;
	LinkNode* prev = pList->pHead;

	if (pList->pHead == NULL)
		return NULL;

	while (prev && prev->next)
	{
		prev = prev->next->next;
		cur = cur->next;
	}
	return cur;
}

void PrintTailToHead(pLinkList pList)	//从尾到头打印单链表
{
	stack<LinkNode*> s;
	LinkNode* cur = pList->pHead;
	LinkNode* top = NULL;

	if (pList->pHead == NULL)
		return ;

	while (cur)
	{
		s.push(cur);
		cur = cur->next;
	}
	while (!s.empty())
	{
		top = s.top();
		printf("%d ",top->data);
		s.pop();
	}
	printf("\n");
}

void ListSort(pLinkList pList)	//单链表排序
{
	//类似于冒泡排序的思想，每次cur都从头结点开始遍历，将最小的交换到最后，并设置一个标志tail
	if (pList->pHead == NULL)	//0个或者1个结点，无需排序
		return ;
	if (pList->pHead->next == NULL)
		return ;

	LinkNode* cur = pList->pHead;
	LinkNode* tail = NULL;
	while (cur != tail)
	{
		while (cur->next != tail)
		{
			if (cur->data < cur->next->data)	//降序排序
			{
				DataType tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
			}
			cur = cur->next;
		}
		tail = cur;
		cur = pList->pHead;
	}
}
