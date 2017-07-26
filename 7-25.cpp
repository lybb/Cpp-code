#include "BinaryTree.h"
//��������ǰ���С���ķǵݹ����
//ǰ����������������˼����һ���ģ����ǽ���·���ȫ��ѹ��ջ��Ȼ��ͨ��ջ����ǰ�����������������ʣ�
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

//������������ʵ�ǰ���ڵ��ǰ�����������Ѿ����ʻ���������ΪNULL�����Ӧ������һ��pos�������Ѿ����ʹ����ҽ�㣬�����ǰ��������
//��ΪNULL������pos��ȣ�˵����ʱ�Ѿ����Է��ʸ��ڵ�
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