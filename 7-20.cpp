#include <stack>
#include <iostream>
using namespace std;

//判断栈的压入弹出顺序：借助辅助栈，按照入栈顺序的数组将数据入栈，没入一次，就判断栈顶元素是否和出栈数组的当前元素是否相同，如果
//相同，就将辅助栈顶元素pop掉，并使出栈数组的下标+1。如果栈不为空，但栈顶元素与出栈数组的当前元素不相等，则返回false
bool  IsPopOrder(int* In, int sz1, int* Out, int sz2)
{
	if(In==NULL || Out==NULL)
		return false;
	int i=0;
	int j=0;
	stack<int> s;
	s.push(In[i++]);
	while(!s.empty() && i<sz1)
	{
		s.push(In[i++]);
		while (!s.empty() && s.top() == Out[j] && j<sz2)
		{
			s.pop();
			j++;
		}
	}
	if (s.empty() || j>=sz2)
		return true;
	else
		return false;
}

//求整数二进制中1的个数
int GetNumCount1(int num)
{
	int count = 0;
	if (num < 0)
	{
		count = 1;
		num = num*-1;
	}
	while (num)
	{
		if((num&1) == 1)
			count++;
		num >>= 1;
	}
	return count;
}

int GetNumCount2(int num)
{
	int count=0;
	while (num)
	{
		if(num & (num-1))
			count++;
		num >>= 1;
	}
	return count;
}


int main()
{
	int ret = GetNumCount1(10);
	//int ret = GetNumCount1(-10);
	int In[] = {1,2,3,4,5};
	//int Out[] = {4,5,3,2,1};
	//int Out[] = {4,5,2,3,1};
	int Out[] = {4,5,1};
	int sz1 = sizeof(In)/sizeof(In[0]);
	int sz2 = sizeof(Out)/sizeof(Out[0]);
	cout<<IsPopOrder(In,sz1,Out,sz2)<<endl;
	system("pause");
	return 0;
}