#include <stack>
#include <iostream>
using namespace std;

namespace MyList
{
	struct Node	//定义结点
	{
		int data;
		Node* next;
		Node(int x)
			:data(x)
			,next(NULL)
		{}
	};

//【链表带环】
//判断相交：先分别找出两个链表中fast指针和slow指针在环内的相交点meet1和meet2，如果meet1和meet2在同一个环内，则两个链表相交，否则就不相交
//求交点：分三种情况：（1）两个链表不带环--->问题转化为上一个求交点的情况；（2）一个链表带环一个链表不带环--->一定不相交；
//	（3）两个带环链表相交：先求出两个链表中环的入口点，如果入口点一样，则链表相交在环外，否则链表相交在环上
//		①相交在环外：找到入口点后，将前一部分与环断开--->问题转化为两个不带环链表求相交点；②相交在环上：任意一个入口点都可以作为相交点


//【链表不带环】
	//判断链表是否带环
	bool IsLoop(Node* pHead)
	{
		if(pHead == NULL)
			return false;
		Node* fast = pHead;
		Node* slow = pHead;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if(fast == slow)
				return true;
		}
		return false;
	}
	//判断相交
	bool IsCross(Node* pHead1,Node* pHead2)
	{
		if(pHead1 == NULL || pHead2 == NULL)
			return false;
		Node* p1 = pHead1;
		Node* p2 = pHead2;
		while (p1->next)
		{
			p1 = p1->next;
		}
		while (p2->next)
		{
			p2 = p2->next;
		}
		if(p1 == p2)
			return true;
		else
			return false;
	} 
	//找交点---快慢指针
	Node* CrossNode1(Node* pHead1,Node* pHead2)
	{
		if(pHead1==NULL || pHead2==NULL)
			return NULL;
		int step1 = 0;
		int step2 = 0;
		Node* p1 = pHead1;
		Node* p2 = pHead2;
		while (p1 || p2)
		{
			if(p1)
			{
				step1++;
				p1 = p1->next;
			}
			if(p2)
			{
				step2++;
				p2 = p2->next;
			}
		}

		p1 = pHead1;
		p2 = pHead2;
		if(step1 > step2)
		{
			int diff = step1-step2;
			while (diff--)
			{
				p1 = p1->next;
			}
		}
		else
		{
			int diff = step2 - step1;
			while (diff--)
			{
				p2 = p2->next;
			}
		}
		while(p1 && p2)
		{
			if(p1 == p2)
				return p1;
			p1 = p1->next;
			p2 = p2->next;
		}
		return NULL;
	}
	//找交点---借助栈
	Node* CrossNode2(Node* pHead1,Node* pHead2)
	{
		if(pHead1==NULL || pHead2==NULL)
			return NULL;
		stack<Node*> s1;
		stack<Node*> s2;
		Node* top = NULL;
		Node* p1 = pHead1;
		Node* p2 = pHead2;
		while (p1)
		{
			s1.push(p1);
			p1 = p1->next;
		}
		while (p2)
		{
			s2.push(p2);
			p2 = p2->next;
		}
		while (!s1.empty() && !s2.empty())
		{
			if(s1.top() != s2.top())
				break;
			top = s1.top();
			s1.pop();
			s2.pop();
		}
		if(s1.empty() || s2.empty())
			return NULL;
		else
			return top;
	}

//【链表带环】
	//找入口点
	Node* FindEnterNode(Node* pHead)
	{
		if(pHead == NULL)
			return NULL;
		Node* fast = pHead;
		Node* slow = pHead;
		Node* meet = NULL;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if(fast == slow)
			{
				meet = slow;
				break;
			}
		}
		slow = pHead;
		while (slow != meet)
		{
			slow = slow->next;
			meet = meet->next;
		}
		return slow;
	}
	//判断相交
	Node* MeetNode(Node* pHead)
	{
		if(pHead == NULL)
			return NULL;
		Node* fast = pHead;
		Node* slow = pHead;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if(fast == slow)
				return slow;
		}
		return NULL;
	}
	bool IsCross_Loop(Node* pHead1,Node* pHead2)
	{
		if(pHead1==NULL || pHead2==NULL)
			return false;
		Node* pMeet1 = MeetNode(pHead1);
		Node* pMeet2 = MeetNode(pHead2);
		Node* cur = pMeet1;
		while (cur)
		{
			if(cur == pMeet2)
				break;
			cur = cur->next;
			if(cur == pMeet1)
				return false;
		}
		return true;
	}
	//求相交点
	Node* GetCrossNode(Node* pHead1,Node* pHead2)
	{
		if(!IsLoop(pHead1) && !IsLoop(pHead2))	//两个都不带环--->单链表求交点
			return CrossNode1(pHead1,pHead2);
		if(IsLoop(pHead1) && !IsLoop(pHead2))	//pHead1带环pHead2不带环--->一定不相交
			return NULL;
		if(!IsLoop(pHead1) && IsLoop(pHead2))	//pHead1不带环pHead2带环--->一定不相交
			return NULL;
		Node* enter1 = FindEnterNode(pHead1);	//两个链表都带环--->分两种情况
		Node* enter2 = FindEnterNode(pHead2);
		Node* pCross = NULL;
		Node* cur = enter1;
		if(enter1 != enter2)	//入口点不同时，任一个一个环的入口点都可以作为交点
		{
			pCross = enter2;
		}
		else	//入口点相同时，从头找交点
		{
			//将两个链表与下一个结点断开，等同于两个不带环的单链表找相交点
			while (cur && cur->next != enter1)
			{
				cur = cur->next;
			}
			cur->next = NULL;
			pCross = CrossNode1(pHead1,pHead2);
		}
		return pCross;
	}

	void Test()
	{
		Node* node1 = new Node(1);	//list1->pHead
		Node* node2 = new Node(2);
		Node* node3 = new Node(3);
		Node* node4 = new Node(4);
		Node* node5 = new Node(5);
		Node* node6 = new Node(6);
		node1->next = node2;
		node2->next = node3;
		node3->next = node4;
		node4->next = node5;
		node5->next = node6;
		//node6->next = node3;
		Node* node7 = new Node(7);	//list2->pHead
		Node* node8 = new Node(8);
		Node* node9 = new Node(9);
		Node* node10 = new Node(10);
		Node* node11 = new Node(11);
		Node* node12 = new Node(12);
		node7->next = node8;
		//node8->next = node3;	//不带环在3处相交 & 两个带环链表在环外相交
		node8->next = node9;
		node9->next = node10;
		//node10->next = node5;	//两个带环链表在环上相交
		node10->next = node11;
		node11->next = node12;
		node12->next = node9;
		//cout<<IsCross(node1,node7)<<endl;
		//Node* ret = CrossNode1(node1,NULL);
		//Node* ret = CrossNode2(node1,node7);
		//带环链表
		//cout<<IsCross_Loop(node1,node7)<<endl;
		Node* ret = GetCrossNode(node1,node7);
		if(ret)
			cout<<ret->data<<endl;
		else
			cout<<"NULL"<<endl;
		//show(node1);
	}
}

int main()
{
	MyList::Test();
	system("pause");
	return 0;
}