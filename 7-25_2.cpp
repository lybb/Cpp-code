//��ĿҪ��
//��֪����A��B��Ԫ�طֱ��ò���ͷ���ĵ�����洢������difference()������⼯��A��B�Ĳ�����������
//���ڼ���A�ĵ������С����磬������A={5,10,20,15,25,30}������B={5,15,35,25}����ɼ����A={10,20,30}�� 
//������Ľṹ���Ͷ������£� 
//
//struct node 
//{ 
//	int elem; 
//	node* next; 
//}; 
//����ɺ���void difference(node** LA , node* LB)��


//˼·������ÿ����LA��һ����㶼��LB�в����Ƿ�����ͬ��㣬����У�����LA�н���free����������ж�LA����һ�����
//������Ҫע����ǣ�LA�����Ƕ���ָ�룬�����һ����������LB��ͬ�Ľ�㣬��Ӧ�ø���LA��ָ��ĵ�һ�����

#include <iostream>
using namespace std;

namespace MyList
{
	struct node 
	{ 
		int elem; 
		node* next; 
		node(int e)
			:elem(e)
			,next(NULL)
		{}
	}; 

	void difference(node** LA , node* LB)
	{
		if (LB == NULL)
			return ;
		node* pa = *LA;
		node* prev = NULL;
		node* pb = LB;
		node* del = NULL;
		
		while (pa)
		{
			pb = LB;	//pbÿ�ζ���ͷ��ʼ����һ�ߣ�������A�Ĳ���
			while (pb && pb->elem != pa->elem)
			{
				pb = pb->next;
			}

			if(pb)	//pb��ΪNULLʱ��ʾ���뵱ǰpa�ظ��Ľ��
			{
				del = pa;
				pa = pa->next;
				if(!prev)
					*LA = pa;	//����LA��ͷ
				else
					prev->next = pa;
				free(del);
				del = NULL;
			}
			else
			{
				prev = pa;
				pa = pa->next;
			}
		}
	}

	void Test()
	{
		node* a1 = new node(5);
		node* a2 = new node(10);
		node* a3 = new node(20);
		node* a4 = new node(15);
		node* a5 = new node(25);
		node* a6 = new node(30);
		a1->next = a2;
		a2->next = a3;
		a3->next = a4;
		a4->next = a5;
		a5->next = a6;

		node* b1 = new node(5);
		node* b2 = new node(15);
		node* b3 = new node(35);
		node* b4 = new node(25);
		b1->next = b2;
		b2->next = b3;
		b3->next = b4;
		difference(&a1,b1);
	}
}

int main()
{
	MyList::Test();
	system("pause");
	return 0;
}