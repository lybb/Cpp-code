#include "BinaryTree.h"

//������������ת����˫������
//˼·����������Ӧ���ҵ�����ڵ㣬��Ϊ˫�������ͷ���������������˳�򣬷ֱ�ݹ鵱ǰ��������������
//lastָ��ת����ɺ��˫����������һ����㣬����last���ı������ָ�롣

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