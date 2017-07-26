#include "BinaryTree.h"
//二叉树的前、中、后的非递归遍历
//前序遍历和中序遍历的思想是一样的，都是将左路结点全部压入栈，然后通过栈顶向当前根的右子树跳并访问；
void _PrevOrderR(Node* root)
{
	if(root == NULL)
		return ;

	Node* cur = root;
	stack<Node*> s;
	while (cur || !s.empty())
	{
		while (cur)
		{
			cout<<cur->_data<<" ";
			s.push(cur);
			cur = cur->_left;
		}

		Node* tmp = s.top();
		s.pop();
		cur = tmp->_right;
	}
	cout<<endl;
}
void _InOrderR(Node* root)
{
	if(root == NULL)
		return ;
	stack<Node*> s;
	Node* cur = root;
	while (cur || !s.empty())
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->_left;
		}
		Node* top = s.top();
		cout<<top->_data<<" ";
		s.pop();
		cur = top->_right;
	}
	cout<<endl;
}

//后序遍历：访问当前根节点的前提是右子树已经访问或者右子树为NULL，因此应该设置一个pos来保存已经访问过的右结点，如果当前根的右子
//树为NULL或者与pos相等，说明此时已经可以访问根节点
void _LastOrder(Node* root)
{
	if(root == NULL)
		return ;
	Node* cur = root;
	Node* pos = NULL;
	stack<Node*> s;
	while (cur || !s.empty())
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->_left;
		}

		Node* top = s.top();
		if(top->_right == NULL || top->_right == pos)
		{
			cout<<top->_data<<" ";
			pos = top;
			s.pop();
		}
		else
			cur = top->_right;
	}
	cout<<endl;
}