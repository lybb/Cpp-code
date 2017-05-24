#pragma once

#include <iostream>
using namespace std;
#include <assert.h>


template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode()
		:_key(0)
		,_left(NULL)
		,_right(NULL)
	{}
	BinarySearchTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}

	K _key;	//�ؼ���
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	
};

template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> Node;
public:
	BinarySearchTree()
	{}
	BinarySearchTree(K* a,size_t size)
		:_root(NULL)
	{
		assert(a);
		for (size_t i=0; i<size; ++i)
		{
			Insert(a[i]);
			//InsertRec(a[i]);
		}
	}
	~BinarySearchTree()
	{
		_Destory(_root);
	}
	
	//�ǵݹ�
	bool Find(const K& key)	//����һ����
	{
		//����
		if (_root == NULL)
			return false;
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key > key)		//���ҵ���������
			{
				cur = cur->_left;
			}
			else if(cur->_key < key)	//���ҵ���������
			{
				cur = cur->_right;
			}
			else						//�ҵ�key
			{
				return true;
			}
		}
		if (cur == NULL)			//û�ҵ�
		{
			return false;
		}
	}
	//�ݹ�
	bool FindRec(const K& key)
	{
		return _FindRec(_root,key);
	}

	//�ǵݹ�
	bool Insert(const K& key)	//����һ����
	{
		//����
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = _root;
		//Node* newNode = new Node(key);
		while (cur)
		{
			if (cur->_key > key)		//������
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)	//������
			{
				parent = cur;
				cur = cur->_right;
			}
			else						//�Ѿ�����
			{
				return false;
			}
		}
		//������
		if (parent->_key > key)		//�ҵ���ȷλ�ã��жϲ�������������������
		{
			parent->_left = new Node(key);
		}
		else
		{
			parent->_right = new Node(key);
		}
	}
	//�ݹ�
	bool InsertRec(const K& key)	//����һ����
	{
		return _InsertRec(_root,key);
	}

	//�ǵݹ�
	bool Remove(const K& key)
	{
		//����
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//�ҵ�key���ڵĽ��----ɾ��
				if (cur->_left == NULL)
				{
					if (parent == NULL)
					{
						_root = _root->_right;
					}
					else
					{
						//�ж�cur��parent�����ӻ����Һ���
						if (parent->_left == cur)
							parent->_left = cur->_right;
						else if(parent->_right == cur)
							parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)
					{
						_root = _root->_left;
					}
					else
					{
						if(parent->_left == cur)
							parent->_left = cur->_left;
						else if(parent->_right == cur)
							parent->_right = cur->_left;
					}
				}
				else	//���ҽڵ㶼��Ϊ��
				{
					parent = cur;
					//��cur����������(С)��㣬�������滻��ɾ��
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						parent = minRight;
						minRight = minRight->_left;
					}
					cur->_key = minRight->_key;

					if(parent->_left == minRight)
						parent->_left = minRight->_right;
					else
						parent->_right = minRight->_right;

					delete minRight;
				}
				return true;
			}
		}
		return false;
	}
	//�ݹ�
	bool RemoveRec(const K& key)
	{
		return _RemoveRec(_root,key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return ;
		Node* cur = root;
		if (cur)
		{
			_InOrder(cur->_left);
			cout<<cur->_key<<" ";
			_InOrder(cur->_right);
		}
	}
	bool _FindRec(Node*& root,const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key > key)
		{
			_FindRec(root->_left,key);
		}
		else if (root->_key < key)
		{
			_FindRec(root->_right,key);
		}
		else
		{
			return true;
		}
	}
	bool _InsertRec(Node*& root,const K& key)
	{
		//����
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}

		Node* cur = root;
		if (cur->_key > key)
			return _InsertRec(cur->_left,key);
		else if (cur->_key < key)
			return _InsertRec(cur->_right,key);
		else
			return false;	//�Ѿ�����key�Ľ��
	}
	bool _RemoveRec(Node*& root,const K& key)
	{
		//����
		if (root == NULL)
			return false;

		if (root->_key > key)
			return _RemoveRec(root->_left,key);
		else if (root->_key < key)
			return _RemoveRec(root->_right,key);
		//�ҵ�Ҫɾ���Ľ��
		else
		{
			Node* parent = root;
			Node* cur = root;
			if (root->_left == NULL)
				root = root->_right;
			else if(root->_right == NULL)
				root = root->_left;
			else
			{
				parent = root;
				root = root->_right;
				while (root->_left)
				{
					root = root->_left;
				}

				if (parent->_left == root)
					parent->_left = root;
				else
					parent->_right = root;
			}
			return true;
		}
		
	}
	void _Destory(Node* root)
	{
		Node* del = root;
		if (del)
		{
			_Destory(del->_left);
			_Destory(del->_right);
			delete del;
			del = NULL;
		}
	}
protected:
	Node* _root;
};


void TestBinarySearchTree()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	int size = sizeof(a)/sizeof(a[0]);
	BinarySearchTree<int> bst1(a,size);
	bst1.InOrder();
	//cout<<"Find(9): "<<bst1.Find(9)<<endl;		//----1
	//cout<<"Find(9): "<<bst1.FindRec(9)<<endl;	//�ݹ�----1
	//cout<<"Find(12): "<<bst1.Find(12)<<endl;	//----0
	//cout<<"Find(12): "<<bst1.FindRec(12)<<endl;	//�ݹ�----0
	//cout<<"Insert(2): "<<bst1.InsertRec(2)<<endl;
	//bst1.InOrder();
	//cout<<"Insert(20): "<<bst1.InsertRec(20)<<endl;
	//bst1.InOrder();
	//cout<<"Remove(2): "<<bst1.Remove(2)<<endl;		//Ҷ�ӽڵ�----1
	//bst1.InOrder();
	//cout<<"Remove(9): "<<bst1.Remove(9)<<endl;		//ֻ��һ�����ӽڵ�----1
	//bst1.InOrder();
	//cout<<"Remove(5): "<<bst1.Remove(5)<<endl;		//��Ҷ�ӽڵ�----1
	//bst1.InOrder();
	//cout<<"Remove(7): "<<bst1.Remove(7)<<endl;		//��Ҷ�ӽڵ�----1
	//bst1.InOrder();
	//bst1.Remove(0);
	//bst1.Remove(1);
	//bst1.Remove(2);
	//bst1.Remove(3);
	//bst1.Remove(4);
	//bst1.Remove(5);
	//bst1.Remove(6);
	//bst1.Remove(7);
	//bst1.Remove(8);
	//bst1.Remove(9);
	bst1.RemoveRec(0);
	bst1.InOrder();
	bst1.RemoveRec(1);
	bst1.InOrder();
	bst1.RemoveRec(2);
	bst1.InOrder();
	bst1.RemoveRec(3);
	bst1.InOrder();
	bst1.RemoveRec(4);
	bst1.InOrder();
	bst1.RemoveRec(5);
	bst1.InOrder();
	bst1.RemoveRec(6);
	bst1.InOrder();
	bst1.RemoveRec(7);
	bst1.InOrder();
	bst1.RemoveRec(8);
	bst1.InOrder();
	bst1.RemoveRec(9);
	bst1.InOrder();
	//cout<<"Remove(13): "<<bst1.Remove(13)<<endl;	//������----0
	//bst1.InOrder();
}