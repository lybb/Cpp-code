#pragma once

#include<queue>
#include<stack>
#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x = T())
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}

	T _data;		//��ֵ��
	BinaryTreeNode<T>* _left;	//������
	BinaryTreeNode<T>* _right;	//������
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _CreatTree(a,size,index,invalid);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			BinaryTree<T> tmp(t);	//��������
			std::swap(_root,tmp._root);
		}
	}
	~BinaryTree()
	{
		_Destory(_root);
	}

	void PrevOrder()		//ǰ��
	{
		if (_root)
			_prevOrder(_root);
		cout<<endl;
	}
	void InOrder()		//����
	{
		if (_root)
			_inOrder(_root);
		cout<<endl;
	}
	void PostOrder()	//����
	{
		if(_root)
			_postOrder(_root);
		cout<<endl;
	}
	void LevelOrder()	//����
	{
		_LevelOrder(_root);
	}
	void PrevOrder_NonR()
	{
		_PrevOrder_NonR(_root);
	}
	void InOrder_N0nR()
	{
		_InOrder_N0nR(_root);
	}
	void PostOrder_NonR()
	{
		_PostOrder_NonR(_root);
	}
	Node* Find(const T& x)
	{
		return _find(_root,x);
	}
	size_t Size()	//������
	{
		return _Size(_root);
	}
	size_t Depth()	//���
	{
		return _Depth(_root);
	}
	size_t LeafSize()	//Ҷ�ӽ��ĸ���
	{
		return _LeafSize(_root);
	}
	size_t GetKLevel(const int& k)		//��K����ĸ���
	{
		return _GetKLevel(_root,k);
	}

	Node* GetRoot()
	{
		return _root;
	}
protected:
	Node* _CreatTree(T* a,size_t size,size_t& index,const T& invalid)
	{
		assert(a);
		Node* root = NULL;
		if((index<size) && a[index]!=invalid)
		{
			root = new Node(a[index]);		//������ڵ�
			root->_left = _CreatTree(a,size,++index,invalid);	//������
			root->_right = _CreatTree(a,size,++index,invalid);	//������
		}
		return root;
	}
	Node* _Copy(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		Node* newroot = NULL;
		if (root)
		{
			newroot = new Node(root->_data);
			newroot->_left = _Copy(root->_left);
			newroot->_right = _Copy(root->_right);
		}
		return newroot;
	}
	void _Destory(Node* root)
	{
		if (root == NULL)
			return;

		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	void _prevOrder(Node* root)	//ǰ---��������---1 2 3 4 5 6
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		if(cur)
		{
			cout<<cur->_data<<" ";
			_prevOrder(cur->_left);
			_prevOrder(cur->_right);
		}
	}
	void _inOrder(Node* root)		//��---�󡢸�����---3 2 4 1 6 5
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		if (cur)
		{
			_inOrder(cur->_left);
			cout<<cur->_data<<" ";
			_inOrder(cur->_right);
		}
	}
	void _postOrder(Node* root)		//��---���ҡ���---3 4 2 6 5 1
	{
		if (root == NULL)
			return ;
		Node* cur = root;
		if (cur)
		{
			_postOrder(cur->_left);
			_postOrder(cur->_right);
			cout<<cur->_data<<" ";
		}
	}
	void _LevelOrder(Node* root)
	{
		if (NULL == root)
			return ;
		queue<Node*> q;
		Node* cur = root;
		q.push(root);
		while (!q.empty())	//���в�Ϊ��˵�������ݿ��Է���
		{
			Node* tmp = q.front();	//�Ը���������������
			cout<<tmp->_data<<" ";
			if (tmp->_left)
				q.push(tmp->_left);
			if (tmp->_right)
				q.push(tmp->_right);
			q.pop();
		}
		cout<<endl;
	}

	void _PrevOrder_NonR(Node* root)	//�ǵݹ�--ǰ��
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		stack<Node*> s;
		while (cur || !s.empty())		//cur != NULL˵����Ȼ���������Ա�����
										//!s.empty()  ˵��ջ��Ϊ��ʱ���������ݱ�����
		{
			while (cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);
				Node* tmp = s.top();
				T x=tmp->_data;
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;	//���ʵ�ǰ���ڵ��������
		}
		cout<<endl;
	}
	void _InOrder_N0nR(Node* root)		//�ǵݹ�--����
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		stack<Node*> s;
		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();	//��ʱջ������ǵ�ǰ�����ĸ��ڵ�
			cout<<top->_data<<" ";
			s.pop();
			cur = top->_right;		//����������Ϊ������������������
		}
		cout<<endl;
	}
	void _PostOrder_NonR(Node* root)	//�ǵݹ�--����
	{
		Node* cur = root;
		Node* pos = root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();

			if (top->_right == NULL || top->_right == pos)
				//top����ǵ�ǰ�ĸ��ڵ㣬��top��������Ϊ�ջ���top��������Ϊpos��˵���������Ѿ���������
				//��ʱ�Ϳ��Է��ʵ�ǰ�ĸ��ڵ���
			{
				cout<<top->_data<<" ";
				pos = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout<<endl;
	}
	Node* _find(Node* root,const T& data)
	{
		if (root == NULL)	//����
			return NULL;
		if(root->_data == data)	//���ڵ������ΪҪ���ҵ�����
			return root;

		Node* ret = _find(root->_left,data);	//�ȱ���������
		if (ret == NULL)	//�������Ѿ������겢��û���ҵ�����ʼ���������в���
		{
			ret = _find(root->_right,data);
		}
		return ret;
	}

	//size_t _Size(Node* root)
	//{
	//	if (root == NULL)
	//		return NULL;

	//	size_t sz = 0;
	//	sz =  _Size(root->_left)+ _Size(root->_right);
	//	return sz+1;	//������ + ������ + ���ڵ�
	//}
	size_t _Size(Node* root)		//ÿ��һ���ڵ㣬count++
	{
		if (root == NULL)
			return 0;
		static size_t count = 0;
		++count;
		if (root)
		{
			_Size(root->_left);
			_Size(root->_right);
		}
		return count;
	}
	size_t _Depth(Node* root)
	{
		size_t leftsz = 0;
		size_t rightsz = 0;
		if (NULL == root)
			return 0;
		else
		{
			leftsz += _Depth(root->_left);		//���������������
			rightsz += _Depth(root->_right);	//���������������
		}
		return leftsz>rightsz?leftsz+1:rightsz+1;	//��������������ļ��ϸ��ڵ㲢����
	}
	size_t _LeafSize(Node* root)
	{
		if (NULL == root)
			return 0;
		Node* cur = root;
		static size_t sz = 0;
		if (cur)
		{
			if (cur->_left == NULL && cur->_right == NULL)
			{
				sz+=1;
			}
			else
			{
				_LeafSize(cur->_left);
				_LeafSize(cur->_right);
			}
		}
		return sz;
	}
	size_t _GetKLevel(Node* root,const int& k)
	{
		if (NULL == root)
			return 0;
		if (k == 1 && root)		//��һ�㣬���Ҳ�Ϊ������ֻ��һ�����ڵ�
			return 1;
		Node* cur = root;
		size_t sz = 0;
		if (cur)
 		{
			sz += _GetKLevel(cur->_left,k-1);
			sz += _GetKLevel(cur->_right,k-1);
		}
	}
protected:
	Node* _root;
};



void TestBinaryTree()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> T1(a2,15,'#');
	BinaryTree<int> t2(t1);
	BinaryTree<int> t3 = t1;
	t1.PrevOrder();			//1 2 3 4 5 6
	t1.PrevOrder_NonR();	//
	t1.InOrder();			//3 2 4 1 6 5
	t1.InOrder_N0nR();
	t1.PostOrder();			//3 4 6 2 5 1
	t1.PostOrder_NonR();

	T1.PrevOrder();	
	T1.PrevOrder_NonR();
	T1.InOrder();
	T1.InOrder_N0nR();
	T1.PostOrder();
	T1.PostOrder_NonR();
	cout<<"����"<<endl;
	t1.LevelOrder();
	T1.LevelOrder();

	//BinaryTreeNode<int>* ret = t1.Find(6);
	//cout<<"Find(6):"<<ret->_data<<endl;
	//BinaryTreeNode<int>* ret2 = t1.Find(8);
	//cout<<"Find(8)"<<ret2<<endl;
	//cout<<"Size:"<<t1.Size()<<endl;
	//cout<<"Size:"<<T1.Size()<<endl;
	//cout<<"Depth:"<<t1.Depth()<<endl;
	//cout<<"Depth:"<<T1.Depth()<<endl;
	//cout<<"LeafSize:"<<t1.LeafSize()<<endl;
	//cout<<"LeafSize:"<<T1.LeafSize()<<endl;
	//cout<<"GetKlevelNode:"<<t1.GetKLevel(3)<<endl;
	//cout<<"GetKlevelNode:"<<T1.GetKLevel(4)<<endl;
}																																																																																																												