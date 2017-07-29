#include "BinaryTree.h"

//将二叉搜索树转换成双向链表
//思路分析：首先应该找到最左节点，作为双向链表的头；根据中序遍历的顺序，分别递归当前根的左右子树，
//last指向转换完成后的双向链表的最后一个结点，利用last来改变结点的右指针。

void _TreeToList(Node* root, Node** last)
{
	if(root == NULL)
		return ;
	if(root->_left)
		_TreeToList(root->_left,last);
	root->_left = *last;
	if(*last)
		(*last)->_right = root;
	*last = root;
	if(root->_right)
		_TreeToList(root->_right,last);
}
Node* TreeToList()
{
	if(_root == NULL)
		return NULL;

	Node* cur = _root;
	while (cur && cur->_left)
		cur = cur->_left;
	Node* last = NULL;
	Node* head = cur;
	_TreeToList(_root,&last);
	return head;
}