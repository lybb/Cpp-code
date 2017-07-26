#include "BinaryTree.h"

//1���ж�һ������Ƿ���һ�ö�������
//���жϵ�ǰ���ڵ��Ƿ���ȣ�������ǣ��������������ң����������û�о����������ң������
//û�оͷ���false
bool _IsInTree(Node* root,const int key)
{
	if(root == NULL)
		return false;
	if(root->_data == key)
		return true;
	return _IsInTree(root->_left,key) ||  _IsInTree(root->_right,key);
}


//2���ж�һ�������Ƿ���һ�ö�����������
//����Ƕ�׵ĵݹ飺�����ж�root2�ĵ�ǰ���ڵ��Ƿ���root1�ĸ��ڵ���ͬ�������ͬ�������ж�����
//����Ƿ���ͬ�������ͬ�����ٲ��������������Ƿ�����ͬ�ĸ��ڵ㣬����У�������ж����ҽ��
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