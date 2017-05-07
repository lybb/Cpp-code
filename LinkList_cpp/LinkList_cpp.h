#include<iostream>
using namespace std;

typedef int DataType;

struct Node
{
	friend ostream& operator<<(ostream& os,Node& node);
	Node(DataType x)
		:data(x)
		,next(NULL)
	{	}

	DataType data;
	Node* next;
};


struct LinkList
{
	friend ostream& operator<<(ostream& os,LinkList& list);
	LinkList()
		:head(NULL)
		,tail(NULL)
	{	}
	~LinkList()
	{
		Node* cur = head;
		while(cur)
		{
			Node* tmp = cur;
			cur = cur->next;
			delete tmp;
		}
	}
	void Display();
	void PushBack(const DataType& x);
	void PopBack();
	void PushFront(const DataType& x);
	void PopFront();
	void Insert(Node* pos,const DataType& x);
	void Remove(DataType x);
	void RemoveAll(DataType x);
	void Sort();

	Node* Find(DataType x)
	{
		Node* cur = head;
		if(NULL == head)
		{
			cout<<"LinkList is empty1"<<endl;
		}
		while(cur)
		{
			if(cur->data == x)
				return cur;
			cur = cur->next;
		}
	}
private:
	Node* head;
	Node* tail;
};
