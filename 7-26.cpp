#include "BinaryTree.h"

//1、判断一个结点是否在一棵二叉树内
//先判断当前根节点是否相等，如果不是，则在左子树中找，如果左子树没有就在右子树找，如果都
//没有就返回false
bool _IsInTree(Node* root,const int key)
{
	if(root == NULL)
		return false;
	if(root->_data == key)
		return true;
	return _IsInTree(root->_left,key) ||  _IsInTree(root->_right,key);
}


//2、判断一棵子树是否是一棵二叉树的子树
//两层嵌套的递归：首先判断root2的当前根节点是否与root1的根节点相同，如果相同，则再判断左右
//结点是否相同；如果不同，则再查找左右子树中是否有相同的根节点，如果有，则继续判断左右结点
bool IsChildTree(Node* root1,Node* root2)
{
	if(root2 == NULL)
		return true;
	if(root1 == NULL)
		return false;
	bool res=false;
	if(root1->_data == root2->_data)
		res=_SubJudge(root1,root2);

	if(res == false)
		res=IsChildTree(root1->_left,root2);

	if(res == false)
		res=IsChildTree(root1->_right,root2);

	return res;
}
bool _SubJudge(Node* root1, Node* root2)
{
	if(root2 == NULL)
		return true;
	if(root1==NULL)
		return false;
	if(root1->_data != root2->_data)
		return false;
	return _SubJudge(root1->_left,root2->_left)
		&& _SubJudge(root1->_right,root2->_right);
}

int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}