//题目要求
//已知集合A和B的元素分别用不含头结点的单链表存储，函数difference()用于求解集合A与B的差集，并将结果保
//存在集合A的单链表中。例如，若集合A={5,10,20,15,25,30}，集合B={5,15,35,25}，完成计算后A={10,20,30}。 
//链表结点的结构类型定义如下： 
//
//struct node 
//{ 
//	int elem; 
//	node* next; 
//}; 
//请完成函数void difference(node** LA , node* LB)；


//思路分析：每遍历LA的一个结点都在LB中查找是否有相同结点，如果有，则在LA中将其free掉；否则就判断LA的下一个结点
//这里需要注意的是，LA传的是二级指针，如果第一个结点就有与LB相同的结点，就应该更新LA锁指向的第一个结点

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
			pb = LB;	//pb每次都从头开始遍历一边，查找与A的并集
			while (pb && pb->elem != pa->elem)
			{
				pb = pb->next;
			}

			if(pb)	//pb不为NULL时表示有与当前pa重复的结点
			{
				del = pa;
				pa = pa->next;
				if(!prev)
					*LA = pa;	//更新LA的头
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