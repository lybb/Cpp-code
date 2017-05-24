#pragma once

#include <iostream>
using namespace std;

#include <assert.h>

enum PointerTag
{
	LINK,	//LINK = 0 表示指向左孩子指针---------表示结点
	THREAD,	//THREAD = 1表示指向前驱或后继的线索----------表示线索
};

//线索二叉树的结点
template<class T>
struct BinaryTreeNode_Thd
{
	//构造函数
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
	BinaryTreeNode_Thd* _left;	//左孩子
	BinaryTreeNode_Thd* _right;	//右孩子
	PointerTag _lefttag;	//右孩子线索标志
	PointerTag _righttag;	//左孩子线索标志

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

	//前序线索化
	void PrevOrderThread()
	{
		Node* prev = NULL;
		_PrevOrderThread(_root,prev);
	}
	//前序线索遍历
	void PrevOrder()
	{
		_PrevOrder(_root);
	}

	//中序线索化
	void InOrderThread()
	{
		Node* prev = NULL;
		_InOrderTh(_root,prev);
	}
	//中序线索化的遍历
	void InOrder()
	{
		_InOrder(_root);
	}
public:
	//构造一个树
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

	//前序线索化
	void _PrevOrderThread(Node* cur, Node*& prev)	//prev要用引用
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
	//前序线索化的遍历
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

	//中序线索化
	void _InOrderTh(Node* cur,Node*& prev)
	{
		if (cur == NULL)
			return ;
		if (cur)
		{
			_InOrderTh(cur->_left,prev);
			if (cur->_left == NULL)	//线索化当前结点
			{
				cur->_lefttag = THREAD;
				cur->_left = prev;
			}
			if (prev && prev->_right == NULL)	//线索化前一个结点
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

			cur = cur->_right;	//调到右树继续访问
		}
		cout<<endl;
	}
protected:
	Node* _root;
};

//中序遍历的迭代器实现
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
	Self& operator++()	//找右树的最左结点
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
	Self& operator--()	//找左树的最右结点
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