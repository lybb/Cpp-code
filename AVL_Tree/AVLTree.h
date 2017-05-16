#pragma  once
#include <iostream>
using namespace std;


template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}

	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;
	K _key;
	V _value;

	int _bf;	//平衡因子
};


template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{
		_Destory(_root);
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//已经有key，插入失败
				return false;
			}
		}
		cur = new Node(key,value);
		cur->_parent = parent;
		if (cur->_key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		//插入新的结点后，检查是否满足平衡二叉树，不满足就进行旋转
		while(parent)
		{
			if (parent->_left == cur)	//新增结点在左，_bf--
			{
				parent->_bf --;
			}
			else if(parent->_right == cur)	//新增结点在右，_bf++
			{
				parent->_bf ++;
			}
			//判断父亲的平衡因子，若parent->_bf为2、-2，就进行旋转
			if (parent->_bf == 0)
			{
				break;	//parent的平衡因子为0，说明这棵树一定满足平衡二叉树
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				//继续更新平衡因子
				cur = parent;
				parent = cur->_parent;
			}
			else	//parent->_bf == -2 / 2
			{
				if (parent->_bf == -2)
				{
					if(cur->_bf == -1)
						RotateRight(parent);
					else
						RotateLR(parent);
				}
				else
				{
					if (cur->_bf == -1)
						RotateRL(parent);
					else
						RotateLeft(parent);
				}
			}
		}
		return true;
	}
	bool Remove(const K& key)
	{
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(cur->_key > key)
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
				break;	//找到key结点并准备进行删除
			}
		}
		if (cur->_left && cur->_right)	//删除非叶子结点不会破坏平衡，用其左孩子代替
		{
			Node* tmpleft = cur->_left;
			Node* tmpright = cur->_right;
			if (parent->_left == cur)
			{
				parent->_left = tmpleft;
				tmpleft->_parent = parent;
				parent->_bf ++;

				tmpleft->_right = tmpright;
				tmpright->_parent = tmpleft;
				
			}
			else
			{
				parent->_right = tmpleft;
				tmpleft->_parent = parent;
				parent->_bf--;

				tmpleft->_right = tmpright;
				tmpright->_parent = tmpleft;
			}
		}
		else
		{
			if (cur->_left == NULL)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
					parent->_bf++;
				}
				else
				{
					parent->_right = cur->_right;
					parent->_bf--;
				}
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
					parent->_bf++;
				}
				else
				{
					parent->_right = cur->_right;
					parent->_bf--;
				}
			}
		}

	
		//			if (cur->_left == NULL)
		//			{
		//				if (parent->_left == cur)
		//				{
		//					parent->_left = cur->_right;
		//					parent->_bf++;
		//				}
		//				else	//parent->right == cur
		//				{
		//					parent->_right = cur->_right;
		//					parent->_bf--;
		//				}
		//			}
		//			else if (cur->_right == NULL)
		//			{
		//				if (parent->_left == cur)
		//				{
		//					parent->_left = cur->_left;
		//					parent->_bf++;
		//				}
		//				else
		//				{
		//					parent->_right = cur->_left;
		//					parent->_bf--;
		//				}
		//			}
		//			delete cur;
		//			if (parent->_left == NULL && parent->_right == NULL)
		//			{
		//				Node* ppNode = parent->_parent;
		//				if (parent == ppNode->_left)
		//					ppNode->_bf++;
		//				else
		//					ppNode->_bf--;
		//				cur = parent;
		//				parent = ppNode;
		//			}
		//			
		//			if (parent->_bf == 0 || parent->_bf == -1 || parent->_bf == 1)	//继续向上更新
		//			{
		//				cur = parent;
		//				parent = cur->_parent;
		//			}
		//			if (parent->_bf == -1 || parent->_bf == 1)
		//			{
		//				break;
		//			}
		//			//else if (parent->_bf == 0)
		//			//{
		//			//}
		//			else	//parent->_bf == -2 || parent->_bf == 2-------进行旋转
		//			{
		//				if (parent->_bf == 2)
		//				{
		//					if (cur->_bf == 1)
		//						RotateLeft(parent);
		//					else
		//						RotateRL(parent);
		//				}
		//				else	//parent->_bf == -2
		//				{
		//					if (cur->_bf == 1)
		//						RotateLR(parent);
		//					else
		//						RotateRight(parent);
		//				}
		//			}
		//		}
		//		return true;
		//	}
		//}
		return false;
	}

	void _JudgeBf(Node* parent,Node* cur)
	{

		if (parent->_bf == 2)
		{
			if (cur->_bf == 2)

		}
	}

	bool IsBalance()
	{
		//return _IsBalance(_root);
		int height = 0;
		return _IsBalanceOP(_root,height);
	}	
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		if (abs(rightHeight - leftHeight) < 2)
		{
			return true;
		}
		else
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
			return false;
		}
	}
	bool _IsBalanceOP(Node* root,int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}

		int leftHeight = 0;
		if (_IsBalanceOP(root->_left,leftHeight) == false)
		{
			return false;
		}

		int rightHeight = 0;
		if (_IsBalanceOP(root->_right,rightHeight) == false)
		{
			return false;
		}

		if (abs(rightHeight-leftHeight) < 2)//如果平衡因子正确，就将其深度返回给上一层
		{
			height = leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
			return true;
		}
		else
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
			return false;
		}
	}
	int _Height(Node* root)
	{
		if(root == NULL)
			return 0;

		int leftHeight = _Height(root->_left)+1;
		int rightHeight = _Height(root->_right)+1;

		return leftHeight > rightHeight ? leftHeight:rightHeight;
	}
	void RotateLeft(Node* parent)	//左单旋
	{		
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;	//先改变parent的右指针
		if (subRL)	//subRL可能为NULL
		{
			subRL->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			//判断subR应链接在ppNode的左子树还是右子树
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

		subR->_bf = parent->_bf = 0;
	}
	void RotateRight(Node* parent)	//右单旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == NULL)	//说明parent结点为根节点
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			//如果parent不为根节点，判断其在上一个结点的右还是左
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		
		subL->_bf = parent->_bf = 0;
	}
	void RotateLR(Node* parent)		//左右双旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateLeft(parent->_left);
		RotateRight(parent);

		if (bf == 0)		//subLR本身就是新增节点
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if(bf == 1)	//subLR的右子树是新增节点
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else	//bf == -1----subLR的左子树是新增结点
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}
	void RotateRL(Node* parent)		//右左双旋
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateRight(parent->_right);
		RotateLeft(parent);

		if (bf == 0)		//subRL本身就是新增节点
		{
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if(bf == 1)	//subRL的右子树是新增节点
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 1;
		}
		else	//bf == -1----subR L的左子树是新增结点
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = -1;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<"<"<<root->_value<<">"<<" ";
		if (abs(root->_bf) > 1)
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
		}
		_InOrder(root->_right);
	}
	void _Destory(Node* root)
	{
		if (root == NULL)
			return ;
		Node* cur = root;
		if (cur)
		{
			_Destory(cur->_left);
			_Destory(cur->_right);
			delete cur;
		}
	}
protected:
	Node* _root;
};


void TestAVLTree()
{
	//int a1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	//AVLTree<int,int> t1;
	//for (size_t i=0; i<sizeof(a1)/sizeof(a1[0]); ++i)
	//{
	//	t1.Insert(a1[i],i);
	//}
	//t1.InOrder();
	//cout<<"Balance?---"<<t1.IsBalance()<<endl;

	int a2[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int,int>  t2;
	for (size_t i=0; i<sizeof(a2)/sizeof(a2[0]); ++i)
	{
		t2.Insert(a2[i],i);
	}
	cout<<"Balance?---"<<t2.IsBalance()<<endl;
	t2.Remove(1);
	t2.Remove(3);
	//t2.Remove(7);
	t2.InOrder();
	cout<<"Balance?---"<<t2.IsBalance()<<endl;
}