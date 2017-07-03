#include "LinkList.h"


//---------������������⣨��---------
void EraseNotTail(pLinkNode pos)//ɾ����ͷ������ķ�β���
{
	LinkNode* _next = pos->next;
	pos->data = _next->data;
	pos->next = _next->next;
	delete _next;
	_next = NULL;
}

void ReverList(pLinkList pList)//��������
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

void InsertFrontNode(pLinkNode pos,DataType x)//�ڵ�ǰ���ǰ����һ�����ݣ���ͷ��㵥����
{
	//�Ȳ��뵽pos����һ����Ȼ�󽻻���������ֵ
	LinkNode* newNode = BuyNode(x);
	newNode->next = pos->next;
	pos->next = newNode;

	DataType tmp = pos->data;
	pos->data = newNode->data;
	newNode->data = tmp;
}

LinkNode* FindMiddleNode(pLinkList pList)//����һ��������м�ڵ�
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

void PrintTailToHead(pLinkList pList)	//��β��ͷ��ӡ������
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

void ListSort(pLinkList pList)	//����������
{
	//������ð�������˼�룬ÿ��cur����ͷ��㿪ʼ����������С�Ľ�������󣬲�����һ����־tail
	if (pList->pHead == NULL)	//0������1����㣬��������
		return ;
	if (pList->pHead->next == NULL)
		return ;

	LinkNode* cur = pList->pHead;
	LinkNode* tail = NULL;
	while (cur != tail)
	{
		while (cur->next != tail)
		{
			if (cur->data < cur->next->data)	//��������
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
