#include <iostream>
using namespace std;

//-1������ת������һ�������һ����k����������1��2��3��4��5��6��k=2����ת��2��1��4��3��6��5��
//��k=3,��ת��3��2��1��6��5��4����k=4����ת��4��3��2��1��5��6.
//�ó���ʵ��Node* RotateList(Node* list, size_t k).


//˼·��������������k�Ĵ�С�ֳ�һ��һ���ġ����䡱����ÿһ������������ú󣬽���������������
//��Ҫ�õ�ÿ�����ú�������ͷָ��head��βָ��tail����pos��¼��һ�����䷭ת���βָ��tail����1����
//�䷭ת����Ҫ��������head�������γ�ѭ���������ڶ������䷭ת�Ժ��ٿ�ʼ���ϴε�βָ��pos��¼��
//λ������η�ת���headָ���������

Node* ReverseList(Node* pHead)	//�������÷���ͷ���
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

Node* GetTailNode(Node* pHead)	//ȡ��β���
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
	Node* prev = pHead;	//��Ҫ��ת�������ͷ���
	Node* next = NULL;
	Node* head = NULL;
	Node* tail = NULL;
	Node* pos = NULL;
	Node* newHead = NULL;	//��¼�������ͷ���
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
			head = ReverseList(prev);	//��ת���ͷ���
			tail = GetTailNode(cur);	//��ת���β���

			//��posΪ��ʱ������ͷ������һ�η�ת
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
