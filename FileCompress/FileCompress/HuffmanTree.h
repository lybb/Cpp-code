#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"


template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode()
	{}

	HuffmanTreeNode(const T& x)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_weight(x)
	{}
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _weight;
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
	{}
	HuffmanTree(T* arr,size_t sz,const T& invalid)
	{
		assert(arr);

		//构建哈夫曼树需要小堆，因为每次需要从堆顶拿出最小的值
		struct NodeLess
		{
			bool operator()(Node* left,Node* right)const
			{
				return (left->_weight < right->_weight);
			}
		};

		//1.将所有数据插入一个堆中
		Heap<Node*,NodeLess> minHeap;

		for (size_t idx=0; idx<sz; idx++)
		{
			if(arr[idx] != invalid)
			{
				Node* node = new Node(arr[idx]);
				minHeap.Push(node);
			}
		}

		//2.构建HuffmanTree
		while (minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* root = new Node(left->_weight + right->_weight);
			root->_left = left;
			root->_right = right;
			left->_parent = root;
			right->_parent = root;

			minHeap.Push(root);
		}

		//3.得到根节点
		_root = minHeap.Top();
		minHeap.Pop();
	}
	~HuffmanTree()
	{
		_Destory(_root);
	}
	Node* GetRoot()
	{
		return _root;
	}
protected:
	void _Destory(Node* root)
	{
		if(root == NULL)
			return ;

		Node* del = root;
		if(del)
		{
			_Destory(del->_left);
			_Destory(del->_right);
			delete del;
			del = NULL;
		}
	}
private:
	Node* _root;
};
