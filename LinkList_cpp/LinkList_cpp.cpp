#include"LinkList_cpp.h"

ostream& operator<<(ostream& os,Node& node)
{
	os<<node.data<<" ";
	return os;
}

ostream& operator<<(ostream& os,LinkList& list)
{
	Node* cur = list.head;
	while(cur)
	{
		os<<(*cur);
		cur = cur->next;
	}
	return os;
}

void LinkList::Display()
{
	Node* cur = head;
	while(cur)
	{
		cout<<cur->data<<" ";
		cur = cur->next;
	}
	cout<<endl;
}

void LinkList::PushBack(const DataType& x)
{
	Node* tmp = new Node(x);
	if(tail != NULL)
	{
		tail->next = tmp;
		tail = tmp;
	}
	else
	{
		head = tmp;
		tail = tmp;
	}
}
void LinkList::PopBack()
{
	Node* cur = head;
	if(NULL == head)
	{
		cout<<"LinkList is empty!"<<endl;
	}
	else if(tail == head)
	{
		head = NULL;
		tail = NULL;
	}
	else
	{
		while(cur->next != tail)
		{
			cur = cur->next;
		}
		cur->next = NULL;
	}
}
void LinkList::PushFront(const DataType& x)
{
	Node* tmp = new Node(x);
	if(NULL == head)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tmp->next = head;
		head = tmp;
	}
}
void LinkList::PopFront()		
{
	Node* del = head;
	if(NULL == head)
	{
		cout<<"LinkList is empty!"<<endl;
	}
	else
	{
		head = head->next;
	}
	if(head == tail)
	{
		cout<<"LinkList has no data!"<<endl;
	}
}
void LinkList::Insert(Node* pos,const DataType& x)
{
	Node* newnode = new Node(x);
	Node* cur = head;
	Node* prev = head;
	if(NULL == head)
	{
		head = newnode;
		return ;
	}
	if(head == pos)
	{
		newnode->next = head;
		head = newnode;
		return ;
	}
	while(cur != pos)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = newnode;
	newnode->next = cur;
}
void LinkList::Remove(DataType x)
{
	Node* ret = Find(x);
	Node* cur = head;
	while(cur->next != ret)
	{
		cur = cur->next;
	}
	cur->next = ret->next;
}
void LinkList::RemoveAll(DataType x)
{
	Node* cur = head;
	Node* prev = head;
	if(cur->next == NULL)
	{
		if(cur->data == x)
		{
			head = NULL;
		}
	}
	while(cur)
	{
		if(prev->data == x)
		{
			head = prev->next;
		}
		if(cur->data == x)
		{
			prev->next = cur->next;
			cur = prev;
		}
		prev = cur;
		cur = cur->next;
	}
}
void LinkList::Sort()
{
	Node* tail = NULL;
	Node* cur = NULL;
	if((head == NULL)||(head->next == NULL))
	{
		cout<<"LinkList do not need to sort!"<<endl;
		return ;
	}
	cur = head;
	while(cur != tail)
	{
		while(cur->next != tail)
		{
			if(cur->data < cur->next->data)
			{
				DataType tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
			}
			cur = cur->next;
		}
		tail = cur;
		cur = head;
	}
}