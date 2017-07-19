#include <stack>
#include <iostream>
using namespace std;

//1.ʵ��һ��ջStack��Ҫ��ʵ��Push����ջ����Pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1) 


//����ջʵ��
//ʵ��һ����Сջ��ά������ջ��minS��s��s����һ��Ĳ��룬minS�ڱ�֤��С��ֵ��ջ���������ֵxֻҪС�ڵ�ǰminSջ��ֵʱ����minSջ��
//������Сֵʱ�Ϳ���ֱ�ӷ���minSջ����ֵ
//class MinStack
//{
//public:
//	void Push(int x)
//	{
//		s.push(x);
//		if(minS.empty() || x<=minS.top())
//			minS.push(x);
//	}
//	void Pop()
//	{
//		if(s.top() == minS.top())
//			minS.pop();
//		s.pop();
//	}
//	int Min()
//	{
//		if(!minS.empty())
//			return minS.top();
//	}
//private:
//	stack<int> minS;
//	stack<int> s;
//};

//һ��ջʵ��
//˼·��������ջΪ��ʱ������һ�β����ֵ�������Σ������ô����ݼ�¼Ϊmin���Ժ�ÿ����һ�����ͺ�s.top()���Ƚϣ����xС��topֵ�������min�����ڲ���x֮��
//�ٽ�minֵ����һ��---��֤��min��Զ��ջ��
class MinStack
{
public:
	void Push(int x)
	{
		if(s.empty())
		{
			s.push(x);
			s.push(x);
			min = x;
		}
		else
		{
			if(x < s.top())
				min = x;
			s.push(x);
			s.push(min);
		}
	}
	void Pop()
	{
		if(!s.empty())
		{
			s.pop();
			s.pop();
			if(!s.empty())
				min = s.top();
		}
	}
	int Min()
	{
		if(!s.empty())
			return s.top();
	}
private:
	stack<int> s;
	int min;
};

int main()
{
	MinStack ms;
	ms.Push(-1);
	ms.Push(2);
	ms.Push(0);
	ms.Push(5);
	ms.Push(4);
	int ret = ms.Min();
	ms.Pop();
	ms.Pop();
	ret = ms.Min();
	ms.Pop();
	ret = ms.Min();
	ms.Pop();
	ret = ms.Min();
	ms.Pop();
	ret = ms.Min();	
	system("pause");
	return 0;
}