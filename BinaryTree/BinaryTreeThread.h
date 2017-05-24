#pragma once

#include <iostream>
using namespace std;

#include <assert.h>

enum PointerTag
{
	LINK,	//LINK = 0 ��ʾָ������ָ��---------��ʾ���
	THREAD,	//THREAD = 1��ʾָ��ǰ�����̵�����----------��ʾ����
};

//�����������Ľ��
template<class T>
struct BinaryTreeNode_Thd
{
	//���캯��
	BinaryTreeNode_Thd()
		:_data(0)
		,_left(NULL)
		,_right(NULL)
		,_lefttag(LINK)
		,_righttag(LINK)
	{}

	BinaryTreeNode_Thd(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_lefttag(LINK)
		,_righttag(LINK)
	{}

	T _data;
	BinaryTreeNode_Thd* _left;	//����
	BinaryTreeNode_Thd* _right;	//�Һ���
	PointerTag _lefttag;	//�Һ���������־
	PointerTag _righttag;	//����������־

};

template<class T>
class BinaryTreeThread
{
	typedef BinaryTreeNode_Thd<T> Node;
public:
 	typedef InoderThreadIterator<T,T&,T*> Iterator;
	typedef InoderThreadIterator<T,const T&,const T*> ConstIterator;

	Iterator Begin()
	{
		assert(_root);
		Node* cur = _root;
		while (cur && cur->_lefttag == LINK)
		{
			cur = cur->_left;
		}
		return Iterator(cur);
	}
	Iterator End()
	{
		assert(_root);
		Node* cur = _root;
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}
		return Iterator(cur);
	}

	BinaryTreeThread(T* a,size_t size,const T& invilue)
	{
		size_t index = 0;
		_root = _CreatTree(a,size,index,invilue);
	}

	//ǰ��������
	void PrevOrderThread()
	{
		Node* prev = NULL;
		_PrevOrderThread(_root,prev);
	}
	//ǰ����������
	void PrevOrder()
	{
		_PrevOrder(_root);
	}

	//����������
	void InOrderThread()
	{
		Node* prev = NULL;
		_InOrderTh(_root,prev);
	}
	//�����������ı���
	void InOrder()
	{
		_InOrder(_root);
	}
public:
	//����һ����
	Node* _CreatTree(T* a,size_t size,size_t& index,const T& invilue)
	{
		assert(a);
		Node* newtree = NULL;
		if ((index < size) && (a[index] != invilue))
		{
			newtree = new Node(a[index]);
			newtree->_left = _CreatTree(a,size,++index,invilue);
			newtree->_right = _CreatTree(a,size,++index,invilue);
		}
		return newtree;
	}

	//ǰ��������
	void _PrevOrderThread(Node* cur, Node*& prev)	//prevҪ������
	{
		if(cur == NULL)
			return ;

		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_lefttag = THREAD;
		}
 		if (prev && prev->_right == NULL)
		{
			prev->_righttag = THREAD;
			prev->_right = cur;
		}
 		prev = cur;
		if (cur->_lefttag == LINK)
		{
			_PrevOrderThread(cur->_left,prev);
		}
		if (cur->_righttag == LINK)
		{
			_PrevOrderThread(cur->_right,prev);
		}
	}
	//ǰ���������ı���
	void _PrevOrder(Node* cur)
	{
		if(cur == NULL)
			return ;
		while (cur)
		{
			while (cur && cur->_lefttag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";
			cur = cur->_right;
			//if (cur && cur->_righttag == THREAD)
			//{
			//	cur = cur->_right;
			//	cout<<cur->_data<<" ";
			//}
			//if(cur)
			//	cur = cur->_right;
		}
		cout<<endl;
	}

	//����������
	void _InOrderTh(Node* cur,Node*& prev)
	{
		if (cur == NULL)
			return ;
		if (cur)
		{
			_InOrderTh(cur->_left,prev);
			if (cur->_left == NULL)	//��������ǰ���
			{
				cur->_lefttag = THREAD;
				cur->_left = prev;
			}
			if (prev && prev->_right == NULL)	//������ǰһ�����
			{
				prev->_righttag = THREAD;
				prev->_right = cur;
			}
			prev = cur;
			_InOrderTh(cur->_right,prev);
		}
	}
	void _InOrder(Node* cur)
	{
		if (cur == NULL)
			return ;
		while (cur)
		{
			while(cur->_lefttag == LINK)
				cur = cur->_left;

			cout<<cur->_data<<" ";

			while (cur && cur->_righttag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			cur = cur->_right;	//����������������
		}
		cout<<endl;
	}
protected:
	Node* _root;
};

//��������ĵ�����ʵ��
template<class T,class Ref, class Ptr>
struct InoderThreadIterator
{
	typedef BinaryTreeNode_Thd<T> Node;
	typedef InoderThreadIterator<T,Ref,Ptr> Self;

	InoderThreadIterator()
	{}
	InoderThreadIterator(Node* node)
		:_node()
	{}

	Ref operator*()
	{
		assert(_node);
		return _node->_data;
	}
	Self& operator++()	//��������������
	{
		assert(_node);
		if (_node->_righttag == LINK)
		{
			if (_node->_left)
			{
				
			}
		}
	}
	Self operator++(int)
	{

	}
	Self& operator--()	//�����������ҽ��
	{

	}
	Self operator--(int)
	{

	}
	bool operator!=(const Self s)const
	{
		return _node != s._node;
	}

	Node* _node;
};


void TestBinaryTreeThread()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTreeThread<int> t1(a1,10,'#');
	BinaryTreeThread<int> t2(a2,15,'#');

	//t1.PrevOrderThread();
	//t1.PrevOrder();
	//t2.PrevOrderThread();
	//t2.PrevOrder();

	t1.InOrderThread();
	t1.InOrder();
	t2.InOrderThread();
	t2.InOrder();
}