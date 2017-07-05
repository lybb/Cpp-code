#include "LinkList.h"

//---------------���������⣨����---------------
pLinkNode  merge(pLinkList pList1, pLinkList pList2) //�ϲ�����������������
{
	if (pList1->pHead == NULL)
		return pList2->pHead;
	if (pList2->pHead == NULL)
		return pList1->pHead;

	pLinkNode p1 = pList1->pHead;
	pLinkNode p2 = pList2->pHead;
	pLinkNode newHead = NULL;
	if (p1->data < p2->data)
	{
		newHead = p1;
		p1 = p1->next;
	}
	else
	{
		newHead = p2;
		p2 = p2->next;
	}
	pLinkNode cur = newHead;
	while (p1 && p2)
	{
		if (p1->data < p2->data)
		{
			cur->next = p1;
			p1 = p1->next;
		}
		else
		{
			cur->next = p2;
			p2 = p2->next;
		}
		cur = cur->next;
	}

	//��ʣ�ಿ�����ںϲ������β��
	if (p1)
		cur->next = p1;
	if (p2)
		cur->next = p2;

	//��ӡ
	cur = newHead;
	while(cur)
	{
		printf("%d->",cur->data);
		cur = cur->next;
	}
	printf("over!\n");

	return newHead;
}

////���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������( k>=1 )------�ⷨһ������ջ
//pLinkNode FindLastKNode(pLinkList pList,int k)
//{
//	if ((pList->pHead == NULL) || k <= 0)
//		return NULL;
//
//	stack<pLinkNode> s;
//	pLinkNode cur = pList->pHead;
//	while (cur)
//	{
//		s.push(cur);
//		cur = cur->next;
//	}
//	pLinkNode top = NULL;
//	while (k && !s.empty())
//	{
//		top = s.top();
//		s.pop();
//		k--;
//	}
//	if (k <= 0)	//k�������������Χ֮��
//		return top;
//	else		//k��ֵ�Ѿ���������Ľ�����
//		return NULL;
//}
//���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������( k>=1 )------�ⷨ��������ָ��
pLinkNode FindLastKNode(pLinkList pList,int k)
{
	if ((pList->pHead == NULL) || k <= 0)
		return NULL;
	
	pLinkNode fast = pList->pHead;
	pLinkNode slow = pList->pHead;
	int i=0;
	while (i < k)
	{
		if(fast->next)
			fast = fast->next;
		else
			return NULL;
		i++;
	}

	while (fast)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}


//����һ����������
void CreatLoopList(pLinkList pList,int key)
{
	if (pList->pHead == NULL)
		return ;

	//ʹ����β����nextָ����������
	pLinkNode pos = Find(pList,key);	//��ڵ�λ��
	pLinkNode head = pList->pHead;
	while (head->next)
	{
		head = head->next;
	}
	head->next = pos;	//����4->5->6
}

int IsLoop(pLinkList pList)//�ж������Ƿ����
{
	if (pList->pHead == NULL)
		return 0;

	pLinkNode slow = pList->pHead;
	pLinkNode fast = pList->pHead;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return 1;
	}
	return 0;
}

int GetLoopLength(pLinkList pList)//�󻷵ĳ���
{
	if (pList->pHead == NULL)
		return -1;	//�������Ϊ�գ����ص�ֵΪ-1��

	pLinkNode fast = pList->pHead;
	pLinkNode slow = pList->pHead;
	int length = 0;
	pLinkNode cur = NULL;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
		{
			cur = fast->next;
			length = 1;
			break;
		}
	}
	while (cur != fast)
	{
		cur = cur->next;
		length++;
	}
	return length;
}

pLinkNode FindLoopPort(pLinkList pList)//�󻷵���ڵ�
{
	if (pList->pHead == NULL)
		return NULL;

	pLinkNode slow = pList->pHead;
	pLinkNode fast = pList->pHead;
	pLinkNode pos = NULL;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}

	//slow������ͷ���ߣ�pos��fast��slowָ��������λ���ߣ�pos�п�����nȦ������pos��slow�����ĵ�Ϊ������ڵ�
	pos = fast;
	slow = pList->pHead;
	while (slow != pos)
	{
		slow = slow->next;
		pos = pos->next;
	}
	return slow;
}


void CreatCrossList(pLinkList plist1,pLinkList plist2,int key)	//����һ���ཻ����
{
	if (plist1->pHead==NULL  ||  plist2->pHead==NULL)
		return ;
	pLinkNode pos = Find(plist1,key);
	pLinkNode start = plist2->pHead;
	pLinkNode prev = NULL;
	while (start)
	{
		prev = start;
		start = start->next;
		if (start->data == pos->data)
		{
			prev->next = pos;
			break;
		}
	}
}

int IsCrossing(pLinkList plist1,pLinkList plist2)	//�ж������Ƿ��ཻ
{
	if (plist1->pHead==NULL  ||  plist2->pHead==NULL)
		return 0;

	CreatCrossList(plist1,plist2,7);
	pLinkNode p1 = plist1->pHead;
	pLinkNode p2 = plist2->pHead;
	while (p1->next)
	{
		p1 = p1->next;
	}
	while (p2->next)
	{
		p2 = p2->next;
	}
	if (p1->data == p2->data)
		return 1;
	else
		return 0;
}

//pLinkNode FindCrossNode(pLinkList plist1,pLinkList plist2)	//���ཻ��----�ⷨһ������ջ
//{
//	if (plist1->pHead==NULL  ||  plist2->pHead==NULL)
//		return NULL;
//
//	stack<pLinkNode> s1;
//	stack<pLinkNode> s2;
//	pLinkNode p1 = plist1->pHead;
//	pLinkNode p2 = plist2->pHead;
//	while (p1)
//	{
//		s1.push(p1);
//		p1 = p1->next;
//	}
//	while (p2)
//	{
//		s2.push(p2);
//		p2 = p2->next;
//	}
//
//	pLinkNode top = NULL;
//	while (!s1.empty() && !s2.empty())
//	{
//		if (s1.top() == s2.top())
//			top = s1.top();
//		s1.pop();
//		s2.pop();
//	}
//	return top;
//}

pLinkNode FindCrossNode(pLinkList plist1,pLinkList plist2)	//���ཻ��----�ⷨ�����󳤶Ȳ�
{
	if (plist1->pHead==NULL  ||  plist2->pHead==NULL)
		return NULL;

	int diff = 0;
	int len1 = 0;
	int len2 = 0;
	pLinkNode p1 = plist1->pHead;
	pLinkNode p2 = plist2->pHead;
	while (p1)
	{
		len1++;
		p1 = p1->next;
	}
	while (p2)
	{
		len2++;
		p2 = p2->next;
	}

	p1 = plist1->pHead;
	p2 = plist2->pHead;
	if (len1 > len2)
	{
		diff = len1-len2;
		while (diff)	//list1����list1������diff�����
		{
			p1 = p1->next;
			diff--;
		}
		while (p1 && p2)
		{
			if(p1 == p2)
				return p2;
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	else
	{
		diff = len2-len1;
		while (diff)	//list2����list2������diff�����
		{
			p2 = p2->next;
			diff--;
		}
		while (p1 && p2)
		{

			if(p1 == p2)
				return p1;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return NULL;
}


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

