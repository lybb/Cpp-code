#include <stack>
#include <iostream>
using namespace std;

namespace MyList
{
	struct Node	//������
	{
		int data;
		Node* next;
		Node(int x)
			:data(x)
			,next(NULL)
		{}
	};

//�����������
//�ж��ཻ���ȷֱ��ҳ�����������fastָ���slowָ���ڻ��ڵ��ཻ��meet1��meet2�����meet1��meet2��ͬһ�����ڣ������������ཻ������Ͳ��ཻ
//�󽻵㣺�������������1��������������--->����ת��Ϊ��һ���󽻵���������2��һ���������һ����������--->һ�����ཻ��
//	��3���������������ཻ����������������л�����ڵ㣬�����ڵ�һ�����������ཻ�ڻ��⣬���������ཻ�ڻ���
//		���ཻ�ڻ��⣺�ҵ���ڵ�󣬽�ǰһ�����뻷�Ͽ�--->����ת��Ϊ�����������������ཻ�㣻���ཻ�ڻ��ϣ�����һ����ڵ㶼������Ϊ�ཻ��


//������������
	//�ж������Ƿ����
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
	//�ж��ཻ
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
	//�ҽ���---����ָ��
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
	//�ҽ���---����ջ
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

//�����������
	//����ڵ�
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
	//�ж��ཻ
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
	//���ཻ��
	Node* GetCrossNode(Node* pHead1,Node* pHead2)
	{
		if(!IsLoop(pHead1) && !IsLoop(pHead2))	//������������--->�������󽻵�
			return CrossNode1(pHead1,pHead2);
		if(IsLoop(pHead1) && !IsLoop(pHead2))	//pHead1����pHead2������--->һ�����ཻ
			return NULL;
		if(!IsLoop(pHead1) && IsLoop(pHead2))	//pHead1������pHead2����--->һ�����ཻ
			return NULL;
		Node* enter1 = FindEnterNode(pHead1);	//������������--->���������
		Node* enter2 = FindEnterNode(pHead2);
		Node* pCross = NULL;
		Node* cur = enter1;
		if(enter1 != enter2)	//��ڵ㲻ͬʱ����һ��һ��������ڵ㶼������Ϊ����
		{
			pCross = enter2;
		}
		else	//��ڵ���ͬʱ����ͷ�ҽ���
		{
			//��������������һ�����Ͽ�����ͬ�������������ĵ��������ཻ��
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
		//node8->next = node3;	//��������3���ཻ & �������������ڻ����ཻ
		node8->next = node9;
		node9->next = node10;
		//node10->next = node5;	//�������������ڻ����ཻ
		node10->next = node11;
		node11->next = node12;
		node12->next = node9;
		//cout<<IsCross(node1,node7)<<endl;
		//Node* ret = CrossNode1(node1,NULL);
		//Node* ret = CrossNode2(node1,node7);
		//��������
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