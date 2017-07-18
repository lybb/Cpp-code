#include <stack>
#include <queue>
#include <iostream>
using namespace std;

//两个栈实现一个队列
template<class T>
class StoQueue
{
public:
	//插入在s1中进行,删除在s2中进行
	void Push(T x)
	{
		s1.push(x);
	}
	void Pop()
	{
		int val = 0;
		if (s2.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		s2.pop();
	}
	T Front()
	{
		if(s2.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		T val = s2.top();
		return val;
	}
	T Back()
	{
		if(!s1.empty())
		{
			T val = s1.top();
			return val;
		}
		if(!s2.empty())
		{
			while (!s2.empty())
			{
				s1.push(s2.top());
				s2.pop();
			}
			return s1.top();
		}
	}
	size_t Size()
	{
		size_t sz1 = s1.size();
		size_t sz2 = s2.size();
		return sz1+sz2;
	}
	bool Empty()
	{
		return (s1.empty() && s2.empty());
	}
private:
	stack<T> s1;
	stack<T> s2;
};

//两个队列实现一个栈
template<typename T>
class QtoStack
{
public:
	void Push(T x)
	{
		q1.push(x);//将新插入的数据尾插到q1中---保证出栈顺序
	}
	void Pop()
	{
		//q1的数据插入到q2，当q1中的front和back执行同一个数时就不再向q2中插入
		if(!q1.empty())
		{
			while (q1.front() != q1.back())
			{
				q2.push(q1.front());  //将前n-1个元素插入到q2中
				q1.pop();
			}
			q1.pop();
		}
		else
		{
			if(!q2.empty())
			while (q2.front() != q2.back())
			{
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		}
	}
	T Top()
	{
		if (!q1.empty())
		{
			while (!q1.empty())
			{
				q2.push(q1.front());
				q1.pop();
			}
			return q2.back();
		}
		else
		{
			if(!q2.empty())
				return q2.back();
		}
	}
	int Size()
	{
		return q1.size() + q2.size();
	}
	bool Empty()
	{
		return (q1.empty() && q2.empty());
	}
private:
	queue<T> q1;
	queue<T> q2;
};


int main()
{
	//StoQueue<int> q1;
	//q1.Push(1);
	//q1.Push(2);
	//q1.Push(3);
	//cout<<q1.Empty()<<endl;
	//size_t sz = q1.Size();
	//int val1 = q1.Front();
	//int val2 = q1.Back();
	//q1.Pop();
	//q1.Pop();
	//q1.Pop();
	//cout<<q1.Empty()<<endl;
	QtoStack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	size_t sz = s.Size();
	int val = s.Top();
	s.Pop();
	s.Pop();
	sz = s.Size();
	val = s.Top();
	s.Pop();
	system("pause");
	return 0;
}