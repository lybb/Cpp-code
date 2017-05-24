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

	K _key;	//关键字
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
	
	//非递归
	bool Find(const K& key)	//查找一个数
	{
		//空树
		if (_root == NULL)
			return false;
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key > key)		//查找的数在左树
			{
				cur = cur->_left;
			}
			else if(cur->_key < key)	//查找的数在右树
			{
				cur = cur->_right;
			}
			else						//找到key
			{
				return true;
			}
		}
		if (cur == NULL)			//没找到
		{
			return false;
		}
	}
	//递归
	bool FindRec(const K& key)
	{
		return _FindRec(_root,key);
	}

	//非递归
	bool Insert(const K& key)	//插入一个数
	{
		//空树
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
			if (cur->_key > key)		//在左树
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)	//在右树
			{
				parent = cur;
				cur = cur->_right;
			}
			else						//已经存在
			{
				return false;
			}
		}
		//不存在
		if (parent->_key > key)		//找到正确位置，判断插入左子树还是右子树
		{
			parent->_left = new Node(key);
		}
		else
		{
			parent->_right = new Node(key);
		}
	}
	//递归
	bool InsertRec(const K& key)	//插入一个数
	{
		return _InsertRec(_root,key);
	}

	//非递归
	bool Remove(const K& key)
	{
		//空树
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
				//找到key所在的结点----删除
				if (cur->_left == NULL)
				{
					if (parent == NULL)
					{
						_root = _root->_right;
					}
					else
					{
						//判断cur是parent的左孩子还是右孩子
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
				else	//左右节点都不为空
				{
					parent = cur;
					//找cur右树的最左(小)结点，并利用替换法删除
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
	//递归
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
		//空树
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
			return false;	//已经存在key的结点
	}
	bool _RemoveRec(Node*& root,const K& key)
	{
		//空树
		if (root == NULL)
			return false;

		if (root->_key > key)
			return _RemoveRec(root->_left,key);
		else if (root->_key < key)
			return _RemoveRec(root->_right,key);
		//找到要删除的结点
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
	//cout<<"Find(9): "<<bst1.FindRec(9)<<endl;	//递归----1
	//cout<<"Find(12): "<<bst1.Find(12)<<endl;	//----0
	//cout<<"Find(12): "<<bst1.FindRec(12)<<endl;	//递归----0
	//cout<<"Insert(2): "<<bst1.InsertRec(2)<<endl;
	//bst1.InOrder();
	//cout<<"Insert(20): "<<bst1.InsertRec(20)<<endl;
	//bst1.InOrder();
	//cout<<"Remove(2): "<<bst1.Remove(2)<<endl;		//叶子节点----1
	//bst1.InOrder();
	//cout<<"Remove(9): "<<bst1.Remove(9)<<endl;		//只有一个孩子节点----1
	//bst1.InOrder();
	//cout<<"Remove(5): "<<bst1.Remove(5)<<endl;		//非叶子节点----1
	//bst1.InOrder();
	//cout<<"Remove(7): "<<bst1.Remove(7)<<endl;		//非叶子节点----1
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
	//cout<<"Remove(13): "<<bst1.Remove(13)<<endl;	//不存在----0
	//bst1.InOrder();
}