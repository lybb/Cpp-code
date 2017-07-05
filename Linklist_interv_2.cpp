#include "LinkList.h"

//---------------链表面试题（二）---------------
pLinkNode  merge(pLinkList pList1, pLinkList pList2) //合并两个有序单链表（升序）
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

	//将剩余部分链在合并链表的尾部
	if (p1)
		cur->next = p1;
	if (p2)
		cur->next = p2;

	//打印
	cur = newHead;
	while(cur)
	{
		printf("%d->",cur->data);
		cur = cur->next;
	}
	printf("over!\n");

	return newHead;
}

////查找单链表的倒数第k个节点，要求只能遍历一次链表( k>=1 )------解法一，借助栈
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
//	if (k <= 0)	//k在链表结点个数范围之内
//		return top;
//	else		//k的值已经超过链表的结点个数
//		return NULL;
//}
//查找单链表的倒数第k个节点，要求只能遍历一次链表( k>=1 )------解法二，快慢指针
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


//构造一个带环链表
void CreatLoopList(pLinkList pList,int key)
{
	if (pList->pHead == NULL)
		return ;

	//使链表尾结点的next指向第三个结点
	pLinkNode pos = Find(pList,key);	//入口点位置
	pLinkNode head = pList->pHead;
	while (head->next)
	{
		head = head->next;
	}
	head->next = pos;	//环：4->5->6
}

int IsLoop(pLinkList pList)//判断链表是否带环
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

int GetLoopLength(pLinkList pList)//求环的长度
{
	if (pList->pHead == NULL)
		return -1;	//如果链表为空，返回的值为-1；

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

pLinkNode FindLoopPort(pLinkList pList)//求环的入口点
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

	//slow从链表头部走，pos从fast和slow指针相遇的位置走，pos有可能走n圈，最终pos和slow相遇的点为环的入口点
	pos = fast;
	slow = pList->pHead;
	while (slow != pos)
	{
		slow = slow->next;
		pos = pos->next;
	}
	return slow;
}


void CreatCrossList(pLinkList plist1,pLinkList plist2,int key)	//构造一个相交链表
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

int IsCrossing(pLinkList plist1,pLinkList plist2)	//判断链表是否相交
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

//pLinkNode FindCrossNode(pLinkList plist1,pLinkList plist2)	//求相交点----解法一：借助栈
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

pLinkNode FindCrossNode(pLinkList plist1,pLinkList plist2)	//求相交点----解法二：求长度差
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
		while (diff)	//list1长，list1就先走diff个结点
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
		while (diff)	//list2长，list2就先走diff个结点
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

