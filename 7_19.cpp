#include <stack>
#include <iostream>
using namespace std;

//1.实现一个栈Stack，要求实现Push（出栈）、Pop（入栈）、Min（返回最小值的操作）的时间复杂度为O(1) 


//两个栈实现
//实现一个最小栈：维护两个栈，minS和s，s用来一般的插入，minS内保证最小的值在栈顶，插入的值x只要小于当前minS栈顶值时就入minS栈内
//返回最小值时就可以直接返回minS栈顶的值
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

//一个栈实现
//思路分析：当栈为空时，将第一次插入的值插入两次，并将该次数据记录为min，以后每插入一个数就和s.top()作比较，如果x小于top值，则更新min，并在插入x之后
//再将min值插入一次---保证了min永远在栈顶
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